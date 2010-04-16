/////////////////////////////////////////////////////////////////////////////
// Search.cpp : implementation file
//

#include "stdafx.h"
#include "wed.h"
#include "strlist.h"
#include "weddoc.h"
#include "wedview.h"
#include "Search.h"
#include "mxpad.h"
#include "editor.h"
#include "misc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Search dialog

Search::Search(CWnd* pParent /*=NULL*/)
	: CDialog(Search::IDD, pParent)
{
	//{{AFX_DATA_INIT(Search)
	m_combo1 = _T("");
	m_combo2 = _T("");
	//}}AFX_DATA_INIT
	m_taush = FALSE;
	m_stype = 0;
}

/////////////////////////////////////////////////////////////////////////////
// void Search::DoDataExchange(CDataExchange* pDX)

void Search::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Search)
	DDX_Control(pDX, IDC_COMBO2, m_com2);
	DDX_Control(pDX, IDC_COMBO1, m_com1);
	DDX_CBString(pDX, IDC_COMBO1, m_combo1);
	DDX_CBString(pDX, IDC_COMBO2, m_combo2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(Search, CDialog)
	//{{AFX_MSG_MAP(Search)
	ON_BN_CLICKED(IDCANCEL2, OnCancel2)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDCANCEL3, OnCancel3)
	ON_BN_CLICKED(IDCANCEL4, OnCancel4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// void Search::OnCancel()

void Search::OnCancel()
{
	m_esc = TRUE;
	CDialog::OnCancel();
}

/////////////////////////////////////////////////////////////////////////////
// void Search::OnOK()

void Search::OnOK()
{
	UpdateData();
	m_files.RemoveAll();

	// Save MRU search list
	if(m_combo1 != "")
		{
		// Do not add empty string
		CString latest;

		if (!combofill.IsEmpty())
			latest = combofill.GetHead();

		if(latest != m_combo1)
			combofill.AddHead(m_combo1);
		}

	// Limit to 12 pushed entries
	if(combofill.GetCount() > 12)
		{
		combofill.RemoveTail();
		}

	CString str3;
	int lim = m_list.GetCount();
	for(int loop3 = 0; loop3 < lim; loop3++)
		{
		if(m_list.GetCheck(loop3))
			{
			m_list.GetText(loop3, str3);
			m_files.AddTail(str3);
			}
		}
	P2N("Searching for %s as type %d\r\n",
						m_combo1, m_stype);
	CDialog::OnOK();
}

/////////////////////////////////////////////////////////////////////////////
// BOOL Search::OnInitDialog()

BOOL Search::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_list.SubclassDlgItem(IDC_LIST1, this);
	m_esc = FALSE;
	m_files.RemoveAll();

  	if(m_taush)
		{
		CWnd  *ed2 = GetDlgItem(IDC_COMBO2);
		ASSERT(ed2);
		ed2->EnableWindow();
		SetWindowText("Search/Replace");
		}
	else
		{
		SetWindowText("Search");
		}

   	int count = 0;
	CWedDoc* mydoc = NULL;
	if(currentedit)
		{
		ASSERT_VALID(currentedit);
		mydoc = ((CWedView*)currentedit)->GetDocument();
		ASSERT_VALID(mydoc);

		CString str =  mydoc->GetPathName();
		m_list.AddString(str);
		m_list.SetCheck(0, 1);
		}
	// Make a list without current edited buffer
    CMultiDocTemplate* pDocTemplate =
				((CWedApp*)AfxGetApp())->pDocTemplate;
	POSITION Pos = 	pDocTemplate->GetFirstDocPosition();
	for(;;)
		{
		if(!Pos)
			break;
		CWedDoc* doc = (CWedDoc*)pDocTemplate->GetNextDoc(Pos);
		if(doc)
			{
			ASSERT_VALID(doc);
			if(doc != mydoc)
				{
				CString str = doc->GetPathName();
				m_list.AddString(str);
				}
			}
		}
   	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// void Search::OnCancel2()

void Search::OnCancel2()
{
	int lim = m_list.GetCount();
	for(int loop3 = 0; loop3 < lim; loop3++)
		{
		m_list.SetCheck(loop3, TRUE);
		}
}

/////////////////////////////////////////////////////////////////////////////
// void Search::OnShowWindow(BOOL bShow, UINT nStatus)

void Search::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CWnd *dd = GetDlgItem(IDC_RADIO4);

	m_stype = S_UCASE;
	dd->SendMessage(BM_SETCHECK , 1, 0);

	m_com1.AddString(m_combo1);

	for(int loop = 0; loop < combofill.GetCount(); loop++)
		{
		CString str = combofill.GetAt(combofill.FindIndex(loop));
		m_com1.AddString(str);
		m_com2.AddString(str);
		}
	m_com1.SetFocus();
	//UpdateData();
	CDialog::OnShowWindow(bShow, nStatus);
}

