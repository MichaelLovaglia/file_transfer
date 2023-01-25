// FileTransferServerView.cpp : implementation of the CFileTransferServerView class
//

#include "stdafx.h"
#include "FileTransferServer.h"

#include "FileTransferServerDoc.h"
#include "FileTransferServerView.h"
#include <stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const UINT UWM_FILESENDEVENT = ::RegisterWindowMessage(
		_T( "UWM_FILESENDEVENT_27580DB4_1360_4062_BB4E_C5C894E90CCC" ) );


/////////////////////////////////////////////////////////////////////////////
// CFileTransferServerView

IMPLEMENT_DYNCREATE(CFileTransferServerView, CFormView)

BEGIN_MESSAGE_MAP(CFileTransferServerView, CFormView)
	//{{AFX_MSG_MAP(CFileTransferServerView)
	ON_BN_CLICKED(IDC_BUTTON_LISTEN, OnButtonListen)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
	ON_REGISTERED_MESSAGE( UWM_FILESENDEVENT, OnFileSendEvent )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileTransferServerView construction/destruction

CFileTransferServerView::CFileTransferServerView()
	: CFormView(CFileTransferServerView::IDD)
{
	//{{AFX_DATA_INIT(CFileTransferServerView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

	m_iNumMismatches = 0;
	m_strFileName.Empty();
	m_pThread = NULL;
}

CFileTransferServerView::~CFileTransferServerView()
{
}

void CFileTransferServerView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileTransferServerView)
	DDX_Control(pDX, IDC_CHECK_SIMULATION, m_ctlSimulate);
	DDX_Control(pDX, IDC_BUTTON_LISTEN, m_btnStartListen);
	DDX_Control(pDX, IDC_STATIC_STATUS, m_ctlStatus);
	DDX_Control(pDX, IDC_STATIC_NUMMISMATCHES, m_ctlNumMismatches);
	DDX_Control(pDX, IDC_PROGRESS_SEND, m_ctlProgressSend);
	DDX_Control(pDX, IDC_EDIT_FILENAME, m_ctlFileName);
	//}}AFX_DATA_MAP
}

BOOL CFileTransferServerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CFileTransferServerView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

		
	// initialize controls based on .INI file settings

	CWinApp* pApp = AfxGetApp();


	CString fName = pApp->GetProfileString( "Dialog Settings", "Last File Name", NULL );
	m_ctlFileName.SetWindowText( fName );

	
	BOOL bCheck = (BOOL)pApp->GetProfileInt( "Dialog Settings", "Inject Mismatch Events", 0 );
	m_ctlSimulate.SetCheck( bCheck );


	// setup auxiliary controls

	CString msg;
	msg.Empty();

	msg.Format( "Status: Idle" );
	m_ctlStatus.SetWindowText( msg );

	msg.Format( "Send mismatch events = %d", m_iNumMismatches );
	m_ctlNumMismatches.SetWindowText( msg );

	m_ctlProgressSend.SetRange( 0, 128 );
	m_ctlProgressSend.SetPos( 0 );

}


#define FSE_THREADSTART			0x00000001
#define FSE_THREADCOMPLETE		0x00000002
#define FSE_UPDATECONTROLS		0x00000004
#define FSE_STATUSCONNECTED		0x00000008

afx_msg LRESULT CFileTransferServerView::OnFileSendEvent(WPARAM wParam, LPARAM lParam)
{
	switch ( wParam )
	{
	case FSE_THREADSTART:
		m_btnStartListen.EnableWindow( FALSE );
		m_ctlFileName.EnableWindow( FALSE );
		m_ctlSimulate.EnableWindow( FALSE );

		m_ctlStatus.SetWindowText( "Waiting for incoming connection ..." );

		break;

	case FSE_THREADCOMPLETE:
		m_btnStartListen.EnableWindow( TRUE );
		m_ctlFileName.EnableWindow( TRUE );
		m_ctlSimulate.EnableWindow( TRUE );

		m_ctlStatus.SetWindowText( "Status: Idle" );
		m_ctlProgressSend.SetPos( 0 );

		m_pThread = NULL;

		break;

	case FSE_UPDATECONTROLS:
		{
			CString msg;
			msg.Format( "Send mismatch events = %d", m_iNumMismatches );
			m_ctlNumMismatches.SetWindowText( msg );
		}

		break;

	case FSE_STATUSCONNECTED:
		m_ctlStatus.SetWindowText( "Connection accepted -- sending file ..." );


		break;

	default:
		ASSERT( FALSE );	// shouldn't get here
	}

	return 0L;
}

