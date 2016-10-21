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

cmake_minimum_required (VERSION 2.8)

include (axl_cmake.cmake NO_POLICY_SCOPE)

#. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

include (version.cmake)

add_subdirectory (src)

#...............................................................................
