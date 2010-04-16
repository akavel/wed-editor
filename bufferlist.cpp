/////////////////////////////////////////////////////////////////////////////
// BufferList.cpp : implementation file
//

#include "stdafx.h"
#include "wed.h"
#include "BufferList.h"

#include "strlist.h"
#include "weddoc.h"
#include "wedview.h"
#include "mxpad.h"
#include "editor.h"
#include "mainfrm.h"
#include "misc.h"

extern CMainFrame* pMainFrame;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// BufferList dialog

BufferList::BufferList(CWnd* pParent /*=NULL*/)
    : CDialog(BufferList::IDD, pParent)
{
    //{{AFX_DATA_INIT(BufferList)
	//}}AFX_DATA_INIT
}

/////////////////////////////////////////////////////////////////////////////
// void BufferList::DoDataExchange(CDataExchange* pDX)

void BufferList::DoDataExchange(CDataExchange* pDX)

{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(BufferList)
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
    DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(BufferList, CDialog)
    //{{AFX_MSG_MAP(BufferList)
    ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDOK,  OnOK)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// void BufferList::OnShowWindow(BOOL bShow, UINT nStatus)

void BufferList::OnShowWindow(BOOL bShow, UINT nStatus)

{
    CDialog::OnShowWindow(bShow, nStatus);
	
}

/////////////////////////////////////////////////////////////////////////////
// void	BufferList::Fill()

void	BufferList::Fill()

{
 	POSITION	pos2;
    char		mod[12] = "   ";
	CWedView	*cv;

	m_list.ResetContent();

    CWedApp     *app = (CWedApp*)AfxGetApp();
    POSITION	Pos = app->pDocTemplate->GetFirstDocPosition();

    int loop = 0;
    for(;;)
        {
        if(!Pos)
            break;

        CWedDoc* doc = (CWedDoc*)app->pDocTemplate->GetNextDoc(Pos);

		if(!doc)
			continue;

        ASSERT_VALID(doc);
        CString file = doc->GetPathName();

		if(doc->IsModified())
			mod[0] = '*';
		else
			mod[0] = ' ';

		int pos3 = m_list.AddString(mod + file);

		pos2 = doc->GetFirstViewPosition();
		cv = (CWedView*)doc->GetNextView(pos2);

		//P2N("BufferList:: Alt-B view: %d --- %d \r\n", cv, m_cv);

		if(m_cv == (long)cv)
			m_list.SetCurSel(pos3);

		loop++;
       }
	CString num; num.Format("%d buffers", loop);
	m_edit1.SetWindowText(num);
}

/////////////////////////////////////////////////////////////////////////////
// Switch to selection

void BufferList::OnOK()

{
	CString str;
	CWedDoc *pdoc;
	POSITION pos;
	CWedView *cv;

	int sel = m_list.GetCurSel();
	if(sel == -1)	  		// Nothing selected, just close
		{
		message("No document selected");
		goto endd;
		}
	m_list.GetText(sel, str);
	//P2N("Selected: %s\r\n", str);
	pdoc =  GetDocFromPath(str.Right(str.GetLength()-3) );

	if(!pdoc)			// Null doc
		goto endd;

	ASSERT_VALID(pdoc);
	pos = pdoc->GetFirstViewPosition();
	cv = (CWedView*)pdoc->GetNextView(pos);
	if(!cv)
		goto endd;

	ASSERT_VALID(cv);

endd:
	CDialog::OnOK();

	if(sel != -1)
		pMainFrame->MDIActivate (cv->GetParent());
}

/////////////////////////////////////////////////////////////////////////////
// void BufferList::OnButton1()

void BufferList::OnButton1()
{
	int sel = m_list.GetCurSel();
	SaveAllDocs();
	Fill();
	m_list.SetCurSel(sel);
}

/////////////////////////////////////////////////////////////////////////////
// void BufferList::OnButton2()

void BufferList::OnButton2()

{
	CString str;
	CWedDoc *pdoc;

	int sel = m_list.GetCurSel();
	if(sel == -1)	  		// Nothing selected, just close
		{
		message("No document selected");
		goto endd;
		}
	m_list.GetText(sel, str);
	str =  str.Right(str.GetLength()-3);
	pdoc =  GetDocFromPath(str);

	if(!pdoc)			// Null doc
		goto endd;

	if(!pdoc->IsModified())
		{
		message("Document not modified");
/////////////////////////////////////////////////////////////////////////////
		goto endd;
		}
	pdoc->OnSaveDocument(str);
	Fill();
	m_list.SetCurSel(sel);

endd:;
}

/////////////////////////////////////////////////////////////////////////////
// void BufferList::OnButton3()

void BufferList::OnButton3()

{

	CString str;
	CWedDoc *pdoc;
	int ret;

	int sel = m_list.GetCurSel();
	if(sel == -1)	  		// Nothing selected, just close
		{
		message("No document selected");
		goto endd;
		}

	m_list.GetText(sel, str);
	str =  str.Right(str.GetLength()-3);
	pdoc =  GetDocFromPath(str);

	if(!pdoc)			// Null doc
		goto endd;

	ASSERT_VALID(pdoc);

	if(pdoc->IsModified())
		{
		CString num; num.Format("Save  %s  ?", str);
		ret = AfxMessageBox(num,  MB_YESNOCANCEL);
		switch (ret)
			{
			case IDYES : pdoc->OnSaveDocument(str);
			 	break;

			case IDCANCEL: goto endd;
				break;

			case IDNO :
				break;
			}
		}
	pdoc->OnCloseDocument();
	Fill();

	if(sel <= 0)
		m_list.SetCurSel(sel);
	else
		m_list.SetCurSel(sel-1);

endd:;
}

/////////////////////////////////////////////////////////////////////////////
// BOOL BufferList::OnInitDialog()

BOOL BufferList::OnInitDialog()

{
	CDialog::OnInitDialog();
	
	Fill();

	return TRUE;
}

void BufferList::OnDblclkList1()

{
	OnOK();
}
