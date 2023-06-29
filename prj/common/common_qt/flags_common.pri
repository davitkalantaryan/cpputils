#
# repo:                 cpputils
# file:			flags_common.pri
# path:			prj/common/common_qt/flags_common.pri  
# created on:		2023 Jan 10
# Created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
#

message ("$${PWD}/flags_common.pri")
cpputilsFlagsCommonIncluded = 1

isEmpty( cpputilsResolveCommonIncluded ) {
        include("$${PWD}/resolve_common.pri")
        cpputilsResolveCommonIncluded = 1
}

isEmpty( cinternalFlagsCommonIncluded ) {
        include ( "$${cinternalRepoRoot}/prj/common/common_qt/flags_common.pri" )
        cinternalFlagsCommonIncluded = 1
}

INCLUDEPATH += $${cpputilsRepoRoot}/include
