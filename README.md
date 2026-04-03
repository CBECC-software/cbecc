# CBECC
Building energy code compliance analysis tools - developed for and supported by the California Energy Commission (CEC). This series of program modules enable energy code authorities to easily define and maintain a building data model and rules database that ensure accurate energy code compliance analysis. Performance compliance tools based on this open source project use both EnergyPlus (via OpenStudio) and CSE (California Simulation Engine) building energy simulation tools in comparing proposed and standard/baseline model energy use to determine code compliance.  
For more information about each program module, refer to the src\README.md file.  

# Supporting Files
Weather, rule and other analysis files are included in this repository under \bin. These files include CEC Title-24 analysis rules that are maintained on the following GitHub repository: https://github.com/NOR-Codes-Stds/CBECC
As of version 2025.2.0, CBECC-Res has been integrated into CBECC, but analysis rulesets (both source and binaries) remain unique to NRMF (nonresidential/multifamily) and SFam (single-family/duplex) model analysis. Only occasional release versions of CBECC ruleset binaries will be posted to this repository. For the latest rule source, refer to the repository above.

# Supported Compiler and Platform
This project currently supports compilation using Visual Studio 2022 to produce Windows 64-bit (x64) CBECC executable. Refer to the descriptions of each module under \src\ for more information on system dependencies.

# Build Guidance
Visual Studio 2022 solution and project files are located under src. The main solution file is: \src\CBECC-VS22.sln

In addition to the conventional third party tool dependencies (described below), developers must also have the MFC MBCS DLL add-on (Microsoft Foundation Classes library for multibyte character encoding).  
The CBECC tools rely on a number of other open source projects. A subset of code from these tools (all needed to compile CBECC) is included under \vendor.  
We recommend that you read through and download (& unzip) the vendor binaries below (or install the complete versions listed below) prior to opening up the CBECC solution in Visual Studio.

# Vendor Binaries
Executable and library files for each of these tools can either be compiled by you, the devloper, or downloaded via the following links. Each of these compressed files are designed to be unzipped into the root repository directory.

*CSE v0.928.0*:  https://drive.google.com/file/d/1bmskv35vA8OYJEZUkEoLXPfmx0Nheq_S/view?usp=sharing (~9.3 MB, updated 4/2/26 for 2025.2.1 release)  
- Project site:  https://github.com/cse-sim 

*OpenStudio / EnergyPlus v25-1*:  https://drive.google.com/file/d/1pjbVf7rDkZ1AXBdzaJZ7mZcTTRDm8VBH/view?usp=sharing (~124 MB, updated 8/14/25)  
- OpenStudio project site:  https://github.com/NREL/OpenStudio  
- Link to [OpenStudio branch CBECC-25-1 commit]https://github.com/NREL/OpenStudio/commit/e80a80c812eefa68d5b6df209e32373646515355 (used by CBECC 2025.2.*)
- EnergyPlus project site:  https://github.com/NREL/EnergyPlus  

*Boost v1.74.0*:  https://drive.google.com/file/d/1VRc5BLzsbdP94S6UoLPIQ3EQhz4TjrIv/view?usp=sharing (~46 MB, updated 1/30/25)  
- Project site:  http://www.boost.org/

*Qt v5.15.0*:  https://drive.google.com/file/d/1SAo-_pwd4WgzCDDzADsHc1x3wAgtqsP0/view?usp=sharing (~29 MB, updated 3/31/26)  
- Project site:  https://www.qt.io/  

*OpenSSL v1.1.1h*:  https://drive.google.com/file/d/1mdKTRPWu6_2h9GmF7V3bZX4c-4PXBXTR/view?usp=sharing (~24 MB, updated 1/30/25)  
- Project site:  https://www.openssl.org/  
