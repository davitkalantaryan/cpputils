

mkfile_path		=  $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir		=  $(shell dirname $(mkfile_path))
cpputilsRepoRoot	:= $(shell curDir=`pwd` && cd $(mkfile_dir)/../../.. && pwd && cd ${curDir})
ifndef repoRootPath
        repoRootPath	= $(cpputilsRepoRoot)
endif
#include $(cpputilsRepoRoot)/contrib/cinternal/prj/common/common_mkfl/unix.common.Makefile
include $(cpputilsRepoRoot)/contrib/cinternal/prj/common/common_mkfl/sys_common.unix.Makefile
COMMON_FLAGS	+= -I$(cpputilsRepoRoot)/include
