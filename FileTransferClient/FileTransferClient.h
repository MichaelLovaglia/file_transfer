// FileTransferClient.h : main header file for the FILETRANSFERCLIENT application
//

#if !defined(AFX_FILETRANSFERCLIENT_H__3C53A771_FDA7_4259_8D2C_050BFE963F84__INCLUDED_)
#define AFX_FILETRANSFERCLIENT_H__3C53A771_FDA7_4259_8D2C_050BFE963F84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFileTransferClientApp:
// See FileTransferClient.cpp for the implementation of this class
//

class CFileTransferClientApp : public CWinApp
{
public:
	CFileTransferClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileTransferClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CFileTransferClientApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILETRANSFERCLIENT_H__3C53A771_FDA7_4259_8D2C_050BFE963F84__INCLUDED_)
