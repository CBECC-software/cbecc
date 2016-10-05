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
#include "Qt_FileDownloader.h"
#include "BEMCmpMgr.h"
#include "BEMCM_I.h"

#pragma warning(disable : 4100 4127 4512)
#include <QtCore/QFile>
#include <QtCore/QEventLoop>
#include <QtWidgets/QMessageBox>
#include <QtNetwork/QHttpMultiPart>
#include <QtNetwork/QSslConfiguration>
#pragma warning(default : 4100 4127 4512)
#include "memLkRpt.h"

Qt_FileDownloader::Qt_FileDownloader(QUrl imageUrl, QObject *parent, const char* /*pszCACertPath*/,
													const char* pszProxyAddress, const char* pszProxyCredentials, const char* pszProxyType,
													const char* pszDataToPost, int iPostDataLen, bool bVerbose ) :
    QObject(parent)
{
	m_bVerbose = bVerbose;
																//		QMessageBox msgBox;
																//		msgBox.setWindowTitle( "Qt_FileDownloader::Qt_FileDownloader()" );
																//		msgBox.setIcon( QMessageBox::Warning ); 
																//		msgBox.setText( QString("URL: %1\nPost Length: %L2\nVerbose: %6").arg(imageUrl.path()).arg(iPostDataLen).arg((bVerbose?"true":"false")) );
																//		msgBox.exec();
	QString sProxyMsg;
	QMessageBox msgBoxProxy;
	if (pszProxyAddress && strlen(pszProxyAddress) > 0)
	{
		m_sProxyUser = "";
		m_sProxyPassword = "";

		QString sProxyTypeMsg = "HttpProxy";		// works for NORESCO and default in OS
		if (pszProxyType == NULL || strlen( pszProxyType ) < 1)
			m_proxy.setType(QNetworkProxy::HttpProxy);
		else
		{	std::string sProxyType = pszProxyType;
			if (boost::iequals( sProxyType, "Default" ))
			{		m_proxy.setType(QNetworkProxy::DefaultProxy);		sProxyTypeMsg = "DefaultProxy";		}
			else if (boost::iequals( sProxyType, "No" ))
			{		m_proxy.setType(QNetworkProxy::NoProxy);				sProxyTypeMsg = "NoProxy";				}
			else if (boost::iequals( sProxyType, "Socks5" ))
			{		m_proxy.setType(QNetworkProxy::Socks5Proxy);			sProxyTypeMsg = "Socks5Proxy";		}
			else if (boost::iequals( sProxyType, "HttpCaching" ))
			{		m_proxy.setType(QNetworkProxy::HttpCachingProxy);	sProxyTypeMsg = "HttpCachingProxy";		}
			else if (boost::iequals( sProxyType, "FtpCaching" ))
			{		m_proxy.setType(QNetworkProxy::FtpCachingProxy);	sProxyTypeMsg = "FtpCachingProxy";		}
			else
					m_proxy.setType(QNetworkProxy::HttpProxy);
		}

		sProxyMsg  = "Setting Proxy to:\n   ProxyType = QNetworkProxy::";
		sProxyMsg += sProxyTypeMsg;
		std::string sPAdd = pszProxyAddress;
		std::size_t found = sPAdd.find(':');
		if (found == std::string::npos)
		{	m_proxy.setHostName(pszProxyAddress);
			sProxyMsg += "\n   ProxyHostName = ";	sProxyMsg += pszProxyAddress;
		}
		else
		{	m_proxy.setHostName( sPAdd.substr( 0, found ).c_str() );
			sProxyMsg += "\n   ProxyHostName = ";	sProxyMsg += sPAdd.substr( 0, found ).c_str();
			if (found < (sPAdd.length()-1))
			{	int iPort = atoi( sPAdd.substr( found+1 ).c_str() );
				if (iPort >= 0)
				{	m_proxy.setPort(iPort);
					sProxyMsg += "\n   ProxyPort = ";	sProxyMsg += QString::number( iPort );
		}	}	}
		std::string sPCred = pszProxyCredentials;
		found = sPCred.find(':');
		if (found == std::string::npos)
		{	//m_proxy.setUser(pszProxyCredentials);
			m_sProxyUser = pszProxyCredentials;
//			sProxyMsg += "\n   ProxyUser = ";	sProxyMsg += pszProxyCredentials;
		}
		else
		{	//m_proxy.setUser( sPCred.substr( 0, found ).c_str() );
			m_sProxyUser = sPCred.substr( 0, found ).c_str();
//			sProxyMsg += "\n   ProxyUser = ";	sProxyMsg += sPCred.substr( 0, found ).c_str();
			if (found < (sPCred.length()-1))
			{	//m_proxy.setPassword( sPCred.substr( found+1 ).c_str() );
				m_sProxyPassword = sPCred.substr( found+1 ).c_str();
//				sProxyMsg += "\n   ProxyPassword = ";	sProxyMsg += sPCred.substr( found+1 ).c_str();
		}	}
//		msgBoxProxy.setText( sProxyMsg );		msgBoxProxy.exec();
		m_WebCtrl.setProxy( m_proxy );
		if (m_bVerbose)
			m_sVerboseStr += QString("Proxy: %1 - %2 - %3 >> ").arg(sProxyTypeMsg, sPAdd.c_str(), sPCred.c_str());
	}
//	else
//	{	msgBoxProxy.setText( "No proxy server information provided for file download." );		msgBoxProxy.exec();
//	}

	if (pszDataToPost && iPostDataLen > 0)
	{	m_DataToUpload.append( pszDataToPost, iPostDataLen );
		if (m_bVerbose)
			m_sVerboseStr += QString("Posting data: %L1 >> ").arg(iPostDataLen);
	}

																	//	QMessageBox msgBox;
																	//	msgBox.setWindowTitle( "Qt_URLFile::DownloadFile()" );
																	//	msgBox.setIcon( QMessageBox::Warning ); 
																//		msgBox.setText( QString("About to create QNetworkRequest") );
																//		msgBox.exec();

	QNetworkRequest request(imageUrl);

//	QSslConfiguration sslConfig( QSslConfiguration::defaultConfiguration() );		// SAC 12/15/15
//	if (pszCACertPath && strlen( pszCACertPath ) > 0)
//	{	QString certFile = QString( "%1/curl-ca-bundle.crt" ).arg(pszCACertPath);
//		if (FileExists( certFile.toLocal8Bit() ))
//		{
//			QList<QSslCertificate> certs;
//			certs.append(sslConfig.caCertificates());
//			QList<QSslCertificate> certsFromFile = QSslCertificate::fromPath( certFile, QSsl::Pem, QRegExp::Wildcard );
//			certs.append(certsFromFile);
//
//																	//	QMessageBox msgBox;
//																	//	msgBox.setWindowTitle( "Qt_URLFile::DownloadFile()" );
//																	//	msgBox.setIcon( QMessageBox::Warning ); 
//																//		msgBox.setText( QString("Applying %L1 CA certificates to SSL config.").arg(certs.size()) );
//																//		msgBox.exec();
//
//			sslConfig.setCaCertificates( certs );
//			request.setSslConfiguration( sslConfig );
//	}	}

	if (m_DataToUpload.size() > 0)
	{
//		QString preview_path  = "C:/preview.jpg";
//		QHttpPart previewPathPart;
//		previewPathPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"preview_path\""));
//		previewPathPart.setBody(preview_path.toLatin1());
//		multiPart->append(previewPathPart);
//		multiPart->append(previewFilePart);
//
//		textPart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));
//		textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"text\""));
//		textPart.setBody("here goes the body");

//		QHttpMultiPart *pMultiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
//		QHttpPart dataPart;
//		dataPart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));
//		dataPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"text\""));
//		dataPart.setBody( m_DataToUpload );
//		pMultiPart->append( dataPart );
//
//		QNetworkReply* reply = m_WebCtrl.post(request, pMultiPart);
//		pMultiPart->setParent( reply ); // delete the multiPart with the reply

						if (m_bVerbose)
							m_sVerboseStr += QString("posting %L1 to '%2' >> ").arg(m_DataToUpload.size()).arg(imageUrl.path());
		m_WebCtrl.post(request, m_DataToUpload);
	}
	else
	{					if (m_bVerbose)
							m_sVerboseStr += QString("getting '%1' >> ").arg(imageUrl.path());
		m_WebCtrl.get(request);
	}

	connect(&m_WebCtrl,	SIGNAL(finished(QNetworkReply*)),
								SLOT(fileDownloaded(QNetworkReply*)));
	connect(&m_WebCtrl,	SIGNAL(proxyAuthenticationRequired(const QNetworkProxy&, QAuthenticator*)),
								SLOT(onProxyAuthenticationRequired(const QNetworkProxy&, QAuthenticator*)));
	if (m_DataToUpload.size() > 0)
		connect(&m_WebCtrl,	SIGNAL(uploadProgress(qint64, qint64)),
									SLOT(onUploadProgress(qint64, qint64)));

																	//	QMessageBox msgBox;
																	//	msgBox.setWindowTitle( "Qt_URLFile::DownloadFile()" );
																	//	msgBox.setIcon( QMessageBox::Warning ); 
																	//	msgBox.setText( QString("Leaving - verbose info:\n%1").arg(m_sVerboseStr) );
																	//	msgBox.exec();
}
 
