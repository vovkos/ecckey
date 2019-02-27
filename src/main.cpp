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
#include "KeyIniParser.h"
#include "version.h"

#define _PRINT_USAGE_IF_NO_ARGUMENTS

//..............................................................................

void
printVersion()
{
	printf(
		"ecckey v%d.%d.%d (%s%s)\n",
		VERSION_MAJOR,
		VERSION_MINOR,
		VERSION_REVISION,
		AXL_CPU_STRING,
		AXL_DEBUG_SUFFIX
		);
}

void
printUsage()
{
	printVersion();

	sl::String helpString = CmdLineSwitchTable::getHelpString();
	printf("Usage: ecckey <options>...\n%s", helpString.sz());
}

void
listCurves(CmdLine* cmdLine)
{
	size_t count = EC_get_builtin_curves(NULL, 0);

	sl::Array<EC_builtin_curve> curveArray;
	curveArray.setCount(count);
	count = EC_get_builtin_curves(curveArray, count);

	if (cmdLine->m_flags & CmdLineFlag_Minimalistic)
		for (size_t i = 0; i < count; i++)
			printf("%s\n", OBJ_nid2sn (curveArray [i].nid));
	else
		for (size_t i = 0; i < count; i++)
			printf(
				"NID     = %d\n"
				"SN      = %s\n"
				"comment = %s\n\n",
				curveArray[i].nid,
				OBJ_nid2sn(curveArray[i].nid),
				curveArray[i].comment
				);
}

int
newLicenseFile(CmdLine* cmdLine)
{
	bool doesExist = io::doesFileExist(cmdLine->m_licenseFileName);
	if (doesExist)
	{
		printf("file %s already exists\n", cmdLine->m_licenseFileName.sz());
		return -1;
	}

	io::File file;
	bool result = file.open(cmdLine->m_licenseFileName);
	if (!result)
	{
		printf(
			"can't open %s: %s\n", cmdLine->m_licenseFileName.sz(),
			err::getLastErrorDescription().sz()
			);
		return -1;
	}

	cry::EcKey key(cmdLine->m_curveId);
	key.generateKey();

	cry::EcPoint publicKey = key.getPublicKey();
	cry::BigNum privateKey = key.getPrivateKey();

	sl::String buffer;
	buffer.format(
		"[sample-license]\n"
		"curve       = %s\n"
		"public-key  = %s\n"
		"private-key = %s\n",
		OBJ_nid2sn(cmdLine->m_curveId),
		publicKey.getHexString(key.getGroup()).sz(),
		privateKey.getHexString().sz()
		);

	privateKey.detach();
	publicKey.detach();

	file.write(buffer, buffer.getLength());
	return 0;
}

int
newLicenseKey(CmdLine* cmdLine)
{
	cry::EcKey key(cmdLine->m_curveId);
	key.generateKey();

	cry::EcPoint publicKey = key.getPublicKey();
	cry::BigNum privateKey = key.getPrivateKey();

	printf(
		"curve       = %s\n"
		"public-key  = %s\n"
		"private-key = %s\n",
		OBJ_nid2sn(cmdLine->m_curveId),
		publicKey.getHexString(key.getGroup()).sz(),
		privateKey.getHexString().sz()
		);

	privateKey.detach();
	publicKey.detach();

	if (cmdLine->m_flags & CmdLineFlag_Minimalistic)
		return 0;

	sl::StringRef sampleUserName = "Sample User";

	sl::String sampleProductKey = cry::generateEcProductKey(
		key,
		sampleUserName,
		cmdLine->m_hyphenDistance
		);

	bool isValidKey = cry::verifyEcProductKey(key, sampleUserName, sampleProductKey);
	if (!isValidKey)
	{
		printf("error: unable to verify sample product key\n");
		return -1;
	}

	printf(
		"\n# sample:\n"
		"# user        = %s\n"
		"# product key = %s\n",
		sampleUserName.sz(),
		sampleProductKey.sz()
		);

	return 0;
}

int
verifyProductKey(CmdLine* cmdLine)
{
	bool result;

	if (cmdLine->m_licensePublicKey.isEmpty())
	{
		KeyIniParser parser(cmdLine);
		result = parser.parseFile(cmdLine->m_licenseFileName);
		if (!result)
		{
			printf(
				"error reading %s: %s\n",
				cmdLine->m_licenseFileName.sz(),
				err::getLastErrorDescription().sz()
				);
			return -1;
		}
	}

	cry::EcKey key(cmdLine->m_curveId);
	result = key.setPublicKeyHexString(cmdLine->m_licensePublicKey);
	if (!result)
	{
		printf(
			"invalid public key '%s': %s\n",
			cmdLine->m_licensePublicKey.sz(),
			err::getLastErrorDescription().sz()
			);
		return -1;
	}

	size_t dueTimeIndex = cmdLine->m_productKey.find(':');

	if (dueTimeIndex == -1)
	{
		result = cry::verifyEcProductKey(key, cmdLine->m_userName, cmdLine->m_productKey);
		if (!result)
		{
			printf("invalid user-name/product-key combination\n");
			return -1;
		}
	}
	else
	{
		sl::StringRef productKey = cmdLine->m_productKey.getSubString(0, dueTimeIndex);
		sl::StringRef dueTimeString = cmdLine->m_productKey.getSubString(dueTimeIndex + 1);

		sl::Array<char> dueTimeBuffer = enc::Base32Encoding::decode(dueTimeString);
		if (dueTimeBuffer.getCount() < sizeof(uint32_t))
		{
			printf("invalid product-key\n");
			return -1;
		}

		sl::String userName = cmdLine->m_userName;
		userName.append(dueTimeBuffer, sizeof(uint32_t));

		result = cry::verifyEcProductKey(key, userName, productKey);
		if (!result)
		{
			printf("invalid user-name/product-key combination\n");
			return -1;
		}

		uint64_t dueTime = (*(uint32_t*)dueTimeBuffer.cp());
		dueTime <<= 32;

		if (dueTime < sys::getTimestamp())
		{
			printf("product key is valid, but expired\n");
			return -2;
		}
	}

	printf("product key is valid\n");
	return 0;
}

