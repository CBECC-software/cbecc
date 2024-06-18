/**********************************************************************
 *  Copyright (c) 2022, SAC Software Solutions, LLC
 *  All rights reserved.
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions, the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *  - Neither the name of the California Energy Commission nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *  DISCLAIMER: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NON-INFRINGEMENT ARE DISCLAIMED. IN NO EVENT SHALL CALIFORNIA ENERGY COMMISSION,
 *  WRIGHTSOFT CORPORATION, ITRON, INC. OR ANY OTHER AUTHOR OR COPYRIGHT HOLDER OF
 *  THIS SOFTWARE (COLLECTIVELY, THE "AUTHORS") BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 *  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 *  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 *  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  EACH LICENSEE AND SUBLICENSEE OF THE
 *  SOFTWARE AGREES NOT TO ASSERT ANY CLAIM AGAINST ANY OF THE AUTHORS RELATING TO
 *  THIS SOFTWARE, WHETHER DUE TO PERFORMANCE ISSUES, TITLE OR INFRINGEMENT ISSUES,
 *  STRICT LIABILITY OR OTHERWISE.
 **********************************************************************/

#include "stdafx.h"
#include "BEMCmpMgr.h"
#include "BEMCM_I.h"
#include "..\BEMProc\BEMProc.h"
#include "..\BEMProc\BEMClass.h"
#include "ModelkitInterface.h"
#include "memLkRpt.h"
#include "BEMCmpMgrCom.h"

//#include <boost/process.hpp>

using namespace std;
#include <string>
#include <vector>
#include <iostream>     // std::ios, std::istream, std::cout
#include <fstream>      // std::filebuf
//#include <processthreadsapi.h>

// return value:                 // SAC 06/16/22
//       0 : success
//       1 : IDF file to process not found - <sIDFPath>\<sIDFFilenameNoExt>.idf
//       2 : IDF file to process not found - <sIDFPath>\<sIDFFilenameNoExt>.idf
//       3 : IDF file to process not found - <sIDFPath>\<sIDFFilenameNoExt>.idf
//       4 : Intermediate IDF file cannot exist before processing - <sIDFPath>\<sIDFFilenameNoExt> - HybridHVAC-initial.idf
//       5 : error encountered renaming IDF to processing name
int ExecuteModelkitBat(	LPCSTR sModelkitBatPathFile, LPCSTR sModelkitRubyScriptPathFile,
                        LPCSTR sIDFPath, LPCSTR sIDFFilenameNoExt, bool bVerboseOutput /*=false*/,
                        char* pszReturnStr /*=NULL*/, int iReturnStrLength /*=0*/ )
{  int iRetVal = 0;
   string sRetStr;

   string sMainIDFPathFile = sIDFPath;
   sMainIDFPathFile += sIDFFilenameNoExt;
   string sModelkitProcPathFileNoExt = sMainIDFPathFile;
   string sProcessIDFPathFile = sMainIDFPathFile;
   sMainIDFPathFile += ".idf";
   sProcessIDFPathFile += " - HybridHVAC-initial.idf";

   if (!FileExists( sModelkitBatPathFile ))
   {  iRetVal = 1;
      sRetStr = "Modelkit .bat file not found:  " + string( sModelkitBatPathFile );
   }
   else if (!FileExists( sModelkitRubyScriptPathFile ))
   {  iRetVal = 2;
      sRetStr = "IDF file to process not found:  " + string( sModelkitRubyScriptPathFile );
   }
   else if (!FileExists( sMainIDFPathFile.c_str() ))
   {  iRetVal = 3;
      sRetStr = "IDF file to process not found:  " + sMainIDFPathFile;
   }
   else if (FileExists( sProcessIDFPathFile.c_str() ))
   {  iRetVal = 4;
      sRetStr = "Intermediate IDF file cannot exist before processing:  " + sProcessIDFPathFile;
   }
   else  // assuming here that other needed file(s) present, such as:  <sIDFPath>\<sIDFFilenameNoExt> - HybridHVAC.csv
   {
      int iRenRet = rename( sMainIDFPathFile.c_str(), sProcessIDFPathFile.c_str() );
      if (iRenRet != 0)
      {  iRetVal = 5;
         sRetStr = "Error encountered renaming main IDF to processing IDF (* - HybridHVAC-initial.idf)";
      }
      else
      {
         //string sCmdLine = boost::str( boost::format( "ruby \"%s\" \"%s\"" ) % sModelkitRubyScriptPathFile % sModelkitProcPathFileNoExt.c_str() );
         //string sCmdLine = boost::str( boost::format( "\"%s\" ruby \"%s\" \"%s\"" ) % sModelkitBatPathFile % sModelkitRubyScriptPathFile % sModelkitProcPathFileNoExt.c_str() );
         string sCmdLine = boost::str( boost::format( "CALL \"%s\" ruby \"%s\" \"%s\"" ) % sModelkitBatPathFile % sModelkitRubyScriptPathFile % sModelkitProcPathFileNoExt.c_str() );
               if (bVerboseOutput)
                  //BEMPX_WriteLogFile( QString( "              ExecuteModelkitBat() - executing Modelkit:  %1 %2" ).arg( sModelkitBatPathFile, sCmdLine.c_str() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                  //BEMPX_WriteLogFile( QString( "              ExecuteModelkitBat() - executing Modelkit:  CALL %1" ).arg( sCmdLine.c_str() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
                  BEMPX_WriteLogFile( QString( "              ExecuteModelkitBat() - executing Modelkit:  %1" ).arg( sCmdLine.c_str() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

         //int iModelkitRetVal = boost::process::system( sModelkitBatPathFile, sCmdLine.c_str() );
         //int iModelkitRetVal = boost::process::system( "CALL", sCmdLine.c_str() );
         //int iModelkitRetVal = boost::process::system( sCmdLine.c_str() );

         int iModelkitRetVal = system( sCmdLine.c_str() );   // -1 if creating the new process for the command to be executed fails, otherwise it returns the exit code of the command executed

         sRetStr = boost::str( boost::format( "Modelkit returned:  %d" ) % iModelkitRetVal );
               if (bVerboseOutput)
                  BEMPX_WriteLogFile( QString( "              ExecuteModelkitBat() - %1" ).arg( sRetStr.c_str() ), NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
      }
   }

   if (pszReturnStr && iReturnStrLength > 0)
      _snprintf( pszReturnStr, iReturnStrLength, "%s", sRetStr.c_str() );

   return iRetVal;
}