Qt_FileDownloader::~Qt_FileDownloader()
{
}
 
void Qt_FileDownloader::onProxyAuthenticationRequired(const QNetworkProxy&, QAuthenticator* auth)
{
																//		QMessageBox msgBox;
																//		msgBox.setWindowTitle( "Qt_FileDownloader::onProxyAuthenticationRequired()" );
																//		msgBox.setIcon( QMessageBox::Warning ); 
																//		msgBox.setText( QString("in routine...") );
																//		msgBox.exec();
								if (m_bVerbose)
									m_sVerboseStr += QString("\nonProxyAuthenticationRequired() - ");
	QString sProxyMsg;
	if (m_sProxyUser.size() > 0)
	{	auth->setUser( m_sProxyUser );
		sProxyMsg += "\n   ProxyUser = ";		sProxyMsg += m_sProxyUser;
								if (m_bVerbose)
									m_sVerboseStr += QString("proxy user '%1' set >> ").arg(m_sProxyUser);
	}
	if (m_sProxyPassword.size() > 0)
	{	auth->setPassword( m_sProxyPassword );
		sProxyMsg += "\n   ProxyPassword = ";	sProxyMsg += m_sProxyPassword;
								if (m_bVerbose)
									m_sVerboseStr += QString("proxy password set >> ");
	}

//	QMessageBox msgBoxProxy;
//	if (sProxyMsg.length() < 1)
//		sProxyMsg = "Proxy Authentication Required, but none available.";
//	else
//		sProxyMsg = "Proxy Authentication Required:" + sProxyMsg;
//	msgBoxProxy.setText( sProxyMsg );	msgBoxProxy.exec();
}

