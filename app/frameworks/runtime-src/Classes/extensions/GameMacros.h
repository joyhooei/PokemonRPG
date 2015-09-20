//
//  GameMacros.h
//  PokemonRPG
//
//  Created by Xin Wan on 9/19/15.
//
//

#ifndef GameMacros_h
#define GameMacros_h

#define GAME_NS_BEGIN namespace game {
#define GAME_NS_END }

#define ACTION_INTERVAL_OVERRIDES(__CLASS__)    \
virtual __CLASS__ *clone() const override;  \
virtual __CLASS__ *reverse(void) const override;    \
virtual void startWithTarget(cocos2d::Node *target) override;

#endif /* GameMacros_h */