int
newProductKey(CmdLine* cmdLine)
{
	bool result;

	if (cmdLine->m_licensePrivateKey.isEmpty())
	{
		KeyIniParser parser(cmdLine);
		result = parser.parseFile(cmdLine->m_licenseFileName);
		if (!result)
		{
			printf(
				"error reading %s: %s\n",
				cmdLine->m_licenseFileName.sz(),
				err::getLastErrorDescription().sz()
				);
			return -1;
		}
	}

	if (cmdLine->m_randomLength)
	{
		char buffer[256];
		sl::Array<char> data(ref::BufKind_Stack, buffer, sizeof(buffer));
		data.setCount(cmdLine->m_randomLength);

		static char base[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

		for (size_t i = 0; i < cmdLine->m_keyCount; i++)
		{
			::RAND_bytes((uchar_t*)data.p(), cmdLine->m_randomLength);

			sl::String key;
			for (size_t i = 0, j = 1; i < cmdLine->m_randomLength; i++, j++)
			{
				key += base[data[i] % lengthof(base)];

				if (j % cmdLine->m_hyphenDistance == 0)
					key += '-';
			}

			if (key.isSuffix("-"))
				key.chop(1);

			printf("product key = %s\n", key.sz());
		}

		return 0;
	}

	cry::EcKey key(cmdLine->m_curveId);
	result = key.setPrivateKeyHexString(cmdLine->m_licensePrivateKey);
	if (!result)
	{
		printf(
			"invalid private key '%s': %s\n",
			cmdLine->m_licensePrivateKey.sz(),
			err::getLastErrorDescription().sz()
			);
		return -1;
	}

	sl::String productKey;

	uint64_t dueTime;

	if (!cmdLine->m_timeLimit)
	{
		productKey = cry::generateEcProductKey(key, cmdLine->m_userName, cmdLine->m_hyphenDistance);
	}
	else
	{
		dueTime = sys::getTimestamp();
		dueTime += (uint64_t)cmdLine->m_timeLimit * 24 * 60 * 60 * 1000 * 10000;
		dueTime >>= 32;

		sl::String userName = cmdLine->m_userName;
		userName.append((char*) &dueTime, 4);

		productKey = cry::generateEcProductKey(key, userName, cmdLine->m_hyphenDistance);

		productKey += ':';
		productKey += enc::Base32Encoding::encode(&dueTime, 4, -1);
	}

	if (!cmdLine->m_license.isEmpty())
		printf("license     = %s\n", cmdLine->m_license.sz());

	printf(
		"user        = %s\n"
		"product key = %s\n",
		cmdLine->m_userName.sz(),
		productKey.sz()
		);

	if (cmdLine->m_timeLimit)
	{
		printf(
			"time limit  = %d days\n"
			"expires on  = %s\n",
			cmdLine->m_timeLimit,
			sys::Time(dueTime << 32).format().sz()
			);
	}

	cmdLine->m_productKey = productKey;

	printf("\nverifying...\n");
	return verifyProductKey(cmdLine);
}

//..............................................................................

#if (_AXL_OS_WIN)
int
wmain(
	int argc,
	wchar_t* argv[]
	)
#else
int
main(
	int argc,
	char* argv[]
	)
#endif
{
	int result;

#if _AXL_OS_POSIX
	setvbuf(stdout, NULL, _IOLBF, 1024);
#endif

	srand((int)sys::getTimestamp());

	g::getModule()->setTag("ecckey");
	lex::registerParseErrorProvider();
	cry::registerCryptoErrorProvider();

	CmdLine cmdLine;
	CmdLineParser parser(&cmdLine);

#ifdef _PRINT_USAGE_IF_NO_ARGUMENTS
	if (argc < 2)
	{
		printUsage();
		return 0;
	}
#endif

	result = parser.parse(argc, argv);
	if (!result)
	{
		printf("error parsing command line: %s\n", err::getLastErrorDescription().sz());
		return -1;
	}

#if (_AXL_OS_WIN)
	SetConsoleOutputCP(CP_UTF8);
#endif

	result = 0;

	if (cmdLine.m_flags & CmdLineFlag_Help)
		printUsage();
	else if (cmdLine.m_flags & CmdLineFlag_Version)
		printVersion();
	else if (cmdLine.m_flags & CmdLineFlag_ListCurves)
		listCurves(&cmdLine);
	else if (cmdLine.m_flags & CmdLineFlag_NewLicenseFile)
		result = newLicenseFile(&cmdLine);
	else if (cmdLine.m_flags & CmdLineFlag_NewLicenseKey)
		result = newLicenseKey(&cmdLine);
	else if (cmdLine.m_flags & CmdLineFlag_NewProductKey)
		result = newProductKey(&cmdLine);
	else if (cmdLine.m_flags & CmdLineFlag_VerifyProductKey)
		result = verifyProductKey(&cmdLine);

	return result;
}

//..............................................................................
