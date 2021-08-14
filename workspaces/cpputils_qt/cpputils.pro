

TEMPLATE = subdirs
#CONFIG += ordered


SUBDIRS		+=	"$${PWD}/../../prj/tests/any_quick_test_qt/any_quick_test.pro"
SUBDIRS		+=	"$${PWD}/../../prj/tests/googletest_mult/googletest_getter.pro"

# devsheetlang.g4

OTHER_FILES	+=	\
	"$${PWD}/../../.gitattributes"						\
	"$${PWD}/../../.gitignore"						\
	"$${PWD}/../../.gitmodules"						\
	"$${PWD}/../../CMakeLists.txt"						\
	"$${PWD}/../../LICENSE"							\
	"$${PWD}/../../README.md"						\
	\
	"$${PWD}/../../docs/questions.md"					\
	\
	"$${PWD}/../../scripts/findfiles"					\
	"$${PWD}/../../scripts/findfiles.bat"					\
	\
	"$${PWD}/../../scripts/.cicd/unix_prebuild.sh"				\
	"$${PWD}/../../scripts/.cicd/unix_test_pull_to_master_build.sh"		\
	"$${PWD}/../../scripts/.cicd/unix_test_pull_to_master_unittest.sh"	\
	"$${PWD}/../../scripts/.cicd/windows_test_pull_to_master_build.bat"	\
	\
	"$${PWD}/../../.github/workflows/test_pull_to_master.yml"		\
	\
	"$${PWD}/../../prj/common/common_mkfl/unix.common.Makefile"		\
	"$${PWD}/../../prj/common/common_mkfl/windows.common.Makefile"		\
	"$${PWD}/../../prj/tests/googletest_mult/unix.Makefile"			\
	"$${PWD}/../../prj/tests/googletest_mult/windows.Makefile"
