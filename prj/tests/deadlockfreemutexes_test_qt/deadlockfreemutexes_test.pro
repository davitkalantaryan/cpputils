#
# file:			any_quick_test.pro
# path:			prj/tests/any_quick_test_qt/any_quick_test.pro
# created on:	2021 Mar 07
# created by:	Davit Kalantaryan
#

message("!!! $${_PRO_FILE_}")
include ( "$${PWD}/../../common/common_qt/flagsandsys_common.pri" )
DESTDIR     = "$${artifactRoot}/sys/$${CODENAME}/$$CONFIGURATION/test"

QT -= gui
QT -= core
QT -= widgets
CONFIG -= qt
CONFIG += console

DEFINES += CPPUTILS_DO_NOT_USE_STD_FUNCTION
DEFINES += cinternal_gettid_needed

win32{
	LIBS += -lWs2_32
} else {
	LIBS += -pthread
}


SOURCES	+=		\
    "$${cpputilsRepoRoot}/src/tests/main_deadlockfreemutexes_test.cpp"			\
    "$${cpputilsRepoRoot}/src/core/cpputils_runtimedeadlockfreemutexes.cpp"

HEADERS += \
    "$${cpputilsRepoRoot}/include/cpputils/impl/cpputils_orderedcalls.impl.hpp"		\
    "$${cpputilsRepoRoot}/include/cpputils/impl/cpputils_deadlockfreemutexes.impl.hpp"	\
    "$${cpputilsRepoRoot}/include/cpputils/deadlockfreemutexes.hpp"			\
    "$${cpputilsRepoRoot}/include/cpputils/export_symbols.h"				\
    "$${cpputilsRepoRoot}/include/cpputils/orderedcalls.hpp"				\
    "$${cpputilsRepoRoot}/include/cpputils/runtimedeadlockfreemutexes.hpp"
