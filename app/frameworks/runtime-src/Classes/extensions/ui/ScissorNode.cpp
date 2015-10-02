//
//  ScissorNode.cpp
//  PokemonRPG
//
//  Created by Winder Wan on 10/2/15.
//
//

#include "ScissorNode.h"
#include <new>

using namespace cocos2d;
using namespace std;

GAME_NS_BEGIN

ScissorNode *ScissorNode::create()
{
    auto ret = new (nothrow) ScissorNode();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_RELEASE(ret);
    return nullptr;
}

bool ScissorNode::init()
{
    if (!Node::init()) {
        return false;
    }
    
    return true;
}

ScissorNode::ScissorNode()
: Node()
, _beforeVisitCmd()
, _afterVisitCmd()
{
    
}

void ScissorNode::visit(cocos2d::Renderer *renderer, const cocos2d::Mat4 &parentTransform, uint32_t parentFlags)
{
    _beforeVisitCmd.init(_globalZOrder);
    _beforeVisitCmd.func = [this] {
        glEnable(GL_SCISSOR_TEST);
        auto rect = this->_getBoundingBoxToWorld();
        Director::getInstance()->getOpenGLView()->setScissorInPoints(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
    };
    renderer->addCommand(&_beforeVisitCmd);
    
    Node::visit(renderer, parentTransform, parentFlags);
    
    _afterVisitCmd.init(_globalZOrder);
    _afterVisitCmd.func = [this] {
        glDisable(GL_SCISSOR_TEST);
    };
    renderer->addCommand(&_afterVisitCmd);
}

Rect ScissorNode::_getBoundingBoxToWorld()
{
    Rect bound = this->getBoundingBox();
    Mat4 trans = this->getNodeToWorldTransform();
    Vec4 originVec4 = Vec4(bound.origin.x, bound.origin.y, 0, 1);
    Vec4 transformedVec4 = trans * originVec4;
    bound.origin = Point(transformedVec4.x / transformedVec4.w, transformedVec4.y / transformedVec4.w);
    
    return bound;
}

GAME_NS_END