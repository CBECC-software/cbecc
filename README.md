# CBECC
Building energy code compliance analysis tools - developed for and supported by the California Energy Commission (CEC). This series of program modules enable energy code authorities to easily define and maintain a building data model and rules database that ensure accurate energy code compliance analysis. Performance compliance tools based on this open source project use both EnergyPlus (via OpenStudio) and CSE (California Simulation Engine) building energy simulation tools in comparing proposed and standard/baseline model energy use to determine code compliance.  
For more information about each program module, refer to the src\README.md file.  

# Supporting Files
Weather, rule and other analysis files are included in this repository under \bin. These files include CEC Title-24 analysis rules that are maintained on the following SVN repositories:  
CBECC:      https://sourceforge.net/projects/cbecc-com/  
CBECC-Res:  https://sourceforge.net/projects/cbecc-res/  
Only occasional release versions of ruleset binaries for these products will be posted to this repository. For the latest rule source, refer to the repositories above.

# Supported Compiler and Platform
This project currently supports compilation using Visual Studio 2022 to produce Windows 64-bit (x64) executables, CBECC and CBECC-Res. Refer to the descriptions of each module under \src\ for more information on system dependencies.

# Build Guidance
Visual Studio 2022 solution and project files are located under src. The main solution file is: \src\CBECC-VS22.sln

In addition to the conventional third party tool dependencies (described below), developers must also have the MFC MBCS DLL add-on (Microsoft Foundation Classes library for multibyte character encoding).  
The CBECC tools rely on a number of other open source projects. A subset of code from these tools (all needed to compile CBECC-*) is included under \vendor.  
We recommend that you read through and download (& unzip) the vendor binaries below (or install the complete versions listed below) prior to opening up the CBECC solution in Visual Studio 2022.

# Vendor Binaries
Executable and library files for each of these tools can either be compiled by you, the devloper, or downloaded via the following links. Each of these compressed files are designed to be unzipped into the root repository directory.

*CSE v0.923.1*:  https://drive.google.com/file/d/1anJCTqV1oIA_rMS2XIr-yUf4rtcvUdNK/view?usp=sharing (~3.2 MB, updated 1/30/25 for 2022.3.2 releases)  
- Project site:  https://github.com/cse-sim 

*OpenStudio / EnergyPlus v9.4*:  https://drive.google.com/file/d/1yEO0ILgJf50m8fIwBvomiULhc2zSImvl/view?usp=sharing (~359 MB, updated 1/30/25)  
- OpenStudio project site:  https://github.com/NREL/OpenStudio  
- Link to [OpenStudio branch CBECC-9-4 commit]https://github.com/NREL/OpenStudio/commit/6c605c36c6ec7e45e7648c835ae2e9a7d823838a) used by CBECC 2033.3.2
- EnergyPlus project site:  https://github.com/NREL/EnergyPlus  

*Boost v1.74.0*:  https://drive.google.com/file/d/1VRc5BLzsbdP94S6UoLPIQ3EQhz4TjrIv/view?usp=sharing (~46 MB, updated 1/30/25)  
- Project site:  http://www.boost.org/

*Qt v5.15.0*:  https://drive.google.com/file/d/1ee-VGrN_cErDbwlQSCueal43daXI1gQh/view?usp=sharing (~207 MB, updated 1/30/25)  
- Project site:  https://www.qt.io/  

*OpenSSL v1.1.1h*:  https://drive.google.com/file/d/1mdKTRPWu6_2h9GmF7V3bZX4c-4PXBXTR/view?usp=sharing (~24 MB, updated 1/30/25)  
- Project site:  https://www.openssl.org/  
