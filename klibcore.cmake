cmake_minimum_required(VERSION 3.5)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(${CMAKE_CURRENT_LIST_DIR})

set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/src/audio/kamplitudetransformer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/audio/kaudiodevice.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/audio/kintegratedsound.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/audio/ksound.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/audio/ksoundarray.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/audio/ksoundchain.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/audio/ksoundmix.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/audio/ksoundprocessor.cpp

    ${CMAKE_CURRENT_LIST_DIR}/src/containers/kobservablelist.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/containers/ktreenode.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/containers/kuniversaltable.cpp

    ${CMAKE_CURRENT_LIST_DIR}/src/experimental/bus/kabstractbus.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/experimental/bus/kdirectbus.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/experimental/bus/kmultithreadbus.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/experimental/universalqueue/kcirclebuffer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/experimental/universalqueue/kuniversalqueue.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/experimental/universalqueue/kvoidhandle.cpp

    ${CMAKE_CURRENT_LIST_DIR}/src/graphics/paint/karraypaintedtool.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/graphics/paint/kmodelpaintedtool.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/graphics/paint/kpagepaintedtool.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/graphics/paint/kpaintedtool.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/graphics/paint/kstackpaintedtool.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/graphics/kaftershiningmonitor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/graphics/khistorymonitor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/graphics/klamp.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/graphics/klamprectangle.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/graphics/kpainteditem.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/graphics/kqmlloader.cpp

    ${CMAKE_CURRENT_LIST_DIR}/src/math/processors/kamplifier.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/math/processors/kdifferentiator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/math/processors/kintegratorprocessor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/math/processors/kmemoryprocessor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/math/processors/knoisegenerator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/math/processors/koscillator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/math/processors/kqualitydeteriorator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/math/processors/krppressureprocessor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/math/processors/ksignalprocessor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/math/keventcounter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/math/kfading.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/math/kmath.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/math/krisedetector.cpp

    ${CMAKE_CURRENT_LIST_DIR}/src/memcontrol/kabstractfactory.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/memcontrol/kmodulehandler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/memcontrol/kmoduleswitch.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/memcontrol/kpull.cpp

    ${CMAKE_CURRENT_LIST_DIR}/src/models/kcustomgridmodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/models/kcustomtablemodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/models/kflexiblemodel.cpp

    ${CMAKE_CURRENT_LIST_DIR}/src/network/kframeagregator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/network/klocalbeacon.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/network/klocalconnector.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/network/klocalretranslator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/network/klocalsyncronizer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/network/kpackage.cpp

    ${CMAKE_CURRENT_LIST_DIR}/src/utility/kabstractvaluehistory.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/utility/kvaluehistory.h
    ${CMAKE_CURRENT_LIST_DIR}/src/utility/kdelegate.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/utility/kdelegatechooser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/utility/kmemorydiagnosticservice.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/utility/kmetafunction.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/utility/kobjectlistener.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/utility/ksearchinput.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/utility/ksysinfo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/utility/kthreadorientedfunction.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/utility/ktype.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/utility/kvaluehistory.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/utility/kvaluesaver.cpp

    ${CMAKE_CURRENT_LIST_DIR}/src/kadditional.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/kclassregistry.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/klibinfo.cpp
    )

