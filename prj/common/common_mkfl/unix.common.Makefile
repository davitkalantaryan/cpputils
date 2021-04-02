
mkfile_path    = $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir     = $(shell dirname $(mkfile_path))
repoRootPath  := $(shell curDir=`pwd` && cd $(mkfile_dir)/../../.. && pwd && cd ${curDir})
lsbCode		  := $(shell lsb_release -sc)

MAKEFLAGS=-j 2

#CXX=ccache g++
ifndef CC
	CC=gcc
endif
ifndef CXX
	CC=g++
endif
ifndef LINK
	LINK=g++
endif
EMXX=env CCACHE_CPP2=1 ccache em++

#COMMON_FLAGS=-g -Wall -Wextra -Werror -std=c++14 -Icpp 
#COMMON_FLAGS+=-Wno-attributes
#COMMON_FLAGS+=-Wno-format

CPPFLAGS=$(COMMON_FLAGS) -fPIC

DEBUG_FLAGS_DEBUG=-O0 -g
DEBUG_FLAGS_RELEASE=-O3

ifdef CPPUTILS_DEBUG
	DEBUG_FLAGS=$(DEBUG_FLAGS_DEBUG)
	Configuration=Debug
else
	DEBUG_FLAGS=$(DEBUG_FLAGS_RELEASE)
	Configuration=Release
endif

EMFLAGS=$(COMMON_FLAGS) -isystem cpp/_system -Os
EMFLAGS+=-s ASSERTIONS=1 -s ENVIRONMENT=web -s EXPORT_ES6=1
EMFLAGS+=-s MODULARIZE=1 -s USE_ES6_IMPORT_META=0
EMFLAGS+=-s DISABLE_EXCEPTION_CATCHING=0
EMFLAGS+=-s ALLOW_MEMORY_GROWTH=1
EMFLAGS+=-s USE_BOOST_HEADERS=1


$(repoRootPath)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)/%.cc.o : %.cc
	mkdir -p $(dir $@)
	$(CXX) -c $(CPPFLAGS) $(DEBUG_FLAGS) -o $@ $<

$(repoRootPath)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)/%.cpp.o : %.cpp
	mkdir -p $(dir $@)
	$(CXX) -c $(CPPFLAGS) $(DEBUG_FLAGS) -o $@ $<

$(repoRootPath)/sys/wasm/$(Configuration)/.objects/$(targetName)/%.cc.bc : %.cc
	mkdir -p $(dir $@)
	$(EMXX) -c $(EMFLAGS) -o $@ $<

$(repoRootPath)/sys/wasm/$(Configuration)/.objects/$(targetName)/%.cpp.bc : %.cpp
	mkdir -p $(dir $@)
	$(EMXX) -c $(EMFLAGS) -o $@ $<
