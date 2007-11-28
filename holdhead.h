#if !defined(AFX_HOLDHEAD_H__5369EEA4_F409_11D2_B398_525400D994D7__INCLUDED_)
#define AFX_HOLDHEAD_H__5369EEA4_F409_11D2_B398_525400D994D7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// HoldHead.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// HoldHead dialog

class HoldHead : public CDialog
{
// Construction
public:
	HoldHead(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(HoldHead)
	enum { IDD = IDD_DIALOG2 };
	CString	m_edit1;
	CString	m_edit10;
	CString	m_edit2;
	CString	m_edit3;
	CString	m_edit4;
	CString	m_edit5;
	CString	m_edit6;
	CString	m_edit7;
	CString	m_edit8;
	CString	m_edit9;
	CString	m_edit11;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(HoldHead)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(HoldHead)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOLDHEAD_H__5369EEA4_F409_11D2_B398_525400D994D7__INCLUDED_)
