/////////////////////////////////////////////////////////////////////////////
// About dialog
//

#include "stdafx.h"
#include "io.h"

#include "wed.h"

#include "StrList.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "wedDoc.h"
#include "wedView.h"
#include "splash.h"
#include "editor.h"
#include "wedview.h"
#include "mxpad.h"
#include "build.h"

#include "about.h"

/////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Declare the variables needed

	#ifdef _DEBUG
    static CMemoryState oldMemState2, newMemState2, diffMemState2;
	#endif

/////////////////////////////////////////////////////////////////////////////

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	#ifdef _DEBUG
    oldMemState2.Checkpoint();
	#endif

	//{{AFX_DATA_INIT(CAboutDlg)
	m_build = _T("");
	m_date = _T("");
	m_reg = _T("");
	//}}AFX_DATA_INIT
}

/////////////////////////////////////////////////////////////////////////////

CAboutDlg::~CAboutDlg()
{
	//DestroyWindow();

	#ifdef _DEBUG
    newMemState2.Checkpoint();

    if( diffMemState2.Difference( oldMemState2, newMemState2 ) )
    	{
		diffMemState2.DumpAllObjectsSince();
		//P2N("Aboutdlg Memory leaked!\r\n");
        //TRACE( "Memory leaked!\n" );
    	}
	#endif
}

/////////////////////////////////////////////////////////////////////////////

void 	CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_EDIT1, m_build);
	DDX_Text(pDX, IDC_EDIT2, m_date);
	DDX_Text(pDX, IDC_EDIT3, m_reg);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

BOOL 	CAboutDlg::OnInitDialog()

{
	// Get fresh copy of build/date
	m_build = CURRENTBUILD;
	m_date	= CURRENTDATE;
	m_reg	= GetRegStr();

	CDialog::OnInitDialog();
	return TRUE;
}

// EOF


