/**********************************************************************
 *  Copyright (c) 2012-2017, California Energy Commission
 *  Copyright (c) 2012-2017, Wrightsoft Corporation
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

#ifdef CECRPTGEN

#include <openssl/sha.h>

#include "..\BEMProc\BEMProc.h"
#include "BEMCmpMgr.h"
#include "BEMCM_I.h"
#include <fstream>      // fstream
#include "memLkRpt.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

//int ComputeSHA1( const char* pszPathFile )
//{
//    unsigned char ibuf[] = "compute sha1";
//    unsigned char obuf[20];
//
//    SHA1(ibuf, strlen((const char*)ibuf), obuf);
//
//    int i;
//    for (i = 0; i < 20; i++) {
//        printf("%02x ", obuf[i]);
//    }
//    printf("\n");
//
//    return 0;
//}

////////////////////////////////////////////////////////////////////////////////////////////////////

int ComputeSHA256_File( const char* pszPathFile, char* pResultBuffer, int iResultBufferLen )
{
	unsigned char hash[SHA256_DIGEST_LENGTH];
	int iRetVal = ComputeSHA256_File_Raw( pszPathFile, hash, SHA256_DIGEST_LENGTH );
	if (iRetVal == 0 && iResultBufferLen >= 65)
	{
		//	sha256_hash_string(hash, output);
			int i = 0;	// convert hash to series of 2-digit byte
			for (; i < SHA256_DIGEST_LENGTH; i++)
			{	sprintf_s( pResultBuffer + (i*2), iResultBufferLen - (i*2), "%02x", hash[i] );
			}
			pResultBuffer[64] = 0;
	}
	return iRetVal;
}


int ComputeSHA256_File_Raw( const char* pszPathFile, unsigned char* hash /*pResultBuffer*/, int iHashLen )
{

// perform checks on file existence
//	if (iResultBufferLen >= 65)
	if (iHashLen >= SHA256_DIGEST_LENGTH)
	{

		FILE* file = NULL;
		int ErrorCode;

		try
		{
			//file = fopen( pszPathFile, "rb" );
			ErrorCode = fopen_s( &file, pszPathFile, "rb");
			if (!file) return -1;

//			unsigned char hash[SHA256_DIGEST_LENGTH];
			SHA256_CTX sha256;
			SHA256_Init(&sha256);
			const int bufSize = 32768;
			char* buffer = (char*) malloc(bufSize);
			int bytesRead = 0;
			if (!buffer) return -1;
			bytesRead = fread(buffer, 1, bufSize, file);
			while (bytesRead > 0)
			{	SHA256_Update(&sha256, buffer, bytesRead);
				bytesRead = fread(buffer, 1, bufSize, file);
			}
			SHA256_Final(hash, &sha256);

//		//	sha256_hash_string(hash, output);
//			int i = 0;	// convert hash to series of 2-digit byte
//			for (; i < SHA256_DIGEST_LENGTH; i++)
//			{	sprintf_s( pResultBuffer + (i*2), iResultBufferLen - (i*2), "%02x", hash[i] );
//			}
//			pResultBuffer[64] = 0;

			fclose(file);
			free(buffer);
		}
	//	catch(CException e) {
	//		BEMMessageBox( "Unexpected error loading symbolic file list." );
	//	}
		catch( ... )
		{	//assert( FALSE );
			//VERIFY( BEMPX_WriteLogFile( "ComputeSHA256_File():  Unknown error generating has (SHA-256) of file.", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ ) );
			//	if (!bSilent)
			//		BEMMessageBox( "Unknown error generating compliance report." );
		}
	}

	return 0;
}

int ComputeSHA256_Compare( const char* pszPathFile, const char* pBufferToCompare )
{
	assert( strlen( pBufferToCompare ) == 64 );
	int iRetVal = -1;
	char pThisFileHash[65];
	if (pBufferToCompare == NULL || strlen( pBufferToCompare ) != 64)
		iRetVal = 1;
	else
	{	int iFileSHARetVal = ComputeSHA256_File( pszPathFile, pThisFileHash, 65 );
		if (iFileSHARetVal != 0)
			iRetVal = 2;
		else if (strlen( pThisFileHash ) != 64)
			iRetVal = 3;
		else
			iRetVal = (strncmp( pBufferToCompare, pThisFileHash, 64 )!=0 ? 4 : 0);
	}
	return iRetVal;
}


