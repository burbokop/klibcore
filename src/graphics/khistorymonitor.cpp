#include "khistorymonitor.h"

#include <QPainter>
#include <QTimer>

#include <src/math/kmath.h>

void KHistoryMonitor::drawChart(QPainter *painter, KHistoryMonitor::Record r, quint64 channel) {
    if(r.history) {
        painter->setPen(r.pen);

        auto list = r.history->historyUnit(timeWidth());
        auto startTime = r.history->currentTime() - timeWidth();

        QPoint last;
        bool hasLast = false;
        QVector<Record>::size_type distortionChannel = 0;
        for(auto l : list) {
            const auto m = l.toMap();
            const auto relativeTime = m["time"].toDouble() - startTime;
            auto value = m["value"].toDouble();

            if(r.style == UninterruptedWithIntegrator) {
                value = integrator.process(value, channel);
            } else if(r.style == Distortion) {
                value = integrator.process(value, distortionChannel);
            }

            const auto x = KMath::instance()->dmap(relativeTime, 0, timeWidth(), 0, width());
            const auto y = KMath::instance()->dmap(value, min(), max(), height(), 0);

            if(hasLast) {
                if(r.style == Discrete) {
                    painter->drawLine(last, QPoint(x, last.y()));
                    painter->drawLine(QPoint(x, last.y()), QPoint(x, y));
                } else {
                    painter->drawLine(last, QPoint(x, y));
                }
            }

            last = QPoint(x, y);
            hasLast = true;
            ++distortionChannel;
        }

        if(r.style != Distortion)
            integrator.resetSelf();

        painter->drawLine(last, QPoint(width(), last.y()));
    }
}

KHistoryMonitor::KHistoryMonitor(QQuickItem *parent) : KPaintedItem(parent) {
    QTimer *ut = new QTimer(this);
    connect(ut, &QTimer::timeout, this, [this](){ update(); });
    connect(this, &KHistoryMonitor::autoUpdateEnabledChanged, this, [ut, this](bool state) {
        if(state) {
            ut->start(updateInterval());
        } else {
            ut->stop();
        }
    });
    connect(this, &KHistoryMonitor::updateIntervalChanged, this, [ut](auto value) { ut->setInterval(value); });

    if(autoUpdateEnabled()) {
        ut->start(updateInterval());
    } else {
        ut->stop();
    }
}

void KHistoryMonitor::paint(QPainter *painter) {
    if(painter->isActive()) {
        auto ids = KMath::instance()->customContainerIndices(records);
        auto center = width() * 0.5;
        auto rstart = -records.size() / 2;

        int i = 0;
        for(auto r : records) {
            auto c = rstart + i;
            painter->setPen(r.pen);
            painter->drawText(QPoint(center + c * 40, 12), r.title);

            drawChart(painter, r, ids[i]);
            ++i;
        }
    }
}

void KHistoryMonitor::addHistory(KAbstractValueHistory *history, QPen pen, QString title, GraphStyle style) {
    records.push_back({ history, pen, title, style });
}

bool KHistoryMonitor::removeHistory(KAbstractValueHistory *history) {
    return records.removeOne({ history, QColor(), QString(), Discrete });
}
