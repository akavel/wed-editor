//////////////////////////////////////////////////////////////////////
// wedView.cpp : 	implementation of the CWedView class
//

#include "stdafx.h"

#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include "io.h"

#include "wed.h"
#include "MainFrm.h"
#include "StrList.h"
#include "wedDoc.h"
#include "wedView.h"
#include "FileInfo.h"
#include "bufferlist.h"
#include "gotoline.h"
#include "page1.h"
#include "page2.h"
#include "setup.h"
#include "coco.h"
#include "oleComm.h"
#include "notepad.h"
#include "holdhead.h"
#include "editor.h"
#include "undo.h"
#include "diff.h"
#include "src.h"
#include "search.h"
#include "srcsel.h"
#include "mainfrm.h"
#include "stringex.h"
#include "RegEx.h"

coco co;
ColeComm m_ole;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CMainFrame* pMainFrame;
extern CWedApp theApp;

int tabs[10];
int tabstop = 4;
int backwrap;

int kblock = FALSE;

CStringList holding[10];
CStringList macros[10];

CString delim  = "<>,/:;{}[]() \t+-\"\'=";
CString wdelim = "-/{}[]() \t";

char  Mfilter[] =
"\
Macro Files (*.mac)\0*.mac\0\
All Files\0*.*\0\0\
";

char    Ffilter[] =
"\
All  files (*.*)\0*.*\0\
Source files (*.cpp)\0*.cpp\0\
Source files (*.c)\0*.c\0\
Source files (*.java)\0*.java\0\
Source files (*.class)\0*.class\0\
Header files (*.h)\0*.h\0\
Text files (*.txt)\0*.txt\0\
Definition files (*.def)\0*.def\0\
Resource files (*.rc)\0*.rc\0\
Make files (*.dsw; *.dsp; Makefile)\0*.dsw;*.dsp;Makefile\0\0\
";

int holdflag[10] = {0};
int newcount = 0;
int currhold = 0;
int currmac = 0;
int Tab2Space =  0;

int in_draw = FALSE;

static int play = FALSE;

// CWedView

IMPLEMENT_DYNCREATE(CWedView, CView)

BEGIN_MESSAGE_MAP(CWedView, CView)
    //{{AFX_MSG_MAP(CWedView)
    ON_WM_CHAR()
    ON_WM_KEYDOWN()
    ON_WM_KEYUP()
    ON_WM_SYSKEYDOWN()
    ON_WM_SYSCHAR()
    ON_WM_SYSKEYUP()
    ON_WM_SETFOCUS()
    ON_WM_CREATE()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONDBLCLK()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_WM_VSCROLL()
    ON_WM_SHOWWINDOW()
    ON_COMMAND(ID_VIEW_VIEWHEX, OnViewViewhex)
    ON_WM_HSCROLL()
    ON_COMMAND(ID_VIEW_FONTS, OnViewFonts)
    ON_WM_KILLFOCUS()
    ON_COMMAND(ID_VIEW_FOREGROUNDCOLOR, OnViewForegroundcolor)
    ON_COMMAND(ID_VIEW_BACKGROUNDCOLOR, OnViewBackgroundcolor)
    ON_COMMAND(ID_VIEW_HIGHLITEBACKGROUND, OnViewHighlitebackground)
    ON_COMMAND(ID_VIEW_COLOMNHIGHLITEBACKGROUND, OnViewColomnhighlitebackground)
    ON_COMMAND(ID_VIEW_SELECTPRINTERFONT, OnViewSelectprinterfont)
    ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
    ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
    ON_COMMAND(ID_VIEW_VIEWHOLDINGHEADS, OnViewViewholdingheads)
    ON_COMMAND(ID_WINDOW_MAXIMIZEMAIN, OnWindowMaximizemain)
    ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
    ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
    ON_WM_RBUTTONDOWN()
    ON_COMMAND(ID_OPERATIONS_SELECTLINE, OnOperationsSelectline)
    ON_COMMAND(ID_SEARCH_FIND, OnSearchFind)
    ON_COMMAND(ID_SEARCH_REPLACE, OnSearchReplace)
    ON_COMMAND(ID_VIEW_STOPDIFFING, OnViewStopdiffing)
    ON_COMMAND(ID_EDIT_RECORDMACRO, OnEditRecordmacro)
    ON_COMMAND(ID_EDIT_PLAYMACRO, OnEditPlaymacro)
    ON_COMMAND(ID_SEARCH_SELEXTHOLDING_BUFFER1, OnSearchSelextholdingBuffer1)
    ON_COMMAND(ID_SEARCH_SELEXTHOLDING_BUFFER2, OnSearchSelextholdingBuffer2)
    ON_COMMAND(ID_SEARCH_SELEXTHOLDING_BUFFER3, OnSearchSelextholdingBuffer3)
    ON_COMMAND(ID_SEARCH_SELEXTHOLDING_BUFFER4, OnSearchSelextholdingBuffer4)
    ON_COMMAND(ID_SEARCH_SELEXTHOLDING_BUFFER5, OnSearchSelextholdingBuffer5)
    ON_COMMAND(ID_SEARCH_SELEXTHOLDING_BUFFER6, OnSearchSelextholdingBuffer6)
    ON_COMMAND(ID_SEARCH_SELEXTHOLDING_BUFFER7, OnSearchSelextholdingBuffer7)
    ON_COMMAND(ID_SEARCH_SELEXTHOLDING_BUFFER8, OnSearchSelextholdingBuffer8)
    ON_COMMAND(ID_SEARCH_SELEXTHOLDING_BUFFER9, OnSearchSelextholdingBuffer9)
    ON_COMMAND(ID_SEARCH_SELEXTHOLDING_BUFFER10, OnSearchSelextholdingBuffer10)
    ON_COMMAND(ID_MOVE_NEXTCHARACTER, OnMoveNextcharacter)
    ON_COMMAND(ID_MOVE_PREVIOUSCHAR, OnMovePreviouschar)
    ON_COMMAND(ID_MOVE_NEXTLINE, OnMoveNextline)
    ON_COMMAND(ID_MOVE_PREVIOUSLINE, OnMovePreviousline)
    ON_COMMAND(ID_MOVE_PAGEDOWN, OnMovePagedown)
    ON_COMMAND(ID_MOVE_PAGEUP, OnMovePageup)
    ON_COMMAND(ID_MOVE_NEXTWORD, OnMoveNextword)
    ON_COMMAND(ID_MOVE_PREVIOUSEWORD, OnMovePreviouseword)
    ON_COMMAND(ID_MOVE_ENDOFWORD, OnMoveEndofword)
    ON_COMMAND(ID_MOVE_BEGINNINGOFWORD, OnMoveBeginningofword)
    ON_COMMAND(ID_MOVE_NEXTPARAGRAPH, OnMoveNextparagraph)
    ON_COMMAND(ID_MOVE_PREVIOUSEPARAGRAPH, OnMovePreviouseparagraph)
    ON_COMMAND(ID_MOVE_ENDOFLINE, OnMoveEndofline)
    ON_COMMAND(ID_MOVE_BEGINNINGOFLINE, OnMoveBeginningofline)
    ON_COMMAND(ID_MOVE_BEGINNINGOFFILE, OnMoveBeginningoffile)
    ON_COMMAND(ID_MOVE_ENDOFFILE, OnMoveEndoffile)
    ON_COMMAND(ID_EDIT_CUT, OnEditCut)
    ON_COMMAND(ID_EDIT_UPPERCASEWORD, OnEditUppercaseword)
    ON_COMMAND(ID_EDIT_LOWERCASEWORD, OnEditLowercaseword)
    ON_COMMAND(ID_EDIT_CAPITALIZEWORD, OnEditCapitalizeword)
    ON_COMMAND(ID_EDIT_STARTSELECTALTL, OnEditStartselectaltl)
    ON_COMMAND(ID_EDIT_STARTCOLUMNSELECTALTC, OnEditStartcolumnselectaltc)
    ON_COMMAND(ID_SELECT_CANCELSELECT, OnSelectCancelselect)
    ON_COMMAND(ID_SELECT_SELECTALL, OnSelectSelectall)
    ON_COMMAND(ID_EDIT_CUTTOHOLDING, OnEditCuttoholding)
    ON_COMMAND(ID_EDIT_COPYTOHOLDING, OnEditCopytoholding)
    ON_COMMAND(ID_EDIT_PASTEHOLDING, OnEditPasteholding)
    ON_COMMAND(ID_SEARCH_CANCELFIND, OnSearchCancelfind)
    ON_COMMAND(ID_MOVE_GOTOLINE, OnMoveGotoline)
    ON_COMMAND(ID_INSERT_INCREMENTEDNUMBER, OnInsertIncrementednumber)
    ON_COMMAND(ID_INSERT_SETINCREMNETSTARTVALUE, OnInsertSetincremnetstartvalue)
    ON_COMMAND(ID_MOVE_GOTOCOLUMN, OnMoveGotocolumn)
    ON_COMMAND(ID_SEARCH_FINDNEXT, OnSearchFindnext)
    ON_COMMAND(ID_SEARCH_FINDPREVIOUS, OnSearchFindprevious)
    ON_COMMAND(ID_SELECT_SELECTWORD, OnSelectSelectword)
    ON_COMMAND(ID_SELECT_SELECTPARAGRAPH, OnSelectSelectparagraph)
    ON_COMMAND(ID_VIEW_FILEPROPERTIES, OnViewFileproperties)
    ON_COMMAND(ID_INSERT_USER, OnInsertUser)
    ON_COMMAND(ID_EDIT_UPPERCASESELECTION, OnEditUppercaseselection)
    ON_COMMAND(ID_EDIT_LOWERCASESELECTION, OnEditLowercaseselection)
    ON_COMMAND(ID_INSERT_DATETIME_RFCSTANDARDDATE, OnInsertDatetimeRfcstandarddate)
    ON_COMMAND(ID_INSERT_DATETIME_MMDDYYHHMMSS, OnInsertDatetimeMmddyyhhmmss)
    ON_COMMAND(ID_INSERT_DATETIME_DDMMYYHHMMSS, OnInsertDatetimeDdmmyyhhmmss)
    ON_COMMAND(ID_INSERT_PAGEFEEDMARK, OnInsertPagefeedmark)
    ON_COMMAND(ID_INSERT_BYTE, OnInsertByte)
    ON_COMMAND(ID_INSERT_DATETIME_TIMEHHMMSS, OnInsertDatetimeTimehhmmss)
    ON_COMMAND(ID_INSERT_DATETIME_WEEKDAY, OnInsertDatetimeWeekday)
    ON_COMMAND(ID_INSERT_DATETIME_MONTHNAME, OnInsertDatetimeMonthname)
    ON_COMMAND(ID_INSERT_DATETIME_DATEFORMATTEDASLOCALE, OnInsertDatetimeDateformattedaslocale)
    ON_COMMAND(ID_INSERT_FUNCTION, OnInsertFunction)
    ON_COMMAND(ID_INSERT_FORLOOP, OnInsertForloop)
    ON_COMMAND(ID_INSERT_IFCONDITION, OnInsertIfcondition)
    ON_COMMAND(ID_SETTINGS_SETUPWED, OnSettingsSetupwed)
    ON_COMMAND(ID_EDIT_LOADMACRO, OnEditLoadmacro)
    ON_COMMAND(ID_EDIT_SAVEMACRO, OnEditSavemacro)
    ON_COMMAND(ID_VIEW_COCOCODECOLECTOR, OnViewCococodecolector)
    ON_COMMAND(ID_COMPILE_MAKE, OnCompileMake)
    ON_COMMAND(ID_COMPILE_EXECUTEDEVSTUDIOPROJECT, OnCompileExecutedevstudioproject)
    ON_COMMAND(ID_FILE_SAVEALL, OnFileSaveall)
    ON_COMMAND(ID_VIEW_VIEWMACROHEADS, OnViewViewmacroheads)
    ON_COMMAND(ID_SELECT_MARKBLOCK, OnSelectMarkblock)
    ON_COMMAND(ID_MOVE_ENDOFPAGE, OnMoveEndofpage)
    ON_COMMAND(ID_MOVE_BEGINNINGOFPAGE, OnMoveBeginningofpage)
    ON_COMMAND(ID_WINDOWS_NEXTBUFFER, OnWindowsNextbuffer)
    ON_COMMAND(ID_VIEW_FULLSCREEN, OnViewFullscreen)
    ON_COMMAND(ID_FILE_MULTIOPEN, OnFileMultiopen)
    ON_COMMAND(ID_SETTINGS_TOGGLESCROLLBARS, OnSettingsTogglescrollbars)
    ON_COMMAND(ID_SETTINGS_REVERSEIT, OnSettingsReverseit)
    ON_COMMAND(ID_MACRO_ANIMATEMACRO, OnMacroAnimatemacro)
    ON_COMMAND(ID_DIFF_DIFFONE,   OnDiffDiffone)
    ON_COMMAND(ID_DIFF_DIFFTWO,   OnDiffDifftwo)
    ON_COMMAND(ID_DIFF_DIFFTHREE, OnDiffDiffthree)
    ON_COMMAND(ID_DIFF_DIFFFOUR,  OnDiffDifffour)
    ON_COMMAND(ID_DIFF_DIFFFIVE,  OnDiffDiffive)
    ON_COMMAND(ID_EDIT_CLEANNONASCII, OnEditCleannonascii)
    ON_COMMAND(ID_EDIT_WRAPTOWINDOW, OnEditWraptowindow)
    ON_COMMAND(ID_EDIT_WEEDEMPTYLINES, OnEditWeedemptylines)
    ON_COMMAND(ID_INSERT_DELETEATCURSOR, OnInsertDeleteatcursor)
    ON_COMMAND(ID_INSERT_DELETEBEFORECURSOR, OnInsertDeletebeforecursor)
    ON_COMMAND(ID_INSERT_DELETELINE, OnInsertDeleteline)
    ON_COMMAND(ID_INSERT_DELETETILLENDOFLINE, OnInsertDeletetillendofline)
    ON_COMMAND(ID_INSERT_C_SWITCHCASE, OnInsertCSwitchcase)
    ON_COMMAND(ID_INSERT_C_TEMPLATE, OnInsertCTemplate)
    ON_COMMAND(ID_INSERT_JAVA_TEMPLATE, OnInsertJavaTemplate)
    ON_COMMAND(ID_SETTINGS_SEARCHHIGHLITECOLORFG, OnSettingsSearchhighlitecolorfg)
    ON_COMMAND(ID_SETTINGS_COMMENTHIGHLITECOLOR, OnSettingsCommenthighlitecolor)
    ON_COMMAND(ID_VIEW_GOTONEXTDIFFERENCE, OnViewGotonextdifference)
    ON_COMMAND(ID_VIEW_GOTOPREVIOUSDIFFERENCE, OnViewGotopreviousdifference)
    ON_COMMAND(ID_SETTINGS_DIFFADDCOLOR, OnSettingsDiffaddcolor)
    ON_COMMAND(ID_SETTINGS_DIFFCHANGEDCOLOR, OnSettingsDiffchangedcolor)
    ON_COMMAND(ID_SETTINGS_DIFFDELCOLOR, OnSettingsDiffdelcolor)
    ON_COMMAND(ID_VIEW_FILEBUFERS, OnViewFilebufers)
    ON_WM_MOVE()
    ON_WM_SETCURSOR()
    ON_WM_SIZE()
    ON_COMMAND(ID_EDIT_APPENDTOHOLDING, OnEditAppendtoholding)
    ON_COMMAND(ID_SEARCH_HITEDITMODE, OnSearchHiteditmode)
    ON_COMMAND(ID_MACRO_SELECTRECORDHOLDING_BUFFER10, OnMacroSelectrecordholdingBuffer10)
    ON_COMMAND(ID_EDIT_SELECTRECORDBUFFER_BUFFER1, OnEditSelectrecordbufferBuffer1)
    ON_COMMAND(ID_MACRO_SELECTRECORDHOLDING_BUFFER1, OnMacroSelectrecordholdingBuffer1)
    ON_COMMAND(ID_MACRO_SELECTRECORDHOLDING_BUFFER3, OnMacroSelectrecordholdingBuffer3)
    ON_COMMAND(ID_MACRO_SELECTRECORDHOLDING_BUFFER4, OnMacroSelectrecordholdingBuffer4)
    ON_COMMAND(ID_MACRO_SELECTRECORDHOLDING_BUFFER5, OnMacroSelectrecordholdingBuffer5)
    ON_COMMAND(ID_MACRO_SELECTRECORDHOLDING_BUFFER6, OnMacroSelectrecordholdingBuffer6)
    ON_COMMAND(ID_MACRO_SELECTRECORDHOLDING_BUFFER7, OnMacroSelectrecordholdingBuffer7)
    ON_COMMAND(ID_MACRO_SELECTRECORDHOLDING_BUFFER8, OnMacroSelectrecordholdingBuffer8)
    ON_COMMAND(ID_MACRO_SELECTRECORDHOLDING_BUFFER9, OnMacroSelectrecordholdingBuffer9)
    ON_COMMAND(ID_WINDOWS_MAXIMIZECURRENT, OnWindowsMaximizecurrent)
    ON_WM_DROPFILES()
    ON_COMMAND(ID_INSERT_BASIC_FORLOOP, OnInsertBasicForloop)
    ON_COMMAND(ID_INSERT_BASIC_IF, OnInsertBasicIf)
    ON_COMMAND(ID_INSERT_BASIC_SELECTCASE, OnInsertBasicSelectcase)
    ON_COMMAND(ID_INSERT_BASIC_FUNCTION, OnInsertBasicFunction)
    ON_COMMAND(ID_INSERT_JAVA_PRIVATEMETHOD, OnInsertJavaPrivatemethod)
    ON_COMMAND(ID_ADVANCED_LOCKKEYBOARD, OnAdvancedLockkeyboard)
    ON_UPDATE_COMMAND_UI(ID_ADVANCED_LOCKKEYBOARD, OnUpdateAdvancedLockkeyboard)
    ON_UPDATE_COMMAND_UI(ID_SEARCH_HITEDITMODE, OnUpdateSearchHiteditmode)
    ON_UPDATE_COMMAND_UI(ID_VIEW_VIEWHEX, OnUpdateViewViewhex)
    ON_COMMAND(ID_SETTINGS_ALLOWBACKSPACETOWRAPLINES, OnSettingsAllowbackspacetowraplines)
    ON_UPDATE_COMMAND_UI(ID_SETTINGS_ALLOWBACKSPACETOWRAPLINES, OnUpdateSettingsAllowbackspacetowraplines)
    ON_COMMAND(ID_SETTINGS_SAVETABSASSPACES, OnSettingsSavetabsasspaces)
    ON_UPDATE_COMMAND_UI(ID_SETTINGS_SAVETABSASSPACES, OnUpdateSettingsSavetabsasspaces)
    ON_COMMAND(ID_INSERT_DATETIME_BORDERSAFEDATE, OnInsertDatetimeBordersafedate)
    ON_COMMAND(ID_INSERT_TEMPLATEONE, OnInsertTemplateone)
    ON_COMMAND(ID_INSERT_TEMPLATETWO, OnInsertTemplatetwo)
    ON_COMMAND(ID_INSERT_TEMPLATETHREE, OnInsertTemplatethree)
    ON_COMMAND(ID_ADVANCED_SPELLCHECK, OnAdvancedSpellcheck)
    ON_COMMAND(ID_ADVANCED_COMMENTADSTRINGSPELLCHECK, OnAdvancedCommentadstringspellcheck)
	ON_COMMAND(ID_MOVE_NEXTLONGLINE, OnMoveNextlongline)
	ON_COMMAND(ID_MOVE_MOVEPREVIOUSLONGLINE, OnMoveMovepreviouslongline)
	ON_COMMAND(ID_SETTINGS_LONGLINECOLORFG, OnSettingsLonglinecolorfg)
    ON_WM_TIMER()
    ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_DIRECT, OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_FILE_MULTIOPENDEST, OnFileMultiopendest)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

// Declare the variables needed
#ifdef _DEBUG
    static CMemoryState oldMemState, newMemState, diffMemState;
#endif


// CWedView construction/destruction

CWedView::CWedView()

{

#ifdef _DEBUG
    oldMemState.Checkpoint();
#endif


    row = col = srow = scol = 0;
    soh = eoh =  soch = eoch = -1;

    AllowShighlite  = 0;
    diffchange      = FALSE;
    init_search     = 0;

    diff        = 0;
    hex         = 0;
    highlite    = 0;
    record      = 0;
    drag        = 0;
    mouse       = 0;
    scrolldiv   = 1;
    m_busy      = 0;
    shift       = 0;
    control     = 0;
    alt         = 0;
    hitmode     = 0;
}

//////////////////////////////////////////////////////////////////////
// ~CWedView

CWedView::~CWedView()

