# non-recursive Makefile https://github.com/AndreRenaud/non-recursive-make

mkfile_path    = $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir     = $(shell dirname $(mkfile_path))
repoRootPath  := $(shell curDir=`pwd` && cd $(mkfile_dir)/../../.. && pwd && cd ${curDir})
lsbCode		  := $(shell lsb_release -sc)

#MAKEFLAGS=-j 8
MAKEFLAGS=-j 2

#CC=disabled
#CXX=ccache g++
CC=gcc
CXX=g++
LINK=g++
EMXX=env CCACHE_CPP2=1 ccache em++

COMMON_FLAGS=-g -Wall -Wextra -Werror -std=c++14 -Icpp 
COMMON_FLAGS+=-Wno-attributes
COMMON_FLAGS+=-Wno-format

CPPFLAGS=$(COMMON_FLAGS) -fPIC

GENSRC_FLAGS=-Wno-unused-parameter

DEBUG_FLAGS=

EMFLAGS=$(COMMON_FLAGS) -isystem cpp/_system -Os
EMFLAGS+=-s ASSERTIONS=1 -s ENVIRONMENT=web -s EXPORT_ES6=1
EMFLAGS+=-s MODULARIZE=1 -s EXPORT_NAME=SSS -s USE_ES6_IMPORT_META=0
EMFLAGS+=-s DISABLE_EXCEPTION_CATCHING=0
EMFLAGS+=-s ALLOW_MEMORY_GROWTH=1
EMFLAGS+=-s USE_BOOST_HEADERS=1
EMFLAGS+=-Wno-overloaded-virtual
EMFLAGS+=-Wno-potentially-evaluated-expression
EMFLAGS+=-Wno-deprecated-copy 
EMFLAGS+=-DGOOGLE_PROTOBUF_NO_THREAD_SAFETY
EMFLAGS+=-DNO_DEBUG_IKU

# generate .o .bc relative to Makefile

build/Debug/%.cc.o : %.cc
	mkdir -p $(dir $@)
	$(CXX) -c $(CPPFLAGS) $(DEBUG_FLAGS) -o $@ $<

build/Debug/%.cpp.o : %.cpp
	mkdir -p $(dir $@)
	$(CXX) -c $(CPPFLAGS) $(DEBUG_FLAGS) -o $@ $<

build/wasm/%.cc.bc : %.cc
	mkdir -p $(dir $@)
	$(EMXX) -c $(EMFLAGS) -o $@ $<

build/wasm/%.cpp.bc : %.cpp
	mkdir -p $(dir $@)
	$(EMXX) -c $(EMFLAGS) -o $@ $<

# treat files in build/gen the same way

build/Debug/%.cc.o : build/gen/%.cc
	mkdir -p $(dir $@)
	$(CXX) -c $(CPPFLAGS) $(DEBUG_FLAGS) $(GENSRC_FLAGS) -o $@ $<

build/Debug/%.cpp.o : build/gen/%.cpp
	mkdir -p $(dir $@)
	$(CXX) -c $(CPPFLAGS) $(DEBUG_FLAGS) $(GENSRC_FLAGS) -o $@ $<

build/wasm/%.cc.bc : build/gen/%.cc
	mkdir -p $(dir $@)
	$(EMXX) -c $(EMFLAGS) $(GENSRC_FLAGS) -o $@ $<

build/wasm/%.cpp.bc : build/gen/%.cpp
	mkdir -p $(dir $@)
	$(EMXX) -c $(EMFLAGS) $(GENSRC_FLAGS) -o $@ $<
