/**********************************************************************
 *  Copyright (c) 2012-2016, California Energy Commission
 *  Copyright (c) 2012-2016, Wrightsoft Corporation
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

#pragma warning(disable : 4127)
#include <QtXml/qdom.h>
#include <QtCore/qfile.h>
#include <QtCore/qiodevice.h>
#include <QtCore/qtextstream.h>
#include <QtCore/QXmlStreamWriter>
#include <QtCore/QXmlStreamReader>
#pragma warning(default : 4127)


////////////////////////////////////////////////////////////////////////////////
// OpenSSL includes:
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

// sample code from OpenSSL docu:
//		Read Base64 encoded data from standard input and write the decoded data to standard output:
//			BIO *bio, *b64, *bio_out;
//			char inbuf[512];
//			int inlen;
//
//			b64 = BIO_new(BIO_f_base64());
//			bio = BIO_new_fp(stdin, BIO_NOCLOSE);
//			bio_out = BIO_new_fp(stdout, BIO_NOCLOSE);
//			BIO_push(b64, bio);
//			while((inlen = BIO_read(b64, inbuf, 512)) > 0) 
//			        BIO_write(bio_out, inbuf, inlen);
//
//			BIO_flush(bio_out);
//			BIO_free_all(b64);

long CMX_EncodeBase64( const unsigned char *input, int length, char* output, int outLength, bool bSecure )
{
	char* inpCrypt = (char*) malloc( length );
	memcpy( inpCrypt, input, length );
	if (bSecure)
		CM_CryptEncode( inpCrypt, length );

	BIO *bmem,*b64 = NULL;
	BUF_MEM *bptr;
	b64 = BIO_new(BIO_f_base64());
	bmem = BIO_new(BIO_s_mem());
	b64 = BIO_push(b64,bmem);
	BIO_write(b64,inpCrypt,length);
	BIO_flush(b64);
	BIO_get_mem_ptr(b64,&bptr);

	long iRetVal = (long) bptr->length;
	if (outLength < iRetVal)
		iRetVal = -1;  // output buffer too small
	else
	{	memcpy(output,bptr->data,bptr->length-1);
		output[bptr->length-1] = 0;
	}
//	char *buff = (char *)malloc(bptr->length);
//	memcpy(buff,bptr->data,bptr->length-1);
//	buff[bptr->length-1] = 0;

	BIO_free_all(b64);
	free( inpCrypt );
//	return buff;
	return iRetVal;
}

int CMX_DecodeBase64( char* outData, const char* inData, bool bSecure )
{	int iRetVal = 0;
	int length = strlen(inData);

	BIO *bmem = BIO_new_mem_buf( (void*)inData, length );
	BIO *b64 = BIO_new(BIO_f_base64());
	BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
	bmem = BIO_push(b64, bmem);
	long n = BIO_read(bmem, outData, length);
	if (n > 0 && n <= length)
		iRetVal = n;
	else
		outData[0] = 0; // note: this is an error state.
	BIO_free_all(bmem);

	if (iRetVal > 0 && iRetVal <= length)
	{	if (bSecure)
			CM_CryptDecode( outData, iRetVal );
		outData[iRetVal] = 0;
	}

	return iRetVal;
}

bool DecodeBase64ToFile( const char* outFileName, const char* inData )
{	int length = strlen(inData);
	char *outData = (char*) malloc(length+1);

//	int iDecodeRetVal = (length > 0 && DecodeBase64( res, inData ));
	BIO *bmem = BIO_new_mem_buf( (void*)inData, length );
	BIO *b64 = BIO_new(BIO_f_base64());
	BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
	bmem = BIO_push(b64, bmem);
	long n = BIO_read(bmem, outData, length);
	if (n > 0 && n <= length)
#pragma warning(disable:4996)
	{	FILE* pOutFile = fopen( outFileName, "wb" );
		if (pOutFile == NULL)
			n = -1;
		else
		{
			fwrite( outData, sizeof(char), n, pOutFile );
			fflush( pOutFile );
			fclose( pOutFile );
	}	}
#pragma warning(default:4996)
	else
	{	outData[0] = 0; // note: this is an error state.
		n = -2;
	}

	BIO_free_all(bmem);
	free(outData);
	return (n > 0);
}


bool DecodeBase64_ORIGINAL_VERSION( const char* outFileName, const char* data )
{	bool bRetVal = true;
	int length = strlen(data);
	char *res = (char*) malloc(length+1);
	BIO *bmem = BIO_new_mem_buf( (void*)data, length );
	BIO *b64 = BIO_new(BIO_f_base64());
	BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
	bmem = BIO_push(b64, bmem);

	long n = BIO_read(bmem, res, length);
	if (n > 0 && n <= length)
//		res[n] = 0;
// now write decoded data into output file
#pragma warning(disable:4996)
	{	FILE* pOutFile = fopen( outFileName, "wb" );
		if (pOutFile == NULL)
			bRetVal = false;
		else
		{
			fwrite( res, sizeof(char), n, pOutFile );
			fflush( pOutFile );
			fclose( pOutFile );
	}	}
#pragma warning(default:4996)
	else
	{	res[0] = 0; // note: this is an error state.
		bRetVal = false;
	}

	BIO_free_all(bmem);

	free(res);


/*
	// first write encoded data to temp file
	QString dataTempPathFile;
	FILE* pEncDataFile = NULL;
		try
		{
				TCHAR szTempFileName[MAX_PATH];  
				dataTempPathFile.clear();
				TCHAR lpTempPathBuffer[MAX_PATH];
				//  Gets the temp path env string (no guarantee it's a valid path).
				DWORD dwRetVal = GetTempPath( MAX_PATH, lpTempPathBuffer ); // buffer for path 
				if (dwRetVal > MAX_PATH || (dwRetVal == 0))
				{	assert( FALSE );
				}
				else
				{	//  Generates a temporary file name. 
					UINT uRetVal = GetTempFileName( lpTempPathBuffer, TEXT("pk"), // file name prefix
																					0, // create unique name
																					szTempFileName );
					if (uRetVal == 0)
					{	assert( FALSE );
					}
					else
					{	int iErrorCode = fopen_s( &pEncDataFile, szTempFileName, "wb" );
						if (iErrorCode != 0 || pEncDataFile == NULL)
						{	assert( FALSE );
							pEncDataFile = NULL;
						}
				}	}

				fprintf( pEncDataFile, data );

				if (pEncDataFile)
				{
					fflush( pEncDataFile );
					fclose( pEncDataFile );
					dataTempPathFile = szTempFileName;
				}
		}
		catch( ... )
		{
			assert( FALSE );
			bRetVal = false;
		}


// NOW decode input data into output file
	if (bRetVal)
	{
	BIO *bio, *b64, *bio_out;
	char inbuf[512];
	int inlen;

	b64 = BIO_new(BIO_f_base64());

//	bio = BIO_new_fp(stdin, BIO_NOCLOSE);
#pragma warning(disable:4996)
		pEncDataFile = fopen( dataTempPathFile.toLocal8Bit().constData(), "r" );
		if ((bio = BIO_new( BIO_s_file() )) == NULL)
		{	//	PEMerr(PEM_F_PEM_READ_PRIVATEKEY,ERR_R_BUF_LIB);
			assert( FALSE );
			bRetVal = false;
		}
		BIO_set_fp( bio, pEncDataFile, BIO_NOCLOSE );
#pragma warning(default:4996)

//	bio_out = BIO_new_fp( outFileName, BIO_NOCLOSE );  // stdout, BIO_NOCLOSE);
#pragma warning(disable:4996)
		FILE* pOutFile = fopen( outFileName, "wb" );
		if ((bio_out = BIO_new( BIO_s_file() )) == NULL)
		{	//	PEMerr(PEM_F_PEM_READ_PRIVATEKEY,ERR_R_BUF_LIB);
			assert( FALSE );
			bRetVal = false;
		}
		BIO_set_fp( bio_out, pOutFile, BIO_NOCLOSE );
#pragma warning(default:4996)

	BIO_push(b64, bio);
	while((inlen = BIO_read(b64, inbuf, 512)) > 0) 
	        BIO_write(bio_out, inbuf, inlen);

//	BIO_flush(bio_out);
//	BIO_free_all(b64);

		if (pOutFile)
		{	fflush( pOutFile );
			fclose( pOutFile );
		}
		else
			bRetVal = false;

		if (pEncDataFile)
			fclose( pEncDataFile );
		else
			bRetVal = false;

	BIO_free_all(b64);
	}

		if (!dataTempPathFile.isEmpty())  // delete encoded data file created above
		{	if (remove( dataTempPathFile.toLocal8Bit().constData() ) != 0 )
			{	assert( FALSE );	// error deleting file
		}	}
*/


	return bRetVal;
}

