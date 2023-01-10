#
# file:				flags_common.pri
# path:				prj/common/common_qt/flags_common.pri  
# created on:		2023 Jan 10
# Created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
#

message ("$${PWD}/flags_common.pri")

isEmpty( cpputilsRepoRoot ) {
	cpputilsRepoRoot = $${PWD}/../../..
}

isEmpty( cinternalRepoRoot ) {
	cinternalRepoRoot=$${cpputilsRepoRoot}/contrib/cinternal
}

include ( "$${cinternalRepoRoot}/prj/common/common_qt/flags_common.pri" )

INCLUDEPATH += $${cpputilsRepoRoot}/include
