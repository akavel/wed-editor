// toolbard.cpp : implementation file
//

#include "stdafx.h"
#include "Dummy.h"
#include "toolbard.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolBarDlg dialog


CToolBarDlg::CToolBarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CToolBarDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CToolBarDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_ComboBox.m_hWndToolBar = m_ToolBarCtrl.m_hWnd;
}


void CToolBarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolBarDlg)
	DDX_Control(pDX, IDC_ZOOM, m_Zoom);
	DDX_Control(pDX, IDC_SELECT, m_Select);
	DDX_Control(pDX, IDC_RECT, m_Rect);
	DDX_Control(pDX, IDC_PEN, m_Pen);
	DDX_Control(pDX, IDC_OVAL, m_Oval);
	DDX_Control(pDX, IDC_LINE, m_Line);
	DDX_Control(pDX, IDC_FRAME, m_Frame);
	DDX_Control(pDX, IDC_FILL, m_Fill);
	DDX_Control(pDX, IDC_EYEDROP, m_Eyedrop);
	DDX_Control(pDX, IDC_ERASE, m_Erase);
	DDX_Control(pDX, IDC_BRUSH, m_Brush);
	DDX_Control(pDX, IDC_AIRBRUSH, m_AirBrush);
	DDX_Control(pDX, IDC_CHECK1, m_CheckButton);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CToolBarDlg, CDialog)
	//{{AFX_MSG_MAP(CToolBarDlg)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	//}}AFX_MSG_MAP

//	We add our own handlers for toolbar buttons also.
//	This is used where a button does not have a dialog control 
//	(or menu item) to handle the button's actions.

	ON_BN_CLICKED(IDC_LAST_BUTTON, OnLastButton)
	ON_BN_CLICKED(IDC_OTHER_BUTTON, OnOtherButton)

//	Handlers for the 'optional' buttons:

	ON_BN_CLICKED(IDC_ERASE,    OnIDC_ERASE   )
	ON_BN_CLICKED(IDC_PEN,      OnIDC_PEN     )
	ON_BN_CLICKED(IDC_SELECT,   OnIDC_SELECT  )
	ON_BN_CLICKED(IDC_BRUSH,    OnIDC_BRUSH   )
	ON_BN_CLICKED(IDC_AIRBRUSH, OnIDC_AIRBRUSH)
	ON_BN_CLICKED(IDC_FILL,     OnIDC_FILL    )
	ON_BN_CLICKED(IDC_LINE,     OnIDC_LINE    )
	ON_BN_CLICKED(IDC_EYEDROP,  OnIDC_EYEDROP )
	ON_BN_CLICKED(IDC_ZOOM,     OnIDC_ZOOM    )
	ON_BN_CLICKED(IDC_RECT,     OnIDC_RECT    )
	ON_BN_CLICKED(IDC_FRAME,    OnIDC_FRAME   )
	ON_BN_CLICKED(IDC_OVAL,     OnIDC_OVAL    )

END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CToolBarDlg message handlers

// Default (addable) buttons:

TBBUTTON tbButtonNew[] =
{
    { 8,  IDC_ERASE,       TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0},
    { 9,  IDC_PEN,         TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0},
    {10,  IDC_SELECT,      TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0},
    {11,  IDC_BRUSH,       TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0},
    {12,  IDC_AIRBRUSH,    TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0},
    {13,  IDC_FILL,        TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0},
    {14,  IDC_LINE,        TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0},
    {15,  IDC_EYEDROP,     TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0},
    {16,  IDC_ZOOM,        TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0},
    {17,  IDC_RECT,        TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0},
    {18,  IDC_FRAME,       TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0},
    {19,  IDC_OVAL,        TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0},

};


BOOL CToolBarDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

