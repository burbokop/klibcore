#include "ksearchinput.h"
#include <QPainter>

QStringList KSearchInput::parseModel(const QVariant &model, const QString &text, const QString &role) {
    QStringList result;
    auto js = model.value<QJSValue>();
    if(!js.isNull() && js.toVariant().isValid()) {
        auto list = js.toVariant().toList();
        for(auto l : list) {
            auto str = l.toString();
            if(str != text && str.indexOf(text) == 0) {
                result.push_back(str);
            }
        }
    } else {
        auto ref = model.value<QQmlListReference>();
        if(ref.isValid()) {
            for(auto i = 0, size = ref.count(); i < size; ++i) {
                auto obj = ref.at(i);
                if(obj) {
                    auto str = obj->property(role.toStdString().c_str()).toString();
                    if(str != text && str.indexOf(text) == 0) {
                        result.push_back(str);
                    }
                }
            }
        } else {
            auto qobj = model.value<QObject*>();
            if(qobj) {
                auto meta = qobj->metaObject();
                for(auto i = 0, count = meta->propertyCount(); i < count; ++i) {
                    QString str = meta->property(i).name();
                    if(str != text && str.indexOf(text) == 0) {
                        result.push_back(str);
                    }
                }
            } else {
                auto list = model.toList();
                if(list.size() > 0) {
                    for(auto l : list) {
                        auto str = l.toString();
                        if(str != text && str.indexOf(text) == 0) {
                            result.push_back(str);
                        }
                    }
                }
            }
        }
    }
    return result;
}

QString KSearchInput::sameBeginningSubstring(const QStringList &list) {
    QString::size_type i = 0;
    QString result;

    QString::size_type max = std::numeric_limits<QString::size_type>::min();
    for(auto l : list) {
        if(l.size() > max) {
            max = l.size();
        }
    }

    while(true) {
        QString substr;
        for(auto l : list) {
            auto s = l.mid(0, i);
            if(!substr.isEmpty() && s != substr) {
                return result;
            }
            substr = s;
        }
        result = substr;
        if(i > max) {
            return result;
        }
        ++i;
    }
}

KSearchInput::KSearchInput(QQuickItem *parent) : QQuickPaintedItem(parent) {
    setAcceptedMouseButtons(Qt::LeftButton);
    connect(this, &KSearchInput::textChanged, this, [this](){ update(); });
}

void KSearchInput::paint(QPainter *painter) {
    if(qFuzzyCompare(textSize(), 0))
        return;

    painter->drawText(boundingRect(), text(), QTextOption(Qt::AlignRight | Qt::AlignVCenter));
}

template<typename T, typename R>
typename T::value_type kmin(const T &container, R(T::value_type::*function)() const) {
    R min = std::numeric_limits<R>::max();
    typename T::value_type result;
    for(auto c : container) {
        auto current = (c.*function)();
        if(current < min) {
            min = current;
            result = c;
        }
    }
    return result;
}

void KSearchInput::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Backspace) {
        if(m_text.size() > 0)
            m_text.resize(m_text.size() - 1);
    } else if(event->key() == Qt::Key_Tab) {
        if(m_text.size() > 1) {
            auto stringVariants = parseModel(model(), text(), role());
            auto res = sameBeginningSubstring(stringVariants);
            if(!res.isEmpty())
                m_text = res;
        }
    } else if(event->key() == Qt::Key_Return) {
        accepted();
    } else {
        m_text += event->text();
    }
    textChanged(text());
}

void KSearchInput::mousePressEvent(QMouseEvent *event) {
    Q_UNUSED(event)
    setFocus(true);
}