{
    currentedit = NULL;

#ifdef _DEBUG
    newMemState.Checkpoint();
    if( diffMemState.Difference( oldMemState, newMemState ) )
    {
        //PrintToNotepad("WedView Memory leaked!\r\n");
        TRACE( "Memory leaked!\n" );
    }
#endif
}

//////////////////////////////////////////////////////////////////////
// CWedView drawing

void CWedView::OnDraw(CDC* pDC)

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);

    int xx, yy, loop, lim;
    CString str;
    CFont *oldfont;
    TEXTMETRIC tm;
    COLORREF oldcr, oldbk, sbgcol, sfgcol;

    oldcr = pDC->GetTextColor();  oldbk = pDC->GetBkColor();

    // Signal to others we are drawing
    in_draw = TRUE;

    // Make logical highlite
    int lsoh, leoh;
    if(soh < eoh)
        {
        lsoh = soh; leoh = eoh;
        }
    else
        {
        leoh = soh; lsoh = eoh;
        }

    // Make logical colomn highlite
    int lsoch, leoch;
    if(soch < eoch)
        {
        lsoch = soch; leoch = eoch+1;
        }
    else
        {
        leoch = soch+1; lsoch = eoch;
        }

    oldfont = pDC->SelectObject( &ff );
    pDC->GetTextMetrics(&tm);

    // Global for the cursor functions:
    fflf.lfWidth  =  tm.tmAveCharWidth;
    fflf.lfHeight =  tm.tmHeight;
    tabs[0] =  tm.tmAveCharWidth * tabstop;

    RECT rec, rec2;
    GetClientRect(&rec2);
    pDC->GetClipBox(&rec);

    pDC->SetTextColor(fgcol);
    pDC->SetBkColor(bgcol);

    int height = rec.bottom - rec.top;
    int fullheight = rec2.bottom - rec2.top;

    // remainder is just incremented
    int fullwidth  = (rec2.right - rec2.left)/ tm.tmAveCharWidth + 1;
    xx   = 0;

    //PrintToNotepad("lfwidth2: %d lfheight2: %d fullwith: %d\r\n",
    //                      fflf.lfWidth, fflf.lfHeight, fullwidth);

    // Figure out where to update
    loop = rec.top / tm.tmHeight;
    yy   = loop  * tm.tmHeight;         // Start at line boundary

    lim  = rec.bottom / tm.tmHeight;
    if(rec.bottom  % tm.tmHeight)       // Carry over
        lim++;

    loop += srow;                       // Adjust for relative pos
    lim  += srow;

    // Adjust for coordinates shift
    if(lsoch != -1)
        {
        lsoch -= scol;
        leoch -= scol;
        }
    //PrintToNotepad("Start draw: lim = %d loop = %d srow = %d\r\n",
    //                    lim, loop, srow);

    lim = min(lim, pDoc->strlist.GetCount()+1);

    int fulldiff   =  fullheight/tm.tmHeight  - (lim-loop);
    if(fullheight % tm.tmHeight)
        fulldiff++;

    for( ; loop < lim; loop++)
        {
        int startp = 0, endp = 0;
        int split = FALSE;

        str = pDoc->strlist.GetLine(loop);

        // Adjust max col length for scroll
        if(pDoc->maxcol < str.GetLength())
            pDoc->maxcol = str.GetLength();

        // Long line colors
        if(str.GetLength() > 85)
            {
            sbgcol  = bgcol;
            sfgcol  = clng;
        	pDC->SetTextColor(clng);
            }
       	else
       		{
            sbgcol  = bgcol;
            sfgcol  = fgcol;
		    pDC->SetTextColor(fgcol);
       		}

        // Pre-render tabs
        if(!hex)
            ExpandTabs(str);

        // Adjust for relative horizontal pos
        if(scol)
            str = str.Right(str.GetLength() - scol);

        // Padd string till eol
        if(!hex)
            {
            CString padd(' ', fullwidth - str.GetLength());
            str +=padd;
            }

        // Comment colors
        if(!hex)
        	{
        	int commx = str.Find(pDoc->comment);
        	if(commx != -1)
        	    {
        	 	//pDC->SetTextColor(comm);
        	    split = TRUE;
        	    startp  = commx;
        	    endp    = str.GetLength();

        	    sbgcol  = bgcol;
        	    sfgcol  = comm;
        	    }
			}
        // Search highlite
        if(AllowShighlite)
            {
             int offs = min(pDoc->ssel.lineb.GetSize()-1, loop);
             if(!pDoc->ssel.lineb.GetAt(offs))
                {
                // Ignore lines not in search hit
                 pDC->SetTextColor(fgcol);
                sfgcol  = fgcol;
                if(hitmode)
                    {
                    lim = pDoc->strlist.GetCount()+1;
                    continue;
                    }
                }
             else
                {
                // Color whole line
                 pDC->SetTextColor(srcc);
                sfgcol  = srcc;
                }
            }
        else
            {
            // Cancel hit mode too
            hitmode = 0;
            }

        // Select Highlight
        if(loop >= lsoh &&  lsoh != -1)
            {
            pDC->SetBkColor(selcol);
            sbgcol  = selcol;

            if(lsoch != -1)
                {
                split = TRUE;
                startp  = lsoch;
                endp    = leoch;
                sbgcol  = cselcol;
                sfgcol  = fgcol;
                }
            }
        if(loop > leoh &&  leoh != -1)
            {
            pDC->SetBkColor(bgcol);
            split = FALSE;
            }

        // Do diff coloring
        if(diff)
            {
            int difflag = diffa.GetAt( min(loop, diffa.GetSize()-1) );
            switch(difflag)
                {
                case DIFF_ADD:
                    pDC->SetTextColor(cadd); sfgcol = cadd;
                    break;

                case DIFF_DEL:
                    pDC->SetTextColor(cdel); sfgcol = cdel;
                    break;

                case DIFF_CHG:
                    pDC->SetTextColor(cchg); sfgcol = cchg;
                    break;

                default:
                    pDC->SetTextColor(oldcr); sfgcol = oldcr;
                    break;
                }
        }

        // ---------------------------------------------

        if(split)
            {
            // Display a split colored string:
            CString ll, mm, rr;
            ll = str.Left(startp);
            mm = str.Mid(startp, endp - startp);
            rr = str.Right(str.GetLength() - endp);

            pDC->SetBkColor(bgcol);
            pDC->SetTextColor(fgcol);
            //pDC->TabbedTextOut(xx, yy, ll, 1, tabs, 0);
            pDC->TextOut(xx, yy, ll);

            pDC->SetBkColor(sbgcol);
            pDC->SetTextColor(sfgcol);
            int offset =  ll.GetLength()* tm.tmAveCharWidth;
            //pDC->TabbedTextOut(xx + offset, yy, mm, 1, tabs, offset);
            pDC->TextOut(xx + offset, yy, mm);

            pDC->SetBkColor(bgcol);
            pDC->SetTextColor(fgcol);
            offset =  ll.GetLength()* tm.tmAveCharWidth +
                        mm.GetLength()* tm.tmAveCharWidth;

            //pDC->TabbedTextOut(xx +  offset,  yy, rr, 1, tabs, offset);
            pDC->TextOut(xx +  offset,  yy, rr);
            }

        // ---------------------------------------------

        else
            {
            if(hex)
                {
                CString num;
                int loop;
                CString padd(' ', fullwidth);
                pDC->TextOut(xx, yy, padd);

                for(loop = 0; loop < str.GetLength(); loop++)
                    {
                    num.Format( "%02x ", (unsigned char) str.GetAt(loop));
                    //pDC->TabbedTextOut(xx + tm.tmAveCharWidth * loop * 3, yy, num,
                    //            strlen(num), 1, tabs, 0);

                    pDC->TextOut(xx + tm.tmAveCharWidth * loop * 3, yy, num);
                    }
                }
            else
                {
                //pDC->TabbedTextOut(xx, yy, str, 1, tabs, 0);
                pDC->TextOut(xx, yy, str);
                }
            }
        // ---------------------------------------------
        yy+=tm.tmHeight;

        // Reached limit of client area, stop
        if(yy > fullheight && ! pDC->IsPrinting())
            break;
        }
    // Clear the rest of the screen (if needed)
    //PrintToNotepad("Full diff %d\r\n", fulldiff);

    if(hitmode)
        {
        fulldiff = (fullheight - yy)/tm.tmHeight;
        // remainder
        if(fullheight % tm.tmHeight)
            fulldiff++;
        }
    CString padd(' ', fullwidth);
    for(loop =  0; loop < fulldiff; loop++)
        {
        //pDC->TabbedTextOut(xx, yy, padd, 1, tabs, 0);
        pDC->TextOut(xx, yy, padd);
        yy+=tm.tmHeight;
        }

    // Restore stolen settings:
    pDC->SetTextColor(oldcr);  pDC->SetBkColor(oldbk);
    pDC->SelectObject(oldfont);
    SyncCaret();
    in_draw = FALSE;
}


//////////////////////////////////////////////////////////////////////
// OnPreparePrinting

BOOL CWedView::OnPreparePrinting(CPrintInfo* pInfo)

{
    // WinBug
    if(! pInfo)
        return TRUE;

    return DoPreparePrinting(pInfo);
}

//////////////////////////////////////////////////////////////////////
// OnBeginPrinting

void CWedView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)

{
      progress = 0;
      pages.SetSize(2);
}

//////////////////////////////////////////////////////////////////////
// OnEndPrinting

void CWedView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)

{
    pages.SetSize(2);
}

// CWedView diagnostics

#ifdef _DEBUG

//////////////////////////////////////////////////////////////////////
// AssertValid

void CWedView::AssertValid() const

{
    CView::AssertValid();
}

//////////////////////////////////////////////////////////////////////
// Dump

void CWedView::Dump(CDumpContext& dc) const

{
    CView::Dump(dc);
}

//////////////////////////////////////////////////////////////////////
// GetDocument

CWedDoc* CWedView::GetDocument() // non-debug version is inline

{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWedDoc)));
    return (CWedDoc*)m_pDocument;
}
#endif //_DEBUG

//////////////////////////////////////////////////////////////////////
// OnShowWindow

void CWedView::OnShowWindow(BOOL bShow, UINT nStatus)

{
    PrintToNotepad("OnShowWindow\r\n");
}

//////////////////////////////////////////////////////////////////////
// OnChar

void CWedView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    int wants = 0;
    CString str, lstr, rstr;

    PrintToNotepad("OnChar: %d (%c) Flags: %d\r\n", nChar, nChar, nFlags);

    if( kblock )
        return;

    if(record)
        {
        CString num;
        num.Format( "%d %d %d %d",  R_CHAR, nChar, nRepCnt, nFlags);
        //PrintToNotepad("Recording %s\r\n", num);
        macros[currmac].AddTail(num);
        }

    switch(nChar)
        {
        case VK_RETURN:
            {
            if(hitmode)
                {
                CancelHit();
                break;
                }
            // CR pressed:
            int indent = 0;
            if(row < pDoc->strlist.GetCount()-1)
                {
                // Split line, create new:
                str = pDoc->strlist.GetLine(row);

                int realindent, realcol, ontab;
                realindent = WalkStr(str, " \t");

                if(realindent == -1)
                    realindent = 0;

                UnTabbedPos(str, realindent, &indent, &ontab);
                TabbedPos(str, col, &realcol,    &ontab);

                lstr = str.Left(realcol);

                if(col >= indent)
                    rstr = str.Right(str.GetLength() - realcol);
                else
                    rstr = str.Right(str.GetLength() - realindent);

                SaveUndo(this, UNDO_MOD, row, col, str);
                SaveUndo(this, UNDO_ADD|UNDO_BLOCK, row+1, col, rstr);

                //PrintToNotepad("%s -- indent %d col: %d \r\n",
                //      str, indent, col);

                if(indent > 0)
                    {
                    CString pad;
                    pad = str.Left(realindent);
                    pad += rstr;  rstr = pad;
                    }
                pDoc->strlist.SetLine(row, lstr);
                pDoc->strlist.InsertLine(row + 1, rstr);
                pDoc->SetModifiedFlag();
                wants = 1;
            }
            // Move to next line:
            col = indent;
            row++;
            // Add new line if over the end
            if(row >= pDoc->strlist.GetCount())
                {
                pDoc->strlist.AddTail("");
                }
            if (wants)
                pDoc->UpdateAllViews(NULL);
            SyncCaret();
            }
            break;

    case VK_BACK:
        // Backspace:
        BackSpace();
        break;

    case VK_ESCAPE:
        Esc();
        break;

    case VK_TAB:
        // TAB:
        if(shift)
            {
            int step = col % 4;
            if(!step)  step = 4;
            col -= step;
            col = max(col, 0);
            SyncCaret();
            }
        else
            addchar(this, '\t');
        break;

    // --------------------------------------------------

    // ctrl-a
    case 'a'-'a' + 1:
        OnSelectSelectall();
        break;

    // ctrl-b
    case 'b'-'a' + 1:
        OnInsertCTemplate();
        break;

    // ctrl-d
    case 'd'-'a' + 1:
        OnViewGotonextdifference();
        break;

    // ctrl-e
    case 'e'-'a' + 1:
        AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_FILE_SAVE_AS, 0);
        break;

    // ctrl-f
    case 'f'-'a' + 1:
        SearchFile();
        break;

    // ctrl-g
    case 'g'-'a' + 1:
        message("Closing file");
        AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_FILE_CLOSE, 0);
        break;

    // ctrl-j
    case 'j'-'a' + 1:
        OnInsertJavaTemplate();
        break;

    // ctrl-k
    case 'k'-'a' + 1:
        OnViewViewhex();
        break;

    // ctrl-l
    case 'l'-'a' + 1:
        OnEditLowercaseword();
        break;

    // ctrl-q
    case 'q'-'a' + 1:
        message("Arrange windows");
        AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_WINDOW_CASCADE, 0);
        break;

    // ctrl-r
    case 'r'-'a' + 1:
        OnViewGotopreviousdifference();
        break;

    // ctrl-s
    case 's'-'a' + 1:
        if(!pDoc->IsModified())
            {
            message("Document not modified");
            break;
            }
        AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_FILE_SAVE, 0);
        break;

    // ctrl-u
    case 'u'-'a' + 1:
        OnEditUppercaseword();
        pDoc->SetModifiedFlag();
        break;

    // ctrl-w
    case 'w'-'a' + 1:
        OnEditCapitalizeword();
        pDoc->SetModifiedFlag();
        break;

    // ctrl-y
    case 'y'-'a' + 1:
        ReDo(this);
        break;

    // ---------------------------------------------

    // The default action is to add the character
    default:
        // filter gray+- with numlock off
        if((nChar == '+' || nChar == '-') &&
            nFlags > 32 &&  !GetKeyState(VK_NUMLOCK) )
            {
            //PrintToNotepad("GRAY+- NO NUM\r\n");
            }
        else
            addchar(this, nChar);
        break;
    }
    CView::OnChar(nChar, nRepCnt, nFlags);
}

//////////////////////////////////////////////////////////////////////
// OnKeyUp

void CWedView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);

    //PrintToNotepad("Keyup: %d (%c) Flags: %d\r\n", nChar, nChar, nFlags);

    if( kblock )
        {
        return;
        }
    if(record)
        {
        CString num;
        if(nChar != VK_F7 && nChar != VK_F8)
            {
            num.Format( "%d %d %d %d", R_UP, nChar, nRepCnt, nFlags);
            //PrintToNotepad("Recording: %s\r\n", num);
            macros[currmac].AddTail(num);
            }
        }
    switch(nChar)
        {
        case VK_SHIFT:
            //printtonotepad("shiFT UP ");
            shift = FALSE;
        break;

        case VK_CONTROL:
            //PrintToNotepad("CONTROL UP ");
            control = FALSE;
        break;
        }
    //PrintToNotepad("Keyup: %d (%c) Flags: %d\r\n", nChar, nChar, nFlags);
    CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

static int was_home;
static int was_end;

//////////////////////////////////////////////////////////////////////
// OnKeyDown

void CWedView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CString str, lstr, rstr, replay;

    // Reset key timer
    lastkeypress = 0;

    if( kblock )
        {
        message ("Keyboard Locked");
        return;
        }

    if(nChar != VK_HOME)
        was_home = 0;

    if(nChar != VK_END)
        was_end = 0;

    PrintToNotepad("Keydown: %d (%c) Flags: %d\r\n", nChar, nChar, nFlags);

    if(record)
        {
        CString num;
        if( nChar != VK_F7 && nChar != VK_F8  &&
                !(nChar >= '0' && nChar <= '9' && control))
            {
            if(macros[currmac].GetCount() > 80)
                {
                message("Recording longer then usual ...");
                }
            num.Format( "%d %d %d %d", R_DOWN, nChar, nRepCnt, nFlags);
            //PrintToNotepad("Recording: %s\r\n", num);
            macros[currmac].AddTail(num);
            }
        }

    if(nChar >= '0' && nChar <= '9' && control)
        {
        SwitchRec(nChar - '0');
        }
    else
    switch(nChar)
    {
    case VK_CANCEL:
    // control - break => ESC
        if(control)
            OnViewStopdiffing();
            Esc();
        break;

    case VK_SCROLL:
        //scrollock = !scrollock;
        //PrintToNotepad("Scroll lock\r\n");
        break;

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++

    case VK_F2:
        OnInsertTemplateone();
        break;

    case VK_F3:
        OnInsertTemplatetwo();
        break;

    case VK_F4:
        OnInsertTemplatethree();
        break;

    case VK_F5:
        if(control)
            //  Compile
            OnCompileExecutedevstudioproject();
        else
            //  Find prev
            OnSearchFindprevious();
        break;

    case VK_F6:
        //  Find next
        OnSearchFindnext();
        break;

    case VK_F7:
        if(control)
            Spellcheck(TRUE);
        else if(shift)
            Spellcheck(FALSE);
        else
        // Recording key:
            start_record();
        break;

    case VK_F8:
        // Playback key:
        if(control)
            OnCompileMake();
        else
            PlayMacro(shift);
        break;

    case VK_F9:
        if(shift)
            Caseselection(FALSE);
        else if (control)
            Caseselection(TRUE);
        else
            {
            // Open file
            ((CWedApp*)AfxGetApp())->OpenFile();
            message ("Opening file");
            }
        break;

    case VK_F11:
    	if(shift)
			OnMoveNextlongline();
    	else if(control)
    		{}
        break;

    case VK_F12:
    	if(shift)
			OnMoveMovepreviouslongline();
    	else if(control)
    		{}
        break;

    // +++++++++++++++++++++++++++++++++++++++++++++++++++++++

    case VK_SHIFT:
        shift = TRUE;
        break;

    case VK_CONTROL:
        control = TRUE;
        break;

    case VK_LEFT:
        //PrintToNotepad("RIGHT ");
        if(shift && soh == -1)
            {
            soh = eoh = row ;
            soch = eoch = col;
            }
        if(control)
            OnMovePreviouseword();
        else
            OnMovePreviouschar();
        break;

    case VK_RIGHT:
        //PrintToNotepad("LEFT ");
        if(shift && soh == -1)
            {
            soh = eoh = row ;
            soch = eoch = col;
            }
        if(control)
            OnMoveNextword();
        else
            OnMoveNextcharacter();
        break;

    case VK_UP:
        //PrintToNotepad("UP ");
        if(shift && soh == -1)
            soh = eoh = row ;
        OnMovePreviousline();
        HitCusror(FALSE);
        break;

    case VK_DOWN:
        //PrintToNotepad("DOWN ");
        if(shift  && soh == -1)
            soh = eoh = row;
        OnMoveNextline() ;
        HitCusror(TRUE);
        break;

    case VK_ADD:
        // Grey +
        if(GetKeyState(VK_NUMLOCK))
                break;
        //PrintToNotepad("Grey+ ");
        CopyToHold(this, FALSE);
        break;

    case VK_SUBTRACT:
        // Grey -
        if(GetKeyState(VK_NUMLOCK))
            break;
        //PrintToNotepad("Grey - ");
        CopyToHold(this, TRUE);
        break;

    case VK_PRIOR:
        //PrintToNotepad("PGUP ");
        if(shift && soh == -1)
            soh = eoh = row ;

        if(control)
            OnMovePreviouseparagraph();
        else
            OnMovePageup();

        HitCusror(FALSE);
        break;

    case VK_NEXT:
        //PrintToNotepad("PGDOWN ");
        if(shift && soh == -1)
            soh = eoh = row ;
        if(control)
            OnMoveNextparagraph();
        else
            OnMovePagedown();

        HitCusror(TRUE);
        break;

    case VK_HOME:
        //PrintToNotepad("HOME ");
        if(shift && soh == -1)
            {
            soh = eoh = row ;
            soch = eoch = col;
            }
        was_home++;
        if(was_home == 1)
            {
            if(control)
                OnMoveBeginningoffile();
            else
                OnMoveBeginningofline();
            }
        else if(was_home == 2)
            {
            OnMoveBeginningofpage();
            }
        else if(was_home == 3)
            {
            OnMoveBeginningoffile();
            }
        else
            {
            was_home = 0;
            }
        HitCusror(FALSE);
        break;

    case VK_END:
        //PrintToNotepad("END ");
        if(shift && soh == -1)
            {
            soh = eoh = row ;
            soch = eoch = col;
            }
        was_end++;
        if(was_end == 1)
            {
            if(control)
                OnMoveEndoffile();
            else
                OnMoveEndofline();
            }
        else if(was_end == 2)
            {
            OnMoveEndofpage();
            }
        else if(was_end == 3)
            {
            OnMoveEndoffile();
            }
        else
            {
            was_end = 0;
            }
        HitCusror(TRUE);
        break;

    case VK_DELETE:
        Del();
        //PrintToNotepad("DEL ");
        break;

    case VK_INSERT:
        if(hitmode)
            {
            CancelHit();
            break;
            }
        if(shift)
            {
            message ("Paste from clipboard");
            PasteClip(this);
            }
        else if (control)
            {
            message ("Copy to clipboard");
            CopyToClip(this, FALSE);
            }
        else
            {
            PasteHold(this);
            }
        break;

    case 'b':
        if(control)
        {
            message ("Control - B");
        }
        break;
    }
    CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


