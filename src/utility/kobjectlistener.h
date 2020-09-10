#ifndef KOBJECTLISTENER_H
#define KOBJECTLISTENER_H

#include <QMap>
#include <QObject>
#include <QVariant>
#include <QUrl>
#include <QMetaProperty>


/**
 * @brief The KObjectListener class provides observer pattern for all properties for observable object
 * @details One instance of KObjectListener can listen many objects at the same time.
 * When some property of some object changes, listener emits signal KObjectListener::propertyEvent,
 * says what property of what object changed and gives new value of property
 */
class KObjectListener : public QObject {
    Q_OBJECT
    QMap<void*, QMap<int, int>> properties;
private slots:
    void onPropertyNotify();
    bool linkProperty(QObject *obj, const QMetaProperty &prop, QString slot);
public:
    explicit KObjectListener(QObject *parent = nullptr);

signals:
    /**
     * @brief propertyEvent
     * @param objectName - name of object stored in property <b>objectName</b> of observable object
     * @param property - name of property witch is changed
     * @param value - new value of property
     */
    void propertyEvent(QString objectName, QString property, QVariant value);

public slots:
    /**
     * @brief listen function binds to all properties of passed object
     * @param object - pointer to object we need to listen
     * @return true if binding syccesfuly
     */
    bool listen(QObject *object);
};


#endif // KOBJECTLISTENER_H