void Qt_FileDownloader::onUploadProgress(qint64 bytesSent, qint64 bytesTotal)
{
																//		QMessageBox msgBox;
																//		msgBox.setWindowTitle( "Qt_FileDownloader::onUploadProgress()" );
																//		msgBox.setIcon( QMessageBox::Warning ); 
																//		msgBox.setText( QString("in routine...") );
																//		msgBox.exec();

//	std::string sProg = boost::str( boost::format( "  uploaded %ld of %ld bytes" ) % bytesSent % bytesTotal );

		if (m_bVerbose)
			m_sVerboseStr += QString("progress: %L1/%L2 >> ").arg(bytesSent).arg(bytesTotal);

//	QString sProgMsg = sProg.c_str();
//	QMessageBox msgBox;
//	msgBox.setText( sProgMsg );	msgBox.exec();

//    if(bytesSent!=0 && bytesTotal != 0)
//    {
//    qDebug() << "Uploaded:" << bytesSent << " bytes of total: " << bytesTotal << "diff to total: " << bytesTotal-this->totalSize;
//    qint64 bytesDiff = bytesSent - this->lastUlSize;
//    this->UlSize += bytesDiff;
//    this->lastUlSize = bytesSent;
//    int timeDiff = QDateTime::currentMSecsSinceEpoch()/1000-this->time;
//    if(timeDiff!= 0 && bytesSent!=0 && bytesTotal != 0)
//    {
//        qDebug() << "Uploadspeed: " << ((this->UlSize/timeDiff));
//
//        qint64 remainingUl = this->totalSize - this->UlSize;
//        qint64 speed = ((this->UlSize/timeDiff)); //Download Speed in B/s
//        int remainingTimeSec = remainingUl/speed;
//        qDebug() << "Remaining time: " <<  this->readableTime(remainingTimeSec) << " percentage: " << (this->UlSize/this->totalSize)*100;
//        float percentage = ((float)this->UlSize/(float)this->totalSize)*100;
//        emit uploadProg(this->niceSpeed(speed), this->readableTime(remainingTimeSec), percentage);
//    }
//    }
}

