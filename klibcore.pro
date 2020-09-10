QT += core
QT += quick
QT += testlib
QT += widgets
QT += multimedia

CONFIG += c++17

#CONFIG += shared dll
#TEMPLATE = lib

INCLUDEPATH += $$PWD



HEADERS += \
    $$PWD/src/kmacro.h \
    $$PWD/src/math/kmath.h \
    $$PWD/src/klibinfo.h \
    $$PWD/src/tests/kmath_test.h \
    $$PWD/src/math/keventcounter.h \
    $$PWD/src/math/krisedetector.h \
    $$PWD/src/kadditional.h \
    $$PWD/src/tests/kadditional_test.h \
    $$PWD/src/models/kcustomgridmodel.h \
    $$PWD/src/models/kcustomtablemodel.h \
    $$PWD/src/math/kfading.h \
    $$PWD/src/math/processors/kintegratorprocessor.h \
    $$PWD/src/math/processors/kmemoryprocessor.h \
    $$PWD/src/math/processors/knoisegenerator.h \
    $$PWD/src/math/processors/kqualitydeteriorator.h \
    $$PWD/src/math/processors/ksignalprocessor.h \
    $$PWD/src/graphics/kaftershiningmonitor.h \
    $$PWD/src/experimental/universalqueue/kuniversalqueue.h \
    $$PWD/src/utility/ktype.h \
    $$PWD/src/experimental/universalqueue/kcirclebuffer.h \
    $$PWD/src/experimental/universalqueue/kvoidhandle.h \
    $$PWD/src/tests/kuniversalqueue_test.h \
    $$PWD/src/experimental/bus/kmultithreadbus.h \
    $$PWD/src/utility/kmetafunction.h \
    $$PWD/src/utility/kvaluehistory.h \
    $$PWD/src/graphics/klamprectangle.h \
    $$PWD/src/utility/ksysinfo.h \
    $$PWD/src/math/processors/kdifferentiator.h \
    $$PWD/src/utility/kmemorydiagnosticservice.h \
    $$PWD/src/graphics/kpainteditem.h \
    $$PWD/src/graphics/khistorymonitor.h \
    $$PWD/src/utility/kabstractvaluehistory.h \
    $$PWD/src/tests/kgraphics_test.h \
    $$PWD/src/audio/kamplitudetransformer.h \
    $$PWD/src/audio/kintegratedsound.h \
    $$PWD/src/audio/ksound.h \
    $$PWD/src/audio/ksoundarray.h \
    $$PWD/src/audio/ksoundchain.h \
    $$PWD/src/audio/kaudiodevice.h \
    $$PWD/src/audio/ksoundmix.h \
    $$PWD/src/audio/ksoundprocessor.h \
    $$PWD/src/math/processors/koscillator.h \
    $$PWD/src/tests/kaudio_test.h \
    $$PWD/src/utility/kobjectlistener.h \
    $$PWD/src/network/klocalretranslator.h \
    $$PWD/src/network/kframeagregator.h \
    $$PWD/src/utility/kthreadorientedfunction.h \
    $$PWD/src/network/klocalconnector.h \
    $$PWD/src/network/klocalsyncronizer.h \
    $$PWD/src/experimental/bus/kabstractbus.h \
    $$PWD/src/experimental/bus/kdirectbus.h \
    $$PWD/src/network/kpackage.h \
    $$PWD/src/graphics/klamp.h \
    $$PWD/src/graphics/kqmlloader.h \
    $$PWD/src/utility/kdelegate.h \
    $$PWD/src/utility/kdelegatechooser.h \
    $$PWD/src/utility/ksearchinput.h \
    $$PWD/src/utility/kvaluesaver.h \
    $$PWD/src/network/klocalbeacon.h \
    $$PWD/src/kclassregistry.h \
    $$PWD/src/math/processors/krppressureprocessor.h \
    $$PWD/src/math/processors/kamplifier.h \
    $$PWD/src/graphics/paint/kmodelpaintedtool.h \
    $$PWD/src/graphics/paint/kpagepaintedtool.h \
    $$PWD/src/graphics/paint/kpaintedtool.h \
    $$PWD/src/models/kflexiblemodel.h \
    $$PWD/src/tests/kflexiblemodel_test.h \
    $$PWD/src/graphics/paint/kstackpaintedtool.h \
    $$PWD/src/graphics/paint/karraypaintedtool.h \
    $$PWD/src/tests/kpull_test.h \
    $$PWD/src/containers/kobservablelist.h \
    $$PWD/src/containers/ktreenode.h \
    $$PWD/src/containers/kuniversaltable.h \
    $$PWD/src/memcontrol/kabstractfactory.h \
    $$PWD/src/memcontrol/kmodulehandler.h \
    $$PWD/src/memcontrol/kpull.h \
    $$PWD/src/memcontrol/kmoduleswitch.h


