//
//  UITextActions.hpp
//  PokemonRPG
//
//  Created by Xin Wan on 9/23/15.
//
//

#ifndef UITextActions_hpp
#define UITextActions_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../GameMacros.h"
#include <vector>
#include <string>

GAME_NS_BEGIN

class UITextOneByOne : public cocos2d::ActionInterval
{
public:
    static UITextOneByOne *create(float duration, const std::vector<std::string> &stringList);
    
    //
    // Overrides
    //
    ACTION_INTERVAL_OVERRIDES(UITextOneByOne);
    /**
     * @param time in seconds
     */
    virtual void update(float time) override;
    
protected:
    bool init(float duration, const std::vector<std::string> &stringList);
    
    std::vector<std::string> _stringList;
    float _timeOnce;
    cocos2d::ui::Text *_text;
};

GAME_NS_END

#endif /* UITextActions_hpp */
