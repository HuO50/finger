#ifndef _libzkfp_h
#define _libzkfp_h
/**
*	@file		libzkfp.h
*	@brief		�ӿڶ���
*	@author		scar chen
*	@date		2016-04-12
*	@version	5.0
*	@par	��Ȩ��
*				ZKTeco
*	@par	��ʷ�汾			
*
*	@note
*
*/


#include "libzkfptype.h"


#ifdef __cplusplus
extern "C"
{
#endif

/**
	*	@brief	��ʼ����
	*	@param	:
	*		��
	*	@return
	*	����ֵ˵�����£�
	*	value			|	type		|	description of value
	*	----------------|---------------|-------------------------------
	*	0				|	int			|	�ɹ�
	*	����			|	int			|	ʧ��
	*	@note 
*/
ZKINTERFACE int APICALL ZKFPM_Init();

/**
	*	@brief	�ͷſ�
	*	@param	:
	*		��
	*	@return
	*	����ֵ˵�����£�
	*	value			|	type		|	description of value
	*	----------------|---------------|-------------------------------
	*	0				|	int			|	�ɹ�
	*	����			|	int			|	ʧ��
	*	@note 
*/
ZKINTERFACE int APICALL ZKFPM_Terminate();

/**
	*	@brief	��ȡ�豸��
	*	@param	:
	*		��
	*	@return
	*	����ֵ˵�����£�
	*		��ǰ����ָ�������豸��
	*	@note 
*/
ZKINTERFACE int APICALL ZKFPM_GetDeviceCount();

/**
	*	@brief	��ȡ�豸��Ϣ����
	*	@param	:
	*	����˵�����±�
	*	name			|	type		  |	param direction		|	description of param
	*	----------------|-----------------|---------------------|------------------------
	*	devNum			|	int			  |	[in]				|	�豸��
	*	devInfoList		|TZKFPDeviceInfo[]|	[out]				|	�豸��Ϣ����
	*	@return
	*	����ֵ˵�����£�
	*		���ػ�ȡ�豸��Ϣ��
	*	@note 
	*		ĿǰΪԤ���ӿ�
*/
ZKINTERFACE int APICALL ZKFPM_GetDeviceInfoList(int devNum, TZKFPDeviceInfo devInfoList[]);


/**
	*	@brief	��ȡ�豸��Ϣ
	*	@param	:
	*	����˵�����±�
	*	name			|	type		  |	param direction		|	description of param
	*	----------------|-----------------|---------------------|------------------------
	*	index			|	int			  |	[in]				|	�豸����
	*	pDevInfo		|PZKFPDeviceInfo  |	[out]				|	�豸��Ϣ�ṹ��ָ��
	*	@return
	*	����ֵ˵�����£�
	*	value			|	type		|	description of value
	*	----------------|---------------|-------------------------------
	*	0				|	int			|	�ɹ�
	*	����			|	int			|	ʧ��
	*	@note 
	*		ĿǰΪԤ���ӿ�
*/
ZKINTERFACE int APICALL ZKFPM_GetDeviceInfo(int index, PZKFPDeviceInfo pDevInfo);


/**
		*	@brief	���豸
		*	@param	:
		*	����˵�����±�
		*	name			|	type		  |	param direction		|	description of param
		*	----------------|-----------------|---------------------|------------------------
		*	index			|	int			  |	[in]				|	�豸����
		*	@return
		*	����ֵ˵�����£�
		*	value			|	type		|	description of value
		*	----------------|---------------|-------------------------------
		*	NULL			|	HANDLE		|	ʧ��
		*	����			|	HANDLE		|	�ɹ�
		*	@note 
	*/
	ZKINTERFACE HANDLE APICALL ZKFPM_OpenDevice(int index);

	/**
		*	@brief	�ر��豸
		*	@param	:
		*	����˵�����±�
		*	name			|	type		  |	param direction		|	description of param
		*	----------------|-----------------|---------------------|------------------------
		*	hDevice			|	HANDLE		  |	[in]				|	�豸����ʵ��ָ��
		*	@return
		*	����ֵ˵�����£�
		*	value			|	type		|	description of value
		*	----------------|---------------|-------------------------------
		*	0				|	int			|	�ɹ�
		*	����			|	int			|	ʧ��
		*	@note 
	*/
	ZKINTERFACE int APICALL ZKFPM_CloseDevice(HANDLE hDevice);

	/**
		*	@brief	��ȡ�ɼ�����
		*	@param	:
		*	����˵�����±�
		*	name			|	type		  |	param direction		|	description of param
		*	----------------|-----------------|---------------------|------------------------
		*	hDevice			|	HANDLE		  |	[in]				|	�豸����ʵ��ָ��
		*	pCapParams		|	PZKFPCapParams|	[out]				|	�ɼ�����
		*	@return
		*	����ֵ˵�����£�
		*	value			|	type		|	description of value
		*	----------------|---------------|-------------------------------
		*	0				|	int			|	�ɹ�
		*	����			|	int			|	ʧ��
		*	@note 
	*/
	ZKINTERFACE int APICALL ZKFPM_GetCaptureParams(HANDLE hDevice, PZKFPCapParams pCapParams);

	/**
		*	@brief	���ò���
		*	@param	:
		*	����˵�����±�
		*	name			|	type		  |	param direction		|	description of param
		*	----------------|-----------------|---------------------|------------------------
		*	hDevice			|	HANDLE		  |	[in]				|	�豸����ʵ��ָ��
		*	nParamCode		|	int			  |	[in]				|	��������
		*	paramValue		|	unsigned char*|	[in]				|	����ֵ
		*	cbParamValue	|	unsigned int  |	[in]				|	�������ݳ���
		*	@return
		*	����ֵ˵�����£�
		*	value			|	type		|	description of value
		*	----------------|---------------|-------------------------------
		*	0				|	int			|	�ɹ�
		*	����			|	int			|	ʧ��
		*	@note 
	*/
	ZKINTERFACE int APICALL ZKFPM_SetParameters(HANDLE hDevice, int nParamCode, unsigned char* paramValue, unsigned int cbParamValue);

	/**
		*	@brief	��ȡ����
		*	@param	:
		*	����˵�����±�
		*	name			|	type		  |	param direction		|	description of param
		*	----------------|-----------------|---------------------|------------------------
		*	hDevice			|	HANDLE		  |	[in]				|	�豸����ʵ��ָ��
		*	nParamCode		|	int			  |	[in]				|	��������
		*	paramValue		|	unsigned char*|	[out]				|	����ֵ
		*	cbParamValue	|	unsigned int* |	[out]				|	�������ݳ���
		*	@return
		*	����ֵ˵�����£�
		*	value			|	type		|	description of value
		*	----------------|---------------|-------------------------------
		*	0				|	int			|	�ɹ�
		*	����			|	int			|	ʧ��
		*	@note 
	*/
	ZKINTERFACE int APICALL ZKFPM_GetParameters(HANDLE hDevice, int nParamCode, unsigned char* paramValue, unsigned int* cbParamValue);
	
	/**
		*	@brief	��ȡָ��(ͼ��/ģ�壩
		*	@param	:
		*	����˵�����±�
		*	name			|	type		  |	param direction		|	description of param
		*	----------------|-----------------|---------------------|------------------------
		*	hDevice			|	HANDLE		  |	[in]				|	�豸����ʵ��ָ��
		*	fpImage			|	unsigned char*|	[out]				|	ָ��ͼ��
		*	cbFPImage		|	unsigned int  |	[in]				|	fpImage�ڴ��С
		*	fpTemplate		|	unsigned char*|	[out]				|	ָ��ģ��
		*	cbTemplate		|	unsigned int* |	[in/out]			|	ָ��ģ�峤��
		*	@return
		*	����ֵ˵�����£�
		*	value			|	type		|	description of value
		*	----------------|---------------|-------------------------------
		*	0				|	int			|	�ɹ�
		*	����			|	int			|	ʧ��
		*	@note 
	*/
	ZKINTERFACE int APICALL ZKFPM_AcquireFingerprint(HANDLE hDevice, unsigned char* fpImage, unsigned int cbFPImage, unsigned char* fpTemplate, unsigned int* cbTemplate);

	/**
		*	@brief	�����㷨����ʵ��
		*	@param	:
		*	��
		*	@return
		*	����ֵ˵�����£�
		*	value			|	type		|	description of value
		*	----------------|---------------|-------------------------------
		*	NULL			|	HANDLE		|	ʧ��
		*	����			|	HANDLE		|	�ɹ�
		*	@note 
	*/
	ZKINTERFACE HANDLE APICALL ZKFPM_CreateDBCache();

	/**
		*	@brief	�ͷ��㷨����ʵ��
		*	@param	:
		*	����˵�����±�
		*	name			|	type		  |	param direction		|	description of param
		*	----------------|-----------------|---------------------|------------------------
		*	hDBCache		|	HANDLE		  |	[in]				|	�㷨����ʵ��ָ��
		*	@return
		*	����ֵ˵�����£�
		*	value			|	type		|	description of value
		*	----------------|---------------|-------------------------------
		*	0				|	int			|	�ɹ�
		*	����			|	int			|	ʧ��
		*	@note 
	*/
	ZKINTERFACE int APICALL ZKFPM_CloseDBCache(HANDLE hDBCache);


	/**
		*	@brief	��3��ָ��ģ��ϳɵǼ�ģ��
		*	@param	:
		*	����˵�����±�
		*	name			|	type		  |	param direction		|	description of param
		*	----------------|-----------------|---------------------|------------------------
		*	hDBCache		|	HANDLE		  |	[in]				|	�㷨����ʵ��ָ��
		*	temp1			|	unsigned char*|	[in]				|	ָ��ģ��1
		*	temp2			|	unsigned char*|	[in]				|	ָ��ģ��2
		*	temp3			|	unsigned char*|	[in]				|	ָ��ģ��3
		*	regTemp			|	unsigned char*|	[out]				|	�Ǽ�ģ��
		*	cbRegTemp		|	unsigned int* |	[in/out]			|	�Ǽ�ģ�峤��
		*	@return
		*	����ֵ˵�����£�
		*	value			|	type		|	description of value
		*	----------------|---------------|-------------------------------
		*	0				|	int			|	�ɹ�
		*	����			|	int			|	ʧ��
		*	@note 
	*/
	ZKINTERFACE int APICALL ZKFPM_GenRegTemplate(HANDLE hDBCache, unsigned char* temp1, unsigned char* temp2, unsigned char* temp3, unsigned char* regTemp, unsigned int* cbRegTemp);
	
	/**
		*	@brief	����ָ��ģ�嵽����
		*	@param	:
		*	����˵�����±�
		*	name			|	type		  |	param direction		|	description of param
		*	----------------|-----------------|---------------------|------------------------
		*	hDBCache		|	HANDLE		  |	[in]				|	�㷨����ʵ��ָ��
		*	fid				|	unsigned int  |	[in]				|	��ָID
		*	fpTemplate		|	unsigned char*|	[in]				|	ָ��ģ��
		*	cbTemplate		|	unsigned int  |	[in]				|	ָ��ģ�峤��
		*	@return
		*	����ֵ˵�����£�
		*	value			|	type		|	description of value
		*	----------------|---------------|-------------------------------
		*	0				|	int			|	�ɹ�
		*	����			|	int			|	ʧ��
		*	@note 
	*/
	ZKINTERFACE int APICALL ZKFPM_AddRegTemplateToDBCache(HANDLE hDBCache, unsigned int fid, unsigned char* fpTemplate, unsigned int cbTemplate);

	/**
		*	@brief	�ӻ���ɾ��ָ��ģ��
		*	@param	:
		*	����˵�����±�
		*	name			|	type		  |	param direction		|	description of param
		*	----------------|-----------------|---------------------|------------------------
		*	hDBCache		|	HANDLE		  |	[in]				|	�㷨����ʵ��ָ��
		*	fid				|	unsigned int  |	[in]				|	��ָID
		*	@return
		*	����ֵ˵�����£�
		*	value			|	type		|	description of value
		*	----------------|---------------|-------------------------------
		*	0				|	int			|	�ɹ�
		*	����			|	int			|	ʧ��
		*	@note 
	*/
	ZKINTERFACE int APICALL ZKFPM_DelRegTemplateFromDBCache(HANDLE hDBCache, unsigned int fid);

	/**
		*	@brief	����㷨����
		*	@param	:
		*	����˵�����±�
		*	name			|	type		  |	param direction		|	description of param
		*	----------------|-----------------|---------------------|------------------------
		*	hDBCache		|	HANDLE		  |	[in]				|	�㷨����ʵ��ָ��
		*	@return
		*	����ֵ˵�����£�
		*	value			|	type		|	description of value
		*	----------------|---------------|-------------------------------
		*	0				|	int			|	�ɹ�
		*	����			|	int			|	ʧ��
		*	@note 
	*/
	ZKINTERFACE int APICALL ZKFPM_ClearDBCache(HANDLE hDBCache);

	/**
		*	@brief	��ȡ����ģ����
		*	@param	:
		*	����˵�����±�
		*	name			|	type		  |	param direction		|	description of param
		*	----------------|-----------------|---------------------|------------------------
		*	hDBCache		|	HANDLE		  |	[in]				|	�㷨����ʵ��ָ��
		*	fpCount			|	unsigned int* |	[out]				|	ָ��ģ����
		*	@return
		*	����ֵ˵�����£�
		*	value			|	type		|	description of value
		*	----------------|---------------|-------------------------------
		*	0				|	int			|	�ɹ�
		*	����			|	int			|	ʧ��
		*	@note 
	*/
	ZKINTERFACE int APICALL ZKFPM_GetDBCacheCount(HANDLE hDBCache, unsigned int* fpCount);


	/**
		*	@brief	ָ��ʶ��(1:N)
		*	@param	:
		*	����˵�����±�
		*	name			|	type		  |	param direction		|	description of param
		*	----------------|-----------------|---------------------|------------------------
		*	hDBCache		|	HANDLE		  |	[in]				|	�㷨����ʵ��ָ��
		*	fpTemplate		|	unsigned char*|	[in]				|	ָ��ģ��
		*	cbTemplate		|	unsigned int  | [in]				|	ָ��ģ���С
		*	FID				|	unsigned int* |	[out]				|	ָ����ID
		*	score			|	unsigned int* |	[out]				|	����
		*	@return
		*	����ֵ˵�����£�
		*	value			|	type		|	description of value
		*	----------------|---------------|-------------------------------
		*	0				|	int			|	�ɹ�
		*	����			|	int			|	ʧ��
		*	@note 
	*/
	ZKINTERFACE int APICALL ZKFPM_Identify(HANDLE hDBCache, unsigned char* fpTemplate, unsigned int cbTemplate, unsigned int* FID, unsigned int* score);

	/**
		*	@brief	1:1�ȶ��û�ָ��
		*	@param	:
		*	����˵�����±�
		*	name			|	type		  |	param direction		|	description of param
		*	----------------|-----------------|---------------------|------------------------
		*	hDBCache		|	HANDLE		  |	[in]				|	�㷨����ʵ��ָ��
		*	fpTemplate		|	unsigned char*|	[in]				|	ָ��ģ��
		*	cbTemplate		|	unsigned int  | [in]				|	ָ��ģ���С
		*	@return
		*	����ֵ˵�����£�
		*	value			|	type		|	description of value
		*	----------------|---------------|-------------------------------
		*	>0				|	int			|	����
		*	����			|	int			|	ʧ��
		*	@note 
	*/
	ZKINTERFACE int APICALL ZKFPM_VerifyByID(HANDLE hDBCache, unsigned int fid, unsigned char* fpTemplate, unsigned int cbTemplate);


	/**
		*	@brief	�ȶ���öָ��
		*	@param	:
		*	����˵�����±�
		*	name			|	type		  |	param direction		|	description of param
		*	----------------|-----------------|---------------------|------------------------
		*	hDBCache		|	HANDLE		  |	[in]				|	�㷨����ʵ��ָ��
		*	template1		|	unsigned char*|	[in]				|	ָ��ģ��1
		*	cbTemplate1		|	unsigned int  | [in]				|	ָ��ģ��1��С
		*	template2		|	unsigned char*|	[in]				|	ָ��ģ��2
		*	cbTemplate2		|	unsigned int  | [in]				|	ָ��ģ��2��С
		*	@return
		*	����ֵ˵�����£�
		*	value			|	type		|	description of value
		*	----------------|---------------|-------------------------------
		*	>0				|	int			|	����
		*	����			|	int			|	ʧ��
		*	@note 
	*/
	ZKINTERFACE int APICALL ZKFPM_MatchFinger(HANDLE hDBCache, unsigned char* template1, unsigned int cbTemplate1, unsigned char* template2, unsigned int cbTemplate2);

#ifdef __cplusplus
};
#endif


#endif	//_libzkfp_h