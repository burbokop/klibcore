#ifndef KPAGEPAINTEDTOOL_H
#define KPAGEPAINTEDTOOL_H

#include "karraypaintedtool.h"

/**
 * @brief The KPagePaintedTool class is inmplementation of KPaintedTool witch provide painting other KPaintedTool instances as list.
 * @note If sum height of all rows is bigger then height of page expected undefined behaviour
 * @details
 *\n
 * AUTO MEMBERS:
 *
 * | modyfier | type | name             | description                           |
 * | -------- | ---- | ---------------- | ------------------------------------- |
 * | writable | int  | pageNumber       | number of page that will be displayed |
 * | writable | int  | pageNumberMargin | margin of displayed number of page    |
 *
 */
class KPagePaintedTool : public KArrayPaintedTool {
    enum ContentType { Undefined, Rows, Columns } contentType = Undefined;
    int m_preferedHeight = -1;
    void calculatePreferedHeightSum();
    int m_preferedHeightSum = 0;
    K_AUTO_MEMBER(int, pageNumber, pageNumber, setPageNumber, 0)
    K_AUTO_MEMBER(int, pageNumberMargin, pageNumberMargin, setPageNumberMargin, 32)
public:
    KPagePaintedTool();


    /**
     * @brief addRow function adds any row to page
     * @param paintedTool
     * @return height of added row
     * @details height of row will be calculated automaticaly
     */
    int addRow(KPaintedTool *paintedTool);
    /**
     * @brief addRow function adds model row to page
     * @param model - pointer to model
     * @param option - text option (see KModelPaintedTool::textOption auto member)
     * @param paintHeader - see KModelPaintedTool::paintHeader auto member
     * @param hr - horisontal ratio (see KModelPaintedTool::horizontalRatio auto member)
     * @param rolesSequance - order of roles (see KModelPaintedTool::rolesSequance auto member)
     * @return height of added row
     * @details this overload of addRow adds model and applies options. This model will be converted to KModelPaintedTool and added to page.
     * @note This overload provides installing rolesSequance
     */
    int addRow(QAbstractListModel *model, const QTextOption &option = QTextOption(), bool paintHeader = false, double hr = 1, QList<QByteArray> rolesSequance = QList<QByteArray>());
    /**
     * @brief addRow function adds model row to page
     * @param model - pointer to model
     * @param option - text option (see KModelPaintedTool::textOption auto member)
     * @param paintHeader - see KModelPaintedTool::paintHeader auto member
     * @param hr - horisontal ratio (see KModelPaintedTool::horizontalRatio auto member)
     * @param sortFunction - see KModelPaintedTool::sortFunction auto member
     * @return height of added row
     * @details this overload of addRow adds model and applies options. This model will be converted to KModelPaintedTool and added to page.
     * @note This overload provides installing sortFunction
     */
    int addRow(QAbstractListModel *model, const QTextOption &option, bool paintHeader, double hr, std::function<bool(QByteArray,QByteArray)> sortFunction);
    /**
     * @brief addRow function adds text row
     * @param text - text we want to paint
     * @param option - text option wa want to apply to this text
     * @return height of added row
     */
    int addRow(QString text, const QTextOption &option = QTextOption());

    /**
     * @details You can add any type of row with template integer parameter in order to define explicit height of row.
     * if content does not fit it will be scaled down
     */
    template<int preferedHeight, typename ...Args>
    int addRow(Args ...args) { m_preferedHeight = preferedHeight; auto r = addRow(args...); m_preferedHeight = -1; return r; }

    // KPaintedTool interface
public:
    void paint(QPainter *painter) override;
};

#endif // KPAGEPAINTEDTOOL_H
