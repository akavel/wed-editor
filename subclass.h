#if !defined(AFX_SUBCLASS_H__C7BD8AA3_3D42_11D3_B398_525400D994D7__INCLUDED_)
#define AFX_SUBCLASS_H__C7BD8AA3_3D42_11D3_B398_525400D994D7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SubClass.h : header file
//

#define  SP_STOP		1
#define  SP_OK			2
#define  SP_IGNORE		3
#define  SP_IGNORE_ALL	4
#define  SP_LEARN		5

/////////////////////////////////////////////////////////////////////////////
// SubClass dialog

class SubClass : public CDialog
{
// Construction
public:
	SubClass(CWnd* pParent = NULL);   // standard constructor
	int		m_ret;
	FILE	*m_fp;

// Dialog Data
	//{{AFX_DATA(SubClass)
	enum { IDD = IDD_DIALOG11 };
	CButton	m_b4;
	CButton	m_b1;
	CButton	m_cancel;
	CButton	m_ok;
	CComboBox	m_combo;
	CString	m_result;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SubClass)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SubClass)
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton4();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUBCLASS_H__C7BD8AA3_3D42_11D3_B398_525400D994D7__INCLUDED_)