//////////////////////////////////////////////////////////////////////
// OnSysKeyDown

void CWedView::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);

    // Reset key timer
    lastkeypress = 0;

    //PrintToNotepad("SysKeyDown: %d (%c) Flags: %d\r\n", nChar, nChar, nFlags);

    if(record)
        {
        CString num;
        if(nChar != VK_F7 && nChar != VK_F8)
            {
            num.Format( "%d %d %d %d",
                R_SYSDOWN, nChar, nRepCnt, nFlags);
            //PrintToNotepad("Recording: %s\r\n", num);
            macros[currmac].AddTail(num);
            }
        }
    switch(nChar)
        {
        case VK_MENU:
            //PrintToNotepad("ALT");
            alt = TRUE;
            break;

        case VK_UP:
            //alt-up
            PrintToNotepad("ALT-UP");
            break;

        case VK_DOWN:
            //alt-down
            PrintToNotepad("ALT-DOWN\r\n");
            break;

        case VK_LEFT:
            //alt-left
            //PrintToNotepad("ALT-LEFT\r\n);
            OnMoveBeginningofword();
            break;

        case VK_RIGHT:
            //alt-right
            //PrintToNotepad("ALT-RIGHT ");
            OnMoveEndofword() ;
            break;
        }
    CView::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

//////////////////////////////////////////////////////////////////////
// OnSysChar

void CWedView::OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags)

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);

    //PrintToNotepad("SysChar: %d (%c) Flags: %d\r\n", nChar, nChar, nFlags);

    if(record)
        {
        CString num;
        num.Format( "%d %d %d %d", R_SYSCHAR, nChar, nRepCnt, nFlags);

        //PrintToNotepad("Recording: %s\r\n", num);
        macros[currmac].AddTail(num);
        }
    CString str, lstr;
    if(nChar >= '0' && nChar <= '9')
        {
        PrintToNotepad("Alt-1 ctrl: %d alt: %d\r\n", control, alt);
        CString num;
        currhold = nChar - '0';
        num.Format( " H %02d ", currhold);
        message ("Switched holding buffer");
        hold(num);
        }
    else
    switch(tolower(nChar))
    {
        //alt-a
    case 'a':
        // Select all
        OnFileSaveall();
        break;

        //alt-b
    case 'b':
        // Show buffers
        ShowBuffers();
        break;

        //alt-c
    case 'c':
        // Coloumn select
        OnEditStartcolumnselectaltc();
        break;

        //alt-d
    case 'd':
        // Delete line
        DelLine();
        break;

        //alt-e
    case 'e':
        message ("Opening file in source directory");
        OpenSource(srcdir);
        break;

        //alt-f
        // Dedicated to Alt file

        //alt-g
   case 'g':
        // Goto
        OnMoveGotoline();
        break;

        //alt-h
   case 'h':
        OnSearchHiteditmode();
        break;

        //alt-i
    case 'i':
        OnInsertIncrementednumber();
        break;

        //alt-j
    case 'j':
        OnViewCococodecolector();
        break;

        //alt-k
    case 'k':
        // Kill to EOL
        KillToTol();
        break;

        //alt-l
    case 'l':
        // Start line select
        OnEditStartselectaltl();
        break;

        //alt-m
    case 'm':
        OnSelectMarkblock();
        break;

        //alt-n
    case 'n':
        // Switch to next buffer
        SwitchToNext();
        break;

        //alt-o
    case 'o':
        // Open file
        message ("Opening file in destination directory");
        OpenSource(targdir);
        break;

        //alt-p
    case 'p':
        // Paragraph select
        OnSelectSelectparagraph();
        break;

        //alt-q
    case 'q':
        Maximizecurrent();
        break;

        //alt-r
    case 'r':
        // Redo
        ReDo(this);
        break;

        //alt-s
    case 's':
        SearchFile();
        break;

        //alt-t
    case 't':
        // Change (Taush)
        SearchFile(TRUE);
        break;

        //alt-u
    case 'u':
        // Undo
        UnDo(this);
        break;

        //alt-v
    case 'v':
        // Select word with coloumn highlite:
        OnSelectSelectword();
        break;

        //alt-w
    case 'w':
        // Write:
        if(!pDoc->IsModified())
            {
            message("Document not modified");  break;
            }
        AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_FILE_SAVE, 0);
        pDoc->SetTitle(pDoc->GetPathName());
        break;

        //alt-x
    case 'x':
        // Exit
        //SetParent(parent);
        //AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_APP_EXIT, 0);
        break;

        //alt-y
    case 'y':
        OnViewFullscreen();
        break;

        //alt-z
    case 'z':
        OnWindowMaximizemain();
        break;

    default:
        CView::OnSysChar(nChar, nRepCnt, nFlags);
        break;
    }
}

//////////////////////////////////////////////////////////////////////
// OnSysKeyUp

void CWedView::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)

{
    currentedit = this;
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);

    if(record)
        {
        CString num;
        if(nChar != VK_F7 && nChar != VK_F8)
            {
            num.Format( "%d %d %d %d",  R_SYSUP, nChar, nRepCnt, nFlags);
            //PrintToNotepad("Recording: %s\r\n", num);
            macros[currmac].AddTail(num);
            }
        }
    switch(nChar)
        {
        case VK_MENU:
            alt = FALSE;
            break;
        }
    CView::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

//////////////////////////////////////////////////////////////////////
// OnSetFocus

void CWedView::OnSetFocus(CWnd* pOldWnd)

{
    // Call default function
    CView::OnSetFocus(pOldWnd);

    currentedit = this;
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    mode(modestr);

     // Take care of our cursor
    CreateCaret(&caret);  ShowCaret();  SyncCaret();

    // This caused dblclick to be sent
    // YieldToWin();

    //PrintToNotepad("Got Focus: %d from %d parent %d\r\n",
    //                  this, pOldWnd, GetParent());

    mouse = 0;

    scrolldiv = (pDoc->strlist.GetCount() / 33000) + 1;
    SetScrollRange(SB_VERT,  0, pDoc->strlist.GetCount()/scrolldiv);
    SetScrollRange(SB_HORZ,  0, pDoc->maxcol);
    //PrintToNotepad("Scrolldiv %d\r\n", scrolldiv);

    // Fill in diff submenu
    CMenu* pfMenu = GetDiffMenu();
    if(pfMenu)
        {
        for (int iPos = pfMenu->GetMenuItemCount()-1; iPos >= 0; iPos--)
            {
            pfMenu->DeleteMenu(iPos, MF_BYPOSITION);
            }
        // Add an item for each available file
        CWedApp *app = (CWedApp*)AfxGetApp();
        POSITION Pos = app->pDocTemplate->GetFirstDocPosition();

        int offset = 0;
        for(int loop = 0; loop < 5; loop++)
            {
            if(!Pos)
                break;

            CWedDoc* doc = (CWedDoc*)app->pDocTemplate->GetNextDoc(Pos);
            ASSERT_VALID(doc);

            // Current doc, do not count
            if(doc == pDoc)
                continue;

            CString file = doc->GetPathName();
            pfMenu->AppendMenu( MF_STRING, ID_DIFF_DIFFONE + offset  , file);
            offset++;
            }
        }
    // See if file was modified outside of WED
    CString file = pDoc->GetPathName();
    if(file != "")
        {
        struct _stat docstat3;
        if(!_stat(file, &docstat3))
            {
            //PrintToNotepad("file %s Docstat %d docstat2 %d \r\n",
            //                  file, pDoc->docstat2.st_mtime,  docstat3.st_mtime );

            if(pDoc->docstat2.st_mtime != docstat3.st_mtime)
                {
                pDoc->docstat2 = docstat3;
                AfxMessageBox("File changed outside Wed. Please check.");
                YieldToWin();
                }
            }
        }
}

// Make POS and caret agree
// If bound == 1 move 3 lines away from borders
// If bound == 2 || bound == 3 move sync to the middle

//////////////////////////////////////////////////////////////////////
// SyncCaret

int  CWedView::SyncCaret(int bound)

{
    CString num;
    int wants = 0;
    POINT pos;
    RECT rec;
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);

    if(!fflf.lfHeight)
        fflf.lfHeight = 14;
    if(!fflf.lfWidth)
        fflf.lfWidth  = 8;

    //PrintToNotepad("Sync_caret %d %d\r\n", row, col);

    // Make sure we are in file
    if(row >= pDoc->strlist.GetCount())
        {
        row = pDoc->strlist.GetCount()-1;
        }

    // Make sure we are in view
    GetClientRect(&rec) ;

    // Display caret in new position:
    if(srow > row)
        {
        srow = row;
        if(bound == 1)
            srow -= 3;
        //PrintToNotepad("Up scroll srow = %d\r\n", srow);
        wants =  TRUE;
        }
    if(scol > col)
        {
        scol = col;
        //PrintToNotepad("Left scroll scol = %d\r\n", scol);
        wants =  TRUE;
        }
    int xxrow = row;
    // Handle hit mode
    if(hitmode)
        {
        int vrow = srow,  xrow = srow;
        while(TRUE)
            {
            // Limit:
            if(vrow >= pDoc->strlist.GetCount()-1)
                break;
            if(vrow >= row)
                break;
            // Adjust:
            if(pDoc->ssel.lineb.GetAt(vrow))
                xrow++;

            vrow++;
            }
        PrintToNotepad("xrow = %d\r\n", xrow);

        // Adjust virtual position
        xxrow = xrow;
        }
    pos.x = fflf.lfWidth * (col - scol);
    pos.y = fflf.lfHeight * (xxrow - srow) + fflf.lfHeight - 2;

    // Limit it
    if((rec.bottom - rec.top) < pos.y )
        {
        srow = (fflf.lfHeight * (row + 1)  -
                        (rec.bottom - rec.top))/fflf.lfHeight + 1;

        if(bound == 1)
            srow += 3;

        pos.y = fflf.lfHeight * (row - srow) + (fflf.lfHeight-2);
        wants =  TRUE;
        //PrintToNotepad("Scroll srow = %d\r\n", srow);
        }

    // 2 times char width for the scroll bar
    if(rec.right - rec.left < pos.x + 2 * fflf.lfWidth)
        {
        scol = (fflf.lfWidth * (col + 1)
                    - (rec.right - rec.left))/fflf.lfWidth + 1;

        pos.x = fflf.lfWidth * ((col - scol) + 1);
        wants =  TRUE;
        //PrintToNotepad("Scroll scol = %d\r\n", scol);
        }

     // Adjust for bound
    if(bound == 3 || bound == 2 || GetKeyState(VK_SCROLL))
        {
        int mid = ((rec.bottom - rec.top)/fflf.lfHeight)/2;
        if(row >  mid)
            {
            srow = row - mid;
            //row = mid;
            }
        //PrintToNotepad("bound3 scol = %d\r\n", scol);

        pos.x = fflf.lfWidth * (col - scol);
        pos.y = fflf.lfHeight * (row - srow) + (fflf.lfHeight-2);

        wants = TRUE;
        }

    // Check for out of bounds
    srow = min(srow, pDoc->strlist.GetCount()-1);
    srow = max(srow, 0);

    row = min(row, pDoc->strlist.GetCount()-1);
    row = max(row,  0);

    //col = min(col,  0);

    if(wants && !in_draw)
        pDoc->UpdateAllViews(NULL);

    // -----------------------------------------------
    SetCaretPos(pos);

    // Set highlight
    if(soh != -1)
        {
        eoh = row;
        if(soch != -1)
            eoch = col;

        // Redisplay if highlight changed
        if(!in_draw)
            pDoc->UpdateAllViews(NULL);
        }
    // Massage scroll bars
    int lines =  pDoc->strlist.GetCount()-1;
    SetScrollRange(SB_VERT,  0, lines/scrolldiv);
    SetScrollRange(SB_HORZ, 0, pDoc->maxcol);

    SetScrollPos(SB_HORZ, col);
    SetScrollPos(SB_VERT, row/scrolldiv);

    num.Format("Ln %d Col %d ", row, col);
    rowcol(num);

    num.Format("Ln %d ", lines);
    filesize(num);

    // Do not yield here !!!
    return(0);
}


//////////////////////////////////////////////////////////////////////
// OnUpdate

void CWedView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);

    //PrintToNotepad("OnUpdate %d %d\r\n", row, col);

    if(lHint)
        {
        // Only from current postion to end of line
        RECT rec;
        CString str;
        str = pDoc->strlist.GetLine(row);
        rec.left = fflf.lfWidth  * (col-1);
        rec.top  = fflf.lfHeight * (row - srow);
        // in case of deleted char, add one
        rec.right = fflf.lfWidth * (str.GetLength() + 4);
        rec.bottom = rec.top + fflf.lfHeight;

        InvalidateRect(&rec, FALSE);
        }
    else
        {
        // Refresh the whole lot:
        InvalidateRect(NULL, FALSE);
        }
}

//////////////////////////////////////////////////////////////////////
// OnCreate

int  CWedView::OnCreate(LPCREATESTRUCT lpCreateStruct)

{
    ShowScrollBar(SB_BOTH );
    EnableScrollBar(0);
    SetFont(&ff);

    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    return 0;
}

//////////////////////////////////////////////////////////////////////
// ShowBuffers

void CWedView::ShowBuffers()

{
    message("Show Buffers");
    BufferList bl;
    bl.m_edit = (long)this;
    bl.DoModal();
}

static CPoint oldpoint;

//////////////////////////////////////////////////////////////////////
// OnLButtonDown

void CWedView::OnLButtonDown(UINT nFlags, CPoint point)

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);

    PrintToNotepad("Mouse: x=%d y=%d\r\n", point.x, point.y);

    if(fflf.lfHeight == 0 )
        goto endd;
    if(fflf.lfWidth == 0 )
        goto endd;

    // Translate coordinates
    row = point.y /fflf.lfHeight + srow;
    col = point.x /fflf.lfWidth  + scol;
    row = min(row, pDoc->strlist.GetCount()-1);

    // Tell the system the mouse is down ...
    mouse = TRUE;

    //If we clicked on non highlite, stop highlites
    if(row < soh || row > eoh)
        {
        soh = eoh = soch = eoch = -1;
        pDoc->UpdateAllViews(NULL);
        }
    SyncCaret();
    oldpoint = point;

endd: ;
//    CView::OnLButtonDown(nFlags, point);
}


//////////////////////////////////////////////////////////////////////
// OnLButtonDblClk

void CWedView::OnLButtonDblClk(UINT nFlags, CPoint point)

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CString str;
    int wbeg = 0, wend = 0, lrow;

    PrintToNotepad("Dblclick x:%d  y:%d\r\n", point.x, point.y);

    if(fflf.lfHeight == 0 )
        goto endd;
    if(fflf.lfWidth == 0 )
        goto endd;

    lrow = point.y /fflf.lfHeight + srow;
    lrow = min(lrow, pDoc->strlist.GetCount()-1);

    //col = point.x /fflf.lfWidth;
    str = pDoc->strlist.GetLine(lrow);

    // Find word we are sitting on
    SelWord(str, col, &wbeg, &wend);

    //PrintToNotepad("SelWord: %d %d\r\n", wbeg, wend);

    if(wbeg != wend)
        {
        col  = wend-1;
        soh = row;
        eoh = row;
        soch = wbeg;
        eoch = wend;
        }
    pDoc->UpdateAllViews(NULL); SyncCaret();

endd: ;
    //CView::OnLButtonDblClk(nFlags, point);
}

static CString undostr;
static int oldrow, oldcol, startrow, endrow;

//////////////////////////////////////////////////////////////////////
// OnLButtonUp

void CWedView::OnLButtonUp(UINT nFlags, CPoint point)

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);

    // Save undo info for this one:
    if(drag)
    {
        if(startrow != endrow)
        {
        // We have moved a string ...
        //PrintToNotepad("Saveundo: start %d end %d with %s\r\n"
        //        , startrow, endrow, undostr);

        SaveUndo(this, 'd', startrow, 0, undostr);
        SaveUndo(this, 't', endrow, 0, undostr);
        }
    }
    mouse = FALSE;
    drag = FALSE;
    highlite = FALSE;

    ReleaseCapture();

    CView::OnLButtonUp(nFlags, point);
}


//////////////////////////////////////////////////////////////////////
// OnMouseMove

void CWedView::OnMouseMove(UINT nFlags, CPoint point)

{
    int lrow, lcol;
    CWedDoc*    pDoc;

    //PrintToNotepad("Mousemove %d  x=%d y=%d\r\n",
    //  this, point.x, point.y );

    if(m_busy)
        SetCursor(WaitCursor);

    // If mouse is not down, no drag or highlite in progress
    if(!mouse)
        {
        goto end_mou;
        }
    if(fflf.lfHeight == 0 )
        goto end_mou;
    if(fflf.lfWidth == 0 )
        goto end_mou;

    pDoc = GetDocument(); ASSERT_VALID(pDoc);

    // Translate to cursor coordinates:
    lrow = point.y /fflf.lfHeight + srow;
    lcol = point.x /fflf.lfWidth;

    // Check for out of bounds, SetCapture can do minuses
    lrow = max(lrow, 0);
    lrow = min(lrow, pDoc->strlist.GetCount()-1);
    lcol = max(lcol, 0);

    // Move to coordinates
    row = lrow;
    col = lcol;

#if 0
    // Test if in action
    if(drag)
        {
        // Row changed, action
        if(oldrow != lrow)
            {
            int loop, xrow, offset;

            offset = lrow - oldrow;
            xrow = oldrow = lrow;

            //PrintToNotepad("Drag: x=%d y=%d\r\n", point.x, point.y);

            // Remove old
            lrow = soh;

            SaveUndo(this, UNDO_NOP, row, col, "");

            for(loop = 0; loop < draglist.GetCount(); loop++)
                {
                CString str = pDoc->strlist.GetLine(lrow);

                //PrintToNotepad("Delete line: %s\r\n", str);
                SaveUndo(this, UNDO_DEL, lrow, col, str);
                DeleteLine(this, lrow);
                }
            if(offset >  0)
                {
                if (soh < pDoc->strlist.GetCount()-1)
                    {
                    lrow = ++soh;  ++eoh;
                    }
                }
            else
                {
                if (soh)
                    {
                    lrow = --soh; --eoh;
                    }
                }
            // Add new, careful of last line (spent a day tracking):
            POSITION pos = draglist.FindIndex(0);
            loop = lrow;

            while(TRUE)
                {
                CString str2;

                if(!pos)
                    break;

                str2 = draglist.GetNext(pos);
                pDoc->strlist.InsertLine(loop++, str2);
                //PrintToNotepad("Adding: row=%d %s\r\n", lrow, str2);
                }

            //soh = xrow + 1 ;
            //eoh = xrow + draglist.GetCount();

            endrow = lrow;
            pDoc->UpdateAllViews(NULL); SyncCaret();
            }
        }
    else
#endif

    if (highlite)
        {
        if(oldrow != lrow || oldcol != lcol)
            {
            col = lcol;
            row = lrow;

            //PrintToNotepad("Highlite: %d\r\n", row);

            oldrow = lrow;
            oldcol = lcol;

            SyncCaret();
            //pDoc->UpdateAllViews(NULL);
            }
        }
    else
        {
#if 0
        // Not in action, see if we want some
        if(soh != -1)
            {
            // start drag:
            undostr = pDoc->strlist.GetAt(
            pDoc->strlist.FindIndex(lrow));

            // ---------------------------------------------
            if(lrow >= soh && lrow < eoh )
                {
                int loop;

                draglist.RemoveAll();
                for(loop = soh; loop <= eoh; loop++)
                    {
                    CString hl;
                    hl = pDoc->strlist.GetAt(
                            pDoc->strlist.FindIndex(loop));
                    draglist.AddTail(hl);

                    //PrintToNotepad("Drag pick: %s\r\n", hl);
                    }
                }
            else
                {
                soh  = -1;
                eoh  = -1;
                soch = -1;
                eoch = -1;
                highlite = FALSE;
                }

            // ---------------------------------------------

            oldrow = lrow;
            startrow = lrow;
            drag = TRUE;
            }
        else
#endif

            {
            // start higlite, only if we dragged a 1/2 char
            if(abs(oldpoint.x - point.x) > 2)
                {
                //PrintToNotepad("Start col highlite: %d\r\n", soh);
                soh =  eoh =  lrow;
                soch = eoch = lcol;
                highlite = TRUE;
                }
            else if(abs(oldpoint.y - point.y) > 2)
                {
                //PrintToNotepad("Start row highlite: %d\r\n", soh);
                soh = eoh = lrow;
                highlite = TRUE;
                }
            }
        SetCapture();
        }
  end_mou:
   CView::OnMouseMove(nFlags, point);
}


