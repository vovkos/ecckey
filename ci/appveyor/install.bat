::..............................................................................
::
::  This file is part of the ECCKey utility.
::
::  ECCKey is distributed under the MIT license.
::  For details see accompanying license.txt file,
::  the public copy of which is also available at:
::  http://tibbo.com/downloads/archive/ecckey/license.txt
::
::..............................................................................

@echo off

set DOWNLOAD_DIR=c:\downloads
set DOWNLOAD_DIR_CMAKE=%DOWNLOAD_DIR:\=/%
mkdir %DOWNLOAD_DIR%

:: . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

:: Ragel

mkdir %DOWNLOAD_DIR%\ragel
appveyor DownloadFile %RAGEL_DOWNLOAD_URL% -FileName %DOWNLOAD_DIR%\ragel\ragel.7z
7z e -y %DOWNLOAD_DIR%\ragel\ragel.7z -o%DOWNLOAD_DIR%\ragel

echo set (RAGEL_EXE %DOWNLOAD_DIR_CMAKE%/ragel/ragel.exe) >> paths.cmake

:: . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

:: OpenSSL

set OPENSSL_DIR_CMAKE=%OPENSSL_DIR:\=/%

echo set (OPENSSL_INC_DIR %OPENSSL_DIR_CMAKE%/include) >> paths.cmake
echo set (OPENSSL_LIB_DIR %OPENSSL_DIR_CMAKE%/lib) >> paths.cmake

:: . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

:: Get rid of Xamarin annoying build warnings

del "c:\Program Files (x86)\MSBuild\14.0\Microsoft.Common.targets\ImportAfter\Xamarin.Common.targets"
del "c:\Program Files (x86)\MSBuild\4.0\Microsoft.Common.targets\ImportAfter\Xamarin.Common.targets"
