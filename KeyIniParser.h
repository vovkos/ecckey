#pragma once

struct CmdLine;

//.............................................................................

class KeyIniParser: public ini::Parser <KeyIniParser>
{
protected:
	enum Key
	{
		Key_Curve,
		Key_PublicKey,
		Key_PrivateKey,
	};

	AXL_RTL_BEGIN_HASH_TABLE_MAP_STRING (KeyMap, Key)
		AXL_RTL_HASH_TABLE_MAP_ENTRY ("curve",       Key_Curve)
		AXL_RTL_HASH_TABLE_MAP_ENTRY ("public-key",  Key_PublicKey)
		AXL_RTL_HASH_TABLE_MAP_ENTRY ("private-key", Key_PrivateKey)
	AXL_RTL_END_HASH_TABLE_MAP ()

protected:
	bool m_isLicenseMatch;
	CmdLine* m_cmdLine;

public:
	KeyIniParser (CmdLine* cmdLine);

	bool 
	onSection (const char* sectionName);

	bool 
	onKeyValue (
		const char* keyName, 
		const char* value
		);
};

//.............................................................................
