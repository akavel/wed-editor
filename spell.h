#if !defined(AFX_SPELL_H__BC3142E1_5BF0_11D3_B398_525400D994D7__INCLUDED_)
#define AFX_SPELL_H__BC3142E1_5BF0_11D3_B398_525400D994D7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// spell.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// spell dialog

class spell : public CDialog
{
// Construction
public:
	spell(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(spell)
	enum { IDD = IDD_DIALOG10 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(spell)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(spell)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPELL_H__BC3142E1_5BF0_11D3_B398_525400D994D7__INCLUDED_)
