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

/***************************************************************************
 *   RASent Solutions use of curl to implement reporting client for CBECC
 *   Thank you Daniel Stenberg for the original example code -  your documentation is a pleasure to read!
 *   Original code at: http://curl.haxx.se
 ***************************************************************************/

#include "stdafx.h"

#ifdef CECRPTGEN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//CURL #include <curl/curl.h>
//CURL #include <conio.h>
#include <windows.h>

#include "..\BEMProc\BEMProc.h"
#include "BEMCmpMgr.h"
#include "BEMCM_I.h"

// OpenSSL includes:
#include <openssl/bio.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h> 
#include <openssl/evp.h>
#include <openssl/aes.h>
#pragma warning(disable:4996)
#include <openssl/applink.c>
#pragma warning(default:4996)
//CURL #include <curl/curl.h>
#include "memLkRpt.h"

#define ChunkSize 65536

/* Take bineary input and pump out hexidecimal equivalent */
char BinHex(int nib)
{
	char BinChr;
	switch (nib)
	{	case 0:	BinChr = '0'; break;
		case 1:	BinChr = '1'; break;
		case 2:	BinChr = '2'; break;
		case 3:	BinChr = '3'; break;
		case 4:	BinChr = '4'; break;
		case 5:	BinChr = '5'; break;
		case 6:	BinChr = '6'; break;
		case 7:	BinChr = '7'; break;
		case 8:	BinChr = '8'; break;
		case 9:	BinChr = '9'; break;
		case 10:	BinChr = 'A'; break;
		case 11:	BinChr = 'B'; break;
		case 12:	BinChr = 'C'; break;
		case 13:	BinChr = 'D'; break;
		case 14:	BinChr = 'E'; break;
		case 15:	BinChr = 'F'; break;
		default:	BinChr='X';	break;
	}
	return BinChr;
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}


////////////////////////////////////////////////////////////////////////////////

static char sszKeyTrans[1024];

//	bool ConvertBinHex( QString& sHexStr, unsigned char* pBinData, int iLen )
//	{	bool bBHRetVal = true;
//										unsigned char EightBits;
//										char Hex1, Hex2;
//										int MSnib, LSnib;
//										int iTransLen = 0;
//										// for each binary byte write out two hex characters
//										for(int i=0; (iTransLen < 1022 && i < iLen); i++)
//										{	// first byte
//											EightBits = pBinData[i]; 
//											MSnib=(EightBits>>4)&0xF;  LSnib=(EightBits&0xF);
//											Hex1=BinHex(MSnib);
//											Hex2=BinHex(LSnib);
//	
//											//printf("%c%c",Hex1,Hex2);
//											sszKeyTrans[iTransLen++] = char(Hex1);
//											sszKeyTrans[iTransLen++] = char(Hex2);
//										}
//										if (iTransLen >= 1022)
//										{	//sErrMsg = "Error - string too long for BinHex conversion.";
//											bBHRetVal = false;
//										}
//										else
//										{	sszKeyTrans[iTransLen++] = '\0';
//											sHexStr = sszKeyTrans;
//										}
//		return bBHRetVal;
//	}

bool ConvertBinHex( QString& str )
{	bool bBHRetVal = true;
									unsigned char EightBits;
									char Hex1, Hex2;
									int MSnib, LSnib;
									int iTransLen = 0;
									// for each binary byte write out two hex characters
									for(int i=0; (iTransLen < 1022 && i < str.length()); i++)
									{	// first byte
										EightBits = str[i].toLatin1(); 
										MSnib=(EightBits>>4)&0xF;  LSnib=(EightBits&0xF);
										Hex1=BinHex(MSnib);
										Hex2=BinHex(LSnib);

										//printf("%c%c",Hex1,Hex2);
										sszKeyTrans[iTransLen++] = char(Hex1);
										sszKeyTrans[iTransLen++] = char(Hex2);
									}
									if (iTransLen >= 1022)
									{	//sErrMsg = "Error - string too long for BinHex conversion.";
										bBHRetVal = false;
									}
									else
									{	sszKeyTrans[iTransLen++] = '\0';
										str = sszKeyTrans;
									}
	return bBHRetVal;
}

bool RetrievePublicPrivateKeys( QString sSecKeyRulelistName, QString& sRptPubKey, QString& sRptPrvKey, QString* psRptPubHexKey, QString* psRptPrvHexKey, QString& sErrMsg,
											QString* psPrvKeyTempPathFile )
{	bool bPPKRetVal = false;
	int iError;

		FILE* pPrvKeyFile = NULL;
		try
		{
				TCHAR szTempFileName[MAX_PATH];  
				if (psPrvKeyTempPathFile)
				{	psPrvKeyTempPathFile->clear();
					TCHAR lpTempPathBuffer[MAX_PATH];
					//  Gets the temp path env string (no guarantee it's a valid path).
					DWORD dwRetVal = GetTempPath( MAX_PATH, lpTempPathBuffer ); // buffer for path 
					if (dwRetVal > MAX_PATH || (dwRetVal == 0))
					{	assert( FALSE );
					}
					else
					{	//  Generates a temporary file name. 
						UINT uRetVal = GetTempFileName( lpTempPathBuffer, TEXT("pk") /*file name prefix*/, 0 /*create unique name*/, szTempFileName );
						if (uRetVal == 0)
						{	assert( FALSE );
						}
						else
						{	int iErrorCode = fopen_s( &pPrvKeyFile, szTempFileName, "wb" );
							if (iErrorCode != 0 || pPrvKeyFile == NULL)
							{	assert( FALSE );
								pPrvKeyFile = NULL;
							}
				}	}	}

				int prvKeyLen = sRptPrvKey.length();				assert( prvKeyLen == 64 );
				char* prvKey = (char*) malloc( prvKeyLen+1 );
				memcpy( prvKey, sRptPrvKey.toLocal8Bit().constData(), prvKeyLen );		prvKey[prvKeyLen]=0;
				CM_CharSwap( prvKey, prvKeyLen );
				sRptPrvKey = prvKey + QString("\n");
				free( prvKey );

						if (CMX_EvaluateRuleset( sSecKeyRulelistName.toLocal8Bit().constData(), FALSE /*never log evaluation of these rules ?? / bVerbose / bLogRuleEvaluation*/, FALSE /*bTagDataAsUserDefined*/, FALSE /*never verbose evaluation of these rules ?? / bVerboseOutput*/ ))
						{	long lDBID_RptPrvKey = BEMPX_GetDatabaseID( "Proj:RptPrvKey" );		assert( lDBID_RptPrvKey > 0 );
							long lDBID_RptPubKey = BEMPX_GetDatabaseID( "Proj:RptPubKey" );		assert( lDBID_RptPubKey > 0 );
		//					if (pPrvKeyFile)
		//						fprintf( pPrvKeyFile, "-----BEGIN RSA PRIVATE KEY-----\n" );
							if (lDBID_RptPrvKey > 0 && lDBID_RptPubKey > 0)
							{	QString sKeyTemp;
								int i, iPrvKeyStrIdx = 0;
								while (BEMPX_GetString(  lDBID_RptPrvKey + iPrvKeyStrIdx++, sKeyTemp ) && !sKeyTemp.isEmpty())
								{	sRptPrvKey += (sKeyTemp + QString("\n"));
		//							if (pPrvKeyFile)
		//								fprintf( pPrvKeyFile, "%s\n", sKeyTemp.toLocal8Bit().constData() );
								}
								int iPubKeyStrIdx = 0;
								while (BEMPX_GetString(  lDBID_RptPubKey + iPubKeyStrIdx++, sKeyTemp ) && !sKeyTemp.isEmpty())
									sRptPubKey += (sKeyTemp + QString("\n"));		// sKeyTemp;
								if (!sRptPrvKey.isEmpty() && !sRptPubKey.isEmpty())
								{
									sRptPrvKey  = "-----BEGIN RSA PRIVATE KEY-----\n" + sRptPrvKey;
									sRptPrvKey += "-----END RSA PRIVATE KEY-----";
									if (pPrvKeyFile)
										fprintf( pPrvKeyFile, sRptPrvKey.toLocal8Bit().constData() );
		//								fprintf( pPrvKeyFile, "-----END RSA PRIVATE KEY-----" );
							//		sRptPubKey  = "-----BEGIN PUBLIC KEY-----\n" + sRptPubKey;
							//		sRptPubKey += "-----END PUBLIC KEY-----";
	// 9/16/13								sRptPubKey  = "\n-----BEGIN PUBLIC KEY-----\n" + sRptPubKey;
									sRptPubKey  = "-----BEGIN PUBLIC KEY-----\n" + sRptPubKey;
									sRptPubKey += "-----END PUBLIC KEY-----";
					// don't replace original private/public key strings until/unless document signing successful
					//				pszPrivateKey = (const char*) sRptPrvKey;
					//				pszPublicKey  = (const char*) sRptPubKey;
								}
								for (i=0; i<iPrvKeyStrIdx; i++)
									BEMPX_DefaultProperty( lDBID_RptPrvKey + i, iError );	// blast keys immediately after retrieving them from BEMBase
								for (i=0; i<iPubKeyStrIdx; i++)
									BEMPX_DefaultProperty( lDBID_RptPubKey + i, iError );

								bPPKRetVal = true;
								if (psRptPrvHexKey)
								{	*psRptPrvHexKey = sRptPrvKey;
									if (!ConvertBinHex( *psRptPrvHexKey ))
									{	bPPKRetVal = false;
										sErrMsg = "Error - private key too long for BinHex conversion.";
									}
								}
								if (psRptPubHexKey)
								{	*psRptPubHexKey = sRptPubKey;
									if (!ConvertBinHex( *psRptPubHexKey ))
									{	bPPKRetVal = false;
										sErrMsg = "Error - public key too long for BinHex conversion.";
									}
								}
							}
							else
								sErrMsg = "Error retrieving public/private key database IDs.";
						}
						else
							//BEMPX_WriteLogFile( "GenerateReport_CEC():  Error evaluating 'SetReportKeys' rulelist.", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
							sErrMsg = "Error evaluating 'SetReportKeys' rulelist.";


				if (pPrvKeyFile)
				{
					fflush( pPrvKeyFile );
					fclose( pPrvKeyFile );
					*psPrvKeyTempPathFile = szTempFileName;
				}

		}
		catch( ... )
		{
			assert( FALSE );
		}

	if (psPrvKeyTempPathFile && psPrvKeyTempPathFile->isEmpty())
		BEMPX_WriteLogFile( "Error:  Unable to write security key file to disk prior to report generation.", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );

	return bPPKRetVal;
}

