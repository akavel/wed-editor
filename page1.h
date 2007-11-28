#if !defined(AFX_PAGE1_H__4E572626_3E01_11D3_B398_525400D994D7__INCLUDED_)
#define AFX_PAGE1_H__4E572626_3E01_11D3_B398_525400D994D7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// page1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Page1 dialog

class Page1 : public CPropertyPage
{
	DECLARE_DYNCREATE(Page1)

// Construction
public:
	Page1();
	Page1(LPCTSTR  str);
	~Page1();

// Dialog Data
	//{{AFX_DATA(Page1)
	enum { IDD = IDD_PROPPAGE_LARGE1 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(Page1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(Page1)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE1_H__4E572626_3E01_11D3_B398_525400D994D7__INCLUDED_)
