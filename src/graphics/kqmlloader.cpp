#include "kqmlloader.h"

QQuickItem *KQmlLoader::parentItem() const {
    return m_parentItem;
}

void KQmlLoader::continueLoading(QQmlComponent *component, const QUrl &url) {
    if (component->isError()) {
        qWarning() << component->errors();
    } else {
        auto item = qobject_cast<QQuickItem*>(component->create(qmlContext(parentItem())));
        item->setParentItem(parentItem());
        emit loadingCompleated(item, url);
    }
}

void KQmlLoader::directLoad(const QByteArray &data, const QUrl &url) {
    assert(parentItem());
    assert(qmlEngine(parentItem()));
    QQmlComponent *component = new QQmlComponent(qmlEngine(parentItem()), this);
    component->setData(data, url);

    if (component->isLoading())
        QObject::connect(component, &QQmlComponent::statusChanged, this, [this, component, url](){ continueLoading(component, url); });
    else
        continueLoading(component, url);
}

void KQmlLoader::load(const QByteArray &data, const QUrl &url) {
    assert(parentItem());
    if(qmlEngine(parentItem()))
        directLoad(data, url);
    else
        QMetaObject::invokeMethod(this, [this, data, url](){ directLoad(data, url); }, Qt::QueuedConnection);
}

KQmlLoader::KQmlLoader(QQuickItem *parent) : QObject(parent) {
    m_parentItem = parent;
}
