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

#include "pch.h"
#include "CmdLine.h"

//..............................................................................

CmdLine::CmdLine()
{
	m_flags = 0;
	m_hyphenDistance = 6;
	m_licenseFileName = "ecckey.conf";
	m_curveId = NID_secp112r1;
	m_timeLimit = 0;
	m_randomLength = 0;
	m_keyCount = 1;
}

//..............................................................................

bool
CmdLineParser::onSwitch(
	SwitchKind switchKind,
	const sl::StringRef& value
	)
{
	switch (switchKind)
	{
	case CmdLineSwitchKind_Help:
		m_cmdLine->m_flags |= CmdLineFlag_Help;
		break;

	case CmdLineSwitchKind_Version:
		m_cmdLine->m_flags |= CmdLineFlag_Version;
		break;

	case CmdLineSwitchKind_NewLicenseFile:
		m_cmdLine->m_flags |= CmdLineFlag_NewLicenseFile;
		break;

	case CmdLineSwitchKind_NewLicenseKey:
		m_cmdLine->m_flags |= CmdLineFlag_NewLicenseKey;
		break;

	case CmdLineSwitchKind_NewProductKey:
		m_cmdLine->m_flags |= CmdLineFlag_NewProductKey;
		break;

	case CmdLineSwitchKind_VerifyProductKey:
		m_cmdLine->m_flags |= CmdLineFlag_VerifyProductKey;
		break;

	case CmdLineSwitchKind_ListCurves:
		m_cmdLine->m_flags |= CmdLineFlag_ListCurves;
		break;

	case CmdLineSwitchKind_Minimalistic:
		m_cmdLine->m_flags |= CmdLineFlag_Minimalistic;
		break;

	case CmdLineSwitchKind_LicenseFileName:
		m_cmdLine->m_licenseFileName = value;
		break;

	case CmdLineSwitchKind_License:
		m_cmdLine->m_license = value;
		break;

	case CmdLineSwitchKind_LicensePublicKey:
		m_cmdLine->m_licensePublicKey = value;
		break;

	case CmdLineSwitchKind_LicensePrivateKey:
		m_cmdLine->m_licensePrivateKey = value;
		break;

	case CmdLineSwitchKind_LicenseCurve:
		m_cmdLine->m_curveId = OBJ_sn2nid(value.sz());
		if (m_cmdLine->m_curveId == NID_undef)
		{
			err::setFormatStringError("invalid curve '%s'", value.sz());
			return false;
		}

		break;

	case CmdLineSwitchKind_HyphenDistance:
		m_cmdLine->m_hyphenDistance = atoi(value.sz());
		if (!m_cmdLine->m_hyphenDistance)
		{
			err::setFormatStringError("invalid hyphen distance '%s'", value.sz());
			return false;
		}

		break;

	case CmdLineSwitchKind_UserName:
		m_cmdLine->m_userName = value;
		break;

	case CmdLineSwitchKind_ProductKey:
		m_cmdLine->m_productKey = value;
		break;

	case CmdLineSwitchKind_TimeLimit:
		m_cmdLine->m_timeLimit = atoi(value.sz());
		break;

	case CmdLineSwitchKind_AddMacFp:
		enc::Base32Encoding_nj::decode(&m_cmdLine->m_macFp, value);
		break;

	case CmdLineSwitchKind_CalcMacFp:
		m_cmdLine->m_flags |= CmdLineFlag_CalcMacFp;
		break;

	case CmdLineSwitchKind_Count:
		m_cmdLine->m_keyCount = atoi(value.sz());
		break;
	}

	return true;
}

bool
CmdLineParser::finalize()
{
	if (!(m_cmdLine->m_flags & (CmdLineFlag_NewProductKey | CmdLineFlag_VerifyProductKey)))
	{
		if (!m_cmdLine->m_userName.isEmpty() || !m_cmdLine->m_license.isEmpty()) // e.g. ecckey -u user
			m_cmdLine->m_flags |= CmdLineFlag_NewProductKey;
	}
	else if (m_cmdLine->m_userName.isEmpty())
	{
		err::setFormatStringError("missing user name (-u switch)");
		return false;
	}

	if ((m_cmdLine->m_flags & CmdLineFlag_VerifyProductKey) && m_cmdLine->m_productKey.isEmpty())
	{
		err::setFormatStringError("missing product key (-p switch)");
		return false;
	}

	return true;
}

//..............................................................................
