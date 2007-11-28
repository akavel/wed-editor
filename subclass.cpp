// SubClass.cpp : implementation file
//

#include "stdafx.h"
#include "wed.h"
#include "SubClass.h"
#include "strlist.h"
#include "Weddoc.h"
#include "WedView.h"
#include "notepad.h"
#include "editor.h"
#include "undo.h"
#include "diff.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SubClass dialog

	int gl_sc_x = 0; // = 100;
	int gl_sc_y = 0; // = 100;

SubClass::SubClass(CWnd* pParent /*=NULL*/)
	: CDialog(SubClass::IDD, pParent)
{
	//{{AFX_DATA_INIT(SubClass)
	m_result = _T("");
	//}}AFX_DATA_INIT

	m_ret = SP_OK;
}					 


void SubClass::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SubClass)
	DDX_Control(pDX, IDC_BUTTON4, m_b4);
	DDX_Control(pDX, IDC_BUTTON1, m_b1);
	DDX_Control(pDX, IDCANCEL, m_cancel);
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_CBString(pDX, IDC_COMBO1, m_result);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SubClass, CDialog)
	//{{AFX_MSG_MAP(SubClass)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_WM_MOVE()
	ON_WM_CLOSE()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SubClass message handlers

void SubClass::OnButton1()
{
	m_ret = SP_IGNORE_ALL;
	OnOK();
}

void SubClass::OnButton2()
{
	m_ret = SP_IGNORE_ALL;
	OnOK();
}

void SubClass::OnButton4()
{
	m_ret = SP_LEARN;
	OnOK();
}

void SubClass::OnCancel()
{
	m_ret = SP_STOP;
	CDialog::OnCancel();
}

#define MAX_READ 128


BOOL SubClass::OnInitDialog()
{
	CDialog::OnInitDialog();
	char	buffer[MAX_READ];

	if(!gl_sc_x)
		{
		if(currentedit)
			{	
			RECT rct, us;
			GetWindowRect(&us);
			currentedit->GetWindowRect(&rct);
			gl_sc_x = (rct.right - rct.left)/2 -
						(us.right - us.left)/2;
			gl_sc_y = (rct.bottom - rct.top)/2 -
						(us.bottom - us.top)/2;
			}
		}
	SetWindowPos(NULL, gl_sc_x, gl_sc_y, 0 ,
		       0,  SWP_NOOWNERZORDER | SWP_NOSIZE );


	// Fill in selection
	while(TRUE)
		{
		if(!fgets(buffer, MAX_READ, m_fp) )
			break;

		buffer[strlen(buffer)-1] = '\0';

		// Is ascii?
		if(tolower(buffer[0]) >= 'a' && tolower(buffer[0]) <= 'z')
			{
			if(tolower(buffer[0]) !=  tolower(m_result[0]))
				break;
			}

		if(strdiff(m_result, buffer) < 2)
			m_combo.AddString(buffer);
		}
	return TRUE;
}

void SubClass::OnSelchangeCombo1()

{
	int sel = m_combo.GetCurSel();
	if(sel < 0 )
		return;

	CString str;
	m_combo.GetLBText(sel, str);
	m_result = str;
}

void SubClass::OnKillFocus(CWnd* pNewWnd) 
{
	CDialog::OnKillFocus(pNewWnd);
	
	RECT rct;
	GetWindowRect(&rct);
	gl_sc_x = rct.left;
	gl_sc_y = rct.top;
}
