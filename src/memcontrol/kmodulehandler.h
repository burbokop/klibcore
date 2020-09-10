#ifndef KMODULEHANDLER_H
#define KMODULEHANDLER_H

#include "kabstractfactory.h"
#include "kpull.h"
#include <QMap>
#include <QObject>
#include <src/kmacro.h>

/**
 * @brief The KModuleHandler class provide object life controll system
 *
 * @details This class is only available with Qt. Can handle classes inherited by QObject.
 * KModuleHandler can be used:
 * 1. for strategy pattern
 * 2. as core of multistate application
 * 3. to switch modes
 *
 *
 * Mode changes by setting <b>mode</b> property.
 * Modes is registered by KModuleHandler::registerModule and KModuleHandler::registerModules
 */
class KModuleHandler : public QObject {
    Q_OBJECT
    K_OBJECT
    K_QML_TYPE(KModuleHandler)
public:
    /**
     * @brief The StoreMode enum defines how to store current module
     * @details
     *
     * Module registered with pull store mode will be stored to pull is if it is no longer needed and returned from pull if it is needed again (see KPull).
     * Module registered with reincarnation store mode will be deleted if it is no longer needed and created new object if it became necessary.
     */
    enum StoreMode {
        /**undefined store mode*/                 Undefined = 0,
        /**object will be stored in pull*/        Pull,
        /**object will be deleted and recreated*/ Reincarnation
    };
    K_AUTO_PROPERTY(QString, mode, mode, setMode, modeChanged, QString())
private:
    KAbstractFactory<QString, QObject> factory;
    KPull<QString, QObject> pull;

    struct ModuleRecord {
        QString className;
        StoreMode storeMode;
    };
    QMap<QString, QList<ModuleRecord>> modes;
    QList<QObject*> m_instances;
    K_READONLY_LIST_PROPERTY(QObject, instances, m_instances)
    K_READONLY_PROPERTY(QStringList, availableModes, availableModes, setAvailableModes, availableModesChanged, QStringList())
private:
    QMap<QObject*, StoreMode> storeModes;
protected:
    /**
     * @brief initObject function initialized object after creation or enabling
     * @param obj - pointer to object witch need to be initialized
     * @details This function can be overriden
     */
    virtual void initObject(QObject *obj);
    /**
     * @brief deinitObject function deinitialize object before deletation or disabling
     * @param obj - pointer to object witch need to be deinitialized
     * @details This function can be overriden
     */
    virtual void deinitObject(QObject *obj);
private slots:
    void applyMode(QString mode);
signals:
    /**
     * @brief objectInstantiated signal invokes after object is initialized
     * @param object - pointer to object
     * @details You can do some actions in qml with current object when it is initialized
     */
    void objectInstantiated(QObject* object);
public:
    explicit KModuleHandler(QObject *parent = nullptr);

    /**
     * @brief registerModule function registeres one module class
     * @param mode - mode to which module class is binded
     * @param storeMode - mode witch defines how this object is stored (see ModuleHandler::StoreMode enum)
     */
    template<typename T>
    void registerModule(QString mode, StoreMode storeMode = Reincarnation);
    /**
     * @brief registerModule function registeres one ore more module classes
     * @param mode - mode to which all module classes is binded
     * @param storeMode - mode witch defines how all objects will be stored (see ModuleHandler::StoreMode enum)
     */
    template<typename ...T>
    void registerModules(QString mode, StoreMode storeMode = Reincarnation);
    /**
     * @brief instancesOfType function gives list of specific type objects
     * @details Template parameter <b>T</b> defines what type we want to find.
     * if there is no objects with type <b>T</b>in current module handler, function returns empty list
     */
    template<typename T>
    QList<T*> instancesOfType() const;
    /**
     * @brief firstOfType function gives first found object of type <b>T</b> or <b>nullptr</b> if there is no objects with type <b>T</b>
     */
    template<typename T>
    T *firstOfType();

public slots:
    /**
     * @brief firstOfName function gives first found object with object name <b>name</b> or <b>nullptr</b> if there is no objects with this object name
     * @param name
     * @return found instance
     */
    QObject *firstOfName(QString name);
};

template<typename T>
void KModuleHandler::registerModule(QString mode, StoreMode storeMode) {
    modes[mode].push_back({ factory.registerType<T>(), storeMode });
    pull.registerType<T>();
    auto m = availableModes();
    if(!m.contains(mode)) {
        m.push_back(mode);
    }
    setAvailableModes(m);
}


template<typename ...T>
void KModuleHandler::registerModules(QString mode, StoreMode storeMode) {
    K_EXPAND(registerModule<T>(mode, storeMode))
}


template<typename T>
QList<T*> KModuleHandler::instancesOfType() const {
    QList<T*> result;
    for(auto i : m_instances) {
        if(i->metaObject()->className() == KType<T>())
            result.push_back(i);
    }
    return result;
}

template<typename T>
T *KModuleHandler::firstOfType() {
    for(auto i : m_instances) {
        if(i->metaObject()->className() == KType<T>())
            return i;
    }
    return nullptr;
}

#endif // KMODULEHANDLER_H
