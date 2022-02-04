#!/bin/bash

# script to prepare developer host, to work with the code on this repo

#scriptFileFullPath=`readlink -f ${0}`
#scriptDirectory=`dirname ${scriptFileFullPath}`
#cd ${scriptDirectory}/../..
#repositoryRoot=`pwd`

# in mac os above short calculation will not work
# also realpath utilit is missing in mac

scriptDirectory=`dirname "${0}"`
scriptFileName=`basename "${0}"`
cd "${scriptDirectory}"
fileOrigin=`readlink "${scriptFileName}"` || :
while [ ! -z "${fileOrigin}" ]
do
	scriptDirectory=`dirname "${fileOrigin}"`
	scriptFileName=`basename "${fileOrigin}"`
	cd "${scriptDirectory}"
	fileOrigin=`readlink "${scriptFileName}"`  || :
done
cd ../..
repositoryRoot=`pwd`
echo repositoryRoot=$repositoryRoot


# https://intoli.com/blog/exit-on-errors-in-bash-scripts/
# exit when any command fails
set -e

# keep track of the last executed command
trap 'last_command=$current_command; current_command=$BASH_COMMAND' DEBUG
# echo an error message before exiting
#trap 'echo "\"${last_command}\" command finished with exit code $?."' EXIT


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


# $1 is target(lsbCode), $2 is configuration (Release,Debug)
compileGoogleTest(){
	cd "${repositoryRoot}/contrib/googletest"
	if [[ "$1" == "wasm" ]]; then
		emcmake cmake -H. -B../../build/googletest/$1/$2 -DCMAKE_BUILD_TYPE=$2
	else
		cmake -H. -B../../build/googletest/$1/$2 -DCMAKE_BUILD_TYPE=$2
	fi
	cd ../../build/googletest/$1/$2
	cmake --build .
	mkdir -p "${repositoryRoot}/sys/$1/$2/lib"
	cp lib/*.a "${repositoryRoot}/sys/$1/$2/lib/".
	rm -rf "${repositoryRoot}/contrib/googletest/googletest/generated"
}

# compile google test
compileGoogleTest $lsbCode Release
compileGoogleTest $lsbCode Debug
#compileGoogleTest wasm     Release
#compileGoogleTest wasm     Debug

