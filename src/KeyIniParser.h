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

struct CmdLine;

//..............................................................................

class KeyIniParser: public ini::Parser<KeyIniParser> {
protected:
	enum Key {
		Key_Curve,
		Key_PublicKey,
		Key_PrivateKey,
		Key_RandomLength,
		Key_HyphenDistance,
	};

	AXL_SL_BEGIN_STRING_HASH_TABLE(KeyMap, Key)
		AXL_SL_HASH_TABLE_ENTRY("curve",           Key_Curve)
		AXL_SL_HASH_TABLE_ENTRY("public-key",      Key_PublicKey)
		AXL_SL_HASH_TABLE_ENTRY("private-key",     Key_PrivateKey)
		AXL_SL_HASH_TABLE_ENTRY("random-length",   Key_RandomLength)
		AXL_SL_HASH_TABLE_ENTRY("hyphen-distance", Key_HyphenDistance)
	AXL_SL_END_HASH_TABLE()

protected:
	bool m_isLicenseMatch;
	CmdLine* m_cmdLine;

public:
	KeyIniParser(CmdLine* cmdLine);

	bool
	onSection(const sl::StringRef& sectionName);

	bool
	onKeyValue(
		const sl::StringRef& keyName,
		const sl::StringRef& value
	);
};

//..............................................................................
