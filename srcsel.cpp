/////////////////////////////////////////////////////////////////////////////
// Search selection dialog
//

#include "stdafx.h"
#include "wed.h"
#include "srcsel.h"
#include "strlist.h"
#include "Weddoc.h"
#include "WedView.h"
#include "editor.h"
#include "undo.h"
#include "misc.h"
#include "notepad.h"
#include "stringex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

TBBUTTON tbButtonNew[8];

void DoSrcSelChange(srcsel *s1, CWedView *conn);

/////////////////////////////////////////////////////////////////////////////
// srcsel dialog

srcsel::srcsel(CWnd* pParent /*=NULL*/)
    : CDialog(srcsel::IDD, pParent)
{
    //{{AFX_DATA_INIT(srcsel)
    m_list = _T("");
    m_src = _T("");
    //}}AFX_DATA_INIT

    m_busy = FALSE;
	m_rep = 0;
    m_shown = 0;
    m_err = FALSE;
}

srcsel::~srcsel()

{
	m_ToolBarCtrl.DestroyWindow();
}


/////////////////////////////////////////////////////////////////////////////
// void srcsel::DoDataExchange(CDataExchange* pDX)

void srcsel::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(srcsel)
    DDX_LBString(pDX, IDC_LIST1, m_list);
    DDX_Text(pDX, IDC_EDIT1, m_src);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(srcsel, CDialog)
    //{{AFX_MSG_MAP(srcsel)
    ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
    ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList1)
    ON_WM_SIZE()
    ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
    ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
    ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_WM_CHAR()
	ON_BN_CLICKED(IDC_BUTTON10, OnButton10)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
	ON_WM_CHARTOITEM()
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

#include "mainfrm.h"

extern CMainFrame* pMainFrame;

// Remember old position of dialog, offset by caption
static oldx = 0, oldy = 0;

/////////////////////////////////////////////////////////////////////////////
// void srcsel::OnDblclkList1()

void srcsel::OnDblclkList1()

{
	m_shown = 0;
	if(	m_rep)
		OnButton4();
	else
		OnOK();
}

/////////////////////////////////////////////////////////////////////////////
// void srcsel::OnSelchangeList1()

void srcsel::OnSelchangeList1()

{
    GotoSel();
}

/////////////////////////////////////////////////////////////////////////////
// void srcsel::GotoSel()

void srcsel::GotoSel()

{
	CString str;
    int  line, col, sel;

	sel = slb.GetCurSel();

	// Is selected?
	if(sel < 0)
		return;

	// Is in range?
	if(sel >= linea.GetSize())
		return;

	line = linea.GetAt(sel);

	// Get original line
	CWedView *textwin = (CWedView *)connect;
    ASSERT_VALID(textwin);

    CWedDoc*  pDoc = textwin->GetDocument();
	ASSERT_VALID(pDoc);

	// Position to tab correct place
	str	 = pDoc->strlist.GetLine(line);
	col  = cola.GetAt(sel);
	col  = str2scr(str, col);

	// Put to foreground
	pMainFrame->MDIActivate (textwin->GetParent());

	// Set in edit window
    textwin->col = col;
    textwin->row = line;

	textwin->CreateCaret(&caret);
	textwin->ShowCaret();
    textwin->SyncCaret(3);
    //message("Moved to line");
}

/////////////////////////////////////////////////////////////////////////////
// Make list follow dialog size

void srcsel::OnSize(UINT nType, int cx, int cy)
{
    CWnd  *list =  GetDlgItem(IDC_LIST1);
    RECT crect;
    GetClientRect(&crect);

    RECT rect;
    m_ToolBarCtrl.GetClientRect(&rect);
    int wide = rect.right - rect.left;
    int high = rect.bottom - rect.top;

	// Make list follow size
    list->SetWindowPos(NULL, 0, 0, cx ,
           cy - high,  SWP_NOOWNERZORDER | SWP_NOMOVE );

    CDialog::OnSize(nType, cx, cy);
}

/////////////////////////////////////////////////////////////////////////////
// BOOL srcsel::OnInitDialog()