//////////////////////////////////////////////////////////////////////
// OnVScroll

void CWedView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);

    switch(nSBCode)
    {
    // Emulate keystrokes:
    case SB_LINEDOWN   :
            OnKeyDown(40, 1, 336);
            break;

    case SB_LINEUP   :
            OnKeyDown(38, 1, 328);
            break;

    case SB_PAGEDOWN   :
        OnKeyDown(34, 1, 337);
        break;

    case SB_PAGEUP   :
        OnKeyDown(33, 1, 329);
        break;

    case SB_LEFT   :
        OnKeyDown(33, 1, 329);
        break;

    case    SB_THUMBTRACK  :
        row = (nPos * scrolldiv);
        SyncCaret();
        //pDoc->UpdateAllViews(NULL);
        //PrintToNotepad("Scroll track %d\r\n", nPos);
        break;
    }
    SetScrollPos(SB_VERT, row/scrolldiv);
    CView::OnVScroll(nSBCode, nPos, pScrollBar);
}


//////////////////////////////////////////////////////////////////////
// OnViewViewhex

void CWedView::OnViewViewhex()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CString str = pDoc->strlist.GetLine(row);
    int real, ontab;

    if( hex)
    {
        modestr = "";
        mode(modestr);
        hex = FALSE;
        UnTabbedPos(str, col/3, &real, &ontab);
        col = real;
    }
    else
    {
        TabbedPos(str, col, &real, &ontab);
        col = real * 3;
        hex = TRUE;
        modestr = "HEX";
        mode(modestr);
    }
    message ("Toggled HEX mode");
    pDoc->UpdateAllViews(NULL);
}


//////////////////////////////////////////////////////////////////////
// OnPrint

void CWedView::OnPrint(CDC* pDC, CPrintInfo* pInfo)

{
    CString  foot;
    CString  head;
    int xx = 0, yy = 0, lim;
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CString str;
    CFont *oldfont;
    TEXTMETRIC tm;

    //PrintToNotepad("Rendering page: %d\r\n", pInfo->m_nCurPage);

    // Just started
    if(pInfo->m_nCurPage == 1)
    {
        progress = 0;

        // Kill previous array
        pages.SetSize(2);
        pages.SetAtGrow(pInfo->m_nCurPage, progress);
        pInfo->SetMaxPage(pInfo->m_nCurPage+1);
    }
    else
    // Remeber page boundaries for backwards scan
    {
        if(pages.GetSize() < (int)pInfo->m_nCurPage + 1)
            {
            // Add
            pages.SetAtGrow(pInfo->m_nCurPage, progress);
            pInfo->SetMaxPage(pInfo->m_nCurPage+1);
            }
        else
            {
            // Recall
            pInfo->m_bContinuePrinting = TRUE ;
            progress = pages.GetAt(pInfo->m_nCurPage);
            }
    }
    oldfont = pDC->SelectObject( &pp );
    pDC->GetTextMetrics(&tm);

    // Put header and footer
    head.Format("%s:%d", pDoc->GetPathName(), progress);

    pDC->TextOut(pInfo->m_rectDraw.BottomRight().x /2 -
            head.GetLength() * tm.tmAveCharWidth/2, 00,
            head);

    foot.Format("- page %d -", pInfo->m_nCurPage);
    pDC->TextOut(pInfo->m_rectDraw.BottomRight().x /2 -
            foot.GetLength() * tm.tmAveCharWidth/2,
            pInfo->m_rectDraw.BottomRight().y - tm.tmHeight,
                foot);

    // Adjust limits to alow header/footer
    pInfo->m_rectDraw.BottomRight().y  -= 3*tm.tmHeight;
    pInfo->m_rectDraw.TopLeft().y += 3*tm.tmHeight;

    // Leave space for hole punch and right margin
    pInfo->m_rectDraw.TopLeft().x += 6 * tm.tmHeight;
    pInfo->m_rectDraw.BottomRight().x  -= 3 * tm.tmHeight;

    // Do it
    int height = pInfo->m_rectDraw.BottomRight().y -
                        pInfo->m_rectDraw.TopLeft().y ;

    int width = pInfo->m_rectDraw.BottomRight().x -
                        pInfo->m_rectDraw.TopLeft().x ;

    int cwidth = width / tm.tmAveCharWidth;

    xx = pInfo->m_rectDraw.TopLeft().x ;
    yy = pInfo->m_rectDraw.TopLeft().y ;
    lim  = pDoc->strlist.GetCount() ;

    while(TRUE)
        {
        str = pDoc->strlist.GetLine(progress);
        progress++;

        // End of document
        if(progress > lim)
            break;

        // See if it is a pagefeed
        if(str == "\xc")
            {
            //AfxMessageBox("Pagefeed");
            break;
            }

        // Tabs did not work on some printers, we expand them here
        ExpandTabs(str);

        CString str2;
        while(TRUE)
            {
            str2= str.Left(cwidth);

            // Wrap lines, no word boundary is considered
            pDC->TabbedTextOut(xx, yy, str2, 1, tabs, 0);
            yy+=tm.tmHeight;

            // Reached limit of string, stop
            if(str.GetLength() < cwidth)
                break;

            str = str.Right(str.GetLength() - cwidth);

            // Reached limit of client area, stop
            if(yy > height)
                break;
            }

        // Reached limit of client area, stop
        if(yy > height)
            break;
        }

    // Examine end of document
    if(progress > lim)
        {
        pInfo->SetMaxPage(pInfo->m_nCurPage);
        }
    // Restore stolen settings:
    pDC->SelectObject(oldfont);
}


//////////////////////////////////////////////////////////////////////
// OnPrepareDC

void CWedView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)

{
    CView::OnPrepareDC(pDC, pInfo);

    // The class will pass a null pointer, ignore it
    if(!pDC)
        return;

    // The class will pass a null pointer, ignore it
    if(!pInfo)
        return;

    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    int lim  = pDoc->strlist.GetCount() ;

    pInfo->m_bContinuePrinting = TRUE ;

    // Only limit on real printing:
    if(!pInfo->m_bPreview)
    {
    if(progress >= lim)
        {
         pInfo->m_bContinuePrinting = FALSE ;
        }
    }
}


//////////////////////////////////////////////////////////////////////
// OnHScroll

void CWedView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);

    switch(   nSBCode)
    {
    case    SB_LINELEFT:
            OnKeyDown(37, 1, 331);
            break;

    case    SB_LINERIGHT :
            OnKeyDown(39, 1, 333);
            break;

    case    SB_PAGELEFT:
            OnKeyDown(17, 1, 29);
            OnKeyDown(37, 1, 331);
            OnKeyUp(17, 1, 49181);
            break;

    case    SB_PAGERIGHT:
            OnKeyDown(17, 1, 29);
            OnKeyDown(39, 1, 333);
            OnKeyUp(17, 1, 49181);
            break;

    case    SB_THUMBTRACK   :

            col = nPos;
            SyncCaret();
            break;
    }

    CView::OnHScroll(nSBCode, nPos, pScrollBar);
}

//////////////////////////////////////////////////////////////////////
// OnViewFonts

void CWedView::OnViewFonts()

{
    LOGFONT lf;
    //Cfont

    ff.GetObject(sizeof(LOGFONT), &lf);

    CFontDialog dlg(&lf, CF_FIXEDPITCHONLY  |
                            CF_SCREENFONTS  |
                                CF_INITTOLOGFONTSTRUCT);
    if (dlg.DoModal() != IDOK)
        return;

    // Switch to new font.
    ff.DeleteObject();
    if (!ff.CreateFontIndirect(&lf))
        {
        //PrintToNotepad("Cannot set font\r\n");
        MessageBox("Cannot set font");
        }

    // Logical parameters for the new font.
    //if(!ff.GetLogFont(&fflf))
    //  {
    //    //PrintToNotepad("Cannot set font\r\n");
    //    MessageBox("Cannot get logical font parameters");
    //  }
    //PrintToNotepad("Selected new font: HH:%d WW: %d\r\n",
    //                          fflf.lfHeight, fflf.lfWidth);

    // Tell all documents about the change
    POSITION Pos =
        ((CWedApp*)AfxGetApp())->pDocTemplate->
                GetFirstDocPosition();
    for(;;)
        {
        if(!Pos)
            break;
        CWedDoc* doc = (CWedDoc*)
            ((CWedApp*)AfxGetApp())->pDocTemplate->
                    GetNextDoc(Pos);
        doc->UpdateAllViews(NULL);
        }
}

extern CWedApp theApp;
static diffing = FALSE;

//////////////////////////////////////////////////////////////////////
// OnInitialUpdate
// Allocate one time stuff:

void CWedView::OnInitialUpdate()

{
    CView::OnInitialUpdate();
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    pDoc->SetTitle(pDoc->GetPathName());

    parent = GetParent();

    if(!pDoc->inited)
        {
        pDoc->ssel.Create(IDD_DIALOG4);
        pDoc->inited = TRUE;
        SaveUndo(this, UNDO_MARK, row, col, "");
        }
}

//////////////////////////////////////////////////////////////////////
// OnKillFocus

void CWedView::OnKillFocus(CWnd* pNewWnd)

{
    UnFullscreen();
    HideCaret();
    DestroyCaret();
	currentedit = NULL;

    CView::OnKillFocus(pNewWnd);
    //soch = eoch =  soh = eoh = -1;
    mouse = FALSE;
    control = shift = alt = FALSE;
    //PrintToNotepad("Kill focus %d \r\n", this);
}

//////////////////////////////////////////////////////////////////////
// OnViewForegroundcolor

void CWedView::OnViewForegroundcolor()

{
    SetColor(&fgcol);
}

//////////////////////////////////////////////////////////////////////
// OnViewBackgroundcolor

void CWedView::OnViewBackgroundcolor()

{
    SetColor(&bgcol);
}

//////////////////////////////////////////////////////////////////////
// SetColor

void CWedView::SetColor(COLORREF * col)

{
    CColorDialog ccol(*col);

    if(ccol.DoModal() == IDOK)
        {
        *col = ccol.m_cc.rgbResult;

        // Tell all documents about the change
        POSITION Pos =
            ((CWedApp*)AfxGetApp())->pDocTemplate->
                    GetFirstDocPosition();
        for(;;)
            {
            if(!Pos)
                break;
            CWedDoc* doc = (CWedDoc*)
                ((CWedApp*)AfxGetApp())->pDocTemplate->
                    GetNextDoc(Pos);
            doc->UpdateAllViews(NULL);
            }
        }
}


//////////////////////////////////////////////////////////////////////
// OnViewHighlitebackground

void CWedView::OnViewHighlitebackground()

{
    SetColor(&selcol);
}


//////////////////////////////////////////////////////////////////////
// OnViewColomnhighlitebackground

void CWedView::OnViewColomnhighlitebackground()

{
    SetColor(&cselcol);
}


//////////////////////////////////////////////////////////////////////
// OnViewSelectprinterfont

void CWedView::OnViewSelectprinterfont()

{
    LOGFONT lf;

    //memset(&lf, 0, sizeof(lf));
    pp.GetObject(sizeof(LOGFONT), &lf);

    CFontDialog dlg(&lf, CF_FIXEDPITCHONLY   |
                            CF_SCREENFONTS  |

                            //CF_PRINTERFONTS  |
                                CF_INITTOLOGFONTSTRUCT);
    if (dlg.DoModal() == IDOK)
    {
        // switch to new font.
        pp.DeleteObject();
        if (!pp.CreateFontIndirect(&lf))
        {
            //PrintToNotepad("Cannot set font\r\n");
            MessageBox("Cannot set font");
        }
    }
}


//////////////////////////////////////////////////////////////////////
// OnEditCut

void CWedView::OnEditCut()

{
    message ("Cut to clipboard");
    CopyToClip(this, TRUE);
}


//////////////////////////////////////////////////////////////////////
// OnEditCopy

void CWedView::OnEditCopy()

{
    message ("Copy to clipboard");
    CopyToClip(this, FALSE);
}


//////////////////////////////////////////////////////////////////////
// OnEditPaste

void CWedView::OnEditPaste()

{
    message ("Paste from clipboard");
    PasteClip(this);
}

// Copy to holding buffer


//////////////////////////////////////////////////////////////////////
// OnViewViewholdingheads

void CWedView::OnViewViewholdingheads()

{
    HoldHead hh;
    hh.m_edit1  =  holding[0].IsEmpty() ? "empty": holding[0].GetHead() ;
    hh.m_edit2  =  holding[1].IsEmpty() ? "empty": holding[1].GetHead() ;
    hh.m_edit3  =  holding[2].IsEmpty() ? "empty": holding[2].GetHead() ;
    hh.m_edit4  =  holding[3].IsEmpty() ? "empty": holding[3].GetHead() ;
    hh.m_edit5  =  holding[4].IsEmpty() ? "empty": holding[4].GetHead() ;
    hh.m_edit6  =  holding[5].IsEmpty() ? "empty": holding[5].GetHead() ;
    hh.m_edit7  =  holding[6].IsEmpty() ? "empty": holding[6].GetHead() ;
    hh.m_edit8  =  holding[7].IsEmpty() ? "empty": holding[7].GetHead() ;
    hh.m_edit9  =  holding[8].IsEmpty() ? "empty": holding[8].GetHead() ;
    hh.m_edit10 =  holding[9].IsEmpty() ? "empty": holding[9].GetHead() ;
    hh.m_edit11 = "Head of holding buffers";
    hh.DoModal();
}


//////////////////////////////////////////////////////////////////////
// OnWindowMaximizemain

void CWedView::OnWindowMaximizemain()

{
    AfxGetApp()->m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
}


//////////////////////////////////////////////////////////////////////
// OnEditUndo

void CWedView::OnEditUndo()

{
    UnDo(this);
}


//////////////////////////////////////////////////////////////////////
// OnEditRedo

void CWedView::OnEditRedo()

{
    ReDo(this);
}


//////////////////////////////////////////////////////////////////////
// OnRButtonDown

void CWedView::OnRButtonDown(UINT nFlags, CPoint point)

{
    POINT scr = point;
    ClientToScreen(&scr);

    CMenu mm;
    mm.LoadMenu(IDR_MENU1);
    CMenu *pp = mm.GetSubMenu( 0 );
    pp->TrackPopupMenu( TPM_LEFTALIGN, scr.x, scr.y, this);

    //PrintToNotepad("RbuttonDown\r\n");

    CView::OnRButtonDown(nFlags, point);
}


//////////////////////////////////////////////////////////////////////
// OnOperationsSelectline

void CWedView::OnOperationsSelectline()

{
    CWedDoc*    pDoc = GetDocument(); ASSERT_VALID(pDoc);
    soh = row;
    eoh = row;

    SyncCaret();  pDoc->UpdateAllViews(NULL);

    message("Line selected");
}

//////////////////////////////////////////////////////////////////////
// OnDiffDiffone

void CWedView::OnDiffDiffone()

{
    OnDiffToX(0);
}

//////////////////////////////////////////////////////////////////////
// OnDiffDifftwo

void CWedView::OnDiffDifftwo()

{
    OnDiffToX(1);
}


//////////////////////////////////////////////////////////////////////
// OnDiffDiffthree

void CWedView::OnDiffDiffthree()

{
    OnDiffToX(2);
}


//////////////////////////////////////////////////////////////////////
// OnDiffDifffour

void CWedView::OnDiffDifffour()

{
    OnDiffToX(3);
}

//////////////////////////////////////////////////////////////////////
// OnDiffDiffive

void CWedView::OnDiffDiffive()

{
    OnDiffToX(4);
}

//////////////////////////////////////////////////////////////////////
// OnDiffToX

void CWedView::OnDiffToX(int num)

{
    CWedDoc*    pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CString str, file;
    CWedDoc* doc;
    CMenu *mmm = GetDiffMenu();

    mmm->GetMenuString(num, str, MF_BYPOSITION);
    CWedApp     *app = (CWedApp*)AfxGetApp();
    POSITION Pos = app->pDocTemplate->GetFirstDocPosition();

    for(;;)
        {
        if(!Pos)
            break;

        doc = (CWedDoc*)app->pDocTemplate->GetNextDoc(Pos);
        ASSERT_VALID(doc);
        file = doc->GetPathName();
        if(file == str)
            break;
        }
    ASSERT_VALID(doc);

    //PrintToNotepad("diff to X: %d %s -- %s\r\n", num, str, file);

    POSITION pos = doc->GetFirstViewPosition();
    CView *cv = doc->GetNextView(pos);
    ASSERT_VALID(cv);

    //diffing = TRUE;
    Busy(TRUE);
    dodiff(this, (CWedView*)cv);
    Busy(FALSE);

    // Make them display it
    diff = 1;

     // Color to diff specs
    pDoc->SetTitle( pDoc->GetPathName() + " Diff Source ");

    other = (CWedView*)cv;
    doc->SetTitle( doc->GetPathName() + " Diff Target ");
    ((CWedView*)cv)->diff = 2;
    ((CWedView*)cv)->other = this;

    pDoc->UpdateAllViews(NULL);
    doc->UpdateAllViews(NULL);
}

static CString old;

//////////////////////////////////////////////////////////////////////
// SearchFile

void CWedView::SearchFile(int replace)

{
    CWedDoc*    pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CString str2, str = pDoc->strlist.GetLine(row);

    // Stop highlite
    if(AllowShighlite)
        {
        AllowShighlite = 0;
        pDoc->UpdateAllViews(NULL);
        }
    // Find word we are sitting on
    int wbeg = 0, wend = 0;
    SelWord(str, col, &wbeg, &wend);
    //PrintToNotepad("SelWord: %d %d\r\n", wbeg, wend);

    // Two int-s have the word
    if(wbeg != wend)
        {
        wbeg = scr2str(str, wbeg);
        wend = scr2str(str, wend);
        str2 = str.Mid(wbeg, wend-wbeg);
        }
    else
        {
        str2 = old;
        }
    PrintToNotepad("Got string '%s'\r\n", str2);

    // Init search dialog
    CString old = srcdlg.m_combo1;
    srcdlg.m_combo1 = str2;
    srcdlg.m_taush = replace;

    if(srcdlg.m_taush)
        srcdlg.m_combo2  = str2;
    else
        srcdlg.m_combo2  = "";

    // Activate it
    srcdlg.DoModal();
    old = srcdlg.m_combo1;

    if( srcdlg.m_esc || (srcdlg.m_combo1 == ""  &&
                srcdlg.m_stype != S_FUNCTION) )
        {
        srcdlg.m_esc = FALSE;
        srcdlg.m_combo1 = old;
        return;     // Cancelled
        }
    // Iterate on all documents:
    int lim = srcdlg.m_files.GetCount();
    for(int loop3 = 0; loop3 < lim; loop3++)
        {
        CString str3;

        POSITION pos = srcdlg.m_files.FindIndex(loop3);
        if(pos)
            {
            str3 = srcdlg.m_files.GetAt(pos);
            CWedDoc*  doc = GetDocFromPath(str3);
            if(doc)
                {
                DoSearch(doc, replace);
                }
            }
        }
}

//////////////////////////////////////////////////////////////////////
// DoSearch

void CWedView::DoSearch(CWedDoc*  pDoc, int replace)

