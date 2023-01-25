// FileTransferServer.h : main header file for the FILETRANSFERSERVER application
//

#if !defined(AFX_FILETRANSFERSERVER_H__DF889028_00A6_4F2A_907A_185A69D0FB5E__INCLUDED_)
#define AFX_FILETRANSFERSERVER_H__DF889028_00A6_4F2A_907A_185A69D0FB5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFileTransferServerApp:
// See FileTransferServer.cpp for the implementation of this class
//

class CFileTransferServerApp : public CWinApp
{
public:
	CFileTransferServerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileTransferServerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CFileTransferServerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILETRANSFERSERVER_H__DF889028_00A6_4F2A_907A_185A69D0FB5E__INCLUDED_)
