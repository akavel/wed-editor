#if !defined(AFX_REGISTER_H__BCE9A6C2_0DC3_11D4_B398_525400D994D7__INCLUDED_)
#define AFX_REGISTER_H__BCE9A6C2_0DC3_11D4_B398_525400D994D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Register.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Register dialog

class Register : public CDialog
{
// Construction
public:
	Register(CWnd* pParent = NULL);   // standard constructor
		int Register::SumStr(CString &str) ;	
	void Register::Genpass();

// Dialog Data
	//{{AFX_DATA(Register)
	enum { IDD = IDD_DIALOG13 };
	CEdit	m_show;
	CString	m_reg;
	CString	m_company;
	CString	m_pass;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Register)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Register)
	afx_msg void OnKillfocusEdit1();
	afx_msg void OnKillfocusEdit2();
	virtual void OnOK();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGISTER_H__BCE9A6C2_0DC3_11D4_B398_525400D994D7__INCLUDED_)
