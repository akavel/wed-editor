
/* =====[ FindFiles.cpp ]========================================== 
                                                                             
   Description:     The wed project, implementation of the FindFiles.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  1/7/2009  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

// FindFiles.cpp : implementation file
//

#include "stdafx.h"
#include "wed.h"

#include <malloc.h>
#include <io.h>
#include <direct.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

#include "FindFiles.h"
#include "mxpad.h"
#include "DlgGetPath.h"								//Definition to get path
#include "RegEx.h"
#include "StringEx.h"
#include "WedDoc.h"
#include "WedView.h"
#include "misc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	NORMAL_SRC	0
#define	NOCASE_SRC	1
#define	REGEX_SRC	2

//CStringList dirfill;
//CStringList extfill;
//CStringList pathfill;

#define MAXRECENT 12

static	CString strConfig = "Remember";

//////////////////////////////////////////////////////////////////////////
//

int		wildcmp(const char *string, const char *wild) 

{
	const char *cp = NULL, *mp = NULL;

	// Scan thru initial non wild
	while ((*string) && (*wild != '*')) 
		{
		if ((*wild != *string) && (*wild != '?')) 
			{
			// Non wild mismatch
			return 0;
			}
		wild++;	string++;
		}

	//
	while (*string) 
		{
		if (*wild == '*') 
			{
			// End of wild
			if (!*++wild) 
				{
				return 1;
				}
			mp = wild;
			cp = string+1;
			} 
		else if ((*wild == *string) || (*wild == '?')) 
			{
			wild++;
			string++;
			} 
		else 
			{
			wild = mp;
			string = cp++;
			}
		}

	// Skip to end
	while (*wild == '*') 
		{
		wild++;
		}

	return !*wild;
}

//////////////////////////////////////////////////////////////////////////

int		wildcmparr(const char *string, const char *wild) 

{
	// Early out
	if(strchr(wild, ';') == NULL)
		{
		return(wildcmp( string, wild));
		}

	int ret = 0;
	char	tmp[_MAX_PATH];	
	const char *next = wild;

	while(true)
		{
		char *endd = strchr(next, ';');

		// Emit last one if any
		if(!endd)
			{
			int len2 = min(strlen(next), sizeof(tmp));
			strncpy(tmp, next, len2);
			tmp[len2] = 0;

			//P2N("Parsed- '%s'\r\n", tmp);

			ret = wildcmp(string, tmp);
			break;
			}

		// Cap it off at storage limit
		int len = min(endd-next, sizeof(tmp));
		strncpy(tmp, next, len );
		tmp[len] = 0;
	
		//P2N("Parsed+ '%s'\r\n", tmp);

		ret = wildcmp(string, tmp);
		if(ret)
			break;

		next = endd + 1;
		if(*next == 0)
			break;
		}

	return ret;
}


int		heapcheck(const char *str, int showok)

{	 
	CString str2 = str;
	
	int heapstatus = _heapchk();

	//if(str2 == "")
	//	{
	//	str2.Format("%s -- line :: %d ", __FILE__ , __LINE__);
	//	}

   //P2N("Heap check ret = %d\r\n", _heapchk());

	switch( heapstatus )
		{
		case _HEAPOK:
			if(showok)
				P2N("%s Heap Check -- OK - heap is fine\r\n", str2);
			break;

		case _HEAPEMPTY:
			P2N("%s Heap Check -- OK - heap is empty\r\n", str2);
			break;

		case _HEAPBADBEGIN:
			P2N( "%s Heap Check --ERROR - bad start of heap\r\n", str2);
			break;

		case _HEAPBADNODE:
			P2N( "%s Heap Check --ERROR - bad node in heap\r\n", str2);
			break;

		default:
			P2N("%s UKN - heap ret code\r\n", str2);
			break;
		}

   return 0;
}

///////////////////////////////////////////////////////////////////////////
// YieldToWinEx
// Let every accumulated message go through
// Return 1 if ESC | Ctrl-Break pressed -- 2 if EXITING


static int     YieldToWinEx()

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
                //wait_exit = TRUE;
                ret_val = 2; break;
                }
        // App kill
        if(msg.message == WM_DESTROY)
                {
                //wait_exit = TRUE;
                ret_val = 2; break;
                }
        // Every other message is processed
        TranslateMessage(&msg); DispatchMessage(&msg);
        }
    return(ret_val);
}

/////////////////////////////////////////////////////////////////////////////
//  void	ShortenPath(CString &str, int len)
// Shorten path to len

static void	ShortenPath(CString &str, int len)

{
	int slen = str.GetLength();

	// Nothing to do
	if(slen <= len)
		return;

	CString lstr = str.Left ((len-5)/2);
	CString rstr = str.Right((len-5)/2);
	str = lstr + " ... " + rstr;
}


//////////////////////////////////////////////////////////////////////////
//
// Function name:    IsDir
// Description:      return true if it is a directory 
// Return type:      
// Argument:         const char *str
//
//////////////////////////////////////////////////////////////////////////

int		IsDir(const char *str)

{
	int ret = 0;		// Default to NOT
	struct _stat buff; 

	CString str2(str);

	if(str2 == "")
		goto endd;

	// Repair path if it ends in backslash
	if(str2[str2.GetLength() - 1] == '\\')
		{
		if(str2[str2.GetLength() - 2] != ':')
			{
			//P2N("backslash on IsDir()\r\n");
			str2 = str2.Mid(0, str2.GetLength() - 1);
			}
		}

	if(_stat(str2, &buff) < 0)
		{
		//P2N("Not stat\r\n");
		goto endd;
		}

	if(buff.st_mode & _S_IFDIR)
		{
		//P2N("Not dir\r\n");
		ret = true;
		}
endd:
	return ret;
}

#if 0
	CString indir, outdir;

	if(cline != "")
		{
		// Parse command line:
		int idx3, idx2, idx1 = cline.Find(' ');
		if(idx1 >= 0)
			{
			indir = cline.Mid(0, idx1);
			idx2 = cline.Find(' ', idx1);
			if(idx2 >= 0)
				{
				idx3 = cline.Find(' ', idx1);
				if(idx3 >= 0)
					{
					outdir = cline.Mid(idx2 + 1, idx3);
					}
				else{
					outdir = cline.Mid(idx2 + 1);
					}
				}
			}
		else
			{
			indir = cline.Mid(0);
			}

		// Eval correct command line
		if(outdir == "")
			{	
			MBOX("Timedim: Cannot automate with one command argument. Use: timedim in_dir out_dir");
			}
		else
			{
			//P2N("Automating. indir='%s' outdir='%s'\r\n", indir, outdir);
			}
		}
	else
		{
		//P2N("Empty command line\r\n");
		}

#endif

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


static BOOL	GetSpecialFolder(UINT SpecialFolder, CString &SpecialFolderString)

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


//////////////////////////////////////////////////////////////////////////
//
// Function name:    largeuint2double
// Description:      <empty description>
// Return type:      
// Argument:         ULARGE_INTEGER lint
//
//////////////////////////////////////////////////////////////////////////

double	largeuint2double(ULARGE_INTEGER lint)

{
	double ret;

	ret =  ((double)lint.HighPart) * (1 << 16);
	ret *= (1 << 16);
	ret  += lint.LowPart;

	return(ret);
}

//////////////////////////////////////////////////////////////////////////
//
// Function name:    uint64todouble
// Description:      <empty description>
// Return type:      
// Argument:         __int64 int64val
//
//////////////////////////////////////////////////////////////////////////

double	uint64todouble(__int64 int64val)

{
	double ret = 0;

	unsigned int *ptr = (unsigned int*)&int64val;

	ret = *(ptr + 1);
	ret *= (1 << 16); ret *= (1 << 16);	
	ret += *(ptr);
	
	return(ret);
}

//////////////////////////////////////////////////////////////////////////

double	GetFreeDiskSpace(const char *drv)

{
	ULARGE_INTEGER FreeBytesAvailableToCaller, TotalNumberOfBytes, TotalNumberOfFreeBytes;
	
	CString str(drv);

	// Repair free space drive string
	str = str.Left(3);

	double freeb = 0;

	BOOL ret = GetDiskFreeSpaceEx(
			str,
			&FreeBytesAvailableToCaller,	// disk available to the caller
			&TotalNumberOfBytes,			// receives the number of bytes on disk
			&TotalNumberOfFreeBytes		// receives the free bytes on disk
			);

	if(ret)
		{
		freeb = largeuint2double(FreeBytesAvailableToCaller);
		}

	//P2N("Get free space %s %.0f\r\n", str, freeb);

	return freeb;
}

//////////////////////////////////////////////////////////////////////////
//
// Function name:    addcommas
// Description:      <empty description>
// Return type:      
// Argument:         CString &str
//
//////////////////////////////////////////////////////////////////////////

void	addcommas(CString &str) 

{
	CString tmp;

	//P2N("addcomas() in='%s'  ", str);

	int len = str.GetLength();

	// Reverse string, add commas
	for(int loop = 0; loop < len ; loop++)
		{
		if(loop % 3 == 0 && loop != 0 ) 
			tmp+= ',';
		
		tmp += str[len - 1 - loop];
		}

	// Get ready to reconstruct
	str = ""; len = tmp.GetLength();

	// Reverse back to original
	for(int loop2 = 0; loop2 < len ; loop2++)
		{
		str += tmp[len - 1 - loop2];
		}

	//P2N("out='%s'\r\n", str);
}

/////////////////////////////////////////////////////////////////////////////
// CFindFiles dialog


CFindFiles::CFindFiles(CWnd* pParent /*=NULL*/)
	: CDialog(CFindFiles::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFindFiles)
	m_comstr1 = _T("");
	m_comstr4 = _T("");
	m_comstr3 = _T("");
	//}}AFX_DATA_INIT

	stop = false;
}

