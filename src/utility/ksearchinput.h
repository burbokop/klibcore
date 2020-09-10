#ifndef KSEARCHINPUT_H
#define KSEARCHINPUT_H

#include <QQuickPaintedItem>
#include <src/kmacro.h>

class KSearchInput : public QQuickPaintedItem {
    Q_OBJECT
    K_QML_TYPE(KSearchInput)

    K_AUTO_PROPERTY(QString, text, text, setText, textChanged, QString())
    K_AUTO_PROPERTY(double, textSize, textSize, setTextSize, textSizeChanged, 8)
    K_AUTO_PROPERTY(QVariant, model, model, setModel, modelChanged, QVariant())
    K_AUTO_PROPERTY(QString, role, role, setRole, roleChanged, QString())

public:
    static QStringList parseModel(const QVariant &model, const QString &text, const QString &role);
    static QString sameBeginningSubstring(const QStringList &list);
    KSearchInput(QQuickItem *parent = nullptr);

signals:
    void accepted();

    // QQuickPaintedItem interface
public:
    virtual void paint(QPainter *painter) override;

    // QQuickItem interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
};

#endif // KSEARCHINPUT_H
