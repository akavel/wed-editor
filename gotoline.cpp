// gotoline.cpp : implementation file
//

#include "stdafx.h"
#include "wed.h"
#include "gotoline.h"

#include "srcsel.h"					  
#include "strlist.h"
#include "Weddoc.h"
#include "WedView.h"
#include "notepad.h"
#include "editor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cgotoline dialog


Cgotoline::Cgotoline(CWnd* pParent /*=NULL*/)
	: CDialog(Cgotoline::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cgotoline)
	m_str = _T("");
	m_prompt = _T("");
	//}}AFX_DATA_INIT
	m_esc = FALSE;

}


void Cgotoline::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cgotoline)
	DDX_Text(pDX, IDC_EDIT1, m_str);
	DDX_Text(pDX, IDC_EDIT2, m_prompt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cgotoline, CDialog)
	//{{AFX_MSG_MAP(Cgotoline)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cgotoline message handlers


BOOL Cgotoline::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetWindowText(caption);
	return TRUE;
}

void Cgotoline::OnCancel() 
{
	// TODO: Add extra cleanup here
	m_esc = TRUE;	
	CDialog::OnCancel();
}
