// wedDoc.h : interface of the CWedDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WEDDOC_H__87F3F48C_DE8E_11D2_BEED_002078105E2C__INCLUDED_)
#define AFX_WEDDOC_H__87F3F48C_DE8E_11D2_BEED_002078105E2C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxcoll.h>

#include <sys/types.h> 
#include <sys/stat.h>


class CWedDoc : public CDocument
{
protected: // create from serialization only
	CWedDoc();
	DECLARE_DYNCREATE(CWedDoc)

// Attributes
public:

	//srcsel ssel(AfxGetMainWnd());
	srcsel	ssel;
	
	StrList strlist;
	CStringList undo;
	CStringList redo;
	CStringList rec;
	CString comment;
	int	readonly;
	int	spaceify;
	int	inited;
	int undopos;
	int origlines;
	struct _stat docstat;
	struct _stat docstat2;
	int unix;
	int maxcol;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWedDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	int notfullundo;
	int undoorig;
	virtual ~CWedDoc();
	void	SaveUndo();
	void	SaveRedo();
	void	LoadRedo(LPCTSTR lpszPathName);
	void	LoadUndo(LPCTSTR lpszPathName);
	void	AutoSave();
	void 	SaveBackup(const char *docname);
	int		GetNumOfDocs();
	void 	Serialize(CArchive& ar, const char *docname);
	int		GetComment(const char *fname);


#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWedDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WEDDOC_H__87F3F48C_DE8E_11D2_BEED_002078105E2C__INCLUDED_)
