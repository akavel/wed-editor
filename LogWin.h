#if !defined(AFX_LOGWIN_H__CD34F076_43EE_4915_8945_D259D158C695__INCLUDED_)
#define AFX_LOGWIN_H__CD34F076_43EE_4915_8945_D259D158C695__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogWin.h : header file
//

#define WM_LOGDBL	(WM_USER + 2)

#define LOGWIN_MAGIC 0x45345

/////////////////////////////////////////////////////////////////////////////
// CLogWin window 

class CFindFiles;

#define	DEFAULT_MAX_LINES 50000

class CLogWin : public CWnd

{
	friend CFindFiles;

// Construction
public:

	CLogWin();
	int	magic;

protected:

	CString		laststr, fill;

	CStringList strlist;
	CScrollBar  vs, hs;

	CSize	txtss;

	int		sw, sh;
	int		firstpaint;
	int		heightcnt, widthcnt;
	//int		lines;	
	int		lastoffset;
	int		in_timer;
	int		prevnl;
	int		bgcolor;
	int		maxlines;

// Attributes
public:

	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogWin)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	void ScanAction(CPoint point);

	void FirstPaint();
	void Clear();
	void AddString(const char *str);
	virtual ~CLogWin();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLogWin)
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGWIN_H__CD34F076_43EE_4915_8945_D259D158C695__INCLUDED_)
