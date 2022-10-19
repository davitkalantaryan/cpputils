#
# name:			flags_common.pri
# path:			${repositoryRoot}/prj/common/common_qt/flags_common.pri
# created on:		2022 Oct 19
# created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
# usage:		Use this qt include file to calculate some platform specific stuff
#


message("!!! $${PWD}/flags_common.pri")

isEmpty( cpputilsRepoRoot ){
        cpputilsRepoRoot=$${PWD}/../../..
}

INCLUDEPATH += $${cpputilsRepoRoot}/include


macx {
        message ("!!!!!!!!!! mac")
	QMAKE_CXXFLAGS += -Werror
	#LIBS += -framework SystemConfiguration -framework AppKit
} else:win32 {
	QMAKE_CXXFLAGS += /Wall /WX
	contains(QMAKE_TARGET.arch, x86_64) {
	        message ("!!!!!!!!!! windows 64")
	} else {
	        message ("!!!!!!!!!! windows 32")
	}
	CONFIG(debug, debug|release) {
	        #LIBS += -lcomsuppwd
	} else:CONFIG(release, debug|release) {
	        #LIBS += -lcomsuppw
	}

} else:linux {
        message ("!!!!!!!!!! linux")
	QMAKE_CXXFLAGS += -Wall
	QMAKE_CXXFLAGS += -Werror
	QMAKE_CXXFLAGS += -Wno-attributes
} else:android {
        message ("!!!!!!!!!! android")
	QMAKE_CXXFLAGS += -Wall
	QMAKE_CXXFLAGS += -Werror
} else:ios {
        message ("!!!!!!!!!! ios")
	QMAKE_CXXFLAGS += -Werror
} else {
        message ("!!!!!!!!!! wasm")
	QT -= sql
	#DEFINES += USE_DLOPEN_FROM_WASM
	QMAKE_CXXFLAGS += -Wall
	QMAKE_CXXFLAGS += -Werror
	QMAKE_CXXFLAGS += -fexceptions
	#QMAKE_CXXFLAGS += -s DISABLE_EXCEPTION_CATCHING=0 -s ASYNCIFY -O3
	QMAKE_CXXFLAGS += -s DISABLE_EXCEPTION_CATCHING=0 -O3 $$(EXTRA_WASM_FLAGS)
}
