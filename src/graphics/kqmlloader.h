#ifndef KQMLLOADER_H
#define KQMLLOADER_H

#include <QObject>
#include <QQuickItem>
#include <src/kmacro.h>

class KQmlLoader : public QObject {
    Q_OBJECT
    K_QML_TYPE(KQmlLoader)
    QQuickItem *m_parentItem = nullptr;
public:
    explicit KQmlLoader(QQuickItem *parent = nullptr);
    QQuickItem *parentItem() const;
private slots:
    void continueLoading(QQmlComponent *component, const QUrl &url);
public slots:
    void directLoad(const QByteArray &data, const QUrl &url = QUrl());
    void load(const QByteArray &data, const QUrl &url = QUrl());
signals:
    void loadingCompleated(QQuickItem *item, const QUrl &url);
};

#endif // KQMLLOADER_H