/////////////////////////////////////////////////////////////////////////////
// void Search::OnCheck1()

void Search::OnCheck1()
{
	UpdateData();
#if 0
	CWnd *cc = GetDlgItem(IDC_COMBO1);
	if(m_check1)
		{
		cc->EnableWindow(FALSE);
		cc->SetWindowText("");
		}
	else
		{
		cc->EnableWindow(TRUE);
		cc->SendMessage(CB_SETCURSEL, 0, 0);
		}
#endif
}

/////////////////////////////////////////////////////////////////////////////
// Search types

void Search::OnRadio2()
{
	m_stype = S_FUNCTION;
}

void Search::OnRadio4()
{
	m_stype = S_UCASE;
}

void Search::OnRadio1()
{
	m_stype = S_REGEX;
}

/////////////////////////////////////////////////////////////////////////////
// void	Search::OnCancel3()

void	Search::OnCancel3()

{
	CString str3;
	UpdateData();

	AfxGetApp()->DoWaitCursor(TRUE);
	int lim = m_list.GetCount();

	for(int loop2 = 0; loop2 < lim; loop2++)
		m_list.SetCheck(loop2, FALSE);

	for(int loop3 = 0; loop3 < lim; loop3++)
		{
		m_list.GetText(loop3, str3);
		//P2N("Automate %s\r\n", str3);
		if(IsCandidate(str3))
			m_list.SetCheck(loop3, TRUE);
		}
	UpdateData();
	AfxGetApp()->DoWaitCursor(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// IsCandidate

int		Search::IsCandidate(const char *str)

{
	static int is_can = 0;

	if(is_can)
		return (0);
	is_can = TRUE;

	int found = 0;
	CString str2 = str, filename;
	int idx;

	if((idx = str2.ReverseFind('\\')) != -1)
		{
		filename = str2.Right(str2.GetLength() - (idx+1));
		}
	CWedDoc*  doc = GetDocFromPath(str);
	ASSERT_VALID(doc);

	CWedView* vv = (CWedView*)GetViewFromDoc(doc);
	ASSERT_VALID(vv);

	vv->init_search = TRUE;
	vv->Busy(TRUE);

	// Iterate whole doc
   	int lim  =  doc->strlist.GetCount();
    for(int loop = 0; loop < lim; loop++)
		{
		// Add lines matching criteria:
		int ccol = 0, backwalk = 0;
		found = vv->SearchType(loop, &ccol, &backwalk);

		if(found)
			{
			found = TRUE;
			break;
			}
		if(!(loop % 100))
		    {
			CString num;
	        num.Format("Searching for auto in %s at %d",
									filename, loop);
		    message(num);

			if(YieldToWinEx())
				{
				AfxMessageBox("Aborted auto, partial auto valid");
				break;
				}
			}
		}
	vv->Busy(FALSE);
	is_can = FALSE;
	return(found);
}


void Search::OnCancel4()
{
 	int lim = m_list.GetCount();
	for(int loop3 = 0; loop3 < lim; loop3++)
		{
		m_list.SetCheck(loop3, FALSE);
		}

}

