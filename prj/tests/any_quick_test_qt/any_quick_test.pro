#
# file:			any_quick_test.pro
# path:			prj/tests/any_quick_test_qt/any_quick_test.pro
# created on:	2021 Mar 07
# created by:	Davit Kalantaryan
#

include ( "$${PWD}/../../common/common_qt/sys_common.pri" )

QT -= gui
QT -= core
QT -= widgets
CONFIG -= qt

LIBS += -pthread

repoRootPath=$${PWD}/../../..

INCLUDEPATH += "$${PWD}/../../../include"
DEFINES += CPPUTILS_USING_STATIC_LIB_OR_OBJECTS


SOURCES	+=		\
	"$${PWD}/../../../src/tests/main_any_quick_test.cpp"			\
	"$${PWD}/../../../src/core/cpputils_bigint.cpp"				\
	"$${PWD}/../../../src/core/cpputils_functional_old.cpp"			\
	"$${PWD}/../../../src/core/cpputils_hashtbl.cpp"			\
	"$${PWD}/../../../src/core/cpputils_inscopecleaner.cpp"			\
	"$${PWD}/../../../src/core/cpputils_thread_local.cpp"

COMMON_HDRS	= $$cpputilsFindFilesRecursive($${repoRootPath}/include, .h)
COMMON_HDRSPP	= $$cpputilsFindFilesRecursive($${repoRootPath}/include, .hpp)

HEADERS += $$COMMON_HDRS
HEADERS += $$COMMON_HDRSPP