set(HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/src/audio/ksoundprocessor.h
    ${CMAKE_CURRENT_LIST_DIR}/src/audio/kamplitudetransformer.h
    ${CMAKE_CURRENT_LIST_DIR}/src/audio/kaudiodevice.h
    ${CMAKE_CURRENT_LIST_DIR}/src/audio/kintegratedsound.h
    ${CMAKE_CURRENT_LIST_DIR}/src/audio/ksound.h
    ${CMAKE_CURRENT_LIST_DIR}/src/audio/ksoundarray.h
    ${CMAKE_CURRENT_LIST_DIR}/src/audio/ksoundchain.h
    ${CMAKE_CURRENT_LIST_DIR}/src/audio/ksoundmix.h

    ${CMAKE_CURRENT_LIST_DIR}/src/containers/kuniversaltable.h
    ${CMAKE_CURRENT_LIST_DIR}/src/containers/kobservablelist.h
    ${CMAKE_CURRENT_LIST_DIR}/src/containers/ktreenode.h

    ${CMAKE_CURRENT_LIST_DIR}/src/experimental/bus/kmultithreadbus.h
    ${CMAKE_CURRENT_LIST_DIR}/src/experimental/bus/kabstractbus.h
    ${CMAKE_CURRENT_LIST_DIR}/src/experimental/bus/kdirectbus.h
    ${CMAKE_CURRENT_LIST_DIR}/src/experimental/universalqueue/kvoidhandle.h
    ${CMAKE_CURRENT_LIST_DIR}/src/experimental/universalqueue/kcirclebuffer.h
    ${CMAKE_CURRENT_LIST_DIR}/src/experimental/universalqueue/kuniversalqueue.h

    ${CMAKE_CURRENT_LIST_DIR}/src/graphics/paint/kstackpaintedtool.h
    ${CMAKE_CURRENT_LIST_DIR}/src/graphics/paint/karraypaintedtool.h
    ${CMAKE_CURRENT_LIST_DIR}/src/graphics/paint/kmodelpaintedtool.h
    ${CMAKE_CURRENT_LIST_DIR}/src/graphics/paint/kpagepaintedtool.h
    ${CMAKE_CURRENT_LIST_DIR}/src/graphics/paint/kpaintedtool.h
    ${CMAKE_CURRENT_LIST_DIR}/src/graphics/kqmlloader.h
    ${CMAKE_CURRENT_LIST_DIR}/src/graphics/kaftershiningmonitor.h
    ${CMAKE_CURRENT_LIST_DIR}/src/graphics/khistorymonitor.h
    ${CMAKE_CURRENT_LIST_DIR}/src/graphics/klamp.h
    ${CMAKE_CURRENT_LIST_DIR}/src/graphics/klamprectangle.h
    ${CMAKE_CURRENT_LIST_DIR}/src/graphics/kpainteditem.h

    ${CMAKE_CURRENT_LIST_DIR}/src/math/processors/ksignalprocessor.h
    ${CMAKE_CURRENT_LIST_DIR}/src/math/processors/kamplifier.h
    ${CMAKE_CURRENT_LIST_DIR}/src/math/processors/kdifferentiator.h
    ${CMAKE_CURRENT_LIST_DIR}/src/math/processors/kintegratorprocessor.h
    ${CMAKE_CURRENT_LIST_DIR}/src/math/processors/kmemoryprocessor.h
    ${CMAKE_CURRENT_LIST_DIR}/src/math/processors/knoisegenerator.h
    ${CMAKE_CURRENT_LIST_DIR}/src/math/processors/koscillator.h
    ${CMAKE_CURRENT_LIST_DIR}/src/math/processors/kqualitydeteriorator.h
    ${CMAKE_CURRENT_LIST_DIR}/src/math/processors/krppressureprocessor.h
    ${CMAKE_CURRENT_LIST_DIR}/src/math/krisedetector.h
    ${CMAKE_CURRENT_LIST_DIR}/src/math/keventcounter.h
    ${CMAKE_CURRENT_LIST_DIR}/src/math/kfading.h
    ${CMAKE_CURRENT_LIST_DIR}/src/math/kmath.h

    ${CMAKE_CURRENT_LIST_DIR}/src/memcontrol/kpull.h
    ${CMAKE_CURRENT_LIST_DIR}/src/memcontrol/kabstractfactory.h
    ${CMAKE_CURRENT_LIST_DIR}/src/memcontrol/kmodulehandler.h
    ${CMAKE_CURRENT_LIST_DIR}/src/memcontrol/kmoduleswitch.h

    ${CMAKE_CURRENT_LIST_DIR}/src/models/kflexiblemodel.h
    ${CMAKE_CURRENT_LIST_DIR}/src/models/kcustomgridmodel.h
    ${CMAKE_CURRENT_LIST_DIR}/src/models/kcustomtablemodel.h

    ${CMAKE_CURRENT_LIST_DIR}/src/network/kpackage.h
    ${CMAKE_CURRENT_LIST_DIR}/src/network/kframeagregator.h
    ${CMAKE_CURRENT_LIST_DIR}/src/network/klocalbeacon.h
    ${CMAKE_CURRENT_LIST_DIR}/src/network/klocalconnector.h
    ${CMAKE_CURRENT_LIST_DIR}/src/network/klocalretranslator.h
    ${CMAKE_CURRENT_LIST_DIR}/src/network/klocalsyncronizer.h

    ${CMAKE_CURRENT_LIST_DIR}/src/utility/kvaluesaver.h
    ${CMAKE_CURRENT_LIST_DIR}/src/utility/kabstractvaluehistory.h
    ${CMAKE_CURRENT_LIST_DIR}/src/utility/kdelegate.h
    ${CMAKE_CURRENT_LIST_DIR}/src/utility/kdelegatechooser.h
    ${CMAKE_CURRENT_LIST_DIR}/src/utility/kmemorydiagnosticservice.h
    ${CMAKE_CURRENT_LIST_DIR}/src/utility/kmetafunction.h
    ${CMAKE_CURRENT_LIST_DIR}/src/utility/kobjectlistener.h
    ${CMAKE_CURRENT_LIST_DIR}/src/utility/ksearchinput.h
    ${CMAKE_CURRENT_LIST_DIR}/src/utility/ksysinfo.h
    ${CMAKE_CURRENT_LIST_DIR}/src/utility/kthreadorientedfunction.h
    ${CMAKE_CURRENT_LIST_DIR}/src/utility/ktype.h

    ${CMAKE_CURRENT_LIST_DIR}/src/kmacro.h
    ${CMAKE_CURRENT_LIST_DIR}/src/kadditional.h
    ${CMAKE_CURRENT_LIST_DIR}/src/kclassregistry.h
    ${CMAKE_CURRENT_LIST_DIR}/src/klibinfo.h

    )


