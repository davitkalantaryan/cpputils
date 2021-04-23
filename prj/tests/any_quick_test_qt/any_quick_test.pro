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

LIBS += -pthread

INCLUDEPATH += $${PWD}/../../../include
DEFINES += CPPUTILS_USING_STATIC_LIB_OR_OBJECTS


SOURCES	+=		\
	$${PWD}/../../../src/tests/main_any_quick_test.cpp					\
	$${PWD}/../../../src/core/cpputils_bigint.cpp						\
	$${PWD}/../../../src/core/cpputils_functional_old.cpp				\
	$${PWD}/../../../src/core/cpputils_hashtbl.cpp						\
	$${PWD}/../../../src/core/cpputils_inscopecleaner.cpp				\
	$${PWD}/../../../src/core/cpputils_thread_local.cpp


HEADERS	+=		\
	$${PWD}/../../../include/cpputils_internal_header.h					\
	$${PWD}/../../../include/cpputils/bigint.hpp						\
	$${PWD}/../../../include/cpputils/bigint.impl.hpp					\
	$${PWD}/../../../include/cpputils/endian.hpp						\
	$${PWD}/../../../include/cpputils/enums.hpp							\
	$${PWD}/../../../include/cpputils/functional.hpp					\
	$${PWD}/../../../include/cpputils/functional_old.hpp				\
	$${PWD}/../../../include/cpputils/functional_old.impl.hpp			\
	$${PWD}/../../../include/cpputils/hashtbl.hpp						\
	$${PWD}/../../../include/cpputils/hashtbl.def.hpp					\
	$${PWD}/../../../include/cpputils/hashtbl.impl.hpp					\
	$${PWD}/../../../include/cpputils/inscopecleaner.hpp				\
	$${PWD}/../../../include/cpputils/macroses.h						\
	$${PWD}/../../../include/cpputils/sharedptr.hpp						\
	$${PWD}/../../../include/cpputils/sharedptr.impl.hpp				\
	$${PWD}/../../../include/cpputils/enums/base.hpp					\
	$${PWD}/../../../include/cpputils/enums/fast.hpp					\
	$${PWD}/../../../include/cpputils/enums/fast.impl.hpp				\
	$${PWD}/../../../include/cpputils/enums/full.hpp					\
	$${PWD}/../../../include/cpputils/enums/full.impl.hpp				\
	$${PWD}/../../../include/cpputils/enums/fullslow.hpp				\
	$${PWD}/../../../include/cpputils/enums/fullslow.impl.hpp			\
	$${PWD}/../../../include/cpputils/thread_local.h					\
	$${PWD}/../../../include/cpputils/tls_data.hpp						\
	$${PWD}/../../../include/cpputils/tls_data.impl.hpp					\
	$${PWD}/../../../include/cpputils/tls_ptr.windows.impl.hpp			\
	$${PWD}/../../../include/cpputils/tls_ptr.posix.impl.hpp			\
