

mkfile_path			=  $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir			=  $(shell dirname $(mkfile_path))

ifndef cpputilsRepoRoot
        cpputilsRepoRoot	:= $(shell curDir=`pwd` && cd $(mkfile_dir)/../../.. && pwd && cd ${curDir})
endif

ifndef repositoryRoot
        repositoryRoot	= $(cpputilsRepoRoot)
endif

ifndef artifactRoot
        artifactRoot	= $(repositoryRoot)
endif

ifndef cinternalRepoRoot
        cinternalRepoRoot	= $(cpputilsRepoRoot)/contrib/cinternal
endif


COMMON_FLAGS	+= -I$(cpputilsRepoRoot)/include
include $(cinternalRepoRoot)/prj/common/common_mkfl/sys_common.unix.Makefile
