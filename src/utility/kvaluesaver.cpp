#include "kvaluesaver.h"

#include <QCoreApplication>
#include <QFile>
#include <src/kadditional.h>
#include <src/network/kpackage.h>


KValueSaver::KValueSaver(QObject *parent) : QObject(parent) {
    connect(QCoreApplication::instance(), &QCoreApplication::aboutToQuit, this, [this](){
        QFile output(m_path);
        output.open(QIODevice::WriteOnly);
        QVariantList list;
        output.write(KPackage("", value()).toBinary());
    });
}

bool KValueSaver::bindToFile(QString path, bool convertToAbsolutePath) {
    if(convertToAbsolutePath) {
        path = KAdditional::absolutePath(path);
    }

    m_path = path;
    QFile input(path);
    if(input.open(QIODevice::ReadOnly)) {
        auto p = KPackage::fromBinary(input.readAll());
        setValue(p.data());
        return true;
    }
    return false;
}
