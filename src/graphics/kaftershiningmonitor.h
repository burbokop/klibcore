#ifndef KAFTERSHININGMONITOR_H
#define KAFTERSHININGMONITOR_H

#include <QElapsedTimer>
#include <QImage>
#include <QQuickPaintedItem>

#include <src/kmacro.h>

/**
 * @brief The KAfterShiningMonitor class provides drawing quick painted items with aftersining effect
 * @details
 *
 * \n
 *
 * PROPERTIES:
 *
 * | modyfier | type                        | name                  | description                       |
 * | -------- | --------------------------- | --------------------- | --------------------------------- |
 * | writable | QQuickPaintedItem*          | contentPaintedItem    | item that will will be painted    |
 * | writable | double                      | afterShiningIntencity | intencity of after shining effect |
 * | writable | int                         | interval              | update interval in miliseconds    |
 *
 *
 * \n
 *
 *
 *
 *
 * Qml Example:
 * ```
 *  //example 0
 *  SomeItemInheritsQQuickPaintedItem {
 *     anchors.fill: parent
 *     //some property initialization
 *  }
 *
 *  //example 1
 *  KAfterShiningMonitor {
 *      anchors.fill: parent
 *
 *      contentPaintedItem: SomeItemInheritsQQuickPaintedItem {
 *          //some property initialization
 *      }
 *  }
 * ```
 * <b>example 1</b> will look like <b>example 0</b> but with applied aftersining effect
 *
 * @note if content item has property with name <b>autoUpdateEnabled</b> this property will set to false after adding this content item.
 * It is needed so that content item know if it is handled by KAfterShiningMonitor.
 * Recommended inherit KPaintedItem witch has this property
 */
class KAfterShiningMonitor : public QQuickPaintedItem {
    Q_OBJECT
    K_QML_TYPE(KAfterShiningMonitor)
    K_AUTO_PROPERTY(QQuickPaintedItem*, contentPaintedItem ,contentPaintedItem, setContentPaintedItem, contentPaintedItemChanged, nullptr)
    K_AUTO_PROPERTY(double, afterShiningIntencity, afterShiningIntencity, setAfterShiningIntencity, afterShiningIntencityChanged, 1)
    K_AUTO_PROPERTY(int, interval, interval, setInterval, intervalChanged, 50)

    QImage buffer = QImage(width(), height(), QImage::Format_ARGB32);    

    void updateAfterShining();
    void sizeChanged();
    double coeficient = 0;
public:
    KAfterShiningMonitor(QQuickItem *parent = nullptr);

signals:


    // QQuickPaintedItem interface
public:
    virtual void paint(QPainter *painter) override;
};

#endif // KAFTERSHININGMONITOR_H
