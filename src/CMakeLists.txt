# This file is part of AXL (R) Library
# Tibbo Technology Inc (C) 2004-2015. All rights reserved
# Author: Vladimir Gladkov

#..............................................................................
#
# app folder
#

set (
	APP_H_LIST
	CmdLine.h
	KeyIniParser.h
	version.h.in
	)

set (
	APP_CPP_LIST
	main.cpp
	CmdLine.cpp
	KeyIniParser.cpp
	)

source_group (
	app
	FILES
	${APP_H_LIST}
	${APP_CPP_LIST}
	)

# . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
#
# res folder
#

set (
	RES_RC_LIST
	res.rc
	)

source_group (
	res
	FILES
	${RES_RC_LIST}
	)

# . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
#
# gen folder
#

set (GEN_DIR ${CMAKE_CURRENT_BINARY_DIR}/gen)
file (MAKE_DIRECTORY ${GEN_DIR})

axl_push_and_set (CMAKE_CURRENT_BINARY_DIR ${GEN_DIR})

configure_file (
	version.h.in
	${GEN_DIR}/version.h
	)

set (
	GEN_H_LIST
	${GEN_DIR}/version.h
	)

axl_pop (CMAKE_CURRENT_BINARY_DIR)

source_group (
	gen
	FILES
	${GEN_H_LIST}
	)

# . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
#
# pch folder
#

set (PCH_H   pch.h)
set (PCH_CPP pch.cpp)

source_group (
	pch
	FILES
	${PCH_H}
	${PCH_CPP}
	)

#..............................................................................
#
# ecckey elliptic curve product key tool
#

include_directories (
	${OPENSSL_INC_DIR}
	${AXL_INC_DIR}
	${GEN_DIR}
	)

link_directories (
	${OPENSSL_LIB_DIR}
	${AXL_LIB_DIR}
	)

add_executable (
	ecckey
	${PCH_H}
	${PCH_CPP}
	${APP_H_LIST}
	${APP_CPP_LIST}
	${RES_RC_LIST}
	${GEN_H_LIST}
	)

axl_set_pch (
	ecckey
	${PCH_H}
	${PCH_CPP}
	)

set_target_properties (
	ecckey
	PROPERTIES
	FOLDER tools
	)
	
target_link_libraries (
	ecckey
	axl_cry
	axl_ini
	axl_lex
	axl_io
	axl_core
	)

if (WIN32)
	target_link_libraries (
		ecckey
		libeay32MT
		)
elseif (UNIX)
	target_link_libraries (
		ecckey
		crypto
		dl
		pthread
		)
		
	if (NOT APPLE)
		target_link_libraries (
			ecckey
			rt
			)
	endif ()
endif ()

#..............................................................................