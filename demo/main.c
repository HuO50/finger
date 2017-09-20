#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include "include/zkinterface.h"
#include "include/libzkfperrdef.h"
#include "include/libzkfptype.h"
#include "include/libzkfp.h"

#ifndef HANDLE
#define HANDLE void *
#endif

#define ENROLLCNT 3
HANDLE m_hDevice = NULL;
HANDLE m_hDBCache = NULL;
unsigned char *m_pImgBuf = NULL;
unsigned char m_arrPreRegTemps[ENROLLCNT][MAX_TEMPLATE_SIZE];
unsigned int m_arrPreTempsLen[3];
int m_nLastRegTempLen = 0;
unsigned char m_szLastRegTemplate[MAX_TEMPLATE_SIZE];
int m_bIdentify = 0;
int m_bRegister = 0;
int m_tid = 0;
int m_enrollIdx = 0;

static void sighandler(int signo)
{
	if(m_pImgBuf)
	{
		free(m_pImgBuf);
		m_pImgBuf = NULL;
	}
	if(m_hDevice)
	{
		ZKFPM_CloseDevice(m_hDevice);
		ZKFPM_Terminate();
	}
	printf("sighandler\n");
	exit(signo);
}

void SetExitSignalHandle(void)
{
	int index;
	struct sigaction sa;
	int sigs[] = {
		SIGILL, SIGFPE, SIGABRT, SIGBUS,
		SIGSEGV, SIGHUP, SIGINT, SIGQUIT,
		SIGTERM
	};

	sa.sa_handler = sighandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESETHAND;
	for(index = 0; index < sizeof(sigs)/sizeof(sigs[0]); ++index) {
		if (sigaction(sigs[index], &sa, NULL) == -1) {
			perror("Could not set signal handler");
		}
	}
}

unsigned int GetTickCount()
{
	struct timeval tv;
	struct timezone tz;
	gettimeofday(&tv, &tz);
	return (tv.tv_sec*1000 + tv.tv_usec/1000);
}

void DoVerify(HANDLE handle, unsigned char *temp, int len)
{
	if(m_nLastRegTempLen > 0)	//enrolled template
	{
		if(m_bIdentify)
		{
			int ret = ZKFP_ERR_OK;
			unsigned int tid = 0;
			unsigned int score = 0;
			ret = ZKFPM_Identify(handle, temp, len, &tid, &score);
			if (ZKFP_ERR_OK != ret)
			{
				printf("Identify failed, ret = %d\n", ret);
			}
			else
			{
				printf("Identify succ, tid=%d, score=%d\n", tid, score);
			}
		}
		else
		{
			int ret = ZKFPM_MatchFinger(handle, m_szLastRegTemplate, m_nLastRegTempLen, temp, len);
			if (ZKFP_ERR_OK >= ret)
			{
				printf("Verify failed, ret=%d\n", ret);
			}
			else
			{
				printf("Verify succ, score=%d\n", ret);
			}
		}
	}
	else
	{
		printf("Please register first\n");
	}
}

int DoRegister(HANDLE handle, unsigned char* temp, int len)
{
	int ret = 0;
	if(m_enrollIdx >= ENROLLCNT)
	{
		m_enrollIdx = 0;	//restart enroll
		return 1;
	}
	if(m_enrollIdx > 0)
	{
		ret = ZKFPM_MatchFinger(m_hDBCache, m_arrPreRegTemps[m_enrollIdx-1], m_arrPreTempsLen[m_enrollIdx-1], temp, len);
		printf("ZKFPM_MatchFinger ret=%d\n", ret);
		if(ZKFP_ERR_OK >= ret)
		{
			m_enrollIdx = 0;
			printf("Resigter failed, please place the same finger\n");
			return 1;
		}
	}
	m_arrPreTempsLen[m_enrollIdx] = len;
	memcpy(m_arrPreRegTemps[m_enrollIdx], temp, len);
	if(++m_enrollIdx >= ENROLLCNT)
	{
		int ret = 0;
		unsigned char szRegTemp[MAX_TEMPLATE_SIZE] = {0x0};
		unsigned int cbRegTemp = MAX_TEMPLATE_SIZE;
		ret = ZKFPM_GenRegTemplate(m_hDBCache, m_arrPreRegTemps[0], m_arrPreRegTemps[1], m_arrPreRegTemps[2], szRegTemp, &cbRegTemp);
		m_enrollIdx = 0;
		if(ZKFP_ERR_OK == ret)
		{
			ret = ZKFPM_AddRegTemplateToDBCache(m_hDBCache, m_tid++, szRegTemp, cbRegTemp);
			if(ZKFP_ERR_OK == ret)
			{
				memcpy(m_szLastRegTemplate, szRegTemp, cbRegTemp);
				m_nLastRegTempLen = cbRegTemp;
				ZKFPM_GetDBCacheCount(m_hDBCache, &ret);
				printf("Register tid=%d succ, DBCount=%d\n", m_tid-1, ret);
			}
			else
			{
				printf("ZKFPM_AddRegTemplateToDBCache failed, ret=%d\n", ret);
			}
		}
		else
		{
			printf("Register failed, ZKFPM_GenRegTemplate=%d\n", ret);
		}
		return 1;
	}
	else
	{
		printf("Please still place %d times\n", ENROLLCNT-m_enrollIdx);
		return 0;
	}
}

