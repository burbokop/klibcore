#include "kpaintedtool.h"

#include <QPainter>

KPaintedTool::KPaintedTool() {}

void KPaintedTool::setSize(const QSizeF &size) {
    m_width = size.width();
    m_height = size.height();
}

void KPaintedTool::setPosition(const QPoint &point) {
    m_xOffset = point.x();
    m_yOffset = point.y();
}

void KPaintedTool::setRect(const QRectF &rect) {
    setRect(rect.toRect());
}

void KPaintedTool::setRect(const QRect &rect) {
    m_xOffset = rect.x();
    m_yOffset = rect.y();
    m_width = rect.width();
    m_height = rect.height();
}

QRect KPaintedTool::rect() const {
    return QRect(m_xOffset, m_yOffset, m_width, m_height);
}

void KPaintedTool::applyMargins(KPaintedTool *paintedTool, int margin) {
    paintedTool->setWidth(paintedTool->width() - margin * 2);
    paintedTool->setHeight(paintedTool->height() - margin * 2);
    paintedTool->setXOffset(paintedTool->xOffset() + margin);
    paintedTool->setYOffset(paintedTool->yOffset() + margin);
}

KTextPaintedTool::KTextPaintedTool(QString text, QTextOption option) {
    setText(text);
    setTextOption(option);
}

void KTextPaintedTool::paint(QPainter *painter) {
    painter->drawText(rect(), text(), textOption());
}

