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

set (
	AXL_PATH_LIST

	OPENSSL_INC_DIR
	OPENSSL_LIB_DIR
	AXL_CMAKE_DIR
	RAGEL_EXE
	)

set (
	AXL_IMPORT_LIST

	REQUIRED
		openssl
		axl
		ragel
	)

#...............................................................................