bool CMX_RetrievePublicKey( QString sSecKeyRulelistName, bool bConvertBinHex, QString& sRptPubKey, QString& sErrMsg )
{	QString sRptPrvKey, sRptPubHexKey;

//  ??? SecurityKeyIdx already set ???

	bool bRetVal = RetrievePublicPrivateKeys( sSecKeyRulelistName, sRptPubKey, sRptPrvKey, &sRptPubHexKey, NULL, sErrMsg, NULL );
	if (bConvertBinHex)
		sRptPubKey = sRptPubHexKey;
	return bRetVal;
}


////////////////////////////////////////////////////////////////////////////////

int spc_sign(unsigned char *msg, unsigned int mlen, unsigned char *out,
             unsigned int *outlen, RSA *r) {
  unsigned char hash[20];
   
  if (!SHA1(msg, mlen, hash)) return 0;
  return RSA_sign(NID_sha1, hash, 20, out, outlen, r);
}


//Signs and verifies using existing PEM files
bool SignXML(char *szXmldata, char **signature_hex, const char* pszPrvKeyFN, bool /*bVerbose*/ )
{
	                    //     BEMMessageBox( "Signing Report XML", "" );
	//char * szXmlMsg = NULL;				//original xml data
	unsigned char* signature;			//sign value
	QString sErrMsg;
	char pErrBuffer[120]; 


//	FILE *fp_PrvKey;
//	int iErrorCode;
//	try
//	{	iErrorCode = fopen_s( &fp_PrvKey, "E:\\WSF\\PrvKey_Res-OpenSrc-write.pem", "w" );
//		if (iErrorCode != 0 || fp_PrvKey == NULL)
//		{	assert( FALSE );
//		}
//		else
//		{	fprintf( fp_PrvKey, "-----BEGIN RSA PRIVATE KEY-----\n" );
//			fprintf( fp_PrvKey, "-----END RSA PRIVATE KEY-----\n" );
//			fflush( fp_PrvKey );
//			fclose( fp_PrvKey );
//		}
//	}
//	catch( ... )
//	{	BEMMessageBox( "Unknown error writing PEM key file." );
//	}


//		unsigned int slen, verified;
//		RSA * rsaPrivKey = RSA_new();					//RSA Private Key
//		RSA * rsaPubKey  = RSA_new();					//RSA Pulic Key
//	
//		size_t pub_len;						// Length of public key
//		unsigned char	*pub_key;           // Public key
//	
//		FILE* pubKey = NULL;
//		FILE* privKey = NULL;
//	
//	//	privKey = fopen( "E:\\WSF\\PrvKey_Res-OpenSrc.pem", "r" );
//		privKey = fopen( "E:\\WSF\\PrvKey_Res-OpenSrc-write.pem", "r" );
//		if(privKey){
//	                rsaPrivKey = PEM_read_RSAPrivateKey(privKey, &rsaPrivKey, NULL,NULL);
//			}
//	
//		pubKey = fopen( "E:\\WSF\\PubKey_Res-OpenSrc.pem", "r" );
//		 ERR_print_errors_fp(stdout);
//	        if(pubKey)
//	        {
//	                rsaPubKey = PEM_read_RSA_PUBKEY(pubKey, &rsaPubKey, NULL, NULL);
//	        }
//			if (rsaPrivKey)
//			{

// we do not have PEM files on disk to read, we have key strings already read into memory,
// so replace the above code with the code below


		unsigned int slen;
		RSA * rsaPrivKey = NULL;					//RSA Private Key
		BIO *pbioPrv=NULL; 


#pragma warning(disable:4996)
//		FILE* privKey = fopen( "E:\\WSF\\PrvKey_Res-OpenSrc.pem", "r" );
		FILE* privKey = fopen( pszPrvKeyFN, "r" );
		if ((pbioPrv = BIO_new( BIO_s_file() )) == NULL)
		{
		//	PEMerr(PEM_F_PEM_READ_PRIVATEKEY,ERR_R_BUF_LIB);
	   //             return(0);
		}
		BIO_set_fp( pbioPrv, privKey, BIO_NOCLOSE );
#pragma warning(default:4996)


//	const char* pszRptPrvKey2 = 
//	"-----BEGIN RSA PRIVATE KEY-----\n"
//	"-----END RSA PRIVATE KEY-----\n";
//	
//			int iPrvKeyLen = strlen( pszRptPrvKey2 );
//			pbioPrv = BIO_new(BIO_s_mem());				assert( pbioPrv );
//			BUF_MEM* pBM = BUF_MEM_new(); 				assert( pBM );
//			if (!BUF_MEM_grow( pBM, iPrvKeyLen ))
//			{	assert(FALSE);
//			}
//			memcpy( pBM->data, pszRptPrvKey2, iPrvKeyLen );
//			BIO_set_mem_buf( pbioPrv, pBM, BIO_NOCLOSE );		// or end in:  0 /*not used*/);
//			BIO_set_mem_eof_return( pbioPrv, 0 );


//	pbioPrv = BIO_new_mem_buf( (void*) pszRptPrvKey, -1 );
//	BIO_set_mem_eof_return( pbioPrv, 0 );


//	if (pbioPrv == NULL)
//	{	//ERR_print_errors_fp(stdout);
//		ERR_error_string( ERR_get_error(), pErrBuffer ); 
//				sErrMsg.sprintf( "GenerateReport_CEC():  Data signing error - BIO_new_mem_buf() failure:  %s", pErrBuffer );
//	}
//	else
//	{	


//	if (bVerbose)
//	{	QString sDbg;	sDbg.sprintf( "SignXML() pbioPrv data:  method:type: %d  /method:name: '%s'  /init: %d  /shutdown: %d  /flags: %d  /retry_reason: %d  /num: %d  /references: %d  /num_read: %ul  /num_write: %ul",
//										pbioPrv->method->type, pbioPrv->method->name, pbioPrv->init, pbioPrv->shutdown, pbioPrv->flags, pbioPrv->retry_reason, pbioPrv->num, pbioPrv->references, pbioPrv->num_read, pbioPrv->num_write );
//		BEMPX_WriteLogFile( sDbg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
//	}


//		EVP_PKEY* pEVPKey = PEM_read_bio_PrivateKey( pbioPrv, NULL, NULL, NULL );
//		rsaPrivKey = EVP_PKEY_get1_RSA( pEVPKey );
//		EVP_PKEY_free( pEVPKey );

		rsaPrivKey = PEM_read_bio_RSAPrivateKey( pbioPrv, NULL, NULL, NULL );
		if (rsaPrivKey == NULL)
		{	//ERR_print_errors_fp(stdout);
			ERR_error_string( ERR_get_error(), pErrBuffer ); 
				sErrMsg.sprintf( "SignXML():  Data signing error - PEM_read_bio_RSAPrivateKey() failure:  %s", pErrBuffer );
		}
		else
		{

//	if (bVerbose)
//	{	QString sDbg;	sDbg.sprintf( "SignXML() rsaPrivKey data:  pad: %d  /version: %ld  /meth:name: '%s'", rsaPrivKey->pad, rsaPrivKey->version, rsaPrivKey->meth->name );
//		BEMPX_WriteLogFile( sDbg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
//	}

			signature = (unsigned char*) malloc( RSA_size( rsaPrivKey ) );
			if (!signature)
			{	sErrMsg.sprintf( "SignXML():  Error allocating signature of size %d", RSA_size( rsaPrivKey ) );
			}
			else
			{	unsigned char hash[SHA_DIGEST_LENGTH];
				if (!SHA1((unsigned char *)szXmldata, strlen(szXmldata), hash)) 
				{	//ERR_print_errors_fp(stdout);
					ERR_error_string( ERR_get_error(), pErrBuffer ); 
					sErrMsg.sprintf( "SignXML():  Data signing error - SHA1() failure:  %s", pErrBuffer );
				} 
				else if (!RSA_sign( NID_sha1, hash, SHA_DIGEST_LENGTH, signature, &slen, rsaPrivKey ))
				{	//ERR_print_errors_fp(stdout);
					ERR_error_string( ERR_get_error(), pErrBuffer ); 
					sErrMsg.sprintf( "SignXML():  Data signing error - RSA_sign() failure:  %s", pErrBuffer );
				}
				else
				{
		// bail on verification for now - would require RSA version of public key...
		//			/* do verify */
		//			if (RSA_verify(NID_sha1, hash, SHA_DIGEST_LENGTH, signature, slen,rsaPubKey))
		//				cout<<"Verify OK!"<<endl;
		//			else
		//				cout<<"Verify fail!"<<endl;
		//			/* end verify*/

#if 0	// enable to debug SHA1
					if (bVerbose)
					{	char szHashHex[SHA_DIGEST_LENGTH*2+1];
						for(int i = 0; i < SHA_DIGEST_LENGTH; i++)
							sprintf( &szHashHex[i*2], "%02x", hash[i] );
						QString sMsg;
						sMsg.sprintf("SignXML():  SHA1 %s", szHashHex);
						BEMPX_WriteLogFile( sMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
					}
#endif

					*signature_hex = (char *)malloc(slen * 2 + 1);
					if(*signature_hex)
					{
#pragma warning(disable:4996)
						for(int i = 0; i < (int) slen; i++)
							sprintf(*signature_hex + i * 2, "%02x", signature[i]);
#pragma warning(default:4996)
					}

	//				if (bVerbose)
	//					BEMPX_WriteLogFile( "GenerateReport_CEC():  Results data signature successfully generated.", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
				}
			
				free(signature);
			}
			RSA_free( rsaPrivKey );

		}

		if (privKey)
			fclose( privKey );
//	}


	if (!sErrMsg.isEmpty())
	{	BEMPX_WriteLogFile( sErrMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
	}

	return (sErrMsg.isEmpty());
}
//		//sign xml using sha1	
//		if(privKey){
//			signature = (unsigned char *) malloc(RSA_size(rsaPrivKey));
//			if(signature){
//				cout<<"-------Sign xml data-------"<<endl<<endl<<endl;
//				unsigned char hash[20];
//				/*do sign*/
//				if (!SHA1((unsigned char *)szXmldata, strlen(szXmldata), hash)) 
//				{
//					cout <<"SHA1 error"<<endl;
//					return false;
//				}
//				
//				if (RSA_sign(NID_sha1, hash, 20, signature, &slen, rsaPrivKey))
//				{
//					/* do verify */
//					if (RSA_verify(NID_sha1, hash, 20, signature, slen,rsaPubKey))
//						cout<<"Verify OK!"<<endl;
//					else
//						cout<<"Verify fail!"<<endl;
//					/* end verify*/
//	
//					*signature_hex = (char *)malloc(slen * 2 + 1);
//					if(*signature_hex)
//					{
//						for(int i = 0; i < slen; i++) sprintf(*signature_hex + i * 2, "%02x", signature[i]);
//					}
//	
//				}
//				/* end sign */
//				
//				free(signature);
//			}
//		}
//		
//		
//		fclose(pubKey);
//		fclose(privKey);
//		return true;
//	}


////////////////////////////////////////////////////////////////////////////////

//		Return Values:		0 =>	SUCCESS
//							 > 0 =>	Error Code:
//											 (see below)
int CMX_GenerateReport_CEC(	const char* pszXMLResultsPathFile, const char* pszCACertPath, const char* pszReportName,
										const char* pszAuthToken1, const char* pszAuthToken2, const char* pszSignature, const char* pszPublicKey, 
										const char* pszDebugBool, bool bVerbose /*=false*/, bool bSilent /*=false*/, bool bSchemaBasedRptGen /*=false*/ )   // SAC 11/20/18
{
	return GenerateReport_CEC(	pszXMLResultsPathFile, pszCACertPath, pszReportName, pszAuthToken1, pszAuthToken2,
										pszSignature, pszPublicKey, NULL /*pszRptPrvKey*/, NULL, NULL, "true" /*pszPDFOnlyBool*/, pszDebugBool, bVerbose, bSilent, false,
										NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, true, bSchemaBasedRptGen );
}

//		Return Values:		0 =>	SUCCESS
//							 > 0 =>	Error Code:
//											 (see below)
int  CMX_GenerateReport_Proxy_CEC(	const char* pszXMLResultsPathFile, const char* pszCACertPath, const char* pszReportName,
												const char* pszAuthToken1, const char* pszAuthToken2, const char* pszSignature, const char* pszPublicKey, 
												const char* pszProxyAddress, const char* pszProxyCredentials,		// pass NULLs for no proxy  
												const char* pszDebugBool, bool bVerbose /*=false*/, bool bSilent /*=false*/,
												const char* pszCompRptID /*=NULL*/, const char* pszRptGenServer /*=NULL*/, const char* pszRptGenApp /*=NULL*/,
												const char* pszRptGenService /*=NULL*/, const char* pszSecKeyRLName /*=NULL*/, const char* pszOutputPathFile /*=NULL*/,
												const char* pszProxyType /*=NULL*/, const char* pszNetComLibrary /*=NULL*/, bool bSchemaBasedRptGen /*=false*/ )	// SAC 11/5/15   // SAC 11/20/18
{
	return GenerateReport_CEC(	pszXMLResultsPathFile, pszCACertPath, pszReportName, pszAuthToken1, pszAuthToken2, pszSignature, 
										pszPublicKey, NULL /*pszRptPrvKey*/, pszProxyAddress, pszProxyCredentials, "true" /*pszPDFOnlyBool*/, pszDebugBool, bVerbose, bSilent, false,
										pszCompRptID, pszRptGenServer, pszRptGenApp, pszRptGenService, pszSecKeyRLName, pszOutputPathFile, pszProxyType, pszNetComLibrary, 0, true, bSchemaBasedRptGen );
}


//		Return Values:		0 =>	SUCCESS
//							 > 0 =>	Error Code:
//											 1 : XML file not found
//											 2 : CACert file not found
//											 3 : Error opening and/or reading the analysis results XML file
//											 4 : Error allocating memory for XML file storage
//											 5 : User chose not to overwrite output report file
//											 6 : Error opening report output file
//											 7 : Error reading analysis results XML file
//											 8 : Error reading analysis results XML file
//											 9 : Error initializing CURL (curl_easy_init() returned NULL)
//											10 : Report generation processing error in send request
//											11 : Report generation processing error in result retrieval
//											12 : No Report Name specified
//											13 : Missing or invalid PDF Only boolean string (must be 'true', 'false', 'both' or a Component:Property name (case insensitive))   - REVISED
//											14 : Missing or invalid report generation debug boolean string (must be 'true' or 'false' (case insensitive))
//											15 : Missing or invalid AuthToken1 string
//											16 : Missing or invalid AuthToken2 string
//											17 : Missing or invalid Signature string
//											18 : Missing or invalid PublicKey string
//											19 : Error opening output file following report generation
//											20 : Error reading data from output file following report generation
//											21 : PDF report contains XML data - likely error messages from web server
//											22 : XML Path not specified
//											23 : CACert path not specified
//											24 : CACertPath not a valid or found directory
//											25 : Error converting results file signature to hexidecimal
//											26 : Error extracting PDF from compliance report XML
int GenerateReport_CEC(	const char* pszXMLResultsPathFile, const char* pszCACertPath, const char* pszReportName,
										const char* pszAuthToken1, const char* pszAuthToken2, const char* pszSignature, const char* pszPublicKey, const char* pszPrivateKey, 
										const char* pszProxyAddress, const char* pszProxyCredentials, 		// pass NULLs for no proxy 
										const char* pszPDFOnlyBool, const char* pszDebugBool, bool bVerbose /*=false*/, bool bSilent /*=false*/, bool bSendSignature /*=false*/,
										const char* pszCompRptID /*=NULL*/, const char* pszRptGenServer /*=NULL*/, const char* pszRptGenApp /*=NULL*/,
										const char* pszRptGenService /*=NULL*/, const char* pszSecKeyRLName /*=NULL*/, const char* pszOutputPathFile /*=NULL*/,  // SAC 6/2/14  // SAC 10/9/14
										const char* pszProxyType /*=NULL*/, const char* pszNetComLibrary /*=NULL*/, long iSecurityKeyIndex /*=0*/, 	// SAC 11/5/15   // SAC 1/10/17
										bool bFinalPDFGeneration /*=true*/, bool bSchemaBasedRptGen /*=false*/ )		// SAC 11/20/18
{ 
				if (bVerbose)
				{	QString sFuncArgMsg;
					sFuncArgMsg.sprintf( "GenerateReport_CEC( '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', %s, %s, %s, '%s', '%s', '%s', '%s', '%s',\n                                           '%s', '%s', '%s', %s, %s )",
							(pszXMLResultsPathFile ? pszXMLResultsPathFile : "(null)"), (pszCACertPath ? pszCACertPath : "(null)"), (pszReportName ? pszReportName : "(null)"), (pszAuthToken1 ? pszAuthToken1 : "(null)"), (pszAuthToken2 ? pszAuthToken2 : "(null)"),
							(pszSignature ? pszSignature : "(null)"), (pszPublicKey ? "<PubKey>"/*pszPublicKey*/ : "(null)"), (pszPrivateKey ? "<PrvKey>"/*pszPrivateKey*/ : "(null)"), (pszProxyAddress ? pszProxyAddress : "(null)"), (pszProxyCredentials ? pszProxyCredentials : "(null)"),
							(pszPDFOnlyBool ? pszPDFOnlyBool : "(null)"), (pszDebugBool ? pszDebugBool : "(null)"), (bVerbose ? "true" : "false"), (bSilent ? "true" : "false"), (bSendSignature ? "true" : "false"), (pszCompRptID ? pszCompRptID : "(null)"),
							(pszRptGenServer ? pszRptGenServer : "(null)"), (pszRptGenApp ? pszRptGenApp : "(null)"), (pszRptGenService ? pszRptGenService : "(null)"), (pszSecKeyRLName ? pszSecKeyRLName : "(null)"),
							(pszOutputPathFile ? pszOutputPathFile : "(null)"), (pszProxyType ? pszProxyType : "(null)"), (pszNetComLibrary ? pszNetComLibrary : "(null)"), (iSecurityKeyIndex==0 ? "0" : ">0"), (bSchemaBasedRptGen ? "true" : "false") );
					BEMPX_WriteLogFile( sFuncArgMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
				}
	int iRetVal = 0;

	FILE *fp_xml = NULL;
	FILE *fp_Out = NULL;
  
	char FileOutName[MAX_PATH+1];		// SAC 9/25/16 - was: 256];  //, FileInName[256], CACertPath[256];
	char FileOutPDFName[MAX_PATH+1];		FileOutPDFName[0]='\0';
	int ErrorCode;  //, count;
	char buff[ChunkSize];
	char *postthis = NULL; // need to malloc (gasp!) to the filesize
	long int FileInSize = 0;
	long int nread = 0;
	int npost = 0;	// index into postthis
	//int FullFlag = 0;
	int i;	// loop counter
	bool bFileWritten = false;
	QString sLogMsg;

	QString sReportName = pszReportName;
	QString sPDFOnlyBool = pszPDFOnlyBool;
	QString sDebugBool = pszDebugBool;

	QString sCompRptID     = ((pszCompRptID      != NULL && strlen( pszCompRptID     ) > 0) ? pszCompRptID     : "BEES" );		// SAC 6/2/14
	QString sRptGenServer  = ((pszRptGenServer   != NULL && strlen( pszRptGenServer  ) > 0) ? pszRptGenServer  : "t24docs.com" );
	QString sRptGenApp     = ((pszRptGenApp      != NULL && strlen( pszRptGenApp     ) > 0) ? pszRptGenApp     : (sReportName.indexOf( "NRCC_" )==0 ? "ReportGeneratorCom2" : "ReportGeneratorRes2") );  // SAC 1/5/15 - was: "T24SoftwareReportingServiceDev" );  // SAC 8/31/17 - updated to Com/Res'2'
	QString sRptGenService = ((pszRptGenService  != NULL && strlen( pszRptGenService ) > 0) ? pszRptGenService : "ReportingService.svc" );
	QString sSecKeyRLName  = ((pszSecKeyRLName   != NULL && strlen( pszSecKeyRLName  ) > 0) ? pszSecKeyRLName  : (sReportName.indexOf( "NRCC_" )==0 ? "rl_SECURITYKEYS" : "SetReportKeys") );
	if (sReportName.indexOf("STD") > 0)		// SAC 11/13/15 - tweak output report filename for 'Std' reports
		sCompRptID += "-Std";

	bool bNetComCURL = false;	// SAC 11/5/15
	if (pszNetComLibrary && strlen( pszNetComLibrary ) > 0)
	{	std::string sNetComLibrary = pszNetComLibrary;
		bNetComCURL = (boost::iequals( sNetComLibrary, "CURL" ));
	}			assert( !bNetComCURL );		// CURL not implemented in open source version

	QString sXMLPathFile = pszXMLResultsPathFile;
	sXMLPathFile.replace( "\\", "/" );
//	QString sCACertPathFile, sCACertPath = pszCACertPath;
//	sCACertPath.replace( "\\", "/" );

//BEMMessageBox( QString( "Checking existence of results file: %1" ).arg( (sXMLPathFile.isEmpty() ? "(missing)" : sXMLPathFile) ) );

	if (sXMLPathFile.isEmpty())
	{	iRetVal = 22;				assert( FALSE );			//	22 : XMLResultsPathFile not specified
	}
	else if (!FileExists( sXMLPathFile ))
	{	iRetVal = 1;			assert( FALSE );			//	1 : XML file not found
	}

	long lRptIDNum = -1;		// SAC 8/24/17 - revise use of PDFOnlyBool argument to enable specification of a report ID number Component:Property name
	if (!sPDFOnlyBool.isEmpty() && sPDFOnlyBool.indexOf(':') > 0)
	{	long lDBID_RptIDNum = BEMPX_GetDatabaseID( sPDFOnlyBool.toLocal8Bit().constData() );			assert( lDBID_RptIDNum > 0 );
		if (lDBID_RptIDNum < BEM_COMP_MULT || !BEMPX_GetInteger( lDBID_RptIDNum, lRptIDNum, -1 ))
			lRptIDNum = -1;
	}

	if (iRetVal != 0)
	{	// do nothing
	}
	else if (sReportName.isEmpty())
		iRetVal = 12;
	else if (sPDFOnlyBool.isEmpty() || (lRptIDNum < 0 &&		// SAC 8/24/17
	                                    sPDFOnlyBool.compare("true", Qt::CaseInsensitive)!=0 && sPDFOnlyBool.compare("false", Qt::CaseInsensitive)!=0 && sPDFOnlyBool.compare("both", Qt::CaseInsensitive)!=0))  // SAC 7/14/17
		iRetVal = 13;
	else if (sDebugBool.isEmpty() || (sDebugBool.compare("true", Qt::CaseInsensitive)!=0 && sDebugBool.compare("false", Qt::CaseInsensitive)!=0))
		iRetVal = 14;
	else if (pszAuthToken1 == NULL || strlen( pszAuthToken1 ) < 1)
		iRetVal = 15;
	else if (pszAuthToken2 == NULL || strlen( pszAuthToken2 ) < 1)
		iRetVal = 16;
	else if (pszSignature == NULL || strlen( pszSignature ) < 1)
		iRetVal = 17;
	else if (pszPublicKey == NULL || strlen( pszPublicKey ) < 1)
		iRetVal = 18;
	else
	{	bool bPDFRpt=false, bXMLRpt=false, bSecRpts[4]={false,false,false,false}, bSingleRpt=false;
		if (lRptIDNum >= 0)
		{	bPDFRpt = (lRptIDNum & 2);		bSecRpts[0] = (lRptIDNum & 4);		bSecRpts[2] = (lRptIDNum & 16);
			bXMLRpt = (lRptIDNum & 1);		bSecRpts[1] = (lRptIDNum & 8);		bSecRpts[3] = (lRptIDNum & 32);
		}
		else
		{	bSingleRpt = true; 
			bPDFRpt = ((sPDFOnlyBool.compare("true",  Qt::CaseInsensitive) == 0 || sPDFOnlyBool.compare("both", Qt::CaseInsensitive) == 0) ? true : false);
			bXMLRpt = ((sPDFOnlyBool.compare("false", Qt::CaseInsensitive) == 0 || sPDFOnlyBool.compare("both", Qt::CaseInsensitive) == 0) ? true : false);
			if (sReportName.indexOf( "NRCC_" )==0)
			{	if (sReportName.indexOf( "STD" ) >= 0)
					lRptIDNum  = 4;
				else
				{	lRptIDNum  = (bPDFRpt ? 2 : 0);
					lRptIDNum += (bXMLRpt ? 1 : 0);
		}	}	}

		try
		{
	// code to collect private/public keys to perform digital signing...
			bool bSignData = false;
			QString sRptPrvKey, sRptPubKey, sRptPubHexKey, sPrvKeyPathFile;
//			if (false)
//			if (true)
			if (bSendSignature && (pszSignature == NULL || strlen( pszSignature ) < 6))
			{	if (!pszPrivateKey || strlen( pszPrivateKey ) < 70)
				{	if (!sSecKeyRLName.isEmpty())
					{
						BEMPX_SetBEMData( BEMPX_GetDatabaseID( "Proj:SecurityKeyIdx" ), BEMP_Int, (void*) &iSecurityKeyIndex );   // SAC 1/11/17
						QString sKeyErrMsg;
						sRptPrvKey = pszPrivateKey;  // now expected as input - SAC 1/10/17
						if (!RetrievePublicPrivateKeys( sSecKeyRLName, sRptPubKey, sRptPrvKey, &sRptPubHexKey, NULL, sKeyErrMsg, &sPrvKeyPathFile ))
						{	if (!sKeyErrMsg.isEmpty())
								sLogMsg.sprintf( "GenerateReport_CEC():  %s", sKeyErrMsg.toLocal8Bit().constData() );
							else
								sLogMsg = "GenerateReport_CEC():  Error retrieving public/private keys from BEMBase.";
							BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
						}
//#ifdef _DEBUG
//			sLogMsg.sprintf( "GenerateReport_CEC():  Public Key:\n%s", sRptPubKey );
//			BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
//			sLogMsg.clear();
//#endif
					}
				}

				if (!sRptPrvKey.isEmpty() && !sRptPubKey.isEmpty())
				{	bSignData = true;  // sign data w/ supplied public/private keys
					if (bVerbose)
						BEMPX_WriteLogFile( "GenerateReport_CEC():  Public/private keys necessary to sign results transmission successfully loaded.", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
				}
				else if (bVerbose)
					BEMPX_WriteLogFile( "GenerateReport_CEC():  Unable to retrieve public/private keys necessary to sign results transmission.", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			}

		/* XML file as input */
			ErrorCode = fopen_s( &fp_xml, sXMLPathFile.toLocal8Bit().constData(), "rb");		// SAC 6/4/13 - switched open flag to 'binary' mode to fix file size issue (in text mode, file size can be bogus)
			if (iRetVal == 0 && ErrorCode != 0)
			{	iRetVal = 3;
			}
		// NOTE:  fstat would be so cool - but not avaiable for this environment
			if (iRetVal == 0)  // && bVerbose)
			{	ErrorCode = fseek(fp_xml, 0L, SEEK_END);  // seek to the end for filesize info
				if (ErrorCode <0) {
					iRetVal = 3;
		//			fprintf(stderr,"Oops:  fseek returns %d\n", ErrorCode); 
		//			/* wait for a response from the keyboard */
		//			printf("Press any key to continue...");
		//			 _getch();
		//			return (-5);
				}  // fseek error
				FileInSize=ftell(fp_xml);
				fseek (fp_xml,0L, SEEK_SET);	// go back to the beginning
			}

		// // Debug
		//    printf_s("FileIn: %s has %d bytes\n", sXMLPathFile, FileInSize);

			if (iRetVal == 0)
	//		{  postthis = (char *) malloc(FileInSize*sizeof(char) + 1);
			{  postthis = (char *) malloc( (FileInSize)*sizeof(char) + 1);
			  if (postthis == NULL) {
					iRetVal = 4;
			//	  		fprintf(stderr,"Oops:  Asked for %d bytes but malloc returned NULL!\n", FileInSize); 
			//		/* wait for a response from the keyboard */
			//		printf("Press any key to continue...");
			//		 _getch();
			//		return (-6);
			  }
			}
 
		/* Create the Output File for response */
		// Shouldn't assume input is xml and output is .pdf
		// Debug
			if (iRetVal == 0)
			{
				QString sResPathFileNotExt = sXMLPathFile;
				if (sResPathFileNotExt.lastIndexOf('.') > 0)
					sResPathFileNotExt = sResPathFileNotExt.left( sResPathFileNotExt.lastIndexOf('.') );
		//		QString sRptFileExt = (bPDFOnly ? "pdf" : "xml");
				if (pszOutputPathFile && strlen( pszOutputPathFile ) > 0)	// SAC 10/9/14
				{	QString sOutPathFile = pszOutputPathFile;
					sOutPathFile.replace( '\\', '/' );  // replace backslashes w/ slashes to provide more universal compatibility
					int iLstOutDot   = sOutPathFile.lastIndexOf( '.' );
					int iLstOutSlash = sOutPathFile.lastIndexOf( '/' );
					if (iLstOutDot > iLstOutSlash)
					{	// file ext is specified
						QString sOutLast3 = sOutPathFile.right(3);
						if (sOutLast3.compare("pdf", Qt::CaseInsensitive) == 0 && bPDFRpt)
						{	// file ext is PDF (and PDF rpt requested)
							_snprintf_s( FileOutName,    MAX_PATH+1, MAX_PATH, "%s.xml", pszOutputPathFile );
							_snprintf_s( FileOutPDFName, MAX_PATH+1, MAX_PATH, "%s",     pszOutputPathFile );
						}
						else if (bPDFRpt)
						{	// file ext provided, but it is not PDF (despite PDF rpt being requested)
							if (sOutLast3.compare("xml", Qt::CaseInsensitive) == 0)
								_snprintf_s( FileOutName,    MAX_PATH+1, MAX_PATH, "%s",     pszOutputPathFile );
							else
								_snprintf_s( FileOutName,    MAX_PATH+1, MAX_PATH, "%s.xml", pszOutputPathFile );
							_snprintf_s(    FileOutPDFName, MAX_PATH+1, MAX_PATH, "%s.pdf", pszOutputPathFile );
						}
						else  // only XML requested, so use specified filename regardless of extension
							_snprintf_s( FileOutName, MAX_PATH+1, MAX_PATH, "%s", pszOutputPathFile );
					}
					else
					{	// NO file ext specified
						_snprintf_s(    FileOutName,    MAX_PATH+1, MAX_PATH, "%s.xml", pszOutputPathFile );
						if (bPDFRpt)
							_snprintf_s( FileOutPDFName, MAX_PATH+1, MAX_PATH, "%s.pdf", pszOutputPathFile );
				}	}
				else
				{	_snprintf_s(    FileOutName,    MAX_PATH+1, MAX_PATH, "%s-%s.xml", sResPathFileNotExt.toLocal8Bit().constData(), sCompRptID.toLocal8Bit().constData() );
					if (bPDFRpt)
						_snprintf_s( FileOutPDFName, MAX_PATH+1, MAX_PATH, "%s-%s.pdf", sResPathFileNotExt.toLocal8Bit().constData(), sCompRptID.toLocal8Bit().constData() );
				}

				//	if (pszReportType && (pszReportType[0] == 'f' || pszReportType[0] == 'F')) {    // (argv[3])[0]=='f') {
				//		//printf_s("Full Output\n");
				//		sprintf_s(FileOutName, "%s/%s-BEES.xml", pszXMLPath, pszXMLFileNoExt );  //argv[1], argv[2]);
				//		FullFlag=1;}
				//	else {
				//		//printf_s("Short Output\n");
				//		sprintf_s(FileOutName, "%s/%s-BEES.pdf", pszXMLPath, pszXMLFileNoExt );  //argv[1], argv[2]);
				//		FullFlag=0;}
			//// Debug
			//	printf_s("FileOutName: %s\n", FileOutName);
			}

//	BEMMessageBox( QString( "about to write rpt file:  %1" ).arg( FileOutName ) );
			if (iRetVal == 0)
			{	sLogMsg.sprintf( "The XML file '%s' is opened in another application.  This file must be closed in that "
			                "application before an updated file can be written.\n\nSelect 'Retry' to proceed "
								 "(once the file is closed), or \n'Abort' to abort the report generation.", FileOutName );
				if (!OKToWriteOrDeleteFile( FileOutName, sLogMsg, bSilent ))
				{	//sErrorMsg.sprintf( "ERROR:  User chose not to overwrite %s file:  %s", pszOutFileDescs[i], sOutFiles[i] );
					iRetVal = 5;
				}
			}

			if (iRetVal == 0)
			{	//	Here is where you read in the file chunk by chunk
				// build up the postthis array
				npost = 0;	// postthis index
				nread = (long) fread(buff, sizeof(char), ChunkSize, fp_xml);
				if (nread <=0) {
					iRetVal = 7;
				//	fprintf(stderr,"Oops: input file read %d bytes\n", nread);
				}
				else {
					for (i=0;i<nread;i++) { 
							postthis[i+npost] = buff[i];}
					}
				npost += nread;	//; update index into postthis
				if (npost >= FileInSize)		// SAC 3/19/20 - fix bug where SMALL results files not calculating hash properly due to lack of terminator on postthis
					postthis[npost]='\0';	// postthis needs to be NULL terminated; later usage in SignXML uses strlen() when calling SHA1
				// if we have more to read
				while (iRetVal == 0 && npost < FileInSize) { // we have more to read	
					nread = (long) fread(buff, sizeof(char), ChunkSize, fp_xml);
					if (nread <= 0) {
					//	fprintf(stderr,"input file read %d bytes - oops\n", nread);
						iRetVal = 8;
							// SAC 6/4/13 - (PERHAPS IN FUTURE) before we throw an error here, check to see if the file has a valid XML end marker and adjust FileInSize
					}
					 else {
						for (i=0;i<nread;i++) { 
							postthis[i+npost] = buff[i];
						}
					}
				 npost += nread;	// update index into postthis
				 postthis[npost]='\0';	// postthis needs to be NULL terminated; later usage in SignXML uses strlen() when calling SHA1
				}	// end while npost < FileInSize
			// Debug
			//	printf_s("size of postthis: %d bytes\n", npost);
			}

			assert( fp_xml || iRetVal > 0 );
			if (fp_xml)
				fclose( fp_xml );  // close XML file (finished reading it)
			fp_xml = NULL;

			QString sURL;
			if (iRetVal == 0)
			{
			// final step of signature/public key prep
				QString sSignHex;

	// SAC 10/14/13 - latest XMl signing/security stuff from RS ->
				char *signature_hex = 0; // rsa signature
				if (bSignData && SignXML( postthis, &signature_hex, sPrvKeyPathFile.toLocal8Bit().constData() /*sRptPrvKey*/, bVerbose ))
				{
					sSignHex = signature_hex;
#pragma warning(disable:4996)
				// now simple Bin->Hex of public key...
					int iRptPubKeyLen = sRptPubKey.length();
					char* pszRptPubKeyOrig = (char *)malloc( iRptPubKeyLen + 1 );
					if (pszRptPubKeyOrig)
					{	sprintf( pszRptPubKeyOrig, "%s", sRptPubKey.toLocal8Bit().constData() );
						char* pszRptPubKeyHex = (char *)malloc( iRptPubKeyLen * 2 + 1 );
						if(pszRptPubKeyHex)
						{	for(int iH = 0; iH < iRptPubKeyLen; iH++)
								sprintf( pszRptPubKeyHex + iH * 2, "%02x", pszRptPubKeyOrig[iH] );
							sRptPubHexKey = pszRptPubKeyHex;
							delete [] pszRptPubKeyHex;
						}
						delete [] pszRptPubKeyOrig;
					}
#pragma warning(default:4996)
				}
				if (signature_hex)
					delete [] signature_hex;

				if (!sPrvKeyPathFile.isEmpty())  // delete private key file
				{	if( remove( sPrvKeyPathFile.toLocal8Bit().constData() ) != 0 )
   					{	assert( FALSE );	// error deleting file
					}
				}

				//if (bVerbose)
				//{	if (!sRptPubHexKey.isEmpty())
				//		sLogMsg.sprintf( "GenerateReport_CEC():  hex-encoded public key:\n%s", sRptPubHexKey.toLocal8Bit().constData() );
				//	else
				//		sLogMsg.sprintf( "GenerateReport_CEC():  hex-encoded public key NOT COMPUTED" );
				//	BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
				//	if (!sSignHex.isEmpty())
				//		sLogMsg.sprintf( "GenerateReport_CEC():  hex-encoded signature:\n%s", sSignHex.toLocal8Bit().constData() );
				//	else
				//		sLogMsg.sprintf( "GenerateReport_CEC():  hex-encoded signature NOT COMPUTED" );
				//	BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
				//	sLogMsg.clear();
				//}

				if (sSignHex.isEmpty())
				{
					if (pszSignature && strlen( pszSignature ) > 0 && pszPublicKey && strlen( pszPublicKey ) > 0)
					{	sSignHex      = pszSignature;
						sRptPubHexKey = pszPublicKey;			assert( (strlen(pszSignature) < 5 && strlen(pszPublicKey) < 5) );  // shouldn't be here ??
					}
					else
					{	sSignHex      = "none";
						sRptPubHexKey = "none";
				}	}

				if (TRUE)	//bVerbose)
				{
					sLogMsg.sprintf( "  Generating report '%s' %s %s", pszReportName, (bPDFRpt && bXMLRpt ? "pdf+xml" : (bPDFRpt ? "pdf" : "xml")), (sSignHex.length() > 5 ? "(signed)" : " ") );
					BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
					sLogMsg.clear();
				}

         // URL setting moved down here from above
		//			sURL.sprintf( "https://%s/%s/%s/%s/%s/%s/%s/%s/%s/%s", sRptGenServer.toLocal8Bit().constData(), sRptGenApp.toLocal8Bit().constData(), sRptGenService.toLocal8Bit().constData(), 
		//								pszReportName, pszAuthToken1, pszAuthToken2, pszPDFOnlyBool, pszDebugBool, sSignHex.toLocal8Bit().constData(), sRptPubHexKey.toLocal8Bit().constData() );
		// SAC 7/14/17 - new URL scheme for single-pass report gen
		// SAC 8/24/17 - revised new scheme replacing bPDFRpt & bXMLRpt w/ an integer servings as bitwise flags for addiitonal reports
				if (lRptIDNum >= 0)
				{	if (bSchemaBasedRptGen)		// SAC 11/20/18 - report incompatibility of URL for CF1R XML schema-based report gen
					{	sLogMsg.sprintf( "  ERROR: CF1R XML schema-based report gen URL incompatible with RptIDNum >= 0 reports, generating report '%s' %s %s", pszReportName, (bPDFRpt && bXMLRpt ? "pdf+xml" : (bPDFRpt ? "pdf" : "xml")), (sSignHex.length() > 5 ? "(signed)" : " ") );
						BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
						sLogMsg.clear();
					}
					sURL.sprintf( "https://%s/%s/%s/%s/%s/%s/%ld/%s/%s", sRptGenServer.toLocal8Bit().constData(), sRptGenApp.toLocal8Bit().constData(), sRptGenService.toLocal8Bit().constData(), 
							pszReportName, pszAuthToken1, pszAuthToken2, lRptIDNum, /*pszDebugBool,*/ sSignHex.toLocal8Bit().constData(), sRptPubHexKey.toLocal8Bit().constData() );
				}
				else
					sURL.sprintf( "https://%s/%s/%s/%s/%s/%s/%s/%s/%s/%s", sRptGenServer.toLocal8Bit().constData(), sRptGenApp.toLocal8Bit().constData(), sRptGenService.toLocal8Bit().constData(), 
							pszReportName, pszAuthToken1, pszAuthToken2, (bPDFRpt ? "true" : "false"), (bXMLRpt ? "true" : "false"), /*pszDebugBool,*/ sSignHex.toLocal8Bit().constData(), sRptPubHexKey.toLocal8Bit().constData() );

				if (bVerbose)
				{	sLogMsg.sprintf( "GenerateReport_CEC():  web server URI:  %s", sURL.toLocal8Bit().constData() );
					BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
				}

// ------------------------
// --  Qt Communication  --
// ------------------------
							if (bVerbose)
								BEMPX_WriteLogFile( "    Communicating w/ report generator using Qt", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
					iRetVal = GenerateReportViaQt( FileOutName, sURL.toLocal8Bit().constData(), pszCACertPath, postthis, npost, pszProxyAddress, pszProxyCredentials,
																pszProxyType, NULL /*pszErrorMsg*/, 0 /*iErrorMsgLen*/, bVerbose );
			}

		// moved flush/close of output file down here and executed anytime the file exists, rather than only when CURL executed successfully - SAC 9/21/13
			if (/*res == CURLE_OK &&*/ fp_Out)
			{	fflush( fp_Out );
				fclose( fp_Out );
				fp_Out = NULL;
			}

		// CHECK FOR OUTPUT FILE NOT AN XML (if PDF requested)
			if (iRetVal == 0)   // && bPDFOnly)  - SAC 7/14/17
			{
				fp_Out = _fsopen( FileOutName, "rb", _SH_DENYNO /*_SH_DENYWR*/ );
				if (fp_Out==NULL) 
					iRetVal = 19;		//	19 : Error opening output file following report generation
				else
				{	nread = (long) fread( buff, sizeof(char), 20, fp_Out );  // first 20 chars of file should do it...
					if (nread < 20)
						iRetVal = 20;		//	20 : Error reading data from output file following report generation
			//		else					- SAC 7/14/17 - returned file is always XML
			//		{	buff[20] = '\0';
			//			QString sHdrText = buff;
			//			sHdrText = sHdrText.toLower();
			//			if (sHdrText.indexOf("xml") >= 0)
			//				iRetVal = 21;		//	21 : PDF report contains XML data - likely error messages from web server
			//		}
					fclose( fp_Out );
				}
			}

			// code to extract PDF from XML report - and delete the XML if full rpt not requested
			int iNumPDFsSaved=0;
			if (iRetVal == 0 && bFinalPDFGeneration)
			{	if (bSingleRpt)
				{	QString sXMLRptID = (lRptIDNum == 4 ? "Report3" : "Report2");
					if (!CMX_ExtractTitle24ReportFromXML( FileOutName, FileOutPDFName, sXMLRptID.toLocal8Bit().constData(), TRUE /*bSupressAllMessageBoxes*/ ))
						iRetVal = 26;		// Error extracting PDF from compliance report XML
					else
						iNumPDFsSaved++;
				}
				else
				{	if (bPDFRpt)
					// EXTRACT PDF from XML
					{	if (!CMX_ExtractTitle24ReportFromXML( FileOutName, FileOutPDFName, "Report2", TRUE /*bSupressAllMessageBoxes*/ ))
							iRetVal = 26;		// Error extracting PDF from compliance report XML
						else
							iNumPDFsSaved++;
					}
					for (int iPDFRpt=1; iPDFRpt<=4; iPDFRpt++)
					{	if (iRetVal == 0 && bSecRpts[iPDFRpt-1])
						{	QString qsRptID = QString( "Report%1" ).arg( QString::number(iPDFRpt+2) );
							QString qsRptFile = QString( "%1 - rpt%2.pdf" ).arg( pszOutputPathFile, QString::number(iPDFRpt+2) );
							if (!CMX_ExtractTitle24ReportFromXML( FileOutName, qsRptFile.toLocal8Bit().constData(), qsRptID.toLocal8Bit().constData(), TRUE /*bSupressAllMessageBoxes*/ ))
								iRetVal = 26;		// Error extracting PDF from compliance report XML
							else
								iNumPDFsSaved++;
					}	}
				}

				if (iRetVal == 0 && iNumPDFsSaved > 0 && !bXMLRpt)
					// DELETE Full (XML) compliance report (if XML (full) report not requested & no errors logged there)
					DeleteFile( FileOutName );
			}

// never happens since bFileWritten not set (based on QT communication)
//		// SAC 9/3/14 - if report generation was unsuccessful, then RENAME the resulting file 
//			if (bFileWritten && // bPDFOnly &&  - only for PDFs??
//					iRetVal > 0)
//			{	if (!FileWriteable( FileOutName ))
//				{	assert( FALSE );
//				}
//				else
//				{	QString sRenameTo = FileOutName;
//					sRenameTo += "-errant";
//					if (FileExists( sRenameTo ))
//					{	if (!FileWriteable( sRenameTo.toLocal8Bit().constData() ) || !DeleteFile( sRenameTo.toLocal8Bit().constData() ))
//						{	sLogMsg.sprintf( "    unable to replace errant report file with latest version:  %s", sRenameTo.toLocal8Bit().constData() );
//							BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
//							sRenameTo.clear();
//					}	}
//					if (!sRenameTo.isEmpty())
//					{	if (MoveFile( FileOutName, sRenameTo.toLocal8Bit().constData() ))
//							sLogMsg.sprintf( "    errant report file renamed to:  %s", sRenameTo.toLocal8Bit().constData() );
//						else
//							sLogMsg.sprintf( "    attempt to rename errant report file failed:  '%s' -->> '%s'", FileOutName, sRenameTo.toLocal8Bit().constData() );
//						BEMPX_WriteLogFile( sLogMsg, NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
//			}	}	}

		}
	//	catch(CException e) {
	//		BEMMessageBox( "Unexpected error loading symbolic file list." );
	//	}
		catch( ... ) {
			assert( FALSE );
			BEMPX_WriteLogFile( "GenerateReport_CEC():  Unknown error generating compliance report.", NULL /*sLogPathFile*/, FALSE /*bBlankFile*/, TRUE /*bSupressAllMessageBoxes*/, FALSE /*bAllowCopyOfPreviousLog*/ );
			//	if (!bSilent)
			//		BEMMessageBox( "Unknown error generating compliance report." );
		}
	}

// wait for a response from the keyboard 
//	printf("Look for the output file %s.\nPress any key to continue...", FileOutName);
//	_getch();

  return iRetVal;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//#include <Winhttp.h>

//		Return Values:	  -1 =>	SUCCESS  (using no proxy server settings)
//							  -2 =>	SUCCESS  (using supplied proxy server settings)
//							  -3 =>	SUCCESS  (using proxy server settings retrieved from operating system)
//						 -11-13 =>	SUCCESS  (same codes as above (minus 10) but ALSO 'true' returned in file from server, indicating report gen site up and functioning)
//							 100 =>  Error - pszSite contained BEMBase Object:Property, but error retrieving URL using that
//							 > 0 =>	Error Code:
//											 (see below)
int CMX_CheckSiteAccess(	const char* pszSite, const char* pszCACertPath, const char* pszProxyAddress, const char* pszProxyCredentials,		// pass NULLs for no proxy  
									char* pszErrorMsg /*=NULL*/, int iErrorMsgLen /*=0*/, bool bVerbose /*=false*/, const char* pszProxyType /*=NULL*/, const char* pszNetComLibrary /*=NULL*/ )
{	int iRetVal = 0;
	QString sSite = pszSite;
	long lDBID = 0;
	if (sSite.indexOf(':') > 0 && sSite.indexOf(':') == sSite.lastIndexOf(':') && sSite.indexOf('/') < 0)
		lDBID = BEMPX_GetDatabaseID( sSite );
#pragma warning(disable:4996)
	if (lDBID > BEM_COMP_MULT)
	{	// pszSite populated w/ Object:Property rather than URL, so retrieve URL from BEMBase 
		if (!BEMPX_GetString( lDBID, sSite ) || sSite.isEmpty())
		{	iRetVal = 100;
			if (pszErrorMsg && iErrorMsgLen > 0)
				_snprintf( pszErrorMsg, iErrorMsgLen, "CMX_CheckSiteAccess() failure:  error retrieving site URL from BEMBase property '%s'.", pszSite );
		}
	}
	if (iRetVal == 0)
	{	QString sNetComLibrary = pszNetComLibrary;	// SAC 11/5/15
 		if (!sNetComLibrary.isEmpty() && !sNetComLibrary.compare( "CURL", Qt::CaseInsensitive ))
		{	iRetVal = 1;
			if (pszErrorMsg && iErrorMsgLen > 0)
				_snprintf( pszErrorMsg, iErrorMsgLen, "CMX_CheckSiteAccess() failure:  method of checking site access via CURL not available." );
		}
//CURL 			iRetVal = CheckSiteAccess(	sSite, pszCACertPath, pszProxyAddress, pszProxyCredentials,		// pass NULLs for no proxy
//CURL 												pszErrorMsg, iErrorMsgLen, bVerbose );
 		else
			iRetVal = CheckSiteAccessViaQt(	sSite.toLocal8Bit().constData(), pszCACertPath, pszProxyAddress, pszProxyCredentials, pszProxyType,		// pass NULLs for no proxy
														pszErrorMsg, iErrorMsgLen, bVerbose );
	}
#pragma warning(default:4996)

	return iRetVal;
}

//		Return Values:	  -1 =>	SUCCESS  (using no proxy server settings)
//							  -2 =>	SUCCESS  (using supplied proxy server settings)
//							  -3 =>	SUCCESS  (using proxy server settings retrieved from operating system)
//						 -11-13 =>	SUCCESS  (same codes as above (minus 10) but ALSO 'true' returned in file from server, indicating report gen site up and functioning)
//							 > 0 =>	Error Code:
//											 1 : Error initializing CURL on first attempt
//											 2 : Error initializing CURL on secondary attempt
//											 3 : No direct connection available and unable to retrieve proxy server settings
//											 4 : Direct connection attempt failed
//											 5 : Connection attempt using supplied proxy server settings failed
//											 6 : Connection attempt using proxy server settings retrieved from the operating system failed
//											 7 : Unable to connect either directly or via proxy server settings retrieved from the operating system
//											 8 : Unable to connect via supplied proxy server settings
//											 9 : Error initializing temporary file path to copy site status to
//											10 : Error initializing temporary file to copy site status to
//											11 : Error opening temporary file to copy site status to
//											12 : CACertificate file not provided
//											13 : path to CACertificate file not found
//											14 : CACertificate file not found
//CURLint CheckSiteAccess(	const char* pszSite, const char* pszCACertPath, const char* pszProxyAddress, const char* pszProxyCredentials,		// pass NULLs for no proxy
//CURL							char* /*pszErrorMsg=NULL*/, int /*iErrorMsgLen=0*/, bool /*bVerbose=false*/,
//CURL							char* /*pszFoundProxyAddress=NULL*/, int /*iFoundProxyAddressLen=0*/,
//CURL							char* /*pszFoundProxyCredentials=NULL*/, int /*iFoundProxyCredentialsLen=0*/ )
//CURL{	int iRetVal = 0;
//CURL	CURL *curl;
//CURL	CURLcode res = CURLE_OK;
//CURL	QString sSite = (pszSite && strlen( pszSite ) > 0) ? pszSite : "t24docs.com";
//CURL
//CURL
//CURL	QString sCACertPathFile, sCACertPath = pszCACertPath;
//CURL	sCACertPath.replace( "\\", "/" );
//CURL	if (sCACertPath.isEmpty())
//CURL	{	iRetVal = 12;				assert( FALSE );			//	23 : CACert path not specified
//CURL	}
//CURL	else
//CURL	{	if (sCACertPath[sCACertPath.length()-1] == '/')
//CURL			sCACertPath = sCACertPath.left( sCACertPath.length()-1 );
//CURL   	if (!DirectoryExists( sCACertPath ))
//CURL		{	iRetVal = 13;				assert( FALSE );			//	24 : CACertPath not a valid or found directory
//CURL		}
//CURL		else
//CURL		{	sCACertPathFile.sprintf( "%s/curl-ca-bundle.crt", sCACertPath );
//CURL			if (!FileExists( sCACertPathFile ))
//CURL			{	iRetVal = 14;			assert( FALSE );			//	2 : CACert file not found
//CURL			}
//CURL		}
//CURL	}
//CURL
//CURL
//CURL	
//CURL			FILE *fp_Out = NULL;		// setup temporary file to store returned HTML page to
//CURL			TCHAR szTempFileName[MAX_PATH];
//CURL	int iFirstTry = (pszProxyAddress && strlen( pszProxyAddress ) > 0) ? 0 : 1;   // if proxy server settings passed in, then ONLY try that method
//CURL	int iLastTry  = (iFirstTry == 0) ? 0 : 2;  // was: 100;
//CURL	for (int i=iFirstTry; (iRetVal == 0 && i <= iLastTry); i++)
//CURL	{
//CURL		curl = curl_easy_init();
//CURL		if (!curl)
//CURL		{	// ERROR
//CURL			iRetVal = (i==iFirstTry) ? 1 : 2;
//CURL//											 1 : Error initializing CURL on first attempt
//CURL//											 2 : Error initializing CURL on secondary attempt
//CURL		}
//CURL		else
//CURL		{
//CURL		// PROXY SETUP
//CURL			const char *pszUseProxyAddress=NULL, *pszUseProxyCredentials=NULL;
//CURL			if (i == 0)
//CURL			{	pszUseProxyAddress = pszProxyAddress;
//CURL				if (pszProxyCredentials && strlen( pszProxyCredentials ) > 0)
//CURL					pszUseProxyCredentials = pszProxyCredentials;
//CURL			}
//CURL			else if (i > 1)   // i==1 attempts DIRECT connection
//CURL			{
//CURL	// retrieve default proxy server settings from Windows
//CURL
//CURL//											 3 : No direct connection available and unable to retrieve proxy server settings
//CURL
//CURL			}
//CURL
//CURL			if (iRetVal == 0)
//CURL			{	TCHAR lpTempPathBuffer[MAX_PATH];
//CURL				DWORD dwRetVal = GetTempPath( MAX_PATH, lpTempPathBuffer );
//CURL				if (dwRetVal > MAX_PATH || (dwRetVal == 0))
//CURL				{	iRetVal = 9;
//CURL				}
//CURL				else
//CURL				{	UINT uRetVal = GetTempFileName( lpTempPathBuffer, TEXT("rptgensite"), // temp file name prefix 
//CURL																0 /*create unique name*/, szTempFileName );  // buffer for name 
//CURL    				if (uRetVal == 0)
//CURL					{	iRetVal = 10;
//CURL					}
//CURL					else
//CURL					{	int ErrorCode = fopen_s( &fp_Out, szTempFileName, "wb" );
//CURL						if (ErrorCode != 0)
//CURL						{	iRetVal = 11;
//CURL				}	}	}
//CURL			}
//CURL
//CURL			if (iRetVal == 0)
//CURL			{
//CURL
//CURL					curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
//CURL					curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2);
//CURL					curl_easy_setopt(curl, CURLOPT_CAINFO, sCACertPathFile);
//CURL//
//CURL//					curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postthis );
//CURL//					/* if we don't provide POSTFIELDSIZE, libcurl will strlen() by
//CURL//						 itself */
//CURL//					curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, npost);
//CURL//
//CURL					curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
//CURL					curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp_Out);
//CURL//
//CURL//					/* Perform the requests, res will get the return code */
//CURL//					res = curl_easy_perform(curl);   // send request
//CURL//					bFileWritten = true;
//CURL
//CURL
//CURL				curl_easy_setopt( curl, CURLOPT_URL, sSite );
//CURL
//CURL				if (pszUseProxyAddress && strlen( pszUseProxyAddress ) > 0)
//CURL				{	curl_easy_setopt(curl, CURLOPT_PROXY, pszUseProxyAddress );
//CURL					curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1 );
//CURL					curl_easy_setopt(curl, CURLOPT_HEADER, 1 );
//CURL					if (pszUseProxyCredentials && strlen( pszUseProxyCredentials ) > 0)
//CURL						curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, pszUseProxyCredentials );
//CURL				}
//CURL
//CURL				bool bKeepTrying = true;
//CURL				while (bKeepTrying && (res = curl_easy_perform(curl)) != CURLE_OK)
//CURL				{
//CURL					switch (res)
//CURL					{	case CURLE_COULDNT_CONNECT:
//CURL						case CURLE_COULDNT_RESOLVE_HOST:
//CURL						case CURLE_COULDNT_RESOLVE_PROXY:
//CURL										bKeepTrying = false;
//CURL										break;
//CURL						default:		bKeepTrying = false;
//CURL										iRetVal = (i==1 ? 4 : (i==0 ? 5 : 6));
//CURL//											 4 : Direct connection attempt failed
//CURL//											 5 : Connection attempt using supplied proxy server settings failed
//CURL//											 6 : Connection attempt using proxy server settings retrieved from the operating system failed
//CURL								//		cerr<<"Request failed:"<<curl_easy_strerror(res)<<endl;
//CURL								//		exit(1);
//CURL										break;
//CURL					}
//CURL				}
//CURL				if (res == CURLE_OK)
//CURL					iRetVal = (i==0 ? -2 : (i==1 ? -1 : -3));
//CURL//		Return Values:	  -1 =>	SUCCESS  (using no proxy server settings)
//CURL//							  -2 =>	SUCCESS  (using supplied proxy server settings)
//CURL//							  -3 =>	SUCCESS  (using proxy server settings retrieved from operating system)
//CURL			}
//CURL
//CURL			// cleanup curl
//CURL			curl_easy_cleanup(curl);
//CURL
//CURL		// moved flush/close of output file down here and executed anytime the file exists, rather than only when CURL executed successfully - SAC 9/21/13
//CURL			if (/*res == CURLE_OK &&*/ fp_Out)
//CURL			{	fflush( fp_Out );
//CURL				fclose( fp_Out );
//CURL				fp_Out = NULL;
//CURL				if (iRetVal >= 0)		// if still looping or errant return code, then DELETE the temp file site status was written to
//CURL					DeleteFile( szTempFileName );
//CURL			}
//CURL		}
//CURL	}
//CURL
//CURL
//CURL	// CHECK FOR OUTPUT FILE containing 'true' - indicating report gen site up and functioning
//CURL	if (iRetVal < 0 && FileExists( szTempFileName ))
//CURL	{
//CURL		fp_Out = _fsopen( szTempFileName, "rb", _SH_DENYNO /*_SH_DENYWR*/ );
//CURL		if (fp_Out==NULL) 
//CURL		{ }	//	iRetVal = 19;		//	19 : Error opening output file following report generation
//CURL		else
//CURL		{	char buff[32];
//CURL			int nread = fread( buff, sizeof(char), 20, fp_Out );  // first 20 chars of file should do it...
//CURL			if (nread < 4)
//CURL			{ }	//	iRetVal = 20;		//	20 : Error reading data from output file following report generation
//CURL			else
//CURL			{	buff[20] = '\0';
//CURL				QString sHdrText = buff;
//CURL				sHdrText.toLower();
//CURL				if (sHdrText.indexOf("true") >= 0)
//CURL				{	iRetVal -= 10;		// adjust retval to reflect 'true' response
//CURL				}
//CURL			}
//CURL			fclose( fp_Out );
//CURL		}
//CURL	   DeleteFile( szTempFileName );
//CURL	}
//CURL
//CURL
//CURL	if (iRetVal == 0)
//CURL		iRetVal = (iFirstTry==0 ? 8 : 7);
//CURL//											 7 : Unable to connect either directly or via proxy server settings retrieved from the operating system
//CURL//											 8 : Unable to connect via supplied proxy server settings
//CURL
//CURL	return iRetVal;
//CURL}

////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
