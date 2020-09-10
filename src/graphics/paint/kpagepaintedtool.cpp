#include "kpagepaintedtool.h"

#include <QAbstractListModel>
#include <QPainter>
#include "kmodelpaintedtool.h"


void KPagePaintedTool::calculatePreferedHeightSum() {
    m_preferedHeightSum = 0;
    for(auto it = childrenBegin(); it != childrenEnd(); ++it) {
        if((*it)->height() >= 0) {
            m_preferedHeightSum += (*it)->height();
        }
    }
}

KPagePaintedTool::KPagePaintedTool() {

}

int KPagePaintedTool::addRow(KPaintedTool *paintedTool) {
    paintedTool->setHeight(m_preferedHeight);
    addChild(paintedTool);
    calculatePreferedHeightSum();
    return m_preferedHeight;
}

int KPagePaintedTool::addRow(QAbstractListModel *model, const QTextOption &option, bool paintHeader, double hr, QList<QByteArray> rolesSequance) {
    if(m_preferedHeight < 0) {
        m_preferedHeight = model->rowCount() * 250;
    }

    auto p = new KModelPaintedTool(model);
    p->setTextOption(option);
    p->setPaintHeader(paintHeader);
    p->setHeight(m_preferedHeight);
    p->setHorizontalRatio(hr);
    p->setRolesSequence(rolesSequance);
    addChild(KPointerHandle<KPaintedTool>(p, KPointerHandle<KPaintedTool>::ManualDestroy));
    calculatePreferedHeightSum();
    return m_preferedHeight;
}

int KPagePaintedTool::addRow(QAbstractListModel *model, const QTextOption &option, bool paintHeader, double hr, std::function<bool (QByteArray, QByteArray)> sortFunction) {
    if(m_preferedHeight < 0) {
        m_preferedHeight = model->rowCount() * 250;
    }

    auto p = new KModelPaintedTool(model);
    p->setTextOption(option);
    p->setPaintHeader(paintHeader);
    p->setHeight(m_preferedHeight);
    p->setHorizontalRatio(hr);
    p->setSortFunction(sortFunction);
    addChild(KPointerHandle<KPaintedTool>(p, KPointerHandle<KPaintedTool>::ManualDestroy));
    calculatePreferedHeightSum();
    return m_preferedHeight;
}

int KPagePaintedTool::addRow(QString text, const QTextOption &option) {
    auto p = new KTextPaintedTool(text, option);
    p->setHeight(m_preferedHeight);
    addChild(KPointerHandle<KPaintedTool>(p, KPointerHandle<KPaintedTool>::ManualDestroy));
    calculatePreferedHeightSum();
    return m_preferedHeight;
}

void KPagePaintedTool::paint(QPainter *painter) {
    if(childrenCount() > 0 && painter->isActive() && height() > 0) {
        double mc = 1;
        auto defaultRowHeight = height() / childrenCount();
        if(m_preferedHeightSum > height()) {
            mc = height() / m_preferedHeightSum;
        }
        int y = 0;
        for(auto it = childrenBegin(); it != childrenEnd(); ++it) {
            auto rowData = (*it);
            int rowHeight;
            if(rowData->height() >= 0) {
                rowHeight = rowData->height() * mc;
            } else {
                rowHeight = defaultRowHeight * mc;
            }

            QRect rect;
            rect.setX(xOffset());
            rect.setY(yOffset() + y);
            rect.setWidth(width());
            rect.setHeight(rowHeight);

            rowData->setRect(rect);
            rowData->paint(painter);
            y += rowHeight;
        }

        if(pageNumber() > 0) {
            painter->drawText(
                        xOffset() + width() - pageNumberMargin(),
                        yOffset() + height() - pageNumberMargin(),
                        QString::number(pageNumber())
                        );
        }
    }
}


