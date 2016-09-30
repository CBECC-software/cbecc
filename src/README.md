# CBECC Program Modules
Each of the source directories here compile into unique executables (DLL or EXE). The first two, BEMProc and BEMCmpMgr provide the most critical functionality in managing and analyzing building descriptions in testing their compliance to energy codes. These modules were recently migrated away from propertietary library dependencies to open soruce options. BEMCompiler and OS_Wrap also rely primarily on open source depndencies while the main user interface modules, CBECCUI and BEMProcUI, are still heavily dependent on MFC (Microsoft Foundation Classes).  
With the exception of the main UI executable, each of these modules compile into two, and soon more, unique executables. The output name of these executables has a trailing number (currently 16) representing the energy code year and letter (c/r) representing commercial vs. residnetial analysis. This enables multiple sector and energy code year tools to co-exist in a single directory.  

**BEMProc** - Building Energy Model Processor:  Reads, parses & compiles data model and ruleset source into binaries, manages and applies compliance rules to building description during analysis.  

**BEMCmpMgr** - BEM Compliance Manager:  Contains routines designed to manage each step of compliance analysis based on energy code, sector and year. Also handles communication with online report generator and product-specific analysis results exports.  

**OS_Wrap** - OpenStudio Wrapper:  Wrapper DLL providing model manipulation, simulation launching and results retrieval via OpenStudio  

**BEMCompiler** - small utility to convert data model and ruleset source into binary files read and processed at runtime by the above modules.  

**BEMTest** - a work in progress - to be a simple interfacing enabling the launching of single-run and batch compliance analysis. No use in compiling or running this program yet.

**BEMProcUI** - a DLL used to read, parse and manage textual screen definition files specific to energy code sector and year, used to drive the tabbed dialog interface of the CBECC tools.

**CBECCUI** - main program user interface.
