#include "kcustomgridmodel.h"

KCustomGridModel::KCustomGridModel(QObject *parent) : QAbstractListModel(parent) {}


int KCustomGridModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return records.size();
}

QVariant KCustomGridModel::data(const QModelIndex &index, int role) const {
    if(index.row() >= records.size())
        return QVariant();
    switch (role) {
    case Row:
        return records[index.row()].row;
    case Column:
        return records[index.row()].column;
    case Data:
        return records[index.row()].data;
    }
    return QVariant();
}

QHash<int, QByteArray> KCustomGridModel::roleNames() const {
    return {
        { Row, "cellRow" },
        { Column, "cellColumn" },
        { Data, "cellData" }
    };
}

void KCustomGridModel::updateCell(int column, int row, const QVariant &data) {
    bool found = false;
    int i = 0;
    for(auto r : records) {
        if(r.row == row && r.column == column) {
            found = true;
            break;
        }
        ++i;
    }

    if(found) {
        if(records[i].data == data)
            return;
        records[i].data = data;
        matrix[column][row] = data;
        emit dataChanged(index(i), index(i));
    } else {
        setColumns(std::max(columns(), column + 1));
        setRows(std::max(rows(), row + 1));
        matrix[column][row] = data;
        beginInsertRows(QModelIndex(), records.size(), records.size());
        records.push_back({ column, row, data });
        endInsertRows();
    }
}

QVariant KCustomGridModel::cellData(int column, int row) const {
    return matrix[column][row];
}
