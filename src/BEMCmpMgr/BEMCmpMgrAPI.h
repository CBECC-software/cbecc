
#ifndef __BEMCMPMGRAPI_H__
#define __BEMCMPMGRAPI_H__

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the BEMCMPMGR_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// BEMCMPMGR_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef BEMCMPMGR_EXPORTS
#define BEMCMPMGR_API __declspec(dllexport)
#else
#define BEMCMPMGR_API __declspec(dllimport)
#endif

#endif // __BEMCMPMGRAPI_H__
