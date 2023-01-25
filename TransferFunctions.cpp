
#define PRE_AGREED_PORT		8686
#define SEND_BUFFER_SIZE	4096


BOOL CYourServerClass::SendFileToRemoteRecipient(CString fName)
{
	/***************************
	// listens for a connection from a remote client and uploads a file to it
	// the remote client must be running a counterpart GetFileFromRemoteSender function
	// Input: CString fName = name of local file which will be uploaded to remote client
	// Output: BOOL return value indicates success or failure of the upload
	***************************/
	
	// create socket and listen on pre-designated port

///	AfxSocketInit(NULL);	// make certain this is done somewhere in each thread (usually in InitInstance for main thread)
	CSocket sockSrvr; 
	sockSrvr.Create(PRE_AGREED_PORT);	// Creates our server socket
	sockSrvr.Listen();					// Start listening for the client at PORT
	CSocket sockConnection;
	sockSrvr.Accept(sockConnection);	// Use another CSocket to accept the connection
	
	// local variables used in file transfer (declared here to avoid "goto skips definition"-style compiler errors)

	BOOL bRet = TRUE;				// return value

	int fileLength, cbLeftToSend;	// used to monitor the progress of a sending operation
	
	BYTE* sendData = NULL;			// pointer to buffer for sending data (memory is allocated after sending file size)
	
	CFile sourceFile;
	CFileException fe;
	BOOL bFileIsOpen = FALSE;
	
	if( !( bFileIsOpen = sourceFile.Open( fName, CFile::modeRead | CFile::typeBinary, &fe ) ) )
	{
		TCHAR strCause[256];
		fe.GetErrorMessage( strCause, 255 );
		TRACE( "SendFileToRemoteRecipient encountered an error while opening the local file\n"
			"\tFile name = %s\n\tCause = %s\n\tm_cause = %d\n\tm_IOsError = %d\n",
			fe.m_strFileName, strCause, fe.m_cause, fe.m_lOsError );
		
		/* you should handle the error here */
		
		bRet = FALSE;
		goto PreReturnCleanup;
	}
	

	// first send length of file
	
	fileLength = sourceFile.GetLength();
	fileLength = htonl( fileLength );
	
	cbLeftToSend = sizeof( fileLength );
	
	do
	{
		int cbBytesSent;
		BYTE* bp = (BYTE*)(&fileLength) + sizeof(fileLength) - cbLeftToSend;
		cbBytesSent = sockConnection.Send( bp, cbLeftToSend );
		
		// test for errors and get out if they occurred
		if ( cbBytesSent == SOCKET_ERROR )
		{
			int iErr = ::GetLastError();
			TRACE( "SendFileToRemoteRecipient returned a socket error while sending file length\n"
				"\tNumber of Bytes sent = %d\n"
				"\tGetLastError = %d\n", cbBytesSent, iErr );
			
			/* you should handle the error here */

			bRet = FALSE;
			goto PreReturnCleanup;
		}
		
		// data was successfully sent, so account for it with already-sent data
		cbLeftToSend -= cbBytesSent;
	}
	while ( cbLeftToSend>0 );
	
	
	// now send the file's data
	
	sendData = new BYTE[SEND_BUFFER_SIZE]; 
	
	cbLeftToSend = sourceFile.GetLength();
	
	do
	{
		// read next chunk of SEND_BUFFER_SIZE bytes from file
		
		int sendThisTime, doneSoFar, buffOffset;
		
		sendThisTime = sourceFile.Read( sendData, SEND_BUFFER_SIZE );
		buffOffset = 0;
		
		do
		{
			doneSoFar = sockConnection.Send( sendData + buffOffset, sendThisTime ); 
			
			// test for errors and get out if they occurred
			if ( doneSoFar == SOCKET_ERROR )
			{
				int iErr = ::GetLastError();
				TRACE( "SendFileToRemoteRecipient returned a socket error while sending chunked file data\n"
					"\tNumber of Bytes sent = %d\n"
					"\tGetLastError = %d\n", doneSoFar, iErr );
				
				/* you should handle the error here */
				
				bRet = FALSE;
				goto PreReturnCleanup;
			}
			
/***************************
  un-comment this code and put a breakpoint here to prove to yourself that sockets can send fewer bytes than requested
			  
			if ( doneSoFar != sendThisTime )
			{
				int ii = 0;
			}
****************************/
			
			// data was successfully sent, so account for it with already-sent data
			
			buffOffset += doneSoFar;
			sendThisTime -= doneSoFar;
			cbLeftToSend -= doneSoFar;
		}
		while ( sendThisTime > 0 );
		
	}
	while ( cbLeftToSend > 0 );
	
	
PreReturnCleanup:		// labelled goto destination
	
	// free allocated memory
	// if we got here from a goto that skipped allocation, delete of NULL pointer
	// is permissible under C++ standard and is harmless
	delete[] sendData;
	
	if ( bFileIsOpen )
		sourceFile.Close();		// only close file if it's open (open might have failed above)
	
	sockConnection.Close();
	
	return bRet;
	
}




