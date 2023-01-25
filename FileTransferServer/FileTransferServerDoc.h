// FileTransferServerDoc.h : interface of the CFileTransferServerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILETRANSFERSERVERDOC_H__16141209_03A2_4524_B2B1_8BD90839C922__INCLUDED_)
#define AFX_FILETRANSFERSERVERDOC_H__16141209_03A2_4524_B2B1_8BD90839C922__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFileTransferServerDoc : public CDocument
{
protected: // create from serialization only
	CFileTransferServerDoc();
	DECLARE_DYNCREATE(CFileTransferServerDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileTransferServerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFileTransferServerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFileTransferServerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILETRANSFERSERVERDOC_H__16141209_03A2_4524_B2B1_8BD90839C922__INCLUDED_)