SOURCES += \
    $$PWD/src/math/kmath.cpp \
    $$PWD/src/klibinfo.cpp \
    $$PWD/src/klibmain.cpp \
    $$PWD/src/tests/kmath_test.cpp \
    $$PWD/src/math/keventcounter.cpp \
    $$PWD/src/math/krisedetector.cpp \
    $$PWD/src/kadditional.cpp \
    $$PWD/src/tests/kadditional_test.cpp \
    $$PWD/src/models/kcustomgridmodel.cpp \
    $$PWD/src/models/kcustomtablemodel.cpp \
    $$PWD/src/math/kfading.cpp \
    $$PWD/src/math/processors/kintegratorprocessor.cpp \
    $$PWD/src/math/processors/kmemoryprocessor.cpp \
    $$PWD/src/math/processors/knoisegenerator.cpp \
    $$PWD/src/math/processors/kqualitydeteriorator.cpp \
    $$PWD/src/math/processors/ksignalprocessor.cpp \
    $$PWD/src/graphics/kaftershiningmonitor.cpp \
    $$PWD/src/experimental/universalqueue/kuniversalqueue.cpp \
    $$PWD/src/utility/ktype.cpp \
    $$PWD/src/experimental/universalqueue/kcirclebuffer.cpp \
    $$PWD/src/experimental/universalqueue/kvoidhandle.cpp \
    $$PWD/src/tests/kuniversalqueue_test.cpp \
    $$PWD/src/experimental/bus/kmultithreadbus.cpp \
    $$PWD/src/utility/kmetafunction.cpp \
    $$PWD/src/utility/kvaluehistory.cpp \
    $$PWD/src/graphics/klamprectangle.cpp \
    $$PWD/src/utility/ksysinfo.cpp \
    $$PWD/src/math/processors/kdifferentiator.cpp \
    $$PWD/src/utility/kmemorydiagnosticservice.cpp \
    $$PWD/src/graphics/kpainteditem.cpp \
    $$PWD/src/graphics/khistorymonitor.cpp \
    $$PWD/src/utility/kabstractvaluehistory.cpp \
    $$PWD/src/tests/kgraphics_test.cpp \
    $$PWD/src/audio/kamplitudetransformer.cpp \
    $$PWD/src/audio/kintegratedsound.cpp \
    $$PWD/src/audio/ksound.cpp \
    $$PWD/src/audio/ksoundarray.cpp \
    $$PWD/src/audio/ksoundchain.cpp \
    $$PWD/src/audio/kaudiodevice.cpp \
    $$PWD/src/audio/ksoundmix.cpp \
    $$PWD/src/audio/ksoundprocessor.cpp \
    $$PWD/src/math/processors/koscillator.cpp \
    $$PWD/src/tests/kaudio_test.cpp \
    $$PWD/src/utility/kobjectlistener.cpp \
    $$PWD/src/network/klocalretranslator.cpp \
    $$PWD/src/network/kframeagregator.cpp \
    $$PWD/src/utility/kthreadorientedfunction.cpp \
    $$PWD/src/network/klocalconnector.cpp \
    $$PWD/src/network/klocalsyncronizer.cpp \
    $$PWD/src/experimental/bus/kabstractbus.cpp \
    $$PWD/src/experimental/bus/kdirectbus.cpp \
    $$PWD/src/network/kpackage.cpp \
    $$PWD/src/graphics/klamp.cpp \
    $$PWD/src/graphics/kqmlloader.cpp \
    $$PWD/src/utility/kdelegate.cpp \
    $$PWD/src/utility/kdelegatechooser.cpp \
    $$PWD/src/utility/ksearchinput.cpp \
    $$PWD/src/utility/kvaluesaver.cpp \
    $$PWD/src/network/klocalbeacon.cpp \
    $$PWD/src/kclassregistry.cpp \
    $$PWD/src/math/processors/krppressureprocessor.cpp \
    $$PWD/src/math/processors/kamplifier.cpp \
    $$PWD/src/graphics/paint/kmodelpaintedtool.cpp \
    $$PWD/src/graphics/paint/kpagepaintedtool.cpp \
    $$PWD/src/graphics/paint/kpaintedtool.cpp \
    $$PWD/src/models/kflexiblemodel.cpp \
    $$PWD/src/tests/kflexiblemodel_test.cpp \
    $$PWD/src/graphics/paint/kstackpaintedtool.cpp \
    $$PWD/src/graphics/paint/karraypaintedtool.cpp \
    $$PWD/src/tests/kpull_test.cpp \
    $$PWD/src/containers/kobservablelist.cpp \
    $$PWD/src/containers/ktreenode.cpp \
    $$PWD/src/containers/kuniversaltable.cpp \
    $$PWD/src/memcontrol/kabstractfactory.cpp \
    $$PWD/src/memcontrol/kmodulehandler.cpp \
    $$PWD/src/memcontrol/kpull.cpp \
    $$PWD/src/memcontrol/kmoduleswitch.cpp

DISTFILES += \
    $$PWD/README.md

RESOURCES += \
    $$PWD/klibcoreqml.qrc
