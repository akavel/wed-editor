// gotoline.cpp : implementation file
//

#include "stdafx.h"
#include "wed.h"
#include "gotoline.h"

#include "srcsel.h"
#include "strlist.h"
#include "Weddoc.h"
#include "WedView.h"
#include "mxpad.h"
#include "editor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGotoLine dialog


CGotoLine::CGotoLine(CWnd* pParent /*=NULL*/)
	: CDialog(CGotoLine::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGotoLine)
	m_str = _T("");
	m_prompt = _T("");
	//}}AFX_DATA_INIT
	m_esc = FALSE;

}


void CGotoLine::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGotoLine)
	DDX_Text(pDX, IDC_EDIT1, m_str);
	DDX_Text(pDX, IDC_EDIT2, m_prompt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGotoLine, CDialog)
	//{{AFX_MSG_MAP(CGotoLine)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGotoLine message handlers


BOOL CGotoLine::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetWindowText(caption);
	return TRUE;
}

void CGotoLine::OnCancel()
{
	// TODO: Add extra cleanup here
	m_esc = TRUE;
	CDialog::OnCancel();
}