//	We create our toolbar (this is in a standard dialog box)
//	with the CToolBarCtrl.Create() function. This function takes 
//	a RECT structure as a parameter, but the RECT structure is ignored
//	and not used.

	int ButtonBitmap = 0;
	int ButtonString = 0;
	int ButtonCount = 0;

	RECT	rect;
	rect.top = 0;
	rect.left = 0;
	rect.bottom = 60;
	rect.right = 100;
	
	m_ToolBarCtrl.Create(
		WS_CHILD | WS_VISIBLE | CCS_TOP | TBSTYLE_TOOLTIPS | CCS_ADJUSTABLE, 
		rect, this, 0);

	ButtonBitmap = m_ToolBarCtrl.AddBitmap(20, IDB_TOOLBAR);
	ButtonString = m_ToolBarCtrl.AddString(IDS_FIRST_BUTTON);

	m_Buttons[ButtonCount].iBitmap = NULL;
	m_Buttons[ButtonCount].idCommand = 0;
	m_Buttons[ButtonCount].fsState = TBSTATE_ENABLED;
	m_Buttons[ButtonCount].fsStyle = TBSTYLE_SEP;
	m_Buttons[ButtonCount].dwData = 0;
	m_Buttons[ButtonCount].iString = NULL;
	
	++ButtonCount;

//	Move everything over to leave room for the combobox
//	which will be on the far left of the toolbar.
//	The combobox could be anywhere, but putting it on the 
//	left is easier for the programmer. Most applications with 
//	stock implementations of CToolBarCtrl do it this way.

	m_Buttons[ButtonCount] = m_Buttons[ButtonCount - 1]; 
	++ButtonCount;
	m_Buttons[ButtonCount] = m_Buttons[ButtonCount - 1]; 
	++ButtonCount;
	m_Buttons[ButtonCount] = m_Buttons[ButtonCount - 1]; 
	++ButtonCount;
	m_Buttons[ButtonCount] = m_Buttons[ButtonCount - 1]; 
	++ButtonCount;
	m_Buttons[ButtonCount] = m_Buttons[ButtonCount - 1]; 
	++ButtonCount;
	m_Buttons[ButtonCount] = m_Buttons[ButtonCount - 1]; 
	++ButtonCount;
	m_Buttons[ButtonCount] = m_Buttons[ButtonCount - 1]; 
	++ButtonCount;
	m_Buttons[ButtonCount] = m_Buttons[ButtonCount - 1]; 
	++ButtonCount;
	m_Buttons[ButtonCount] = m_Buttons[ButtonCount - 1]; 
	++ButtonCount;
	m_Buttons[ButtonCount] = m_Buttons[ButtonCount - 1]; 
	++ButtonCount;
	m_Buttons[ButtonCount] = m_Buttons[ButtonCount - 1]; 
	++ButtonCount;
	m_Buttons[ButtonCount] = m_Buttons[ButtonCount - 1]; 
	++ButtonCount;

	m_Buttons[ButtonCount].iBitmap = ButtonBitmap + 0;
	m_Buttons[ButtonCount].idCommand = IDOK;
	m_Buttons[ButtonCount].fsState = TBSTATE_ENABLED;
	m_Buttons[ButtonCount].fsStyle = TBSTYLE_BUTTON;
	m_Buttons[ButtonCount].dwData = 0;
	m_Buttons[ButtonCount].iString = ButtonString;

	++ButtonCount;
	
	m_Buttons[ButtonCount].iBitmap = NULL;
	m_Buttons[ButtonCount].idCommand = 0;
	m_Buttons[ButtonCount].fsState = TBSTATE_ENABLED;
	m_Buttons[ButtonCount].fsStyle = TBSTYLE_SEP;
	m_Buttons[ButtonCount].dwData = 0;
	m_Buttons[ButtonCount].iString = NULL;
	
	++ButtonCount;

	m_Buttons[ButtonCount].iBitmap = ButtonBitmap + 1;
	m_Buttons[ButtonCount].idCommand = IDCANCEL;
	m_Buttons[ButtonCount].fsState = TBSTATE_ENABLED;
	m_Buttons[ButtonCount].fsStyle = TBSTYLE_BUTTON;
	m_Buttons[ButtonCount].dwData = 0;
	m_Buttons[ButtonCount].iString = NULL;

	++ButtonCount;

	m_Buttons[ButtonCount].iBitmap = ButtonBitmap + 2;
	m_Buttons[ButtonCount].idCommand = IDC_CHECK1;
	m_Buttons[ButtonCount].fsState = TBSTATE_ENABLED;
	m_Buttons[ButtonCount].fsStyle = TBSTYLE_CHECK;
	m_Buttons[ButtonCount].dwData = 0;
	m_Buttons[ButtonCount].iString = NULL;

	++ButtonCount;
	
	m_Buttons[ButtonCount].iBitmap = ButtonBitmap + 3;
	m_Buttons[ButtonCount].idCommand = IDC_OTHER_BUTTON;
	m_Buttons[ButtonCount].fsState = TBSTATE_ENABLED;
	m_Buttons[ButtonCount].fsStyle = TBSTYLE_BUTTON;
	m_Buttons[ButtonCount].dwData = 0;
	m_Buttons[ButtonCount].iString = NULL;

	++ButtonCount;
	
	m_Buttons[ButtonCount].iBitmap = ButtonBitmap + 4;
	m_Buttons[ButtonCount].idCommand = 0;
	m_Buttons[ButtonCount].fsState = TBSTATE_ENABLED;
	m_Buttons[ButtonCount].fsStyle = TBSTYLE_SEP;
	m_Buttons[ButtonCount].dwData = 0;
	m_Buttons[ButtonCount].iString = NULL;
	
	++ButtonCount;

	m_Buttons[ButtonCount].iBitmap = ButtonBitmap + 5;
	m_Buttons[ButtonCount].idCommand = IDC_LAST_BUTTON;
	m_Buttons[ButtonCount].fsState = TBSTATE_ENABLED;
	m_Buttons[ButtonCount].fsStyle = TBSTYLE_BUTTON;
	m_Buttons[ButtonCount].dwData = 0;
	m_Buttons[ButtonCount].iString = ButtonString;

	++ButtonCount;