void Qt_FileDownloader::fileDownloaded(QNetworkReply* pReply)
{

																//		QMessageBox msgBox;
																//		msgBox.setWindowTitle( "Qt_FileDownloader::fileDownloaded()" );
																//		msgBox.setIcon( QMessageBox::Warning ); 
																//		msgBox.setText( QString("in routine...") );
																//		msgBox.exec();

						if (m_bVerbose)
							m_sVerboseStr += QString("\nfileDownloaded() - ");
	if (pReply == NULL)
	{					if (m_bVerbose)
							m_sVerboseStr += QString("reply ptr NULL, returning");
		return;
	}
	else
	{	bool bEmitDownloadedSignal = true;
		int iStatusCode = pReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
						if (m_bVerbose)
							m_sVerboseStr += QString("reply status code: %L1 >> ").arg(iStatusCode);

		if (pReply->error() != QNetworkReply::NoError)		// check for error
		{	QVariant statusCode = pReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
			switch(pReply->error())
			{	case QNetworkReply::AuthenticationRequiredError:
								m_sErrorStr += "Invalid Auth Key";
								break;
				case QNetworkReply::ConnectionRefusedError:
								m_sErrorStr += "Network Error: Connection Refused";
								break;
				case QNetworkReply::UnknownContentError:
								m_sErrorStr += "Network Error: Unknown Content.  Verify the User-Agent header";
								break;
				case QNetworkReply::HostNotFoundError:
							//	if (pReply->m_ip.isEmpty())
							//		m_sErrorStr += "Network Error: Offline.  Check your internet connection";
							//	else
									m_sErrorStr += "Network Error: Host Not Found";
								break;
				case QNetworkReply::UnknownNetworkError:
								if (pReply->errorString().startsWith("Error creating SSL context"))
									m_sErrorStr += "DLL Error: SSL unavailable";
								else
									m_sErrorStr += "Network Error: Unknown Network Error";
								break;
				default:
								m_sErrorStr += QString("Network Error: %1%2").arg(!statusCode.isNull() ? statusCode.toString() + " - " : "", pReply->errorString());
			}
						if (m_bVerbose)
					//		m_sVerboseStr += QString("reply from '%1' failed: %2").arg(pReply->url().toEncoded().constData()).arg(pReply->errorString());
							m_sVerboseStr += QString("reply from '%1' failed: %2").arg(pReply->url().toEncoded().constData()).arg(m_sErrorStr);
																//		QMessageBox msgBox;
																//		msgBox.setWindowTitle( "Qt_FileDownloader::fileDownloaded()" );
																//		msgBox.setIcon( QMessageBox::Warning ); 
																//		msgBox.setText( m_sVerboseStr );
																//		msgBox.exec();
		}
		else if (iStatusCode == 302)		// handle status redirect
		{
			QUrl newUrl = pReply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
						if (m_bVerbose)
							m_sVerboseStr += QString("redirected to: %1 >> returning").arg(newUrl.toString());
						//qDebug() << "redirected from " + replyUrl + " to " + newUrl.toString();
			QNetworkRequest newRequest(newUrl);
			if (m_DataToUpload.size() > 0)
				m_WebCtrl.post(newRequest, m_DataToUpload);
			else
				m_WebCtrl.get(newRequest);
			bEmitDownloadedSignal = false;
																//		QMessageBox msgBox;
																//		msgBox.setWindowTitle( "Qt_FileDownloader::fileDownloaded()" );
																//		msgBox.setIcon( QMessageBox::Warning ); 
																//		msgBox.setText( m_sVerboseStr );
																//		msgBox.exec();
		}
		else
		{
			m_DownloadedData = pReply->readAll();
						if (m_bVerbose)
							m_sVerboseStr += QString("reply size: %L1 >> ").arg(m_DownloadedData.size());
		}

		pReply->deleteLater();
		if (bEmitDownloadedSignal)		// m_DownloadedData.size() > 0)    //emit a signal
		{	emit downloaded();
						if (m_bVerbose)
							m_sVerboseStr += QString("downloaded signal emitted >> ");
		}
		else
		{				if (m_bVerbose)
							m_sVerboseStr += QString("downloaded signal NOT emitted (no data yet) >> ");
		}
																//		QMessageBox msgBox;
																//		msgBox.setWindowTitle( "Qt_FileDownloader::fileDownloaded()" );
																//		msgBox.setIcon( QMessageBox::Warning ); 
																//		msgBox.setText( m_sVerboseStr );
																//		msgBox.exec();
	}
}
 
