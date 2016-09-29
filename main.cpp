#include "pch.h"
#include "CmdLine.h"
#include "KeyIniParser.h"
#include "version.h"

#define _PRINT_USAGE_IF_NO_ARGUMENTS

//.............................................................................

void
printVersion ()
{
	printf (
		"ecc-key v%d.%d.%d (%s%s)\n",
		VERSION_MAJOR,
		VERSION_MINOR,
		VERSION_REVISION,
		AXL_CPU_STRING,
		AXL_DEBUG_SUFFIX
		);
}

void
printUsage ()
{
	printVersion ();

	sl::String helpString = CmdLineSwitchTable::getHelpString ();
	printf ("Usage: ecc-key <options>...\n%s", helpString.cc ());
}

void
listCurves (CmdLine* cmdLine)
{
	size_t count = EC_get_builtin_curves (NULL, 0);
	
	sl::Array <EC_builtin_curve> curveArray;
	curveArray.setCount (count);
	count = EC_get_builtin_curves (curveArray, count);

	if (cmdLine->m_flags & CmdLineFlag_Minimalistic)
		for (size_t i = 0; i < count; i++)
			printf ("%s\n", OBJ_nid2sn (curveArray [i].nid));
	else 
		for (size_t i = 0; i < count; i++)
			printf (
				"NID     = %d\n"
				"SN      = %s\n"
				"comment = %s\n\n", 
				curveArray [i].nid, 
				OBJ_nid2sn (curveArray [i].nid),
				curveArray [i].comment
				);
}

int 
newLicenseKey (CmdLine* cmdLine)
{
	cry::EcKey key (cmdLine->m_curveId);
	key.generateKey ();

	cry::EcPoint publicKey = key.getPublicKey ();
	cry::BigNum privateKey = key.getPrivateKey ();

	printf (
		"curve       = %s\n"
		"public-key  = %s\n"
		"private-key = %s\n",
		OBJ_nid2sn (cmdLine->m_curveId),
		publicKey.getHexString (key.getGroup ()).cc (),
		privateKey.getHexString ().cc ()
		);

	privateKey.detach ();
	publicKey.detach ();

	if (cmdLine->m_flags & CmdLineFlag_Minimalistic)
		return 0;

	const char* sampleUserName = "Sample User";

	sl::String sampleProductKey = cry::generateEcProductKey (
		key,
		sampleUserName,
		cmdLine->m_hyphenDistance
		);

	bool isValidKey = cry::verifyEcProductKey (key, sampleUserName, sampleProductKey);
	if (!isValidKey)
	{
		printf ("error: unable to verify sample product key\n");
		return -1;
	}

	printf (
		"\n# sample:\n"
		"# user        = %s\n"
		"# product key = %s\n",
		sampleUserName,		
		sampleProductKey.cc ()
		);

	return 0;
}

int 
newProductKey (CmdLine* cmdLine)
{
	bool result;

	if (cmdLine->m_licensePrivateKey.isEmpty ())
	{
		KeyIniParser parser (cmdLine);
		result = parser.parseFile (cmdLine->m_licenseFileName);
		if (!result)
		{
			printf (
				"error reading %s: %s\n",
				cmdLine->m_licenseFileName.cc (),
				err::getLastErrorDescription ().cc ()
				);
			return -1;
		}
	}

	cry::EcKey key (cmdLine->m_curveId);
	result = key.setPrivateKeyHexString (cmdLine->m_licensePrivateKey);
	if (!result)
	{
		printf (
			"invalid private key '%s': %s\n",
			cmdLine->m_licensePrivateKey.cc (),
			err::getLastErrorDescription ().cc ()
			);
		return -1;
	}

	sl::String productKey = cry::generateEcProductKey (key, cmdLine->m_userName, cmdLine->m_hyphenDistance);

	EC_GROUP* group = key.getGroup ();
	BIGNUM* privateKey = key.getPrivateKey ();

	cry::EcPoint publicKey (group);
	publicKey.mul (group, privateKey);
	key.setPublicKey (publicKey);

	bool isValidKey = cry::verifyEcProductKey (key, cmdLine->m_userName, productKey);
	if (!isValidKey)
	{
		printf ("error: unable to verify newly created product key\n");
		return -1;
	}

	if (!cmdLine->m_license.isEmpty ())
		printf ("license     = %s\n", cmdLine->m_license.cc ());

	printf (
		"user        = %s\n"
		"product key = %s\n",
		cmdLine->m_userName.cc (),
		productKey.cc ()
		);

	return 0;
}

int 
verifyProductKey (CmdLine* cmdLine)
{
	bool result;

	if (cmdLine->m_licensePublicKey.isEmpty ())
	{
		KeyIniParser parser (cmdLine);
		result = parser.parseFile (cmdLine->m_licenseFileName);
		if (!result)
		{
			printf (
				"error reading %s: %s\n",
				cmdLine->m_licenseFileName.cc (),
				err::getLastErrorDescription ().cc ()
				);
			return -1;
		}
	}

	cry::EcKey key (cmdLine->m_curveId);
	result = key.setPublicKeyHexString (cmdLine->m_licensePublicKey);
	if (!result)
	{
		printf (
			"invalid public key '%s': %s\n",
			cmdLine->m_licensePublicKey.cc (),
			err::getLastErrorDescription ().cc ()
			);
		return -1;
	}

	result = cry::verifyEcProductKey (key, cmdLine->m_userName, cmdLine->m_productKey);
	if (!result)
	{
		printf ("invalid user-name/product-key combination\n");
		return -1;
	}
	else
	{
		printf ("product key is valid\n");
		return 0;
	}
}

//.............................................................................

#if (_AXL_OS_WIN)
int
wmain (
	int argc,
	wchar_t* argv []
	)
#else
int
main (
	int argc,
	char* argv []
	)
#endif
{
	int result;

	lex::registerParseErrorProvider ();
	cry::registerCryptoErrorProvider ();

	CmdLine cmdLine;
	CmdLineParser parser (&cmdLine);

#ifdef _PRINT_USAGE_IF_NO_ARGUMENTS
	if (argc < 2)
	{
		printUsage ();
		return 0;
	}
#endif

	result = parser.parse (argc, argv);
	if (!result)
	{
		printf ("error parsing command line: %s\n", err::getLastErrorDescription ().cc ());
		return -1;
	}

#if (_AXL_OS_WIN)
	SetConsoleOutputCP (CP_UTF8);
#endif

	result = 0;

	if (cmdLine.m_flags & CmdLineFlag_Help)
		printUsage ();
	else if (cmdLine.m_flags & CmdLineFlag_Version)
		printVersion ();
	else if (cmdLine.m_flags & CmdLineFlag_ListCurves)
		listCurves (&cmdLine);
	else if (cmdLine.m_flags & CmdLineFlag_NewLicenseKey)
		result = newLicenseKey (&cmdLine);
	else if (cmdLine.m_flags & CmdLineFlag_NewProductKey)
		result = newProductKey (&cmdLine);
	else if (cmdLine.m_flags & CmdLineFlag_VerifyProductKey)
		result = verifyProductKey (&cmdLine);

	return result;
}

//.............................................................................
