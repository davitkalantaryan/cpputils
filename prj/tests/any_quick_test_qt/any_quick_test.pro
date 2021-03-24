#
# file:			any_quick_test.pro
# path:			prj/tests/any_quick_test_qt/any_quick_test.pro
# created on:	2021 Mar 07
# created by:	Davit Kalantaryan
#

include ( $${PWD}/../../common/common_qt/sys_common.pri )

INCLUDEPATH += $${PWD}/../../../include
DEFINES += CPPUTILS_USING_STATIC_LIB_OR_OBJECTS


SOURCES	+=		\
	$${PWD}/../../../src/tests/main_any_quick_test.cpp					\
	$${PWD}/../../../src/common/common_hashtbl.cpp						\
	$${PWD}/../../../src/common/common_bigint.cpp


HEADERS	+=		\
	$${PWD}/../../../include/cpputils_internal_header.h					\
	$${PWD}/../../../include/common/endian.hpp							\
	$${PWD}/../../../include/common/hashtbl.hpp							\
	$${PWD}/../../../include/common/hashtbl.impl.hpp					\
	$${PWD}/../../../include/common/bigint.hpp							\
	$${PWD}/../../../include/common/bigint.impl.hpp						\
	
