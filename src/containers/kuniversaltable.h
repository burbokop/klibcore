#ifndef KUNIVERSALTABLE_H
#define KUNIVERSALTABLE_H

#include <QAbstractListModel>
#include <src/kmacro.h>

/**
 * @brief The KUniversalTableModel class provides standart QAbstractListModel given from KUniversalTable
 * @details You can not create instanse of this class manualy, only get from KUniversalTable instance.
 * This model provides roles in format [role0, role1, ...] (count of roles is the same as parent KUniversalTable collumn count)
 */
class KUniversalTableModel : public QAbstractListModel {
    template<typename ...T>
    friend class KUniversalTable;
    Q_OBJECT
    K_QML_INTERFACE(KUniversalTableModel)
    std::function<int()> m_count;
    std::function<QVariant(int, int)> m_data;
    QHash<int, QByteArray> m_roleNames;
    KUniversalTableModel(QObject *parent = nullptr);
public:

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
};


/**
 * @brief The KUniversalTable class provides notifieble tuple oriented list witch can be visualized as table
 * Template pack defines types of values in one row
 */
template<typename ...T>
class KUniversalTable {
    KUniversalTableModel *m_model = nullptr;
    QList<std::tuple<T...>> m_data;

    template<size_t... Is, class Tuple, typename Func>
    static void for_each(std::index_sequence<Is...>, Tuple tup, Func f) {
        K_EXPAND(f(std::get<Is>(std::forward<Tuple>(tup)), Is));
    }

    template<size_t... Is, class Tuple, typename Func>
    static void for_each_s(std::index_sequence<Is...>, Tuple &tup, Func f) {
        K_EXPAND((void)(std::get<Is>(std::forward<Tuple&>(tup)) = f(std::get<Is>(std::forward<Tuple>(tup)), Is)));
    }


    typedef std::make_index_sequence<sizeof ...(T)> index_seq;
public:
    KUniversalTable() {
        m_model = new KUniversalTableModel();

        QHash<int, QByteArray> hash;
        for(size_t i = 0; i < sizeof...(T); ++i) {
            hash[Qt::UserRole + i] = "role" + QString::number(i).toUtf8();
        }
        m_model->m_roleNames = hash;
        m_model->m_count = [this]() { return m_data.size(); };
        m_model->m_data = [this](int row, int role) -> QVariant {
            QVariant result;
            const auto f = [&](auto a, int i){
                if(i == role - Qt::UserRole)
                    result = a;
            };

            for_each(index_seq(), m_data[row], f);
            return result;
        };
    }

    /**
     * @brief push_back - adds new row to the end and sends notification to model
     * @param args - values of row (types must match ones in KUniversalTable class instantiation)
     */
    void push_back(T... args) {
        m_model->beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
        m_data.push_back(std::make_tuple(args...));
        m_model->endInsertRows();
    }


    /**
     * @brief removeAt - removes one element by index
     * @param i - index
     */
    void removeAt(int i) {
        m_model->beginRemoveRows(QModelIndex(), i, i);
        m_data.removeAt(i);
        m_model->endRemoveRows();
    }

    /**
     * @brief erase - remove one element by iterator
     * @param it
     */
    template<typename Iterator>
    auto erase(Iterator it) {
        m_model->beginRemoveRows(QModelIndex(), it - m_data.begin(), it - m_data.begin());
        const auto rit = m_data.erase(it);
        m_model->endRemoveRows();
        return rit;
    }

    /**
     * @brief find - finds row in witch value of <b>C</b> column equals <b>value</b>
     * @return iterator if success or pointer to end if fail
     * @note This function returns non-const iterator (you can change its value but changes is not notifieble. to notify use KUniversalTable::update or KUniversalTable::updateOne)
     * @details
     * Example:
     * ```
     * auto it = table.find<2>("gogadoda");
     * //it points to row in witch table contains "gogadoda" in column with index 2
     * ```
     */
    template<size_t C, typename V>
    constexpr auto find(V value) {
        for(auto it = m_data.begin(); it != m_data.end(); ++it) {
            if(std::get<C>(*it) == value) {
                return it;
            }
        }
        return m_data.end();
    }

    /**
     * @brief contains function returns true if list contains value <b>value</b> in column <b>i</b>
     * @details
     * Example:
     * ```
     * bool ok = table.contains<2>("gogadoda");
     * //true if table contains "gogadoda" in column with index 2
     * ```
     */
    template<size_t i, typename V>
    bool contains(V value) {
        return find<i>(value) != end();
    }

    /**
     * @brief value - gives value by column <b>i</b> and row pointed in <b>it</b>
     */
    template<size_t i, typename Iterator>
    static auto value(Iterator it) { return std::get<i>(*it); }

