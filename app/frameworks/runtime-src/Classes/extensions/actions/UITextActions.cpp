//
//  UITextActions.cpp
//  PokemonRPG
//
//  Created by Xin Wan on 9/23/15.
//
//

#include "UITextActions.h"

#include <algorithm>
#include <new>

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace std;

GAME_NS_BEGIN

UITextOneByOne *UITextOneByOne::create(float duration, const std::vector<std::string> &stringList)
{
    auto ret = new (nothrow) UITextOneByOne();
    if (ret && ret->init(duration, stringList)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_RELEASE(ret);
    return nullptr;
}

bool UITextOneByOne::init(float duration, const std::vector<std::string> &stringList)
{
    if (!ActionInterval::initWithDuration(duration)) {
        return false;
    }
    
    if (stringList.size() <= 0) {
        return false;
    }
    _stringList = stringList;
    _timeOnce = 1.0f / _stringList.size();
    
    return true;
}

UITextOneByOne *UITextOneByOne::clone() const
{
    return UITextOneByOne::create(_duration, _stringList);
}

UITextOneByOne *UITextOneByOne::reverse() const
{
    std::vector<std::string> stringList(_stringList);
    std::reverse(stringList.begin(), stringList.end());
    return UITextOneByOne::create(_duration, stringList);
}

void UITextOneByOne::startWithTarget(cocos2d::Node *target)
{
    Text *text = dynamic_cast<Text *>(target);
    CCASSERT(text, "Target must be ui::Text");
    ActionInterval::startWithTarget(target);
    _text = text;
}

void UITextOneByOne::update(float time)
{
    if (_target) {
        size_t index = floor(time / _timeOnce);
        if (index >= _stringList.size()) {
            index = _stringList.size() - 1;
        }
        _text->setString(_stringList[index]);
    }
}

GAME_NS_END