{
    static int in_search;

    if(in_search)
        return;

    in_search = TRUE;

    int high = 0, items = 0, loop, lim, start;
    ASSERT_VALID(pDoc);

    POSITION   pos = pDoc->GetFirstViewPosition();
    CWedView* pView = (CWedView*)pDoc->GetNextView(pos);

    // Scoped search
    if(pView->soh == -1)
        {
        lim  =  pDoc->strlist.GetCount() ;
        start = 0;
        }
    else
        {
        // Make logical highlite
        int lsoh, leoh;
        if(soh < eoh)
            {
            lsoh = soh; leoh = eoh;
            }
        else
            {
            leoh = soh; lsoh = eoh;
            }
        start = lsoh;
        lim  =  leoh+1;

        // Cancel it, looks nicer
        soch = eoch =  soh = eoh = -1;
        }
    pDoc->ssel.ShowWindow(TRUE);
    pDoc->ssel.m_rep = replace;
    pDoc->ssel.m_src = srcdlg.m_combo1;
    pDoc->ssel.connect = (int)pView;
    pDoc->ssel.slb.ResetContent();

    Busy(TRUE);
    //CWaitCursor cursor;

    CString str3 = srcdlg.m_combo1; str3.MakeUpper();

    // Fill in src window title
    CString spath = pDoc->GetTitle();
    ShortenPath(spath, 30);

    if(replace)
        {
        pDoc->ssel.SetWindowText(spath
            + " replace '" + srcdlg.m_combo1 + "'" +
            " with '" + srcdlg.m_combo2 + "'");
        }
    else
        {
        pDoc->ssel.SetWindowText(spath
            + " searching for '" + srcdlg.m_combo1 + "'");
        }

    // Free storage
    pDoc->ssel.cola.RemoveAll();
    pDoc->ssel.linea.RemoveAll();
    pDoc->ssel.lineb.RemoveAll();

    // Redisplay curson in edit window
    CreateCaret(&caret); ShowCaret();

    // Pre-expand virtual list
    pDoc->ssel.lineb.SetAtGrow(lim, TRUE);

    // Start new search (regex an ucase)
    init_search = TRUE;

    // Go get it
    // --------------------------------------------------------
    for(loop = start ; loop < lim; loop++)
    {
    if(!(loop % 100))
        {
        CString num;
        num.Format("Searching at line %d found %d", loop, items);
        message(num);

        if(YieldToWinEx())
            {
            AfxMessageBox("Aborted search, partial matches shown");
            break;
            }
        }
    // Cancel this loop if user closed dialog
    if(!pDoc->ssel.m_shown)
        {
        //PrintToNotepad("Closed dialalog while search\r\n");
        break;
        }

    // Add lines matching criteria:
    int ccol = 0, found = 0, backwalk = 0;
    found = pView->SearchType(loop, &ccol, &backwalk);

    if(found)
        {
        pDoc->ssel.cola.SetAtGrow(items, ccol);
        pDoc->ssel.linea.SetAtGrow(items, loop + backwalk);
        pDoc->ssel.lineb.SetAtGrow(loop + backwalk, TRUE);

        CString str = pDoc->strlist.GetLine(loop + backwalk);
        ExpandTabs(str);
        pDoc->ssel.slb.AddString(str);

        if(items > 32000)
            {
            AfxMessageBox("Space tight, partial matches shown");
            break;
            }
        if(loop >= row && !high)
            high = items;
        items++;
        }
    }
    Busy(FALSE);

    // --------------------------------------------------------
    if(!items)
        {
        pDoc->ssel.slb.AddString("Not found");
        }
    else
        {
        // Provide selection in none
        if(pDoc->ssel.slb.GetCurSel() == -1)
            {
            pDoc->ssel.slb.SetCurSel(high-1);
            pDoc->ssel.slb.SetCurSel(high);
            }
        }
    // Check all
    int lim2 = pDoc->ssel.slb.GetCount(), loop2;
    for(loop2 = 0; loop2 < lim2; loop2++)
        {
        pDoc->ssel.slb.SetCheck(loop2, 1);
        }
    pDoc->ssel.GotoSel();

    AllowShighlite = 1;
    pDoc->UpdateAllViews(NULL);
    CString num; num.Format("Search found %d items", items);
    message (num);
    in_search = FALSE;
}

//////////////////////////////////////////////////////////////////////
// OnSearchFind

void  CWedView::OnSearchFind()

{
   SearchFile();
}


//////////////////////////////////////////////////////////////////////
// OnSearchReplace

void  CWedView::OnSearchReplace()

{
   SearchFile(TRUE);
}

//
// Get diff menu
//


//////////////////////////////////////////////////////////////////////
// GetDiffMenu

CMenu *CWedView::GetDiffMenu()

{
    int iPos;
    CMenu* pViewMenu = NULL;
    CMenu* pTopMenu = AfxGetMainWnd()->GetMenu();

    for (iPos = pTopMenu->GetMenuItemCount()-1; iPos >= 0; iPos--)
    {
        CMenu* pMenu = pTopMenu->GetSubMenu(iPos);
        if (pMenu && pMenu->GetMenuItemID(0) == ID_COMPILE_MAKE)
        {
            pViewMenu = pMenu;
            break;
        }
    }
    if(!pViewMenu)
        return(NULL);

    //ASSERT(pViewMenu != NULL);

    CMenu* pfMenu = NULL;
    for (iPos = pViewMenu->GetMenuItemCount()-1; iPos >= 0; iPos--)
    {
        pfMenu = pViewMenu->GetSubMenu(iPos);
        if(pfMenu)
            break;
    }
    // ASSERT(pfMenu != NULL);
    return (pfMenu);
}

//////////////////////////////////////////////////////////////////////
// OnViewStopdiffing

void  CWedView::OnViewStopdiffing()

{
    CWedDoc     *doc;
    CWedApp     *app = (CWedApp*)AfxGetApp();
    POSITION Pos = app->pDocTemplate->GetFirstDocPosition();

    for(;;)
        {
        if(!Pos)
            break;
        doc = (CWedDoc*)app->pDocTemplate->GetNextDoc(Pos);
        ASSERT_VALID(doc);
        POSITION pos = doc->GetFirstViewPosition();
        CView *cv = doc->GetNextView(pos);

        ASSERT_VALID(cv);
        ((CWedView*)cv)->other = NULL;
        ((CWedView*)cv)->diff = 0;
        doc->UpdateAllViews(NULL);

        // Set back titles
        CString str2 =  doc->GetTitle();
        CString str3 =  doc->GetPathName();
        if(str3 != str2)
            {
            doc->SetTitle(str3);
            }
        }
}


//////////////////////////////////////////////////////////////////////
// OnEditRecordmacro

void  CWedView::OnEditRecordmacro()

{
        start_record();
}


//////////////////////////////////////////////////////////////////////
// start_record

void  CWedView::start_record()

{

    if(play)
    {
        message("Cannot start recording while playing");
        return;
    }
    if(record)
        {
        // Stop
        modestr = ""; mode(modestr);
        record = FALSE;
        message("Ended recording");
        }
   else
        {
        // Start
        modestr = "REC"; mode(modestr);
        macros[currmac].RemoveAll();
        record = TRUE;
        message("Started recording");
        }
}


//////////////////////////////////////////////////////////////////////
// OnEditPlaymacro

void  CWedView::OnEditPlaymacro()

{
    // if shift is held, animate
    PlayMacro(shift);
}



//////////////////////////////////////////////////////////////////////
// PlayMacro

void  CWedView::PlayMacro(int animate)

{
    int  chh, flag, type, cnt;
    POSITION pos;

    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);

    if(record)
        {
        message("Cannot play back while recording");
        return;
        }
    if(play)
        return;
    play = TRUE;

    if(macros[currmac].IsEmpty())
        {
        message("Nothing to play back");
        goto endd;
        }
    mode("PLAY");

    YieldToWin();
    pos = macros[currmac].GetHeadPosition();
    while(TRUE)
        {
        if (!pos)
            break;
        CString replay =  macros[currmac].GetNext(pos);
        sscanf(replay, "%d %d %d %d", &type, &chh, &cnt, &flag);

        PrintToNotepad("Playing: %d %d %d %d\r\n",
                            type, chh, cnt, flag);

        // Mimic keystrokes in order they got here:
        switch(type)
            {
            case R_DOWN:  OnKeyDown(chh, cnt, flag); break;
            case R_CHAR:  OnChar(chh, cnt, flag);    break;
            case R_UP:    OnKeyUp(chh, cnt, flag);   break;

            case R_SYSDOWN:  OnSysKeyDown(chh, cnt, flag); break;
            case R_SYSCHAR:  OnSysChar(chh, cnt, flag);    break;
            case R_SYSUP:    OnSysKeyUp(chh, cnt, flag);   break;

            default:
                //AfxMessageBox("Invalid macro entry");
                //PrintToNotepad("Error on playing: %d %d %d\r\n", chh, cnt, flag);
                break;
            }
        if(animate)
            {
            if(type == R_UP || type == R_SYSUP)
                {
                // Update the screen after every char
                pDoc->UpdateAllViews(NULL);
                // Stop if needed
                if(YieldToWinEx())
                    {
                    message("Aborted playback");
                    break;
                    }
                }
            Sleep(150);
            }
        else
            {
            if(type == R_UP || type == R_SYSUP)
                {
                // Stop if needed
                if(YieldToWinEx())
                    {
                    message("Aborted playback");
                    break;
                    }
                }
            }
        }
endd:
    mode("");
    play = FALSE;

    // Update the screen after playing back
    pDoc->UpdateAllViews(NULL);  SyncCaret(); YieldToWin();
}


//////////////////////////////////////////////////////////////////////
// OnSearchSelextholdingBuffer1

void  CWedView::OnSearchSelextholdingBuffer1()

{
    SwitchholdingBuffer(1);
}


//////////////////////////////////////////////////////////////////////
// OnSearchSelextholdingBuffer2

void  CWedView::OnSearchSelextholdingBuffer2()

{
    SwitchholdingBuffer(2);
}


//////////////////////////////////////////////////////////////////////
// OnSearchSelextholdingBuffer3

void  CWedView::OnSearchSelextholdingBuffer3()

{
    SwitchholdingBuffer(3);
}


//////////////////////////////////////////////////////////////////////
// OnSearchSelextholdingBuffer4

void  CWedView::OnSearchSelextholdingBuffer4()

{
    SwitchholdingBuffer(4);
}


//////////////////////////////////////////////////////////////////////
// OnSearchSelextholdingBuffer5

void  CWedView::OnSearchSelextholdingBuffer5()

{
    SwitchholdingBuffer(5);
}


//////////////////////////////////////////////////////////////////////
// OnSearchSelextholdingBuffer6

void  CWedView::OnSearchSelextholdingBuffer6()

{
    SwitchholdingBuffer(6);
}


//////////////////////////////////////////////////////////////////////
// OnSearchSelextholdingBuffer7

void  CWedView::OnSearchSelextholdingBuffer7()

{
    SwitchholdingBuffer(7);
}


//////////////////////////////////////////////////////////////////////
// OnSearchSelextholdingBuffer8

void  CWedView::OnSearchSelextholdingBuffer8()

{
    SwitchholdingBuffer(8);
}


//////////////////////////////////////////////////////////////////////
// OnSearchSelextholdingBuffer9

void  CWedView::OnSearchSelextholdingBuffer9()

{
    SwitchholdingBuffer(9);
}


//////////////////////////////////////////////////////////////////////
// OnSearchSelextholdingBuffer10

void  CWedView::OnSearchSelextholdingBuffer10()

{
    SwitchholdingBuffer(0);
}


//////////////////////////////////////////////////////////////////////
// SwitchholdingBuffer

void  CWedView::SwitchholdingBuffer(int buffnum)

{
    CString num;

    buffnum = min(9, buffnum);
    buffnum = max(0, buffnum);

    currhold = buffnum;
    num.Format( " H %02d ", currhold);
    message ("Switched holding buffer");
    hold(num);
}


//////////////////////////////////////////////////////////////////////
// OnMoveNextcharacter

void  CWedView::OnMoveNextcharacter()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    col++;
    SyncCaret();
}


//////////////////////////////////////////////////////////////////////
// OnMovePreviouschar

void  CWedView::OnMovePreviouschar()

{

    if(!col)
        message("At beginning of line");
    else
        col--;

    SyncCaret();
}


//////////////////////////////////////////////////////////////////////
// OnMoveNextline

void  CWedView::OnMoveNextline()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);

        if(row < pDoc->strlist.GetCount()-1)
            row++;
        else
            message("At end of file");
    SyncCaret();
}

//////////////////////////////////////////////////////////////////////
// OnMovePreviousline

void  CWedView::OnMovePreviousline()

{
    if(row)
        row--;
    else
        message("At beginning of file");

    SyncCaret();
}


//////////////////////////////////////////////////////////////////////
// OnMovePagedown

void  CWedView::OnMovePagedown()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);

    if(row >= pDoc->strlist.GetCount()-1)
        {
        message("At end of file"); return;
        }

    RECT rec;
    GetClientRect(&rec) ;
    int height = (rec.bottom - rec.top)/fflf.lfHeight;

    row += height-3;
    row  = min(row, pDoc->strlist.GetCount()-1);

    SyncCaret();
}


//////////////////////////////////////////////////////////////////////
// OnMovePageup

void  CWedView::OnMovePageup()

{
    if(!row)
        {
        message("At beginning of file"); return;
        }
    RECT rec;
    GetClientRect(&rec) ;
    int height = (rec.bottom - rec.top)/fflf.lfHeight;

    row -= height - 3;
    row =  max(row, 0);

    SyncCaret();
}

//////////////////////////////////////////////////////////////////////
// Jump to begin of next word

void CWedView::MoveNextword()

{
    OnMoveNextword();
}

//////////////////////////////////////////////////////////////////////
// OnMoveNextword

void CWedView::OnMoveNextword()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    int pos;

    CString str = pDoc->strlist.GetLine(row);
    int len = str.GetLength();

    // Empty string, jump to the next line
    if(!len)
        {
        row++;  return;
        }

    pos = scr2str(str, col);
    if(pos >= len)
        return;

    // Step to end of current word:
        while(wdelim.Find(str.GetAt(pos)) == -1)
            {
            pos++;
            if(pos >= len)
                goto endd1;
            }
        // Step to end of current space:
        while(wdelim.Find(str.GetAt(pos)) != -1)
            {
            pos++;
            if(pos >= len)
                goto endd1;
            }

   endd1:
    // Jump to the next line if at EOL
    if(pos >= len && row < pDoc->strlist.GetCount()-1)
        {
        row++;  col = 0;
        }
    else
        col = str2scr(str, pos);

    SyncCaret();
}

// Jump to begin of prev word


//////////////////////////////////////////////////////////////////////
// OnMovePreviouseword

void CWedView::OnMovePreviouseword()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    int pos, ontab;
    CString str = pDoc->strlist.GetLine(row);

    int len = str.GetLength();
    if(!len)
        return;

    TabbedPos(str, col, &pos, &ontab);
    pos = min(pos, len-1);

        // Step to beginning of current word:
        while(wdelim.Find(str.GetAt(pos)) == -1)
            {
            if(!pos)
                goto endd2;
            pos--;
            }
        // Step to beginning of this space:
        while(wdelim.Find(str.GetAt(pos)) != -1)
            {
            if(!pos)
                goto endd2;
            pos--;
            }
        // Step to beginning of prevous word:
        while(wdelim.Find(str.GetAt(pos)) == -1)
            {
            if(!pos)
                goto endd2;
            pos--;
            }
        // Step to first char of this word:
        while(wdelim.Find(str.GetAt(pos)) != -1)
            {
            if(pos >= len)
                goto endd2;
            pos++;
            }

   endd2:
    UnTabbedPos(str, pos, &col, &ontab);
    //col = pos;
    SyncCaret();
}


//////////////////////////////////////////////////////////////////////
// OnMoveEndofword

void CWedView::OnMoveEndofword()

{

    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);

    CString str = pDoc->strlist.GetLine(row);
    int pos, len = str.GetLength();

    if(!len)
        goto endd3;

    pos = scr2str(str, col);
    pos = min(pos, str.GetLength()-1);
    pos = max(pos,0);

    // Step to end of current space:
    while(wdelim.Find(str.GetAt(pos)) != -1)
        {
        pos++;
        if(pos >= len)
            goto endd3;
        }
    // Step to end of current word:
    while(wdelim.Find(str.GetAt(pos)) == -1)
        {
        pos++;
        if(pos >= len)
            {
            pos--; break;
            }
        }
    // Step back to last char
    while(wdelim.Find(str.GetAt(pos)) != -1)
        {
        if(!pos)
            goto endd3;
        pos--;
        }

   endd3:
    col = str2scr(str, pos);

    SyncCaret();
}


//////////////////////////////////////////////////////////////////////
// OnMoveBeginningofword

void CWedView::OnMoveBeginningofword()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);

    CString str = pDoc->strlist.GetLine(row);
    int pos, len = str.GetLength();

    pos = scr2str(str, col);
    pos = min(pos, str.GetLength()-1);
    pos = max(pos,0);

    // Step to begin of current space:
    while(wdelim.Find(str.GetAt(pos)) != -1)
        {
        if(!pos)
            goto endd4;
        pos--;
        }
    // Step to begin of current word:
    while(wdelim.Find(str.GetAt(pos)) == -1)
        {
        if(!pos)
            goto endd4;
        pos--;
        }
    // Step forward to first char:
    while(wdelim.Find(str.GetAt(pos)) != -1)
        {
        pos++;
        if(pos >= len)
            goto endd4;
        }

   endd4:
    col = str2scr(str, pos);
    SyncCaret();
}

// Move to next paragraph


//////////////////////////////////////////////////////////////////////
// OnMoveNextparagraph

void CWedView::OnMoveNextparagraph()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    int lcol = 0, lrow = row;
    CString str;

    while(lrow <= pDoc->strlist.GetCount()-1)
        {
        lrow++;
        str = pDoc->strlist.GetLine(lrow);

        // Break on paragraph boundary:
        if(str == "" )
            {
            col = 0;
            message("Moved to end of Paragraph");
            break;
            }

        // Break on block boundary:
        lcol = str.Find('}');
        if(lcol != -1)
            {
            col = lcol;
            message("Moved to end of Block");
            break;
            }
        }
    row = lrow;
    SyncCaret();
}

//////////////////////////////////////////////////////////////////////
// OnMovePreviouseparagraph

void CWedView::OnMovePreviouseparagraph()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    int lcol = col, lrow = row;
    CString str;

    while(lrow)
    {
        lrow--;
        str = pDoc->strlist.GetLine(lrow);

        // Break on paragraph boundary:
        if(str == "" )
        {
            col = 0;
            message("Moved to beginning of Paragraph");
            break;
        }
        // Break on block boundary:
        lcol = str.Find('{');
        if(lcol != -1)
        {
            // Here we move after the '{' to let the work begin
            col = lcol+1;
            message("Moved to beginning of Block");
            break;
        }
    }
    row = lrow;
    SyncCaret();
}

//////////////////////////////////////////////////////////////////////
// OnMoveEndofline

void CWedView::OnMoveEndofline()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CString str = pDoc->strlist.GetLine(row);
    col = str2scr(str, str.GetLength());
    SyncCaret();
    message("Moved to the end of Line");
}

//////////////////////////////////////////////////////////////////////
// OnMoveBeginningofline

void CWedView::OnMoveBeginningofline()
{
    col = 0;
    SyncCaret();
    message("Moved to beginning of Line");
}

//////////////////////////////////////////////////////////////////////
// OnMoveBeginningofpage

void CWedView::OnMoveBeginningofpage()

{
    message("Moved to beginning of Page");
    col = 0; row = srow;
    SyncCaret();
}

//////////////////////////////////////////////////////////////////////
// OnMoveBeginningoffile

void CWedView::OnMoveBeginningoffile()

{
    col = 0;  row = 0;
    SyncCaret();
    message("Moved to beginning of File");
}

//////////////////////////////////////////////////////////////////////
// OnMoveEndofpage

void CWedView::OnMoveEndofpage()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CString str;

    RECT rec;
    GetClientRect(&rec) ;
    int height = (rec.bottom - rec.top)/fflf.lfHeight;
    row = srow + (height - 1);
    OnMoveEndofline();
    SyncCaret();
    message("Moved to end of Page");
}

//////////////////////////////////////////////////////////////////////
// OnMoveEndoffile

void CWedView::OnMoveEndoffile()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CString str;

    row = pDoc->strlist.GetCount()-1;
    OnMoveEndofline();
    SyncCaret();
    message("Moved to end of File");
}

//////////////////////////////////////////////////////////////////////
// OnEditUppercaseword

void CWedView::OnEditUppercaseword()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);

    CString str = pDoc->strlist.GetLine(row);

    if(!str.GetLength())
        goto endd5;

    SaveUndo(this, UNDO_MOD, row, col, str);

    int begin, end, lpos;
    SelWord(str, col, &begin, &end);
    begin = scr2str(str, begin);
    end = scr2str(str, end);

    for(lpos = begin; lpos < end; lpos++)
        str.SetAt(lpos, (char)toupper(str.GetAt(lpos)));

   endd5:

    pDoc->strlist.SetLine(row, str);
    message("Uppercase word");
    pDoc->UpdateAllViews(NULL);
}

//////////////////////////////////////////////////////////////////////
// OnEditLowercaseword