void CFindFiles::DoDataExchange(CDataExchange* pDX)

{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindFiles)
	DDX_Control(pDX, IDC_COMBO4, m_com4);
	DDX_Control(pDX, IDC_COMBO3, m_com3);
	DDX_Control(pDX, IDC_LOGWIN, m_logwin);
	DDX_Control(pDX, IDC_EDIT2, m_lab);
	DDX_Control(pDX, IDC_COMBO1, m_com1);
	DDX_CBString(pDX, IDC_COMBO1, m_comstr1);
	DDX_CBString(pDX, IDC_COMBO4, m_comstr4);
	DDX_CBString(pDX, IDC_COMBO3, m_comstr3);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFindFiles, CDialog)
	//{{AFX_MSG_MAP(CFindFiles)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP

	ON_MESSAGE( WM_LOGDBL, LogDblClick )

END_MESSAGE_MAP()


//////////////////////////////////////////////////////////////////////////
//

void	CFindFiles::LogDblClick(unsigned int wParam, long lParam)

{
	CLogWin *logwin = (CLogWin *)lParam;

	ASSERT(logwin->magic == LOGWIN_MAGIC);

	CString laststr = (const char *)wParam;

	//P2N("CFindFiles::LogDblClick %s\r\n", (const char *)wParam);

	// Find line number:
	CString num, str;
	int idx1 = laststr.Find('[');
	int idx2 = laststr.Find(']');

	if(idx1 >= 0 && idx2 >= 0)
		{
		num = logwin->laststr.Mid(idx1 + 1, idx2 - (idx1 + 1));
		//P2N("Line number '%s'\r\n", num);
		}

	// Find full name:
	int prog = logwin->lastoffset;
	while(true)
		{
		str = logwin->strlist.GetAt(logwin->strlist.FindIndex(prog));

		if(str[0] != ' ')
			break;

		if(prog-- == 0)
			break;
		}

	str.TrimRight();

	// -------------------------------------------------------------------
	// Control docs

	//P2N("CFindFiles::LogDblClick LineNo: '%d' Filename = '%s'\r\n",  atoi(num), str);

	CWedApp     *app = (CWedApp*)AfxGetApp();
    CWedDoc		*doc = NULL;
	POSITION	pos = app->pDocTemplate->GetFirstDocPosition();
	
    int found = 0;
    while(pos)
        {
        doc = (CWedDoc*)app->pDocTemplate->GetNextDoc(pos);
		ASSERT(doc);

		CString docname = doc->GetPathName();
		if(docname == str)
			{
			found = true; break;
			}
		}

	if(!found)
		{
		doc = (CWedDoc *)AfxGetApp()->OpenDocumentFile(str);
		ASSERT(doc);
		}

	POSITION pos2 = doc->GetFirstViewPosition();
	CWedView *cv = (CWedView*)doc->GetNextView(pos2);

	if(num != "")
		{
		int idx3;
		cv->row =  atoi(num) - 1;
		CStringEx str = doc->strlist.GetLine(cv->row);

		CRegExp regex;
		
		if(nocase == REGEX_SRC)
			regex.RegComp(m_comstr1);
	
		if(nocase == NOCASE_SRC)
			idx3 = str.FindNoCase(m_comstr1);
		else if(nocase == REGEX_SRC)
			idx3 = regex.RegFind(m_comstr1);			
		else
			idx3 = str.Find(m_comstr1);
	
		if(idx3 >= 0)
			cv->col = idx3;

		cv->SyncCaret(2);
		}

	cv->GetParent()->BringWindowToTop();
	cv->SetFocus();
}

