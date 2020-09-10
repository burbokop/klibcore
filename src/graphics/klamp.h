#ifndef KLAMP_H
#define KLAMP_H

#include <QQuickItem>
#include <src/kmacro.h>
#include "kaftershiningmonitor.h"
#include "kqmlloader.h"

/**
 * @brief The KLamp class
 */
class KLamp : public QQuickItem {
    Q_OBJECT
    K_QML_TYPE(KLamp)

    K_AUTO_PROPERTY(QString, text, text, setText, textChanged, QString())
    K_AUTO_PROPERTY(QColor, ledColor, ledColor, setLedColor, ledColorChanged, "#ffff00")
    K_AUTO_PROPERTY(QColor, backgroundColor, backgroundColor, setBackgroundColor, backgroundColorChanged, "#666666")
    K_AUTO_PROPERTY(QColor, textColor, textColor, setTextColor, textColorChanged, "#000000")
    K_AUTO_PROPERTY(bool, state, state, setState, stateChanged, false)
    K_READONLY_PROPERTY(KAfterShiningMonitor*, afterShining, afterShining, setAfterShining, afterShiningChanged, new KAfterShiningMonitor(this));

    KQmlLoader *qmlLoader = new KQmlLoader(this);
public:
    KLamp(QQuickItem *parent = nullptr);

signals:

};

#endif // KLAMP_H
