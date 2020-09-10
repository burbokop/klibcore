#ifndef KCUSTOMTABLEMODEL_H
#define KCUSTOMTABLEMODEL_H

#include "kcustomgridmodel.h"

class KCustomTableModel : public KCustomGridModel {
    Q_OBJECT
    K_QML_TYPE(KCustomTableModel)

    K_AUTO_PROPERTY(int, expectedColumns, expectedColumns, setExpectedColumns, expectedColumnsChanged, 0)
    K_AUTO_PROPERTY(int, expectedRows, expectedRows, setExpectedRows, expectedRowsChanged, 0)

    QMap<int, QVariant> leftHeaders;
    QMap<int, QVariant> rightHeaders;
    QMap<int, QVariant> topHeaders;
    QMap<int, QVariant> bottomHeaders;
public:
    KCustomTableModel(QObject *parent = nullptr);
public slots:
    inline void setupLeftHeader(int row, const QVariant &data) { leftHeaders[row] = data; }
    inline void setupRightHeader(int row, const QVariant &data) { rightHeaders[row] = data; }
    inline void setupTopHeader(int column, const QVariant &data) { topHeaders[column] = data; }
    inline void setupBottomHeader(int column, const QVariant &data) { bottomHeaders[column] = data; }
    void updateTableCell(int column, int row, const QVariant &data);
    QVariant tableData(int column, int row) const;
signals:
    void tableCellChanged();
};

#endif // KCUSTOMTABLEMODEL_H
