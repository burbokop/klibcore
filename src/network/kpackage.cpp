#include "kpackage.h"
#include <QFile>
#include <QJsonDocument>


QString KPackage::type() const {
    return m_type;
}

QDateTime KPackage::creationTime() const {
    return m_creationTime;
}

void KPackage::setType(const QString &type) {
    m_type = type;
    m_isValid = true;
}

QVariant KPackage::data() const {
    return m_data;
}

void KPackage::setData(const QVariant &data) {
    m_data = data;
}

QByteArray KPackage::toJson() {
    QVariantMap result;
    result["type"] = type();
    result["data"] = data();
    result["creationTime"] = creationTime();
    return QJsonDocument::fromVariant(result).toJson();    
}

KPackage KPackage::fromJson(QByteArray json) {
    QVariantMap map = QJsonDocument::fromJson(json).toVariant().toMap();
    QVariant type = map["type"];
    KPackage result;
    result.m_isValid = type.isValid();
    if(!result.isValid()) return result;
    result.m_creationTime = map["creationTime"].toDateTime();
    result.setData(map["data"]);
    result.setType(type.toString());
    return result;
}

QByteArray KPackage::toBinary() {
    QByteArray result;
    QDataStream stream(&result, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_5_0);
    stream << type() << data() << creationTime();
    return result;
}

KPackage KPackage::fromBinary(QByteArray data) {
    KPackage result;
    QDataStream stream(&data, QIODevice::ReadOnly);
    stream.setVersion(QDataStream::Qt_5_0);
    stream >> result.m_type >> result.m_data >> result.m_creationTime;
    return result;
}

KPackage KPackage::loadJson(const QString &file, std::function<QByteArray(const QByteArray &)> decoder) {
    QFile f(file);
    if(f.open(QIODevice::ReadOnly)) {
        return fromJson(decoder(f.readAll()));
    }
    return KPackage();
}

KPackage KPackage::loadBynary(const QString &file, std::function<QByteArray(const QByteArray &)> decoder) {
    QFile f(file);
    if(f.open(QIODevice::ReadOnly)) {
        return fromBinary(decoder(f.readAll()));
    }
    return KPackage();
}

bool KPackage::storeJson(const QString &file, std::function<QByteArray(const QByteArray &)> encoder) {
    QFile f(file);
    if(f.open(QIODevice::WriteOnly)) {        
        f.write(encoder(toJson()));
        return true;
    }
    return false;
}

bool KPackage::storeBynary(const QString &file, std::function<QByteArray(const QByteArray &)> encoder) {
    QFile f(file);
    if(f.open(QIODevice::WriteOnly)) {
        f.write(encoder(toBinary()));
        return true;
    }
    return false;
}

bool KPackage::isValid() const {
    return m_isValid;
}

KPackage::KPackage() {
    m_creationTime = QDateTime::currentDateTime();
}

KPackage::KPackage(const QString &type, const QVariant &data) : KPackage() {
    setType(type);
    setData(data);
}
