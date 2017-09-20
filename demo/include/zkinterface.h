#ifndef ZKINTERFACE_H
#define ZKINTERFACE_H

#ifndef APICALL
#ifdef WIN32
#define APICALL __stdcall
#else
#define APICALL
#endif
#endif


#ifndef ZKAPI
#ifdef WIN32
#define ZKAPI __stdcall
#else
#define ZKAPI
#endif
#endif

#ifdef WIN32
#ifndef ZKINTERFACE
#ifndef _USRDLL 
#ifdef _LIB
#define ZKINTERFACE
#else
#define ZKINTERFACE __declspec(dllimport)
#endif
#else	//_ZKDLL
#define ZKINTERFACE
#endif	//_ZKDLL
#endif
#else
#define ZKINTERFACE
#endif



#endif	//ZKINTERFACE_H
