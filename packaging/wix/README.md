Prerequisites
=============

To create an MSI-distribution package you need to have Windows Installer XML Toolset installed.

Package compilation
===================

To create an MSI-distribution package you have to run the following commands from command line:

	candle.exe libnavigate.wxs
	light -ext WixUIExtension -cultures:en-us libnavigate.wixobj -out libnavigate-win7-x86.msi

This will create distribution package from compiled binaries of libnavigate.

Package installation
====================

To install the compiled distribution package you have to run the foolowing command:

	msiexec /i libnavigate.msi
