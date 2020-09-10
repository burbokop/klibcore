#include "karraypaintedtool.h"
#include "kmodelpaintedtool.h"

KArrayPaintedTool::KArrayPaintedTool() {}

void KArrayPaintedTool::addModel(QAbstractListModel *model, const QTextOption &option, bool paintHeader, double hr, QList<QByteArray> rolesSequance) {
    auto p = new KModelPaintedTool(model);
    p->setTextOption(option);
    p->setPaintHeader(paintHeader);
    p->setHorizontalRatio(hr);
    p->setRolesSequence(rolesSequance);
    addChild(KPointerHandle<KPaintedTool>(p, KPointerHandle<KPaintedTool>::ManualDestroy));
}

void KArrayPaintedTool::addText(QString text, const QTextOption &option) {
    addChild(KPointerHandle<KPaintedTool>(new KTextPaintedTool(text, option), KPointerHandle<KPaintedTool>::ManualDestroy));
}

