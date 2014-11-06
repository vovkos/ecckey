#pragma once

//.............................................................................

enum CmdLineFlag
{
	CmdLineFlag_Help             = 0x0001,
	CmdLineFlag_Version          = 0x0002,
	CmdLineFlag_NewLicenseKey    = 0x0004,
	CmdLineFlag_NewProductKey    = 0x0008,
	CmdLineFlag_VerifyProductKey = 0x0010,
	CmdLineFlag_ListCurves       = 0x0020,
	CmdLineFlag_Minimalistic     = 0x0040,
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

struct CmdLine
{
	uint_t m_flags;
	size_t m_hyphenDistance;
	uint_t m_curveId;
	
	rtl::String m_licenseFileName;
	rtl::String m_license;
	rtl::String m_licensePublicKey;
	rtl::String m_licensePrivateKey;
	rtl::String m_userName;
	rtl::String m_productKey;

	CmdLine ();
};

//.............................................................................

enum CmdLineSwitchKind
{
	CmdLineSwitchKind_Undefined = 0,
	CmdLineSwitchKind_Help,
	CmdLineSwitchKind_Version,
	CmdLineSwitchKind_NewLicenseKey,
	CmdLineSwitchKind_NewProductKey,
	CmdLineSwitchKind_VerifyProductKey,
	CmdLineSwitchKind_ListCurves,
	CmdLineSwitchKind_Minimalistic,
	CmdLineSwitchKind_LicenseFileName = rtl::CmdLineSwitchFlag_HasValue,
	CmdLineSwitchKind_License,
	CmdLineSwitchKind_LicensePublicKey,
	CmdLineSwitchKind_LicensePrivateKey,
	CmdLineSwitchKind_LicenseCurve,
	CmdLineSwitchKind_HyphenDistance,
	CmdLineSwitchKind_UserName,
	CmdLineSwitchKind_ProductKey,
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

AXL_RTL_BEGIN_CMD_LINE_SWITCH_TABLE (CmdLineSwitchTable, CmdLineSwitchKind)
	AXL_RTL_CMD_LINE_SWITCH_2 (
		CmdLineSwitchKind_Help,
		"h", "help", NULL,
		"Display this help"
		)
	AXL_RTL_CMD_LINE_SWITCH_2 (
		CmdLineSwitchKind_Version,
		"v", "version", NULL,
		"Display version of ecc-key"
		)
	AXL_RTL_CMD_LINE_SWITCH (
		CmdLineSwitchKind_NewLicenseKey,
		"new-license-key", NULL,
		"Generate a new license key"
		)
	AXL_RTL_CMD_LINE_SWITCH (
		CmdLineSwitchKind_NewProductKey,
		"new-product-key", NULL,
		"Generate a new product key"
		)
	AXL_RTL_CMD_LINE_SWITCH_2 (
		CmdLineSwitchKind_VerifyProductKey,
		"verify", "check", NULL,
		"Verify a product key"
		)
	AXL_RTL_CMD_LINE_SWITCH (
		CmdLineSwitchKind_ListCurves,
		"list-curves", NULL,
		"Display the list of available ECC curves"
		)
	AXL_RTL_CMD_LINE_SWITCH_2 (
		CmdLineSwitchKind_Minimalistic,
		"min", "minimalistic", NULL,
		"Omit verbose data where possible"
		)
	AXL_RTL_CMD_LINE_SWITCH_2 (
		CmdLineSwitchKind_LicenseFileName,
		"f", "license-file", "<file>",
		"Specify license file (default: ecc-key.conf)"
		)
	AXL_RTL_CMD_LINE_SWITCH_2 (
		CmdLineSwitchKind_License,
		"l", "license", "<license>",
		"Specify license (default: the 1st license in file)"
		)
	AXL_RTL_CMD_LINE_SWITCH (
		CmdLineSwitchKind_LicensePublicKey,
		"public-key", "<key>",
		"Specify license public key (for verification)"
		)
	AXL_RTL_CMD_LINE_SWITCH (
		CmdLineSwitchKind_LicensePrivateKey,
		"private-key", "<key>",
		"Specify license private key"
		)
	AXL_RTL_CMD_LINE_SWITCH_2 (
		CmdLineSwitchKind_LicenseCurve,
		"c", "curve", "<curve>",
		"Specify ECC curve (default: secp112r1)"
		)
	AXL_RTL_CMD_LINE_SWITCH (
		CmdLineSwitchKind_HyphenDistance,
		"hyphen-distance", "<n>",
		"Specify hyphen distance (default: 6)"
		)
	AXL_RTL_CMD_LINE_SWITCH_2 (
		CmdLineSwitchKind_UserName,
		"u", "user", "<user>",
		"Specify user name"
		)
	AXL_RTL_CMD_LINE_SWITCH_2 (
		CmdLineSwitchKind_UserName,
		"p", "product-key", "<key>",
		"Specify product key (for verification)"
		)
AXL_RTL_END_CMD_LINE_SWITCH_TABLE ()

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

class CmdLineParser: public rtl::CmdLineParser <CmdLineParser, CmdLineSwitchTable>
{
	friend class rtl::CmdLineParser <CmdLineParser, CmdLineSwitchTable>;

protected:
	CmdLine* m_cmdLine;

public:
	CmdLineParser (CmdLine* cmdLine)
	{
		m_cmdLine = cmdLine;
	}

protected:
	bool
	onValue (const char* value)
	{
		err::setFormatStringError ("invalid argument %s", value);
		return true;
	}

	bool
	onSwitch (
		SwitchKind switchKind,
		const char* value
		);
	
	bool
	finalize ();
};

//.............................................................................
