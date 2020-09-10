#ifndef KCLASSREGISTRY_H
#define KCLASSREGISTRY_H

#include <QStringList>
#include <src/klibinfo.h>
#include <src/memcontrol/kabstractfactory.h>

class QObject;
class KClassRegistry {
    inline static KAbstractFactory<QString, QObject> factory;
    inline static QStringList m_typeNames;
public:
    template<typename T>
    static QString registerType() {
        auto typeName = factory.registerType<T>();
        if(!m_typeNames.contains(typeName)) {
            m_typeNames.push_back(typeName);
        }
        return typeName;
    }
    friend QObject *kInstantinate(QString className);
    friend QStringList kAvailableClasses();
};

QObject *kInstantinate(QString className);
QStringList kAvailableClasses();



class __KMeta {
    inline static KAbstractFactory<std::string, void> factory;
    inline static std::vector<std::string> m_classNames;
public:
    static auto instantiate(std::string className) { return factory.create(className); }
    static auto classNames() { return m_classNames; }

    template<typename T>
    class __KRegisterer {
        static const inline int __i = []() {
            auto name = __KMeta::factory.registerType<T>();
            bool found = false;
            for(size_t i = 0; i < __KMeta::m_classNames.size(); ++i) {
                if(__KMeta::m_classNames[i] == name) {
                    found = true;
                    break;
                }
            }
            if(!found) {
                __KMeta::m_classNames.push_back(name);
            }
            return 0;
        }();
    public:
        constexpr __KRegisterer() { (void)__i; }
    };
};


#define K_OBJECT \
    auto __meta_registerer() { \
        static constexpr __KMeta::__KRegisterer<std::remove_pointer<decltype (this)>::type> result; \
        return result; \
    }



#endif // KCLASSREGISTRY_H
