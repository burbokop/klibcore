#ifndef TREENODE_H
#define TREENODE_H

#include <QObject>
#include <src/kmacro.h>
#include <QPointF>

/**
 * @brief The KTreeNode class provides tree container and can be visualized in qml
 * @details This class can contains both data and list of children (KTreeNode instances).
 * Data is stored as pointer to QObject witch life is controled by tree node.
 * The KTreeNode class provides several standart operations under tree structure.
 * \n
 *
 * PROPERTIES:
 *
 * | modyfier | type                        | name       | description                                   |
 * | -------- | --------------------------- | ---------- | --------------------------------------------- |
 * | readonly | QObject*                    | data       | contained data                                |
 * | readonly | int                         | level      | depth of current node in tree (0 - root node) |
 * | readonly | int                         | nodeCount  | count of children                             |
 * | readonly | QQmlListProperty<KTreeNode> | childNodes | children (can be passed to <b>ListView</b>)   |
 */
class KTreeNode : public QObject {
    Q_OBJECT
    K_QML_TYPE(KTreeNode)
    K_READONLY_PROPERTY(QObject*, data, data, setData, dataChanged, nullptr)
    K_READONLY_PROPERTY(int, level, level, setLevel, levelChanged, 0)
    K_READONLY_PROPERTY(int, nodeCount, nodeCount, setNodeCount, nodeCountChanged, 0)
private:
    QList<KTreeNode*> m_childNodes;
    K_READONLY_LIST_PROPERTY(KTreeNode, childNodes, m_childNodes)
public:
    explicit KTreeNode(QObject *parent = nullptr);
    /**
     * @brief toVariant - serialization function
     * @param signature - magic string witch is used only as id or file (pachage) type
     * @return serialized data
     * @note for deserialization see KTreeNode::fromVariant
     */
    QVariant toVariant(QString signature = QString()) const;
    /**
     * @brief checkSignature - function verify if some serialized data has specifuc signature
     * @param data
     * @param signature
     * @return true if passed data has passed signature
     */
    static bool checkSignature(const QVariant &data, const QString &signature);
    /**
     * @brief readId - every serialized data has unique id witch can be read by this function
     * @param data
     * @return uuid string
     */
    static QString readId(const QVariant &data);
    /**
     * @brief fromVariant deserializes and constructs KTreeNode instance from data.
     * @param value - serialized data
     * @return pointer to new instance of KTreeNode
     * @note for serialization see KTreeNode::toVariant
     */
    static KTreeNode* fromVariant(const QVariant &value);
    /**
     * @brief removeNulls function removes all nullptr chuld nodes
     */
    void removeNulls();
    /**
     * @brief parentNode function gives pointer to parent tree node
     * @return
     */
    KTreeNode *parentNode() const;
    /**
     * @brief fullList - function straightens it tree to list and returns it
     * @return
     * @details
     *
     * Example:\n
     * ```
     *    source tree
     *
     *         |
     *    -----------
     *    |         |
     *   ____      ____
     *   |   |     |   |
     *   a   b     t   r
     *
     *    result list
     *
     *    a, b, t, r
     * ```
     */
    QList<KTreeNode*> fullList() const;

    /**
     * @brief gives pointer to data casted to <b>T</b>
     */
    template<typename T>
    T *dataAs() const { return qobject_cast<T*>(data()); };

    /**
     * @brief forEach - function iterates by all tree hierarchy in order as KTreeNode::fullList
     * @param callback - function witch will be called for each element
     */
    void forEach(std::function<void(KTreeNode *node)> callback) {
        auto list = fullList();
        for(auto n : list) {
            callback(n);
        }
    }

    /**
     * @brief forEachAsync - iterates by all tree hierarchy with undefined order
     * @param callback - function witch will be called for each element
     * @details This function should be used if you need to do long-term operation witch stop main thread.
     * Async variant of this function gives control to main thread in intervals between child nodes.
     */
    void forEachAsync(std::function<void(KTreeNode *node)> callback) {
        forEach([callback](auto n){ QMetaObject::invokeMethod(n, [n, callback](){ callback(n); }, Qt::QueuedConnection); });
    }

    /**
     * @brief nextSibling - gives pointer to next sibling tree node
     * @return
     */
    KTreeNode *nextSibling() const;
    /**
     * @brief next - gives pointer to next [sibling / child / lover level] tree node
     * @return
     */
    KTreeNode *next() const;
    /**
     * @brief lastNode - gives pointer to last node in tree hierarchy
     * @return
     */
    KTreeNode *lastNode();
    /**
     * @brief lastChildNode - gives last of children
     * @return
     */
    KTreeNode *lastChildNode();

    /**
     * @brief readDataProperty - gives value of data property with name <b>propertyName</b>
     * @param propertyName
     * @return
     */
    QVariant readDataProperty(const char *propertyName) const;
    /**
     * @brief readParentDataProperty - gives value of parent tree node data property with name <b>propertyName</b>
     * @param propertyName
     * @return
     */
    QVariant readParentDataProperty(const char *propertyName) const;
signals:

public slots:
    /**
     * @brief addChildNode - adds node to children and
     * @param node
     */
    void addChildNode(KTreeNode *node);
    /**
     * @brief assignData - assigns new data object
     * @param data
     */
    void assignData(QObject *data);
    /**
     * @brief swap - swaps data between nodes
     * @param node1
     * @param node2
     */
    static void swap(KTreeNode *node1, KTreeNode *node2);
};

#endif // TREENODE_H
