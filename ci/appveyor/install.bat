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

:: OpenSSL

set OPENSSL_DIR_CMAKE=%OPENSSL_DIR:\=/%

echo set (OPENSSL_INC_DIR %OPENSSL_DIR_CMAKE%/include) >> paths.cmake
echo set (OPENSSL_LIB_DIR %OPENSSL_DIR_CMAKE%/lib) >> paths.cmake
echo set (OPENSSL_DLL_DIR %OPENSSL_DIR_CMAKE%/bin) >> paths.cmake
echo set (OPENSSL_CRYPTO_LIB_NAME libeay32) >> paths.cmake
echo set (OPENSSL_CRYPTO_DLL_NAME libeay32) >> paths.cmake
echo set (OPENSSL_SSL_LIB_NAME ssleay32) >> paths.cmake
echo set (OPENSSL_SSL_DLL_NAME ssleay32) >> paths.cmake

:: . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

:: Get rid of Xamarin annoying build warnings

del "c:\Program Files (x86)\MSBuild\14.0\Microsoft.Common.targets\ImportAfter\Xamarin.Common.targets"
del "c:\Program Files (x86)\MSBuild\4.0\Microsoft.Common.targets\ImportAfter\Xamarin.Common.targets"
