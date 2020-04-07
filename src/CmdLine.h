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

//..............................................................................

enum CmdLineFlag
{
	CmdLineFlag_Help             = 0x0001,
	CmdLineFlag_Version          = 0x0002,
	CmdLineFlag_NewLicenseFile   = 0x0004,
	CmdLineFlag_NewLicenseKey    = 0x0008,
	CmdLineFlag_NewProductKey    = 0x0010,
	CmdLineFlag_VerifyProductKey = 0x0020,
	CmdLineFlag_ListCurves       = 0x0040,
	CmdLineFlag_Minimalistic     = 0x0080,
	CmdLineFlag_GetMacTag        = 0x0100,
};

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

struct CmdLine
{
	uint_t m_flags;
	size_t m_hyphenDistance;
	uint_t m_curveId;
	uint_t m_timeLimit; // in days
	size_t m_randomLength;
	size_t m_keyCount;

	sl::String m_licenseFileName;
	sl::String m_license;
	sl::String m_licensePublicKey;
	sl::String m_licensePrivateKey;
	sl::String m_userName;
	sl::String m_productKey;
	sl::Array<char> m_macTag;

	CmdLine();
};

//..............................................................................

enum CmdLineSwitchKind
{
	CmdLineSwitchKind_Undefined = 0,
	CmdLineSwitchKind_Help,
	CmdLineSwitchKind_Version,
	CmdLineSwitchKind_NewLicenseFile,
	CmdLineSwitchKind_NewLicenseKey,
	CmdLineSwitchKind_NewProductKey,
	CmdLineSwitchKind_VerifyProductKey,
	CmdLineSwitchKind_ListCurves,
	CmdLineSwitchKind_Minimalistic,
	CmdLineSwitchKind_LicenseFileName,
	CmdLineSwitchKind_License,
	CmdLineSwitchKind_LicensePublicKey,
	CmdLineSwitchKind_LicensePrivateKey,
	CmdLineSwitchKind_LicenseCurve,
	CmdLineSwitchKind_HyphenDistance,
	CmdLineSwitchKind_UserName,
	CmdLineSwitchKind_ProductKey,
	CmdLineSwitchKind_TimeLimit,
	CmdLineSwitchKind_AddMacTag,
	CmdLineSwitchKind_GetMacTag,
	CmdLineSwitchKind_Count,
};

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

AXL_SL_BEGIN_CMD_LINE_SWITCH_TABLE(CmdLineSwitchTable, CmdLineSwitchKind)
	AXL_SL_CMD_LINE_SWITCH_2(
		CmdLineSwitchKind_Help,
		"h", "help", NULL,
		"Display this help"
		)
	AXL_SL_CMD_LINE_SWITCH_2(
		CmdLineSwitchKind_Version,
		"v", "version", NULL,
		"Display version of ecckey"
		)
	AXL_SL_CMD_LINE_SWITCH_2(
		CmdLineSwitchKind_NewLicenseFile,
		"g", "new-license-file", NULL,
		"Generate a new license file (-f to specify name)"
		)
	AXL_SL_CMD_LINE_SWITCH(
		CmdLineSwitchKind_NewLicenseKey,
		"new-license-key", NULL,
		"Generate a new license key"
		)
	AXL_SL_CMD_LINE_SWITCH(
		CmdLineSwitchKind_NewProductKey,
		"new-product-key", NULL,
		"Generate a new product key"
		)
	AXL_SL_CMD_LINE_SWITCH_3(
		CmdLineSwitchKind_VerifyProductKey,
		"y", "verify", "check", NULL,
		"Verify a product key"
		)
	AXL_SL_CMD_LINE_SWITCH(
		CmdLineSwitchKind_ListCurves,
		"list-curves", NULL,
		"Display the list of available ECC curves"
		)
	AXL_SL_CMD_LINE_SWITCH_2(
		CmdLineSwitchKind_Minimalistic,
		"min", "minimalistic", NULL,
		"Omit verbose data where possible"
		)
	AXL_SL_CMD_LINE_SWITCH_2(
		CmdLineSwitchKind_LicenseFileName,
		"f", "license-file", "<file>",
		"Specify license file (default: ecckey.conf)"
		)
	AXL_SL_CMD_LINE_SWITCH_2(
		CmdLineSwitchKind_License,
		"l", "license", "<license>",
		"Specify license (default: the 1st license in file)"
		)
	AXL_SL_CMD_LINE_SWITCH(
		CmdLineSwitchKind_LicensePublicKey,
		"public-key", "<key>",
		"Specify license public key (for verification)"
		)
	AXL_SL_CMD_LINE_SWITCH(
		CmdLineSwitchKind_LicensePrivateKey,
		"private-key", "<key>",
		"Specify license private key"
		)
	AXL_SL_CMD_LINE_SWITCH_2(
		CmdLineSwitchKind_LicenseCurve,
		"c", "curve", "<curve>",
		"Specify ECC curve (default: secp112r1)"
		)
	AXL_SL_CMD_LINE_SWITCH(
		CmdLineSwitchKind_HyphenDistance,
		"hyphen-distance", "<n>",
		"Specify hyphen distance (default: 6)"
		)
	AXL_SL_CMD_LINE_SWITCH_2(
		CmdLineSwitchKind_UserName,
		"u", "user", "<user>",
		"Specify user name"
		)
	AXL_SL_CMD_LINE_SWITCH_2(
		CmdLineSwitchKind_ProductKey,
		"p", "product-key", "<key>",
		"Specify product key (for verification)"
		)
	AXL_SL_CMD_LINE_SWITCH_2(
		CmdLineSwitchKind_TimeLimit,
		"t", "time-limit", "<days>",
		"Specify time limit (in days)"
		)
	AXL_SL_CMD_LINE_SWITCH_3(
		CmdLineSwitchKind_AddMacTag,
		"m", "mac-tag", "add-mac-tag", "<mac-tag>",
		"Add MAC-tag to make product key machine-specific"
		)
	AXL_SL_CMD_LINE_SWITCH(
		CmdLineSwitchKind_GetMacTag,
		"get-mac-tag", NULL,
		"Display MAC-tag of the current machine"
		)
	AXL_SL_CMD_LINE_SWITCH_2(
		CmdLineSwitchKind_Count,
		"n", "count", "<count>",
		"Specify product key count"
		)
AXL_SL_END_CMD_LINE_SWITCH_TABLE()

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

class CmdLineParser: public sl::CmdLineParser<CmdLineParser, CmdLineSwitchTable>
{
	friend class sl::CmdLineParser<CmdLineParser, CmdLineSwitchTable>;

protected:
	CmdLine* m_cmdLine;

public:
	CmdLineParser(CmdLine* cmdLine)
	{
		m_cmdLine = cmdLine;
	}

protected:
	bool
	onValue(const sl::StringRef& value)
	{
		err::setFormatStringError("invalid argument %s", value.sz());
		return true;
	}

	bool
	onSwitch(
		SwitchKind switchKind,
		const sl::StringRef& value
		);

	bool
	finalize();
};

//..............................................................................
