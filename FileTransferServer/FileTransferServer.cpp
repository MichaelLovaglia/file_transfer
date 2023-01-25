// FileTransferServer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "FileTransferServer.h"

#include "MainFrm.h"
#include "FileTransferServerDoc.h"
#include "FileTransferServerView.h"


#include <shlwapi.h>
#pragma comment( lib, "shlwapi.lib" )


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileTransferServerApp

BEGIN_MESSAGE_MAP(CFileTransferServerApp, CWinApp)
	//{{AFX_MSG_MAP(CFileTransferServerApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileTransferServerApp construction

CFileTransferServerApp::CFileTransferServerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFileTransferServerApp object

CFileTransferServerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CFileTransferServerApp initialization

BOOL CFileTransferServerApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	// don't need this registry stuff
	
///	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

///	LoadStdProfileSettings();  // Load standard INI file options (including MRU)
	
	// initialize path name for current module, and use it for .INI file creation
	
	CString sModulePath;
	::GetModuleFileName( NULL, sModulePath.GetBuffer(255), 255 );
	::PathMakePretty( sModulePath.GetBuffer(255) );
	::PathRemoveFileSpec( sModulePath.GetBuffer(255) );
	sModulePath.ReleaseBuffer();

	// Use an .ini paradigm to load settings, rather than the registry
	// This makes for cleaner installs/uninstalls, and further lets us put
	// a ton of stuff in the .ini file, that we would never put in the registry
	// because of its bulk.  See

	// http://msdn.microsoft.com/library/default.asp?url=/library/en-us/vclib/html/_mfc_cwinapp.3a3a.m_pszprofilename.asp

	//First free the string allocated by MFC at CWinApp startup

	free((void*)this->m_pszProfileName);
	
	//Change the name of the .INI file.
	//The CWinApp destructor will free the memory.
	
	CString tINI = sModulePath + "\\FileTransferServer.ini";
	
	this->m_pszProfileName=_tcsdup( tINI );

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CFileTransferServerDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CFileTransferServerView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CFileTransferServerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CFileTransferServerApp message handlers

