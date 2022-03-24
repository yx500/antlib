

DEFINES +=QT_ANTLIB

#QT+=concurrent

INCLUDEPATH +=$$PWD/../qt
INCLUDEPATH +=$$PWD/../BGI
INCLUDEPATH +=$$PWD/../Ext
INCLUDEPATH +=$$PWD/../Gora
INCLUDEPATH +=$$PWD/../Comp


HEADERS += \
$$PWD/../qt/systypes.h \
$$PWD/../qt/winbgi_qt.h \
$$PWD/../BGI/winbgi.h \
$$PWD/../Comp/ACom_T.h \
$$PWD/../Comp/ACom_V.h \
$$PWD/../Comp/ALIB.h \
$$PWD/../Comp/APch.h \
$$PWD/../Comp/col.h \
$$PWD/../Comp/common.h \
$$PWD/../Comp/Comp.h \
$$PWD/../Comp/Elem.h \
$$PWD/../Comp/EnergUnit.h \
$$PWD/../Comp/F.h \
$$PWD/../Comp/Gorl.h \
$$PWD/../Comp/Impuls.h \
$$PWD/../Comp/LampExtDraw.h \
$$PWD/../Comp/Lamps.h \
$$PWD/../Comp/Line.h \
$$PWD/../Comp/Marshrut.h \
$$PWD/../Comp/out_num.h \
$$PWD/../Comp/pmComp.h \
$$PWD/../Comp/Polig.h \
$$PWD/../Comp/Scrin.h \
$$PWD/../Comp/SIZE.h \
$$PWD/../Comp/Stan.h \
$$PWD/../Comp/Static.h \
$$PWD/../Comp/Strel.h \
$$PWD/../Comp/Str_fun.h \
$$PWD/../Comp/Svet.h \
$$PWD/../Comp/uExtElem.h \
$$PWD/../Comp/Vatempl.h \
$$PWD/../Comp/Ways.h \
$$PWD/../Comp/YchParams.h \
$$PWD/../Comp/Y_STREL.h \
$$PWD/../Gora/Gor_Elem.h \
$$PWD/../Gora/Gor_Logic.h \
$$PWD/../Gora/tGorka.h \
$$PWD/../Gora/tNsl4Term.h \
$$PWD/../Ext/actools.h \
$$PWD/../Ext/EXDH.h \
$$PWD/../Ext/propmap.h \
$$PWD/../Ext/uETTList.h \
$$PWD/../Ext/uEXD.h \
$$PWD/../Ext/uFormula.h \
$$PWD/../Ext/uImgContainer.h \
$$PWD/../Ext/uParString.h \
    $$PWD/vcl.h


SOURCES += \
$$PWD/../Comp/ACom_T.cpp \
$$PWD/../Comp/ACom_V.cpp \
$$PWD/../Comp/ALIB.cpp \
$$PWD/../Comp/APch.cpp \
$$PWD/../Comp/col.cpp \
$$PWD/../Comp/common.cpp \
$$PWD/../Comp/Comp.cpp \
$$PWD/../Comp/Elem.cpp \
$$PWD/../Comp/EnergUnit.cpp \
$$PWD/../Comp/F.cpp \
$$PWD/../Comp/Gorl.cpp \
$$PWD/../Comp/Impuls.cpp \
$$PWD/../Comp/LampExtDraw.cpp \
$$PWD/../Comp/Lamps.cpp \
$$PWD/../Comp/Line.cpp \
$$PWD/../Comp/Marshrut.cpp \
$$PWD/../Comp/out_num.cpp \
$$PWD/../Comp/pmComp.cpp \
$$PWD/../Comp/Polig.cpp \
$$PWD/../Comp/Scrin.cpp \
$$PWD/../Comp/SIZE.cpp \
$$PWD/../Comp/Stan.cpp \
$$PWD/../Comp/Static.cpp \
$$PWD/../Comp/Strel.cpp \
$$PWD/../Comp/Str_fun.cpp \
$$PWD/../Comp/Svet.cpp \
$$PWD/../Comp/uExtElem.cpp \
$$PWD/../Comp/Vatempl.cpp \
$$PWD/../Comp/Ways.cpp \
$$PWD/../Comp/YchParams.cpp \
$$PWD/../Comp/Y_STREL.cpp \
$$PWD/../Gora/Gor_Elem.cpp \
$$PWD/../Gora/Gor_Logic.cpp \
$$PWD/../Ext/actools.cpp \
$$PWD/../Ext/propmap.cpp \
$$PWD/../Ext/uETTList.cpp \
$$PWD/../Ext/uEXD.cpp \
$$PWD/../Ext/uFormula.cpp \
$$PWD/../Ext/uImgContainer.cpp \
$$PWD/../Ext/uParString.cpp

    
