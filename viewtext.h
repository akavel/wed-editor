#if !defined(AFX_VIEWTEXT_H__B8B00522_09CF_11D3_B398_525400D994D7__INCLUDED_)
#define AFX_VIEWTEXT_H__B8B00522_09CF_11D3_B398_525400D994D7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ViewText.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ViewText dialog

class ViewText : public CDialog
{
// Construction
public:
	ViewText(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ViewText)
	enum { IDD = IDD_DIALOG10 };
	CString	m_str;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ViewText)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ViewText)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWTEXT_H__B8B00522_09CF_11D3_B398_525400D994D7__INCLUDED_)
