#include "kuniversaltable.h"

KUniversalTableModel::KUniversalTableModel(QObject *parent) : QAbstractListModel(parent) {

}

int KUniversalTableModel::rowCount(const QModelIndex &parent) const {
    (void)parent;
    return m_count();
}

QVariant KUniversalTableModel::data(const QModelIndex &index, int role) const {
    return m_data(index.row(), role);
}

QHash<int, QByteArray> KUniversalTableModel::roleNames() const {
    return m_roleNames;
}