/////////////////////////////////////////////////////////////////////////////
// CFindFiles message handlers

BOOL CFindFiles::OnInitDialog() 

{
	//P2N("CFindFiles::OnInitDialog\r\n");

	CDialog::OnInitDialog();
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFindFiles::OnOK() 

{
	//P2N("CFindFiles::OnOK\r\n");

	SaveData();

	CDialog::OnOK();
}

void CFindFiles::OnButton1() 

{
	CDlgGetPath gp;

	TCHAR szPath[_MAX_PATH];
	VERIFY( _getdcwd( _getdrive(), szPath, _MAX_PATH ) != NULL );
	
	gp.SetPath(szPath);

	if(gp.DoModal() == IDOK)
		{	
		UpdateData(true);
		m_comstr4 = gp.GetPath();
		UpdateData(false);
		}
}

void CFindFiles::OnButton3() 

{
	UpdateData();

	// Set up param vars
	found = dcounter = fcounter = 0;
	fonly = ((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck();	

	if(((CButton*)GetDlgItem(IDC_RADIO4))->GetCheck())	
		nocase = NOCASE_SRC;
	else if(((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck())	
		nocase = REGEX_SRC;
	else
		nocase = NORMAL_SRC;

	recur = ((CButton*)GetDlgItem(IDC_CHECK3))->GetCheck();

	stop = false;

	if(m_comstr1 == "")
		{
		AfxMessageBox("Please specify a string to search for.");
		return;
		}

	m_logwin.Clear();

	TCHAR szPath[_MAX_PATH];
	VERIFY( _getdcwd( _getdrive(), szPath, _MAX_PATH ) != NULL );

	ScanRecurse(m_comstr4 + "\\", m_comstr3);
	
	_chdir(szPath);

	CString tmp; tmp.Format("Scanned %d dirs %d files, found %d hits.", 
				dcounter, fcounter, found);
	m_lab.SetWindowText(tmp);

	
	m_logwin.SetFocus();
}

int CFindFiles::ScanRecurse(const char *src, const char *wild)

{
	//P2N("CFindFiles::ScanRecurse '%s' '%s'\r\n", src, wild);

	if(stop)
		return 0;

	if(strlen(wild) == 0)
		wild  = "*.cpp;*.h";

	_chdir(src);

	// Parse into components, reassemble
	CString buffer(src), drive, dir, fname, ext;
	SplitPath( buffer, drive, dir, fname, ext);

	//P2N("Recursing to dir %s\r\n", drive + dir);

	CString sdir(drive + dir);
	ShortenPath(sdir, 44);
	
	// Time for dir refresh?
	unsigned int iclock = clock();
	if(iclock > oldc + CLOCKS_PER_SEC / 4)
		{
		//P2N("Clock %u cps: %u\r\n", iclock, CLOCKS_PER_SEC);
		oldc = iclock;
		m_lab.SetWindowText("Scan Dir:  " + sdir);
		}
		
	// Time for window taskbar text refresh?
	
	SYSTEMTIME SystemTime;
	GetSystemTime(&SystemTime);
	if(abs(SystemTime.wSecond - old.wSecond) > 1)
		{
		old.wSecond = SystemTime.wSecond;		
		//SetWindowText(sdir);
		}

	struct _finddata_t c_file;
    long hFile;

    if( (hFile = _findfirst(drive + dir + "*.*", &c_file )) == -1L )
		{
		goto endd2;
		}
	else 
		{
		while( _findnext( hFile, &c_file ) == 0 )
			{
			CString fff(c_file.name);

			CString nnn = drive  + dir  + fff;
			//CString ttt = drive2 + dir2 + fff;

			CString drive3, dir3, fname3, ext3;
			SplitPath( nnn, drive3, dir3, fname3, ext3);

			if(fff.GetAt(0) == '.')
				{
				continue;
				}
		
			else if(IsDir(nnn))
				{
				// Do not descend on recycle bin
				if(nnn.Find("\\RECYCLER\\", 2 ) >= 0)
					{
					//P2N("Not copying %s %x\r\n", nnn, GetFileAttributes(nnn));
					}
				else
					{
					dcounter++;

					if(recur)
						ScanRecurse(nnn + "\\", wild);					
					}
				//continue;
				}
			else
				{
				int attrib = GetFileAttributes(nnn);
				if(attrib  & FILE_ATTRIBUTE_SYSTEM)
					{
					//P2N("Not copying sys file %s %x\r\n", nnn, GetFileAttributes(nnn));
					}
				if(attrib  & FILE_ATTRIBUTE_TEMPORARY)
					{
					//P2N("Not copying tmp file %s %x\r\n", nnn, GetFileAttributes(nnn));
					}
				else
					{
					// is it a match?
					if(wildcmparr(fff, wild))
						{
						//P2N("Scanning %s\r\n", nnn);
						ScanFile(nnn,  m_comstr1);
						fcounter++;
						}
					}
				}
			YieldToWinEx();

			if(stop)
				break;
			}		
		}

	_findclose( hFile );

endd2:

	return 0; 
}

void CFindFiles::OnButton2() 

{
	stop = true;	
	YieldToWinEx();
}

//////////////////////////////////////////////////////////////////////////

void CFindFiles::ScanFile(const char *fname, const char *needle) 

{
	// Parse filename into components

	int first = 0;
	CString buffer(fname), drive, dir, name, ext;
	SplitPath( buffer, drive, dir, name, ext);

	YieldToWinEx();

	CRegExp regex;

	if(nocase == REGEX_SRC)
		regex.RegComp(needle);
					
	CFile cf;
    if( cf.Open(fname, CFile::modeRead ))
        {
		int linenum = 0, ret;
		CString tmp;			
		CStringEx str;

        CArchive ar( &cf, CArchive::load);

        while(TRUE)
            {
			if(stop)
				break;

            if(!ar.ReadString(str))
                break;
	
			if(linenum++ % 100 == 0)
				YieldToWinEx();

			if(nocase == NOCASE_SRC)
				ret = str.FindNoCase(needle);
			else if(nocase == REGEX_SRC)
				ret = regex.RegFind(str);			
			else
				ret = str.Find(needle);

			if(ret >= 0)
				{
				if(!first)
					{
					first = true;
					m_logwin.AddString(fname);
					
					if(!fonly)
						m_logwin.AddString("\r\n");					
					}
				found++;
				if(!fonly)
					{
					tmp.Format(" %s%s [%d]\t%s\r\n", name, ext, linenum, str);
					m_logwin.AddString(tmp);			
					}
				}
            }
		if(fonly && first)
			{
			tmp.Format("  %d lines match\r\n", found);
			m_logwin.AddString(tmp);			
			}
        }
}



void CFindFiles::OnCancel()
{
	//P2N("CFindFiles::OnCancel\r\n");

	SaveData();

	CDialog::OnCancel();
}

void CFindFiles::SaveData()

{
	UpdateData();
	
	 // Write it out
	PersistCombo(strConfig, "RecentFind%d", &m_com1);
	PersistCombo(strConfig, "RecentExt%d",  &m_com3);
	PersistCombo(strConfig, "RecentDir%d",  &m_com4);
}

// Save combo box contents to registry.
//
//	const char *reg,  registry to save at
//	const char *templ, 
//	CComboBox *box
//

void CFindFiles::PersistCombo(const char *reg, const char *templ, CComboBox *box)

{
	// Write it out
	CString tmp; tmp.Format(templ, 0);			

	box->ResetContent();

	for(int loop6 = 0; loop6 < MAXRECENT; loop6++)
		{	
		CString str;

		tmp.Format(templ, loop6);	
		
		if(loop6 == 0)
			{
			box->GetWindowText(str);	
			}
		else
			{			
			// Listbox/CString asserts if invalid index passed,
			// get strlen first
			if(box->GetLBTextLen(loop6) > 0)
				box->GetLBText(loop6, str);
			}		
		if(str != "")
			{
			AfxGetApp()->WriteProfileString(reg, tmp, str);
			}
		}
}

void CFindFiles::LoadToCombo(const char *reg, const char *templ, CComboBox *box)

{
	for(int loop7 = 0; loop7 < MAXRECENT; loop7++)
		{
		CString tmp; tmp.Format(templ, loop7);
		CString str = AfxGetApp()->GetProfileString(strConfig, tmp, "");

		if(str == "")
			break;

		box->AddString(str);	
		}
}

void CFindFiles::OnShowWindow(BOOL bShow, UINT nStatus) 

{
	//P2N("CFindFiles::OnShowWindow %d\r\n", bShow);

	CDialog::OnShowWindow(bShow, nStatus);
	
	if(bShow)
		{
		LoadToCombo(strConfig, "RecentFind%d", &m_com1);
		LoadToCombo(strConfig, "RecentExt%d",  &m_com3);
		LoadToCombo(strConfig, "RecentDir%d",  &m_com4);

		if(m_com3.GetCount() == 0)
			{
			m_com3.AddString("*.cpp;*.h");
			m_com3.AddString("*.txt");
			m_com3.AddString("*.php");
			m_com3.AddString("*.py");
			m_com3.AddString("*.c;*.h");
			m_com3.AddString("*.pl");
			m_com3.AddString("*.sh");
			m_com3.AddString("*.*");
			}

		m_comstr3 = "*.cpp;*.h";
		UpdateData(false);

		((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(true);
		((CButton*)GetDlgItem(IDC_CHECK3))->SetCheck(true);

		TCHAR szPath[_MAX_PATH];
		VERIFY( _getdcwd( _getdrive(), szPath, _MAX_PATH ) != NULL );
		
		m_comstr4 = szPath;
		UpdateData(false);
		}
}
