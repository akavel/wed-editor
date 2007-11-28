#if !defined(AFX_EXEC_H__21784642_139D_11D3_B398_525400D994D7__INCLUDED_)
#define AFX_EXEC_H__21784642_139D_11D3_B398_525400D994D7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// exec.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// exec command target

class exec : public CCmdTarget
{
	DECLARE_DYNCREATE(exec)

	exec();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(exec)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~exec();

	// Generated message map functions
	//{{AFX_MSG(exec)
	afx_msg void OnCompileMake();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXEC_H__21784642_139D_11D3_B398_525400D994D7__INCLUDED_)