void CFileTransferServerView::OnDestroy() 
{
	// save settings in .INI file
	
	CWinApp* pApp = AfxGetApp();

	CString fName;
	m_ctlFileName.GetWindowText( fName );	
	pApp->WriteProfileString( "Dialog Settings", "Last File Name", fName );

	
	pApp->WriteProfileInt( "Dialog Settings", "Inject Mismatch Events", (BOOL)m_ctlSimulate.GetCheck() );


	CFormView::OnDestroy();
	
}


/////////////////////////////////////////////////////////////////////////////
// CFileTransferServerView printing

BOOL CFileTransferServerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFileTransferServerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFileTransferServerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CFileTransferServerView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CFileTransferServerView diagnostics

#ifdef _DEBUG
void CFileTransferServerView::AssertValid() const
{
	CFormView::AssertValid();
}

void CFileTransferServerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CFileTransferServerDoc* CFileTransferServerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFileTransferServerDoc)));
	return (CFileTransferServerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFileTransferServerView message handlers

void CFileTransferServerView::OnButtonListen() 
{
	if ( m_pThread != NULL )	// make certain thread is not already running
		return;

	CString fName;
	m_ctlFileName.GetWindowText( fName );

	// confirm that file exists

	WIN32_FIND_DATA  fd;
	HANDLE hFile = ::FindFirstFile( fName, &fd );

	if ( hFile == INVALID_HANDLE_VALUE )
	{
		// file must not exist -- warn user

		CString sMessage;
		sMessage.Format( "Could not find specified file\n\"%s\"", fName );
		
		::MessageBox( NULL, sMessage, "Could Not Find File",
			MB_OK | MB_ICONEXCLAMATION );

		::FindClose( hFile );
		return;

	}

	::FindClose( hFile );

	// now send the file
	
///	SendFileToRemoteRecipient( fName );	// now do this in a thread, below

	m_strFileName = fName;
	m_bSimulateEvents = m_ctlSimulate.GetCheck();

	m_pThread = ::AfxBeginThread( ThreadedSendFileToRemoteRecipient, (LPVOID) this, 
		THREAD_PRIORITY_BELOW_NORMAL );
	
}


#define PRE_AGREED_PORT		8686
#define SEND_BUFFER_SIZE	4096


BOOL CFileTransferServerView::SendFileToRemoteRecipient(CString fName)
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


UINT CFileTransferServerView::ThreadedSendFileToRemoteRecipient(LPVOID pVoid)
{
	CFileTransferServerView* pThis = (CFileTransferServerView*)pVoid;
	pThis->PostMessage( UWM_FILESENDEVENT, FSE_THREADSTART, 0L );
	
	AfxSocketInit(NULL);	// make certain this is done somewhere in each thread (usually in InitInstance for main thread)
	CSocket sockSrvr; 
	sockSrvr.Create(PRE_AGREED_PORT); // Creates our server socket
	sockSrvr.Listen(); // Start listening for the client at PORT
	CSocket sockConnection;
	sockSrvr.Accept(sockConnection); // Use another CSocket to accept the connection
	
	pThis->PostMessage( UWM_FILESENDEVENT, FSE_STATUSCONNECTED, 0L );
	
	// local variables used in file transfer (declared here to avoid "goto skips definition"-style compiler errors)

	int fileLength, cbLeftToSend;	// used to monitor the progress of a sending operation
	int simulate;	// used to simulate mismatch events (if designated by user)
	
	BYTE* sendData = NULL;	// pointer to buffer for sending data (memory is allocated after sending file size)
	
	int pbInterval = 0; int curPB = 0;	// progress bar variables
	
	
	CFile sourceFile;
	CFileException fe;
	BOOL bFileIsOpen = FALSE;
	
	if( !( bFileIsOpen = sourceFile.Open( pThis->m_strFileName, CFile::modeRead | CFile::typeBinary, &fe ) ) )
	{
		TCHAR strCause[256];
		fe.GetErrorMessage( strCause, 255 );
		TRACE( "SendFileToRemoteRecipient encountered an error while opening the local file\n"
			"\tFile name = %s\n\tCause = %s\n\tm_cause = %d\n\tm_IOsError = %d\n",
			fe.m_strFileName, strCause, fe.m_cause, fe.m_lOsError );

		/* you should handle the error here */

		goto PreReturnCleanup;
	}

	
	
	// first send length of file
	
	fileLength = sourceFile.GetLength();
	fileLength = htonl( fileLength );
	
	cbLeftToSend = sizeof( fileLength );
	
	// Inject mismatch events (if selected by user)
	// Seed the random-number generator with current time 
	srand( (unsigned)time( NULL ) );
	
	simulate = 1 + rand() % 2;	// either 1 or 2
	simulate = ( pThis->m_bSimulateEvents ) ? simulate : 0;	// zero if user de-selected event simulation
	
	do
	{
		int cbBytesSent;
		BYTE* bp = (BYTE*)(&fileLength) + sizeof(fileLength) - cbLeftToSend;
		cbBytesSent = sockConnection.Send( bp, cbLeftToSend - simulate );
		simulate = 0;
		
		// test for errors and get out if they occurred
		if ( cbBytesSent == SOCKET_ERROR )
		{
			int iErr = ::GetLastError();
			TRACE( "SendFileToRemoteRecipient returned a socket error while sending file length\n"
				"\tNumber of Bytes sent = %d\n"
				"\tGetLastError = %d\n", cbBytesSent, iErr );
			
			/* you should handle the error here */
			
			goto PreReturnCleanup;
		}
		
		// data was successfully sent, so account for it with already-sent data
		cbLeftToSend -= cbBytesSent;
	}
	while ( cbLeftToSend>0 );
	
	
	// now send the file's data
	
	sendData = new BYTE[SEND_BUFFER_SIZE]; 
	
	cbLeftToSend = sourceFile.GetLength();
	
	
	// set up progress bar
	
	fileLength = cbLeftToSend;
	pbInterval = fileLength>>7;		// divide by 128
	curPB = 0;
	
	pThis->m_ctlProgressSend.PostMessage( PBM_SETPOS, (WPARAM) curPB, 0L );
	
	do
	{
		// read next chunk of SEND_BUFFER_SIZE bytes from file
	
		int sendThisTime, doneSoFar, buffOffset;
		
		sendThisTime = sourceFile.Read( sendData, SEND_BUFFER_SIZE );
		buffOffset = 0;
		
		// simulate mismatch events
		
		simulate = rand();
		simulate = ( simulate>RAND_MAX/10 ) ? 0 : 2560*simulate/RAND_MAX ;	// up to 256 but only inject mismatches 10% of the time
		simulate = ( pThis->m_bSimulateEvents ) ? simulate : 0 ;	// zero if user de-selected event simulation
		
		do
		{
			doneSoFar = sockConnection.Send( sendData + buffOffset, sendThisTime - simulate ); 
			simulate = 0;
			
			// test for errors and get out if they occurred
			if ( doneSoFar == SOCKET_ERROR )
			{
				int iErr = ::GetLastError();
				TRACE( "SendFileToRemoteRecipient returned a socket error while sending chunked file data\n"
					"\tNumber of Bytes sent = %d\n"
					"\tGetLastError = %d\n", doneSoFar, iErr );
				
				/* you should handle the error here */
				
				goto PreReturnCleanup;
			}
			
			// data was successfully sent, so account for it with already-sent data
			// but first, advise main thread of a send mismatch if everything was not sent in one shot
			
			if ( doneSoFar != sendThisTime )
			{
				pThis->m_iNumMismatches++;
				pThis->PostMessage( UWM_FILESENDEVENT, FSE_UPDATECONTROLS, 0L );
			}
			
			buffOffset += doneSoFar;
			sendThisTime -= doneSoFar;
			cbLeftToSend -= doneSoFar;
		}
		while ( sendThisTime > 0 );
		
		// update progress bar
		
		if ( pbInterval*curPB < (fileLength-cbLeftToSend) )
		{
			curPB++;
			pThis->m_ctlProgressSend.PostMessage( PBM_SETPOS, (WPARAM) curPB, 0L );
		}
		
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
	
	// advise main thread that we're completed
	pThis->PostMessage( UWM_FILESENDEVENT, FSE_THREADCOMPLETE, 0L );
	
	return 0;
	
}
