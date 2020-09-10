#include "kaftershiningmonitor.h"

#include <QPainter>
#include <QQmlProperty>
#include <QTimer>
#include <math.h>

void KAfterShiningMonitor::updateAfterShining() {
    if(coeficient < 0) coeficient = 0;
    int imageHeight = static_cast<int>(height());
    for (int i = imageHeight - 1; i >= 0; --i) {
        auto line = buffer.scanLine(i);
        for (int j = 3; j < buffer.bytesPerLine(); j += 4) {                        
            if (line[j] > 0.7 * 255) line[j] = static_cast<unsigned char>(line[j] * coeficient);
            else if (line[j] > 0.3 * 255) line[j] = static_cast<unsigned char>(line[j] * 0.8 / 0.9 * coeficient);
            else line[j] = static_cast<unsigned char>(line[j] * coeficient);
        }
    }
}

void KAfterShiningMonitor::sizeChanged() {
    buffer = QImage(width(), height(), QImage::Format_ARGB32);
}

KAfterShiningMonitor::KAfterShiningMonitor(QQuickItem *parent) : QQuickPaintedItem(parent) {
    QTimer *surfaceUpdateTimer = new QTimer(this);
    connect(this, &KAfterShiningMonitor::intervalChanged, this, [surfaceUpdateTimer](int value) {
        surfaceUpdateTimer->setInterval(value);
    });
    connect(this, &KAfterShiningMonitor::afterShiningIntencityChanged, this, [this](auto value){ coeficient = 1 - std::pow(M_E, -value); });
    connect(surfaceUpdateTimer, &QTimer::timeout, this, [this]() {
        updateAfterShining();
        if(contentPaintedItem()) {
            contentPaintedItem()->setWidth(width());
            contentPaintedItem()->setHeight(height());
            contentPaintedItem()->setX(x());
            contentPaintedItem()->setY(y());

            QPainter bufferPainter(&buffer);
            contentPaintedItem()->paint(&bufferPainter);
        }
        update();
    });
    surfaceUpdateTimer->start(interval());


    connect(this, &KAfterShiningMonitor::contentPaintedItemChanged, this, [this](QQuickPaintedItem *item) {
        if(item) {
            item->setParent(this);

            QQmlProperty prop(item, "autoUpdateEnabled");
            if(prop.isValid() && prop.isWritable()) {
                prop.write(false);
            }
        }
    });

    connect(this, &KAfterShiningMonitor::widthChanged, this, &KAfterShiningMonitor::sizeChanged);
    connect(this, &KAfterShiningMonitor::heightChanged, this, &KAfterShiningMonitor::sizeChanged);
}

void KAfterShiningMonitor::paint(QPainter *painter) {
    if(!buffer.isNull()) {
        painter->setRenderHints(QPainter::Antialiasing, true);
        painter->drawImage(0, 0, buffer);
    }
}