BOOL srcsel::OnInitDialog()
{
	CWnd *dt = AfxGetMainWnd();
	RECT dtr;
	int dtw, dth;

	if(dt)
		{
		dt->GetClientRect(&dtr);
		dtw = dtr.right - dtr.left;
		dth = dtr.bottom - dtr.top;
		//PrintToNotepad("MainWindow %dx%d\r\n", dtw, dth);
		}

	// Subclassed from checklistbox
	slb.SubclassDlgItem(IDC_LIST1, this);

	// Create and init Toolbar
    RECT    rect;
    GetClientRect(&rect);

	if(!m_ToolBarCtrl.Create(
        WS_CHILD | WS_VISIBLE | CCS_TOP | TBSTYLE_TOOLTIPS | CCS_ADJUSTABLE,
			rect , this, int(this)))
		{
		m_err = TRUE;
		return TRUE;
		}

    for(int loop = 0; loop < 8; loop++)
		{
		tbButtonNew[loop].iBitmap = loop;
		tbButtonNew[loop].idCommand = IDOK;
		tbButtonNew[loop].fsState = TBSTATE_ENABLED;
		tbButtonNew[loop].fsStyle = TBSTYLE_BUTTON;
		tbButtonNew[loop].dwData  = 0;
		tbButtonNew[loop].iString = loop;
		}
    tbButtonNew[0].idCommand = IDC_BUTTON1;
    tbButtonNew[1].idCommand = IDC_BUTTON2;
    tbButtonNew[2].idCommand = IDC_BUTTON3;
    tbButtonNew[3].idCommand = IDC_BUTTON4;
    tbButtonNew[4].idCommand = IDC_BUTTON9;
    tbButtonNew[5].idCommand = IDC_BUTTON10;
    tbButtonNew[6].idCommand = IDC_BUTTON5;
    tbButtonNew[7].idCommand = IDOK;

    m_ToolBarCtrl.AddButtons(8, tbButtonNew);
    m_ToolBarCtrl.AddBitmap(8, IDR_TOOLBAR1);

    //PrintToNotepad("Init Dialog\r\n");
    m_ToolBarCtrl.GetWindowRect(&rect);
    CWnd  *list =   GetDlgItem(IDC_LIST1);
    ASSERT(list);

    list->SetWindowPos( NULL, 0, rect.bottom-rect.top,
            0, 0, SWP_NOOWNERZORDER | SWP_NOSIZE );

	if(!oldx && !oldy)
		{
		oldx = rect.left;  oldy = rect.top;
		}
    oldx += 20; oldy += 20;

	POINT pp; 	 pp.x = oldx;  pp.y = oldy;
	//ClientToScreen(&pp);

	if(	oldx + (rect.right-rect.left) > dtw ||
		oldy + (rect.bottom-rect.top) > dth )
		{
		oldx = 0; oldy = 20;
		}

	 SetWindowPos( NULL, pp.x, pp.y, 0, 0,
                SWP_NOOWNERZORDER | SWP_NOSIZE );

   	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// Select all checkmarks:

void srcsel::OnButton1()
{
    int lim = slb.GetCount();
    for(int loop = 0; loop < lim; loop++)
		{
        slb.SetCheck(loop, 1);
		}
}

/////////////////////////////////////////////////////////////////////////////
// Deselect all checkmarks:

void srcsel::OnButton2()
{
    int lim = slb.GetCount();
    for(int loop = 0; loop < lim; loop++)
		{
        slb.SetCheck(loop, 0);
		}
}

/////////////////////////////////////////////////////////////////////////////
// Exec change on all selected

void srcsel::OnButton3()

{
	if(!m_rep)
		{
		AfxMessageBox("Not in replace mode"); return;
		}
	CWedView *textwin = (CWedView *)connect; 
	ASSERT_VALID(textwin);
    CWedDoc*    pDoc = textwin->GetDocument();
	ASSERT_VALID(pDoc);

	int made = 0;
	int lim  = pDoc->ssel.slb.GetCount();

	// Init undo
    SaveUndo(textwin, UNDO_NOP, textwin->row, textwin->col, "");

	for(int loop = 0; loop < lim; loop++)
		{
		if(pDoc->ssel.slb.GetCheck(loop))
			{
			pDoc->ssel.DoChange(loop, 1); made++;
			}
		}
	CString num; num.Format("%d lines changed", made);
	message(num);

	// Communicate changes
	if(made)
		{
		pDoc->SetModifiedFlag(TRUE);
		}

    pDoc->UpdateAllViews(NULL);

	// Close (hide) search window
	pDoc->ssel.ShowWindow(SW_HIDE);
}

/////////////////////////////////////////////////////////////////////////////
// Exec one line change

void srcsel::OnButton4()

{
	if(!m_rep)
		{
		AfxMessageBox("Not in replace mode");
		return;
		}
	CWedView *textwin = (CWedView *)connect;
    ASSERT_VALID(textwin);
    CWedDoc*    pDoc = textwin->GetDocument();
	ASSERT_VALID(pDoc);

	int lbl = slb.GetCurSel();
	if(slb.GetCheck(lbl))
		{
		DoChange(lbl, 0);
		pDoc->SetModifiedFlag(1);
		}
    pDoc->UpdateAllViews(NULL);
}

/////////////////////////////////////////////////////////////////////////////
// BOOL srcsel::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)

BOOL srcsel::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
    TOOLTIPTEXT * tt;
    tt = (TOOLTIPTEXT *)lParam;

    switch(tt->hdr.code)
		{
        case TTN_NEEDTEXT:
		switch(tt->hdr.idFrom)
			{
			case IDC_BUTTON1: strcpy(tt->szText, "Select All   Alt+A ");
				break;

			case IDC_BUTTON2: strcpy(tt->szText, "Select None   Alt+N ");
				break;

			case IDC_BUTTON3: strcpy(tt->szText, "Change All Alt+C ");
				break;

			case IDC_BUTTON4: strcpy(tt->szText, "Change One Alt+O ");
				break;

			case IDC_BUTTON9: strcpy(tt->szText,
								"Change in All Files (Global) Alt+G ");
				break;

			case IDC_BUTTON10: strcpy(tt->szText, "Undo Alt+U");
				break;

			case IDC_BUTTON5:  strcpy(tt->szText, "Copy to holding Buffer Alt+B");
				break;

			case IDOK:  strcpy(tt->szText, "Close Alt+E");
				break;

			default:
	            break;
			}
		break;
        }
    return CDialog::OnNotify(wParam, lParam, pResult);
}

