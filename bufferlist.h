#if !defined(AFX_BUFFERLIST_H__F71BD6A0_DFE4_11D2_BEED_002078105E2C__INCLUDED_)
#define AFX_BUFFERLIST_H__F71BD6A0_DFE4_11D2_BEED_002078105E2C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BufferList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// BufferList dialog

class BufferList : public CDialog
{
// Construction
public:
	long m_cv;
	BufferList(CWnd* pParent = NULL);   // standard constructor
	void	Fill();

// Dialog Data
	//{{AFX_DATA(BufferList)
	enum { IDD = IDD_DIALOG1 };
	CEdit	m_edit1;
	CListBox	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BufferList)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(BufferList)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual void OnOK();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkList1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUFFERLIST_H__F71BD6A0_DFE4_11D2_BEED_002078105E2C__INCLUDED_)
