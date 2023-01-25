// FileTransferServerView.h : interface of the CFileTransferServerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILETRANSFERSERVERVIEW_H__A79DC164_19C5_4ADD_93E1_F0CC5F9F9B70__INCLUDED_)
#define AFX_FILETRANSFERSERVERVIEW_H__A79DC164_19C5_4ADD_93E1_F0CC5F9F9B70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFileTransferServerView : public CFormView
{
protected: // create from serialization only
	CFileTransferServerView();
	DECLARE_DYNCREATE(CFileTransferServerView)

public:
	//{{AFX_DATA(CFileTransferServerView)
	enum { IDD = IDD_FILETRANSFERSERVER_FORM };
	CButton	m_ctlSimulate;
	CButton	m_btnStartListen;
	CStatic	m_ctlStatus;
	CStatic	m_ctlNumMismatches;
	CProgressCtrl	m_ctlProgressSend;
	CEdit	m_ctlFileName;
	//}}AFX_DATA

// Attributes
public:
	CFileTransferServerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileTransferServerView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL m_bSimulateEvents;
	CWinThread* m_pThread;
	static UINT ThreadedSendFileToRemoteRecipient( LPVOID pVoid );
	int m_iNumMismatches;
	CString m_strFileName;
	BOOL SendFileToRemoteRecipient( CString fName );
	virtual ~CFileTransferServerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFileTransferServerView)
	afx_msg void OnButtonListen();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg LRESULT OnFileSendEvent(WPARAM, LPARAM);

	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FileTransferServerView.cpp
inline CFileTransferServerDoc* CFileTransferServerView::GetDocument()
   { return (CFileTransferServerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILETRANSFERSERVERVIEW_H__A79DC164_19C5_4ADD_93E1_F0CC5F9F9B70__INCLUDED_)
