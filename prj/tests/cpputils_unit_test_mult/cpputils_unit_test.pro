#
# file:			cpputils_unit_test.pro
# path:			prj/tests/cpputils_unit_test_mult/cpputils_unit_test.pro
# created on:	2021 Mar 27
# created by:	Davit Kalantaryan
#

message("!!! $${_PRO_FILE_}")
include ( "$${PWD}/../../common/common_qt/flagsandsys_common.pri" )
DESTDIR = "$${ArifactFinal}/test"

QT -= gui
QT -= core
QT -= widgets
CONFIG -= qt
CONFIG += console

win32{
	LIBS += -lWs2_32
} else {
	LIBS += -pthread
}


DEFINES += CINTERNAL_UNIT_TEST_USE_GTEST_LIKE_MACROSES

SOURCES += $$files($${cpputilsRepoRoot}/src/tests/unit_test/*.cpp)
SOURCES	+= $$files($${cpputilsRepoRoot}/src/core/*.cpp)  # I assume, that in core we will not have subdirs
SOURCES += $$files($${cinternalRepoRoot}/src/core/*.c)


HEADERS =  $$files($${cpputilsRepoRoot}/include/*.h,true)
HEADERS += $$files($${cpputilsRepoRoot}/include/*.hpp,true)

OTHER_FILES += $$files($${PWD}/*.Makefile)
OTHER_FILES += "$${PWD}/packages.config.locked"
