#if !defined(AFX_SEARCH_H__FA8B3803_E9A1_11D2_B398_525400D994D7__INCLUDED_)
#define AFX_SEARCH_H__FA8B3803_E9A1_11D2_B398_525400D994D7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Search.h : header file
//

#define		S_REGEX		 1
#define		S_UCASE		 2
#define		S_FUNCTION	 4

/////////////////////////////////////////////////////////////////////////////
// Search dialog

class Search : public CDialog
{
// Construction					   
public:
	int			m_stype;
	int			m_taush;
	int			m_esc;

	sellist		m_list;
	CStringList m_files;
	Search(CWnd* pParent = NULL);   // standard constructor
	int		IsCandidate(const char *str);

// Dialog Data
	//{{AFX_DATA(Search)
	enum { IDD = IDD_DIALOG3 };
	CComboBox	m_com2;
	CComboBox	m_com1;
	CString	m_combo1;
	CString	m_combo2;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Search)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Search)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancel2();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCheck1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio4();
	afx_msg void OnRadio1();
	afx_msg void OnCancel3();
	afx_msg void OnCancel4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCH_H__FA8B3803_E9A1_11D2_B398_525400D994D7__INCLUDED_)
