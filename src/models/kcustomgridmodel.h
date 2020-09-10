#ifndef KCUSTOMGRIDMODEL_H
#define KCUSTOMGRIDMODEL_H

#include <QAbstractListModel>
#include <src/kmacro.h>

class KCustomGridModel : public QAbstractListModel {
    Q_OBJECT
    K_QML_TYPE(KCustomGridModel)
    K_READONLY_PROPERTY(int, columns, columns, setColumns, columnsChanged, 0);
    K_READONLY_PROPERTY(int, rows, rows, setRows, rowsChanged, 0);
public:
    enum Roles {
        Column = 0,
        Row,
        Data
    };
private:
    Q_ENUM(Roles)
    struct Record {
        int column = 0;
        int row = 0;
        QVariant data;
    };
    QList<Record> records;
    QMap<int, QMap<int, QVariant>> matrix;
public:
    KCustomGridModel(QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
public slots:
    void updateCell(int column, int row, const QVariant &data);
    QVariant cellData(int column, int row) const;
};

#endif // KCUSTOMGRIDMODEL_H
