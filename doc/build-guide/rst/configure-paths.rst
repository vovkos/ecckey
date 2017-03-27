.. .............................................................................
..
..  This file is part of the ECCKey utility.
..
..  ECCKey is distributed under the MIT license.
..  For details see accompanying license.txt file,
..  the public copy of which is also available at:
..  http://tibbo.com/downloads/archive/ecckey/license.txt
..
.. .............................................................................

paths.cmake
===========

.. expand-macro:: paths-cmake ECCKey

.. code-block:: bash

	OPENSSL_INC_DIR     # path to OpenSSL include directory
	OPENSSL_LIB_DIR     # path to OpenSSL library directory
	SPHINX_BUILD_EXE    # (optional) path to Sphinx compiler executable sphinx-build
	PDFLATEX_EXE        # (optional) path to Latex-to-PDF compiler

.. expand-macro:: dependencies-cmake AXL

On Windows you will need to specify paths to OpenSSL librariy -- they are unlikely to be found automatically.

.. rubric:: Sample paths.cmake on Windows:

.. code-block:: cmake

	set (OPENSSL_VERSION 1.0.1h)

	if ("${TARGET_CPU}" STREQUAL "amd64")
		set (OPENSSL_INC_DIR    c:/Develop/openssl/openssl-win64-${OPENSSL_VERSION}/include)
		set (OPENSSL_LIB_DIR    c:/Develop/openssl/openssl-win64-${OPENSSL_VERSION}/lib/vc/static)
	else ()
		set (OPENSSL_INC_DIR    c:/Develop/openssl/openssl-win32-${OPENSSL_VERSION}/include)
		set (OPENSSL_LIB_DIR    c:/Develop/openssl/openssl-win32-${OPENSSL_VERSION}/lib/vc/static)
	endif()

	set (SPHINX_BUILD_EXE c:/Develop/ActivePython/Scripts/sphinx-build.exe)
	set (PDFLATEX_EXE     "c:/Program Files (x86)/MiKTeX 2.9/miktex/bin/pdflatex.exe")
