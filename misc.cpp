/////////////////////////////////////////////////////////////////////////////
// misc.cpp : Services for the WED application
//

#include "stdafx.h"
#include "io.h"

#include "wed.h"

#include "StrList.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "wedDoc.h"
#include "wedView.h"
#include "splash.h"
#include "editor.h"
#include "wedview.h"
#include "notepad.h"
#include "build.h"
#include "about.h"
#include "misc.h"
#include "FileDialogST.h"

/////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Data

extern CWedApp		theApp;

CString		srcdir;
CString		targdir;
int 		timer_in = 0;

/////////////////////////////////////////////////////////////////////////////
// CView*  GetViewFromDoc(CDocument *doc)
// Get view from doc

CView*  GetViewFromDoc(CDocument *doc)

{
	CView*  ret = NULL;

	POSITION pos = doc->GetFirstViewPosition();
	for(;;)
		{
		if(!pos)
			break;
		CView *cv = (CView*)doc->GetNextView(pos);
		if(cv)
			{
			ASSERT_VALID(cv);
			ret = cv;
			break;
			}
		}
	return(ret);
}

/////////////////////////////////////////////////////////////////////////////
// CMenu 	*GetTemplateMenu()

CMenu 	*GetTemplateMenu()
{
    int iPos;
    CMenu* pViewMenu = NULL;
    CMenu* pTopMenu = AfxGetMainWnd()->GetMenu();

    for (iPos = pTopMenu->GetMenuItemCount()-1; iPos >= 0; iPos--)
    {
        CMenu* pMenu = pTopMenu->GetSubMenu(iPos);
        if (pMenu && pMenu->GetMenuItemID(0) == ID_VIEW_TOOLBAR)
        {
            pViewMenu = pMenu;
            break;
        }
    }
    ASSERT(pViewMenu != NULL);

    CMenu* pfMenu = NULL;
    for (iPos = pViewMenu->GetMenuItemCount()-1; iPos >= 0; iPos--)
    {
        pfMenu = pViewMenu->GetSubMenu(iPos);
        if(pfMenu)
            break;
    }
    ASSERT(pfMenu != NULL);
    return (pfMenu);
}

/////////////////////////////////////////////////////////////////////////////
// void	OpenSource(CString &dir)
// Opensource

void	OpenSource(CString &dir)

{
	CWedDoc *pDoc;

	CFileDialogST cdf(TRUE);
	CString droot, dresult, dfile, fname;
	char *buff = (char*)malloc(MAXFILENAMES + 1);

	if(!buff)
		{
		AfxMessageBox("Cannot get memory for OpenFile");
		return;
		}
	*buff = '\0';

	if(dir == "")
		cdf.m_ofn.lpstrInitialDir = droot;
	else
		cdf.m_ofn.lpstrInitialDir = dir;

	cdf.m_ofn.lpstrFilter = Ffilter;
	cdf.m_ofn.lpstrFile = (char *)buff;
	cdf.m_ofn.nMaxFile = MAXFILENAMES;
	cdf.m_ofn.nFilterIndex = 1;
	cdf.m_ofn.Flags |= OFN_ALLOWMULTISELECT;

	if(cdf.DoModal() == IDOK)
		{
		POSITION pos = cdf.GetStartPosition();
		while(TRUE)
			{
			if (!pos)
				break;
			fname = cdf.GetNextPathName(pos);
			pDoc = (CWedDoc*)
					AfxGetApp()->OpenDocumentFile(fname);
			if(!pDoc)
				break;

			if(YieldToWinEx())
				break;
			}
		dir = fname;
		PathToDir(dir);
		}
	free(buff);
}

/////////////////////////////////////////////////////////////////////////////
// void	OpenSource(CString &dir)
// Opensource

void	SaveSourceAs(CString &dir)

{
}


/////////////////////////////////////////////////////////////////////////////
// void 	SaveAllDocs()
// Save all documents ...

void 	SaveAllDocs()

