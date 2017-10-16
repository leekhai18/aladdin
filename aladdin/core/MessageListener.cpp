#include "MessageListener.h"
#include "GameManager.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0( ala::MessageListener )

MessageListener::MessageListener() {}

MessageListener::~MessageListener() {
  unsubcribeAllMessages();
}

void MessageListener::subscribeGlobalMessage( const std::string& messageId, const std::function<void( MessageArgs* )>& callback ) {
  if ( callback == NULL ) return;

  const auto token = GameManager::get()->getGlobalMessenger()->subscribe( messageId, callback );

  const auto vecIt = _subcribedGlobalTokens.find( messageId );
  if ( vecIt == _subcribedGlobalTokens.end() ) {
    std::vector<long> vec;
    vec.push_back( token );
    _subcribedGlobalTokens.emplace( messageId, vec);
  }
  else {
    auto& vec = vecIt->second;
    vec.push_back( token );
  }
}

void MessageListener::unsubcribeGlobalMessage( const std::string& messageId ) {
  for ( const auto token : _subcribedGlobalTokens[messageId] ) {
    GameManager::get()->getGlobalMessenger()->unsubscribe( messageId, token );
  }
  _subcribedGlobalTokens.erase( messageId );
}

void MessageListener::unsubcribeAllMessages() {
  unsubcribeAllGlobalMessages();
  unsubcribeAllObjectMessages();
}

void MessageListener::unsubcribeAllGlobalMessages() {
  for ( const auto vecIt : _subcribedGlobalTokens ) {
    for ( const auto token : vecIt.second ) {
      GameManager::get()->getGlobalMessenger()->unsubscribe( vecIt.first, token );
    }
  }
  _subcribedGlobalTokens.clear();
}

void MessageListener::unsubcribeAllObjectMessages() {
  for ( const auto mapIt : _subcribedObjectTokens ) {
    const auto object = GameManager::get()->getNodeById( mapIt.first );
    if ( object == NULL ) continue;

    for ( const auto vecIt : mapIt.second ) {
      for ( const auto token : vecIt.second ) {
        object->getMessenger()->unsubscribe( vecIt.first, token );
      }
    }
  }
  _subcribedObjectTokens.clear();
}
}
