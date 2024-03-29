# "$Date: 2019-11-15 01:28:07 -0300 (sex, 15 nov 2019) $"
# "$Author: chico $"
# "$Revision: 148 $"

#-------------------------------------------------
#
# Project created by QtCreator 2019-11-06T13:21:10
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

VER_MAJ = 0
VER_MIN = 9
VER_PAT = 3
PROJECT_DIR=$$PWD
include (../QtBaseGeral/base_geral.pri)


TARGET = horloge
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

# DEFINES += DESCANSO

SOURCES += \
		main.cpp \
		CApplication.cpp \
		horloge.cpp \
		runguard.cpp

HEADERS += \
		CApplication.h \
		horloge.h \
		runguard.h

FORMS += \
		horloge.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = $$[_PRO_FILE_PWD_]
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
	horloge.qrc

TRANSLATIONS += \
	./en_US.ts \
	./es_ES.ts \
	./pt_BR.ts

DISTFILES += \
	en_US.ts \
	es_ES.ts \
	pt_BR.ts \
	build.sh \
	distclean.sh \
	_config.yml \
	README.md

win32:	DEFINES += _TTY_WIN_ # QWT_DLL QT_DLL

win32:	RC_FILE += horloge.rc
