#if !defined(AFX_Coco_H__D2211722_06A9_11D3_B398_525400D994D7__INCLUDED_)
#define AFX_Coco_H__D2211722_06A9_11D3_B398_525400D994D7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Coco.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Coco dialog

class Coco : public CDialog
{
// Construction
public:
	Coco(CWnd* pParent = NULL);   // standard constructor
	void CreateBranch(int donode);
	void getitem(char *name) ;
	void BuildTree(CString &str) ;
	void GetNodeFname(CString &str);
	void ShowCode();


// Dialog Data
	//{{AFX_DATA(Coco)
	enum { IDD = IDD_DIALOG9 };
	CTreeCtrl	m_tree;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Coco)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Coco)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnButton1();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButton8();
	afx_msg void OnRclickTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnOperationsCopy();
	afx_msg void OnOperationsEdit();
	afx_msg void OnOperationsPaste();
	afx_msg void OnOperationsShow();
	afx_msg void OnOperationsDelete();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnOperationsNew();
	afx_msg void OnOperationsNewnode();
	afx_msg void OnButton11();
	afx_msg void OnButton12();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_Coco_H__D2211722_06A9_11D3_B398_525400D994D7__INCLUDED_)
