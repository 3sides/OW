// UserConfig.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "UserConfig.h"


// This is an example of an exported variable
USERCONFIG_API int nUserConfig=0;

// This is an example of an exported function.
USERCONFIG_API int fnUserConfig(void)
{
    return 42;
}

// This is the constructor of a class that has been exported.
// see UserConfig.h for the class definition
CUserConfig::CUserConfig()
{
    return;
}
