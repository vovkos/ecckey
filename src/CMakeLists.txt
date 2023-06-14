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

#
# app folder
#

set(
	APP_H_LIST
	CmdLine.h
	KeyIniParser.h
	version.h.in
)

set(
	APP_CPP_LIST
	main.cpp
	CmdLine.cpp
	KeyIniParser.cpp
)

source_group(
	app
	FILES
	${APP_H_LIST}
	${APP_CPP_LIST}
)

#. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
#
# res folder
#

set(
	RES_RC_LIST
	res.rc
)

source_group(
	res
	FILES
	${RES_RC_LIST}
)

#. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
#
# gen folder
#

set(GEN_DIR ${CMAKE_CURRENT_BINARY_DIR}/gen)
file(MAKE_DIRECTORY ${GEN_DIR})

axl_push_and_set(CMAKE_CURRENT_BINARY_DIR ${GEN_DIR})

configure_file(
	version.h.in
	${GEN_DIR}/version.h
)

set(
	GEN_H_LIST
	${GEN_DIR}/version.h
)

axl_pop(CMAKE_CURRENT_BINARY_DIR)

source_group(
	gen
	FILES
	${GEN_H_LIST}
)

#. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
#
# pch folder
#

set(PCH_H   pch.h)

source_group(
	pch
	FILES
	${PCH_H}
	REGULAR_EXPRESSION cmake_pch
)

#...............................................................................
#
# ecckey elliptic curve product key tool
#

include_directories(
	${OPENSSL_INC_DIR}
	${AXL_INC_DIR}
	${GEN_DIR}
)

link_directories(
	${OPENSSL_LIB_DIR}
	${AXL_LIB_DIR}
)

add_executable(
	ecckey
	${PCH_H}
	${APP_H_LIST}
	${APP_CPP_LIST}
	${RES_RC_LIST}
	${GEN_H_LIST}
)

target_precompile_headers(
	ecckey
	PRIVATE
	${PCH_H}
)

set_target_properties(
	ecckey
	PROPERTIES
	FOLDER tools
)

target_link_libraries(
	ecckey
	axl_cry
	axl_ini
	axl_lex
	axl_io
	axl_mem_new
	axl_core
	${OPENSSL_CRYPTO_LIB_NAME}
)

if(WIN32)
	target_link_libraries(
		ecckey
		iphlpapi
	)
elseif(UNIX)
	target_link_libraries(
		ecckey
		dl
		pthread
	)

	if(NOT APPLE)
		target_link_libraries(
			ecckey
			rt
		)
	endif()
endif()

if(WIN32 AND OPENSSL_DLL_DIR AND OPENSSL_CRYPTO_DLL_NAME)
	set(_DEBUG_SUFFIX $<$<CONFIG:Debug>:d>)

	add_custom_command(
		TARGET ecckey
		POST_BUILD
		COMMAND
			echo Copying DLL files for ecckey...
		COMMAND
			${CMAKE_COMMAND} -E copy
			${OPENSSL_DLL_DIR}/${OPENSSL_CRYPTO_DLL_NAME}.dll
			${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CONFIGURATION}
		)
endif()

#. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

install(
	TARGETS ecckey
	DESTINATION ${ECCKEY_INSTALL_BIN_SUBDIR}
)

#...............................................................................