void CWedView::OnEditLowercaseword()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CString str = pDoc->strlist.GetLine(row);

    if(!str.GetLength())
        goto endd6;

    SaveUndo(this, UNDO_MOD, row, col, str);
    int begin, end, lpos;
    SelWord(str, col, &begin, &end);
    begin = scr2str(str, begin);
    end = scr2str(str, end);

    for(lpos = begin; lpos < end; lpos++)
        str.SetAt(lpos, (char)tolower(str.GetAt(lpos)));

   endd6:
    pDoc->strlist.SetLine(row, str);
    message("Lowercase word");

    pDoc->SetModifiedFlag();
    pDoc->UpdateAllViews(NULL);
}

//////////////////////////////////////////////////////////////////////
// OnEditCapitalizeword

void CWedView::OnEditCapitalizeword()

{
    int begin, end, lpos;
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CString str = pDoc->strlist.GetLine(row);
    int len = str.GetLength();

    if(!len)
        {
        message ("Empty line"); return;
        }
    SelWord(str, col, &begin, &end);

    // Convert back to string coordinates
    begin = scr2str(str, begin);
    end = scr2str(str, end);

    if(begin == end)
        {
        message ("Not on word"); return;
        }
    if(begin >= len)
        {
        message ("After EOL"); return;
        }
    SaveUndo(this, UNDO_MOD, row, col, str);

    // Lowercase all
    for(lpos = begin; lpos < end; lpos++)
        {
        str.SetAt(lpos, (char)tolower(str.GetAt(lpos)));
        }
    // Uppercase first
    str.SetAt(begin, (char)toupper(str.GetAt(begin)));

    pDoc->strlist.SetLine(row, str);
    pDoc->SetModifiedFlag();
    message("Capitalize word");
    pDoc->UpdateAllViews(NULL);
}

//////////////////////////////////////////////////////////////////////
// OnEditCuttoholding

void CWedView::OnEditCuttoholding()

{
    CopyToHold(this, TRUE);
}

//////////////////////////////////////////////////////////////////////
// OnEditCopytoholding

void CWedView::OnEditCopytoholding()

{
    CopyToHold(this, FALSE);
}

//////////////////////////////////////////////////////////////////////
// OnEditPasteholding

void CWedView::OnEditPasteholding()

{
    PasteHold(this);
}

//////////////////////////////////////////////////////////////////////
// OnEditStartselectaltl

void  CWedView::OnEditStartselectaltl()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    if(soh == -1)
        {
        // Set markers
        soh = eoh = row;
        message ("Mark set");
        }
    else
        {
        // Reset markers
        soh = eoh = -1;
        soch = eoch = -1;
        message ("Marks unset");
        }
    SyncCaret();  pDoc->UpdateAllViews(NULL);  SyncCaret();
}

//////////////////////////////////////////////////////////////////////
// OnEditStartcolumnselectaltc

void  CWedView::OnEditStartcolumnselectaltc()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    if(soh == -1)
        soh = row;
    else
        soh =-1;

    if(soch == -1)
        {
        // Set
        soch = col;
        eoch = col;
        message ("Column mark set");
        }
    else
        {
        // Reset
        soch = eoch = -1;
        message ("Column mark unset");
        }
    pDoc->UpdateAllViews(NULL); SyncCaret();
}


//////////////////////////////////////////////////////////////////////
// OnSelectCancelselect

void CWedView::OnSelectCancelselect()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    message ("Stopped highlite");
    soh = eoh = -1;
    soch = eoch = -1;
    pDoc->UpdateAllViews(NULL); SyncCaret();
}



//////////////////////////////////////////////////////////////////////
// OnSelectSelectall

void CWedView::OnSelectSelectall()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    soh = 0;
    eoh = row = pDoc->strlist.GetCount()-1;
    pDoc->UpdateAllViews(NULL); SyncCaret();
}


//////////////////////////////////////////////////////////////////////
// InsertClip

void CWedView::InsertClip()

{

}


//////////////////////////////////////////////////////////////////////
// OnSearchCancelfind

void CWedView::OnSearchCancelfind()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    //pDoc->search = "";
    srcdlg.m_combo1 = "";
    pDoc->UpdateAllViews(NULL);
}

//////////////////////////////////////////////////////////////////////
// OnMoveGotoline

void CWedView::OnMoveGotoline()

{
    static      old_goto;
    Cgotoline   gt;

    CString num; num.Format("%d", old_goto);
    gt.m_str    =   num;
    gt.m_prompt =   "Line to Go To";
    gt.caption  =   "Goto Line";

    gt.DoModal();
    row         =   atoi(gt.m_str);
    old_goto    =   row;
    SyncCaret();
}

//Add incremented number to current position

static serial;

//////////////////////////////////////////////////////////////////////
// OnInsertIncrementednumber

void CWedView::OnInsertIncrementednumber()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CString lstr, rstr, num;
    CString str = pDoc->strlist.GetLine(row);

    // Generate number:
    num.Format("%02d", serial);

    // Split line:
    lstr = str.Left(col);
    rstr = str.Right(str.GetLength() - col);

    SaveUndo(this, UNDO_MOD, row, col, str);

    // Output:
    pDoc->strlist.SetLine(row, lstr + num + rstr);
    if(shift)
        col += num.GetLength();
    else
        row++;

    serial++;
    pDoc->UpdateAllViews(NULL);
}

//////////////////////////////////////////////////////////////////////
// OnInsertSetincremnetstartvalue

void CWedView::OnInsertSetincremnetstartvalue()

{
    serial = 0;
      CString num;
    Cgotoline   gt;

    num.Format("%d", serial);
    gt.m_str =  num;
    gt.m_prompt =  "Set starting number for increment";
    gt.caption = "Increment Start Value";
    gt.DoModal();
    serial = atoi(gt.m_str);
}


//////////////////////////////////////////////////////////////////////
// OnMoveGotocolumn

void CWedView::OnMoveGotocolumn()

{
    static      old_num;

    CString num;  num.Format("%d", old_num);

    Cgotoline   gt;
    gt.m_str    =   num;
    gt.m_prompt =   "Column to Go To";
    gt.caption  =   "Goto Column";

    // Open it
    gt.DoModal();

    col         =   atoi(gt.m_str);
    old         =   col;
    SyncCaret();
}

//////////////////////////////////////////////////////////////////////
// OnSearchFindnext

void CWedView::OnSearchFindnext()

{
    CWedDoc*    pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CString     str, str2;
    int         lim, cnt = row+1, ccol;
    CStringEx   str3;

    if( srcdlg.m_esc ||
            (srcdlg.m_combo1 == "" &&
                srcdlg.m_stype != S_FUNCTION)
      )
        {
        message("No active search string");
        return;     // Cancelled
        }
    lim = pDoc->strlist.GetCount() - 1;

    if(srcdlg.m_stype != S_FUNCTION)
        {
        // See if current line has more
        str3 = pDoc->strlist.GetLine(row);
        int col2 =  scr2str(str3, col);

        if((ccol = str3.FindNoCase(srcdlg.m_combo1, col2+1)) != -1)
            {
            col = str2scr(str3, ccol);
            SyncCaret();
            message("Found next on same line");
            return;
            }
        }
    else
        {
        // Skip to next body ...
        while(TRUE)
            {
            if(cnt >= lim)
                {
                message("Reached last searched item");
                break;
                }
            str = pDoc->strlist.GetLine(cnt);
            cnt++;
            if(str == "{")
                break;
            }
        }
    Busy(TRUE);
    // Scan it
    while(TRUE)
        {
        int found;

        if(cnt >= lim)
            {
            message("Reached last searched item");
            break;
            }
        if(!(cnt%100))
            {
            CString num; num.Format("Searching at %d ", cnt);
            message(num);
            }
        str = pDoc->strlist.GetLine(cnt);

        // Find lines matching criteria:
        int ccol = 0, backwalk = 0;
        found = SearchType(cnt, &ccol, &backwalk);
        if(found)
            {
            row = cnt + backwalk;

            if(backwalk)
                str = pDoc->strlist.GetLine(cnt);

            col = str2scr(str, ccol);
            //PrintToNotepad("Found at %d -- %d\r\n", cnt, ccol);
            SyncCaret(1);
            pDoc->UpdateAllViews(NULL);
            message("Found next");
            break;
            }
        cnt++;
        }
    Busy(FALSE);
}

//////////////////////////////////////////////////////////////////////
// OnSearchFindprevious

void CWedView::OnSearchFindprevious()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    int cnt = max(0, row-1);
    CStringEx       str, str2, str3;
    int ccol;

    if( srcdlg.m_esc ||
            (srcdlg.m_combo1 == "" &&
                srcdlg.m_stype != S_FUNCTION)
      )
        {
        message("No active search string");
        return;     // Cancelled
        }

    str2 = srcdlg.m_combo1; // pDoc->search;

    // See if current line has more
    if(srcdlg.m_stype != S_FUNCTION)
    {
    if(col)
        {
        str3 = pDoc->strlist.GetLine(row);
        int col2 =  scr2str(str3, col);

        if((ccol = str3.ReverseFindNoCase(str2, col2-1)) != -1)
            {
            col = str2scr(str3, ccol);
            SyncCaret();
            message("Found previous on same line");
            return;
            }
        }
    }
    Busy(TRUE);
    while(TRUE)
        {
        if(!cnt)
            {
            message("Reached first searched item");
            break;
            }
        if(!(cnt%100))
            {
            CString num; num.Format("Searching at %d ", cnt);
            message(num);
            }
        //str = pDoc->strlist.GetLine(cnt);
        // Find lines matching criteria:
        int ccol = 0, backwalk = 0;
        int found = SearchType(cnt, &ccol, &backwalk);
        if(found)
            {
            row = cnt + backwalk;
            str = pDoc->strlist.GetLine(cnt);
            col = str2scr(str, ccol);
            //PrintToNotepad("Found at %d -- %d\r\n", cnt, ccol);
            pDoc->UpdateAllViews(NULL);  SyncCaret(1);
            message("Found previous");
            break;
            }
        cnt--;
        }
    Busy(FALSE);
}

//////////////////////////////////////////////////////////////////////
// Select word in current line, return coordinates

void CWedView::OnSelectSelectword()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CString  str = pDoc->strlist.GetLine(row);

    int     wbegin, wend;
    SelWord(str, col, &wbegin, &wend);
    if(wbegin < wend)
        {
        //PrintToNotepad("Select word: %s", str.Mid(wbegin, wend));
        soch = wbegin;
        col = eoch = wend -1;
        soh  = row;
        }
    message ("Selected word");
    pDoc->UpdateAllViews(NULL); SyncCaret();
}

//////////////////////////////////////////////////////////////////////
// OnSelectSelectparagraph

void CWedView::OnSelectSelectparagraph()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    int lrow = row, urow = row;
    int max  = pDoc->strlist.GetCount();

    message("Selected paragraph");
    CString str;
    while(TRUE)
        {
        if(!lrow)
            break;
        str = pDoc->strlist.GetLine(lrow);
        if(str == "")
            break;
        lrow--;
        }
    soh = lrow;
    while(TRUE)
        {
        if(urow >= max)
            break;
        str = pDoc->strlist.GetLine(urow);
        if(str == "")
            break;
        urow++;
        }
    row = eoh = urow;
    col = 0;
    pDoc->UpdateAllViews(NULL);
}


//////////////////////////////////////////////////////////////////////
// OnViewFileproperties

void CWedView::OnViewFileproperties()

{
    FileInfo fi;
    fi.v1 = this;
    fi.DoModal();
}


//////////////////////////////////////////////////////////////////////
// OnInsertUser

void CWedView::OnInsertUser()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CString str = pDoc->strlist.GetLine(row);
    SaveUndo(this, UNDO_ADD, row, col, str);
    str = "Peter";
    pDoc->strlist.InsertLine(row, str);
    pDoc->UpdateAllViews(NULL);
}


//////////////////////////////////////////////////////////////////////
// OnEditUppercaseselection

void CWedView::OnEditUppercaseselection()

{
    Caseselection(TRUE);
}


//////////////////////////////////////////////////////////////////////
// OnEditLowercaseselection

void CWedView::OnEditLowercaseselection()

{
    Caseselection(FALSE);
}


// Change the case of selection


//////////////////////////////////////////////////////////////////////
// Caseselection

void CWedView::Caseselection(int updown)

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CString str;
    // Make logical highlite
    int lsoh, leoh;
    if(soh <= eoh)
        {
        lsoh = soh; leoh = eoh;
        }
    else
        {
        leoh = soh; lsoh = eoh;
        }

    if(soh == -1)
        {
        str = pDoc->strlist.GetLine(row);
        SaveUndo(this, UNDO_MOD, row, col, str);
        if(updown)
            str.MakeUpper();
        else
            str.MakeLower();

        pDoc->strlist.SetLine(row, str);
        }
    else
    {
    int loop2;
    for (loop2 = lsoh; loop2 <= leoh; loop2++)
       {
        if(!(loop2 % 100))
            {
            CString num;
            num.Format( "Copy line %d", loop2);
            message(num);
            }
        str = pDoc->strlist.GetLine(loop2);
        SaveUndo(this, UNDO_MOD, loop2, col, str);

        if(updown)
            str.MakeUpper();
        else
            str.MakeLower();
        pDoc->strlist.SetLine(loop2, str);
        }
    }

    if(updown)
        message("Uppercased selection");
    else
        message("Lowercased selection");

    pDoc->UpdateAllViews(NULL);
}


//////////////////////////////////////////////////////////////////////
// OnInsertDatetimeRfcstandarddate

void CWedView::OnInsertDatetimeRfcstandarddate()

{
    InsertDate("%a %b %d %H:%M:%S %Y %z ");
}


//////////////////////////////////////////////////////////////////////
// OnInsertDatetimeMmddyyhhmmss

void CWedView::OnInsertDatetimeMmddyyhhmmss()

{
    InsertDate("%m/%d/%y %H:%M:%S ");
}


//////////////////////////////////////////////////////////////////////
// OnInsertDatetimeDdmmyyhhmmss

void CWedView::OnInsertDatetimeDdmmyyhhmmss()

{
    InsertDate("%d-%m-%y %H:%M:%S ");
}


//////////////////////////////////////////////////////////////////////
// OnInsertDatetimeTimehhmmss

void CWedView::OnInsertDatetimeTimehhmmss()

{
    InsertDate("%c ");
}


//////////////////////////////////////////////////////////////////////
// OnInsertDatetimeWeekday

void CWedView::OnInsertDatetimeWeekday()

{
    InsertDate("%A ");
}


//////////////////////////////////////////////////////////////////////
// OnInsertDatetimeMonthname

void CWedView::OnInsertDatetimeMonthname()

{
    InsertDate("%B ");
}


//////////////////////////////////////////////////////////////////////
// OnInsertDatetimeDateformattedaslocale

void CWedView::OnInsertDatetimeDateformattedaslocale()

{
    InsertDate("%c ");
}


//////////////////////////////////////////////////////////////////////
// InsertDate

void CWedView::InsertDate(char *format)

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CString str, lstr, rstr, nstr, dstr;
    str = pDoc->strlist.GetLine(row);
    CTime tt = CTime::GetCurrentTime();

    lstr = str.Left(col);
    rstr = str.Right(str.GetLength() - col);
    dstr = tt.Format(format);
    SaveUndo(this, UNDO_MOD, row, col, str);
    nstr = lstr + dstr + rstr;
    pDoc->strlist.SetLine(row, nstr);
    col += nstr.GetLength() - str.GetLength();

    pDoc->SetModifiedFlag();
	pDoc->UpdateAllViews(NULL);

}


//////////////////////////////////////////////////////////////////////
// OnInsertPagefeedmark

void CWedView::OnInsertPagefeedmark()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    SaveUndo(this, UNDO_ADD, row, col, "");
    pDoc->strlist.InsertLine(row, (CString)"\xc");
    pDoc->UpdateAllViews(NULL);
}


//////////////////////////////////////////////////////////////////////
// OnInsertByte

void CWedView::OnInsertByte()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CString str = pDoc->strlist.GetLine(row);

    static  unsigned char old;
    unsigned char ins;

    CString num;
    Cgotoline   gt;

    num.Format("%u", old);
    gt.m_str =  num;
    gt.m_prompt =  "Inser BYTE char";
    gt.caption  =  "Enter decimal charater number";
    gt.DoModal();

    if(!gt.m_esc)
    {
        SaveUndo(this, UNDO_MOD, row, col, str);

        CString lstr, rstr, nstr, dstr;
        lstr = str.Left(col);
        rstr = str.Right(str.GetLength() - col);
        ins = atoi(gt.m_str) % 255;
        old = ins;
        nstr = lstr + (char)ins + rstr;
        pDoc->strlist.SetLine(row, nstr);
        col++;
        pDoc->UpdateAllViews(NULL);
    }
}


//////////////////////////////////////////////////////////////////////
// OnInsertFunction

void CWedView::OnInsertFunction()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CString str, pad;

    SaveUndo(this, UNDO_ADD, row, col, "");
    pDoc->strlist.InsertLine(row++, pad + "");

    SaveUndo(this, UNDO_ADD, row, col, "");
    str.Format("// function%d ", serial);
    pDoc->strlist.InsertLine(row++, str);

    SaveUndo(this, UNDO_ADD, row, col, "");
    pDoc->strlist.InsertLine(row++, pad+"//");

    SaveUndo(this, UNDO_ADD, row, col, "");
    pDoc->strlist.InsertLine(row++, pad);

    SaveUndo(this, UNDO_ADD, row, col, "");
    str.Format("int function%d (int arg1, int arg2)", serial++);
    pDoc->strlist.InsertLine(row++, pad+str);

    SaveUndo(this, UNDO_ADD, row, col, "");
    pDoc->strlist.InsertLine(row++, pad + "{");

    SaveUndo(this, UNDO_ADD, row, col, "");
    pDoc->strlist.InsertLine(row++, pad);

    SaveUndo(this, UNDO_ADD, row, col, "");
    pDoc->strlist.InsertLine(row++, pad + "}");

    // Position cursor to a good place
    row -= 2; col = col + 4;

    pDoc->SetModifiedFlag();
    pDoc->UpdateAllViews(NULL);  SyncCaret();
}


//////////////////////////////////////////////////////////////////////
// OnInsertForloop

void CWedView::OnInsertForloop()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CString str, pad(' ', col);

    SaveUndo(this, UNDO_ADD, row, col, "");
    str.Format("for (var%d = 0; var%d < var%d; var%d++)",
            serial, serial, serial+1, serial);
    serial+=2;
    pDoc->strlist.InsertLine(row++, pad+str);

    SaveUndo(this, UNDO_ADD, row, col, "");
    pDoc->strlist.InsertLine(row++, pad + "    {");

    SaveUndo(this, UNDO_ADD, row, col, "");
    pDoc->strlist.InsertLine(row++, pad + "");

    SaveUndo(this, UNDO_ADD, row, col, "");
    pDoc->strlist.InsertLine(row++, pad + "    }");

    // Position cursor to a good place
    row -= 2; col = col + 4;

    pDoc->SetModifiedFlag();
    pDoc->UpdateAllViews(NULL); SyncCaret();
}


//////////////////////////////////////////////////////////////////////
// OnInsertIfcondition

void CWedView::OnInsertIfcondition()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CString str, pad(' ', col);

    SaveUndo(this, UNDO_ADD, row, col, "");
    str.Format("if (var%d < var%d)", serial, serial+1);
    serial+=2;
    pDoc->strlist.InsertLine(row++, pad + str);

    SaveUndo(this, UNDO_ADD, row, col, "");
    pDoc->strlist.InsertLine(row++, pad + "    {");

    SaveUndo(this, UNDO_ADD, row, col, "");
    pDoc->strlist.InsertLine(row++, pad + "");

    SaveUndo(this, UNDO_ADD, row, col, "");
    pDoc->strlist.InsertLine(row++, pad + "    }");

    // Position cursor to a good place
    row -= 2; col = col + 4;

    pDoc->SetModifiedFlag();
    pDoc->UpdateAllViews(NULL); SyncCaret();
}


//////////////////////////////////////////////////////////////////////
// OnSettingsSetupwed

void CWedView::OnSettingsSetupwed()

{
    CPropertySheet ps("Wed Setup");
    Page1   p1;
    Page2   p2;

    ps.m_psh.dwFlags |=  PSH_NOAPPLYNOW;
    //  ps.m_psh.dwFlags &=  PSH_HASHELP;

    ps.AddPage(&p1);
    ps.AddPage(&p2);

    ps.DoModal();
}


//////////////////////////////////////////////////////////////////////
// OnEditLoadmacro

void CWedView::OnEditLoadmacro()

