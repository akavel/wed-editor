#if !defined(AFX_GOTOLINE_H__45A56F45_FD70_11D2_B398_525400D994D7__INCLUDED_)
#define AFX_GOTOLINE_H__45A56F45_FD70_11D2_B398_525400D994D7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// gotoline.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGotoLine dialog

class CGotoLine : public CDialog
{
// Construction
public:
	CString caption;
	CGotoLine(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGotoLine)
	enum { IDD = IDD_DIALOG7 };
	CString	m_str;
	CString	m_prompt;
	//}}AFX_DATA
	int m_esc;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGotoLine)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGotoLine)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GOTOLINE_H__45A56F45_FD70_11D2_B398_525400D994D7__INCLUDED_)
