// FileTransferClientDoc.cpp : implementation of the CFileTransferClientDoc class
//

#include "stdafx.h"
#include "FileTransferClient.h"

#include "FileTransferClientDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileTransferClientDoc

IMPLEMENT_DYNCREATE(CFileTransferClientDoc, CDocument)

BEGIN_MESSAGE_MAP(CFileTransferClientDoc, CDocument)
	//{{AFX_MSG_MAP(CFileTransferClientDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileTransferClientDoc construction/destruction

CFileTransferClientDoc::CFileTransferClientDoc()
{
	// TODO: add one-time construction code here

}

CFileTransferClientDoc::~CFileTransferClientDoc()
{
}

BOOL CFileTransferClientDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFileTransferClientDoc serialization

void CFileTransferClientDoc::Serialize(CArchive& ar)
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
// CFileTransferClientDoc diagnostics

#ifdef _DEBUG
void CFileTransferClientDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFileTransferClientDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFileTransferClientDoc commands
