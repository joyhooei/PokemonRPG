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
#include "../GameMacros.h"

GAME_NS_BEGIN

class UIProgressBy : public cocos2d::ActionInterval
{
public:
    static UIProgressBy *create(float duration, float percent);
    
    //
    // Overrides
    //
    virtual UIProgressBy *clone() const override;
    virtual UIProgressBy *reverse(void) const  override;
    virtual void startWithTarget(cocos2d::Node *target) override;
    /**
     * @param time in seconds
     */
    virtual void update(float time) override;
    
protected:
    bool init(float duration, float percent);
    
    float _prev;
    float _start;
    float _delta;
};

class UIProgressTo : public UIProgressBy
{
public:
    static UIProgressTo *create(float duration, float to);
    
    //
    // Overrides
    //
    virtual UIProgressTo *clone() const override;
    virtual UIProgressTo *reverse(void) const  override;
    virtual void startWithTarget(cocos2d::Node *target) override;
    
protected:
    bool init(float duration, float to);
    
    float _to;
};

GAME_NS_END

#endif /* UIProgressBy_hpp */
