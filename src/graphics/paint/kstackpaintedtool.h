#ifndef KSTACKPAINTEDTOOL_H
#define KSTACKPAINTEDTOOL_H

#include "karraypaintedtool.h"

/**
 * @brief The KStackPaintedTool class is inmplementation of KPaintedTool witch provide painting a lot of painted tool on each other
 * @details All painted tools will be painted in order they were added.
 */
class KStackPaintedTool : public KArrayPaintedTool {
public:
    KStackPaintedTool();

    // KPaintedTool interface
public:
    virtual void paint(QPainter *painter) override;
};

#endif // KSTACKPAINTEDTOOL_H
