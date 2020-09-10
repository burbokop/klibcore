#include "kadditional.h"

#include <QCoreApplication>
#include <QDir>
#include <QRegularExpression>
#include <QStack>

QString KAdditional::constrainPath(const QString &path) {
    if(path.size() <= 0)
        return "";

    auto results = path.split(separator);

    QStack<QString> stack;
    for(auto&& r : results) {
        if(r == "..") {
            stack.pop_back();
        } else if(r == ".") {

        } else if(r == "") {

        } else {
            stack.push_back(r);
        }
    }

    QString result = (path[0] == separator) ? separatorString : "";
    int i = 0;
    for(auto&& s : stack) {
        result += ((i == 0) ? "" : separatorString) + s;
        i++;
    }
    return result;
}

QString KAdditional::absolutePath(const QString &path) {
    if(QCoreApplication::arguments().size() <= 0) return "";
    if(path.size() <= 0) return "";

#ifdef __WIN32__
    if(path.size() > 2 && path[1] == ":" && path[2] == separator) return path;
#else
    if(path[0] == separatorString) return path;
#endif

    return constrainPath(QCoreApplication::arguments()[0] + separatorString + ".." + separatorString + path);
}

bool KAdditional::urlEndsWith(const QUrl &url, const QString string) {
    return url.path().endsWith(string);
}

void KAdditional::mkdirIfNotExist(const QString &path) {
    if(!QDir(path).exists()) {
        auto folderName = path.split(KAdditional::separator);
        if(folderName.size() > 0) {
            QDir(KAdditional::constrainPath(path + KAdditional::separator + "..")).mkdir(folderName.last());
        }
    }
}

QString KAdditional::urlPath(const QUrl &url) {
    auto path = url.path();
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    if(!path.isEmpty()) {
        path.remove(0, 1);
    }

    path.replace("/", "\\");
#endif
    return path;
}

int KAdditional::extractInt(const QString &str, bool *ok) {
    QRegularExpression regexp("[a-zA-Zа-яА-Я_ ]*([0-9]+).*");
    auto match = regexp.match(str);
    if(match.hasMatch()) {
        return match.captured(match.lastCapturedIndex()).toInt(ok);
    } else {
        if(ok)
            *ok = false;
        return 0;
    }
}
