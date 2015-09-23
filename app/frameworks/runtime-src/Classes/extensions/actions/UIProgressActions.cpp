//
//  UIProgressBy.cpp
//  PokemonRPG
//
//  Created by Xin Wan on 9/19/15.
//
//

#include "UIProgressActions.h"

#include <new>

using namespace std;
using namespace cocos2d;
using namespace cocos2d::ui;

GAME_NS_BEGIN

UIProgressBy *UIProgressBy::create(float duration, float percent)
{
    auto ret = new (nothrow) UIProgressBy();
    if (ret && ret->init(duration, percent)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_RELEASE(ret);
    return nullptr;
}

bool UIProgressBy::init(float duration, float percent)
{
    if (!ActionInterval::initWithDuration(duration)) {
        return false;
    }
    _delta = percent;
    return true;
}

UIProgressBy *UIProgressBy::clone() const
{
    return UIProgressBy::create(_duration, _delta);
}

UIProgressBy *UIProgressBy::reverse() const
{
    return UIProgressBy::create(_duration, -_delta);
}

void UIProgressBy::startWithTarget(cocos2d::Node *target)
{
    LoadingBar *loadingBar = dynamic_cast<LoadingBar *>(target);
    CCASSERT(loadingBar, "Target must be ui::LoadingBar");
    ActionInterval::startWithTarget(target);
    _prev = _start = loadingBar->getPercent();
    _loadingBar = loadingBar;
}

void UIProgressBy::update(float time)
{
    if (_target)
    {
#if CC_ENABLE_STACKABLE_ACTIONS
        float currentProgress = _loadingBar->getPercent();
        float diff = currentProgress - _prev;
        _start += diff;
        float newProgress = _start + (_delta * time);
        _loadingBar->setPercent(newProgress);
        _prev = newProgress;
#else
        _loadingBar->setPercent(_start + _delta * time);
#endif // CC_ENABLE_STACKABLE_ACTIONS
    }
}



UIProgressTo *UIProgressTo::create(float duration, float to)
{
    auto ret = new (nothrow) UIProgressTo();
    if (ret && ret->init(duration, to)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_RELEASE(ret);
    return nullptr;
}

bool UIProgressTo::init(float duration, float to)
{
    if (!ActionInterval::initWithDuration(duration)) {
        return false;
    }
    if (to < 0) {
        to = 0.0f;
    } else if (to > 100) {
        to = 100.0f;
    }
    _to = to;
    return true;
}

UIProgressTo *UIProgressTo::clone() const
{
    return UIProgressTo::create(_duration, _to);
}

UIProgressTo *UIProgressTo::reverse() const
{
    CCASSERT(false, "UIProgressTo doesn't support reverse.");
    return nullptr;
}

void UIProgressTo::startWithTarget(cocos2d::Node *target)
{
    LoadingBar *loadingBar = dynamic_cast<LoadingBar *>(target);
    CCASSERT(loadingBar, "Target must be ui::LoadingBar");
    ActionInterval::startWithTarget(target);
    _prev = _start = loadingBar->getPercent();
    _delta = _to - _start;
    _loadingBar = loadingBar;
}

GAME_NS_END