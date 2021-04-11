#
# file:			googletest_getter.pro
# path:			prj/tests/googletest_mult/googletest_getter.pro
# created on:	2021 Mar 27
# created by:	Davit Kalantaryan
#

include ( $${PWD}/../../common/common_qt/sys_common.pri )

# we reevaluate this
DESTDIR = $${PRJ_PWD}/$${SYSTEM_PATH}/test

QT -= gui
QT -= core
QT -= widgets
CONFIG -= qt

win32{
} else {
	LIBS += $${PWD}/../../../contrib/googletest/lib/libgtest_main.a
	LIBS += $${PWD}/../../../contrib/googletest/lib/libgtest.a
	LIBS += -lpthread
}

repoRootPath=$${PWD}/../../..
SRC_DIR=$${repoRootPath}/src/tests/googletest

INCLUDEPATH += $${PWD}/../../../include
INCLUDEPATH += $${PWD}/../../../contrib/googletest/googletest/include

COMMON_SRCS   = $$system($${PWD}/../../../scripts/findfiles $${repoRootPath}/src/core .cpp)
COMMON_HDRS   = $$system($${PWD}/../../../scripts/findfiles $${repoRootPath}/include .h)
COMMON_HDRSPP = $$system($${PWD}/../../../scripts/findfiles $${repoRootPath}/include .hpp)

UNITTEST_SRCS   = $$system($${PWD}/../../../scripts/findfiles $${SRC_DIR} .cpp)
UNITTEST_HDRS   = $$system($${PWD}/../../../scripts/findfiles $${SRC_DIR} .h)
UNITTEST_HDRSPP = $$system($${PWD}/../../../scripts/findfiles $${SRC_DIR} .hpp)

SOURCES =  $$UNITTEST_SRCS
SOURCES += $$COMMON_SRCS
HEADERS =  $$UNITTEST_HDRS
HEADERS += $$UNITTEST_HDRSPP
HEADERS += $$COMMON_HDRS
HEADERS += $$COMMON_HDRSPP

OTHER_FILES +=	\
	$${PWD}/unix.Makefile										\
	$${PWD}/windows.Makefile									\
	$${PWD}/packages.config
