#if !defined(AFX_SETUP_H__7C11A5A2_0520_11D3_B398_525400D994D7__INCLUDED_)
#define AFX_SETUP_H__7C11A5A2_0520_11D3_B398_525400D994D7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Setup.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// setup dialog

#include "page1.h"

class setup : public CPropertySheet
{
// Construction
public:
	setup(char *caption);   // standard constructor
	Page1  p1;

// Dialog Data
	//{{AFX_DATA(setup)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(setup)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(setup)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUP_H__7C11A5A2_0520_11D3_B398_525400D994D7__INCLUDED_)
