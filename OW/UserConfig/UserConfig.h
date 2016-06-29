#pragma once

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the USERCONFIG_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// USERCONFIG_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef USERCONFIG_EXPORTS
#define USERCONFIG_API __declspec(dllexport)
#else
#define USERCONFIG_API __declspec(dllimport)
#endif

// This class is exported from the UserConfig.dll
class USERCONFIG_API CUserConfig {
public:
	CUserConfig(void);
	// TODO: add your methods here.
};

extern USERCONFIG_API int nUserConfig;

USERCONFIG_API int fnUserConfig(void);
