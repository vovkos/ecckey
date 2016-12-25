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

Building Documentation
======================

ECCKey contains two documentation packages:

* Build guide
* Manual

.. expand-macro:: build-doc-intro ./build/ecckey

Build Guide
-----------

.. expand-macro:: build-doc-build-guide ./build/ecckey

Manual
------

A manual on the ECCKey command-line tool.

Documentation sources are located at: ``./doc/manual`` (not yet, but soon)

Build steps:

.. code-block:: bash

	cd ./build/ecckey/doc/manual
	./build-html
	./build-pdf
