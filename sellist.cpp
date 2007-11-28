// sellist.cpp : implementation file
//

#include "stdafx.h"
#include "wed.h"
#include "sellist.h"
#include "notepad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// sellist

sellist::sellist()
{

	 
}

sellist::~sellist()
{
}


BEGIN_MESSAGE_MAP(sellist, CCheckListBox)
	//{{AFX_MSG_MAP(sellist)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// sellist message handlers

BOOL sellist::OnInitDialog() 
{
	OnInitDialog();
		return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int sellist::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CCheckListBox::OnCreate(lpCreateStruct) == -1)
		return -1;
  
	// TODO: Add extra initialization here
	

	// TODO: Add your specialized creation code here
	
	return 0;
}
