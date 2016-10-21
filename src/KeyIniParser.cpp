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
#include "KeyIniParser.h"
#include "CmdLine.h"

//..............................................................................

KeyIniParser::KeyIniParser (CmdLine* cmdLine)
{
	m_cmdLine = cmdLine;
	m_isLicenseMatch = false;
}

bool
KeyIniParser::onSection (const sl::StringRef& sectionName)
{
	if (m_cmdLine->m_license.isEmpty ())
	{
		m_cmdLine->m_license = sectionName;
		m_isLicenseMatch = true;
		return true;
	}

	m_isLicenseMatch = m_cmdLine->m_license == sectionName;
	return true;
}

bool
KeyIniParser::onKeyValue (
	const sl::StringRef& keyName,
	const sl::StringRef& value
	)
{
	if (!m_isLicenseMatch) // ignore
		return true;

	KeyMap::Iterator it = KeyMap::find (keyName);
	if (it)
		switch (it->m_value)
		{
		case Key_PublicKey:
			m_cmdLine->m_licensePublicKey = value;
			break;

		case Key_PrivateKey:
			m_cmdLine->m_licensePrivateKey = value;
			break;

		case Key_Curve:
			m_cmdLine->m_curveId = OBJ_sn2nid (value.sz ());
			if (m_cmdLine->m_curveId == NID_undef)
			{
				err::setFormatStringError ("invalid curve '%s'", value.sz ());
				return false;
			}

			break;
	}

	return true;
}

//..............................................................................
