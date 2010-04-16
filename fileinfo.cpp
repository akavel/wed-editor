// FileInfo.cpp : implementation file
//



#include "stdafx.h"
#include "wed.h"
#include "MainFrm.h"
#include "StrList.h"
#include "wedDoc.h"
#include "wedView.h"
#include "FileInfo.h"
#include "mxpad.h"
#include "holdhead.h"
#include "editor.h"
#include "misc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// FileInfo dialog


FileInfo::FileInfo(CWnd* pParent /*=NULL*/)
	: CDialog(FileInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(FileInfo)
	m_1 = _T("");
	m_2 = _T("");
	m_3 = _T("");
	m_4 = _T("");
	m_5 = _T("");
	m_6 = _T("");
	m_7 = _T("");
	m_8 = _T("");
	m_9 = _T("");
	m_10 = _T("");
	m_11 = _T("");
	m_check1 = FALSE;
	m_check2 = FALSE;
	//}}AFX_DATA_INIT
}


void FileInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FileInfo)
	DDX_Text(pDX, IDC_EDIT1, m_1);
	DDX_Text(pDX, IDC_EDIT2, m_2);
	DDX_Text(pDX, IDC_EDIT3, m_3);
	DDX_Text(pDX, IDC_EDIT4, m_4);
	DDX_Text(pDX, IDC_EDIT5, m_5);
	DDX_Text(pDX, IDC_EDIT6, m_6);
	DDX_Text(pDX, IDC_EDIT7, m_7);
	DDX_Text(pDX, IDC_EDIT8, m_8);
	DDX_Text(pDX, IDC_EDIT9, m_9);
	DDX_Text(pDX, IDC_EDIT10, m_10);
	DDX_Text(pDX, IDC_EDIT12, m_11);
	DDX_Check(pDX, IDC_CHECK1, m_check1);
	DDX_Check(pDX, IDC_CHECK2, m_check2);
	DDX_Check(pDX, IDC_CHECK3, m_check3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FileInfo, CDialog)
	//{{AFX_MSG_MAP(FileInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FileInfo message handlers

int FileInfo::DoModal()
{
    CWedDoc* pDoc = v1->GetDocument(); ASSERT_VALID(pDoc);
    CString file;
	CTime tt;

    file = pDoc->GetPathName();
	m_1 = file;

	file.Format("%d", pDoc->docstat.st_size);
	m_2 =  file;

	tt = pDoc->docstat.st_mtime;
	file = tt.Format("%c");
	m_9 =  file;

	tt = pDoc->docstat.st_atime;
	file = tt.Format("%c");
	m_10 =  file;

	file.Format("%d", pDoc->origlines);
	m_3 =  file;

	file.Format("%d", pDoc->strlist.GetCount());
	m_4 =  file;

	file.Format("%d", pDoc->undo.GetCount());
	m_5 =  file;

	file.Format("%d", pDoc->redo.GetCount());
	m_6 =  file;

	if(pDoc->IsModified())
		m_7 =  "Yes";
	else
		m_7 =  "No";

	CString droot;
	int hhh = HashString(pDoc->GetPathName());
	droot.Format("%x", hhh);
	m_11 =  droot;

	m_check1 = pDoc->unix;
	m_check2 = pDoc->readonly;
	m_check3 = pDoc->spaceify;

	return CDialog::DoModal();
}

void FileInfo::OnOK()

{
	CDialog::OnOK();

    CWedDoc* pDoc = v1->GetDocument(); ASSERT_VALID(pDoc);

	pDoc->unix		= m_check1;
	pDoc->readonly	= m_check2;
	pDoc->spaceify	= m_check3;
}

