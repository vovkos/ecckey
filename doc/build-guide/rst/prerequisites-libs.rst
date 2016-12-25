.. .............................................................................
..
..  This file is part of the ECCKey utility.
..
..  ECCKey is distributed under the MIT license.
..  For details see accompanying license.txt file,
..  the public copy of which is also available at:
..  http://tibbo.com/downloads/archive/ecckey/license.txt
..
.. .............................................................................

Libraries
=========

These libraries are **required** for building the ECCKey.

* OpenSSL

	ECCKey uses OpenSSL as a cryptographic provider for ECC algorithms (via ``axl_cry`` module of ``AXL`` library).

	.. expand-macro:: openssl-common-info

* AXL

	ECCKey uses AXL as a general purpose C++ support library.

	.. expand-macro:: axl-bundle-info ECCKey ecckey ecckey_b
