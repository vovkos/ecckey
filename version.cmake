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

set(ECCKEY_VERSION_MAJOR     1)
set(ECCKEY_VERSION_MINOR     1)
set(ECCKEY_VERSION_REVISION  0)
set(ECCKEY_VERSION_TAG)

set(ECCKEY_VERSION_FULL "${ECCKEY_VERSION_MAJOR}.${ECCKEY_VERSION_MINOR}.${ECCKEY_VERSION_REVISION}")

if(NOT "${ECCKEY_VERSION_TAG}" STREQUAL "")
	set(ECCKEY_VERSION_TAG_SUFFIX  " ${ECCKEY_VERSION_TAG}")
	set(ECCKEY_VERSION_FILE_SUFFIX "${ECCKEY_VERSION_FULL}-${ECCKEY_VERSION_TAG}")
else()
	set(ECCKEY_VERSION_TAG_SUFFIX)
	set(ECCKEY_VERSION_FILE_SUFFIX "${ECCKEY_VERSION_FULL}")
endif()

string(TIMESTAMP ECCKEY_VERSION_YEAR  "%Y")
string(TIMESTAMP ECCKEY_VERSION_MONTH "%m")
string(TIMESTAMP ECCKEY_VERSION_DAY   "%d")

set(ECCKEY_VERSION_COMPANY "Tibbo Technology Inc")
set(ECCKEY_VERSION_YEARS   "2016-${ECCKEY_VERSION_YEAR}")

#...............................................................................
