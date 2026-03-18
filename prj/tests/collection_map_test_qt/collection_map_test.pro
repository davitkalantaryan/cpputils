#
# file:			any_quick_test.pro
# path:			prj/tests/any_quick_test_qt/any_quick_test.pro
# created on:	2021 Mar 07
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

DEFINES += CPPUTILS_DO_NOT_USE_STD_FUNCTION

win32{
	LIBS += -lWs2_32
} else {
	LIBS += -pthread
}

SOURCES	+= "$${PWD}/../../../src/tests/main_collection_map_test.cpp"
SOURCES	+= "$${cpputilsRepoRoot}/src/core/cpputils_collectionmap.cpp"
SOURCES += "$${cinternalRepoRoot}/src/core/cinternal_core_hash.c"
	
HEADERS += $$files($${cpputilsRepoRoot}/include/*.h,true)
HEADERS += $$files($${cpputilsRepoRoot}/include/*.hpp,true)
