#ifndef KFlexibleModel_H
#define KFlexibleModel_H

#include <QObject>
#include <QAbstractListModel>
#include <src/kmacro.h>

class KFlexibleModel : public QAbstractListModel
{
    Q_OBJECT
    K_QML_TYPE(KFlexibleModel)
    K_READONLY_PROPERTY(int, size, size, setSize, sizeChanged, 0)
public:
    KFlexibleModel(QObject *parent = nullptr);
    KFlexibleModel(QStringList roles, QObject *parent = nullptr);
    KFlexibleModel &operator =(KFlexibleModel &model);
    bool operator ==(KFlexibleModel &model);
    bool operator !=(KFlexibleModel &model);

public slots:
    bool isEmpty();
    void addRole(QString);
    void addRoles(QStringList);
    QStringList sortedRoleNames();
    int roleIndex(QString role) const;

    QVariant value(int row, QString role) const;
    QVariantMap row(int row) const;
    void updateCell(int row, const QString &role, const QVariant &value);

    bool sortByRole(const QString &role, std::function<bool(QVariant, QVariant)> comparator);

    QVector<QMap<int, QVariant>> allData() const;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    //push & pop
    void push_back(QVariantList varList);
    void push_back(QVariantMap varMap);
    void push_front(QVariantList varList);
    void push_front(QVariantMap varMap);

    bool setLineData(QVariantList varList, int row = 0);
    bool setLineData(QVariantMap varMap, int row = 0);

    void insert(int pos, QVariantList varList);
    void insert(int pos, QVariantMap varMap);
    bool remove(int pos);
    bool removeAll();
    void clear();

    //return QVariantList<QVariantMap<QString, QVariant>>>
    QVariant serialize();
    bool deserialize(QVariant variant, bool clear = true, bool append = false);


    bool contains(QVariantMap varMap);
    //returns row (int) if found or -1
    int indexOf(QVariantMap varMap);
    int indexOf(QVariant value, QString role = "");
    /*  returns list of rows or -1
        if combine true -> function AND
        if combine false -> function OR */
    QVariantList indicesOf(QVariantMap varMap, bool combine = true);
    //do the same thing, but without strict binding to roles
    QVariantList indicesOf(QVariantList varList, bool combine = true);
    //do the same, but with strict binding to one role
    QVariantList indicesOf(QVariantList varList, QString role);

private:
    QHash<int, QByteArray> m_roles;
    QStringList m_names;
    QVector<QMap<int, QVariant>> m_data;

    void generateData();
    QMap<int, QVariant> generateMap(QVariantList varList);
    QMap<int, QVariant> generateMap(QVariantMap varMap);

};

#endif // KFlexibleModel_H
