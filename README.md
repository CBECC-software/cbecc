# CBECC
Building energy code compliance analysis tools - developed for and supported by the California Energy Commission (CEC). This series of program modules enable energy code authorities to easily define and maintain a building data model and rules database that ensure accurate energy code compliance analysis. Performance compliance tools based on this open source project use both EnergyPlus (via OpenStudio) and CSE (California Simulation Engine) building energy simulation tools in comparing proposed and standard/baseline model energy use to determine code compliance.  
For more information about each program module, refer to the src\README.md file.  

# Supporting Files
Weather, rule and other analysis files are included in this repository under \bin. These files include CEC Title-24 analysis rules that are maintained on the following SVN repositories:  
CBECC-Com:  https://sourceforge.net/projects/cbecc-com/  
CBECC-Res:  https://sourceforge.net/projects/cbecc-res/  
Only occasional release versions of rule source for these products will be posted to this repository. For the latest rules, refer to the repositories above.

# Supported Compiler and Platform
This project currently supports compilation using Visual Studio 2013 to produce Windows executables, 32-bit (x86) for CBECC-Res and 64-bit (x64) for CBECC-Com.   Refer to the descriptions of each module under \src\ for more information on system dependencies.

# Build Guidance
Visual Studio 2013 solution and project files are located under src. The main solution file is: \src\CBECC.sln

In addition to the conventional third party tool dependencies (described below), developers must also have the MFC MBCS DLL add-on (Microsoft Foundation Classes library for multibyte character encoding).  
You can download that @:  https://msdn.microsoft.com/en-us/library/dn251007(v=vs.120).aspx  
Once on that page, make sure to specify that you need the libraries compatible with Visual Studio 2013.  
The CBECC tools rely on a number of other open source projects. A subset of code from these tools (all needed to compile CBECC-*) is included under \vendor.  
We recommend that you read through and download (& unzip) the vendor binaries below (or install the complete versions listed below) prior to opening up the CBECC solution in Visual Studio 2013.

# Vendor Binaries
Executable and library files for each of these tools can either be compiled by you, the devloper, or downloaded via the following links. Each of these compressed files are designed to be unzipped into the root repository directory.

*CSE v0.884*:  https://drive.google.com/file/d/1J3tNCYhP0PX3h22aWYHVqtREb3fXRmJl/view?usp=sharing (~2.9 MB, updated 11/19/20 for 2019 releases)  
- Project site:  https://github.com/cse-sim  
- Files needed for CBECC:  bin\Debug_VC12\CSE\cse19.exe & bin\Release_VC12\CSE\cse19.exe

*OpenStudio / EnergyPlus v9.0.1-bb7ca4f0da*:  https://drive.google.com/file/d/1wHOdwVaddrhO4iiwpOJ3--EA7eRTAGYe/view?usp=sharing (~116 MB, updated 8/19/20)  
- OpenStudio project site:  https://github.com/NREL/OpenStudio  
- Link to [OpenStudio branch CBECC-9-0 commit]https://github.com/NREL/OpenStudio/commit/59fe8e7e6f5c09c7d93c1da78fe7350f6fbf1400) used by CBECC 2019.3.1 SP1.  
- OS files needed for CBECC:  subset of OpenStudio DLLs in bin\Debug_VC12x64 & bin\Release_VC12x64  
- EnergyPlus project site:  https://github.com/NREL/EnergyPlus  
- E+ files needed for CBECC:  EnergyPlus.exe and some supporting files in bin\Debug_VC12x64\EPlus & bin\Release_VC12x64\EPlus

*Boost v1.55.0*:  https://drive.google.com/file/d/1X_Rijrt9DJZPVJzIBxDBJPnshlqi7XgQ/view?usp=sharing (~56 MB)  
- Project site:  http://www.boost.org/
- Files needed for CBECC:  (all Boost libraries integrated into program executables)

*Qt v5.3.2 for CBECC-Res and v5.6.1 for CBECC-Com*:  https://drive.google.com/file/d/1ee-VGrN_cErDbwlQSCueal43daXI1gQh/view?usp=sharing (~113 MB, updated 3/26/19)  
- Project site:  https://www.qt.io/  
- Files needed for CBECC:  Qt5Core/Gui/Network/Sql/Webkit/Wdigets/Xml in bin\Debug_VC12, bin\Debug_VC12x64, bin\Release_VC12 & bin\Release_VC12x64  

*OpenSSL v1.0.1j for CBECC-Res and v1.0.2q for CBECC-Com*:  https://drive.google.com/file/d/16wjLKvKFQvflo8rRDxXYHtWZJGZuu30Q/view?usp=sharing (~4.3 MB)  
- Project site:  https://www.openssl.org/  
- Files needed for CBECC:  libeay32.dll & ssleay32.dll in bin\Debug_VC12, bin\Debug_VC12x64, bin\Release_VC12 & bin\Release_VC12x64  
