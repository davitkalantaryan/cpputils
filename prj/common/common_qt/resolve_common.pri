#
# file:			sys_common.pri
# path:			prj/common/common_qt/sys_common.pri    
# created on:		2023 Jan 10
# Created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
#

message ("$${PWD}/resolve_common.pri")
cpputilsResolveCommonIncluded = 1

isEmpty( cpputilsRepoRoot ) {
        cpputilsRepoRoot = $$(cpputilsRepoRoot)
        isEmpty(cpputilsRepoRoot) {
            cpputilsRepoRoot = $${PWD}/../../..
        }
}

isEmpty( repositoryRoot ) {
        repositoryRoot = $$(repositoryRoot)
        isEmpty(repositoryRoot) {
            repositoryRoot = $${cpputilsRepoRoot}
        }
}

isEmpty(artifactRoot) {
    artifactRoot = $$(artifactRoot)
    isEmpty(artifactRoot) {
        artifactRoot = $${repositoryRoot}
    }
}

isEmpty( cinternalRepoRoot ) {
        cinternalRepoRoot = $$(cinternalRepoRoot)
        isEmpty(cinternalRepoRoot) {
            cinternalRepoRoot=$${cpputilsRepoRoot}/contrib/cinternal
        }
}

