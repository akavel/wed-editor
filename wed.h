
/* =====[ wed.h ]========================================== 
                                                                             
   Description:     The wed project, implementation of the wed.h                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  1/9/2009  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

/////////////////////////////////////////////////////////////////////////////
// wed.h : main header file for the WED application
//

#include "resource.h"
#include "sellist.h"

#include "Search.h"
#include "resource.h"       // main symbols
#include "srcsel.h"
#include "splash.h"

#include "FindFiles.h"

#if !defined(AFX_WED_H__87F3F484_DE8E_11D2_BEED_002078105E2C__INCLUDED_)
#define AFX_WED_H__87F3F484_DE8E_11D2_BEED_002078105E2C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

/////////////////////////////////////////////////////////////////////////////
// Application limits

#define MAX_HOLDINGS 	10
#define MAX_DOC_LIMIT	300
#define MAX_BACKUP		2000000
#define MAXFILENAMES  	8096

/////////////////////////////////////////////////////////////////////////////
// Global Data

extern CFindFiles ffil; 

extern CString 	srcdir;
extern CString 	targdir;
extern CBitmap 	caret;
extern CFont 	ff;
extern LOGFONT 	fflf;
extern CFont 	pp;
extern LOGFONT 	pplf;

/////////////////////////////////////////////////////////////////////////////
// Application colors

extern COLORREF fgcol  ;
extern COLORREF bgcol  ;
extern COLORREF selcol ;
extern COLORREF cselcol;
extern COLORREF cadd   ;
extern COLORREF cdel   ;
extern COLORREF cchg   ;
extern COLORREF comm   ;
extern COLORREF srcc   ;
extern COLORREF prepro ;
extern COLORREF keywor ;

extern COLORREF clng   ;

extern int 	holdflag[MAX_HOLDINGS];
extern int 	tabs[MAX_HOLDINGS];

/////////////////////////////////////////////////////////////////////////////
// Application flags

extern int 	Tab2Space;
extern int 	timer_in;
extern int	backwrap;
extern int 	comline;
extern int 	currhold;
extern int 	currmac;
extern int 	was_esc;
extern int 	tabstop;
extern int 	newcount;
extern int	wait_exit;
extern int 	lastkeypress;
extern int	wantcaret;


extern CStringList holding[MAX_HOLDINGS];
extern CStringList macros[MAX_HOLDINGS];
extern CStringList combofill;

extern char  Mfilter[];
extern char  Ffilter[];

extern CString delim;

extern CWnd 		*currentedit;
extern char 		approot[];
extern CString		dataroot;

//extern int		splashed;

extern HCURSOR WaitCursor;
extern HCURSOR NormalCursor;

extern Search srcdlg;
extern Splash spp;

CView*  GetViewFromDoc(CDocument *doc);

extern void	SplitPath(CString &full,  CString &drive,
					CString &dir, CString &fname, CString &ext);


class CWedApp : public CWinApp

{
public:
    void NewFile();
    void OpenFile();

    CWedApp();
	~CWedApp();

    CMultiDocTemplate* pDocTemplate;
	BOOL LoadMacros();
	BOOL SaveMacros();
	BOOL SaveHoldings();
	BOOL LoadHoldings();
	char *err2str(long err);

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CWedApp)
	public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
    virtual BOOL SaveAllModified();
	virtual int Run();
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	virtual int DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt);
	virtual LRESULT ProcessWndProcException(CException* e, const MSG* pMsg);
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
	//}}AFX_VIRTUAL

// Implementation

    //{{AFX_MSG(CWedApp)
    afx_msg void OnAppAbout();
	afx_msg void OnFileSeachfiles();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WED_H__87F3F484_DE8E_11D2_BEED_002078105E2C__INCLUDED_)


// EOF

