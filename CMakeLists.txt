get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 6.2 Qt5 5.15 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui REQUIRED)


file(GLOB SOURCES
    # "${CMAKE_CURRENT_SOURCE_DIR}/BGI/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ax/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ax/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/BGI/bgi.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/BGI/winpalet.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/BGI/winpalet.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Comp/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Comp/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Ext/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Ext/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Gora/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Gora/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/qt/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/qt/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/qt/vx/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/qt/vx/*.h"
)
add_library ( ${TARGET_NAME} ${SOURCES} )

target_include_directories ( ${TARGET_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/BGI
    ${CMAKE_CURRENT_SOURCE_DIR}/Comp
    ${CMAKE_CURRENT_SOURCE_DIR}/Ext
    ${CMAKE_CURRENT_SOURCE_DIR}/Gora
    ${CMAKE_CURRENT_SOURCE_DIR}/qt
    ${CMAKE_CURRENT_SOURCE_DIR}/ax
)

target_compile_definitions( ${TARGET_NAME} PUBLIC QT_ANTLIB _VX_)
#target_compile_definitions(desktop PRIVATE
#    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
#    )
target_link_libraries(${TARGET_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
        find_package(Qt6 REQUIRED COMPONENTS Core5Compat)
        target_link_libraries(${TARGET_NAME} PRIVATE Qt6::Core5Compat)
endif()


#install ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
install(TARGETS ${TARGET_NAME} DESTINATION lib)
install(FILES ${SOURCES} DESTINATION include/${TARGET_NAME})		  