QByteArray Qt_FileDownloader::downloadedData() const
{
																//		QMessageBox msgBox;
																//		msgBox.setWindowTitle( "Qt_FileDownloader::downloadedData()" );
																//		msgBox.setIcon( QMessageBox::Warning ); 
																//		msgBox.setText( QString("in routine...") );
																//		msgBox.exec();
    return m_DownloadedData;
}

int Qt_FileDownloader::downloadedDataSize()
{
																//		QMessageBox msgBox;
																//		msgBox.setWindowTitle( "Qt_FileDownloader::downloadedDataSize()" );
																//		msgBox.setIcon( QMessageBox::Warning ); 
																//		msgBox.setText( QString("in routine...") );
																//		msgBox.exec();
	return m_DownloadedData.size();
}


//------------------------------------------------------------------------------
 
Qt_URLFile::Qt_URLFile()
{
//	m_sPathFile = "";
	m_pFileDownloader = NULL;
}

Qt_URLFile::~Qt_URLFile()
{
	if (m_pFileDownloader)
		CleanUp();
}

int Qt_URLFile::DownloadFile( const char* pszUrl, const char* pszPathFile, const char* pszCACertPath,
										const char* pszProxyAddress, const char* pszProxyCredentials, const char* pszProxyType,
										const char* pszDataToPost /*=NULL*/, int iPostDataLen /*=0*/,		// SAC 11/5/15
 										char* pszDebugInfo /*=NULL*/, int iDebugInfoLength /*=0*/, bool bVerbose /*=false*/ )		// SAC 11/30/15
{	int iRetVal = 0;
	m_sVerboseStr = "";
	m_bVerbose = bVerbose;
	m_sPathFile = pszPathFile;
	QUrl url(pszUrl);

																//		QMessageBox msgBox;
																//		msgBox.setWindowTitle( "Qt_URLFile::DownloadFile()" );
																//		msgBox.setIcon( QMessageBox::Warning ); 
																//		msgBox.setText( QString("URL: %1\nProxy Address: %2\nProxy Cred: %3\nProxy Type: %4\nPost Length: %L5\nVerbose: %6").arg(pszUrl).arg(pszProxyAddress).arg(pszProxyCredentials).arg(pszProxyType).arg(iPostDataLen).arg((bVerbose?"true":"false")) );
																//		msgBox.exec();

	m_pFileDownloader = new Qt_FileDownloader( url, this, pszCACertPath, pszProxyAddress, pszProxyCredentials, pszProxyType, pszDataToPost, iPostDataLen, bVerbose );
//	connect( m_pFileDownloader, SIGNAL(downloaded()), SLOT(fileDownloaded()) );

	QEventLoop loop;
	connect( m_pFileDownloader, SIGNAL(downloaded()), &loop, SLOT(quit()) );
// ?? code to execute ??
	loop.exec();

																	//	QMessageBox msgBox;
																	//	msgBox.setWindowTitle( "Qt_URLFile::DownloadFile()" );
																	//	msgBox.setIcon( QMessageBox::Warning ); 
																//		msgBox.setText( QString("Back from loop.exec() - about to SaveFile()") );
																//		msgBox.exec();

	iRetVal = SaveFile();
	if (pszDebugInfo && iDebugInfoLength > 0)		// SAC 11/30/15
	{	if (m_pFileDownloader->ErrorString().length() > 0)
		{	int iToAdd = iDebugInfoLength - 1 - strlen( pszDebugInfo );
			QString sAdd = m_pFileDownloader->ErrorString();
			if (bVerbose && (m_pFileDownloader->VerboseString().length() > 0 || m_sVerboseStr.length() > 0))
				sAdd += '\n';
			if (strcat_s( pszDebugInfo, iDebugInfoLength, sAdd.left(iToAdd).toLocal8Bit() ) != 0)
			{	assert( false );
			}
		}
		if (bVerbose && m_pFileDownloader->VerboseString().length() > 0)
		{	int iToAdd = iDebugInfoLength - 1 - strlen( pszDebugInfo );
			if (strcat_s( pszDebugInfo, iDebugInfoLength, m_pFileDownloader->VerboseString().left(iToAdd).toLocal8Bit() ) != 0)
			{	assert( false );
			}
		}
		if (m_sVerboseStr.length() > 0)
		{	int iToAdd = iDebugInfoLength - 1 - strlen( pszDebugInfo );
			if (strcat_s( pszDebugInfo, iDebugInfoLength, m_sVerboseStr.left(iToAdd).toLocal8Bit() ) != 0)
			{	assert( false );
			}
		}
	}
	CleanUp();

																	//	QMessageBox msgBox;
																	//	msgBox.setWindowTitle( "Qt_URLFile::DownloadFile()" );
																	//	msgBox.setIcon( QMessageBox::Warning ); 
																//		msgBox.setText( QString("SaveFile() and CleanUp() done\ndebug info:  %1").arg(pszDebugInfo) );
																//		msgBox.exec();

	return iRetVal;
}

