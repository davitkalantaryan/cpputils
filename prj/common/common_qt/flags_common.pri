#
# file:			flags_common.pri
# path:			prj/common/common_qt/flags_common.pri  
# created on:		2023 Jan 10
# Created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
#

message ("$${PWD}/flags_common.pri")
cpputilsFlagsCommonIncluded = 1

include ( "$${PWD}/resolve_common.pri" )
isEmpty( cinternalFlagsCommonIncluded ) {
        include ( "$${cinternalRepoRoot}/prj/common/common_qt/flags_common.pri" )
        cinternalFlagsCommonIncluded = 1
}

INCLUDEPATH += $${cpputilsRepoRoot}/include
