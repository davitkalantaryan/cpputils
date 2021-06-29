

mkfile_path		=  $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir		=  $(shell dirname $(mkfile_path))
repoRootPathCppUtils	:= $(shell curDir=`pwd` && cd $(mkfile_dir)/../../.. && pwd && cd ${curDir})
ifndef repoRootPath
	repoRootPath	:= $(repoRootPathCppUtils)
endif
osSystem		:= $(shell uname)
ifeq ($(osSystem),Darwin)
	lsbCode		:= mac
	DEFAULT_CC	:= clang
	DEFAULT_CXX	:= clang++
	DEFAULT_LINK	:= clang++
else
	lsbCode		:= $(shell lsb_release -sc)
	DEFAULT_CC	:= gcc
	DEFAULT_CXX	:= g++
	DEFAULT_LINK	:= g++
endif

MAKEFLAGS=-j 2

#CXX=ccache g++
ifndef CC_IN_USE
	CC_IN_USE=$(DEFAULT_CC)
endif
ifndef CXX_IN_USE
	CXX_IN_USE=$(DEFAULT_CXX)
endif
ifdef LINK_IN_USE
	LINK = $(LINK_IN_USE)
else
	LINK = $(DEFAULT_LINK)
endif
ifndef ANDROID_NDK_BIN
	ANDROID_NDK_BIN = ~/Android/Sdk/ndk/21.3.6528147/toolchains/llvm/prebuilt/linux-x86_64/bin
endif
ifndef ANDROID_CXX
	ANDROID_CXX = $(ANDROID_NDK_BIN)/clang++
endif
ifndef ANDROID_AR
	ANDROID_AR = $(ANDROID_NDK_BIN)/llvm-ar
endif
ifndef ANDROID_TARGET
	ANDROID_TARGET = armv7a-linux-androideabi21
endif
ifndef ANDROID_ARCH
	ANDROID_ARCH = -marm
endif

#EMXX=env CCACHE_CPP2=1 ccache em++
EMXX=em++

COMMON_FLAGS	+= -I$(repoRootPathCppUtils)/include

CPPFLAGS		=  $(COMMON_FLAGS)

DEBUG_FLAGS_DEBUG=-O0 -g
DEBUG_FLAGS_RELEASE=-O3

ifdef CPPUTILS_DEBUG
	DEBUG_FLAGS=$(DEBUG_FLAGS_DEBUG)
	Configuration=Debug
	nameExtension=d
else
	DEBUG_FLAGS=$(DEBUG_FLAGS_RELEASE)
	Configuration=Release
	nameExtension=
endif

EMFLAGS+=$(COMMON_FLAGS)
#EMFLAGS+=-isystem cpp/_system -Os
#EMFLAGS+=-s ASSERTIONS=1 -s ENVIRONMENT=web -s EXPORT_ES6=1
#EMFLAGS+=-s MODULARIZE=1 -s USE_ES6_IMPORT_META=0
EMFLAGS+=-s DISABLE_EXCEPTION_CATCHING=0
EMFLAGS+=-s ALLOW_MEMORY_GROWTH=1
#EMFLAGS+=-s USE_BOOST_HEADERS=1
#EMFLAGS+=-fexceptions

ANDROID_FLAGS += $(COMMON_FLAGS)
ANDROID_FLAGS += -target $(ANDROID_TARGET)
ANDROID_FLAGS += -fstack-protector-strong
ANDROID_FLAGS += -DANDROID
ANDROID_FLAGS += $(ANDROID_ARCH)

# host desktop
$(repoRootPath)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)/%.cc.o : %.cc
	mkdir -p $(dir $@)
	$(CXX_IN_USE) -c $(CPPFLAGS) $(DEBUG_FLAGS) -o $@ $<

$(repoRootPath)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)/%.cpp.o : %.cpp
	mkdir -p $(@D)
	$(CXX_IN_USE) -c $(CPPFLAGS) $(DEBUG_FLAGS) -o $@ $<

# webassembly
$(repoRootPath)/sys/wasm/$(Configuration)/.objects/$(targetName)/%.cc.bc : %.cc
	mkdir -p $(@D)
	$(EMXX) -c $(EMFLAGS) -o $@ $<

$(repoRootPath)/sys/wasm/$(Configuration)/.objects/$(targetName)/%.cpp.bc : %.cpp
	mkdir -p $(@D)
	$(EMXX) -c $(EMFLAGS) -o $@ $<

# android
$(repoRootPath)/sys/android/$(Configuration)/.objects/$(targetName)/%.cc.ao : %.cc
	mkdir -p $(@D)
	$(ANDROID_CXX) -c $(ANDROID_FLAGS) -o $@ $<

$(repoRootPath)/sys/android/$(Configuration)/.objects/$(targetName)/%.cpp.ao : %.cpp
	mkdir -p $(@D)
	$(ANDROID_CXX) -c $(ANDROID_FLAGS) -o $@ $<
