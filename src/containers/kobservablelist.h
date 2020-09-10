#ifndef OBSERVABLELIST_H
#define OBSERVABLELIST_H

#include <src/kmacro.h>
#include <QAbstractItemModel>
#include <QRegularExpression>

class KObservableModel;

/**
 * @brief The KObservableList class provides list functions with ability of sending notification to gui
 * @details This list if developed for storing only QObject and inherited by classes instances.
 * If you change list (add new object, remove, change value of object) if says to qml what is changed and updates visualization
 * To get notification you need to detachModel special model witch is inherited by QAbstractListModel and pass it to qml
 */
template <class T>
class KObservableList {
public:
    explicit KObservableList();
    ~KObservableList();
    /**
     * @brief push_back function adds one element to the end
     */
    void push_back(T*);
    /**
     * @brief at function gives value by index
     * @return
     */
    T* at(int) const;
    /**
     * @brief remove function removes one element by index
     */
    void remove(int);
    /**
     * @brief removeOne function removes element by value
     * @return
     */
    bool removeOne(T*);
    /**
     * @brief takeAt function removes element and returns it
     * @param index
     * @return value
     */
    T* takeAt(int index);
    /**
     * @brief indexOf function gies index of value
     * @return index
     */
    inline int indexOf(T*) const;
    /**
     * @brief clear function cleares all data
     */
    void clear();
    /**
     * @brief insert function inserts value by index
     * @param index
     * @param value
     */
    void insert(int index, T* value);
    /**
     * @brief count - gives count of elements
     * @return
     */
    int count() const { return m_data.count(); }
    /**
     * @brief size - gicves size of list (the same as KObservableList<T>::count)
     * @return
     */
    int size() const { return m_data.size(); }
    /**
     * @brief begin - gives begin iterator
     */
    auto begin() const { return m_data.begin(); }
    /**
     * @brief end - gives end iterator
     */
    auto end() const { return m_data.end(); }
    /**
     * @brief setFilterRule function sets filter rule
     * @param property - the property by which the filtering will take place
     * @param regex - rule (all elements with values of property <b>property</b> witch is not match with this regex will be filtered out)
     */
    void setFilterRule(const QString &property, const QRegularExpression &regex);

    /**
     * @brief detachModel function detaches model
     * @param parent
     * @return pointer to model
     * @details After calling this function obserable list will not control life of model so you need to do it by your own.
     */
    KObservableModel* detachModel(QObject *parent = nullptr) const;

private:
    QList<T*> m_data;
    KObservableModel *m_modelShell;
    QPair<QString, QRegularExpression> m_filterRule;
    bool filt(QVariant value);
};

/**
 * @brief The KObservableModel class is inmplementation of QAbstractListModel and is used by KObservableList
 * @details This class can not be insantiated without KObservableList instance
 * You can get instance of KObservableModel by function KObservableList::detachModel and pass to qml.
 * It can be used as standart QAbstractListModel with role <b>object</b>.
 */
class KObservableModel : public QAbstractListModel
{
    Q_OBJECT
    K_QML_INTERFACE(KObservableModel)
    template<typename> friend class KObservableList;
    KObservableModel() {}
public:
    int rowCount(const QModelIndex &) const override {
        return m_sizzer();
    }
    QVariant data(const QModelIndex &index, int) const override {
        auto object = m_getter(index.row());
        if(m_filter(object)) {
            return QVariant::fromValue(object);
        }

        return QVariant::fromValue<QObject*>(nullptr);
    }

    QHash<int, QByteArray> roleNames() const override { return {{ Qt::UserRole + 1, "object" }};}
private:
    std::function<QObject*(int)> m_getter;
    std::function<int()> m_sizzer;
    std::function<bool(QObject*)> m_filter;
};


template<class T>
KObservableList<T>::KObservableList() {
    m_modelShell = new KObservableModel();
    m_modelShell->m_getter = [this](int ind){ return static_cast<QObject*>(this->m_data[ind]); };
    m_modelShell->m_sizzer = [this](){ return this->m_data.count(); };
    m_modelShell->m_filter = [this](QObject* object) { return m_filterRule.first.isEmpty() ? true : filt(object->property(m_filterRule.first.toStdString().c_str())); };
}

template<class T>
KObservableList<T>::~KObservableList() {
    if(m_modelShell && m_modelShell->parent() == nullptr) {
        delete m_modelShell;
    }
}

template<class T>
void KObservableList<T>::push_back(T *v)
{
    m_modelShell->beginInsertRows(QModelIndex(), m_data.count(), m_data.count());
    m_data.append(v);
    m_modelShell->endInsertRows();
}

template<class T>
T *KObservableList<T>::at(int ind) const {
    return m_data[ind];
}

template<class T>
void KObservableList<T>::remove(int ind)
{
    m_modelShell->beginRemoveRows(QModelIndex(), ind, ind);
    auto r =  m_data.takeAt(ind);
    m_modelShell->endRemoveRows();
}

template<class T>
T* KObservableList<T>::takeAt(int index)
{
    m_modelShell->beginRemoveRows(QModelIndex(), index, index);
    auto r =  m_data.takeAt(index);
    m_modelShell->endRemoveRows();
    return r;
}

template<class T>
bool KObservableList<T>::removeOne(T *v)
{
    int index = m_data.indexOf(v);
    if(index >= 0) {
        m_modelShell->beginRemoveRows(QModelIndex(), index, index);
        m_data.removeAt(index);
        m_modelShell->endRemoveRows();
        return true;
    }
    return false;
}

template<class T>
int KObservableList<T>::indexOf(T *v) const
{
    return m_data.indexOf(v);
}

template<class T>
void KObservableList<T>::clear()
{
    m_modelShell->beginResetModel();
    m_data.clear();
    m_modelShell->endResetModel();
}

template<class T>
void KObservableList<T>::insert(int index, T *value)
{

    if (index > m_data.size() - 1) push(value);
    else if (index < 0){

        m_modelShell->beginInsertRows(QModelIndex(), 0, 0);
        m_data.push_front(value);
        m_modelShell->endInsertRows();
    }
    else
    {
        m_modelShell->beginInsertRows(QModelIndex(), index, index);
        m_data.insert(index, value);
        m_modelShell->endInsertRows();
    }
}

template<class T>
void KObservableList<T>::setFilterRule(const QString &property, const QRegularExpression &regex) {
    m_filterRule = { property, regex };
    m_modelShell->dataChanged(m_modelShell->index(0), m_modelShell->index(m_modelShell->m_sizzer()));
}

template<class T>
KObservableModel *KObservableList<T>::detachModel(QObject *parent) const { m_modelShell->setParent(parent); return m_modelShell; }

template<class T>
bool KObservableList<T>::filt(QVariant value) {
    if(value.isNull())
        return false;

    QRegularExpressionMatch match = m_filterRule.second.match(value.toString());
    return match.capturedTexts().size() > 0;
}


#endif // OBSERVABLELIST_H
