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

CMake Configuration Step
========================

.. expand-macro:: cmake-configure ecckey_b

.. rubric:: Sample Linux output:

::

	AXL CMake:
	    Invoked from:        /home/vladimir/Projects/ecckey_b/CMakeLists.txt
	    dependencies.cmake:  /home/vladimir/Projects/ecckey_b/dependencies.cmake
	    settings.cmake:      /home/vladimir/Projects/settings.cmake
	    paths.cmake:         /home/vladimir/Projects/paths.cmake
	    Target CPU:          amd64
	    Build configuration: Debug
	C/C++:
	    C Compiler:          /usr/bin/cc
	    C flags (Debug):     -m64 -mcx16 -fPIC -fvisibility=hidden -Wno-multichar -g
	    C flags (Release):   -m64 -mcx16 -fPIC -fvisibility=hidden -Wno-multichar -O3 -DNDEBUG
	    C++ Compiler:        /usr/bin/c++
	    C++ flags (Debug):   -m64 -mcx16 -fPIC -fvisibility=hidden -Wno-multichar -g
	    C++ flags (Release): -m64 -mcx16 -fPIC -fvisibility=hidden -Wno-multichar -O3 -DNDEBUG
	Dependency path definitions:
	    AXL_CMAKE_DIR:       /home/vladimir/Projects/ecckey_b/axl/cmake;/home/vladimir/Projects/ecckey_b/axl/build/make-amd64/cmake
	OpenSSL paths:
	    Includes:            /usr/include
	    Libraries:           /usr/lib64
	AXL paths:
	    CMake files:         /home/vladimir/Projects/ecckey_b/axl/cmake;/home/vladimir/Projects/ecckey_b/axl/build/make-amd64/cmake
	    Includes:            /home/vladimir/Projects/ecckey_b/axl/include
	    Libraries:           /home/vladimir/Projects/ecckey_b/axl/build/make-amd64/lib/Debug
	Sphinx found at:         /usr/bin/sphinx-build
	Pdflatex found at:       /usr/bin/pdflatex
	Configuring done

.. rubric:: Sample Windows output:

::

	AXL CMake:
	    Invoked from:        /home/vladimir/Projects/ecckey_b/CMakeLists.txt
	    dependencies.cmake:  /home/vladimir/Projects/ecckey_b/dependencies.cmake
	    settings.cmake:      /home/vladimir/Projects/settings.cmake
	    paths.cmake:         /home/vladimir/Projects/paths.cmake
	    Target CPU:          amd64
	    Build configuration: Debug
	C/C++:
	    C Compiler:          /usr/bin/cc
	    C flags (Debug):     -m64 -mcx16 -fPIC -fvisibility=hidden -Wno-multichar -g
	    C flags (Release):   -m64 -mcx16 -fPIC -fvisibility=hidden -Wno-multichar -O3 -DNDEBUG
	    C++ Compiler:        /usr/bin/c++
	    C++ flags (Debug):   -m64 -mcx16 -fPIC -fvisibility=hidden -Wno-multichar -g
	    C++ flags (Release): -m64 -mcx16 -fPIC -fvisibility=hidden -Wno-multichar -O3 -DNDEBUG
	Dependency path definitions:
	    AXL_CMAKE_DIR:       /home/vladimir/Projects/ecckey_b/axl/cmake;/home/vladimir/Projects/ecckey_b/axl/build/make-amd64/cmake
	OpenSSL paths:
	    Includes:            /usr/include
	    Libraries:           /usr/lib64
	AXL paths:
	    CMake files:         /home/vladimir/Projects/ecckey_b/axl/cmake;/home/vladimir/Projects/ecckey_b/axl/build/make-amd64/cmake
	    Includes:            /home/vladimir/Projects/ecckey_b/axl/include
	    Libraries:           /home/vladimir/Projects/ecckey_b/axl/build/make-amd64/lib/Debug
	Sphinx found at:         /usr/bin/sphinx-build
	Pdflatex found at:       /usr/bin/pdflatex
	Configuring done

.. expand-macro:: cmake-post-configure
