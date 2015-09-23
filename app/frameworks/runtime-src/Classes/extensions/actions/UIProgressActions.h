//
//  UIProgressBy.hpp
//  PokemonRPG
//
//  Created by Xin Wan on 9/19/15.
//
//

#ifndef UIProgressBy_hpp
#define UIProgressBy_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../GameMacros.h"

GAME_NS_BEGIN

class UIProgressBy : public cocos2d::ActionInterval
{
public:
    static UIProgressBy *create(float duration, float percent);
    
    //
    // Overrides
    //
    ACTION_INTERVAL_OVERRIDES(UIProgressBy);
    /**
     * @param time in seconds
     */
    virtual void update(float time) override;
    
protected:
    bool init(float duration, float percent);
    
    float _prev;
    float _start;
    float _delta;
    cocos2d::ui::LoadingBar *_loadingBar;
};

class UIProgressTo : public UIProgressBy
{
public:
    static UIProgressTo *create(float duration, float to);
    
    //
    // Overrides
    //
    ACTION_INTERVAL_OVERRIDES(UIProgressTo);
    
protected:
    bool init(float duration, float to);
    
    float _to;
};

GAME_NS_END

#endif /* UIProgressBy_hpp */
