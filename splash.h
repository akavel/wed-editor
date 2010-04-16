#if !defined(AFX_SPLASH_H__5369EEA3_F409_11D2_B398_525400D994D7__INCLUDED_)
#define AFX_SPLASH_H__5369EEA3_F409_11D2_B398_525400D994D7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Splash.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Splash dialog

class Splash : public CDialog
{
// Construction
public:
	void Show();
	void Hide();
	Splash(CWnd* pParent = NULL);   // standard constructor

	int splashed;

// Dialog Data
	//{{AFX_DATA(Splash)
	enum { IDD = IDD_DIALOG5 };
	CEdit	m_edit1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Splash)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Splash)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLASH_H__5369EEA3_F409_11D2_B398_525400D994D7__INCLUDED_)
