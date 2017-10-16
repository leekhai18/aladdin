/*
* Created by phuctm97 on Sep 27th 2017
*/

#include "Node.h"
#include "GameManager.h"
#include "StdHelper.h"

NAMESPACE_ALA
{
  ALA_CLASS_SOURCE_2(ala::Node, ala::Initializable, ala::Releasable)

  Node::Node(Scene* parentScene, const std::string& name)
  : _id(GameManager::get()->newId()),
  _name(name),
  _parentScene(parentScene),
  _active(false),
  _selfInitialize(true),
  _toReleaseInNextFrame(false),
  _origin ( 0.5, 0.5 ),
  _scale ( 1,1 ),
  _position ( 0,0 ),
  _rotation ( 0 ) {
  // check initial state
  ALA_ASSERT((!isInitialized()) && (!isInitializing()) && (!isReleased()) && (!isReleasing()));

  // attach to GameManager
  GameManager::get()->attach(this);

  // make sure parent scene is not null
  ALA_ASSERT(_parentScene != NULL);

  // attach to Scene
  _parentScene->addNode(this);

  // for debug memory allocation
  TOTAL_NODES_CREATED++;
}

Node::~Node() {
  if (isInitialized()) {
    // make sure object released after destruction
    ALA_ASSERT(isReleased());
  }

  // for debug memory allocation
  TOTAL_NODES_DELETED++;
}

long Node::getId() const {
  return _id;
}

const std::string& Node::getName() const {
  return _name;
}

Scene* Node::getParentScene() const {
  return _parentScene;
}

bool Node::isActive() const {
  return _active;
}

void Node::setActive(const bool val) {
  _active = val;
}

bool Node::isSelfInitialize() const {
  return _selfInitialize;
}

void Node::setSelfInitialize(const bool val) {
  _selfInitialize = val;
}

const Vec2& Node::getPosition ( ) const
{
    return _position;
}

float Node::getPositionX ( ) const
{
    return _position.getX();
}

float Node::getPositionY ( ) const
{
    return _position.getY();
}

void Node::setPosition ( const Vec2& position )
{
    _position = position;
}

void Node::setPosition ( const float x, const float y )
{
    _position = Vec2(x,y);
}

void Node::setPositionX ( const float x )
{
    _position.setX(x);
}

void Node::setPositionY ( const float y )
{
    _position.setY(y);
}

const Vec2& Node::getScale ( ) const
{
  return _scale;
}

void Node::setScale ( const Vec2& scale )
{
  _scale = scale;
}

void Node::setScaleX ( const float x )
{
  _scale.setX(x);
}

void Node::setScaleY ( const float y )
{
  _scale.setY(y);
}

void Node::setScale ( const float scale )
{
  _scale = Vec2(scale, scale);
}

float Node::getRotation ( ) const
{
  return _rotation;
}

void Node::setRotation ( const float rotation )
{
  _rotation = rotation;
}

Mat4 Node::getTransformationMatrix ( ) const
{
  const Mat4 matRotate = Mat4::getRotationZMatrix(D3DXToRadian(_rotation));
  const Mat4 matScale = Mat4::getScalingMatrix(_scale);
  const Mat4 matTranslate = Mat4::getTranslationMatrix(_position);

  return matRotate * matScale * matTranslate;

}

  // ===========================================================
// Events
// ===========================================================

void Node::initialize() {
  // make sure object is not initialized;
  ALA_ASSERT((!isInitialized()) && (!isInitializing()));

  setToInitializing();

  // TODO: lock mutual exclusive when run in multithreading mode

  //init

  setToInitialized();

  // activate
  setActive(true);
}

void Node::update(const float delta) {
  if (isReleasing() || isReleased()) return;

  // update to release in next frame
  if (_toReleaseInNextFrame) {
    release();
    _toReleaseInNextFrame = false;
    return;
  }

  if (!isInitialized()) {
    if (isSelfInitialize()) {
      initialize();
    }
    else return;
  }

  if (!isActive()) return;
}

void Node::render() {
  if ((!isInitialized()) || isReleasing() || isReleased()) return;
}

void Node::release() {

  // make sure object is initialized and not released
  ALA_ASSERT(isInitialized() && (!isReleasing()) && (!isReleased()));

  setToReleasing();

  // TODO: lock mutual exclusive when run in multithreading mode
  
  // remove from parent scene
  if (_parentScene != NULL) {
    _parentScene->removeNode(this);
  }

  // detach from GameManager
  GameManager::get()->detach(this);

  setToReleased();

  // destroy
  delete this;
}

void Node::releaseInNextFrame() {
  // make sure object is initialized and not released
  ALA_ASSERT(isInitialized() && (!isReleasing()) && (!isReleased()));
  _toReleaseInNextFrame = true;
}


// ============================================
// Debug memory allocation
// ============================================

long Node::TOTAL_NODES_CREATED(0);

long Node::TOTAL_NODES_DELETED(0);
}
