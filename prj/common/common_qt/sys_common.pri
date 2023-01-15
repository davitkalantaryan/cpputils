#
# file:				sys_common.pri
# path:				prj/common/common_qt/sys_common.pri    
# created on:		2023 Jan 10
# Created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
#

message ("$${PWD}/sys_common.pri")

isEmpty( cpputilsRepoRoot ) {
	cpputilsRepoRoot = $${PWD}/../../..
}

isEmpty( repositoryRoot ) {
	repositoryRoot = $${cpputilsRepoRoot}
}

isEmpty( cinternalRepoRoot ) {
	cinternalRepoRoot=$${cpputilsRepoRoot}/contrib/cinternal
}


include ( "$${cinternalRepoRoot}/prj/common/common_qt/sys_common.pri" )
