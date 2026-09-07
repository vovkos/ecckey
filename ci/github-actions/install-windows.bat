::..............................................................................
::
::  This file is part of the AXL library.
::
::  AXL is distributed under the MIT license.
::  For details see accompanying license.txt file,
::  the public copy of which is also available at:
::  http://tibbo.com/downloads/archive/axl/license.txt
::
::..............................................................................

@echo off

set DOWNLOAD_DIR=c:\downloads
set DOWNLOAD_DIR_CMAKE=%DOWNLOAD_DIR:\=/%

:: . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

:: wget

echo Installing wget...

choco install wget --no-progress || exit

:: . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

:: Ragel

echo Downloading %RAGEL_DOWNLOAD_URL%...

mkdir %DOWNLOAD_DIR%
wget -nv %RAGEL_DOWNLOAD_URL% -O %DOWNLOAD_DIR%\ragel.exe || exit

echo set(RAGEL_EXE %DOWNLOAD_DIR_CMAKE%/ragel.exe) >> paths.cmake

:: . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

:: OpenSSL

:: choco doesn't ship arm64 builds only

if /i not "%TARGET_CPU%" == "arm64" goto :openssl_install

:: on arm64 we use preinstalled OpenSSL 3 (libs are at lib/VC/<arch>/<crt>)

set OPENSSL_ROOT_DIR=C:/Program Files/OpenSSL

if /i "%CONFIGURATION%" == "Debug" (
	set OPENSSL_LIB_SUBDIR=lib/VC/arm64/MDd
) else (
	set OPENSSL_LIB_SUBDIR=lib/VC/arm64/MD
)

goto :openssl_finalize

:openssl_install

echo Installing OpenSSL %OPENSSL_VERSION%...

choco install openssl --version=%OPENSSL_VERSION% --no-progress %CHOCO_PLATFORM% || exit

set OPENSSL_ROOT_DIR=C:/Program Files%PROGRAM_FILES_DIR_SUFFIX%/OpenSSL%OPENSSL_DIR_SUFFIX%
set OPENSSL_LIB_SUBDIR=lib

:openssl_finalize

echo set(OPENSSL_INC_DIR "%OPENSSL_ROOT_DIR%/include") >> paths.cmake
echo set(OPENSSL_LIB_DIR "%OPENSSL_ROOT_DIR%/%OPENSSL_LIB_SUBDIR%") >> paths.cmake
echo set(OPENSSL_DLL_DIR "%OPENSSL_ROOT_DIR%/bin") >> paths.cmake
echo set(OPENSSL_CRYPTO_LIB_NAME libcrypto) >> paths.cmake
echo set(OPENSSL_CRYPTO_DLL_NAME libcrypto%OPENSSL_DLL_SUFFIX%) >> paths.cmake
echo set(OPENSSL_SSL_LIB_NAME libssl) >> paths.cmake
echo set(OPENSSL_SSL_DLL_NAME libssl%OPENSSL_DLL_SUFFIX%) >> paths.cmake

:: . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
