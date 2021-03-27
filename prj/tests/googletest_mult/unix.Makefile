
targetame=unittest

mkfile_path		= $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir		= $(shell dirname $(mkfile_path))

firstTarget: all

include $(mkfile_dir)/../../common/common_mkfl/unix.common.Makefile

SRC_DIR=$(repoRootPath)/src/tests/googletest
COMMON_SRC_DIR=$(repoRootPath)/src/common

UNIT_TEST_SRCS=$(shell find $(SRC_DIR) -name "*.cpp")
COMMON_SRCS=$(shell find $(COMMON_SRC_DIR) -name "*.cpp")

#CPPFLAGS_OLD := CPPFLAGS
#CPPFLAGS+=-Wno-implicit-fallthrough  -Wno-unknown-pragmas -Wno-attributes -I$(SRC_DIR)
CPPFLAGS = -Wno-sign-compare
CPPFLAGS += -I$(repoRootPath)/contrib/googletest/googletest/include -I$(repoRootPath)/include

LIBS += $(repoRootPath)/contrib/googletest/lib/libgtest_main.a
LIBS += $(repoRootPath)/contrib/googletest/lib/libgtest.a
LIBS += -lpthread

all: $(repoRootPath)/sys/$(lsbCode)/Debug/test/$(targetame)

#$(repoRootPath)/sys/$(lsbCode)/Debug/test/googletest: $(UNIT_TEST_SRCS:%=$(repoRootPath)/sys/$(lsbCode)/Debug/.objects/googletest/%.o)
#$(repoRootPath)/sys/$(lsbCode)/Debug/test/googletest: $(UNIT_TEST_SRCS:%=$(repoRootPath)/sys/$(lsbCode)/Debug/.objects/googletest/%.o)
$(repoRootPath)/sys/$(lsbCode)/Debug/test/$(targetame): $(UNIT_TEST_SRCS:%=build/Debug/%.o) $(COMMON_SRCS:%=build/Debug/%.o)
	@mkdir -p $(repoRootPath)/sys/$(lsbCode)/Debug/test
	@$(LINK) $^ $(LIBS) $(LFLAGS) -o $@
	#rm -f $@
	#ar r $@ $^
	#ranlib $@


.PHONY: clean
clean:
	@rm -rf $(repoRootPath)/sys/$(lsbCode)/Debug/.objects/googletest
	@rm -f  $(repoRootPath)/sys/$(lsbCode)/Debug/test/googletest
	@echo "  " cleaning of googletest complete !!!