{
    CFileDialog cdf(TRUE);
    CString droot, dresult;

    droot.Format("%smacros", approot);

    cdf.m_ofn.lpstrInitialDir = droot;
    cdf.m_ofn.lpstrFilter = Mfilter;
    cdf.m_ofn.lpstrFile = "*.mac";
    cdf.m_ofn.nFilterIndex = 1;

    cdf.DoModal();
    dresult = cdf.GetPathName();

    CFile cf;
    if( cf.Open( dresult, CFile::modeRead ))
        {
        //cstringlist
        macros[currmac].RemoveAll();

        CArchive ar( &cf, CArchive::load);
        macros[currmac].Serialize(ar);
        message("Loaded Macro");
        }
}


//////////////////////////////////////////////////////////////////////
// OnEditSavemacro

void CWedView::OnEditSavemacro()

{
    CFileDialog cdf(FALSE);
    CString droot, dresult, dfile, dext;

    droot.Format("%smacros\\", approot);

    //cdf.m_ofn.lStructSize = sizeof(OPENFILENAME);
    cdf.m_ofn.lpstrInitialDir = droot;
    cdf.m_ofn.lpstrFilter = Mfilter;
    cdf.m_ofn.lpstrFile = "*.mac";
    cdf.m_ofn.nFilterIndex = 1;

    cdf.DoModal();

    dresult = cdf.GetPathName();
    dfile = cdf.GetFileName();
    dext = cdf.GetFileExt();

    // append ".mac" if empty
    if(dext == "")
        dresult += ".mac";

    //PrintToNotepad("Macro file1: %s\r\n", dresult);
    CFile cf;
    if( cf.Open( dresult, CFile::modeCreate | CFile::modeWrite ))
        {
        CArchive ar( &cf, CArchive::store);
        macros[currmac].Serialize(ar);
        message("Saved Macro");
        }
}

//////////////////////////////////////////////////////////////////////
// OnActivateView

	static int firstact = 0;

void CWedView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)

{
 	if(comline & !firstact)
        AfxGetMainWnd()->PostMessage(WM_COMMAND, ID_WINDOW_TILE_VERT, 0);
    firstact = TRUE;

    CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
    return;

#if 0
    if(pActivateView)
        {
        ASSERT_VALID(pActivateView);
        CWedDoc* pDoc =
            ((CWedView *)pActivateView)->GetDocument();
        ASSERT_VALID(pDoc);

        ((CWedView *)pActivateView)->SyncCaret();
        //pDoc->UpdateAllViews(NULL);
        }
    if(pDeactiveView)
        {
        ASSERT_VALID(pDeactiveView);
        CWedDoc* pDoc =
            ((CWedView *)pDeactiveView)->GetDocument();

        ((CWedView *)pDeactiveView)->SyncCaret();
        //pDoc->UpdateAllViews(NULL);
        }
#endif

}


//////////////////////////////////////////////////////////////////////
// OnViewCococodecolector

void CWedView::OnViewCococodecolector()

{
    static created = 0;

    if(!created)
        {
        co.Create(IDD_DIALOG9);
        created = TRUE;
        }
    else
        co.ShowWindow(SW_RESTORE);
}

//////////////////////////////////////////////////////////////////////
// OnCompileMake

void CWedView::OnCompileMake()

{
    SaveAllDocs();
    // Start compiling ...
    message("Sending build command ...");
    m_ole.SendBuild();
}

//////////////////////////////////////////////////////////////////////
// OnCompileExecutedevstudioproject

void CWedView::OnCompileExecutedevstudioproject()

{
    static in_compile;

    if(in_compile)
        return;

    in_compile = TRUE;
    SaveAllDocs();
    message("Sending build command ...");
    m_ole.SendBuild();

    // Execute recent build...
    message("Sending execute command ...");
    m_ole.SendExec();

    in_compile = FALSE;
}


//////////////////////////////////////////////////////////////////////
// OnFileSaveall

void CWedView::OnFileSaveall()

{
    SaveAllDocs();
}



//////////////////////////////////////////////////////////////////////
// OnViewViewmacroheads

void CWedView::OnViewViewmacroheads()

{
    CString ee = "empty";
    HoldHead hh;
    hh.m_edit1  =  macros[0].IsEmpty() ? ee: macros[0].GetHead() ;
    hh.m_edit2  =  macros[1].IsEmpty() ? ee: macros[1].GetHead() ;
    hh.m_edit3  =  macros[2].IsEmpty() ? ee: macros[2].GetHead() ;
    hh.m_edit4  =  macros[3].IsEmpty() ? ee: macros[3].GetHead() ;
    hh.m_edit5  =  macros[4].IsEmpty() ? ee: macros[4].GetHead() ;
    hh.m_edit6  =  macros[5].IsEmpty() ? ee: macros[5].GetHead() ;
    hh.m_edit7  =  macros[6].IsEmpty() ? ee: macros[6].GetHead() ;
    hh.m_edit8  =  macros[7].IsEmpty() ? ee: macros[7].GetHead() ;
    hh.m_edit9  =  macros[8].IsEmpty() ? ee: macros[8].GetHead() ;
    hh.m_edit10 =  macros[9].IsEmpty() ? ee: macros[9].GetHead() ;
    hh.m_edit11 = "Head of macros";
    hh.DoModal();
}


//////////////////////////////////////////////////////////////////////
// OnSelectMarkblock

void CWedView::OnSelectMarkblock()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    int lrow = row, urow = row;
    int max  = pDoc->strlist.GetCount();

    message("Selected block");
    CString str;
    int depth = 0;

    while(TRUE)
    {
        if(!lrow)
            break;
        str = pDoc->strlist.GetLine(lrow);
        if(str.Find('{') != -1)
            depth--;

        if(depth < 0)
            break;

        if(str.Find('}') != -1)
            depth++;

        lrow--;

    }
    soh = lrow;
    depth = 0;
    while(TRUE)
    {
        if(urow >= max)
            break;
        urow++;

        str = pDoc->strlist.GetLine(urow);
        if(str.Find('}') != -1)
            depth--;

        if(depth < 0)
            break;

        if(str.Find('{') != -1)
            depth++;
    }
    row = eoh = urow;
    col = 0;
    CString num;
    num.Format("Selected %d lines", eoh - soh);
    message(num);

    pDoc->UpdateAllViews(NULL); SyncCaret();
}


//////////////////////////////////////////////////////////////////////
// SwitchToNext

void CWedView::SwitchToNext()

{
        // Next buffer
        int got = 0;
        CWedDoc*  pDoc = NULL;
        CMultiDocTemplate* pDocTemplate =
                ((CWedApp*)AfxGetApp())->pDocTemplate;
        POSITION Pos =  pDocTemplate->GetFirstDocPosition();
        for(;;)
        {
        if(!Pos)
            break;
        CWedDoc* doc = (CWedDoc*)pDocTemplate->GetNextDoc(Pos);

        if(!doc)
            continue;
        ASSERT_VALID(doc);

        POSITION pos2 = doc->GetFirstViewPosition();
        CWedView *cv = (CWedView*)doc->GetNextView(pos2);

        if(got == 1)
            {
            pMainFrame->MDIActivate (cv->GetParent());
            got = 2;
            break;
            }
        if(cv == this)
            {
            got = 1;
            }
        }
        if(got != 2)
            {
            // wrapped around buffers, switch:
            POSITION Pos =  pDocTemplate->GetFirstDocPosition();
            CWedDoc* doc = (CWedDoc*)pDocTemplate->GetNextDoc(Pos);
            ASSERT_VALID(doc);
            POSITION pos2 = doc->GetFirstViewPosition();
            CWedView *cv = (CWedView*)doc->GetNextView(pos2);
            ASSERT_VALID(cv);
            pMainFrame->MDIActivate (cv->GetParent());
            }
        message ("Switched to next buffer");
}

//////////////////////////////////////////////////////////////////////
// OnWindowsNextbuffer

void CWedView::OnWindowsNextbuffer()

{
    SwitchToNext();
}

//////////////////////////////////////////////////////////////////////
// Show busy cursor

void CWedView::Busy(int on)
{
    if(on)
        {
        m_busy = TRUE;
        SetCursor(WaitCursor);
        }
    else
        {
        m_busy = FALSE;
        SetCursor(NormalCursor);
        }
}

//////////////////////////////////////////////////////////////////////
// OnViewFullscreen

void CWedView::OnViewFullscreen()

{
    if(GetParent() != parent)
        UnFullscreen();
    else
        ReFullscreen();
}

//////////////////////////////////////////////////////////////////////
// ReFullscreen

void CWedView::ReFullscreen()

{
    // Make the top window our owner
    SetParent(GetDesktopWindow());

    RECT rec;
    SystemParametersInfo(SPI_GETWORKAREA, 0 , &rec, 0);

    int mmm = GetSystemMetrics(SM_CYMENUSIZE);
    int xxx = rec.right - rec.left;
    int yyy = (rec.bottom - rec.top) - mmm;

    MoveWindow (rec.left, rec.top, xxx, yyy);

    // So users will know
    SetWindowText("Wed Full Screen");
    CreateCaret(&caret); ShowCaret();
    message("Full screen view (Control-F or ESC for normal view)");
}

//////////////////////////////////////////////////////////////////////
// UnFullscreen

void CWedView::UnFullscreen()

{
    // See if it is full screenized
    if(GetParent() == parent)
        return;  // no

    BOOL maxi;
    CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;

    // Make the original owner our owner
    SetParent(parent);

    // Send resize to update it properly
    pFrame->MDIGetActive(&maxi);
    if(maxi)
        {
        // End with maxi
        pFrame->MDIRestore (GetParent());
        pFrame->MDIMaximize(GetParent());
        }
    else
        {
        // End with medi
        pFrame->MDIMaximize(GetParent());
        pFrame->MDIRestore (GetParent());
        }
    // System resource, re get it
    CreateCaret(&caret); ShowCaret(); SyncCaret();
    YieldToWin();

    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    pDoc->UpdateAllViews(NULL);
    message("Exited Full screen view");
}

//////////////////////////////////////////////////////////////////////
// OnFileMultiopen

void CWedView::OnFileMultiopen()

{
    OpenSource(srcdir);
}

//////////////////////////////////////////////////////////////////////
// OnSettingsTogglescrollbars

void CWedView::OnSettingsTogglescrollbars()

{
    static on = 1;
    if(on)
        ShowScrollBar(SB_BOTH, 0), on = !on;
    else
        ShowScrollBar(SB_BOTH, 1), on = !on;
}

// Reverse colors

//////////////////////////////////////////////////////////////////////
// OnSettingsReverseit

void CWedView::OnSettingsReverseit()

{
    int tmp = fgcol;
    fgcol = bgcol;
    bgcol = tmp;

    // Tell all documents about the change
    POSITION Pos =
        ((CWedApp*)AfxGetApp())->pDocTemplate->
                GetFirstDocPosition();
    for(;;)
        {
        if(!Pos)
            break;
        CWedDoc* doc = (CWedDoc*)
            ((CWedApp*)AfxGetApp())->pDocTemplate->
                    GetNextDoc(Pos);
        doc->UpdateAllViews(NULL);
        }
}

//////////////////////////////////////////////////////////////////////
// OnMacroAnimatemacro

void CWedView::OnMacroAnimatemacro()

{
    PlayMacro(TRUE);
}

//////////////////////////////////////////////////////////////////////
// OnEditCleannonascii
// Clean out char < 32

void CWedView::OnEditCleannonascii()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);

    int changed = FALSE;
    CString str, str2;
    int lim = pDoc->strlist.GetCount();

    // Iterate every line
    for(int loop = 0; loop < lim; loop++)
        {
        str = pDoc->strlist.GetLine(loop);
        int lim2 = str.GetLength();
        str2 = "";

        for(int loop2 = 0; loop2 < lim2; loop2++)
            {
            char cc = str.GetAt(loop2);
            if(cc >= 32)
                  str2 += cc;
            else
                changed = TRUE;
            }
        pDoc->strlist.SetLine(loop, str2);
        }

    // Tell the doc if changed
    if(changed)
        pDoc->SetModifiedFlag(TRUE);

    pDoc->UpdateAllViews(NULL);
}


//////////////////////////////////////////////////////////////////////
// OnEditWraptowindow
// wrap to 80 for the moment

void CWedView::OnEditWraptowindow()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);

    int changed = FALSE;
    CString str, str2, str3;
    int lim = pDoc->strlist.GetCount();

    // Iterate every line
    for(int loop = 0; loop < lim; loop++)
        {
        int count = 0;
        str = pDoc->strlist.GetLine(loop);
        int lim2 = str.GetLength();

        if(lim2 > 80)
            {
            changed = TRUE;
            char cc;
            pDoc->strlist.RemoveLine(loop);

			// Reflect changes
			if(loop)   loop--;

            while(TRUE)
                {
                int len = str.GetLength();

                if(len < 80 && len > 0)
					{
					pDoc->strlist.InsertLine(loop++, str);
					lim++;
                    break;
					}
                // Find space backwards
                int cutpoint = min(80, len-1);
                while(TRUE)
                    {
                    if(!cutpoint)
                        break;

                    cc = str.GetAt(cutpoint);
                    if (cc == ' ' || cc == '\t')
                        break;

                    cutpoint--;
                    }
                // No safe cutpoint found, force cut at 80
                if(!cutpoint)
                    cutpoint = 80;

                str2 = str.Left(cutpoint);

                // Sitting on space, do not carry to next line
                if(cc == ' '  || cc == '\t')
                    cutpoint++;

                str3 = str.Right(str.GetLength() - cutpoint);

                //PrintToNotepad("str  ===== %s\r\n", str3);
                //PrintToNotepad("str2 ===== = %s\r\n", str2);

                str = str3;

                pDoc->strlist.InsertLine(loop++, str2);
				lim++;
                }
            }
        }

    // Tell the doc if changed
    if(changed)
        pDoc->SetModifiedFlag(TRUE);

    pDoc->UpdateAllViews(NULL);
}


//////////////////////////////////////////////////////////////////////
// OnEditWeedemptylines
// Weed empty

void CWedView::OnEditWeedemptylines()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    int changed = FALSE, empty = 0;
    int lim = pDoc->strlist.GetCount();

    SaveUndo(this, UNDO_NOP, row, col, "");

    // Iterate every line
    for(int loop = lim; loop; loop--)
        {
        CString str = pDoc->strlist.GetLine(loop);
        int count = 0;

        if(!str.GetLength())
            empty++;
        else
            empty = 0;

        if(empty > 3)
            {
            changed = TRUE;

            SaveUndo(this, UNDO_DEL | UNDO_BLOCK, loop, col, str);
            pDoc->strlist.RemoveLine(loop);
            }
        }

    // Tell the doc if changed
    if(changed)
        pDoc->SetModifiedFlag(TRUE);

    pDoc->UpdateAllViews(NULL);
}


//////////////////////////////////////////////////////////////////////
// Escape key pressed

void CWedView::Esc()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    int want = FALSE;

    // Cancel record
    if(record)
        start_record();

    // Cancel search selection:
    if(AllowShighlite)
        {
        AllowShighlite = 0;
        want = TRUE;
        }
    // Cancel highlite selection:
    if(soh != -1)
        {
        want = TRUE;
        soh =  eoh =  soch =  eoch = -1;
        record = FALSE;
        modestr = "";
        mode(modestr);
        }
    if(want)
        {
        message ("Cancelled highlite from selections, searches and recording");
        pDoc->UpdateAllViews(NULL);
        }
    else
        {
        // If did not have to cancel, then restore window
        UnFullscreen();
        }
}

//////////////////////////////////////////////////////////////////////
// Del

void CWedView::Del()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CString lstr, rstr;

    if(soh != -1)
        {
        // Delete lines
        DeleteSelection(this);
        soh = eoh = -1;
        }
    else
        {
        // Delete one character or pull in prev line
        CString str = pDoc->strlist.GetLine(row);

        // If end of line, pull in previous line:
        int real, ontab;
        TabbedPos(str, col, &real, &ontab);

        if(real >= str.GetLength())
            {
            // Discard this action, stop hitmode
            if(hitmode)
                {
                CancelHit();
                return;
                }
            // Pull in prev line
            int old = row;
            SaveUndo(this, UNDO_NOOP, row, col, "");
            SaveUndo(this, UNDO_MOD | UNDO_BLOCK, row, col, str);
            // Extend line to current pos if we point after the end
            int diff = real - str.GetLength();
            if(diff > 0)
                {
                CString spaces(' ', diff);  str+=spaces;
                }
            // Get next line
            rstr = pDoc->strlist.GetLine(row+1);
            SaveUndo(this, UNDO_DEL | UNDO_BLOCK,
                                        row+1, col, rstr);

            // Remove leading spaces from next line
            rstr.TrimLeft();

            // Grab it and set it to current line
            pDoc->strlist.SetLine(row, str + " " + rstr);

            // Remove next line:
            DeleteLine(this, row+1);
            row = old;
            }
        else
            {
            // Split line, reassemble:
            SaveUndo(this, UNDO_MOD, row, col, str);

            // Sitting on tabbed region, replace tab with spaces
            if(ontab)
                {
                OnTabbed(str, ontab);
                // Recalc
                TabbedPos(str, col, &real, &ontab);
                }
            lstr = str.Left(real);
            rstr = str.Right(str.GetLength() - (real+1) );
            pDoc->strlist.SetLine(row, lstr+rstr);
            }
        }
    pDoc->SetModifiedFlag();
    pDoc->UpdateAllViews(NULL); SyncCaret();
}

//////////////////////////////////////////////////////////////////////
// BackSpace

void CWedView::BackSpace()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CString lstr, rstr;
    CString str = pDoc->strlist.GetLine(row);

    if(col)
        {
        // Split line, reassemble:
        str = pDoc->strlist.GetLine(row);

        int real, ontab;
        TabbedPos(str, col, &real, &ontab);

        if(real >  str.GetLength())
            {
            if(col)
                col--;
            message("Backspace on dead area");
            goto endd;
            }
        SaveUndo(this, UNDO_MOD, row, col, str);

        // Sitting on tabbed region, replace tab with spaces
        if(ontab)
            {
            int dummy;
            OnTabbed(str, ontab);
            // Recalc
            TabbedPos(str, col, &real, &dummy);
            }

        // Assemble the two parts
        lstr = str.Left(real-1);  rstr = str.Right(str.GetLength() - real);
        pDoc->strlist.SetLine(row, lstr + rstr);

        // Adjust cursor position
        if(str.GetAt(real-1) == '\t')
            {
            UnTabbedPos(str, real-1, &col, &ontab);
            }
        else
            col--;
endd:
        // Communicate changes
        pDoc->UpdateAllViews(NULL); SyncCaret();
        pDoc->SetModifiedFlag();
        }
    else
        {
        // Wrap to prev line
        if(backwrap)
            {
            if(row)
                {
                SaveUndo(this, UNDO_NOOP, row, col, "");
                str = pDoc->strlist.GetLine(row);

                SaveUndo(this, UNDO_DEL | UNDO_BLOCK,
                                            row, col, str);
                DeleteLine(this, row);

                row--;
                CString str2 = pDoc->strlist.GetLine(row);
                SaveUndo(this, UNDO_MOD | UNDO_BLOCK,
                                            row, col, str2);
                pDoc->strlist.SetLine(row, str2 + str);
                col = str2.GetLength();

                // Communicate changes
                pDoc->UpdateAllViews(NULL); SyncCaret();
                pDoc->SetModifiedFlag();
                }
            else
                {
                message ("Already at the beginning of file");
                }
            }
        else
            {
            message ("Already at the beginning of line");
            }
        }
}

//////////////////////////////////////////////////////////////////////
// OnInsertDeleteatcursor

void CWedView::OnInsertDeleteatcursor()

{
    Del();
}

//////////////////////////////////////////////////////////////////////
// OnInsertDeletebeforecursor

void CWedView::OnInsertDeletebeforecursor()

{
    BackSpace();
}

//////////////////////////////////////////////////////////////////////
// OnInsertDeleteline

void CWedView::OnInsertDeleteline()

{
    DelLine();
}

//////////////////////////////////////////////////////////////////////
// DelLine

void CWedView::DelLine()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CString str = pDoc->strlist.GetLine(row);

    SaveUndo(this, UNDO_DEL, row, col, str);
    DeleteLine(this, row);

    pDoc->SetModifiedFlag();
    pDoc->UpdateAllViews(NULL); SyncCaret();
    message ("Deleted line");
}


//////////////////////////////////////////////////////////////////////
// OnInsertDeletetillendofline

void CWedView::OnInsertDeletetillendofline()

{
    KillToTol();
}

//////////////////////////////////////////////////////////////////////
// KillToTol

void CWedView::KillToTol()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CString str = pDoc->strlist.GetLine(row);
    CString lstr;

    str = pDoc->strlist.GetAt(pDoc->strlist.FindIndex(row));
    SaveUndo(this, UNDO_MOD, row, col, str);
    int pos = scr2str(str, col);
    lstr = str.Left(pos);
    pDoc->strlist.SetLine(row, lstr);
    pDoc->SetModifiedFlag();
    pDoc->UpdateAllViews(NULL); SyncCaret();
    message("Cleared till end of line");
}

