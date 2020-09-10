#include "kstackpaintedtool.h"

KStackPaintedTool::KStackPaintedTool() {}

void KStackPaintedTool::paint(QPainter *painter) {
     for(auto it = childrenBegin(); it != childrenEnd(); ++it) {
         it->data()->setRect(rect());
         it->data()->paint(painter);
     }
}
