#ifndef KTHREADORIENTEDFUNCTION_H
#define KTHREADORIENTEDFUNCTION_H

#include <functional>
#include <QThread>

template <typename T>
class KThreadOrientedFunction {};




/**
 * @brief The KThreadOrientedFunction class contained function and pointer to QThread
 * @details
 *
 * This class is used in cases where we transfering function through threads and need to know from witch thread this function came.
 */
template <typename T, typename ...Args>
class KThreadOrientedFunction<T(Args...)> {
    std::function<T(Args...)> function;
    QThread *m_thread = QThread::currentThread();
public:
    template<typename Function>
    KThreadOrientedFunction(Function function) { this->function = function; };
    KThreadOrientedFunction() {};

    /**
     * @brief isNull
     * @return returns true if function is null
     */
    bool isNull() { return !function; };
    /**
     * @brief operator bool
     * @return true if function is not null
     */
    operator bool() const { return function; }

    /**
     * @brief operator () - standart functor for calling containing function
     * @param args - args of function
     * @return result of function
     */
    T operator()(Args... args) { return function(args...); }

    /**
     * @brief thread
     * @return pointer to QThread in witch function was created
     */
    QThread *thread() const { return m_thread; }
};

#endif // KTHREADORIENTEDFUNCTION_H