//	Once the m_Buttons[] array is filled in, then we add
//	the buttons to the toolbar.

	m_ToolBarCtrl.AddButtons(ButtonCount, m_Buttons);

//	Since our bitmaps are non-standard in size, we resize
//	the toolbar's buttons to fit the bitmaps:

	CSize sizeButtons(55, 65);

	m_ToolBarCtrl.SetButtonSize(sizeButtons);

//	Since our bitmaps are non-standard in size, we tell
//	the toolbar the real size of our images:

	CSize sizeBitmap(48, 45);

	m_ToolBarCtrl.SetBitmapSize(sizeBitmap);

//	Finally, we resize the toolbar for our non-standard
//	button sizes:

	m_ToolBarCtrl.AutoSize();

//	Finally, add our ComboBox to the toolbar. We add it to the 
//	left edge to make things easy. The buttons are spaced over
//      using a bunch of TBSTYLE_SEP buttons.
// 
//	The ComboBox will be created with a standard string height for the 
//	visible portion. The rect.bottom specifies the dropdown part.
//	We set the height of the top part later...

	rect.top = 2; rect.left = 5; rect.bottom = 200; rect.right = 100;

	if (m_ComboBox.Create( WS_CHILD | WS_BORDER | WS_VISIBLE |
		CBS_HASSTRINGS | CBS_DROPDOWN, rect, (CWnd *)&m_ToolBarCtrl, 124) == 0)
	{// Real applications would have to perhaps recover from this error:
                TRACE("Could not create combobox\n");
	}
	else
	{
//		Set the ComboBox's edit area's height to the height of 
//		the button's bitmap size!

		m_ComboBox.SetItemHeight(-1, 45);

//		Add (some dummy) strings to the ComboBox: 

		m_ComboBox.AddString("asdf");
		m_ComboBox.AddString("qwer");
		m_ComboBox.AddString("zxcv");

//		Set the current selection to the (zero based) second item

		m_ComboBox.SetCurSel(1);
	}

	rect.top = 2; rect.left = 5; rect.bottom = 45; rect.right = 100;
	CToolTipCtrl * tt;
	tt = m_ToolBarCtrl.GetToolTips();

	if (tt->AddTool(&m_ComboBox, IDC_COMBO_BOX) == 0)
	{
		TRACE("AddTool() failed!!!!!\n");
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CToolBarDlg::OnCheck1() 
{
//	Our pushbutton on the toolbar is at command index IDC_CHECK1. 

//	Notice how the dialog's check feature now cannot be used directly,
//	that is you must use the toolbar to check/uncheck the control!
//	Real applications would not use this type of control/toolbar connnection
//	however, so this is not an issue.

	if (m_ToolBarCtrl.IsButtonChecked(IDC_CHECK1))
	{// Checked in toolbar
		m_CheckButton.SetCheck(1);
		TRACE("The CheckButton was checked!\n");
	}
	else
	{// Not checked in toolbar
		m_CheckButton.SetCheck(0);
		TRACE("The CheckButton was not checked!\n");
	}

	TRACE("Our Check button has been pressed!\n");
}

void CToolBarDlg::OnLastButton() 
{
//	Toggle the third button on the toolbar!
//	Note: this changes the visual state, but does
//	not call the handler!  Notice that we use a really crude
//	index to determine the check box's state, and this 
//	should not be used in 'real' programs!

//	Calling m_ToolBarCtrl.PressButton(IDC_CHECK1, TRUE);
//  would give the effect of a pressed button without 
//	the 'checked' effect (which displays in a lighter background)


	static int j = 0;

	if (j == 0)
	{
		m_ToolBarCtrl.CheckButton(IDC_CHECK1, TRUE);
		j = 1;
	}
	else
	{
		m_ToolBarCtrl.CheckButton(IDC_CHECK1, FALSE);
		j = 0;
	}

	TRACE("The last button was pressed!\n");
}

void CToolBarDlg::OnOtherButton() 
{
//	Toggle the third button on the toolbar!
//	Note: this changes the visual state, but does
//	not call the handler! Notice that we use a really crude
//	index to determine the check box's state, and this 
//	should not be used in 'real' programs!

//	Calling m_ToolBarCtrl.PressButton(IDC_CHECK1, TRUE);
//  would give the effect of a pressed button without 
//	the 'checked' effect (which displays in a lighter background)


	static int j = 0;

	if (j == 0)
	{
		m_ToolBarCtrl.CheckButton(IDC_CHECK1, TRUE);
		j = 1;
	}
	else
	{
		m_ToolBarCtrl.CheckButton(IDC_CHECK1, FALSE);
		j = 0;
	}

	TRACE("The other button was pressed!\n");
}
//---------------------

void CToolBarDlg::OnIDC_ZOOM() 
{
//	Handles the optional toolbar button, if on the toolbar!


	static int j = 0;

	if (j == 0)
	{
		m_Zoom.SetState(TRUE);
		j = 1;
	}
	else
	{
		m_Zoom.SetState(FALSE);
		j = 0;
	}
}

void CToolBarDlg::OnIDC_SELECT() 
{
//	Handles the optional toolbar button, if on the toolbar!


	static int j = 0;

	if (j == 0)
	{
		m_Select.SetState(TRUE);
		j = 1;
	}
	else
	{
		m_Select.SetState(FALSE);
		j = 0;
	}
}

void CToolBarDlg::OnIDC_RECT() 
{
//	Handles the optional toolbar button, if on the toolbar!


	static int j = 0;

	if (j == 0)
	{
		m_Rect.SetState(TRUE);
		j = 1;
	}
	else
	{
		m_Rect.SetState(FALSE);
		j = 0;
	}
}

void CToolBarDlg::OnIDC_PEN() 
{
//	Handles the optional toolbar button, if on the toolbar!


	static int j = 0;

	if (j == 0)
	{
		m_Pen.SetState(TRUE);
		j = 1;
	}
	else
	{
		m_Pen.SetState(FALSE);
		j = 0;
	}
}

void CToolBarDlg::OnIDC_OVAL() 
{
//	Handles the optional toolbar button, if on the toolbar!


	static int j = 0;

	if (j == 0)
	{
		m_Oval.SetState(TRUE);
		j = 1;
	}
	else
	{
		m_Oval.SetState(FALSE);
		j = 0;
	}
}

void CToolBarDlg::OnIDC_LINE() 
{
//	Handles the optional toolbar button, if on the toolbar!


	static int j = 0;

	if (j == 0)
	{
		m_Line.SetState(TRUE);
		j = 1;
	}
	else
	{
		m_Line.SetState(FALSE);
		j = 0;
	}
}

void CToolBarDlg::OnIDC_FRAME() 
{
//	Handles the optional toolbar button, if on the toolbar!


	static int j = 0;

	if (j == 0)
	{
		m_Frame.SetState(TRUE);
		j = 1;
	}
	else
	{
		m_Frame.SetState(FALSE);
		j = 0;
	}
}

void CToolBarDlg::OnIDC_FILL() 
{
//	Handles the optional toolbar button, if on the toolbar!


	static int j = 0;

	if (j == 0)
	{
		m_Fill.SetState(TRUE);
		j = 1;
	}
	else
	{
		m_Fill.SetState(FALSE);
		j = 0;
	}
}

void CToolBarDlg::OnIDC_EYEDROP() 
{
//	Handles the optional toolbar button, if on the toolbar!


	static int j = 0;

	if (j == 0)
	{
		m_Eyedrop.SetState(TRUE);
		j = 1;
	}
	else
	{
		m_Eyedrop.SetState(FALSE);
		j = 0;
	}
}

void CToolBarDlg::OnIDC_ERASE() 
{
//	Handles the optional toolbar button, if on the toolbar!

	static int j = 0;

	if (j == 0)
	{
		m_Erase.SetState(TRUE);
		j = 1;
	}
	else
	{
		m_Erase.SetState(FALSE);
		j = 0;
	}
}

void CToolBarDlg::OnIDC_BRUSH() 
{
//	Handles the optional toolbar button, if on the toolbar!


	static int j = 0;

	if (j == 0)
	{
		m_Brush.SetState(TRUE);
		j = 1;
	}
	else
	{
		m_Brush.SetState(FALSE);
		j = 0;
	}
}

void CToolBarDlg::OnIDC_AIRBRUSH() 
{
//	Handles the optional toolbar button, if on the toolbar!


	static int j = 0;

	if (j == 0)
	{
		m_AirBrush.SetState(TRUE);
		j = 1;
	}
	else
	{
		m_AirBrush.SetState(FALSE);
		j = 0;
	}
}


//---------------------
BOOL CToolBarDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
//	Our own OnNotify (ClassWizard does not create OnNotify, bummer)...
//	TRACE("OnNotify() called \n");

	TOOLTIPTEXT	* tt;
	NMHDR	* 	hdr;
	tt = (TOOLTIPTEXT *)lParam;
	hdr = (NMHDR *)lParam;
	LPTBNOTIFY	lpTbNotify = (LPTBNOTIFY)lParam;

	CString		Tip;
	CString		String;

	switch(tt->hdr.code)
	{
		case TTN_NEEDTEXT:
//			TRACE("TTN_NEEDTEXT \n");
			Tip.LoadString(tt->hdr.idFrom);
			strcpy(tt->szText, (LPCSTR)Tip);
			break;

		case TBN_QUERYINSERT:
//			TRACE("TBN_QUERYINSERT \n");

			if (pResult != NULL)
				*pResult = TRUE;

			return(TRUE);
			break;

		case TBN_QUERYDELETE:
//			TRACE("TBN_QUERYDELETE \n");			

			if (pResult != NULL)
				*pResult = TRUE;

			return(TRUE);
			break;

		case TBN_GETBUTTONINFO:
//			TRACE("TBN_GETBUTTONINFO \n");

			if (lpTbNotify->iItem < 12)
			{
//  The below TRACE()'s allow you to peek at the passed structures!

//				TRACE("lpTbNotify = %p \n", lpTbNotify);

//				TRACE("lpTbNotify->hdr.hwndFrom = %d \n", 
//					lpTbNotify->hdr.hwndFrom);
//				TRACE("lpTbNotify->hdr.idFrom = %p \n", 
//					lpTbNotify->hdr.idFrom);
//				TRACE("lpTbNotify->hdr.code = %p \n", 
//					lpTbNotify->hdr.code);

//				TRACE("lpTbNotify->iItem = %d \n", lpTbNotify->iItem);

//				TRACE("lpTbNotify->tbButton.iBitmap = %d \n", 
//					lpTbNotify->tbButton.iBitmap);
//				TRACE("lpTbNotify->tbButton.idCommand = %d \n", 
//					lpTbNotify->tbButton.idCommand);				
//				TRACE("lpTbNotify->cchText = %d \n", 
//					lpTbNotify->cchText);
//				TRACE("lpTbNotify->tbButton.fsState = %d \n", 
//					lpTbNotify->tbButton.fsState);
//				TRACE("lpTbNotify->tbButton.fsStyle = %d \n", 
//					lpTbNotify->tbButton.fsStyle);
//				TRACE("lpTbNotify->tbButton.dwData = %d \n", 
//					lpTbNotify->tbButton.dwData);
//				TRACE("lpTbNotify->tbButton.iString = %d \n", 
//					lpTbNotify->tbButton.iString);

//				TRACE("lpTbNotify->pszText = %p \n", 
//					lpTbNotify->pszText);

				lpTbNotify->tbButton = tbButtonNew[lpTbNotify->iItem];

				if (lpTbNotify->pszText != NULL)
				{// Only return the string, if there is a buffer!
                                        String.LoadString(
                                            tbButtonNew[lpTbNotify->iItem].idCommand);

					strcpy(lpTbNotify->pszText, (LPCSTR)String);
					lpTbNotify->cchText = strlen(lpTbNotify->pszText);
				}

				if (pResult != NULL)
					*pResult = TRUE;

				return(TRUE);
			}
			else
			{//	Not a valid button for the toolbar!
//				TRACE("Was not a valid selection!\n");
			}

			break;

		case TBN_BEGINDRAG:
//			Called when the user starts a drag (without using
//			the shift key). Your code must handle this
//			case.

//			TRACE("TBN_BEGINDRAG: \n");
			break;
		case TBN_ENDDRAG:
//			Called when the user ends a drag (without using
//			the shift key). Your code must handle this
//			case.

//			TRACE("TBN_ENDDRAG: \n");
			break;
		case TBN_BEGINADJUST:
//			TRACE("TBN_BEGINADJUST: \n");
			break;
		case TBN_ENDADJUST:
//			TRACE("TBN_ENDADJUST: \n");
			break;
		case TBN_RESET:
//			TRACE("TBN_RESET: \n");
			break;
		case TBN_TOOLBARCHANGE:
//			TRACE("TBN_TOOLBARCHANGE: \n");
			break;
		case TBN_CUSTHELP:
//			TRACE("TBN_CUSTHELP: \n");
			break;

		default: // Should never happen.
//			TRACE("DEFAULT: \n");
			break;
	}

	return CDialog::OnNotify(wParam, lParam, pResult);
}

CComboBoxTip::CComboBoxTip()
{// Constructor does nothing at all!

}
