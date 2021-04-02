#!/bin/bash

# script to prepare developer host, to work with the code on this repo

scriptDirectoryBase=`dirname ${0}`
scriptFileName=`basename ${0}`
cd ${scriptDirectoryBase}
fileOrigin=`readlink ${scriptFileName}`
if [ ! -z "$fileOrigin" ]; then
	relativeSourceDir=`dirname ${fileOrigin}`
	cd ${relativeSourceDir}
fi
scriptDirectory=`pwd`
echo scriptDirectory=$scriptDirectory

cd ../..
repositoryRoot=`pwd`


# thanks to https://stackoverflow.com/questions/3466166/how-to-check-if-running-in-cygwin-mac-or-linux
if [[ "$(uname)" == "Darwin" ]]; then
	# Do something under Mac OS X platform
	lsbCode=mac
	qtTarget=clang_64
elif [[ "$(expr substr $(uname -s) 1 5)" == "Linux" ]]; then
	# Do something under GNU/Linux platform
	lsbCode=`lsb_release -sc`
	qtTarget=gcc_64
#elif [[ "$(expr substr $(uname -s) 1 10)" == "MINGW32_NT" ]]; then
#	# Do something under 32 bits Windows NT platform
#elif [[ "$(expr substr $(uname -s) 1 10)" == "MINGW64_NT" ]]; then
#	# Do something under 64 bits Windows NT platform
#else
fi

cd ${repositoryRoot}/prj/tests/googletest_mult
make -f unix.Makefile $@
