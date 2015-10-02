//
//  ScissorNode.hpp
//  PokemonRPG
//
//  Created by Winder Wan on 10/2/15.
//
//

#ifndef ScissorNode_hpp
#define ScissorNode_hpp

#include "cocos2d.h"
#include "../GameMacros.h"

GAME_NS_BEGIN

class ScissorNode : public cocos2d::Node
{
public:
    static ScissorNode *create();
    
    ScissorNode();
    bool init();
    
    //
    // Overrides
    //
    virtual void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4 &parentTransform, uint32_t parentFlags) override;
    
protected:
    cocos2d::Rect _getBoundingBoxToWorld();
    
    cocos2d::CustomCommand _beforeVisitCmd;
    cocos2d::CustomCommand _afterVisitCmd;
};

GAME_NS_END

#endif /* ScissorNode_hpp */
