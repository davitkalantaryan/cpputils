

mkfile_path				=  $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir				=  $(shell dirname $(mkfile_path))
repoRootPathCppUtils	:= $(shell curDir=`pwd` && cd $(mkfile_dir)/../../.. && pwd && cd ${curDir})
ifndef repoRootPath
	repoRootPath		:= $(repoRootPathCppUtils)
endif
osSystem	  := $(shell uname)
ifeq ($(osSystem),Darwin)
	lsbCode			:= mac
	DEFAULT_CC		:= clang
	DEFAULT_CXX		:= clang++
	DEFAULT_LINK	:= clang++
else
	lsbCode			:= $(shell lsb_release -sc)
	DEFAULT_CC		:= gcc
	DEFAULT_CXX		:= g++
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

$(repoRootPath)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)/%.cc.o : %.cc
	mkdir -p $(dir $@)
	$(CXX_IN_USE) -c $(CPPFLAGS) $(DEBUG_FLAGS) -o $@ $<

$(repoRootPath)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)/%.cpp.o : %.cpp
	mkdir -p $(@D)
	$(CXX_IN_USE) -c $(CPPFLAGS) $(DEBUG_FLAGS) -o $@ $<

$(repoRootPath)/sys/wasm/$(Configuration)/.objects/$(targetName)/%.cc.bc : %.cc
	mkdir -p $(@D)
	$(EMXX) -c $(EMFLAGS) -o $@ $<

$(repoRootPath)/sys/wasm/$(Configuration)/.objects/$(targetName)/%.cpp.bc : %.cpp
	mkdir -p $(@D)
	$(EMXX) -c $(EMFLAGS) -o $@ $<