    /**
     * @brief find - finds row in witch value of <b>C</b> column equals <b>value</b>
     * @return iterator if success or pointer to end if fail
     * @note This this function returns const iterator
     * @details
     * Example:
     * ```
     * auto it = table.find<2>("gogadoda");
     * //it points to row in witch table contains "gogadoda" in column with index 2
     * ```
     */
    template<size_t C, typename V>
    constexpr auto find(V value) const {
        for(auto it = m_data.begin(); it != m_data.end(); ++it) {
            if(std::get<C>(*it) == value) {
                return it;
            }
        }
        return m_data.end();
    }

    /**
     * @brief updateRow function changes one row and sends notification to model
     * @param it - iterator which point to row we need to change
     * @param ...args - pack of new values which will be applied to pointed row
     * @note You can change row value manualy if you has non-const iterator but in this case notification won't be sent.
     */
    template<typename Iterator>
    void updateRow(Iterator it, T ...args) {
        *it = std::make_tuple(args...);
        emit m_model->dataChanged(m_model->index(it - m_data.begin()), m_model->index(it - m_data.begin()));
    }

    /**
     * @brief updateOne function updates one cell at pointed row and column and sends notification to model
     * @param column - int template parameter witch points to column
     * @param it - iterator which point to row
     * @param value - new value that will be applied to cell
     * @note You can change row value manualy if you has non-const iterator but in this case notification won't be sent.
     * @note This overload of KUniversalTable::updateOne can get only constexpr column number
     */
    template<size_t column, typename Iterator, typename Value>
    void updateOne(Iterator it, const Value &value) {
        std::get<column>(*it) = value;
        emit m_model->dataChanged(m_model->index(it - m_data.begin()), m_model->index(it - m_data.begin()));
    }

    /**
     * @brief updateOne function updates one cell at pointed row and column and sends notification to model
     * @param it - iterator which point to row
     * @param column - integer witch points to column
     * @param value - new value that will be applied to cell
     * @note You can change row value manualy if you has non-const iterator but in this case notification won't be sent.
     * @note This overload of KUniversalTable::updateOne can get non-constexpr column number
     */
    template<typename Iterator, typename Value>
    void updateOne(Iterator it, size_t column, const Value &value) {
        for_each_s(index_seq(), *it, [column, &value](auto a, auto i) -> decltype (a) {
            typedef typename std::remove_reference<decltype (a)>::type a_type;
            if(i == column) {
                return QVariant(value).value<a_type>();
            } else {
                return a;
            }
        });
        emit m_model->dataChanged(m_model->index(it - m_data.begin()), m_model->index(it - m_data.begin()));
    }

    /**
     * @brief begin const iterator
     */
    auto begin() const { return m_data.begin(); }
    /**
     * @brief end const iterator
     */
    auto end() const { return m_data.end(); }
    /**
     * @brief begin non-const iterator
     */
    auto begin() { return m_data.begin(); }
    /**
     * @brief end non-const iterator
     */
    auto end() { return m_data.end(); }


    /**
     * @brief toVariant function serializes content of class to data that can be saved to file or transmmitted through internet
     * @return QVariant serialized data
     */
    QVariant toVariant() const {
        QVariantList result;
        for(auto l : m_data) {
            QVariantList record;
            for_each(index_seq(), l, [&record](auto a, auto) {
                record.push_back(a);
            });
            result.push_back(record);
        }
        return result;
    }

    /**
     * @brief fromVariant function deserializes data and creates new instance of KUniversalTable from it
     * @param variant - serialized data
     * @return new KUniversalTable instance
     */
    static KUniversalTable fromVariant(QVariant variant) {
        KUniversalTable result;
        const auto list = variant.toList();
        for(auto l : list) {
            auto record = l.toList();
            auto tuple = std::make_tuple(T()...);

            for_each_s(index_seq(), tuple, [&record](auto a, auto i) {
                typedef typename std::remove_reference<decltype (a)>::type a_type;
                if(static_cast<int>(i) < record.size()) {
                    return record[i].template value<a_type>();
                }
                return a_type();
            });

            result.m_data.push_back(tuple);
        }

        return result;
    }

    ~KUniversalTable() {
        if(m_model && m_model->parent() == nullptr) {
            delete m_model;
        }
    }

    /**
     * @brief detachModel function detaches model
     * @param parent
     * @return pointer to model
     * @details After calling this function instance of KUniversalTable will no longer control life of model so you need to do it by your own.
     */
    KUniversalTableModel *detachModel(QObject *parent = nullptr) const { m_model->setParent(parent); return m_model; }
};





#endif // UNIVERSALTABLEMODEL_H
