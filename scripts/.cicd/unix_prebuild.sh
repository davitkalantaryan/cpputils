#!/bin/bash

# script to prepare developer host, to work with the code on this repo

scriptFileFullPath=`readlink -f ${0}`
scriptDirectory=`dirname ${scriptFileFullPath}`
cd ${scriptDirectory}/../..
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

git submodule sync --recursive
git submodule update --init --recursive


# compile google test
cd ${repositoryRoot}/contrib/googletest
cmake -H. -B../../build/googletest/Release -DCMAKE_BUILD_TYPE=Release
cd ../../build/googletest/Release
cmake --build .
mkdir -p ${repositoryRoot}/sys/$lsbCode/Release/lib
cp lib/*.a ${repositoryRoot}/sys/$lsbCode/Release/lib/.
#rm -rf googletest/generated
cd ${repositoryRoot}/contrib/googletest
cmake -H. -B../../build/googletest/Debug -DCMAKE_BUILD_TYPE=Debug
cd ../../build/googletest/Debug
cmake --build .
mkdir -p ${repositoryRoot}/sys/$lsbCode/Debug/lib
cp lib/*.a ${repositoryRoot}/sys/$lsbCode/Debug/lib/.
rm -rf ${repositoryRoot}/contrib/googletest/googletest/generated