//////////////////////////////////////////////////////////////////////
// OnInsertCSwitchcase

void CWedView::OnInsertCSwitchcase()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CString str, pad(' ', col);

    SaveUndo(this, UNDO_ADD, row, col, "");
    str.Format( "switch(var%d)",
            serial, serial, serial+1, serial);
    serial+=2;
    pDoc->strlist.InsertLine(row++, pad+str);

    SaveUndo(this, UNDO_ADD, row, col, "");
    pDoc->strlist.InsertLine(row++, pad + "    {");

    SaveUndo(this, UNDO_ADD, row, col, "");
    pDoc->strlist.InsertLine(row++, pad + "    case CONST1:");

    SaveUndo(this, UNDO_ADD, row, col, "");
    pDoc->strlist.InsertLine(row++, pad + "        break;");

    SaveUndo(this, UNDO_ADD, row, col, "");
    pDoc->strlist.InsertLine(row++, pad + "");

    SaveUndo(this, UNDO_ADD, row, col, "");
    pDoc->strlist.InsertLine(row++, pad + "    default:");

    SaveUndo(this, UNDO_ADD, row, col, "");
    pDoc->strlist.InsertLine(row++, pad + "        break;");

    SaveUndo(this, UNDO_ADD, row, col, "");
    pDoc->strlist.InsertLine(row++, pad + "    }");

    // Position cursor to a good place
    row -= 8; col = col + 7;

    pDoc->SetModifiedFlag();
    pDoc->UpdateAllViews(NULL); SyncCaret();
}


//////////////////////////////////////////////////////////////////////
// OnInsertCTemplate
// Insert C template at cursor

void CWedView::OnInsertCTemplate()

{
    DoTemplate("template.c");
}


//////////////////////////////////////////////////////////////////////
// OnInsertJavaTemplate
// Insert Java template at cursor

void CWedView::OnInsertJavaTemplate()

{
    DoTemplate("template.java");
}

//////////////////////////////////////////////////////////////////////
// DoTemplate
// Insert template file at cursor

void CWedView::DoTemplate(const char *file)

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CString str, num, droot;

    droot.Format("%swed\\data\\%s", approot, file);

    CFile cf;
    if( cf.Open(droot, CFile::modeRead ))
        {
        num.Format("Reading template %s", droot);
        message(num);
        CArchive ar( &cf, CArchive::load);

        SaveUndo(this, UNDO_NOOP, row, col, "");

        while(TRUE)
            {
            if(!ar.ReadString(str))
                break;
            SaveUndo(this, UNDO_ADD | UNDO_BLOCK, row, col, "");
            pDoc->strlist.InsertLine(row++, str);
            }
        }
    else
        {
        num.Format("Cannot open template\n%s\nPlease create one.", droot);
        AfxMessageBox(num);
        }
    pDoc->SetModifiedFlag();
    pDoc->UpdateAllViews(NULL); SyncCaret();
}

//////////////////////////////////////////////////////////////////////

void CWedView::OnSettingsSearchhighlitecolorfg()

{
    SetColor(&srcc);
}

//////////////////////////////////////////////////////////////////////

void CWedView::OnSettingsCommenthighlitecolor()

{
    SetColor(&comm);
}

//////////////////////////////////////////////////////////////////////

void CWedView::OnViewGotonextdifference()

{
    if(!diff)
        {
        AfxMessageBox("Not diffing");
        return;
        }

    CWedDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    CWedDoc* pDoc2 = other->GetDocument();
    ASSERT_VALID(pDoc2);

    int found = FALSE;
    int loop = row;
    int lim  = diffa.GetSize();

    // Step out of current diff
    while(TRUE)
        {
        if(loop >= lim)
            break;
        if(!diffa.GetAt(loop))
            break;
        loop++;
    }
    // Walk until new diff
    while(TRUE)
        {
        if(loop >= lim)
            break;

        if(diffa.GetAt(loop))
            {
            // Found
            found = TRUE;
            row = loop;
            pDoc->UpdateAllViews(NULL); SyncCaret(3);

            // Reflect selection on other document
            other->row = loop;
            other->SyncCaret(3);
            pDoc2->UpdateAllViews(NULL);
            break;
            }
        loop++;
        }

    if(found)
        message("Found next diff");
    else
        message("No more differences");
}

//////////////////////////////////////////////////////////////////////

void CWedView::OnViewGotopreviousdifference()

{
    if(!diff)
        {
        AfxMessageBox("Not diffing");
        return;
        }

    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CWedDoc* pDoc2 = other->GetDocument();
    ASSERT_VALID(pDoc2);

    int found = FALSE;
    int loop = row;
    int lim  = diffa.GetSize();

    // Step out of current diff
    while(TRUE)
        {
        if(!loop)
            break;
        if(!diffa.GetAt(loop))
            break;
        loop--;
    }
    // Walk until new diff
    while(TRUE)
        {
        if(!loop)
            break;

        if(diffa.GetAt(loop))
            {
            // Found, step to begin of current diff
            while(TRUE)
                {
                if(!loop)
                    break;
                if(!diffa.GetAt(loop))
                    {
                    loop++;
                    break;
                    }
                loop--;
                }
            found = TRUE;
            row = loop;
            pDoc->UpdateAllViews(NULL);

            // Reflect selection on other document
            other->row = loop;
            other->SyncCaret(3);
            pDoc2->UpdateAllViews(NULL);
            break;
            }
        loop--;
        }

    if(found)
        message("Found previous diff");
    else
        message("No more differences");
}

void CWedView::OnSettingsDiffaddcolor()

{
    SetColor(&cadd);
}

void CWedView::OnSettingsDiffchangedcolor()

{
    SetColor(&cchg);
}

void CWedView::OnSettingsDiffdelcolor()

{
    SetColor(&cdel);
}

void CWedView::OnViewFilebufers()

{
    ShowBuffers();
}


void CWedView::OnMove(int x, int y)

{
    PrintToNotepad("Moving CWedView %d %d\r\n", x ,y);

    CView::OnMove(x, y);

    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    pDoc->UpdateAllViews(NULL);
    SyncCaret();
    YieldToWin();
}

BOOL CWedView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)

{
    // it is like a bad kludge, but we need it for the cursor
    //SyncCaret();
    return CView::OnSetCursor(pWnd, nHitTest, message);
}

void CWedView::OnSize(UINT nType, int cx, int cy)

{
    CView::OnSize(nType, cx, cy);

    PrintToNotepad("Sizing CWedView %d %d\r\n", cx ,cy);
}

void CWedView::OnEditAppendtoholding()

{
    shift = TRUE;
    CopyToHold(this, FALSE);
    shift = FALSE;
}

void CWedView::OnSearchHiteditmode()

{
    if(hitmode )
        {
        hitmode = FALSE;
        }
    else
        {
        if(srcdlg.m_combo1 != "")
            {
            hitmode = TRUE;
            message ("Entering hit mode");
            }
        else
            {
            message ("No search string for hit mode");
            }
        }
    if(hitmode)
        {
        modestr = "HIT";
        AfxGetMainWnd()->SendMessage(WM_MENUSELECT,
            ID_SEARCH_HITEDITMODE | (MF_CHECKED << 8), 0);


        }
    else
        {
        modestr = "";
        }
    mode(modestr);
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    pDoc->UpdateAllViews(NULL);
    SyncCaret();
}

// Move cursor to handle hit mode -> TRUE for down

void CWedView::HitCusror(int direction)

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    int vrow = row;

    // Handle hit mode
    if(!hitmode)
        return;

    if(direction)
        {
        while(TRUE)
            {
            // Limit
            if(vrow >= pDoc->strlist.GetCount()-1)
                {
                // Seek back to last valid
                while(TRUE)
                    {
                    if(!vrow)
                        break;
                    if(pDoc->ssel.lineb.GetAt(vrow))
                        {
                        message ("At last hit");
                        row = vrow; break;
                        }
                    vrow--;
                    }
                break;
                }
            if(pDoc->ssel.lineb.GetAt(vrow))
                {
                row = vrow; break;
                }
            vrow++;
            }
        }
    else
        {
        while(TRUE)
            {
            // Limit
            if(!vrow)
                {
                // Seek forward to last valid
                while(TRUE)
                    {
                    if(vrow >= pDoc->strlist.GetCount()-1)
                        break;

                    if(pDoc->ssel.lineb.GetAt(vrow))
                        {
                        message ("At first hit");
                        row = vrow; break;
                        }
                    vrow++;
                    }
                break;
                }
            if(pDoc->ssel.lineb.GetAt(vrow))
                {
                row = vrow; break;
                }
            vrow--;
            }
        }
    SyncCaret();
}

void CWedView::CancelHit()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    if(hitmode)
        {
        message("Cancelled hit mode");
        hitmode = FALSE;
        pDoc->UpdateAllViews(NULL);
        SyncCaret();
        }
}

void CWedView::OnMacroSelectrecordholdingBuffer10()

{
        SwitchRec(0);
}

void CWedView::OnEditSelectrecordbufferBuffer1()

{
        SwitchRec(1);
}

void CWedView::OnMacroSelectrecordholdingBuffer1()

{
        SwitchRec(2);
}

void CWedView::OnMacroSelectrecordholdingBuffer3()

{
        SwitchRec(3);
}

void CWedView::OnMacroSelectrecordholdingBuffer4()

{
        SwitchRec(4);
}

void CWedView::OnMacroSelectrecordholdingBuffer5()

{
        SwitchRec(5);
}

void CWedView::OnMacroSelectrecordholdingBuffer6()

{
        SwitchRec(6);
}

void CWedView::OnMacroSelectrecordholdingBuffer7()

{
        SwitchRec(7);
}

void CWedView::OnMacroSelectrecordholdingBuffer8()

{
        SwitchRec(8);
}

void CWedView::OnMacroSelectrecordholdingBuffer9()

{
        SwitchRec(9);
}

void CWedView::SwitchRec(int newrec)

{
    if(record)
        {
        message("Cannot switch buffers while recording");
        }
    else
        {
        CString num;
        currmac = newrec;;
        num.Format( " M %02d ", currmac);
        message ("Switched macro buffer");
        mac(num);
        }
}

//////////////////////////////////////////////////////////////////////
// Do search according to m_stype
// const char *str          string to search in
// int *ccol                column where found (-1 in not)
// int *back                step back this many for line


int CWedView::SearchType(int loop, int *ccol, int *back)

{
    int found = 0;
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);

    static  CRegExp re;
    static  CString str3;

    *back = 0;
    *ccol = 0;

    CString str = pDoc->strlist.GetLine(loop);

    if(init_search)
        {
        init_search = FALSE;

        if(srcdlg.m_stype == S_REGEX)
            {
            re.RegComp(srcdlg.m_combo1);
            }
        if(srcdlg.m_stype == S_FUNCTION)
            {
            }
        else
            {
            str3 = srcdlg.m_combo1;
            str3.MakeUpper();
            }
        }

    if(srcdlg.m_stype == S_FUNCTION)
        {
        if(str.Left(1) == '{')
            {
            *ccol = 0;
            found = TRUE;
            // Walk backwards till non empty line
            while(TRUE)
                {
                // Bug in C++ post decrement on pointer
                (*back)--;

                // Reached beginning of buffer
                if((loop - *back) < 0)
                    break;

                CString str2;
                str2 = pDoc->strlist.GetLine(loop + *back);
                PrintToNotepad("Backwalk: %s\r\n", str2);
                if(str2 != "")
                	{
					char cc = str2[0]; cc = tolower(cc);
                	// Found ascii or _ start
                	if((cc >= 'a' && cc <= 'z') || cc == '_')
                    	{
                    	break;
                    	}
                    }
                }
            }
        }
    else if(srcdlg.m_stype == S_REGEX)
        {
        if((*ccol = re.RegFind(str)) != -1)
            found = TRUE;
        }
    else
        {
        CString str4 = str;
        str4.MakeUpper();
        if((*ccol = str4.Find(str3)) != -1)
            found = TRUE;
        }
    return(found);
}

void CWedView::OnWindowsMaximizecurrent()

{
    Maximizecurrent();
}

void CWedView::Maximizecurrent()

{
    CWnd *pw = GetParent();
    ASSERT(pw);
    WINDOWPLACEMENT wndpl;
    pw->GetWindowPlacement(&wndpl);
    wndpl.showCmd = SW_SHOWMAXIMIZED;
    pw->SetWindowPlacement(&wndpl);
    message("Maximized current window");
}

void CWedView::OnDropFiles(HDROP hDropInfo)

{
    CView::OnDropFiles(hDropInfo);
}

void CWedView::OnInsertBasicForloop()

{
    OnInsertForloop();
}

void CWedView::OnInsertBasicIf()

{
    OnInsertIfcondition();
}

void CWedView::OnInsertBasicSelectcase()

{
    OnInsertCSwitchcase();
}

void CWedView::OnInsertBasicFunction()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CString str, pad;

    SaveUndo(this, UNDO_ADD, row, col, "");
    pDoc->strlist.InsertLine(row++, pad + "");

    SaveUndo(this, UNDO_ADD, row, col, "");
    str.Format("// class class%d ", serial);
    pDoc->strlist.InsertLine(row++, str);

    SaveUndo(this, UNDO_ADD, row, col, "");
    pDoc->strlist.InsertLine(row++, pad+"//");

    SaveUndo(this, UNDO_ADD, row, col, "");
    pDoc->strlist.InsertLine(row++, pad);

    SaveUndo(this, UNDO_ADD, row, col, "");
    str.Format("public class class%d extends Applet", serial++);
    pDoc->strlist.InsertLine(row++, pad+str);

    SaveUndo(this, UNDO_ADD, row, col, "");
    pDoc->strlist.InsertLine(row++, pad + "{");

    SaveUndo(this, UNDO_ADD, row, col, "");
    pDoc->strlist.InsertLine(row++, pad);

    SaveUndo(this, UNDO_ADD, row, col, "");
    pDoc->strlist.InsertLine(row++, pad + "}");

    // Position cursor to a good place
    row -= 2; col = col + 4;

    pDoc->SetModifiedFlag();
    pDoc->UpdateAllViews(NULL);  SyncCaret();
}

void CWedView::OnInsertJavaPrivatemethod()

{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CString str, pad(' ', col);

    SaveUndo(this, UNDO_ADD, row, col, "");
    str.Format("int method%d (int arg1, int arg2)", serial++);
    pDoc->strlist.InsertLine(row++, pad+str);

    SaveUndo(this, UNDO_ADD, row, col, "");
    pDoc->strlist.InsertLine(row++, pad + "{");

    SaveUndo(this, UNDO_ADD, row, col, "");
    pDoc->strlist.InsertLine(row++, pad);

    SaveUndo(this, UNDO_ADD, row, col, "");
    pDoc->strlist.InsertLine(row++, pad + "}");

    // Position cursor to a good place
    row -= 2; col = col + 4;

    pDoc->SetModifiedFlag();
    pDoc->UpdateAllViews(NULL);  SyncCaret();
}


// Lock keyboard
//

void CWedView::OnAdvancedLockkeyboard()

{
    if(kblock)
        {
        kblock = FALSE;
        message ("Unocked keyboard");
        }
    else
        {
        kblock = TRUE;
        message ("Locked keyboard");
        }
}

void CWedView::OnUpdateAdvancedLockkeyboard(CCmdUI* pCmdUI)

{
    pCmdUI->SetCheck(kblock);
}

void CWedView::OnUpdateSearchHiteditmode(CCmdUI* pCmdUI)

{
    pCmdUI->SetCheck(hitmode);
}

void CWedView::OnUpdateViewViewhex(CCmdUI* pCmdUI)

{
    pCmdUI->SetCheck(hex);
}

void CWedView::OnSettingsAllowbackspacetowraplines()

{

    backwrap = !backwrap;
}

void CWedView::OnUpdateSettingsAllowbackspacetowraplines(CCmdUI* pCmdUI)

{
    pCmdUI->SetCheck(backwrap);
}

void CWedView::OnSettingsSavetabsasspaces()

{

    Tab2Space =  !Tab2Space;
}

void CWedView::OnUpdateSettingsSavetabsasspaces(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(Tab2Space);
}

void CWedView::OnInsertDatetimeBordersafedate()

{
    InsertDate("%d-%b-%Y ");
}

void CWedView::OnInsertTemplateone()
{
    message ("Loading template one");
    DoTemplate("template.1");
}

void CWedView::OnInsertTemplatetwo()

{
    message ("Loading template two");
    DoTemplate("template.2");
}


void CWedView::OnInsertTemplatethree()
{
    message ("Loading template three");
    DoTemplate("template.3");
}

#define MAX_READ 128

void CWedView::OnAdvancedSpellcheck()

{
    Spellcheck(FALSE);
}

void CWedView::OnAdvancedCommentadstringspellcheck()

{
    Spellcheck(TRUE);
}

//

void CWedView::Spellcheck(int strings)

{
    CString str, idx;
    char buffer[MAX_READ];

    str = approot; str +=  "spell.txt";
    //PrintToNotepad("Dictionary: %s\r\n", str);

    message ("Started Spell Check");
    if(access(str, 0))
        {
        CString num;
        num.Format("Cannot open Dictionary: %s", str);
        AfxMessageBox(num);
        return;
        }

    // Check for index, recreate if needed
    idx = approot; idx +=  "spell.idx";
    if(access(idx, 0))
        {
        CString num;
        num.Format("Creating dictionary index ...");
        message(num);

        char    old = 0;
        int     found   = FALSE;
        FILE    *fp, *fp2;

        fp = fopen(str, "rt");
        if(!fp)
            {
            AfxMessageBox("Cannot open data file\n");
            return;
            }
        fp2 = fopen(idx, "w+t");
        if(!fp2)
            {
            AfxMessageBox("Cannot create index file\n");
            return;
            }
        while(TRUE)
            {
            char    *readd;
            long    fpos;

            fpos  = ftell(fp);                    /* prev pos */
            readd = fgets(buffer, MAX_READ, fp);

            if(buffer[0] != old)        /* new buffer */
                {
                fprintf(fp2, "%d\n", fpos);
                old = buffer[0];
                }
            if(!readd)
                break;
            }
        fclose(fp); fclose(fp2);
        }
    CString cus = approot; cus +=  "spell.cus";
    if(access(cus, 0))
		{
        FILE *fp3 = fopen(cus, "w+t");
        if(!fp3)
            {
            AfxMessageBox("Cannot create custom file\n");
            return;
            }
		fclose(fp3);
		}

    Spell(this, str, idx, cus, strings);
    message ("Done Spell Check");
}

//////////////////////////////////////////////////////////////////////

void CWedView::OnMoveNextlongline()

{
	static in_longd;
	if(in_longd)
		{
		return;
		}
	in_longd = TRUE;
	YieldToWin();

    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CString 	str;

	int 		lim = pDoc->strlist.GetCount() - 1;
    int 		cnt = row + 1;

	Busy(TRUE);
    // Scan from current + 1
    while(TRUE)
        {
        if(cnt >= lim)
            {
            message("Reached last long line");
            break;
            }
        if(!(cnt%100))
            {
            CString num; num.Format("Searching for long lines at %d ", cnt);
            message(num);
            }
        str = pDoc->strlist.GetLine(cnt);

        // Find lines matching criteria:
        if(str.GetLength() > 85)
        	{
            //PrintToNotepad("Found long line at %d\r\n", cnt);
        	row = cnt;
            SyncCaret(1); pDoc->UpdateAllViews(NULL);
            message("Found next long line");
            break;
            }
        cnt++;
        }
	Busy(FALSE);
	in_longd = FALSE;
}

//////////////////////////////////////////////////////////////////////

void CWedView::OnMoveMovepreviouslongline()

{
	static in_longd;
	if(in_longd)
		return;

	in_longd = TRUE;
	YieldToWin();

    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    CString 	str;

	int 		lim = pDoc->strlist.GetCount() - 1;
    int 		cnt = row - 1;

	Busy(TRUE);
    // Scan from current - 1
    while(TRUE)
        {
        if(cnt <= 0)
            {
            message("Reached first long line");
            break;
            }
        if(!(cnt%100))
            {
            CString num; num.Format("Searching for long lines at %d ", cnt);
            message(num);
            }
        str = pDoc->strlist.GetLine(cnt);

        // Find lines matching criteria:
        if(str.GetLength() > 85)
        	{
            //PrintToNotepad("Found long line at %d\r\n", cnt);
        	row = cnt;
            SyncCaret(1); pDoc->UpdateAllViews(NULL);
            message("Found previous long line");
            break;
            }
        cnt--;
        }
	Busy(FALSE);
	in_longd = FALSE;
}

//////////////////////////////////////////////////////////////////////

void CWedView::OnSettingsLonglinecolorfg()

{
    SetColor(&clng);
}

//////////////////////////////////////////////////////////////////////

void CWedView::OnFileMultiopendest()

{
    OpenSource(targdir);
}
