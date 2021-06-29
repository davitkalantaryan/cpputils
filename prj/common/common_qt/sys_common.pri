# File sys_common.pri
# File created : 12 Feb 2017
# Created by : Davit Kalantaryan (davit.kalantaryan@desy.de)
# This file can be used to produce Makefile for daqadcreceiver application
# for PITZ
#

#QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter
#QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-variable
#QMAKE_CXXFLAGS_WARN_ON += -Wno-sign-compare
#QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-function
#QMAKE_CXXFLAGS_WARN_ON -= -Wunused-function

STATIC_LIB_EXTENSION	= a
LIB_PREFIX	= lib
TARGET_PATH_EXTRA	=

contains( TEMPLATE, lib ) {
    TARGET_PATH=lib
    #message("Shared library creation")
} else {
    TARGET_PATH=bin
    #message("Binary file creation")
}


PRJ_PWD_TMP = $$PRJ_PWD
isEmpty(PRJ_PWD_TMP) {
    PRJ_PWD = $${PWD}/../../..
}


win32 {
	STATIC_LIB_EXTENSION = lib
	LIB_PREFIX =
    contains(QMAKE_TARGET.arch, x86_64) {
        ## Windows x64 (64bit) specific build here
        CODENAME = win_x64
        SYSTEM_PATH = sys/win_x64

    } else {
        ## Windows x86 (32bit) specific build here
        CODENAME = win_x86
        SYSTEM_PATH = sys/win_x86

    }

} else:mac {
    CODENAME = mac
    SYSTEM_PATH = sys/mac
} else:android {
    CODENAME = android
    SYSTEM_PATH = sys/android

    contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
	#ANDROID_EXTRA_LIBS += $$PWD/../platform/android/openssl/armeabi-v7a/libcrypto.so
	#ANDROID_EXTRA_LIBS += $$PWD/../platform/android/openssl/armeabi-v7a/libssl.so
	CODENAME = android_armeabi-v7a
	SYSTEM_PATH = sys/android_armeabi-v7a
    }

    # aarch64
    #contains(ANDROID_TARGET_ARCH,aarch64) {
	##ANDROID_EXTRA_LIBS += $$PWD/../platform/android/openssl/armeabi-v7a/libcrypto.so
	##ANDROID_EXTRA_LIBS += $$PWD/../platform/android/openssl/armeabi-v7a/libssl.so
	#CODENAME = android_aarch64
	#SYSTEM_PATH = sys/android_aarch64
    #}

    contains(ANDROID_TARGET_ARCH,arm64-v8a) {
	##ANDROID_EXTRA_LIBS += $$PWD/../platform/android/openssl/armeabi-v7a/libcrypto.so
	##ANDROID_EXTRA_LIBS += $$PWD/../platform/android/openssl/armeabi-v7a/libssl.so
	CODENAME = android_arm64-v8a
	SYSTEM_PATH = sys/android_arm64-v8a
    }

    contains(ANDROID_TARGET_ARCH,x86) {
	#ANDROID_EXTRA_LIBS += $$PWD/../platform/android/openssl/x86/libcrypto.so
	#ANDROID_EXTRA_LIBS += $$PWD/../platform/android/openssl/x86/libssl.so
	CODENAME = android_x86
	SYSTEM_PATH = sys/android_x86
    }


} else:linux {
    DEFINES += LINUX
    CODENAME = $$system(lsb_release -c | cut -f 2)
    SYSTEM_PATH = sys/$$CODENAME
} else:ios {
    CODENAME = ios
    SYSTEM_PATH = sys/$$CODENAME
} else:wasm {
	STATIC_LIB_EXTENSION	= ba
    CODENAME = wasm
    SYSTEM_PATH = sys/$$CODENAME
	TARGET_PATH_EXTRA = /$${TARGET}
} else {
    CODENAME = unknownCodeName
    SYSTEM_PATH = sys/$$CODENAME
}

CONFIGURATION=Profile
nameExtension=
Release|release:CONFIGURATION=Release
Debug|debug{
	nameExtension=d
	CONFIGURATION=Debug
}

message("!!! sys_common.pri: SYSTEM_PATH=$${PRJ_PWD}/$${SYSTEM_PATH}")

# Debug:DESTDIR = debug1
SYSTEM_PATH=$$SYSTEM_PATH/$$CONFIGURATION
MAKEFILE = Makefile.$${TARGET}.$${CODENAME}
DESTDIR = $${PRJ_PWD}/$${SYSTEM_PATH}/$${TARGET_PATH}$${TARGET_PATH_EXTRA}
OBJECTS_DIR = $${PRJ_PWD}/$${SYSTEM_PATH}/.objects/$${TARGET}
MOC_DIR = $${PWD}/$$CODENAME/$$CONFIGURATION
UI_DIR  = $${PWD}/$$CODENAME/$$CONFIGURATION


#CONFIG += debug
#CONFIG += c++11
#QMAKE_CXXFLAGS += -std=c++0x
# greaterThan(QT_MAJOR_VERSION, 4):QT += widgets
#QT -= core
#QT -= gui