add_library(klibcore SHARED
    ${SOURCES}
    ${HEADERS}
    )

add_compile_definitions(KLIBCORE_USE_LIBRARY)

find_package(Qt5 COMPONENTS
    Core
    Quick
    Multimedia
    Widgets
    Test
    Qml
    REQUIRED
    )

target_link_libraries(klibcore
    Qt5::Quick
    Qt5::Multimedia
    Qt5::Widgets
    Qt5::Test
    Qt5::Qml
    )


#Tests

enable_testing()

add_executable(klibcore_test
    ${CMAKE_CURRENT_LIST_DIR}/tests/kuniversalqueue_test.h
    ${CMAKE_CURRENT_LIST_DIR}/tests/kadditional_test.h
    ${CMAKE_CURRENT_LIST_DIR}/tests/kaudio_test.h
    ${CMAKE_CURRENT_LIST_DIR}/tests/kflexiblemodel_test.h
    ${CMAKE_CURRENT_LIST_DIR}/tests/kgraphics_test.h
    ${CMAKE_CURRENT_LIST_DIR}/tests/kpull_test.h
    ${CMAKE_CURRENT_LIST_DIR}/tests/kmath_test.h

    ${CMAKE_CURRENT_LIST_DIR}/tests/kadditional_test.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/kaudio_test.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/kflexiblemodel_test.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/kgraphics_test.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/kpull_test.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/kmath_test.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/kuniversalqueue_test.cpp

    ${CMAKE_CURRENT_LIST_DIR}/tests/main.cpp
    )

target_link_libraries(klibcore_test
    Qt5::Quick
    Qt5::Multimedia
    Qt5::Widgets
    Qt5::Test
    Qt5::Qml
    klibcore
    )


add_test(NAME KLibCoreTest COMMAND klibcore_test)


execute_process(
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND mkdir -p klibcore_doc
)

execute_process(
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/klibcore_doc
    COMMAND ${CMAKE_CURRENT_LIST_DIR}/gendoc.sh
)
