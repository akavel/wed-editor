
/* =====[ weddoc.cpp ]========================================== 
                                                                             
   Description:     The wed project, implementation of the weddoc.cpp                
                                                                             
                    Defines the behavior for the application.          
                                                                             
   Compiled:        MS-VC 6.00                                               
                                                                             
   Notes:           <Empty Notes>                                            
                                                                             
   Revisions:                                                                
                                                                             
      REV     DATE        BY            DESCRIPTION                       
      ----  --------  -----------  ----------------------------   
      0.00  1/6/2009  Peter Glen   Initial version.                         
                                                                             
   ======================================================================= */

/////////////////////////////////////////////////////////////////////////////
// wedDoc.cpp : implementation of the CWedDoc class
//

#include "stdafx.h"

#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

#include "wed.h"
#include "StrList.h"
#include "wedDoc.h"
#include "wedView.h"
#include "mxpad.h"
#include "editor.h"
#include "io.h"
#include "misc.h"

/////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

#define		DETECTSIZE		1024
#define		MAX_AUTO_LINES	10000

/////////////////////////////////////////////////////////////////////////////
// Get single line comment delimiter and function regex

const char	*comms[] =

	{
	".PHP",		"//",	"^function",
	".SH",		"#",	"^function",
	".PL",		"#",	"^sub",
	".CGI",		"#",	"^sub",
	".PY",		"#",	"^def",
	".ASM",		";",	"^function",
	".BAT",		"rem",	"^function",
	".C",		"//",	"^([a-z]|[A-Z]).*\\(.*\\)",
	".CPP",		"//",	"^([a-z]|[A-Z]).*\\(.*\\)",
	".JAVA",	"//",	"^([a-z]|[A-Z]).*\\(.*\\)",
	".SRC",		";",	"^([a-z]|[A-Z]).*\\(.*\\)",
	NULL,	  	NULL,  NULL
	} ;

/////////////////////////////////////////////////////////////////////////////
// CWedDoc

IMPLEMENT_DYNCREATE(CWedDoc, CDocument)

BEGIN_MESSAGE_MAP(CWedDoc, CDocument)
    //{{AFX_MSG_MAP(CWedDoc)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
    ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
    ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

// Declare the variables needed
#ifdef _DEBUG
    static CMemoryState oldMemState, newMemState, diffMemState;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWedDoc construction

CWedDoc::CWedDoc()

{
#ifdef _DEBUG
    oldMemState.Checkpoint();
#endif

	inited = notfullundo = 	0;
	unix = 	readonly = 0;
	origlines = undopos = undoorig = 0;
	spaceify = 0;

	// Historical default
	maxcol = 80;
	comment = "//";

	memset(&docstat, 0 , sizeof(docstat));
	memset(&docstat2, 0 , sizeof(docstat2));
}

/////////////////////////////////////////////////////////////////////////////
// CWedDoc destruction

CWedDoc::~CWedDoc()

{

#ifdef _DEBUG
	//oldMemState.DumpAllObjectsSince();
    //newMemState.Checkpoint();
    if( diffMemState.Difference( oldMemState, newMemState ) )
    	{
		//P2N("WedDoc Memory leaked!\r\n");
        //TRACE( "Memory leaked!\n" );
    	}
#endif
}

/////////////////////////////////////////////////////////////////////////////
// OnNewDocument

BOOL CWedDoc::OnNewDocument()

