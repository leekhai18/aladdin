#ifndef __ALADDIN_CORE_QUAD_NODE_H__
#define __ALADDIN_CORE_QUAD_NODE_H__

#include "CoreInclude.h"
#include "ClassMeta.h"
#include "GameObject.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(QuadNode)
public:
  QuadNode();

  virtual ~QuadNode();

  static QuadNode* buildTree();

  int getIndex() const;

  void forEach( const std::function<void( GameObject* )> callback );

  QuadNode* getTopLeft() const;

  QuadNode* getTopRight() const;

  QuadNode* getBottomLeft() const;

  QuadNode* getBottomRight() const;

private:
  int _index;

  QuadNode* _topLeft;

  QuadNode* _topRight;

  QuadNode* _bottomLeft;

  QuadNode* _bottomRight;

  std::unordered_map<long, GameObject*> _gameObjects;
};

}

#endif //!__ALADDIN_CORE_QUAD_NODE_H__
