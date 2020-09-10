#ifndef KPACKAGE_H
#define KPACKAGE_H

#include <QDataStream>
#include <QDateTime>
#include <QString>
#include <QVariant>


class KPackage {
    QString m_type;
    QDateTime m_creationTime;
    QVariant m_data;
    bool m_isValid = false;
public:
    KPackage();
    KPackage(const QString &type, const QVariant &data);
    QString type() const;
    void setType(const QString &type);
    QDateTime creationTime() const;
    QVariant data() const;
    void setData(const QVariant &data);

    
    QByteArray toJson();
    static KPackage fromJson(QByteArray json);
    QByteArray toBinary();
    static KPackage fromBinary(QByteArray data);

    template<typename T>
    static T fromBinary(QByteArray data) {
        T result;
        QDataStream stream(&data, QIODevice::ReadOnly);
        stream.setVersion(QDataStream::Qt_5_0);
        stream >> result;
        return result;
    }

    template<typename T>
    static QByteArray toBinary(const T &data) {
        QByteArray result;
        QDataStream stream(&result, QIODevice::WriteOnly);
        stream.setVersion(QDataStream::Qt_5_0);
        stream << data;
        return result;
    } 

    static KPackage loadJson(const QString &file, std::function<QByteArray(const QByteArray&)> decoder = [](auto d){ return d; });
    static KPackage loadBynary(const QString &file, std::function<QByteArray(const QByteArray&)> decoder = [](auto d){ return d; });

    template<typename T, typename C, typename ...Args>
    static KPackage loadJson(const QString &file, C *obj, T(C::*f)(Args...)) {
        return loadJson(file, [obj, f](auto d) { return (obj->*f)(d); });
    }
    template<typename T, typename C, typename ...Args>
    static KPackage loadBynary(const QString &file, C *obj, T(C::*f)(Args...)) {
        return loadBynary(file, [obj, f](auto d) { return (obj->*f)(d); });
    }

    bool storeJson(const QString &file, std::function<QByteArray(const QByteArray&)> encoder = [](auto d){ return d; });
    bool storeBynary(const QString &file, std::function<QByteArray(const QByteArray&)> encoder = [](auto d){ return d; });

    template<typename T, typename C, typename ...Args>
    bool storeJson(const QString &file, C *obj, T(C::*f)(Args...)) {
        return storeJson(file, [obj, f](auto d) { return (obj->*f)(d); });
    }
    template<typename T, typename C, typename ...Args>
    bool storeBynary(const QString &file, C *obj, T(C::*f)(Args...)) {
        return storeBynary(file, [obj, f](auto d) { return (obj->*f)(d); });
    }

    bool isValid() const;
};




#endif // KPACKAGE_H
