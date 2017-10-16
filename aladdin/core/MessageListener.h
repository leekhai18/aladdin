#ifndef __ALADDIN_CORE_MESSAGE_LISTENER_H__
#define __ALADDIN_CORE_MESSAGE_LISTENER_H__

#include "MessageArgs.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(MessageListener)
public:
  MessageListener();

  virtual ~MessageListener();

  void subscribeGlobalMessage( const std::string& messageId, const std::function<void( MessageArgs* )>& callback );

  void unsubcribeGlobalMessage( const std::string& messageId );

  void unsubcribeAllMessages();

  void unsubcribeAllGlobalMessages();

  void unsubcribeAllObjectMessages();

private:
  std::unordered_map<std::string, std::vector<long>> _subcribedGlobalTokens;

  std::unordered_map<long, std::unordered_map<std::string, std::vector<long>>> _subcribedObjectTokens;
};
}

#endif //!__ALADDIN_CORE_MESSAGE_LISTENER_H__
