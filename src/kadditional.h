#ifndef KADDITIONAL_H
#define KADDITIONAL_H

#include <src/kmacro.h>
#include <QString>

/**
 * @brief The KAdditional class provides pure functions for many different actions.
 * @details This class is only static and available only from c++. Other class KAdditionalPrivate can be used from qml.
 */

class KAdditional {
public:
#ifdef __WIN32__
    static constexpr char separator = '\\';
    static inline const QString separatorString = "\\";
#else
    static constexpr char separator = '/';
    static inline const QString separatorString = "/";
#endif


    /**
     * @brief constrainPath convert path to normalized format
     * @param path - input path
     * @return normalized path
     *
     * Example:\n
     * ```
     * auto cp = KAdditional::constrainPath("/home/user/Documents/../Desktop/././");
     * //cp contains "/home/user/Desktop/"
     * ```
     */
    static QString constrainPath(const QString &path);

    /**
     * @brief absolutePath convert path to one relatively to exe file of program
     * @param path - input path
     * @return exe relative path
     *
     * Example:\n
     * ```
     * auto resultPath = KAdditional::absolutePath("./resources/icon.png"); //exe contained in "/home/user/your-app"
     * //resultPath contains "/home/user/your-app/resources/icon.png"
     * ```
     */
    static QString absolutePath(const QString &path);

    /**
     * @brief urlEndsWith
     * @param url
     * @param string
     * @return true if <b>url</b> ends with <b>string</b>, except false
     *
     * The same as QString::endsWith but works with urls.
     */
    static bool urlEndsWith(const QUrl &url, const QString string);

    /**
     * @brief mkdirIfNotExist creates file is it not exist and nothing more.
     * @param path - path to folder which need creation
     */
    static void mkdirIfNotExist(const QString &path);

    /**
     * @brief urlPath function converts url to path string
     * @param url
     * @return string with path of url <b>url</b>
     */
    static QString urlPath(const QUrl &url);

    /**
     * @brief numberToFixedSizeString function converts any number to fixed size string
     * @param number - input number
     * @param base - base into which you want to convert.
     *
     *
     *
     * Example:\n
     * ```
     * uint8_t a = 110;
     * qDebug() << numberToFixedSizeString(a);
     * //output - "110", size 3
     *
     * uint16_t b = 110;
     * qDebug() << numberToFixedSizeString(b);
     * //output - "110  ", size 5
     * ```
     *
     * This function needed if you want to display table of numbers. For example:
     *
     * ```
     * 1233    3345
     * 121     33
     * 3       23565677
     * 12455   34
     * ```
     *
     */
    template<typename T>
    static QString numberToFixedSizeString(T number, int base = 10) {
        int size;
        switch (sizeof (number)) {
        case 1: size = 3; break;
        case 2: size = 5; break;
        case 4: size = 10; break;
        default: size = 16; break;
        }
        auto numString = QString::number(number, base);
        return numString + QString(' ').repeated(size - numString.size());
    }

    /**
     * @details the same as KAdditional::numberToFixedSizeString but returns std::string
     */
    template<typename T>
    static std::string numberToFixedSizeStdString(T number) {
        return numberToFixedSizeString(number).toStdString();
    }

    /**
     * @brief fillQObjectList<T> creates <b>count</b> objects of type <b>T</b> as QList.
     * @param parent - pointer to QObject that will be parent of all new objects.
     * @param count
     * @return created objects with type QList<T*>
     *
     * This function need if you want to initialize member with list of types inherited from QObject.
     */
    template<typename T>
    static QList<T*> fillQObjectList(QObject *parent, int count);

    /**
     * @brief mapToSortedList function converts map with key type <b>KeyT</b> and value type <b>ValueT</b> to list of pairs and soit it.
     * @param map - input map we want to convert
     * @param f - sorting function (format as one passed to std::sort) decltype(f) = bool(QPair<KeyT, ValueT>, QPair<KeyT, ValueT>)
     */
    template<typename KeyT, typename ValueT, typename Func>
    static QList<QPair<KeyT, ValueT>> mapToSortedList(const QMap<KeyT, ValueT> &map, Func f) {
        QList<QPair<KeyT, ValueT>> result;
        for(auto it = map.begin(); it != map.end(); ++it) {
            result.push_back(QPair(it.key(), it.value()));
        }
        std::sort(result.begin(), result.end(), f);
        return result;
    }

    /**
     * @brief overloads mapToSortedList but works with QHash
     */
    template<typename KeyT, typename ValueT, typename Func>
    static QList<QPair<KeyT, ValueT>> mapToSortedList(const QHash<KeyT, ValueT> &map, Func f) {
        QList<QPair<KeyT, ValueT>> result;
        for(auto it = map.begin(); it != map.end(); ++it) {
            result.push_back(QPair(it.key(), it.value()));
        }
        std::sort(result.begin(), result.end(), f);
        return result;
    }

    /**
     * @brief extractInt function extracts integet from string <b>str</b>
     * @param str
     * @param ok - pointer to bool which contains successfulness flag after calling function
     * @return intterger extracted from string
     */
    static int extractInt(const QString &str, bool *ok = nullptr);
};


template<typename T>
QList<T*> KAdditional::fillQObjectList(QObject *parent, int count) {
    QList<T*> result;
    for(int i = 0; i < count; ++i) {
        result.push_back(new T(parent));
    }
    return result;
}

class KAdditionalPrivate : public QObject {
    Q_OBJECT
    K_PRIVATE_SINGLETON(KAdditionalPrivate)
    K_QML_SINGLETON_ALIAS(KAdditionalPrivate, KAdditional)
    KAdditionalPrivate() {}
public slots:
    inline QString absolutePath(const QString &path) { return KAdditional::absolutePath(path); }
    inline QString constrainPath(const QString &path) { return KAdditional::constrainPath(path); }
    inline bool urlEndsWith(const QUrl &url, const QString string) { return KAdditional::urlEndsWith(url, string); };
    inline void mkdirIfNotExist(const QString &path) const { KAdditional::mkdirIfNotExist(path); }
    inline QString urlPath(const QUrl &url) const { return  KAdditional::urlPath(url); }
};


#endif // KADDITIONAL_H
