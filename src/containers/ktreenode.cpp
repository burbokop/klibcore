#include "ktreenode.h"
#include <QMetaType>
#include <QUuid>
#include <QtDebug>


void KTreeNode::addChildNode(KTreeNode *node) {
    if(node) {
        node->setParent(this);
        node->setLevel(level() + 1);
        connect(node, &KTreeNode::destroyed, this, [this, node]() {
            m_childNodes.removeOne(node);
            childNodesChanged(childNodes());
        });
        m_childNodes.push_back(node);
        setNodeCount(m_childNodes.size());
        childNodesChanged(childNodes());
    }
}

void KTreeNode::assignData(QObject *data) {
    setData(data);
    if(data) {
        data->setParent(this);
    }
}

void KTreeNode::swap(KTreeNode *node1, KTreeNode *node2) {
    (void)node1;
    (void)node2;

    //node1->parentNode()->addChildNode()

//    if(node1 && node1 != this) {
//        auto thisData = this->data();
//        this->assignData(node1->data());
//        node1->assignData(thisData);
//    }
}

QList<KTreeNode *> KTreeNode::fullList() const {
    QList<KTreeNode *> result;
    result.push_back(const_cast<KTreeNode*>(this));
    for(auto c : m_childNodes) {
        if(c)
            result += c->fullList();
    }
    return result;
}

KTreeNode::KTreeNode(QObject *parent) : QObject(parent) { }

QVariant KTreeNode::toVariant(QString signature) const {
    QVariantMap result;

    if(data()) {
        QVariantMap dataObject;
        auto meta = data()->metaObject();
        QVariantMap dataProperties;
        for(auto i = 0; i < meta->propertyCount(); ++i) {
            auto prop = meta->property(i);
            dataProperties[prop.name()] = prop.read(data());
        }

        dataObject["class"] = QString::fromLatin1(meta->className());
        dataObject["properties"] = dataProperties;

        result["data"] = dataObject;
    }

    QVariantList children;
    for(auto c : m_childNodes) {
        children.push_back(c->toVariant());
    }
    result["childNodes"] = children;
    result["signature"] = signature;
    result["uuid"] = QUuid::createUuid().toString();
    return result;
}

bool KTreeNode::checkSignature(const QVariant &data, const QString &signature) {
    if(data.type() == QVariant::Map) {
        auto map = data.toMap();
        auto it = map.find("signature");
        if(it != map.end()) {
            return it.value() == signature;
        }
    }
    return false;
}

QString KTreeNode::readId(const QVariant &data) {
    if(data.type() == QVariant::Map) {
        auto map = data.toMap();
        auto it = map.find("uuid");
        if(it != map.end()) {
            return it.value().toString();
        }
    }
    return QString();
}

KTreeNode *KTreeNode::fromVariant(const QVariant &value) {
    if( value.type() != QVariant::Map)
        return nullptr;

    KTreeNode *result = new KTreeNode();
    auto map = value.toMap();

    QVariantMap dataObject = map["data"].toMap();

    auto typeName = dataObject["class"].toString().toLatin1();

    bool dataCreated = false;
    if(!typeName.isEmpty()) {
        const int type = QMetaType::type(typeName + "*");
        if(type != QMetaType::UnknownType) {
            const QMetaObject *mo = QMetaType::metaObjectForType(type);
            if(mo) {        
                auto instance = mo->newInstance();
                if(instance) {
                    instance->setParent(result);
                    result->setData(instance);
                    dataCreated = true;
                } else {
                    qWarning() << "KTreeNode can not create instance of" << typeName << ". Please mark constructor with Q_INVOKABLE";
                }
            }
        }
    }

    if(dataCreated) {
        auto propMap = dataObject["properties"].toMap();

        auto meta = result->data()->metaObject();
        for(auto i = 0; i < meta->propertyCount(); ++i) {
            auto prop = meta->property(i);
            prop.write(result->data(), propMap[prop.name()]);
        }
    }

    auto children = map["childNodes"].toList();

    for(auto c : children) {
        auto cn = KTreeNode::fromVariant(c);
        cn->setLevel(result->level() + 1);
        cn->setParent(result);
        connect(cn, &KTreeNode::destroyed, result, [result, cn]() {
            result->m_childNodes.removeOne(cn);
            result->childNodesChanged(result->childNodes());
        });
        result->m_childNodes.push_back(cn);
    }
    result->setNodeCount(result->m_childNodes.size());
    result->childNodesChanged(result->childNodes());

    return result;
}

void KTreeNode::removeNulls() {
    for(auto c : m_childNodes) {
        if(c) {
            c->removeNulls();
        } else {
            m_childNodes.removeOne(c);
            childNodesChanged(childNodes());
        }
    }
}

KTreeNode *KTreeNode::parentNode() const {
    return qobject_cast<KTreeNode*>(parent());
}

KTreeNode *KTreeNode::nextSibling() const {
    if(parent()) {
        if(auto parentNode = qobject_cast<KTreeNode*>(parent())) {
            if(parentNode->m_childNodes.size() > 0) {
                auto index = parentNode->m_childNodes.indexOf(const_cast<KTreeNode*>(this));
                if(index >= 0 && (index + 1) < parentNode->m_childNodes.size()) {
                    return parentNode->m_childNodes[index + 1];
                }
            }
        }
    }
    return nullptr;
}

KTreeNode *KTreeNode::next() const {
    if(m_childNodes.size() > 0) {
        return m_childNodes.first();
    } else {
        auto s = nextSibling();
        if(s) {
            return s;
        }
    }
    if(parentNode()) {
        if(parentNode()->parentNode()) {
            return parentNode()->nextSibling();
        }
    }
    return nullptr;
}

KTreeNode *KTreeNode::lastChildNode() {
    if(m_childNodes.size() > 0)
        return m_childNodes.last();

    return nullptr;
}

QVariant KTreeNode::readDataProperty(const char *propertyName) const {
    if(data())
        return data()->property(propertyName);
    return QVariant();
}

QVariant KTreeNode::readParentDataProperty(const char *propertyName) const {
    if(parentNode())
        return parentNode()->readDataProperty(propertyName);
    return QVariant();
}

KTreeNode *KTreeNode::lastNode() {
    KTreeNode *node = next();
    if(node == nullptr) {
        return this;
    } else {
        return node->lastNode();
    }
}
