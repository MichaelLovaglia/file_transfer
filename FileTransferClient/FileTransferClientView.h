// FileTransferClientView.h : interface of the CFileTransferClientView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILETRANSFERCLIENTVIEW_H__A67112BD_5283_46EF_8DCA_A4CA9F3FE816__INCLUDED_)
#define AFX_FILETRANSFERCLIENTVIEW_H__A67112BD_5283_46EF_8DCA_A4CA9F3FE816__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFileTransferClientView : public CFormView
{
protected: // create from serialization only
	CFileTransferClientView();
	DECLARE_DYNCREATE(CFileTransferClientView)

public:
	//{{AFX_DATA(CFileTransferClientView)
	enum { IDD = IDD_FILETRANSFERCLIENT_FORM };
	CButton	m_ctlSimulate;
	CStatic	m_ctlStatus;
	CStatic	m_ctlNumMismatches;
	CProgressCtrl	m_ctlProgressGet;
	CEdit	m_ctlFileName;
	CComboBox	m_cbIPAddresses;
	CIPAddressCtrl	m_ctlTargetIP;
	CButton	m_btnGetFile;
	//}}AFX_DATA

// Attributes
public:
	CFileTransferClientDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileTransferClientView)
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
	CString m_strTargetIP;
	CString m_strFileName;
	int m_iNumMismatches;
	static UINT ThreadedGetFileFromRemoteSender( LPVOID pVoid );
	BOOL GetFileFromRemoteSender( CString strIP, CString fName );
	virtual ~CFileTransferClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFileTransferClientView)
	afx_msg void OnFieldChangedIPAddress(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonGetFile();
	afx_msg void OnSelChangeComboIPAddresses();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg LRESULT OnGetFileEvent(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FileTransferClientView.cpp
inline CFileTransferClientDoc* CFileTransferClientView::GetDocument()
   { return (CFileTransferClientDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILETRANSFERCLIENTVIEW_H__A67112BD_5283_46EF_8DCA_A4CA9F3FE816__INCLUDED_)
