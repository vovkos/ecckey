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

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ECCKEY_BIN_BASE_DIR}/${CONFIGURATION_SUFFIX_0})

#. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

include (version.cmake)

add_subdirectory (src)

#...............................................................................