int Qt_URLFile::CleanUp()
{	int iRetVal = 0;
	if (m_pFileDownloader)
		delete m_pFileDownloader;
	m_pFileDownloader = NULL;
	return iRetVal;
}

////private slots:
//int Qt_URLFile::fileDownloaded()
int Qt_URLFile::SaveFile()
{	int iRetVal = 0;																						assert( m_pFileDownloader );
													if (m_bVerbose)
														m_sVerboseStr += "\nSaveFile() - ";
	if (m_sPathFile.length() < 3)
	{	iRetVal = 1;
													if (m_bVerbose)
														m_sVerboseStr += "no m_sPathFile to write to >> ";
	}
	else if (m_pFileDownloader == NULL || m_pFileDownloader->downloadedDataSize() < 1)
	{	iRetVal = 2;		// this error occurs when NORESCO proxy not able to be negotiated
													if (m_bVerbose)
													{	if (m_pFileDownloader == NULL)
															m_sVerboseStr += "m_pFileDownloader null >> ";
														else
															m_sVerboseStr += "downloadedDataSize() < 1 >> ";
	}												}
	else
	{
		std::string sOverwriteMsg = boost::str( boost::format( "The file to save downloaded data to '%s' is opened in another application.  This file must be closed in that "
													"application before an updated file can be written.\n\nSelect 'Retry' to update the file "
													"(once the file is closed), or \n'Cancel' to abort the file writing." ) % m_sPathFile.toLocal8Bit().constData() );
		if (!OKToWriteOrDeleteFile( m_sPathFile.toLocal8Bit().constData(), sOverwriteMsg.c_str() ))
		{	iRetVal = 3;
													if (m_bVerbose)
														m_sVerboseStr += QString("cannot write file %1 >> ").arg(m_sPathFile);
		}
		else
		{
//			QByteArray qbData = m_pFileDownloader->downloadedData();
		//	QString qsPF = QString::fromUtf8(m_sPathFile.c_str());
			QString qsPF = m_sPathFile;
			QFile file( qsPF );
			file.open(QIODevice::WriteOnly);
			file.write( m_pFileDownloader->downloadedData() );
			file.close();
													if (m_bVerbose)
														m_sVerboseStr += QString("wrote %L1 to file '%2' >> ").arg(m_pFileDownloader->downloadedDataSize()).arg(m_sPathFile);
		}
	}
													if (m_bVerbose)
														m_sVerboseStr += QString("returning %L1").arg(iRetVal);
	return iRetVal;
}
 
