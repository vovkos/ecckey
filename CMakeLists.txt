# This file is part of Doxyrest project
# Tibbo Technology Inc (C) 2004-2016. All rights reserved
# Author: Vladimir Gladkov

#...............................................................................

project (ecckey)

cmake_minimum_required (VERSION 2.8)

include (axl_cmake.cmake NO_POLICY_SCOPE)

#. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

include (version.cmake)

add_subdirectory (src)

#...............................................................................
