#if !defined(AFX_SELLIST_H__A07972E4_F794_11D2_B398_525400D994D7__INCLUDED_)
#define AFX_SELLIST_H__A07972E4_F794_11D2_B398_525400D994D7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// sellist.h : header file
//
			
/////////////////////////////////////////////////////////////////////////////
// sellist window

class sellist : public CCheckListBox
{
// Construction
public:
	sellist();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(sellist)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~sellist();

	// Generated message map functions
protected:
	//{{AFX_MSG(sellist)
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELLIST_H__A07972E4_F794_11D2_B398_525400D994D7__INCLUDED_)
