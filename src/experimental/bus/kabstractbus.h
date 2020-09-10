#ifndef KABSTRACTBUS_H
#define KABSTRACTBUS_H

#include <QList>


/**
 * \callgraph
 * @brief The KAbstractBus inteface summarizes data buses
 * @details KAbstractBus is warking on message driven system many part of program can subscribe on bus and each part can emit messages so that all subscribed parts catch it.
 * @note This class is available whithout Qt.
 */
template <typename KeyType, typename MessageType, typename FunctionHandle = std::function<void(MessageType)>>
class KAbstractBus {
    QMap<KeyType, QList<FunctionHandle>> data;
public:
    typedef FunctionHandle Function;
    KAbstractBus() {};
    /**
     * @brief emitMessage fuction sends message to bus
     * @param key - name / id / type / key of message
     * @param message
     */
    void emitMessage(const KeyType &key, const MessageType &message);
    /**
     * @brief registerHandler function subscribes on message with some name / id / type / key
     * @param key - name / id / type / key of message we want to subscribe
     * @param function - action that will be done on receiving message
     */
    void registerHandler(const KeyType &key, const FunctionHandle &function);
    /**
     * @brief registerHandler overload subscribes on message as KAbstractBus::registerHandler(KeyType, FunctionHandle) but use other format of function
     * @param key - name / id / type / key of message we want to subscribe
     * @param object - pointer to object witch member function we want to use
     * @param function - pointer ro member function
     */
    template<typename ClassType, typename ...Args>
    void registerHandler(const KeyType &key, ClassType *object, void(ClassType:: *function)(Args...));
protected:
    /**
     * @brief invoke virtual function contains instructions how to call <b>function</b> with particular <b>message</b>
     * @param function
     * @param message
     * @details For each inmlementation this function is different (for example in direct inmlementation function is immediately called,
     * in multithread inmpementation the argument is first transferred to the target thead, then is called)
     */
    virtual void invoke(FunctionHandle function, const MessageType &message) = 0;
};

template <typename KeyType, typename MessageType, typename FunctionHandle>
void KAbstractBus<KeyType, MessageType, FunctionHandle>::emitMessage(const KeyType &key, const MessageType &message) {
    QList<std::function<void(MessageType)>> &list = data[key];
    for(auto l : list) {
        invoke(l, message);
    }
}

template<typename KeyType, typename MessageType, typename FunctionHandle>
void KAbstractBus<KeyType, MessageType, FunctionHandle>::registerHandler(const KeyType &key, const FunctionHandle &function) {
    data[key].push_back(function);
}

template<typename KeyType, typename MessageType, typename FunctionHandle>
template<typename ClassType, typename ...Args>
void KAbstractBus<KeyType, MessageType, FunctionHandle>::registerHandler(const KeyType &key, ClassType *object, void(ClassType:: *function)(Args...)) {
    registerHandler(key, [object, function](Args ...args) {
        (object->*function)(args...);
    });
}

#endif // KABSTRACTBUS_H
