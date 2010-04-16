#if !defined(AFX_FINDFILES_H__DE00B16F_ADCC_4FB8_96BE_264542391715__INCLUDED_)
#define AFX_FINDFILES_H__DE00B16F_ADCC_4FB8_96BE_264542391715__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FindFiles.h : header file
//

#include "logwin.h"

/////////////////////////////////////////////////////////////////////////////
// CFindFiles dialog

class CFindFiles : public CDialog

{
// Construction
public:
	void SaveData();
	void OnCancel();

	int fonly, nocase, recur;
	int fcounter, dcounter, found, stop;
	SYSTEMTIME old;
	unsigned int oldc;

	void PersistCombo(const char *reg, const char *templ, CComboBox *box);
	void LoadToCombo(const char *reg, const char *templ, CComboBox *box);
	void CFindFiles::ScanFile(const char *fname, const char *needle);
	int CFindFiles::ScanRecurse(const char *src, const char *wild);

	CFindFiles(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFindFiles)
	enum { IDD = IDD_DIALOG14 };
	CComboBox	m_com4;
	CComboBox	m_com3;
	CLogWin	m_logwin;
	CEdit	m_lab;
	CComboBox	m_com1;
	CString	m_comstr1;
	CString	m_comstr4;
	CString	m_comstr3;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindFiles)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFindFiles)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButton1();
	afx_msg void OnButton3();
	afx_msg void OnButton2();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void	LogDblClick(unsigned int wParam, long lParam);
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDFILES_H__DE00B16F_ADCC_4FB8_96BE_264542391715__INCLUDED_)
