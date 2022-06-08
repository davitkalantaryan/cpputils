#!/bin/bash
# script to prepare developer host, to work with the code on this repo


# in mac short directory calculation based on n'readlink' or 'realpath' will not work
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


# Let's prepare emsdk
if [ -z "$emSdkVersion" ]; then
	#emSdkVersion=latest
	#emSdkVersion=1.39.8
	emSdkVersion=2.0.14
fi
if [[ ! -f "${repositoryRoot}/contrib/emsdk_version_${emSdkVersion}_prepared" ]]; then
	cd "${repositoryRoot}/contrib/emsdk"
	./emsdk install ${emSdkVersion}
	./emsdk activate ${emSdkVersion}
	touch "${repositoryRoot}/contrib/emsdk_version_${emSdkVersion}_prepared"
else
	cd "${repositoryRoot}/contrib/emsdk"
	echo "emsdk already prepared for this repository"
fi
source ./emsdk_env.sh
export EMSDK_FOR_CPPUTILS_SET=1


# $1 is target(lsbCode), $2 is configuration (Release,Debug)
compileGoogleTest(){
	#cd "${repositoryRoot}/contrib/googletest"
	cd "${repositoryRoot}"
	if [[ "$1" == "wasm" ]]; then
		#emcmake cmake -H. -B../../build/googletest/$1/$2 -DCMAKE_BUILD_TYPE=$2
		emcmake cmake -H. -Bbuild/googletest/$1/$2 -DCMAKE_BUILD_TYPE=$2
	else
		#cmake -H. -B../../build/googletest/$1/$2 -DCMAKE_BUILD_TYPE=$2
		cmake -H. -Bbuild/googletest/$1/$2 -DCMAKE_BUILD_TYPE=$2
	fi
	#cd ../../build/googletest/$1/$2
	cd build/googletest/$1/$2
	cmake --build .
	mkdir -p "${repositoryRoot}/sys/$1/$2/lib"
	cp lib/*.a "${repositoryRoot}/sys/$1/$2/lib/".
	rm -rf "${repositoryRoot}/contrib/googletest/googletest/generated"
}

# compile google test
compileGoogleTest $lsbCode Release
compileGoogleTest $lsbCode Debug
compileGoogleTest wasm     Release
compileGoogleTest wasm     Debug
