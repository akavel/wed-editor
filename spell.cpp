// spell.cpp : implementation file
//

#include "stdafx.h"
#include "wed.h"
#include "spell.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// spell dialog


spell::spell(CWnd* pParent /*=NULL*/)
	: CDialog(spell::IDD, pParent)
{
	//{{AFX_DATA_INIT(spell)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void spell::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(spell)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(spell, CDialog)
	//{{AFX_MSG_MAP(spell)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// spell message handlers
