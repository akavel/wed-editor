// goto.cpp : implementation file
//

#include "stdafx.h"
#include "wed.h"
#include "goto.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cgoto dialog


Cgoto::Cgoto(CWnd* pParent /*=NULL*/)
    : CDialog(Cgoto::IDD, pParent)
{
    //{{AFX_DATA_INIT(Cgoto)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


void Cgoto::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(Cgoto)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cgoto, CDialog)
    //{{AFX_MSG_MAP(Cgoto)
        // NOTE: the ClassWizard will add message map macros here
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCgoto message handlers
