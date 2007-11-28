#if !defined(AFX_FILEINFO_H__20063A84_0509_11D3_B398_525400D994D7__INCLUDED_)
#define AFX_FILEINFO_H__20063A84_0509_11D3_B398_525400D994D7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FileInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// FileInfo dialog

class FileInfo : public CDialog
{
// Construction
public:
	FileInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(FileInfo)
	enum { IDD = IDD_DIALOG6 };
	CString	m_1;
	CString	m_2;
	CString	m_3;
	CString	m_4;
	CString	m_5;
	CString	m_6;
	CString	m_7;
	CString	m_8;
	CString	m_9;
	CString	m_10;
	CString	m_11;
	BOOL	m_check1;
	BOOL	m_check2;
	BOOL	m_check3;
	//}}AFX_DATA
	CWedView *v1;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(FileInfo)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(FileInfo)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEINFO_H__20063A84_0509_11D3_B398_525400D994D7__INCLUDED_)
