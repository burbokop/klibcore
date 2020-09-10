#include "kmoduleswitch.h"


KModuleSwitchInterface::KModuleSwitchInterface(QObject *parent) : QObject(parent) {
    connect(this, &KModuleSwitchInterface::activeModuleNameChanged, this, [this](auto a){ m_onActiveModuleChanged(a); });
}
