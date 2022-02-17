

if [ $# -eq 0 ]; then
	if [ $0 != "/bin/bash" -a $0 != "bash" -a $0 != "-bash" ]; then
		sourcePath_local=`bash -c "source $0 1"`
	else
		sourcePath_local=${BASH_SOURCE[0]}
	fi
else
	if [ $# -eq 1 ]; then
		echo ${BASH_SOURCE[0]}
		return 0
	else
		sourcePath_local=${1}
	fi
fi


makeMainJob (){

	local sourcePath=${sourcePath_local}
	unset sourcePath_local
	echo sourcePath=$sourcePath

	local currentDirectory=`pwd`
	echo currentDirectory=$currentDirectory

	if [[ "$(uname)" == "Darwin" ]]; then
		# Do something under Mac OS X platform
		lsbCode=mac
	elif [[ "$(expr substr $(uname -s) 1 5)" == "Linux" ]]; then
		# Do something under GNU/Linux platform
		lsbCode=`lsb_release -sc`
	#elif [[ "$(expr substr $(uname -s) 1 10)" == "MINGW32_NT" ]]; then
	#	# Do something under 32 bits Windows NT platform
	#elif [[ "$(expr substr $(uname -s) 1 10)" == "MINGW64_NT" ]]; then
	#	# Do something under 64 bits Windows NT platform
	#else
	fi
	echo "lsbCode="$lsbCode

	# in mac short directory calculation based on n'readlink' or 'realpath' will not work
	local scriptDirectory=`dirname "${sourcePath}"`
	local scriptFileName=`basename "${sourcePath}"`
	cd "${scriptDirectory}"
	local fileOrigin=`readlink "${scriptFileName}"` || :
	while [ ! -z "${fileOrigin}" ]
	do
		local scriptDirectory=`dirname "${fileOrigin}"`
		local scriptFileName=`basename "${fileOrigin}"`
		cd "${scriptDirectory}"
		local fileOrigin=`readlink "${scriptFileName}"`  || :
	done
	cd ..
	local repositoryRoot=`pwd`
	echo repositoryRoot=$repositoryRoot

	case "$LD_LIBRARY_PATH" in
		${repositoryRoot}/sys/$lsbCode/${configuration}/lib:* )
			echo "LD_LIBRARY_PATH for protobuf has been already set"
			;;
		* )
			export LD_LIBRARY_PATH=${repositoryRoot}/sys/$lsbCode/${configuration}/lib:$LD_LIBRARY_PATH
			;;
	esac

	if [ -z "$EMSDK_FOR_CPPUTILS_SET" ]
	then
	      source ${repositoryRoot}/contrib/emsdk/emsdk_env.sh
		  export EMSDK_FOR_CPPUTILS_SET=1
	else
	      echo "emscriptian already inited"
	fi

	cd ${currentDirectory}
}


makeMainJob
return 0
