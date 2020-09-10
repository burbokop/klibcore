#ifndef KARRAYPAINTEDTOOL_H
#define KARRAYPAINTEDTOOL_H

#include "kpaintedtool.h"
class QAbstractListModel;


/**
 * @brief The KPointerHandle class provides simple smart pointer
 * @details This class is created for controll life of objects in container
 * You can fill container by different objects with different store modes and simply control their life.\n
 * Store modes:\n
 * 1. AutoDestroy - object will be destroyed when container is destroued\n
 * 2. ManualDestroy - object will be destroyed when KPointerHandle::destroy will be called\n
 * 3. NoDestroy - it means that we controll life of this object by our own\n
 *
 */
template<typename T>
class KPointerHandle {
public: enum Mode { AutoDestoy, ManualDestroy, NoDestroy };
    K_READONLY_MEMBER(T*, data, data, setData, nullptr)
    K_READONLY_MEMBER(Mode, mode, mode, setMode, NoDestroy)
public:
    inline T *operator->() const { return m_data; }
    inline T *operator*() const { return m_data; }
    inline KPointerHandle(T *data = nullptr, Mode mode = NoDestroy) { m_data = data; m_mode = mode; }
    inline ~KPointerHandle() { if(m_mode == AutoDestoy) delete m_data; }
    template<typename C>
    static void destroy(const C &container) { for(auto c : container) { if(c.mode() == ManualDestroy) delete c.data(); } }
};


/**
 * @brief The KArrayPaintedTool inteface needed for implementations witch provides containers of painted tools
 */
class KArrayPaintedTool : public KPaintedTool {
    QList<KPointerHandle<KPaintedTool>> m_children;
public:
    KArrayPaintedTool();
    inline auto childrenBegin() { return m_children.begin(); }
    inline auto childrenEnd() { return m_children.end(); }
    inline void addChild(KPointerHandle<KPaintedTool> paintedTool) { m_children.push_back(paintedTool); }
    void addModel(QAbstractListModel *model, const QTextOption &option = QTextOption(), bool paintHeader = false, double hr = 1, QList<QByteArray> rolesSequance = QList<QByteArray>());
    void addText(QString text, const QTextOption &option = QTextOption());

    inline void clearChildren() { KPointerHandle<KPaintedTool>::destroy(m_children); m_children.clear(); }
    inline int childrenCount() { return m_children.size(); }
    inline ~KArrayPaintedTool() { KPointerHandle<KPaintedTool>::destroy(m_children); }
};

#endif // KARRAYPAINTEDTOOL_H
