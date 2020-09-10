#ifndef KMODULESWITCH_H
#define KMODULESWITCH_H

#include <src/kmacro.h>
#include <QStringList>


class KModuleSwitchInterface : public QObject {
    template<typename Base>
    friend class KModuleSwitch;
    Q_OBJECT
    K_QML_TYPE(KModuleSwitchInterface)
    K_AUTO_PROPERTY(QString, activeModuleName, activeModuleName, setActiveModuleName, activeModuleNameChanged, QString())
    K_READONLY_PROPERTY(QStringList, moduleNames, moduleNames, setModuleNames, moduleNamesChanged, QStringList())
    K_READONLY_PROPERTY(QObject*, activeModule, activeModule, setActiveModule, activeModuleChanged, nullptr)

    std::function<void(QString)> m_onActiveModuleChanged = [](auto){};
public:
    KModuleSwitchInterface(QObject *parent = nullptr);
};



template<typename Base>
class KModuleSwitch {
    KAbstractFactory<QString, Base> factory;
    QStringList m_moduleNames;
    QString m_activeModuleName;
    Base *m_activeModule = nullptr;

    friend KModuleSwitchInterface;
    KModuleSwitchInterface *m_interface = nullptr;
public:
    KModuleSwitch() {}

    bool activateModule(const QString &moduleName);
    bool deactivateModule();

    template<typename T>
    void registerModule(QString moduleName = QString()) {
        const auto n = moduleName.isEmpty() ? factory.template registerType<T>() : factory.template registerType<T>(moduleName);
        if(!m_moduleNames.contains(n)) {
            m_moduleNames.push_back(n);

            if(m_interface)
               m_interface->setModuleNames(m_moduleNames);
        }
    }
    QStringList moduleNames() const;
    QString activeModuleName() const;
    Base *activeModule() const;

    KModuleSwitchInterface *detachInterface(QObject *parent = nullptr);
};

template<typename Base>
bool KModuleSwitch<Base>::activateModule(const QString &moduleName) {
    if(moduleName == m_activeModuleName) {
        return false;
    }

    if(auto newObject = factory.create(moduleName)) {
        if(m_activeModule) {
            delete m_activeModule;
        }

        m_activeModule = newObject;
        m_activeModuleName = moduleName;
        if(m_interface) {
            m_interface->setActiveModule(m_activeModule);
            m_interface->setActiveModuleName(moduleName);
        }
        return true;
    }
    return false;
}

template<typename Base>
bool KModuleSwitch<Base>::deactivateModule() {
    if(m_activeModule) {
        delete m_activeModule;
        m_activeModule = nullptr;
        m_activeModuleName = QString();
        if(m_interface) {
            m_interface->setActiveModule(nullptr);
        }
        return true;
    }
    return false;
}

template<typename Base>
QStringList KModuleSwitch<Base>::moduleNames() const {
    return m_moduleNames;
}

template<typename Base>
QString KModuleSwitch<Base>::activeModuleName() const {
    return m_activeModuleName;
}

template<typename Base>
Base *KModuleSwitch<Base>::activeModule() const {
    return m_activeModule;
}

template<typename Base>
KModuleSwitchInterface *KModuleSwitch<Base>::detachInterface(QObject *parent) {
    if(!m_interface) {
        m_interface = new KModuleSwitchInterface(parent);
        m_interface->setModuleNames(m_moduleNames);
        m_interface->setActiveModuleName(activeModuleName());
        m_interface->setActiveModule(activeModule());
        m_interface->m_onActiveModuleChanged = [this](auto m) { activateModule(m); };
    }
    return m_interface;
}


#endif // KMODULESWITCH_H
