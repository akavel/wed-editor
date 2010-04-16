// SelList.cpp : implementation file
//

#include "stdafx.h"
#include "wed.h"
#include "SelList.h"
#include "mxpad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SelList

SelList::SelList()
{


}

SelList::~SelList()
{
}


BEGIN_MESSAGE_MAP(SelList, CCheckListBox)
	//{{AFX_MSG_MAP(SelList)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SelList message handlers

BOOL SelList::OnInitDialog()
{
	OnInitDialog();
		return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int SelList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CCheckListBox::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: Add extra initialization here


	// TODO: Add your specialized creation code here

	return 0;
}
