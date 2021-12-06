#
# file:			windows.common.Makefile
# created on:	2020 Dec 14
# created by:	
#
# This file can be only as include
#

CC						= cl 
CPPC           			= cl -Zc:__cplusplus

!IFNDEF PDB_FILE_PATH
PDB_FILE_PATH			= $(TargetDirectory)\$(TargetName).pdb
!ENDIF
CFLAGS					= $(CFLAGS) /bigobj /nologo
!IF "$(Configuration)" == "Debug"
CFLAGS					= $(CFLAGS) /MDd /Fd"$(PDB_FILE_PATH)"
!ELSE
CFLAGS					= $(CFLAGS) /MD
!ENDIF

TargetFileName			= $(TargetName).$(TargetExtension)
TargetDirectory			= $(RepoRootDir)\sys\win_$(Platform)\$(Configuration)\lib
ObjectsDirBase			= $(MakeFileDir)\sys\win_$(Platform)\$(Configuration)\.objects
ObjectsDir				= $(ObjectsDirBase)\$(TargetName)

CXXFLAGS				= $(CXXFLAGS) $(CFLAGS)
CXXFLAGS				= $(CXXFLAGS) /JMC /permissive- /GS /W3 /Zc:wchar_t  /Zi /Gm- /Od /sdl- 
CXXFLAGS				= $(CXXFLAGS) /Fd"$(PDB_FILE_PATH)"
CXXFLAGS				= $(CXXFLAGS) /Zc:inline /fp:precise /errorReport:prompt /WX- /Zc:forScope /RTC1 /Gd 
CXXFLAGS				= $(CXXFLAGS) /FC /EHsc /diagnostics:column

.cpp.obj:
	 @$(CPPC) /c $(CXXFLAGS) /Fo$(ObjectsDir)\$(@D)\ $<

.cxx.obj:
	 @$(CPPC) /c $(CXXFLAGS) /Fo$(ObjectsDir)\$(@D)\ $<

.cc.obj:
	@$(CPPC) /c $(CXXFLAGS) /Fo$(ObjectsDir)\$(@D)\ $*.cc

.c.obj:
	@$(CC) /c   $(CFLAGS)   /Fo$(ObjectsDir)\$(@D)\ $*.c


__preparationForSetObjects:
	@echo -=-=-=-=-=-=-=-==-=-=-=-=-=-==-=-=-=-=-=-=-= __preparationForSetObjects
	@set __targetToCall=__buildRaw

__preparationForBuildRaw:
	@echo "MakeFileDir"=$(MakeFileDir)
	@cd $(SrcBaseDir)
	@if not exist $(TargetDirectory) mkdir $(TargetDirectory)


__buildRaw: __preparationForBuildRaw $(Objects)
	@cd $(ObjectsDir)
	@$(LINKER) $(Objects) /OUT:$(TargetDirectory)\$(TargetName).$(TargetExtension) /MACHINE:$(Platform) /NOLOGO


clean:
	@if exist "$(ObjectsDir)" rmdir /q /s "$(ObjectsDir)"
	@if exist "$(TargetDirectory)\$(TargetName).*" del /s /q "$(TargetDirectory)\$(TargetName).*"
	@echo "clean done!"

# if 'nr-' specified before the name of directory, then this directory
# scanned for sources not recursively
__setObjects:
	@<<windows_nmake_makefile_setobjects.bat
		@echo off
		setlocal EnableDelayedExpansion enableextensions

		set scriptName=%0
		set scriptDirectory=%~dp0
		set currentDirectory=%cd%

		set ObjectsVar=$(Objects)

		for %%i in ($(DirectoriesToCompile)) do (
			set directoryName=%%i
			set is_recursive_string=!directoryName:~0,3!
			if "!is_recursive_string!" == "nr-" (
				set is_recursive=0
				set directoryName=!directoryName:~3!
			) else (
				set is_recursive=1
			)
			call :iterate_over_files_in_dir !directoryName!
		)

		rem settig environment for target platform if necessary
		if /i "!VSCMD_ARG_TGT_ARCH!"=="$(Platform)" (
			echo "vcvarsall already set to !Platform!"
		) else (
			echo "calling vcvarsall in the !scriptDirectory!!scriptName!"
			if /i "!Platform!"=="x86" (
				set PlatformTarget=x86
			) else (
				set PlatformTarget=x86_$(Platform)
			)
			cd /D "%VCINSTALLDIR%Auxiliary\Build"
			call vcvarsall.bat !PlatformTarget!
			cd /D "%currentDirectory%"
		)


		$(MAKE) /f $(MakeFileDir)\$(MakeFileName) %__targetToCall% ^
				/e Objects="!ObjectsVar!"  ^
				/e Platform=$(Platform)     ^
				/e MakeFileDir=$(MakeFileDir) 

		exit /b !ERRORLEVEL!

		:trim_string
			set %2=%1
			exit /b 0

		:iterate_over_files_in_dir

			cd $(SrcBaseDir)
			set TARGET_PATH_FOR_SOURCE=%cd%\
			cd $(SrcBaseDir)\%1

			if "!is_recursive!" == "0" (
				echo ++++++++++++++++++++++++++++++++++ not recursive dir "%1"
				if not exist "$(ObjectsDir)\%1" mkdir "$(ObjectsDir)\%1"
				for %%I in ("*.cpp" "*.c" "*.cc" "*.cxx") do (
					set relFilePath=%1\%%~nI.obj
					set shouldExlude=0
					for %%e in ($(excludedObjects)) do (
						if "!relFilePath!" == "%%e" (
							echo %%e should be exluded
							set shouldExlude=1
							rem goto :eofloop
						)
					)
					:eofloop
					if "!shouldExlude!" == "0" (
						set ObjectsVar=!ObjectsVar! !relFilePath!
						echo !relFilePath!
					)
					rem iteration of loop done
				)
			) else (
				echo ++++++++++++++++++++++++++++++++++ recursive     dir "%1"
				for /r %%I in ("*.cpp" "*.c" "*.cc" "*.cxx") do (
					set "dirPath=%%~dpI"
					set relDirPath=!dirPath:%TARGET_PATH_FOR_SOURCE%=!
					if not exist "$(ObjectsDir)\!relDirPath!" mkdir "$(ObjectsDir)\!relDirPath!"
					
					set "filePath=%%~dpnI.obj"
					set relFilePath=!filePath:%TARGET_PATH_FOR_SOURCE%=!
					set shouldExlude=0
					for %%e in ($(excludedObjects)) do (
						if "!relFilePath!" == "%%e" (
							echo %%e should be exluded
							set shouldExlude=1
							rem goto :eofloop
						)
					)
					:eofloop
					if "!shouldExlude!" == "0" (
						set ObjectsVar=!ObjectsVar! !relFilePath!
						echo !relFilePath!
					)
					rem iteration of loop done
				)
			)
			
			cd !currentDirectory!
			exit /b 0
			
		endlocal
<<NOKEEP