int CMX_GenerateFileHashesFromCSV( const char* pszHashFileListCSVPathFile, const char* pszHashOutputPathFile, const char* pszDefaultPath /*=NULL*/ )  // SAC 9/2/13
{	int iRetVal = 0;
	int iNumFilesHashed = 0;
	std::ifstream in( pszHashFileListCSVPathFile );
	if (!in.is_open())
	{	//if (pszErrorMsg && iErrorMsgLen > 0)
		//	sprintf_s( pszErrorMsg, iErrorMsgLen, "Error opening batch definitions file:  %s", pszBatchPathFile );
		iRetVal = -1;
	}
	else
	{	std::string sOutputPathFile = pszHashOutputPathFile;
		std::string sOverwriteFileMsg = boost::str( boost::format( "The file hash output file '%s' is opened in another application.  This file must be closed in that "
													"application before an updated file can be written.\n\nSelect 'Retry' to update the file "
													"(once the file is closed), or \n'Abort' to abort the hash generation." ) % sOutputPathFile.c_str() );
		if (!OKToWriteOrDeleteFile( sOutputPathFile.c_str(), sOverwriteFileMsg.c_str() ))
		{	//if (pszErrorMsg && iErrorMsgLen > 0)
			//	sprintf_s( pszErrorMsg, iErrorMsgLen, "Unable to write to file hash output file:  %s", sOutputPathFile );
			iRetVal = -2;
		}
		else
		{	if (FileExists( sOutputPathFile.c_str() ))  // add some separation between previous and new batch runs
			{	BEMPX_WriteLogFile( " ", sOutputPathFile.c_str(), FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
				BEMPX_WriteLogFile( " ", NULL, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
				BEMPX_WriteLogFile( "------------------------------", NULL, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			}
			BEMPX_WriteLogFile( "Initiating file hash generation...", sOutputPathFile.c_str(), FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
		}
	}

   if (iRetVal == 0)
	{	std::string line;
		std::string sLogMsg, sDefaultPath = pszDefaultPath;
		int iNumFileHashErrors = 0;
		bool bEndEncountered = false;
		char pHashBuffer[65];
		while (iRetVal == 0 && !bEndEncountered && getline( in, line ))
		{	std::vector<std::vector<std::string> > lines;
			ParseCSV( line, lines );
			assert( lines.size()==1 );
			if (lines.size() > 0)
			{	if (lines[0][0].size() > 3 && lines[0][0][0] < 0 && lines[0][0][1] < 0 && lines[0][0][2] < 0 && lines[0][0][3] > 0)
					lines[0][0] = lines[0][0].erase( 0, 3 );		// SAC 5/9/17 - blast bogus chars prior to usable record data (possibly resulting from Excel save in 'CSV UTF-8' format)
				if (lines[0][0].find(';') == 0)
				{	// comment line - do nothing
				}
				else
				{	std::string sChkFile = lines[0][0];
					if (!sChkFile.compare("END"))
						bEndEncountered = true;
					else
					{	if (sDefaultPath.length() > 0)
							PrependPathIfNecessary( sChkFile, sDefaultPath );
				//		sOverwriteFileMsg = boost::str( boost::format( "The CSV file '%s' is opened in another application.  This file must be closed in that "
				//													"application before an updated file can be written.\n\nSelect 'Retry' to update the file "
				//													"(once the file is closed), or \n'Cancel' to abort the batch processing." ) % sBatchResultsFN );
				//		if (!OKToWriteOrDeleteFile( sBatchResultsFN.c_str(), sOverwriteResultsFileMsg.c_str() ))
				//		{			iMode = -3;
				//					sLogMsg = boost::str( boost::format( "Error:  Unable to write to batch results file specified in record %d:  '%s'" )
				//																		% iBatchRecNum % sBatchResultsFN.c_str() );
				//		}
				//		else

						int iSHA256_RetVal = ComputeSHA256_File( sChkFile.c_str(), pHashBuffer, 65 );
						if (iSHA256_RetVal != 0)
						{	sLogMsg = boost::str( boost::format( ",\"%s\",ComputeSHA256_File() error: %d" ) % sChkFile.c_str() % iSHA256_RetVal );
							iNumFileHashErrors++;
						}
						else if (strlen( pHashBuffer ) != 64)
						{	sLogMsg = boost::str( boost::format( ",\"%s\",ComputeSHA256_File() error - return string too short: %d" ) % sChkFile.c_str() % strlen( pHashBuffer ) );
							iNumFileHashErrors++;
						}
						else
						{	sLogMsg = boost::str( boost::format( ",\"%s\",\"%s\"" ) % sChkFile.c_str() % pHashBuffer );
							iNumFilesHashed++;
						}
						BEMPX_WriteLogFile( sLogMsg.c_str(), NULL, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
					}
				}
			}
		}
	}
	if (iRetVal == 0 && iNumFilesHashed > 0)
		iRetVal = iNumFilesHashed;

	return iRetVal;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
