TEMPLATE = lib
QT       += core gui widgets

CONFIG += c++17



DEFINES +=QT_ANTLIB

INCLUDEPATH +=$$PWD/ax
INCLUDEPATH +=$$PWD/qt
INCLUDEPATH +=$$PWD/BGI
INCLUDEPATH +=$$PWD/Ext
INCLUDEPATH +=$$PWD/Gora
INCLUDEPATH +=$$PWD/Comp

include($$PWD/BGI/bgi.pri)
include($$PWD/Comp/comp.pri)
include($$PWD/Ext/ext.pri)
include($$PWD/Gora/gora.pri)
include($$PWD/qt/qt.pri)
include($$PWD/ax/ax.pri)





















