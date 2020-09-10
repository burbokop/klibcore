#include "kcustomtablemodel.h"

KCustomTableModel::KCustomTableModel(QObject *parent) : KCustomGridModel(parent) {}

void KCustomTableModel::updateTableCell(int column, int row, const QVariant &data) {
    if(leftHeaders.contains(row)) {
        updateCell(0, row + 1, leftHeaders[row]);
    }
    if(rightHeaders.contains(row)) {
        updateCell(expectedColumns() + 1, row + 1, rightHeaders[row]);
    }
    if(topHeaders.contains(column)) {
        updateCell(column + 1, 0, topHeaders[column]);
    }
    if(bottomHeaders.contains(column)) {
        updateCell(column + 1, expectedRows() + 1, bottomHeaders[column]);
    }

    updateCell(column + 1, row + 1, data);
    emit tableCellChanged();
}

QVariant KCustomTableModel::tableData(int column, int row) const {
    return cellData(column + 1, row + 1);
}