/////////////////////////////////////////////////////////////////////////////
// Change one line in file

void srcsel::DoChange(int lbl, int undogroup)

{

	CWedView *v1 = (CWedView*)connect; 	ASSERT_VALID(v1);
    CWedDoc*  pDoc = v1->GetDocument(); ASSERT_VALID(pDoc);

	//PrintToNotepad("Exec doChange in document %d\r\n", pDoc);

	int	line = pDoc->ssel.linea.GetAt(lbl);
	CStringEx str2 = pDoc->strlist.GetLine(line);

	// Undo is saved here
	int undoop;
	if(undogroup)
		undoop = UNDO_MOD | UNDO_BLOCK;
	else
		undoop = UNDO_MOD;

	SaveUndo(v1, undoop, line, v1->col, str2);

	// Work it, simple non case sensitive change
	str2.FindReplaceNoCase(srcdlg.m_combo1, srcdlg.m_combo2);
	pDoc->strlist.SetLine(line, str2);

	// Duplicate changes avoided this way
	pDoc->ssel.slb.SetCheck(lbl, 0);

}

/////////////////////////////////////////////////////////////////////////////
// void srcsel::OnOK()

void srcsel::OnOK()

{
	int lim = srcdlg.m_files.GetCount();
	CWedDoc*  doc;

	for(int loop3 = 0; loop3 < lim; loop3++)
		{
		CString str3;
		POSITION pos = srcdlg.m_files.FindIndex(loop3);
		if(pos)
			{
			str3 = srcdlg.m_files.GetAt(pos);
			doc = GetDocFromPath(str3);
			ASSERT_VALID(doc);
			doc->ssel.GotoSel();

			// Clean out big memory consumers
			doc->ssel.linea.RemoveAll();
			doc->ssel.slb.ResetContent();

			// Just hide it instead of closing
			doc->ssel.ShowWindow(SW_HIDE);
			}
		}
	m_shown = 0;

    CWedView *textwin = (CWedView *)connect;
	ASSERT_VALID(textwin);
	textwin->SetFocus();

	// Closed one, reset position offset
    oldx = 0; oldy = 0;
	//CDialog::OnOK();
}

/////////////////////////////////////////////////////////////////////////////
// Undo

void srcsel::OnButton10()

{
	if(!m_rep)
		{
		AfxMessageBox("Not in replace mode"); return;
		}
    CWedView *textwin = (CWedView *)connect;
    ASSERT_VALID(textwin);
    UnDo(textwin);
	GotoSel();
}