{
	CWedDoc*  pDoc = NULL;
    CMultiDocTemplate* pDocTemplate =
				((CWedApp*)AfxGetApp())->pDocTemplate;
	POSITION Pos = 	pDocTemplate->GetFirstDocPosition();
	for(;;)
		{
		if(!Pos)
			break;
		CWedDoc* doc = (CWedDoc*)pDocTemplate->GetNextDoc(Pos);

		if(!doc)
			continue;

		ASSERT_VALID(doc);

		if(doc->IsModified())
			doc->OnSaveDocument(doc->GetPathName());
		}
}

/////////////////////////////////////////////////////////////////////////////
// void 	message(const char * str)
// Put a message to the status bar:

void 	message(const char * str)

{
	((CMainFrame*)theApp.m_pMainWnd)->m_wndStatusBar.SetPaneText(0, str);
	timer_in = 8;
}

/////////////////////////////////////////////////////////////////////////////
// void 	rowcol(const char * str)

void 	rowcol(const char * str)

{
	((CMainFrame*)theApp.m_pMainWnd)->m_wndStatusBar.SetPaneText(1, str);
}


/////////////////////////////////////////////////////////////////////////////
// void 	filesize(const char * str)

void 	filesize(const char * str)

{
	((CMainFrame*)theApp.m_pMainWnd)->m_wndStatusBar.SetPaneText(2, str);
}


/////////////////////////////////////////////////////////////////////////////
// void 	hold(const char * str)

void 	hold(const char * str)

{
	((CMainFrame*)theApp.m_pMainWnd)->m_wndStatusBar.SetPaneText(5, str);
}


/////////////////////////////////////////////////////////////////////////////
// void 	mac(const char * str)

void 	mac(const char * str)

{
	((CMainFrame*)theApp.m_pMainWnd)->m_wndStatusBar.SetPaneText(6, str);
}


/////////////////////////////////////////////////////////////////////////////
// void 	mode(const char * str)

void 	mode(const char * str)

{
	((CMainFrame*)theApp.m_pMainWnd)->m_wndStatusBar.SetPaneText(7, str);
}



/////////////////////////////////////////////////////////////////////////////
// void	PathToFname(CString &docname)
// Shorten path to filename

void	PathToFname(CString &docname)

{
	int idx;
	CString filename;

	if((idx = docname.ReverseFind('\\')) != -1)
		{
		filename = docname.Right(docname.GetLength() - (idx+1));
		docname = filename;
		}
}


/////////////////////////////////////////////////////////////////////////////
// void	PathToDir(CString &docname)
// Shorten path to directory name

void	PathToDir(CString &docname)

{
	int idx;
	CString filename;

	if((idx = docname.ReverseFind('\\')) != -1)
		{
		filename = docname.Left(idx+1);
		docname = filename;
		}
}


/////////////////////////////////////////////////////////////////////////////
//  void	ShortenPath(CString &str, int len)
// Shorten path to len

void	ShortenPath(CString &str, int len)

{
	int slen = str.GetLength();

	// Nothing to do
	if(slen <= len)
		return;

	CString lstr = str.Left ((len-5)/2);
	CString rstr = str.Right((len-5)/2);
	str = lstr + " ... " + rstr;
}

#define     ROTATE_LONG_LEFT(x, n)  (((x) << (n))  | ((x) >> (32 - (n))))
#define     ROTATE_LONG_RIGHT(x, n) (((x) >> (n))  | ((x) << (32 - (n))))

/////////////////////////////////////////////////////////////////////////////
// int		HashString(const char *name)

int		HashString(const char *name)

{
	unsigned int ret_val = 0;

    while(*name != '\0')
        {
        ret_val ^= (int)*name;
        ret_val  = ROTATE_LONG_RIGHT(ret_val, 3);          /* rotate right */
        *name++;
        }
    return((int)ret_val);
}

///////////////////////////////////////////////////////////////////////////
// YieldToWin
// Let every accumulated message go through

void    YieldToWin()

