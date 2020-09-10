#ifndef KPAINTEDTOOL_H
#define KPAINTEDTOOL_H

#include <src/kmacro.h>

#include <QRectF>
#include <QSizeF>
#include <QTextOption>

class QPainter;

/**
 * @brief The KPaintedTool class is the base class of paited tools which provides painting on QPainter for printing documents
 * @details Any painted tool has paint overriden function and rectandle in witch it will draw
 * \n\n
 * AUTO MEMBERS:\n
 * int width - paint rectangle width\n
 * int height - paint rectangle height\n
 * int xOffset - x offset relatively to parent painted tool\n
 * int yOffset - y offset relatively to parent painted tool\n
 */
class KPaintedTool {
    K_AUTO_MEMBER(int, width, width, setWidth, 0)
    K_AUTO_MEMBER(int, height, height, setHeight, 0)
    K_AUTO_MEMBER(int, xOffset, xOffset, setXOffset, 0)
    K_AUTO_MEMBER(int, yOffset, yOffset, setYOffset, 0)
public:
    KPaintedTool();
    virtual void paint(QPainter *painter) = 0;
    /**
     * @brief setSize - the same as manualy setting width and height
     * @param size
     */
    void setSize(const QSizeF &size);
    /**
     * @brief setPosition - the same as manualy setting xOffset and yOffset
     * @param point
     */
    void setPosition(const QPoint &point);
    /**
     * @brief setRect - the same as manualy setting all dimentions
     * @param rect
     */
    void setRect(const QRectF &rect);
    /**
     * @brief setRect - the same as manualy setting all dimentions
     * @param rect
     */
    void setRect(const QRect &rect);
    /**
     * @brief rect getter
     * @return
     */
    QRect rect() const;
    virtual ~KPaintedTool() {};

    /**
     * @brief applyMargins - transformations function witch trimm dimentionns of passed painted tool
     * @param paintedTool - in witch we want to apply margins
     * @param margin - number of points wa want to cop out
     */
    static void applyMargins(KPaintedTool *paintedTool, int margin);
};

/**
 * @brief The KTextPaintedTool class is inmplementation of KPaintedTool witch provide drawing text
 * \n\n
 * AUTO MEMBERS:\n
 * QString text - text that will be painted\n
 * QTextOption textOption - option thet will be applied to text\n
 */
class KTextPaintedTool : public KPaintedTool {
    K_AUTO_MEMBER(QString, text, text, setText, QString())
    K_AUTO_MEMBER(QTextOption, textOption, textOption, setTextOption, QTextOption())
public:
    KTextPaintedTool(QString text, QTextOption option = QTextOption());
    void paint(QPainter *painter) override;
};

#endif // KPAINTEDTOOL_H
