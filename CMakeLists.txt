#...............................................................................
#
#  This file is part of the ECCKey utility.
#
#  ECCKey is distributed under the MIT license.
#  For details see accompanying license.txt file,
#  the public copy of which is also available at:
#  http://tibbo.com/downloads/archive/ecckey/license.txt
#
#...............................................................................

project (ecckey)

cmake_minimum_required (VERSION 3.3)

include (axl_cmake.cmake NO_POLICY_SCOPE)

#. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

set (ECCKEY_ROOT_DIR     ${CMAKE_CURRENT_LIST_DIR})
set (ECCKEY_BIN_BASE_DIR ${CMAKE_CURRENT_BINARY_DIR}/bin)
set (ECCKEY_DOC_DIR      ${CMAKE_CURRENT_BINARY_DIR}/doc)
set (ECCKEY_PACKAGE_DIR  ${CMAKE_CURRENT_BINARY_DIR}/package)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ECCKEY_BIN_BASE_DIR}/${CONFIGURATION_SCG})

set (ECCKEY_INSTALL_BIN_SUBDIR bin)

if (WIN32)
	set (ECCKEY_INSTALL_DOC_SUBDIR     doc)
	set (ECCKEY_INSTALL_LICENSE_SUBDIR license)
else ()
	set (ECCKEY_INSTALL_DOC_SUBDIR     share/${CMAKE_PROJECT_NAME}/doc)
	set (ECCKEY_INSTALL_LICENSE_SUBDIR share/${CMAKE_PROJECT_NAME}/license)
endif ()

#. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

include (version.cmake)

add_subdirectory (src)
add_subdirectory (doc)

#. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

install (
	DIRECTORY license/
	DESTINATION ${ECCKEY_INSTALL_LICENSE_SUBDIR}
	)

#...............................................................................

set (CPACK_PACKAGE_VERSION_MAJOR ${ECCKEY_VERSION_MAJOR})
set (CPACK_PACKAGE_VERSION_MINOR ${ECCKEY_VERSION_MINOR})
set (CPACK_PACKAGE_VERSION_PATCH ${ECCKEY_VERSION_REVISION})

if (WIN32)
	set (CPACK_SOURCE_GENERATOR 7Z)
else ()
	set (CPACK_SOURCE_GENERATOR TXZ)
endif ()

set (CPACK_SOURCE_IGNORE_FILES "/[.];[.]user$;/build/;/ci/;/paths.cmake$")

set (CPACK_SOURCE_PACKAGE_FILE_NAME ${CMAKE_PROJECT_NAME}-${ECCKEY_VERSION_FILE_SUFFIX}-src)

if (APPLE)
	set (CPACK_PACKAGE_FILE_NAME ${CMAKE_PROJECT_NAME}-${ECCKEY_VERSION_FILE_SUFFIX}-mac)
else ()
	string (TOLOWER ${CMAKE_SYSTEM_NAME} OS_NAME)
	set (CPACK_PACKAGE_FILE_NAME ${CMAKE_PROJECT_NAME}-${ECCKEY_VERSION_FILE_SUFFIX}-${OS_NAME}-${TARGET_CPU})
endif ()

include (CPack)

#...............................................................................