#define PRE_AGREED_PORT		8686
#define RECV_BUFFER_SIZE	4096

BOOL CYourClientClass::GetFileFromRemoteSender(CString strIP, CString fName)
{
	/***************************
	// connects to a remote server and downloads a file from it
	// the remote server must be running a counterpart SendFileToRemoteRecipient function
	// Inputs: CString strIP = IP address of remote server, in dotted IP format (like "127.0.0.1") or a manchine name (like "localhost")
	//         CString fName = name of local file to which downlaoded data will be stored
	// Output: BOOL return value indiactes success or failure of the download
	****************************/

	// create client socket and connect to server
	
///	AfxSocketInit(NULL);	// make certain this is done somewhere in each thread (usually in InitInstance for main thread)
	CSocket sockClient;
	sockClient.Create();
	
	sockClient.Connect( strIP, PRE_AGREED_PORT );	// PRE_AGREED_PORT is #define'd as 8686
	
	
	// local variables used in file transfer (declared here to avoid "goto skips definition"-style compiler errors)
	
	BOOL bRet = TRUE;								// return value
	
	int dataLength, cbBytesRet, cbLeftToReceive;	// used to monitor the progress of a receive operation
	
	BYTE* recdData = NULL;	// pointer to buffer for receiving data (memory is allocated after obtaining file size)
	
	CFile destFile;
	CFileException fe;
	BOOL bFileIsOpen = FALSE;
	
	// open/create target file that receives the transferred data
	
	if( !( bFileIsOpen = destFile.Open( fName, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary, &fe ) ) )
	{
		TCHAR strCause[256];
		fe.GetErrorMessage( strCause, 255 );
		TRACE( "GetFileFromRemoteSender encountered an error while opening the local file\n"
			"\tFile name = %s\n\tCause = %s\n\tm_cause = %d\n\tm_IOsError = %d\n",
			fe.m_strFileName, strCause, fe.m_cause, fe.m_lOsError );
		
		/* you should handle the error here */
		
		bRet = FALSE;
		goto PreReturnCleanup;
	}
	
	
	// get the file's size first
	
	cbLeftToReceive = sizeof( dataLength );
	
	do
	{
		BYTE* bp = (BYTE*)(&dataLength) + sizeof(dataLength) - cbLeftToReceive;
		cbBytesRet = sockClient.Receive( bp, cbLeftToReceive );
		
		// test for errors and get out if they occurred
		if ( cbBytesRet == SOCKET_ERROR || cbBytesRet == 0 )
		{
			int iErr = ::GetLastError();
			TRACE( "GetFileFromRemoteSite returned a socket error while getting file length\n"
				"\tNumber of Bytes received (zero means connection was closed) = %d\n"
				"\tGetLastError = %d\n", cbBytesRet, iErr );
			
			/* you should handle the error here */
			
			bRet = FALSE;
			goto PreReturnCleanup;
		}
		
		// good data was retrieved, so accumulate it with already-received data
		cbLeftToReceive -= cbBytesRet;
		
	}
	while ( cbLeftToReceive > 0 );
	
	dataLength = ntohl( dataLength );
	
	
	// now get the file in RECV_BUFFER_SIZE chunks at a time
	
	recdData = new byte[RECV_BUFFER_SIZE];
	cbLeftToReceive = dataLength;
	
	do
	{	
		int iiGet, iiRecd;
		
		iiGet = (cbLeftToReceive<RECV_BUFFER_SIZE) ? cbLeftToReceive : RECV_BUFFER_SIZE ;
		iiRecd = sockClient.Receive( recdData, iiGet );
		
		// test for errors and get out if they occurred
		if ( iiRecd == SOCKET_ERROR || iiRecd == 0 )
		{
			int iErr = ::GetLastError();
			TRACE( "GetFileFromRemoteSite returned a socket error while getting chunked file data\n"
				"\tNumber of Bytes received (zero means connection was closed) = %d\n"
				"\tGetLastError = %d\n", iiRecd, iErr );
			
			/* you should handle the error here */
			
			bRet = FALSE;
			goto PreReturnCleanup;
		}

/*************************	
  un-comment this code and put a breakpoint here to prove to yourself that sockets can return fewer bytes than requested
		  
			if ( iiGet != iiRecd )
			{
			int ii=0;
			}			
***************************/
		
		// good data was retrieved, so accumulate it with already-received data
		
		destFile.Write( recdData, iiRecd); // Write it
		cbLeftToReceive -= iiRecd;
		
	} 
	while ( cbLeftToReceive > 0 );
	
	
PreReturnCleanup:		// labelled "goto" destination
	
	// free allocated memory
	// if we got here from a goto that skipped allocation, delete of NULL pointer
	// is permissible under C++ standard and is harmless
	delete[] recdData;		
	
	if ( bFileIsOpen )
		destFile.Close();	// only close file if it's open (open might have failed above)
	
	sockClient.Close();
	
	return bRet;
}
