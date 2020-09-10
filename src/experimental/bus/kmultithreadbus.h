#ifndef KMULTITHREADBUS_H
#define KMULTITHREADBUS_H


#include "kabstractbus.h"
#include <src/utility/kthreadorientedfunction.h>

/**
 * @brief The KMultithreadBus class inmpemets KAbstractBus and provides sending messages through threads
 */
template<typename KeyType, typename MessageType>
class KMultithreadBus : public KAbstractBus<KeyType, MessageType, KThreadOrientedFunction<void(MessageType)>> {
public:
    KMultithreadBus() {};
protected:
    virtual void invoke(KThreadOrientedFunction<void(MessageType)> function, const MessageType &message) override;
};

template<typename KeyType, typename MessageType>
void KMultithreadBus<KeyType, MessageType>::invoke(KThreadOrientedFunction<void(MessageType)> function, const MessageType &message) {
    if(function.thread() == QThread::currentThread()) {
        function(message);
    } else {
        QMetaObject::invokeMethod(function.thread(), [function, message]() {
            static_cast<KThreadOrientedFunction<void(MessageType)>>(function)(message);
        }, Qt::QueuedConnection);
    }
}


#endif // KMULTITHREADBUS_H
