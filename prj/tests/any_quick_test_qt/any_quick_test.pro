#
# file:			any_quick_test.pro
# path:			prj/tests/any_quick_test_qt/any_quick_test.pro
# created on:	2021 Mar 07
# created by:	Davit Kalantaryan
#

include ( $${PWD}/../../common/common_qt/sys_common.pri )

QT -= gui
QT -= core
QT -= widgets
CONFIG -= qt

INCLUDEPATH += $${PWD}/../../../include
DEFINES += CPPUTILS_USING_STATIC_LIB_OR_OBJECTS


SOURCES	+=		\
	$${PWD}/../../../src/tests/main_any_quick_test.cpp					\
	$${PWD}/../../../src/core/cpputils_bigint.cpp						\
	$${PWD}/../../../src/core/cpputils_functional_old.cpp				\
	$${PWD}/../../../src/core/cpputils_hashtbl.cpp						\
	$${PWD}/../../../src/core/cpputils_inscopecleaner.cpp				


HEADERS	+=		\
	$${PWD}/../../../include/cpputils_internal_header.h					\
	$${PWD}/../../../include/cpputils/bigint.hpp						\
	$${PWD}/../../../include/cpputils/bigint.impl.hpp					\
	$${PWD}/../../../include/cpputils/endian.hpp						\
	$${PWD}/../../../include/cpputils/functional.hpp					\
	$${PWD}/../../../include/cpputils/functional_old.hpp				\
	$${PWD}/../../../include/cpputils/functional_old.impl.hpp			\
	$${PWD}/../../../include/cpputils/hashtbl.hpp						\
	$${PWD}/../../../include/cpputils/hashtbl.impl.hpp					\
	$${PWD}/../../../include/cpputils/inscopecleaner.hpp				\
	$${PWD}/../../../include/cpputils/sharedptr.hpp						\
	$${PWD}/../../../include/cpputils/sharedptr.impl.hpp				\
	
