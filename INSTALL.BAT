echo off

rem DOS batch file to install the INMOS C TOOLSET onto a PC
rem Copyright (C) INMOS Ltd, 1990, 1991, 1992

echo **********************************************
echo *     INMOS C TOOLSET D7314 INSTALLATION     *
echo *  Copyright (C) INMOS Ltd 1990, 1991, 1992  *
echo **********************************************

rem %1 = source, %2 = destination

IF "%1" == "" GOTO ERROR1
IF "%2" == "" GOTO ERROR2
IF NOT EXIST %1:\yesorno.exe GOTO ERROR3

ECHO Installing the toolset in the directory %2:\D7314a from drive %1:
%1:yesorno Do you want to continue with the installation ?
IF ERRORLEVEL 1 GOTO END

mkdir %2:\d7314a
%2:
cd \d7314a
copy %1:\install2.bat
install2 %1

:ERROR3
ECHO You have given an invalid drive letter for the installation disks.

:ERROR1
:ERROR2
ECHO You must specify the drive letters for the installation.
ECHO First drive letter must be the drive the in which installation disks are 
ECHO inserted and the second must be the drive on which the toolset is to be 
ECHO installed.

:END
ECHO ON
