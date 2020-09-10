#include "kmodelpaintedtool.h"

#include <QPainter>
#include <QAbstractListModel>

#include <src/kadditional.h>


int KModelPaintedTool::findRoleIndex(const QHash<int, QByteArray> &hash, const QByteArray &value) {
    for(auto it = hash.begin(); it != hash.end(); ++it) {
        if(it.value() == value) {
            return it.key();
        }
    }
    return -1;
}

KModelPaintedTool::KModelPaintedTool(QAbstractListModel *model) {
    m_model = model;
}

void KModelPaintedTool::paint(QPainter *painter) {
    if(!m_model)
        return;

    auto hash = m_model->roleNames();
    auto size = m_model->rowCount();

    if(sortFunction()) {
        const auto sl = KAdditional::mapToSortedList(hash, [this](auto a, auto b){
            return sortFunction()(a.second, b.second);
        });
        QList<QByteArray> newRoleSequence;
        for(auto sli : sl) {
            newRoleSequence.push_back(sli.second);
        }
        setRolesSequence(newRoleSequence);
    }

    QList<int> indicesSequance;
    for(auto s : rolesSequence()) {
        auto index = findRoleIndex(hash, s);
        if(index >= 0) {
            indicesSequance.push_back(index);
        }
    }

    if(size > 0 && painter) {
        auto rowHeight = height() / (size + (m_paintHeader ? 1 : 0));
        if(m_paintHeader) {
            paintLine(painter, model(), -1, 0, width(), rowHeight, Options(textOption(), 2, horizontalRatio(), indicesSequance), xOffset(), yOffset(), hash);
        }

        for(auto i = 0; i < size; ++i) {
            paintLine(painter, model(), i, (i + (m_paintHeader ? 1 : 0)) * rowHeight, width(), rowHeight, Options(textOption(), 1, horizontalRatio(), indicesSequance), xOffset(), yOffset(), hash);
        }
    }
}

void KModelPaintedTool::paintLine(QPainter *painter, QAbstractListModel *model, int row, int y, int rowWidth, int rowHeight, const Options &options, int xOffset, int yOffset, const QHash<int, QByteArray> &hash) {
    if(hash.size() > 0) {
        int x = xOffset;

        double hratio = 1;
        bool hdiraction = false;
        if(options.horizontalRatio() < 0) {
            hratio = -options.horizontalRatio();
            hdiraction = true;
        } else {
            hratio = options.horizontalRatio();
        }

        const int tmp = rowWidth / (hratio + 1);
        auto f = [&options, hratio, tmp, &hash, painter, model, row, rowHeight, y, yOffset](int role, int ax, bool first) {
            int actualCellWith = 0;
            if(first) {
                actualCellWith = tmp * hratio;
            } else {
                if(hash.size() != 1)
                    actualCellWith = tmp / (hash.size() - 1);
            }

            paintCell(painter, model, row, role, ax, yOffset + y, actualCellWith, rowHeight, options, hash);
            return actualCellWith;
        };

        int i = 0;

        if(options.rolesSequence().size() > 0) {
            QList<int> displayedRoles;
            for(auto role : options.rolesSequence()) {
                x += f(role, x, hdiraction ? (i == (options.rolesSequence().size() - 1)) : (i == 0));
                displayedRoles.push_back(role);
                ++i;
            }
            for(auto it = hash.begin(); it != hash.end(); ++it) {
                if(!displayedRoles.contains(it.key())) {
                    x += f(it.key(), x,  hdiraction ? (i == (hash.size() - 1)) : (i == 0));
                    ++i;
                }
            }
        } else {
            for(auto it = hash.begin(); it != hash.end(); ++it) {
                x += f(it.key(), x,  hdiraction ? (i == (hash.size() - 1)) : (i == 0));
                ++i;
            }
        }
    }
}

void KModelPaintedTool::paintCell(QPainter *painter, QAbstractListModel *model, int row, int role, int x, int y, int cellWidth, int cellHeight, const Options &options, const QHash<int, QByteArray> &hash) {
    QString value;
    QPen lastPen = painter->pen();
    if(row >= 0) {
        value = model->data(model->index(row), role).toString();
    } else {
        auto it = hash.find(role);
        if(it != hash.end()) {
            value = QString::fromUtf8(it.value());
        }
        auto pen = painter->pen();
        pen.setWidth(pen.width() * options.penWidthScale());
        painter->setPen(pen);
    }
    painter->drawRect(x, y, cellWidth, cellHeight);
    painter->drawText(QRectF(x, y, cellWidth, cellHeight), value, options.textOption());
    painter->setPen(lastPen);
}
