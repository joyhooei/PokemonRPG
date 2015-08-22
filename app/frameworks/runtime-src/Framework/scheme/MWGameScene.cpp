#include "MWGameScene.h"
#include "cocos2d.h"
#include "MWViewController.h"
#include "MWGameView.h"
#include "MWViewSegue.h"
#include "ScriptingCore.h"
#if MW_ENABLE_SCRIPT_BINDING
#include "../js/MWJsUtils.h"
#endif
#include "../platform/MWSystemHelper.h"
#include <new>

#define MEMORY_SCHEDULER_NAME "MEMORY_CHECK_SCHEDULER"

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

MWGameScene *MWGameScene::create()
{
    auto pScene = new (nothrow) MWGameScene();
    if (pScene && pScene->init()) {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_RELEASE(pScene);
    return nullptr;
}

MWGameScene *MWGameScene::createWithParams(mwframework::MWDictionary *params)
{
    auto pScene = new (nothrow) MWGameScene();
    if (pScene && pScene->init(params)) {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_RELEASE(pScene);
    return nullptr;
}

bool MWGameScene::init(MWDictionary *params)
{
    _viewControllers = new (nothrow) MWDictionary();
    if (_viewControllers) {
        if (params) {
            _params = params->clone();
            // the copy is autoreleased.
            _params->retain();
        } else {
            _params = new (nothrow) MWDictionary();
            if (!_params) {
                return false;
            }
        }
        return true;
    }
    CC_SAFE_RELEASE(_params);
    CC_SAFE_RELEASE(_viewControllers);
    return false;
}

MWGameScene::MWGameScene()
: _params(nullptr)
, _viewControllers(nullptr)
, _memoryWarningLine(400)
{
    
}

MWGameScene::~MWGameScene()
{
    CC_SAFE_RELEASE(_params);
    CC_SAFE_RELEASE(_viewControllers);
}

void MWGameScene::onEnter()
{
    Scene::onEnter();
    
#ifndef MW_DISABLE_MEMORY_DETECTION
    // open scheduler to check memory.
    if (!Director::getInstance()->getScheduler()->isScheduled(MEMORY_SCHEDULER_NAME, this)) {
        Director::getInstance()->getScheduler()->schedule(MW_CALLBACK_1(MWGameScene::checkMemory, this), this, 10, CC_REPEAT_FOREVER, 60, false, MEMORY_SCHEDULER_NAME);
    }
    #endif
}

void MWGameScene::onExit()
{
    // unload all view controllers.
    this->unloadAllViewControllers();
    
#ifndef MW_DISABLE_MEMORY_DETECTION
    // close the memory scheduler
    Director::getInstance()->getScheduler()->unschedule(MEMORY_SCHEDULER_NAME, this);
#endif
    
    Scene::onExit();
}

void MWGameScene::onEnterTransitionDidFinish()
{
    Scene::onEnterTransitionDidFinish();
    
#if MW_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeLua) {
        // lua todo
    } else if (_scriptType == kScriptTypeJavascript) {
        MWJsUtils::getInstance()->executeOwnerFunction(this, "onEnterTransitionDidFinish", 0, nullptr);
    }
#endif
}

void MWGameScene::onExitTransitionDidStart()
{
#if MW_ENABLE_SCRIPT_BINDING
    if (_scriptType == kScriptTypeLua) {
        // lua todo
    } else if (_scriptType == kScriptTypeJavascript) {
        MWJsUtils::getInstance()->executeOwnerFunction(this, "onExitTransitionDidStart", 0, nullptr);
    }
#endif
    
    Scene::onExitTransitionDidStart();
}

void MWGameScene::addParameter(const std::string &key, const std::string &param)
{
    _params->setObjectForKey(key, __String::create(param));
}

std::string MWGameScene::getParameter(const std::string &key)
{
    return static_cast<__String *>(_params->objectForKey(key))->getCString();
}

void MWGameScene::loadViewController(mwframework::MWViewController *controller, const std::string &identifier)
{
    // check parameter.
    if (!controller || identifier.size() <= 0) {
        MW_THROW_EXCEPTION(1006);
    }
    if (_viewControllers->hasKey(identifier)) {
        MW_THROW_EXCEPTION(1011);
    }
    controller->_scene = this;
    controller->_identifer = identifier;
    // initialize the view
    MWViewSegue *pSegue = controller->segue();
    if (pSegue) {
        pSegue->viewReadyToSegue(controller);
    }
    controller->viewDidLoad();
    this->addChild(controller->view());
    _viewControllers->setObjectForKey(identifier, controller);
    // what to do after the loading
    if (pSegue) {
        pSegue->viewDidSegue(controller);
    }
    
    this->detectMemory();
}

void MWGameScene::unloadViewController(mwframework::MWViewController *controller)
{
    // check parameter.
    if (!controller) {
        MW_THROW_EXCEPTION(1006);
    }
    if (_viewControllers->hasKey(controller->getIdentifier())) {
        controller->view()->removeFromParent();
        controller->_scene = nullptr;
        controller->viewDidUnload();
        // what to do after the unloading
        MWViewSegue *pSegue = controller->segue();
        if (pSegue) {
            pSegue->viewDidSegueBack(controller);
        }
        _viewControllers->removeObjectForKey(controller->getIdentifier());
    }
}

void MWGameScene::unloadViewControllerByIdentifier(const std::string &identifier)
{
    MWViewController *pVc = this->getViewControllerByIdentifier(identifier);
    if (pVc) {
        this->unloadViewController(pVc);
    }
}

MWViewController *MWGameScene::getViewControllerByIdentifier(const std::string &identifier)
{
    if (identifier.size() <= 0) {
        return nullptr;
    }
    MWViewController *pVc = nullptr;
    if (_viewControllers->hasKey(identifier)) {
        pVc = static_cast<MWViewController*>(_viewControllers->objectForKey(identifier));
        return pVc;
    }
    return nullptr;
}

void MWGameScene::unloadAllViewControllers()
{
    auto allKeys = _viewControllers->allKeys();
    for (auto &key : allKeys) {
        this->unloadViewControllerByIdentifier(key);
    }
    _viewControllers->clear();
}

void MWGameScene::detectMemory()
{
    // detect memory
    double memory = MWSystemHelper::getInstance()->getCurrentUsedMemory();
    if (memory >= _memoryWarningLine) {
        auto allKeys = _viewControllers->allKeys();
        MWViewController *pVc = nullptr;
        for (auto &key : allKeys) {
            pVc = static_cast<MWViewController*>(_viewControllers->objectForKey(key));
            pVc->didReceiveMemoryWarning();
        }
    }
}

void MWGameScene::checkMemory(float dt)
{
    this->detectMemory();
}

MW_FRAMEWORK_END