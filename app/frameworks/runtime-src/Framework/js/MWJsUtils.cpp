#include "MWJsUtils.h"

using namespace JS;

MW_FRAMEWORK_BEGIN

MWJsUtils::MWJsUtils()
{
    
}

JS::Value MWJsUtils::nativeToJsValue(void *obj)
{
    js_proxy *proxy = jsb_get_native_proxy(obj);
    JSObject *jsObj = proxy->obj;
    
    return OBJECT_TO_JSVAL(jsObj);
}

bool MWJsUtils::executeOwnerFunction(void *owner, const std::string &funcName, int argCount, jsval *vp)
{
    return ScriptingCore::getInstance()->executeFunctionWithOwner(this->nativeToJsValue(owner), funcName.c_str(), argCount, vp);
}

bool MWJsUtils::executeOwnerFunction(void *owner, const std::string &funcName, int argCount, jsval *vp, JS::MutableHandleValue retVal)
{
    return ScriptingCore::getInstance()->executeFunctionWithOwner(this->nativeToJsValue(owner), funcName.c_str(), argCount, vp, retVal);
}

MW_FRAMEWORK_END