int main(int argc, char *argv[])
{
	int m_imgFPWidth = 0;
	int m_imgFPHeight = 0;
	int m_bRegister = 0;
	int ret = 0;
	char cFun;
	
	SetExitSignalHandle();
	
	if((ret = ZKFPM_Init()) != ZKFP_ERR_OK)
	{
		printf("Init ZKFPM failed, ret=%d\n", ret);
		return 0;
	}
	printf("device count=%d\n", ZKFPM_GetDeviceCount());
	if((m_hDevice = ZKFPM_OpenDevice(0) ) == NULL)
	{
		printf("Open device failed\n");
		ZKFPM_Terminate();
		return 0;
	}
	m_hDBCache = ZKFPM_CreateDBCache();
	if (NULL == m_hDBCache)
	{
		printf("Create DBCache failed\n");
		ZKFPM_CloseDevice(m_hDevice);
		ZKFPM_Terminate();
		return 0;
	}
	TZKFPCapParams zkfpCapParams = {0x0};
	ZKFPM_GetCaptureParams(m_hDevice, &zkfpCapParams);
	m_imgFPWidth = zkfpCapParams.imgWidth;
	m_imgFPHeight = zkfpCapParams.imgHeight;
	m_pImgBuf = (unsigned char *)malloc(m_imgFPWidth*m_imgFPHeight);
	m_nLastRegTempLen = 0;
	memset(&m_szLastRegTemplate, 0x0, sizeof(m_szLastRegTemplate));

	printf("Init Succ\n");
	m_tid = 1;
	m_enrollIdx = 0;

	while(1)
	{
		printf("Please input key\ 
				\n['r' or 'R']: Register\
				\n['v' or 'V']: Verify]\
				\n['i' or 'I']: Identify\
				\n['e' or 'E']: Exit\n");
				
		scanf("%s", &cFun);
		
		if(('R' == cFun) || ('r' == cFun)) //Register
		{
			m_bRegister = 1;
			printf("Doing resiger, Please place finger 3 times\n");
		}
		else if(('V' == cFun) || ('v' == cFun)) //Verify
		{
			m_bRegister = 0;
			m_bIdentify = 0;
			printf("Doing verify, Please place finger\n");
		}
		else if(('I' == cFun) || ('i' == cFun)) //Identify
		{
			m_bRegister = 0;
			m_bIdentify = 1;
			printf("Doing identify, Please place finger\n");
		}
		else if(('E' == cFun) || ('e' == cFun))
		{
			break;
		}
		else
		{
			printf("Invalid key\n");
			continue;
		}
		
		
		while(1)
		{
			unsigned char szTemplate[MAX_TEMPLATE_SIZE];
			unsigned int tempLen = MAX_TEMPLATE_SIZE;
			int nTick = 0;
			
			nTick = GetTickCount();
			int ret = ZKFPM_AcquireFingerprint(m_hDevice, m_pImgBuf, m_imgFPWidth*m_imgFPHeight, szTemplate, &tempLen);			
			if (ZKFP_ERR_OK == ret)
			{
				printf("ZKFPM_AcquireFingerprint ret=%d, tempLen=%d, time=%d\n", ret, tempLen, GetTickCount()-nTick);
				if(m_bRegister) //Register
				{
					if(1 == DoRegister(m_hDBCache, szTemplate, tempLen))
					{
						break;
					}
				}
				else	//Identify
				{
					DoVerify(m_hDBCache, szTemplate, tempLen);
					break;
				}
			}
			
			usleep(100000);
		}
		
		
	}	
	
	if(m_pImgBuf)
	{
		free(m_pImgBuf);
		m_pImgBuf = NULL;
	}
	if(m_hDevice)
	{
		ZKFPM_CloseDevice(m_hDevice);
		ZKFPM_Terminate();
	}
	printf("Exit\n");
	return 1;
}
