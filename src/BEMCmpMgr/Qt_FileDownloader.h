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

#ifndef __Qt_FileDownloader_H__
#define __Qt_FileDownloader_H__
// based on Qt Project post: http://qt-project.org/wiki/Download_Data_from_URL

#pragma warning(disable : 4100 4127 4512)
#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkProxy>
#include <QtNetwork/QAuthenticator>
#pragma warning(default : 4100 4127 4512)

 
class Qt_FileDownloader : public QObject
{
    Q_OBJECT
public:
    explicit Qt_FileDownloader(QUrl imageUrl, QObject *parent = 0, const char* pszCACertPath=NULL,
    										const char* pszProxyAddress=NULL, const char* pszProxyCredentials=NULL,
 											const char* pszProxyType=NULL,
											const char* pszDataToPost=NULL, int iPostDataLen=0, bool bVerbose=false);
 
    virtual ~Qt_FileDownloader();
 
    QByteArray downloadedData() const;
    int downloadedDataSize();

    QString ErrorString()		{	return m_sErrorStr;	};
    QString VerboseString()	{	return m_sVerboseStr;	};
 
signals:
        void downloaded();
 
private slots:
 
   void fileDownloaded(QNetworkReply* pReply);
	void onProxyAuthenticationRequired(const QNetworkProxy&, QAuthenticator* auth);
   void onUploadProgress(qint64 bytesSent, qint64 bytesTotal);
 
private:
 
    QNetworkAccessManager m_WebCtrl;

    QNetworkProxy m_proxy;		// SAC 10/29/14
    QString m_sProxyUser;
    QString m_sProxyPassword;

    QString m_sErrorStr;
    QString m_sVerboseStr;
    bool m_bVerbose;
 
    QByteArray m_DownloadedData;
    QByteArray m_DataToUpload;
 
};

//------------------------------------------------------------------------------
 
class Qt_URLFile : public QObject
{
	Q_OBJECT
public:
	explicit Qt_URLFile();
	virtual ~Qt_URLFile();
 
 	int DownloadFile( const char* pszUrl, const char* pszPathFile, const char* pszCACertPath=NULL,
 							const char* pszProxyAddress=NULL, const char* pszProxyCredentials=NULL,
 							const char* pszProxyType=NULL,
 							const char* pszDataToPost=NULL, int iPostDataLen=0,
 							char* pszDebugInfo=NULL, int iDebugInfoLength=0, bool bVerbose=false );
 	int CleanUp();

//private slots:
//	int fileDownloaded();
 
private:
	QString m_sPathFile;		// SAC 4/1/16 - switched from std::string to resolve char encoding issue w/ European chars in filenames (res tic #630)
	Qt_FileDownloader* m_pFileDownloader;

	QString m_sVerboseStr;
	bool m_bVerbose;

	int SaveFile();

};


#endif // __Qt_FileDownloader_H__
