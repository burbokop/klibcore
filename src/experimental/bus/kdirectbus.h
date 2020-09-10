#ifndef KDIRECTBUS_H
#define KDIRECTBUS_H

#include "kabstractbus.h"

/**
 * @brief The KDirectBus class inmpemets KAbstractBus and provides sending direct messages
 * @note This class is available whithout Qt.
 */
template<typename KeyType, typename MessageType>
class KDirectBus : public KAbstractBus<KeyType, MessageType> {
public:
    KDirectBus() {};
    virtual void invoke(typename KAbstractBus<KeyType, MessageType>::Function function, const MessageType &message) override;
};

template<typename KeyType, typename MessageType>
void KDirectBus<KeyType, MessageType>::invoke(typename KAbstractBus<KeyType, MessageType>::Function function, const MessageType &message) {
    function(message);
}

#endif // KDIRECTBUS_H
