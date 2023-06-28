#
# file:			sys_common.pri
# path:			prj/common/common_qt/sys_common.pri    
# created on:		2023 Jan 10
# Created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
#

message ("$${PWD}/sys_common.pri")
cpputilsSysCommonIncluded = 1

include ( "$${PWD}/resolve_common.pri" )
isEmpty( cinternalSysCommonIncluded ) {
        include ( "$${cinternalRepoRoot}/prj/common/common_qt/sys_common.pri" )
        cinternalSysCommonIncluded = 1
}
