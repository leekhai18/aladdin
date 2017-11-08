#include "QuadNode.h"

NAMESPACE_ALA
{
QuadNode::QuadNode(): _index( 0 ) {}

QuadNode::~QuadNode() {}

QuadNode* QuadNode::buildTree() {
  QuadNode* root = new QuadNode();

  return root;
}

int QuadNode::getIndex() const {
  return _index;
}

void QuadNode::forEach( const std::function<void( GameObject* )> callback ) {
  for ( const auto it : _gameObjects ) {
    if ( it.second != NULL ) {
      callback( it.second );
    }
  }
}

QuadNode* QuadNode::getTopLeft() const {
  return _topLeft;
}

QuadNode* QuadNode::getTopRight() const {
  return _topRight;
}

QuadNode* QuadNode::getBottomLeft() const {
  return _bottomLeft;
}

QuadNode* QuadNode::getBottomRight() const {
  return _bottomRight;
}
}
