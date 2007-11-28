/////////////////////////////////////////////////////////////////////////////
// Register.cpp : implementation file
//

#include "stdafx.h"
#include "wed.h"
#include "StrList.h"
#include "wedDoc.h"
#include "wedView.h"
#include "editor.h"
#include "misc.h"
#include "notepad.h"
#include "gotoline.h"

#include "Register.h"

/////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

static	Cgotoline   gt;
static 	int tries = 0;

/////////////////////////////////////////////////////////////////////////////
// Register dialog

Register::Register(CWnd* pParent /*=NULL*/)
	: CDialog(Register::IDD, pParent)
{
	//{{AFX_DATA_INIT(Register)
	m_reg = _T("");
	m_company = _T("");
	m_pass = _T("");
	//}}AFX_DATA_INIT
}

/////////////////////////////////////////////////////////////////////////////
// void Register::DoDataExchange(CDataExchange* pDX)

void Register::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Register)
	DDX_Control(pDX, IDC_EDIT4, m_show);
	DDX_Text(pDX, IDC_EDIT1, m_reg);
	DDX_Text(pDX, IDC_EDIT2, m_company);
	DDX_Text(pDX, IDC_EDIT3, m_pass);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(Register, CDialog)
	//{{AFX_MSG_MAP(Register)
	ON_EN_KILLFOCUS(IDC_EDIT1, OnKillfocusEdit1)
	ON_EN_KILLFOCUS(IDC_EDIT2, OnKillfocusEdit2)
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Register message handlers
// void Register::OnKillfocusEdit1()

void Register::OnKillfocusEdit1()
{
	UpdateData();
	m_show.SetWindowText(m_reg + " " + m_company);
}

/////////////////////////////////////////////////////////////////////////////
// void Register::OnKillfocusEdit2()

void Register::OnKillfocusEdit2()
{
	UpdateData();
	m_show.SetWindowText(m_reg + " " + m_company);
}

/////////////////////////////////////////////////////////////////////////////
// void Register::OnOK()

void Register::OnOK()
{
	int sum = 0;

	if(tries++ > 5)
		{
		AfxMessageBox("Too many tries."); return;
		}
	UpdateData();

	m_pass.MakeUpper();
	sum += SumStr(m_pass);
	sum += SumStr(m_reg);
	sum += SumStr(m_company);

	CString num;
	num.Format("pass sum %d", sum);	message(num);

	// Check Password
	//if(sum % 50 || m_pass.GetLength() < 4)
	//	{
	//	AfxMessageBox("Invalid password, Please check spelling.");
	//	}
	//else
		{
		// Update registry with new info:
		PutRegStr(m_reg + " " + m_company, m_pass);
		CDialog::OnOK();
		}
}

/////////////////////////////////////////////////////////////////////////////
// int  Register::SumStr(CString &str)
// Add them together

int  Register::SumStr(CString &str)
{
    CString str2 = str;
	int sum = 0, loop, lim = str2.GetLength();

	str2.MakeUpper();

	for(loop = 0; loop < lim; loop++)
		{
		char chh = str2.GetAt(loop);

		if(isalnum(chh))
			sum += chh;
		}
	return(sum);
}

/////////////////////////////////////////////////////////////////////////////
//
// void Register::OnLButtonDblClk(UINT nFlags, CPoint point)

void Register::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if(point.x < 10 && point.y < 10)
		{
  		CString		num;
		int			forw = 0, back =0;

    	//gt.m_str    =   old_brace;
    	gt.m_prompt =   "Master pass:";
    	gt.caption  =   "Auth";
    	gt.DoModal();

		if(gt.m_str == "1234")
			{
			Genpass();
			}
		}
	CDialog::OnLButtonDblClk(nFlags, point);
}

/////////////////////////////////////////////////////////////////////////////
// void Register::Genpass()

void Register::Genpass()

{
	int sum = 0, sum2;
	int loop, loop2;

	UpdateData();

	sum += SumStr(m_reg); sum += SumStr(m_company);
	srand(clock());
	// Loop until found
	for(loop2 = 0; loop2 < 10000; loop2++)
		{
		m_pass = "";
		// Produce base
		for(loop = 0; loop < 8; loop++)
			m_pass += (char)(rand() % ('Z'-'A') + 'A');

		sum2 = sum + SumStr(m_pass);

		// Terminal condition
		if(!(sum2 % 50))
			break;
		}
	SetDlgItemText(IDC_EDIT3, m_pass);

	CFile cf; CString fname;
	fname.Format("%s%s", dataroot, "pass.txt");
	if( cf.Open( fname, CFile::modeCreate | CFile::modeWrite))
		{
		cf.Write(m_reg, 	m_reg.GetLength()); 	cf.Write("\r\n", 2);
		cf.Write(m_company, m_company.GetLength()); cf.Write("\r\n", 2);
		cf.Write(m_pass, 	m_pass.GetLength()); 	cf.Write("\r\n", 2);
		cf.Close();
		}
	else
		{
		//PrintToNotepad("Cannot open pass file: %s\r\n", fname);
		}
}

// EOF
