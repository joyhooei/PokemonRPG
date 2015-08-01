#include "MWViewSegue.h"
#include <new>

#include "cocos2d.h"
#include "MWGameView.h"
#include "MWGameScene.h"
#include "MWViewController.h"
#if MW_ENABLE_SCRIPT_BINDING
#include "../js/MWJsUtils.h"
#endif

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

MWViewSegue *MWViewSegue::create()
{
    auto pRet = new (nothrow) MWViewSegue();
    if (pRet && pRet->init()) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_RELEASE(pRet);
    return nullptr;
}

bool MWViewSegue::init()
{
    return true;
}

void MWViewSegue::viewReadyToSegue(MWViewController *controller)
{
    if (!controller) {
        CCLOG("Invalid view parameter.");
        return;
    }
    
#if MW_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeLua) {
        // lua todo
    } else if (_scriptType == kScriptTypeJavascript) {
        jsval args[1];
        args[0] = MWJsUtils::getInstance()->nativeToJsValue(controller);
        MWJsUtils::getInstance()->executeOwnerFunction(this, "viewReadyToSegue", 1, args);
    }
#endif
}

void MWViewSegue::viewDidSegue(MWViewController *controller)
{
    if (!controller) {
        CCLOG("Invalid scene parameter.");
        return;
    }
    
#if MW_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeLua) {
        // lua todo
    } else if (_scriptType == kScriptTypeJavascript) {
        jsval args[1];
        args[0] = MWJsUtils::getInstance()->nativeToJsValue(controller);
        MWJsUtils::getInstance()->executeOwnerFunction(this, "viewDidSegue", 1, args);
    }
#endif
}

void MWViewSegue::viewDidSegueBack(MWViewController *controller)
{
    if (!controller) {
        CCLOG("Invalid scene parameter.");
        return;
    }
    
#if MW_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeLua) {
        // lua todo
    } else if (_scriptType == kScriptTypeJavascript) {
        jsval args[1];
        args[0] = MWJsUtils::getInstance()->nativeToJsValue(controller);
        MWJsUtils::getInstance()->executeOwnerFunction(this, "viewDidSegueBack", 1, args);
    }
#endif
}

MWViewSegue::MWViewSegue()
{
    
}

MW_FRAMEWORK_END