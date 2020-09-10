#ifndef KMODELPAINTEDTOOL_H
#define KMODELPAINTEDTOOL_H

#include <src/kmacro.h>

#include <QColor>
#include <QTextOption>
#include "kpaintedtool.h"

class QAbstractListModel;

/**
 * @brief The KModelPaintedTool class is inmplementation of KPaintedTool witch provide painting tables based on QAbstractListModel
 * @details
 * \n
 * AUTO MEMBERS:
 *
 * | modyfier | type                                       | name            | description                                                                    |
 * | -------- | ------------------------------------------ | --------------- | ------------------------------------------------------------------------------ |
 * | writable | QAbstractListModel*                        | model           | pointer to model witch will be painted                                         |
 * | writable | double                                     | horizontalRatio | horisontla offset coeficient of first column                                   |
 * | writable | bool                                       | paintHeader     | must be true if we want to draw role names as header                           |
 * | writable | QTextOption                                | textOption      | option of text in cells                                                        |
 * | writable | QList<QByteArray>                          | rolesSequence   | list of role names witch defines order in table                                |
 * | writable | std::function<bool(QByteArray,QByteArray)> | sortFunction    | function witch sort roles (std::sort style). if not null rolesSequence ignored |
 */
class KModelPaintedTool : public KPaintedTool {    
    class Options {
        K_READONLY_MEMBER(QTextOption, textOption, textOption, setTextOption, QTextOption());
        K_READONLY_MEMBER(int, penWidthScale, penWidthScale, setPenWidthScale, 1);
        K_READONLY_MEMBER(double, horizontalRatio, horizontalRatio, setHorizontalRatio, 1);
        K_READONLY_MEMBER(QList<int>, rolesSequence, rolesSequence, setRolesSequence, QList<int>());
    public:
        Options(const QTextOption &textOption,
                int penWidthScale = 1,
                double horizontalRatio = 1,
                QList<int> rolesSequence = QList<int>()) {
            setTextOption(textOption);
            setPenWidthScale(penWidthScale);
            setHorizontalRatio(horizontalRatio);
            setRolesSequence(rolesSequence);
        }
    };

    K_AUTO_MEMBER(QAbstractListModel*, model, model, setModel, nullptr);
    K_AUTO_MEMBER(double, horizontalRatio, horizontalRatio, setHorizontalRatio, 1);
    K_AUTO_MEMBER(bool, paintHeader, paintHeader, setPaintHeader, false);
    K_AUTO_MEMBER(QTextOption, textOption, textOption, setTextOption, QTextOption(Qt::AlignVCenter | Qt::AlignLeft));
    K_AUTO_MEMBER(QList<QByteArray>, rolesSequence, rolesSequence, setRolesSequence, QList<QByteArray>())
    K_AUTO_MEMBER(std::function<bool(QByteArray,QByteArray)>, sortFunction, sortFunction, setSortFunction, std::function<bool(QByteArray,QByteArray)>())
private:
    static int findRoleIndex(const QHash<int, QByteArray> &hash, const QByteArray &value);
    static void paintLine(QPainter *painter, QAbstractListModel *model, int row, int y, int rowWidth, int rowHeight, const Options &options, int xOffset, int yOffset, const QHash<int, QByteArray> &hash);
    static void paintCell(QPainter *painter, QAbstractListModel *model, int row, int role, int x, int y, int cellWidth, int cellHeight, const Options &options, const QHash<int, QByteArray> &hash);
public:
    /**
     * @brief KModelPaintedTool constructor
     * @param model - pointer to model witch you want to display
     */
    explicit KModelPaintedTool(QAbstractListModel *model = nullptr);
    virtual void paint(QPainter *painter) override;


};

#endif // KMODELPAINTEDTOOL_H
