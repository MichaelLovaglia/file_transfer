// FileTransferClientDoc.h : interface of the CFileTransferClientDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILETRANSFERCLIENTDOC_H__6CDF6211_00F7_4EA6_B4CA_15E1F4281AF9__INCLUDED_)
#define AFX_FILETRANSFERCLIENTDOC_H__6CDF6211_00F7_4EA6_B4CA_15E1F4281AF9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFileTransferClientDoc : public CDocument
{
protected: // create from serialization only
	CFileTransferClientDoc();
	DECLARE_DYNCREATE(CFileTransferClientDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileTransferClientDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFileTransferClientDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFileTransferClientDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILETRANSFERCLIENTDOC_H__6CDF6211_00F7_4EA6_B4CA_15E1F4281AF9__INCLUDED_)