{
    while(TRUE)
        {
        MSG msg;
        if(!PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
           break;
        TranslateMessage(&msg); DispatchMessage(&msg);
        }
}

///////////////////////////////////////////////////////////////////////////
// YieldToWinEx
// Let every accumulated message go through
// Return 1 if ESC | Ctrl-Break pressed -- 2 if EXITING

int     YieldToWinEx()

{
    int ret_val = 0;
    while(TRUE)
        {
        MSG msg;
        if(!PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
           break;

        // Ctrl-Break
        if(msg.message == WM_KEYDOWN)
            {
            if(msg.wParam == VK_CANCEL)
                {
                ret_val = 1; break;
                }
            }
        // Esc
        if(msg.message == WM_CHAR)
            {
            if(msg.wParam == VK_ESCAPE)
                {
                ret_val = 1; break;
                }
            }
        // App exit
        if(msg.message == WM_QUIT)
                {
                wait_exit = TRUE;
                ret_val = 2; break;
                }
        // App kill
        if(msg.message == WM_DESTROY)
                {
                wait_exit = TRUE;
                ret_val = 2; break;
                }
        // Every other message is processed
        TranslateMessage(&msg); DispatchMessage(&msg);
        }
    return(ret_val);
}

////////////////////////////////////////////////////////////
// Find how many characters in starting

int	 	FindNumOfChar(CString &str, CString &mus, int start)

{
	int ret = 0, loop;
	int lim = str.GetLength();

	for(loop = start; loop < lim; loop++)
		{
		if(mus.Find(str.GetAt(loop)) >=0)
			{
			ret++;
			}
		}
	return(ret);
}

/*
 * Walk thru the directory, create non existing middle directories.
 */

int     create_full_dir(const char *fullname)

{
    PATH    fin;
    char    *one_path, *one_dir;
    int     progress = 1, err = 0, fullen;

    one_path   =  (char *)malloc(_MAX_PATH + 2);
    one_dir    =  (char *)malloc(_MAX_PATH + 2);

	ASSERT(one_path);
	ASSERT(one_dir);

    if(!one_path || !one_dir)
        {
        printf("Out of memory.");
        //err = SYSTEM_NO_MEMORY;
        goto endd;
        }

    _splitpath(fullname, fin.drive, fin.dir, fin.fname, fin.ext);

    fullen = strlen(fin.dir);

    while(TRUE)
        {
        int len = strcspn(fin.dir + progress, "\\/");

        if(progress >= fullen)
            break;

        len = min(len, _MAX_PATH-1);

        if(len)
            strncpy(one_dir, fin.dir, progress + len);

        one_dir[progress +len] = '\0';
        progress += len + 1;

        _makepath(one_path, fin.drive, one_dir, "", "");

        //PrintToNotepad("Component: '%s'\r\n", one_path);

        if(!is_valid_path(one_path))
            {
            if(!CreateDirectory(one_path, NULL))
                {
                err = TRUE; break;
                }
            }
        }

    endd:
        free(one_path);
        free(one_dir);

    return(err);
}


/*
 * Return true if path exists. Path can be a fully blown one with drive.
 *
 * Side effect: Progam might change current directory when aborted
 */

int     is_valid_path(char *str)

{
    PATH    *fout;
    int     ret_val = FALSE;
    char    org_dir[_MAX_PATH], tmp_path[_MAX_PATH];

    fout      =  (PATH *)malloc(sizeof(PATH) +2);
    if(!fout)
        {
        ret_val = FALSE;

        printf(" Out of memory. ");

        //if(prompt)
        //    prompt_user();

        ret_val = -1; //SYSTEM_NO_MEMORY;
        goto endd;
        }

    _splitpath(str, fout->drive, fout->dir, fout->fname, fout->ext);
    _makepath(tmp_path, fout->drive, fout->dir, "", "");

    GetCurrentDirectory(sizeof(org_dir), org_dir);
    ret_val = SetCurrentDirectory(tmp_path);
    SetCurrentDirectory(org_dir);

 endd:

    free(fout);
    return(ret_val);
}

/////////////////////////////////////////////////////////////////////////////////////
//
// This routine is a helper that finds the path to the special folder:
//
// \param SpecialFolder			- an UINT-define (See #defines above or (MSDN))\n
// \param SpecialFolderString	- Reference to a CString that receives the path to the special folder
//
// Returns a BOOL - Found or not \n
//
// CSIDL_APPDATA
// CSIDL_ALTSTARTUP  	File system directory that corresponds to the user's nonlocalized Startup program group.
// CSIDL_APPDATA  		File system directory that serves as a common repository for application-specific data.
// CSIDL_BITBUCKET  	File system directory containing file objects in the user's Recycle Bin. The location of this directory is not in the registry; it is marked with the hidden and system attributes to prevent the user from moving or deleting it.
// CSIDL_COMMON_ALTSTARTUP  File system directory that corresponds to the nonlocalized Startup program group for all users.
// CSIDL_COMMON_DESKTOPDIRECTORY  File system directory that contains files and folders that appear on the desktop for all users.
// CSIDL_COMMON_FAVORITES  File system directory that serves as a common repository for all users' favorite items.
// CSIDL_COMMON_PROGRAMS  File system directory that contains the directories for the common program groups that appear on the Start menu for all users.
// CSIDL_COMMON_STARTMENU  File system directory that contains the programs and folders that appear on the Start menu for all users.
// CSIDL_COMMON_STARTUP  File system directory that contains the programs that appear in the Startup folder for all users.
// CSIDL_CONTROLS  		Virtual folder containing icons for the Control Panel applications.
// CSIDL_COOKIES  		File system directory that serves as a common repository for Internet cookies.
// CSIDL_DESKTOP  		Windows Desktop virtual folder at the root of the namespace.
// CSIDL_DESKTOPDIRECTORY  File system directory used to physically store file objects on the desktop (not to be confused with the desktop folder itself).
// CSIDL_DRIVES  		My Computer  virtual folder containing everything on the local computer: storage devices, printers, and Control Panel. The folder may also contain mapped network drives.
// CSIDL_FAVORITES  	File system directory that serves as a common repository for the user's favorite items.
// CSIDL_FONTS  		Virtual folder containing fonts.
// CSIDL_HISTORY  		File system directory that serves as a common repository for Internet history items.
// CSIDL_INTERNET  		Virtual folder representing the Internet.
// CSIDL_INTERNET_CACHE  File system directory that serves as a common repository for temporary Internet files.
// CSIDL_NETHOOD  		File system directory containing objects that appear in the network neighborhood.
// CSIDL_NETWORK  		Network Neighborhood Folder—virtual folder representing the top level of the network hierarchy.
// CSIDL_PERSONAL  		File system directory that serves as a common repository for documents.
// CSIDL_PRINTERS  		Virtual folder containing installed printers.
// CSIDL_PRINTHOOD  	File system directory that serves as a common repository for printer links.
// CSIDL_PROGRAMS  		File system directory that contains the user's program groups (which are also file system directories).
// CSIDL_RECENT  		File system directory that contains the user's most recently used documents.
// CSIDL_SENDTO  		File system directory that contains Send To menu items.
// CSIDL_STARTMENU  	File system directory containing Start menu items.
// CSIDL_STARTUP  		File system directory that corresponds to the user's Startup program group. The system starts these programs whenever any user logs onto Windows NT or starts Windows 95.
// CSIDL_TEMPLATES  	File system directory that serves as a common repository for document templates.
//


 BOOL	GetSpecialFolder(UINT SpecialFolder, CString &SpecialFolderString)

{
	HRESULT hr;

	LPITEMIDLIST pidl;

	hr = SHGetSpecialFolderLocation(NULL, SpecialFolder, &pidl);

    if(SUCCEEDED(hr))
		{
		// Convert the item ID list's binary representation into a file system path
		char szPath[_MAX_PATH];

		if(SHGetPathFromIDList(pidl, szPath))
			{
			// Allocate a pointer to an IMalloc interface
			LPMALLOC pMalloc;

			// Get the address of our task allocator's IMalloc interface
			hr = SHGetMalloc(&pMalloc);

			// Free the item ID list allocated by SHGetSpecialFolderLocation
			pMalloc->Free(pidl);

			// Free our task allocator
			pMalloc->Release();

			// Work with the special folder's path (contained in szPath)
			SpecialFolderString = szPath;	SpecialFolderString += "\\";
			return TRUE;
			}
		}
	return FALSE;
}

