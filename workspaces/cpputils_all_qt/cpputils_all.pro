

TEMPLATE = subdirs
#CONFIG += ordered

repositoryRoot = $${PWD}/../..


SUBDIRS		+=	"$${repositoryRoot}/prj/tests/any_quick_test_qt/any_quick_test.pro"
SUBDIRS		+=	"$${repositoryRoot}/prj/tests/googletest_mult/googletest_getter.pro"


OTHER_FILES += $$files($${repositoryRoot}/scripts/*.sh,true)
OTHER_FILES += $$files($${repositoryRoot}/scripts/*.bat,true)
OTHER_FILES += $$files($${repositoryRoot}/scripts/.cicd/*.sh,true)
OTHER_FILES += $$files($${repositoryRoot}/scripts/.cicd/*.bat,true)
OTHER_FILES += $$files($${repositoryRoot}/scripts/.raw/*.sh,true)
OTHER_FILES += $$files($${repositoryRoot}/scripts/.raw/*.bat,true)
OTHER_FILES += $$files($${repositoryRoot}/docs/*.md,true)
OTHER_FILES += $$files($${repositoryRoot}/docs/*.txt,true)
OTHER_FILES += $$files($${repositoryRoot}/.github/*.yml,true)

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
