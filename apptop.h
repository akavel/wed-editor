#if !defined(AFX_APPTOP_H__C7BD8AA0_3D42_11D3_B398_525400D994D7__INCLUDED_)
#define AFX_APPTOP_H__C7BD8AA0_3D42_11D3_B398_525400D994D7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AppTop.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AppTop window

class AppTop : public CWnd
{
// Construction
public:
	AppTop();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AppTop)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~AppTop();

	// Generated message map functions
protected:
	//{{AFX_MSG(AppTop)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPTOP_H__C7BD8AA0_3D42_11D3_B398_525400D994D7__INCLUDED_)
