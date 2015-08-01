/******************************
 Description: JavaScript interaction utilities.
 Author: M.Wan
 Date: 7/20/2015
 ******************************/

#ifndef __JS_JS_UTILS__
#define __JS_JS_UTILS__

#include "../base/mwbase.h"
#include "ScriptingCore.h"

MW_FRAMEWORK_BEGIN

class MW_DLL MWJsUtils
{
    MW_SINGLETON(MWJsUtils);
public:
    JS::Value nativeToJsValue(void *obj);
    
    bool executeOwnerFunction(void *owner, const std::string &funcName, int argCount, jsval *vp);
    bool executeOwnerFunction(void *owner, const std::string &funcName, int argCount, jsval *vp, JS::MutableHandleValue retVal);
    
};

MW_FRAMEWORK_END

#endif /* defined(__JS_JS_UTILS__) */
