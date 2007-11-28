#if !defined(AFX_PAGE2_H__C80B5EA3_3E15_11D3_B398_525400D994D7__INCLUDED_)
#define AFX_PAGE2_H__C80B5EA3_3E15_11D3_B398_525400D994D7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Page2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Page2 dialog

class Page2 : public CPropertyPage

{
// Construction
public:
	Page2();   // standard constructor
	Page2(LPCTSTR  str);

	~Page2();

// Dialog Data
	//{{AFX_DATA(Page2)
	enum { IDD = IDD_OLE_PROPPAGE_LARGE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Page2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Page2)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE2_H__C80B5EA3_3E15_11D3_B398_525400D994D7__INCLUDED_)
