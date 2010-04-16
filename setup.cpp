// Setup.cpp : implementation file
//

#include "stdafx.h"
#include "wed.h"
#include "mxpad.h"


#include "Setup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// setup dialog

setup::setup(char * caption)
{
	//{{AFX_DATA_INIT(setup)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	//*p1 = new page1 "xx";
	P2N("Init setup\r\n");
	CPropertySheet::CPropertySheet(caption);
}


void setup::DoDataExchange(CDataExchange* pDX)
{
	CPropertySheet::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(setup)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(setup, CPropertySheet)
	//{{AFX_MSG_MAP(setup)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// setup message handlers
