#if !defined(AFX_SRCSEL_H__67B2EFC3_E9B8_11D2_B398_525400D994D7__INCLUDED_)
#define AFX_SRCSEL_H__67B2EFC3_E9B8_11D2_B398_525400D994D7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// srcsel.h : header file
//

#include "sellist.h"

/////////////////////////////////////////////////////////////////////////////
// srcsel dialog

class srcsel : public CDialog
{
protected:
    CToolBar        m_wndToolBar;
    CToolBarCtrl    m_ToolBarCtrl;

// Construction
public:

    sellist slb;

	int		m_busy;
	int		m_rep;
    int		m_shown;
    int		m_err;
	void	GotoSel();
    int		connect;
    CWordArray linea;
    CWordArray lineb;
    CWordArray cola;

	void DoChange(int line, int undog);

	// standard constructor
    srcsel(CWnd* pParent = AfxGetMainWnd());  

	// standard destructor
    virtual 	~srcsel();

// Dialog Data
    //{{AFX_DATA(srcsel)
    enum { IDD = IDD_DIALOG4 };
    CString m_list;
    CString m_src;
    //}}AFX_DATA

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(srcsel)
	protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(srcsel)
    afx_msg void OnDblclkList1();
    afx_msg void OnSelchangeList1();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    virtual BOOL OnInitDialog();
    afx_msg void OnButton1();	  
    afx_msg void OnButton2();
	afx_msg void OnButton3();
    afx_msg void OnButton4();
	virtual void OnOK();
	afx_msg void OnButton10();
	afx_msg void OnButton9();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnClose();
	afx_msg int OnCharToItem(UINT nChar, CListBox* pListBox, UINT nIndex);
	afx_msg void OnButton5();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRCSEL_H__67B2EFC3_E9B8_11D2_B398_525400D994D7__INCLUDED_)
