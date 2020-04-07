//..............................................................................
//
//  This file is part of the ECCKey utility.
//
//  ECCKey is distributed under the MIT license.
//  For details see accompanying license.txt file,
//  the public copy of which is also available at:
//  http://tibbo.com/downloads/archive/ecckey/license.txt
//
//..............................................................................

#pragma once

#include "axl_sl_CmdLineParser.h"
#include "axl_ini_Parser.h"
#include "axl_cry_EcKey.h"
#include "axl_io_FilePathUtils.h"
#include "axl_io_NetworkAdapter.h"
#include "axl_sys_Time.h"
#include "axl_enc_Base32Encoding.h"

using namespace axl;

#if (_AXL_OS_WIN)
#	pragma comment(lib, "ws2_32.lib")
#	pragma comment(lib, "crypt32.lib")
#endif
