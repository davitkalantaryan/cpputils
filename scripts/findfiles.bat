::
:: file:			findfl.bat
:: created on:		2021 Mar 20
:: created by:		
:: purpose:			...
::

@echo off
setlocal EnableDelayedExpansion


set currentDirectory=%cd%

 rem todo: make proper evaluation of search pattern construction

set "patternToSearch=%2"

for /f "tokens=*" %%a in ('echo %2^| findstr /i "\."') do ( set hasPoint=%%a )

if not "%hasPoint%" == "" (
	set "patternToSearch=\%2"
)

rem echo ++++ patternToSearch = !patternToSearch!
rem exit /b 0

cd /D %1
dir /s /b | findstr /i "!patternToSearch!"
cd /D %currentDirectory%

exit /b 0

endlocal


rem @echo off
rem setlocal EnableDelayedExpansion
rem 
rem 
rem set currentDirectory=%cd%
rem set scriptDirectory=%~dp0
rem 
rem  rem todo: make proper evaluation of search pattern construction
rem 
rem set "patternToSearch=%2"
rem 
rem for /f "tokens=*" %%a in ('echo %2^| findstr /i "\."') do ( set hasPoint=%%a )
rem 
rem if not "%hasPoint%" == "" (
rem 	set "patternToSearch=\%2"
rem )
rem 
rem rem echo ++++ patternToSearch = !patternToSearch!
rem rem exit /b 0
rem 
rem cd /D %1
rem 
rem set "var="
rem 
rem rem dir /s /b | findstr /i "!patternToSearch!"
rem for /F "tokens=* USEBACKQ" %%F IN (`call !scriptDirectory!.raw\_windows_print_directory_content.bat !patternToSearch!`) do (
rem 	set var=!var! "%%F"
rem )
rem 
rem echo !var!
rem 
rem cd /D %currentDirectory%
rem 
rem exit /b 0
rem 
rem :printDirectoryContent
rem 	dir /s /b | findstr /i "!patternToSearch!"
rem 	exit /b 0
rem 
rem endlocal