/////////////////////////////////////////////////////////////////////////////
// Iterate every open document, change
//

void srcsel::OnButton9()
{
	if(!m_rep)
		{
		AfxMessageBox("Not in replace mode"); return;
		}
	int lim = srcdlg.m_files.GetCount();
	for(int loop3 = 0; loop3 < lim; loop3++)
		{
		CString str3;
		POSITION pos = srcdlg.m_files.FindIndex(loop3);
		if(pos)
			{
			str3 = srcdlg.m_files.GetAt(pos);
			//PrintToNotepad("Global search: %s\r\n", str3);

			CWedDoc*  doc = GetDocFromPath(str3);
			ASSERT_VALID(doc);

			if(!doc)
				continue;

			doc->ssel.SetFocus(); 
			doc->ssel.GotoSel();
			YieldToWin(); Sleep(200);
			doc->ssel.OnButton3();
			}
		}

	// Activate current (latest) view
    CWedView *textwin = (CWedView *)connect;
	ASSERT_VALID(textwin);
	textwin->SetFocus();

	CString num; num.Format( "Processed %d files", lim);
    message(num);
}

/////////////////////////////////////////////////////////////////////////////
// void srcsel::OnShowWindow(BOOL bShow, UINT nStatus)

void srcsel::OnShowWindow(BOOL bShow, UINT nStatus)
{
    m_shown = TRUE;

#if 0
	int state;
	// Disable the ones that are not needed
	if(!m_rep)
		state = TBSTATE_INDETERMINATE;
	else
	   	state = TBSTATE_ENABLED;

	m_ToolBarCtrl.SetState(IDC_BUTTON3, state);
	m_ToolBarCtrl.SetState(IDC_BUTTON4, state);
	m_ToolBarCtrl.SetState(IDC_BUTTON9, state);
	m_ToolBarCtrl.SetState(IDC_BUTTON10, state);
#endif

	CDialog::OnShowWindow(bShow, nStatus);

    CWnd  *list =   GetDlgItem(IDC_LIST1);
	ASSERT(list);
    list->SetFocus();
}

void srcsel::OnClose()

{
	m_shown = 0;
	CDialog::OnClose();
}

int srcsel::OnCharToItem(UINT nChar, CListBox* pListBox, UINT nIndex)
{
	//PrintToNotepad("SrcSel char2item: %c %x\r\n", nChar);
	return CDialog::OnCharToItem(nChar, pListBox, nIndex);
}

/////////////////////////////////////////////////////////////////////////////
// Copy to holding

void srcsel::OnButton5()
{
	CString str;
    int lim = slb.GetCount();
	CWedView *textwin = (CWedView *)connect;
    ASSERT_VALID(textwin);
    CWedDoc*    pDoc = textwin->GetDocument();
	ASSERT_VALID(pDoc);

	holding[currhold].RemoveAll();
	holdflag[currhold] = FALSE;

    for(int loop = 0; loop < lim; loop++)
		{
		CString num;
		if(!(loop % 100))
			{
			num.Format( "Copy line %d", loop);
            message(num);
			if(YieldToWinEx())
				{
				AfxMessageBox("Aborted copy to holding");
				goto end2;
				}
			}
		slb.GetText(loop, str);
        holding[currhold].AddTail(str);
		}
end2: ;

	pDoc->SetModifiedFlag(TRUE);
}


#if 0

// 
// Exec change in arbitrary window
//

void DoSrcSelChange(srcsel *s1, CWedView *conn)

{
	CWedView *textwin = (CWedView *)conn;
    ASSERT_VALID(textwin);
    CWedDoc*    pDoc = textwin->GetDocument();
	ASSERT_VALID(pDoc);

	// Init undo
    SaveUndo(textwin, UNDO_NOP, textwin->row, textwin->col, "");

	for(int loop = 0; loop < lim; loop++)
		{
		if(s1->slb.GetCheck(loop))
			{
			DoChange(loop, 1);
			s1->slb.SetCheck(loop, 0);
			made++;
			}
		}
	CString num; num.Format("%d lines changed", made);

	if(made)
		pDoc->SetModifiedFlag(1);

	message(num);
    pDoc->UpdateAllViews(NULL);

	// Close Search window
	pDoc->ssel.ShowWindow(SW_HIDE);
}

#endif