////////////////////////////////////////////////////////////////////////////////


bool ParseTitle24ReportXML( const char* xmlFileName, const char* pdfFileName, const char* rptElemName /*=NULL*/, BOOL bSupressAllMessageBoxes /*=FALSE*/ )
			//			QString& sRulesetFilename, BOOL bReturnRulesetFilename,
         //         int iMaxDBIDSetFailures, int* piDBIDSetFailures,  // SAC 5/12/00 - enable UI reporting of failed data setting
         //         BOOL bSupressAllMessageBoxes /*=FALSE*/,   // SAC 4/27/03 - added to prevent MessageBoxes during processing
         //         int* piObjIdxSetFailures /*=NULL*/, QStringList* psaDataSetFailures /*=NULL*/,   // SAC 7/10/03 - added to facilitate more informative error reporting
			//			BOOL bLogDurations /*=FALSE*/, BOOL bStoreData /*=TRUE*/,   // SAC 10/24/13 - added duration logging  // SAC 10/29/13 - added bStoreData
			//			int* piObjPropCounts /*=NULL*/, BEMStraightMap* pStraightMap,   // SAC 10/30/13 - added to facilitate bulk memory allocation of BEMObject & BEMProperty objects
			//			BEMComponentMap* pCompMap, BEMPropertyMap* pPropMap )
{	bool bRetVal = true;
	QString sFileName = xmlFileName;
	QFile file( sFileName );
	if (!file.open( QFile::ReadOnly | QFile::Text ))
		return false;
	else
	{
		QXmlStreamReader stream( &file );

		QString sRptElemName = rptElemName;
		if (sRptElemName.isEmpty())
			sRptElemName = "Report";
		QString sErrMsg;
		int iXMLElementCount = 0;
		bool bDoneProcessingFile = false, bFoundReport = false;
		QString sElemName;
		while (bRetVal && sErrMsg.isEmpty() && !bDoneProcessingFile && !stream.atEnd())
		{
			stream.readNext();
			if (stream.error())
			{	bRetVal = false;
				QString sErr = QObject::tr("Error: %1 in file '%2' at line %3, column %4")
															.arg(stream.errorString())
															.arg(xmlFileName)
															.arg(stream.lineNumber())
															.arg(stream.columnNumber());
				sErrMsg = sErr.toLocal8Bit().constData();
				//BEMMessageBox( (LPCSTR)sErr.toLocal8Bit().constData(), "BEMProc ReadXMLFile() Error", 3 /*error*/ );
			}
			else
			{
#ifdef _DEBUG
//				WriteTokenToLog( stream );
#endif
				switch (stream.tokenType())
				{	case QXmlStreamReader::NoToken               : assert( FALSE );   break;  // see what conditions we end up here
					case QXmlStreamReader::Invalid               : assert( FALSE );   break;  // see what conditions we end up here
					case QXmlStreamReader::StartElement          : {	iXMLElementCount++;
																						sElemName = stream.name().toLocal8Bit().constData();
																						if (iXMLElementCount == 1 && sElemName.compare("Title24", Qt::CaseInsensitive) != 0)
																						{	// ERROR - not a proper Title24 report XML file (??)
																							bRetVal = false;
																							sErrMsg = QString( "ERROR:  File not a Title24 analysis report, first element '%1' (expected 'Title24' on line %2):  %3" ).arg( sElemName, QString::number(stream.lineNumber()), xmlFileName );
																						}
																						else if (sElemName.compare("Title24", Qt::CaseInsensitive) == 0)
																						{	// do nothing here
																						}
																						else if (sElemName.compare(sRptElemName, Qt::CaseInsensitive) == 0)
																						{	// found Report element
																							bFoundReport = true;

						//																	QXmlStreamAttributes attribs = stream.attributes();
						//																	assert( attribs.size() == 0 );  // only element having attributes is 'RulesetFilename' processed (ignored) above
						//																	int iBEMClassIdx = BEMPX_GetDBComponentID( sElemName.toLocal8Bit().constData() );
						//																	int iBEMMapGroupID = -1;		// SAC 5/7/14
						//																	if (iBEMClassIdx < 1)
						//																		iBEMMapGroupID = FindOldCompMapGroupID( pCompMap, sElemName, lFileVersion, NULL );
						//																	if (iBEMClassIdx < 1 && iBEMMapGroupID < 0)
						//																	{	bRetVal = false;
						//																		sErrMsg = QString( "ERROR:  Invalid object type '%1' encountered on line %2 of SDDXML file:  %3" ).arg( sElemName, QString::number(stream.lineNumber()), xmlFileName );
						//																	}
						//																	else
						//																	{	if (bReturnRulesetFilename)
						//																			bDoneProcessingFile = true;  // if we have reached the point where a BEMBase object is being created, we are beyond where the ruleset filename should be specified
						//																		else
						//																			bRetVal = ReadXMLComponent( xmlFileName, stream, sElemName, iBEMClassIdx, bIsUserInputMode, iBEMProcIdx, sErrMsg, bStoreData, piObjPropCounts,
						//																													pStraightMap, lDBIDVersion, lFileVersion, pCompMap, pPropMap, &ivMapCompsCreated, iDBIDSetFailureIdx, iMaxDBIDSetFailures, piDBIDSetFailures, piObjIdxSetFailures, psaDataSetFailures );
						//																	}
																						}
																						else
																						{	// ignore data in other elements, such as:  Payload / SDDXML
																							QString sSkipElemName;
																							bool bSkippingElement = true;
																							while (bRetVal && sErrMsg.isEmpty() && !bDoneProcessingFile && !stream.atEnd() && bSkippingElement)
																							{
																								stream.readNext();
																								if (stream.error())
																								{	bRetVal = false;
																									QString sErr = QObject::tr("Error: %1 in file '%2' at line %3, column %4").arg(stream.errorString()).arg(xmlFileName).arg(stream.lineNumber()).arg(stream.columnNumber());
																									sErrMsg = sErr.toLocal8Bit().constData();
																									//BEMMessageBox( (LPCSTR)sErr.toLocal8Bit().constData(), "BEMProc ReadXMLFile() Error", 3 /*error*/ );
																								}
																								else
																								{	switch (stream.tokenType())
																									{	case QXmlStreamReader::EndElement	:	sSkipElemName = stream.name().toLocal8Bit().constData();
																																							if (sSkipElemName.compare(sElemName, Qt::CaseInsensitive) == 0)
																																								bSkippingElement = false;
																																							break;
																										default										:	break;
																								}	}
																							}	assert( !bSkippingElement );
																						}
																					}  break;
					case QXmlStreamReader::EndElement            :  {	if (sElemName.compare("Title24", Qt::CaseInsensitive) == 0 || sElemName.compare("Payload", Qt::CaseInsensitive) == 0 ||
																							 sElemName.compare("SDDXML" , Qt::CaseInsensitive) == 0 || sElemName.compare("Report" , Qt::CaseInsensitive) == 0)
																						{	// do nothing here
																						}
																						else
																						{	assert( FALSE );		// ever get here ?
																						}
																					}	break;  // see what conditions we end up here
					case QXmlStreamReader::Characters            :  //if (CharsAreAllSpaces( stream.text().toLocal8Bit().constData() ))
																					//{	siLastIndent = stream.text().length();
																					//	SetIndentString( ssLastIndentChars, siLastIndent );
																					//}
																					if (bFoundReport)
																					{	QString sPDFEncodedData = stream.text().toLocal8Bit().constData();

//  <Report id="Sign2">JVBERi0xL
																						if (!sPDFEncodedData.isEmpty())
																							bRetVal = DecodeBase64ToFile( pdfFileName, sPDFEncodedData.toLocal8Bit().constData() );

																						bFoundReport = false;
																						bDoneProcessingFile = true;  // once we have found & saved the PDF report, bail
																					}
																					break;
					case QXmlStreamReader::Comment               :  assert( FALSE );   break;  // see what conditions we end up here
					case QXmlStreamReader::DTD                   :  assert( FALSE );   break;  // see what conditions we end up here
					case QXmlStreamReader::EntityReference       :  assert( FALSE );   break;  // see what conditions we end up here
					case QXmlStreamReader::ProcessingInstruction :  assert( FALSE );   break;  // see what conditions we end up here
					case QXmlStreamReader::StartDocument         :
					case QXmlStreamReader::EndDocument           :  break;   // ignore these
					default                                      :  assert( FALSE );   break;  // see what conditions we end up here
				}
				//int iHere = 0;
			}
		}

//#ifdef _DEBUG
		if (!bRetVal && sErrMsg.isEmpty())
		{	QString sErr = QObject::tr("%1\nLine %2, column %3")
														.arg(stream.errorString())
														.arg(stream.lineNumber())
														.arg(stream.columnNumber());
			sErrMsg = sErr.toLocal8Bit().constData();
			//BEMMessageBox( (LPCSTR)sErr.toLocal8Bit().constData(), "BEMProc ReadXMLFile() Error", 3 /*error*/ );
		}
//#endif

		if (!sErrMsg.isEmpty())
      {  BEMPX_WriteLogFile( sErrMsg, NULL, FALSE, bSupressAllMessageBoxes );  // SAC 4/27/03
         if (!bSupressAllMessageBoxes)
            BEMMessageBox( sErrMsg, NULL, 2 /*warning*/ );
		}
	}
//	siLastIndent = -1;
//	ssLastIndentChars.clear();

	return bRetVal;
}