

TEMPLATE = subdirs
#CONFIG += ordered

repositoryRoot = $${PWD}/../..

include ( "$${repositoryRoot}/prj/common/common_qt/sys_common.pri" )

SUBDIRS		+=	"$${repositoryRoot}/prj/tests/any_quick_test_qt/any_quick_test.pro"
SUBDIRS		+=	"$${repositoryRoot}/prj/tests/googletest_mult/googletest_getter.pro"

UNIX_SCRIPTS	= $$files($${repositoryRoot}/scripts/*.sh,true)
WINDOWS_SCRIPTS	= $$files($${repositoryRoot}/scripts/*.bat,true)
MDS_IN_DOCS	= $$files($${repositoryRoot}/docs/*.md,true)
TXT_IN_DOCS	= $$files($${repositoryRoot}/docs/*.txt,true)
YML_GH_WORKS	= $$files($${repositoryRoot}/.github/workflows/*.yml)  # default is recurse=false
# YML_GL_WORKS	= $$files($${repositoryRoot}/.gitlab/*.yml,true) # todo: implement this

OTHER_FILES += $$UNIX_SCRIPTS
OTHER_FILES += $$WINDOWS_SCRIPTS
OTHER_FILES += $$MDS_IN_DOCS
OTHER_FILES += $$TXT_IN_DOCS
OTHER_FILES += $$YML_GH_WORKS
OTHER_FILES += $$YML_GL_WORKS

OTHER_FILES	+=	\
	"$${repositoryRoot}/.gitattributes"									\
	"$${repositoryRoot}/.gitignore"										\
	"$${repositoryRoot}/.gitmodules"									\
	"$${repositoryRoot}/CMakeLists.txt"									\
	"$${repositoryRoot}/LICENSE"										\
	"$${repositoryRoot}/README.md"										\
	\
	"$${PWD}/../../scripts/findfiles_no_sp"								\
	"$${PWD}/../../scripts/findfiles_sp"								\
	\
	"$${PWD}/../../prj/common/common_mkfl/unix.common.Makefile"			\
	"$${PWD}/../../prj/common/common_mkfl/windows.common.Makefile"		\
	"$${PWD}/../../prj/tests/googletest_mult/unix.Makefile"				\
	"$${PWD}/../../prj/tests/googletest_mult/windows.Makefile"
