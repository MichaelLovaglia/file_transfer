// FileTransferServerDoc.cpp : implementation of the CFileTransferServerDoc class
//

#include "stdafx.h"
#include "FileTransferServer.h"

#include "FileTransferServerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileTransferServerDoc

IMPLEMENT_DYNCREATE(CFileTransferServerDoc, CDocument)

BEGIN_MESSAGE_MAP(CFileTransferServerDoc, CDocument)
	//{{AFX_MSG_MAP(CFileTransferServerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileTransferServerDoc construction/destruction

CFileTransferServerDoc::CFileTransferServerDoc()
{
	// TODO: add one-time construction code here

}

CFileTransferServerDoc::~CFileTransferServerDoc()
{
}

BOOL CFileTransferServerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFileTransferServerDoc serialization

void CFileTransferServerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFileTransferServerDoc diagnostics

#ifdef _DEBUG
void CFileTransferServerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFileTransferServerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFileTransferServerDoc commands
