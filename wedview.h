
/* =====[ wedview.h ]========================================== 
                                                                             
   Description:     The wed project, implementation of the wedview.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  1/6/2009  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

// wedView.h : interface of the CWedView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WEDVIEW_H__87F3F48E_DE8E_11D2_BEED_002078105E2C__INCLUDED_)
#define AFX_WEDVIEW_H__87F3F48E_DE8E_11D2_BEED_002078105E2C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define WED_MAGIC 0x2345789

class CWedView : public CView
{
protected: //  create from serialization only
    CWedView();
    DECLARE_DYNCREATE(CWedView)

	void CWedView::MoveFunction(int up = false) ;

	CFont m_LogoFont;
	CString sLogoString;

// Attributes
public:

	int			magic;

    CWedView    *other;
	CRect		oldrect;
	CWnd		*parent;

	int 		AllowShighlite;
    int     	progress;
    int     	row, col;
    int     	srow, scol;
    int     	soh, eoh;
    int     	soch, eoch;
    int     	diffchange;
    int     	diff;
    int     	highlite;
    int     	record;
    int     	drag;
    int     	mouse;
    int     	scrollock;
    int     	scrolldiv;
	int			hex;
	int			m_busy;
	int			focus;
	int 		shift;
	int 		control;
	int 		alt;
	int 		hitmode;

	int			init_search;

    CString 	modestr;
    CString 	origtitle;
    CWordArray 	pages;
    CWordArray 	diffa;
    CStringList draglist;

// Implementation
public:
	void 		Busy(int on);
    int			SyncCaret(int bound = 0);
    CWedDoc*	GetDocument();
    CMenu		*GetDiffMenu();
	void		SetColor(COLORREF * col);
    void    	start_record();
	void  		PlayMacro(int animate);
	void  		start_play(int animate);
    void    	SwitchholdingBuffer(int buffnum);
    void    	InsertClip();
	void		ShowBuffers();
	void		Caseselection(int updown = FALSE);
	void		InsertDate(char *format) ;
	void		SearchFile(int replace = FALSE);
	void		DoSearch(CWedDoc*  pDoc, int replace);
	void		SwitchToNext();
	void		OnDiffToX(int num);
	void		UnFullscreen();
	void		ReFullscreen();
	void		Esc();
	void		Del();
	void		BackSpace();
	void		DelLine();
	void		KillToTol();
	void		DoTemplate(const char *file);
	void		HitCusror(int direction);
	void		CancelHit();
	void		SwitchRec(int newrec);
	int			SearchType(int loop, int *ccol, int *back);
	void		Maximizecurrent();
	void		MoveNextword();
	void		Spellcheck(int strings);
	void 		Cleanoldfiles(const char *dir);

    virtual 	~CWedView();

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CWedView)
	public:
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
    virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
    virtual void OnInitialUpdate();
	//virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
    virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL


#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
    //{{AFX_MSG(CWedView)
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg void OnViewViewhex();
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnViewFonts();
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnViewForegroundcolor();
    afx_msg void OnViewBackgroundcolor();
    afx_msg void OnViewHighlitebackground();
    afx_msg void OnViewColomnhighlitebackground();
    afx_msg void OnViewSelectprinterfont();
    afx_msg void OnEditCopy();
    afx_msg void OnEditPaste();
    afx_msg void OnViewViewholdingheads();
    afx_msg void OnWindowMaximizemain();
    afx_msg void OnEditUndo();
    afx_msg void OnEditRedo();
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnOperationsSelectline();
    afx_msg void OnSearchFind();
    afx_msg void OnSearchReplace();
    afx_msg void OnViewStopdiffing();
    afx_msg void OnEditRecordmacro();
    afx_msg void OnEditPlaymacro();
    afx_msg void OnSearchSelextholdingBuffer1();
    afx_msg void OnSearchSelextholdingBuffer2();
    afx_msg void OnSearchSelextholdingBuffer3();
    afx_msg void OnSearchSelextholdingBuffer4();
    afx_msg void OnSearchSelextholdingBuffer5();
    afx_msg void OnSearchSelextholdingBuffer6();
    afx_msg void OnSearchSelextholdingBuffer7();
    afx_msg void OnSearchSelextholdingBuffer8();
    afx_msg void OnSearchSelextholdingBuffer9();
    afx_msg void OnSearchSelextholdingBuffer10();
    afx_msg void OnMoveNextcharacter();
    afx_msg void OnMovePreviouschar();
    afx_msg void OnMoveNextline();
    afx_msg void OnMovePreviousline();
    afx_msg void OnMovePagedown();
    afx_msg void OnMovePageup();
    afx_msg void OnMoveNextword();
    afx_msg void OnMovePreviouseword();
    afx_msg void OnMoveEndofword();
    afx_msg void OnMoveBeginningofword();
    afx_msg void OnMoveNextparagraph();
    afx_msg void OnMovePreviouseparagraph();
    afx_msg void OnMoveEndofline();
    afx_msg void OnMoveBeginningofline();
    afx_msg void OnMoveBeginningoffile();
    afx_msg void OnMoveEndoffile();
    afx_msg void OnEditCut();
    afx_msg void OnEditUppercaseword();
    afx_msg void OnEditLowercaseword();
    afx_msg void OnEditCapitalizeword();
    afx_msg void OnEditStartselectaltl();
    afx_msg void OnEditStartcolumnselectaltc();
    afx_msg void OnSelectCancelselect();
    afx_msg void OnSelectSelectall();
    afx_msg void OnEditCuttoholding();
    afx_msg void OnEditCopytoholding();
    afx_msg void OnEditPasteholding();
	afx_msg void OnSearchCancelfind();
	afx_msg void OnMoveGotoline();
	afx_msg void OnInsertIncrementednumber();
	afx_msg void OnInsertSetincremnetstartvalue();
	afx_msg void OnMoveGotocolumn();
	afx_msg void OnSearchFindnext();
	afx_msg void OnSearchFindprevious();
	afx_msg void OnSelectSelectword();
	afx_msg void OnSelectSelectparagraph();
	afx_msg void OnViewFileproperties();
	afx_msg void OnInsertUser();
	afx_msg void OnEditUppercaseselection();
	afx_msg void OnEditLowercaseselection();
	afx_msg void OnInsertDatetimeRfcstandarddate();
	afx_msg void OnInsertDatetimeMmddyyhhmmss();
	afx_msg void OnInsertDatetimeDdmmyyhhmmss();
	afx_msg void OnInsertPagefeedmark();
	afx_msg void OnInsertByte();
	afx_msg void OnInsertDatetimeTimehhmmss();
	afx_msg void OnInsertDatetimeWeekday();
	afx_msg void OnInsertDatetimeMonthname();
	afx_msg void OnInsertDatetimeDateformattedaslocale();
	afx_msg void OnInsertFunction();
	afx_msg void OnInsertForloop();
	afx_msg void OnInsertIfcondition();
	afx_msg void OnSettingsSetupwed();
	afx_msg void OnEditLoadmacro();
	afx_msg void OnEditSavemacro();
	afx_msg void OnViewCococodecolector();
	afx_msg void OnCompileMake();
	afx_msg void OnCompileExecutedevstudioproject();
	afx_msg void OnFileSaveall();
	afx_msg void OnViewViewmacroheads();
	afx_msg void OnSelectMarkblock();
	afx_msg void OnMoveEndofpage();
	afx_msg void OnMoveBeginningofpage();
	afx_msg void OnWindowsNextbuffer();
	afx_msg void OnViewFullscreen();
	afx_msg void OnFileMultiopen();
	afx_msg void OnSettingsTogglescrollbars();
	afx_msg void OnSettingsReverseit();
	afx_msg void OnMacroAnimatemacro();
	afx_msg void OnDiffDiffone();
	afx_msg void OnDiffDifftwo();
	afx_msg void OnDiffDiffthree();
	afx_msg void OnDiffDifffour();
	afx_msg void OnDiffDiffive();
	afx_msg void OnEditCleannonascii();
	afx_msg void OnEditWraptowindow();
	afx_msg void OnEditWeedemptylines();
	afx_msg void OnInsertDeleteatcursor();
	afx_msg void OnInsertDeletebeforecursor();
	afx_msg void OnInsertDeleteline();
	afx_msg void OnInsertDeletetillendofline();
	afx_msg void OnInsertCSwitchcase();
	afx_msg void OnInsertCTemplate();
	afx_msg void OnInsertJavaTemplate();
	afx_msg void OnSettingsSearchhighlitecolorfg();
	afx_msg void OnSettingsCommenthighlitecolor();
	afx_msg void OnViewGotonextdifference();
	afx_msg void OnViewGotopreviousdifference();
	afx_msg void OnSettingsDiffaddcolor();
	afx_msg void OnSettingsDiffchangedcolor();
	afx_msg void OnSettingsDiffdelcolor();
	afx_msg void OnViewFilebufers();
	afx_msg void OnMove(int x, int y);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEditAppendtoholding();
	afx_msg void OnSearchHiteditmode();
	afx_msg void OnMacroSelectrecordholdingBuffer10();
	afx_msg void OnEditSelectrecordbufferBuffer1();
	afx_msg void OnMacroSelectrecordholdingBuffer1();
	afx_msg void OnMacroSelectrecordholdingBuffer3();
	afx_msg void OnMacroSelectrecordholdingBuffer4();
	afx_msg void OnMacroSelectrecordholdingBuffer5();
	afx_msg void OnMacroSelectrecordholdingBuffer6();
	afx_msg void OnMacroSelectrecordholdingBuffer7();
	afx_msg void OnMacroSelectrecordholdingBuffer8();
	afx_msg void OnMacroSelectrecordholdingBuffer9();
	afx_msg void OnWindowsMaximizecurrent();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnInsertBasicForloop();
	afx_msg void OnInsertBasicIf();
	afx_msg void OnInsertBasicSelectcase();
	afx_msg void OnInsertBasicFunction();
	afx_msg void OnInsertJavaPrivatemethod();
	afx_msg void OnAdvancedLockkeyboard();
	afx_msg void OnUpdateAdvancedLockkeyboard(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSearchHiteditmode(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewViewhex(CCmdUI* pCmdUI);
	afx_msg void OnSettingsAllowbackspacetowraplines();
	afx_msg void OnUpdateSettingsAllowbackspacetowraplines(CCmdUI* pCmdUI);
	afx_msg void OnSettingsSavetabsasspaces();
	afx_msg void OnUpdateSettingsSavetabsasspaces(CCmdUI* pCmdUI);
	afx_msg void OnInsertDatetimeBordersafedate();
	afx_msg void OnInsertTemplateone();
	afx_msg void OnInsertTemplatetwo();
	afx_msg void OnInsertTemplatethree();
	afx_msg void OnAdvancedSpellcheck();
	afx_msg void OnAdvancedCommentadstringspellcheck();
	afx_msg void OnMoveNextlongline();
	afx_msg void OnMoveMovepreviouslongline();
	afx_msg void OnSettingsLonglinecolorfg();
	afx_msg void OnSearchBracecount();
	afx_msg void OnHelpRegistration();
	afx_msg void OnAdvancedCleanoldbackups();
	afx_msg void OnHelpHelponkeyword();
	afx_msg void OnAdvancedCleanoldundofiles();
	afx_msg void OnSettingsSettabstop();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnFileOpen();
	afx_msg void OnFileSaveas2();
	afx_msg void OnAdvancedClearcurrentignorelist();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnEditSetwrappingwidth();
	afx_msg void OnSearchFindinfiles();
	afx_msg void OnInsertTemplatesOpentemplatefile();
	afx_msg void OnFileMultiopendest();
	afx_msg void OnMoveNextfunction();
	afx_msg void OnMovePreviousfunction();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

extern CWedView *mainview;

#ifndef _DEBUG  // debug version in wedView.cpp
inline CWedDoc* CWedView::GetDocument()
   { return (CWedDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WEDVIEW_H__87F3F48E_DE8E_11D2_BEED_002078105E2C__INCLUDED_)