{
	P2N("CWedDoc::OnNewDocument()\r\n");

	if(GetNumOfDocs() > MAX_DOC_LIMIT)
		{
		AfxMessageBox("Too many open documents");
		return FALSE;
		}

	// Go get one
    if (!CDocument::OnNewDocument())
        return FALSE;

	CString num;
	// Find temporary name that is not an existing file
	while(TRUE)
		{
		num.Format("untitled%02d.txt", newcount++);
		if(access(num, 0))
			break;

		// Safety net
		if(newcount > 100)
			break;
		}
	SetPathName(num);
    SetModifiedFlag();
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// OnOpenDocument

BOOL CWedDoc::OnOpenDocument(LPCTSTR lpszPathName)

{
	BOOL retval = FALSE;

	if(GetNumOfDocs() > MAX_DOC_LIMIT)
		{
		AfxMessageBox("Too many open documents");
		return FALSE;
		}

	// For originial document properties
	_stat(lpszPathName, &docstat);  docstat2 = docstat;

	// Load as usual
	retval = CDocument::OnOpenDocument(lpszPathName);

  	//P2N("Opened document %s\r\n", lpszPathName);

	// Get the undo/redo
	LoadUndo(lpszPathName); LoadRedo(lpszPathName);

	// Used by IsDocModified()
	undoorig = undo.GetCount();
	//P2N("Undo orig = %d\r\n", undoorig);

	SaveBackup(lpszPathName);

	// Assign comment file
	GetComment(lpszPathName);

  	return(retval);
}


/////////////////////////////////////////////////////////////////////////////
// Override for displaying correct message
//

void CWedDoc::Serialize(CArchive& ar, const char *docname)

{
    CString 	num, str;
    CString 	filename = docname;

    PathToFname(filename);

    if (ar.IsStoring())
    	{
		// Writing
		CWaitCursor cursor;

        POSITION pos;
		pos = strlist.GetHeadPosition();
		origlines = 0;
        while(TRUE)
        	{
        	CString line;
			if(!(origlines % 100))
				{
				num.Format("Writing %s line %d", filename, origlines);
				message(num);
				}
			origlines++;
            if (!pos)
            	break;

            line = strlist.GetNext(pos);

            // Obey tab save option
			if(Tab2Space ||	spaceify)
				ExpandTabs(line);

            // Dispose space from EOL
			line.TrimRight();

            // Write out to file
            ar.WriteString(line);

            // Do end of line according to settings
			if(unix)
				ar.WriteString("\n");
			else
				ar.WriteString("\r\n");
        	}
		num.Format("Wrote %s", filename);  message(num);

		// If user decides to save, save undo/redo info as well
		SaveUndo(); SaveRedo();
    	}
    else
    	{
		// Reading
		CWaitCursor cursor;
		char buff[DETECTSIZE];

        strlist.RemoveAll();

		// Determine file type
		CFile* fp = ar.GetFile();
		int rlen = fp->Read(buff, DETECTSIZE);

		// File without a newline ---> default to DOS
		if(!strstr(buff, "\n"))
			unix = FALSE;
		else if (strstr(buff, "\r\n"))
			unix = FALSE;
		else
			unix = TRUE;

		// Take a wild guess for tabs
		if(!strstr(buff, "\t") && rlen > DETECTSIZE/2 )
			{
			spaceify = TRUE;
			}

		// Start over on file
		fp->Seek(0,CFile::begin);
		origlines = 0;

		// Load file
        while(TRUE)
        	{
            str = "";
			if(!(origlines % 100))
				{
				CString num;
				num.Format("Reading %s line %d", filename, origlines);
				message(num);
				}
			if(YieldToWinEx())
				{
				readonly = TRUE;
				AfxMessageBox("Aborted load, partial buffer is readonly.");
				break;
				}
			TRY
            	{
            	if(!ar.ReadString(str))
                	break;
            	}
	        	CATCH_ALL(ee); END_CATCH_ALL
			origlines++;
            TRY
            	{
            	strlist.AddTail(str);
            	}
            	CATCH(CMemoryException, ee)
            		{
                	//P2N("Memory exception\r\n");
					break;
            		}
            	END_CATCH
        	}

		// So unix can see an unlocked file
		// Let others see it
		// ReleaseFile(fp, 1);

        // Patch things up
        if( strlist.IsEmpty())
        	{
            //P2N("Empty file\r\n");
            strlist.AddTail("");
        	}
    }
}

/////////////////////////////////////////////////////////////////////////////
// CWedDoc serialization

void CWedDoc::Serialize(CArchive& ar)

{
    CString	 docname  = GetPathName();
    // Call overridden version
	Serialize(ar, docname);
}

/////////////////////////////////////////////////////////////////////////////
// CWedDoc diagnostics

#ifdef _DEBUG

void CWedDoc::AssertValid() const

{
    CDocument::AssertValid();
}

/////////////////////////////////////////////////////////////////////////////

void CWedDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Serialize undo

void CWedDoc::SaveUndo()

{
	CString droot; int hhh = HashString(GetPathName());
	droot.Format("%sdata\\%x.udo", dataroot, hhh);

	//P2N("Save Undo To: %s\r\n", droot);

 	CFile cf;
	if( cf.Open(droot, CFile::modeCreate | CFile::modeWrite ))
		{
		CArchive ar( &cf, CArchive::store);
		undo.Serialize(ar);;
		}
	else
		{
		//P2N(	"Cannot create undo file: %s\r\n", droot);
		}
}

/////////////////////////////////////////////////////////////////////////////
// Serialize redo

void CWedDoc::SaveRedo()
{
	CString droot; int hhh = HashString(GetPathName());
	droot.Format("%sdata\\%x.rdo", dataroot, hhh);

	//P2N("Save Redo To: %s\r\n", droot);

 	CFile cf;
	if( cf.Open(droot, CFile::modeCreate | CFile::modeWrite ))
		{
		CArchive ar( &cf, CArchive::store);
		redo.Serialize(ar);
		}
	else
		{
		//P2N("Cannot create redo file: %s\r\n", droot);
		}
}

/////////////////////////////////////////////////////////////////////////////
// Load Undo

void CWedDoc::LoadUndo(LPCTSTR lpszPathName)

{
	CString  droot; int hhh = HashString(lpszPathName);
	droot.Format("%sdata\\%x.udo", dataroot, hhh);

	//P2N("Load Undo from: %s\r\n", droot);

	CFile cf;
	if( cf.Open(droot, CFile::modeRead ))
		{
		CArchive ar( &cf, CArchive::load);
		undo.Serialize(ar);
		}
	else
		{
		//P2N("Cannot open undo file: %s\r\n", droot);
		}
}

/////////////////////////////////////////////////////////////////////////////
// Load redo

void CWedDoc::LoadRedo(LPCTSTR lpszPathName)

{
	CString  droot;  int hhh = HashString(lpszPathName);
	droot.Format("%sdata\\%x.rdo", dataroot, hhh);

	//P2N("Load Redo from: %s\r\n", droot);

	CFile cf;
	if( cf.Open(droot, CFile::modeRead ))
		{
		CArchive ar( &cf, CArchive::load);
		redo.Serialize(ar);
		}
	else
		{
		//P2N("Cannot open redo file: %s\r\n", droot);
		}
}

/////////////////////////////////////////////////////////////////////////////
// Save Document

BOOL CWedDoc::OnSaveDocument(LPCTSTR lpszPathName)

{
	if(readonly)
		{
		AfxMessageBox("Read only buffer, cannot save");
		return 1;
		}

	//P2N("SaveDocument '%s'\r\n", lpszPathName);
	int ret_val =  CDocument::OnSaveDocument(lpszPathName);

	// Update current stat info
	_stat(lpszPathName, &docstat2);

	// Get comment status
	GetComment(lpszPathName);

	return(ret_val);
}

/////////////////////////////////////////////////////////////////////////////
// Autosave

void CWedDoc::AutoSave()

{
    CString	 num;
    CString  docname = GetPathName();

	if(docname == "")
		{
		message ("Empty file name on AutoSave");
		return;
		}

    CString 	filename = GetPathName();
	PathToFname(filename);

	if(strlist.GetCount() > MAX_AUTO_LINES)
		{
		num.Format("File %s is too large for autosave ", filename);
		message(num);
		return;
		}
	CString droot;  int hhh = HashString(docname);
	droot.Format("%sdata\\%x.sav", dataroot, hhh);

	num.Format("Autosaving %s", filename);  message(num);

	//P2N("AutoSave %s %s\r\n", filename, droot);
	Sleep(300);

 	CFile cf;
	if(cf.Open(droot, CFile::modeCreate | CFile::modeWrite ))
		{
		CArchive ar(&cf, CArchive::store);
		Serialize(ar, droot);
		SetModifiedFlag(FALSE);
		}
	else
		{
		num.Format("Could not autosave %s ", filename);
		message(num);
		//P2N("Cannot create autosave file: %s\r\n", droot);
		}
}

/////////////////////////////////////////////////////////////////////////////
// Save Backup copy of the file

void CWedDoc::SaveBackup(const char *docname)

{
	CString	 num, filename = docname;
    PathToFname(filename);

	if(access(docname, 0) < 0)
		{
		num.Format("File %s does not exist, did make auto backup ", filename);
		message(num);
		//AfxMessageBox(num);
		return;
		}

	// Save only if smaller then 2 Meg
	if(docstat.st_size > MAX_BACKUP)
		{
		num.Format("File is too large for auto backup ", filename);
		message(num);
		return;
		}

	// Truncate up tp the first backslash
	int idx; CString tfn(docname);

	idx = tfn.Find("\\\\");
	if(idx >= 0)
		{
		tfn = tfn.Right(tfn.GetLength() - (idx + 1) );
		}
	else
		{
		idx = tfn.Find('\\');
		if(idx >= 0)
			{
			tfn = tfn.Right(tfn.GetLength() - (idx) );
			}
		}

	CString fbackup;
	//int hhh = HashString(docname);

	fbackup.Format("%sbackup%s", dataroot, tfn);
	create_full_dir(fbackup);

	CString fbdir(fbackup);
	PathToDir(fbdir);
	fbdir += "history\\"; fbdir += filename;

	//P2N("Sent backup copy to: %s\r\n", fbackup);

	// See if backup file exists already
    struct _stat docstat_o, docstat_b;

	_stat(docname, &docstat_o);

	CTime ct(docstat_o.st_mtime);
	CString datestr = ct.Format(".%a_%b_%d_%Y--%H_%M");
	fbdir += datestr;

	//P2N("Sent backup history to: %s\r\n", fbdir);

	// If backup is less than ....
	if(_stat(fbackup, &docstat_b) >=0)
		{
		//P2N("Document %s m_time=%d BackupFile m_time=%d \r\n",
        //              docname, docstat_o.st_mtime,  docstat_b.st_mtime );

		//if((docstat_o.st_mtime -  docstat_b.st_mtime) > 10)
			{
			//P2N("***Backing up: %s\r\n", fbackup);
			create_full_dir(fbdir);
			rename(fbackup, fbdir);
			}
		}

 	CFile cf;
	if(cf.Open(fbackup, CFile::modeCreate | CFile::modeWrite ))
		{
		num.Format("Saving backup copy %s ", filename);
		message(num);
		CArchive ar(&cf, CArchive::store);
		Serialize(ar, fbackup);
		}
	else
		{
		num.Format("Could not create backup copy of %s ", filename);
		message(num);
		//P2N("Cannot create backup copy of: %s\r\n", droot);
		}
}

/////////////////////////////////////////////////////////////////////////////
// Count the number of documents

int	 CWedDoc::GetNumOfDocs()

{
    int cnt = 0;
    POSITION Pos =
        ((CWedApp*)AfxGetApp())->pDocTemplate->GetFirstDocPosition();
    for(;;)
        {
        if(!Pos)
            break;
        CWedDoc* doc = (CWedDoc*)
        	 ((CWedApp*)AfxGetApp())->pDocTemplate->GetNextDoc(Pos);
		cnt++;
        }
	return (cnt);
}

/////////////////////////////////////////////////////////////////////////////

int	 CWedDoc::GetComment(const char *fname)

{
	int loop = 0;
	CString name(fname), drive, dir, filename, ext;
	
	SplitPath(name,  drive, dir, filename, ext);
	ext.MakeUpper();

	comment = "//";

	while(TRUE)
		{
		if(!comms[loop])
			break;

		if(ext == comms[loop])
			{
			comment		= comms[loop+1];
			funcregex	= comms[loop+2]; 
			P2N("Got: '%s' '%s' '%s'\r\n", comms[loop], comms[loop+1], comms[loop+2]);
			break;
			}
		//P2N("Searching extension %s %s\r\n", str, comms[loop]);
		loop += 3;
	}
	return(0);
}


// EOF
