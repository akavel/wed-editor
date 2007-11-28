#if !defined(AFX_GOTO_H__45A56F44_FD70_11D2_B398_525400D994D7__INCLUDED_)
#define AFX_GOTO_H__45A56F44_FD70_11D2_B398_525400D994D7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// goto.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// goto dialog

class Cgoto : public CDialog
{
// Construction
public:
    Cgoto(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(Cgoto)
    enum { IDD = IDD_DIALOG7 };
        // NOTE: the ClassWizard will add data members here
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(Cgoto)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(Cgoto)
        // NOTE: the ClassWizard will add member functions here
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GOTO_H__45A56F44_FD70_11D2_B398_525400D994D7__INCLUDED_)