#-------------------------------------------------
#
# Project created by QtCreator 2015-05-18T17:20:50
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += xml
#QT       += network
#LIBS     += -LE:\YIQICHANG\CODE\SongsManage\SongsMaintain -llibcurl
LIBS     += -lvlc-qt -lvlc-qt-widgets
LIBS     += -L$$PWD/curl/lib -llibcurl
LIBS     += -L$$PWD/zlib128-dll/lib -lzdll
INCLUDEPATH += $$PWD/zlib128-dll/minizip
DEPENDPATH += $$PWD/zlib128-dll/minizip

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
OBJECTS_DIR += obj
UI_DIR += forms
RCC_DIR += rcc
MOC_DIR += moc
DESTDIR += bin

TARGET = YQC_SM
TEMPLATE = app

INCLUDEPATH += $$PWD

SOURCES += main.cpp\
    curlupload.cpp \
    mysqlquery.cpp \
    yqcdelegate.cpp \
    dropshadowwidget.cpp \
    pushbutton.cpp \
    liblistview.cpp \
    mainwidget.cpp \
    titlewidget.cpp \
    util.cpp \
    libinfowidget.cpp \
    songsquerywideget.cpp \
    singerquerywidget.cpp \
    songsonlinewidget.cpp \
    singeronlinewidget.cpp \
    songinfowidget.cpp \
    singerinfowdiget.cpp \
    songslistwidget.cpp \
    fmwidget.cpp \
    fminfowidget.cpp \
    adwidget.cpp \
    blackwidget.cpp \
    listinfowidget.cpp \
    tablemodel.cpp \
    itemdelegate.cpp \
    pagingtableview.cpp \
    libinfodialog.cpp \
    typeindexvalue.cpp \
    songinfodialog.cpp \
    singerinfodialog.cpp \
    fmaddmodifydialog.cpp \
    MP4Player.cpp \
    singeraddmodifydialog.cpp \
    releasedialog.cpp \            
    zlib128-dll/minizip/ioapi.c \
    zlib128-dll/minizip/mztools.c \
    zlib128-dll/minizip/unzip.c \
    zlib128-dll/minizip/zip.c \
    songslistaddmodifydialog.cpp \
    MD5.cpp

HEADERS  += \
    curlupload.h \
    enuminfo.h \
    mysqlquery.h \
    yqcdelegate.h \
    defistruct.h \
    dropshadowwidget.h \
    pushbutton.h \
    liblistview.h \
    mainwidget.h \
    titlewidget.h \
    util.h \
    libinfowidget.h \
    songsquerywideget.h \
    singerquerywidget.h \
    songsonlinewidget.h \
    singeronlinewidget.h \
    songinfowidget.h \
    singerinfowdiget.h \
    songslistwidget.h \
    fmwidget.h \
    fminfowidget.h \
    adwidget.h \
    blackwidget.h \
    listinfowidget.h \
    tablemodel.h \
    itemdelegate.h \
    pagingtableview.h \
    libinfodialog.h \
    typeindexvalue.h \
    songinfodialog.h \
    singerinfodialog.h \
    fmaddmodifydialog.h \
    MP4Player.h \
    singeraddmodifydialog.h \
    releasedialog.h \
    quazip_global.h \
    curl/curl.h \
    curl/curlbuild.h \
    curl/curlrules.h \
    curl/curlver.h \
    curl/easy.h \
    curl/mprintf.h \
    curl/multi.h \
    curl/stdcheaders.h \
    curl/typecheck-gcc.h \       
    zlib128-dll/minizip/crypt.h \
    zlib128-dll/minizip/ioapi.h \
    zlib128-dll/minizip/iowin32.h \
    zlib128-dll/minizip/mztools.h \
    zlib128-dll/minizip/unzip.h \
    zlib128-dll/minizip/zip.h \
    songslistaddmodifydialog.h \
    MD5.h

FORMS    += \
    addfmmedialist.ui \
    MP4Player.ui

RESOURCES += \    
    Resources\YQCML.qrc

RC_FILE += YQCSMico.rc
OTHER_FILES += YQCSMico.rc

DISTFILES += \
    search.qss \
    zlib128-dll/include/zlib.def \
    zlib128-dll/minizip/make_vms.com \
    zlib128-dll/minizip/miniunzip.1 \
    zlib128-dll/minizip/minizip.1 \
    zlib128-dll/minizip/minizip.pc.in \
    zlib128-dll/minizip/MiniZip64_Changes.txt \
    zlib128-dll/minizip/MiniZip64_info.txt \
    zlib128-dll/minizip/configure.ac \
    zlib128-dll/minizip/Makefile \
    zlib128-dll/minizip/Makefile.am


#win32: LIBS += -L$$PWD/quazip-0.7.1/lib/ -lquazip

#INCLUDEPATH += $$PWD/quazip-0.7.1/include
#DEPENDPATH += $$PWD/quazip-0.7.1/include






