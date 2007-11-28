// HoldHead.cpp : implementation file
//

#include "stdafx.h"
#include "wed.h"
#include "HoldHead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// HoldHead dialog


HoldHead::HoldHead(CWnd* pParent /*=NULL*/)
	: CDialog(HoldHead::IDD, pParent)
{
	//{{AFX_DATA_INIT(HoldHead)
	m_edit1 = _T("");
	m_edit10 = _T("");
	m_edit2 = _T("");
	m_edit3 = _T("");
	m_edit4 = _T("");
	m_edit5 = _T("");
	m_edit6 = _T("");
	m_edit7 = _T("");
	m_edit8 = _T("");
	m_edit9 = _T("");
	m_edit11 = _T("");
	//}}AFX_DATA_INIT
}


void HoldHead::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(HoldHead)
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_EDIT10, m_edit10);
	DDX_Text(pDX, IDC_EDIT2, m_edit2);
	DDX_Text(pDX, IDC_EDIT3, m_edit3);
	DDX_Text(pDX, IDC_EDIT4, m_edit4);
	DDX_Text(pDX, IDC_EDIT5, m_edit5);
	DDX_Text(pDX, IDC_EDIT6, m_edit6);
	DDX_Text(pDX, IDC_EDIT7, m_edit7);
	DDX_Text(pDX, IDC_EDIT8, m_edit8);
	DDX_Text(pDX, IDC_EDIT9, m_edit9);
	DDX_Text(pDX, IDC_EDIT11, m_edit11);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(HoldHead, CDialog)
	//{{AFX_MSG_MAP(HoldHead)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// HoldHead message handlers

BOOL HoldHead::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetWindowText(m_edit11);
	return TRUE;  
}
