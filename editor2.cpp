///////////////////////////////////////////////////////////////////////////
// Implement editor specific functions
//

//
// Undo --- How it works:
//
// Undo is line based. Information is saved on what we
// are about to do to the buffer, along with current
// coordinates, and the old line.
//
// The undo routine interprets the instructions, and re-
// applies the transaction. Most of the time it is a
// simple copy of the undo buffer over the old line.
// The cursor is positioned to the undone transaction's
// place.
//
// If series of transactions are marked as UNDO_BLOCK we
// continue to undo events until an entry comes without the
// block undo
//
// The undo mark is used as the beginning mark
// The undo nop is used as the block mark
//

// Undo data Fields: undotype, row, col, strlen, string

#include "stdafx.h"
#include "wed.h"
#include "srcsel.h"
#include "strlist.h"
#include "Weddoc.h"
#include "WedView.h"
#include "mxpad.h"
#include "editor.h"
#include "undo.h"
#include "SubClass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define     CB_HOLD     1
#define     CB_CLIP     2

int clipcol = FALSE;

///////////////////////////////////////////////////////////////////////////
// DeleteLine

void    DeleteLine(CWedView *v1, int rowtodel)

{
    CWedDoc* pDoc = v1->GetDocument(); ASSERT_VALID(pDoc);

    // Make sure we are in document
    if(rowtodel > pDoc->strlist.GetCount()-1)
        {
        //P2N("Attempt to delete after EOF\r\n");
        return;
        }
    pDoc->strlist.RemoveLine(rowtodel);

    // Make sure we are in bounds
    if(rowtodel >= pDoc->strlist.GetCount())
        v1->row = pDoc->strlist.GetCount()-1;
}

///////////////////////////////////////////////////////////////////////////

void    PasteClip(CWedView *v1)

{
    static int in_paste;
    ASSERT(v1);

    if(in_paste)
        return;

    in_paste = TRUE;
    v1->Busy(TRUE);
    PasteData(v1, CB_CLIP);
    v1->Busy(FALSE);
    in_paste = FALSE;

    message("Inserted lines from clipboard");
}

///////////////////////////////////////////////////////////////////////////

void    PasteHold(CWedView *v1)

{
    static int in_ihold;
    CWedDoc* pDoc = v1->GetDocument(); ASSERT_VALID(pDoc);

    if(holding[currhold].IsEmpty())
        {
        message("Empty Holding");  return;
        }
    // Semafor
    if(in_ihold)
        return;

    in_ihold = TRUE;
    v1->Busy(TRUE);
    PasteData(v1, CB_HOLD);
    v1->Busy(FALSE);
    in_ihold = FALSE;
    message("Inserted lines from holding");
}

///////////////////////////////////////////////////////////////////////////
// void PasteData(CWedView *v1, int source)

void    PasteData(CWedView *v1, int source)

{
    HANDLE      hMem;
    int         ucount = 0, ipos = 0;
    POSITION    pos;
    CString     str, clip, str5;
    CWedDoc*    pDoc = v1->GetDocument(); ASSERT_VALID(pDoc);

    // Save undo start flag
    SaveUndo(v1, UNDO_NOP, v1->row, v1->col, "");

    // Put holding into file buffer
    if(source == CB_HOLD)
        {
        pos = holding[currhold].GetHeadPosition();
        }
    if(source == CB_CLIP)
        {
        if(!v1->OpenClipboard())
            goto endd;

        hMem = GetClipboardData(CF_TEXT);
        CloseClipboard();
        if(!hMem)
            goto endd;
        char *ptr = (char*)GlobalLock(hMem);
        if(!ptr)
            {
            message ("Empty clipboard");
            goto endd;
            }
        clip = ptr;
        }
    int colflag;
    if(source == CB_HOLD)
        colflag = holdflag[currhold];
    if(source == CB_CLIP)
        colflag = clipcol;

    // Cycle thru data
    while(TRUE)
        {
        ucount++;
        if(!(ucount%100))
            {
            CString num;
            num.Format( "Pasting %d", ucount);
            message(num);

            if(YieldToWinEx())
                {
                AfxMessageBox("Aborted paste");
                break;
                }
            }
        // Get data
        if(source == CB_HOLD)
            {
            if (!pos)
                break;
            str = holding[currhold].GetNext(pos);
            }
        if(source == CB_CLIP)
            {
            if (ipos == -1)
                break;
            ipos = clip.Find("\r\n");
            if (ipos == -1)
                {
                str = clip;
                if(str == "")
                    break;
                }
            else
                {
                str  = clip.Left(ipos);
                CString str3 = clip.Right(clip.GetLength() - (ipos+2));
                clip = str3;
                }
            }
        // Extend if buffer is not big enough to insert it
        if(pDoc->strlist.GetCount() <= v1->row)
            pDoc->strlist.AddTail("");

        if(colflag)
            {
            // Insert column data
            CString str2 = pDoc->strlist.GetLine(v1->row);

            SaveUndo(v1, UNDO_MOD | UNDO_BLOCK,  v1->row, v1->col, str2);
            int pos2, ontab;

            // Translate current position from tabs
            TabbedPos(str2, v1->col, &pos2, &ontab);
            if(ontab)
                {
                int dummy;
                OnTabbed(str2, ontab);
                TabbedPos(str2, v1->col, &pos2, &dummy);
                }
            int diff = pos2 - str2.GetLength();
            // Expand to col length
            if(diff > 0)
                {
                CString str4(' ', diff);  str2 += str4;
                }
            str5 = str2.Left(pos2) + str +
                        str2.Right(str2.GetLength() - pos2);

            pDoc->strlist.SetLine(v1->row, str5);
            }
        else
            {
            SaveUndo(v1, UNDO_ADD | UNDO_BLOCK,  v1->row, v1->col, "");
            pDoc->strlist.InsertLine(v1->row, str);
            }
        v1->row++;
        }
#if 0
    if(source == CB_CLIP)
        {
        if(colflag)
            {
            v1->col += str.GetLength();
            v1->row--;
            }
        }
#endif

   endd:
    GlobalUnlock( hMem);
    // Communiate changes:
    pDoc->SetModifiedFlag(TRUE);
    v1->SyncCaret();  pDoc->UpdateAllViews(NULL);
}

///////////////////////////////////////////////////////////////////////////

void    CopyToClip(CWedView *v1, int cut)

{
    static int in_ccopy;

    if(in_ccopy)
        return;

    in_ccopy = TRUE;
    v1->Busy(TRUE);
    CopyData(v1, cut, CB_CLIP);
    v1->Busy(FALSE);
    in_ccopy = FALSE;

    if(cut)
        message("Lines cut to clipboard");
    else
        message("Lines copied to clipboard");
}

///////////////////////////////////////////////////////////////////////////

void    CopyToHold(CWedView *v1, int cut)

{
    static int in_ccopy;

    if(in_ccopy)
        return;
    in_ccopy = TRUE;
    v1->Busy(TRUE);
    CopyData(v1, cut, CB_HOLD);
    v1->Busy(FALSE);
    in_ccopy = FALSE;

    if(cut)
        message("Lines cut to holding buffer");
    else
        message("Lines copied to holding buffer");
}

///////////////////////////////////////////////////////////////////////////
// void CopyData(CWedView *v1, int cut, int target)

void    CopyData(CWedView *v1, int cut, int target)

{
    CWedDoc* pDoc = v1->GetDocument(); ASSERT_VALID(pDoc);
    CString     str, str2, strclip;

    // Make logical highlite
    int lsoh, leoh;
    if(v1->soh < v1->eoh)
        {
        lsoh = v1->soh; leoh = v1->eoh;
        }
    else
        {
        leoh = v1->soh; lsoh = v1->eoh;
        }
    // Make logical colomn highlite
    int lsoch, leoch;
    if(v1->soch <= v1->eoch)
        {
        lsoch = v1->soch; leoch = v1->eoch + 1;
        }
    else
        {
        leoch = v1->soch; lsoch = v1->eoch+1;
        }
    // if not append mode, clear old buffer
    if(!v1->shift && target == CB_HOLD)
        {
        holding[currhold].RemoveAll();
        }
    if(!v1->shift && target == CB_CLIP)
        {
        }
    // Nothing selected, get one line
    if(lsoh == -1)
        {
        str = pDoc->strlist.GetLine(v1->row);
        if(target == CB_CLIP)
            {
            clipcol = FALSE;
            strclip += str + "\r\n";
            }
        if(target == CB_HOLD)
            {
            holdflag[currhold] = FALSE;
            holding[currhold].AddTail(str);
            }
        if(cut)
            {
            SaveUndo(v1, UNDO_DEL, v1->row, v1->col, str);
            DeleteLine(v1, v1->row);
            }
        goto done_copy;
        }
    // Normal operation
    if(cut)
        SaveUndo(v1, UNDO_NOP, v1->row, v1->col, "");
    // Column mode
    if(v1->soch != -1)
        {
        int tsoch, teoch;

        if(target == CB_CLIP)
            clipcol = TRUE;
        if(target == CB_HOLD)
            holdflag[currhold] = TRUE;

        for (int loop = lsoh; loop <= leoh; loop++)
            {
            CString num;
            if(!(loop % 100))
                {
                num.Format( "Column copy line %d", loop);
                message(num);

                if(YieldToWinEx())
                    {
                    AfxMessageBox("Aborted copy");
                    goto end2;
                    }
                }
            if(v1->hitmode)
                {
                int offs = min(pDoc->ssel.lineb.GetSize()-1, loop);
                if(!pDoc->ssel.lineb.GetAt(offs))
                    {
                    continue;
                    }
                }
            str = pDoc->strlist.GetLine(loop);
            tsoch = scr2str(str, lsoch);
            teoch = scr2str(str, leoch);
            str2 = str.Mid(tsoch, teoch - tsoch);
            //P2N("Col copy: '%s'\r\n", str2);

            if(target == CB_CLIP)
                strclip += str2 + "\r\n";

            if(target == CB_HOLD)
                holding[currhold].AddTail(str2);

            if(cut)
                {
                pDoc->SetModifiedFlag();
                SaveUndo(v1, UNDO_MOD | UNDO_BLOCK,  loop, v1->col, str);
                str2 = str.Left(tsoch) + str.Right(str.GetLength() - teoch);
                pDoc->strlist.SetLine(loop, str2);
                }
            }
        // Position cursor to original place.
        v1->col = lsoch;
        v1->row = lsoh;
        }
    else
        {
        // Row copy:
        if(target == CB_CLIP)
            holdflag[currhold] = FALSE;

        if(target == CB_HOLD)
            clipcol = FALSE;

        for (int loop = lsoh; loop <= leoh; loop++)
            {
            CString num;
            if(!(loop % 100))
                {
                num.Format( "Copy line %d", loop);
                message(num);
                if(YieldToWinEx())
                    {
                    AfxMessageBox("Aborted copy to holding");
                    goto end2;
                    }
                }
            str = pDoc->strlist.GetLine(loop);
            //P2N("Copying %s\r\n", str);
            if(target == CB_HOLD)
                holding[currhold].AddTail(str);
            if(target == CB_CLIP)
                strclip += str + "\r\n";
            }
        if(cut)
            {
            for (loop = lsoh; loop <= leoh; loop++)
                {
                str = pDoc->strlist.GetLine(lsoh);
                CString num;
                if(!(loop % 100))
                    {
                    num.Format( "Cutting %d", loop);
                    message(num);

                    if(YieldToWinEx())
                        {
                        AfxMessageBox("Aborted cut");
                        goto end2;
                        }
                    }
                SaveUndo(v1, UNDO_DEL | UNDO_BLOCK, lsoh, v1->col, str);
                DeleteLine(v1, lsoh);
                }
            v1->row = lsoh;
            }
        else
            {
            v1->row = leoh+1;
            }
        }

done_copy:
    // Expose clipboard to the system:
    if(target == CB_CLIP)
        {
            HANDLE hMem;
            // Render what goes there ...
            // !!!! Null terminator
            hMem = GlobalAlloc( GMEM_MOVEABLE | GMEM_DDESHARE,
                        strclip.GetLength()+1);
            if(!hMem)
                goto end2;
            ASSERT(hMem);

            char *ptr = (char*)GlobalLock(hMem);
            if(!ptr)
                goto end2;
            ASSERT(ptr);

            strcpy(ptr, (const char *)strclip);
            GlobalUnlock(hMem);

            // Traditional clipboard operation
            if(v1->OpenClipboard())
                {
                SetClipboardData(CF_TEXT, hMem);
                CloseClipboard();
                }
            else
                {
                GlobalFree(hMem);
                }
        }
end2:
    v1->eoch =  v1->soch = -1;
    v1->soh  =  v1->eoh = -1;
    v1->SyncCaret(); pDoc->UpdateAllViews(NULL);
    if(cut)
        pDoc->SetModifiedFlag();
}


///////////////////////////////////////////////////////////////////////////
// On tabbed position, expand tabs to spaces

void    OnTabbed(CString &str, int ontab)

{
    CString str2;
    int tabreal, dummy;
    TabbedPos(str, ontab, &tabreal, &dummy);
    //tabreal = ontab;

    CString str3(' ', 4 - (ontab % 4));
    str2 = str.Left(tabreal) + str3
            + str.Right(str.GetLength() - (tabreal+1));
    str = str2;
}

///////////////////////////////////////////////////////////////////////////
// Convert screen position to string position

void    TabbedPos(CString &str, int col, int *real, int *ontab)

{
    int loop, len, locreal;

    *ontab = 0;
    *real  = col;

    len     = str.GetLength();
    locreal = 0;
    //P2N("Tabbedpos: %d '%s'\r\n", col, str);

    for(loop = 0; loop < col; loop++)
        {
        char chh = 0;
        if(locreal < len)
            chh = str.GetAt(locreal);

        if(chh == '\t')
            {
            int tab = 3 - (loop % 4);

            if(loop > col - (tab+1))
                *ontab = loop;

            loop += tab;
            }
        locreal++;
        }
    *real = locreal;
    //P2N("Tabbedpos: %d ontab: %d\r\n", *real, *ontab);
}

///////////////////////////////////////////////////////////////////////////
// Convert screen pos to string pos
// scr2str

int     scr2str(CString &str, int col)

{
    int real, dummy;
    TabbedPos(str,  col, &real, &dummy);
    return(real);
}

///////////////////////////////////////////////////////////////////////////
// Convert string pos to screen pos
// str2scr

int     str2scr(CString &str, int col)

{
    int real, dummy;
    UnTabbedPos(str,  col, &real, &dummy);
    return(real);
}

///////////////////////////////////////////////////////////////////////////
// UnTabbedPos

void    UnTabbedPos(CString &str, int pos, int *real, int *ontab)

{
    int loop, len, locreal;

    *ontab = 0;
    *real  = pos;

    len     = str.GetLength();
    locreal = 0;
    //P2N("Tabbedpos: %d '%s'\r\n", col, str);

    for(loop = 0; loop < pos; loop++)
        {
        char chh = 0;
        if(loop < len)
            chh = str.GetAt(loop);

        if(chh == '\t')
            {
            int tab = 4 - (locreal % 4);
            if(loop > pos - tab)
                *ontab = loop;

            locreal += tab;
            }
        else
            locreal++;
        }
    *real = locreal;
    //P2N("UnTabbedpos: %d\r\n", *real);
}

///////////////////////////////////////////////////////////////////////////
// Add character at current position

void    addchar(CWedView *v1, char chh)
{
    CString str, str2;
    int ontab, real;
    CWedDoc* pDoc = v1->GetDocument(); ASSERT_VALID(pDoc);

    if(v1->hex)
        {
        message("Buffer is read only in HEX Mode");  return;
        }
    if(pDoc->readonly)
        {
        message("Buffer is read only");  return;
        }
    // Construct undo
    str = pDoc->strlist.GetLine(v1->row);

    if(delim.Find(chh) == -1)
        SaveUndo(v1, UNDO_CHAR, v1->row, v1->col, str);
    else
        SaveUndo(v1, UNDO_SEP, v1->row, v1->col, str);

    // Translate current position from tabs
    TabbedPos(str, v1->col, &real, &ontab);
    if(ontab)
        {
        int dummy;
        OnTabbed(str, ontab);
        TabbedPos(str, v1->col, &real, &dummy);
        }
    // Extend string if we are after the end:
    int diff = real - str.GetLength();
    if(diff > 0)
        {
        CString spaces(' ', diff); str+=spaces;
        }
    // Add it here
    str2 = str.Left(real) + chh + str.Right(str.GetLength() - real);

    // Communicate changes to document:
    pDoc->strlist.SetLine(v1->row, str2);

    if(chh != '\t')
        v1->col++;
    else
        {
        v1->col += 4-(v1->col%4);
        }
    // Tell the doc to redraw
    pDoc->UpdateAllViews(NULL);  v1->SyncCaret();
    pDoc->SetModifiedFlag();
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

///////////////////////////////////////////////////////////////////////////
// Expand tabs:

void    ExpandTabs(CString &str)

{
    CString     str3;
    int     count = 0, wastab = 0;
    int     len = str.GetLength();

    //P2N("Expand '%s'\r\n", str);

    for(int loop = 0; loop < len; loop++)
        {
        char cc = str.GetAt(loop);
        if(cc == '\t')
            {
            int lim = 4 - (count % 4);

            wastab = TRUE;
            for(int loop2 = 0; loop2 < lim; loop2++)
                {
                count++; str3 +=  " ";
                }
            }
       else
            {
            count++; str3 += cc;
            }
       }
    // Output only if changed
    if(wastab)
       str = str3;
}

///////////////////////////////////////////////////////////////////////////
// SubstStr

void    SubstStr(CString &str, CString src, CString sub)

{
    CString     lstr, rstr, estr;
    int         pos;
    int         len = str.GetLength();
    int         wassub = 0;

    //P2N("Subst: '%s'\r\n", str);

    rstr = str;
    while(TRUE)
        {
        if((pos = rstr.Find(src)) == -1)
            {
            estr += rstr;
            break;
            }
        wassub++;
        estr  += rstr.Left(pos) + sub;
        rstr =   rstr.Right(rstr.GetLength()
                            - (pos + src.GetLength()));

        //P2N("rstr: '%s'\r\n", rstr);
        }
    if(wassub)
        str = estr;

    //P2N("Substed: '%s'\r\n", str);
}

///////////////////////////////////////////////////////////////////////////
// Return first position NOT in set
// WalkStr

int     WalkStr(CString &str, CString sub)

{
    int loop;
    int found = 0, len = str.GetLength();

    //P2N("Walk '%s' for '%s'\r\n", str, sub);
    for(loop = 0; loop < len; loop++)
       {
       char cc = str.GetAt(loop);
       if(sub.Find(cc) < 0)
            {
            found = TRUE; break;
            }
       }
    if(!found)
        loop = -1;

    //P2N("Walk '%d'\r\n", loop);
    return(loop);
}


///////////////////////////////////////////////////////////////////////////
// GetDocFromPath
// Get doc from path name (NULL if not here)

CWedDoc*  GetDocFromPath(const char *str)

{
    CWedDoc*  pDoc = NULL;
    CMultiDocTemplate* pDocTemplate =
                ((CWedApp*)AfxGetApp())->pDocTemplate;
    POSITION Pos =  pDocTemplate->GetFirstDocPosition();
    for(;;)
        {
        if(!Pos)
            break;
        CWedDoc* pDoc2 = (CWedDoc*)pDocTemplate->GetNextDoc(Pos);
        if(!pDoc2)
            continue;
        ASSERT_VALID(pDoc2);
        if( str == pDoc2->GetPathName())
            {
            ////P2N("Got pDoc2: %d %s\r\n", pDoc2, str);
            pDoc = pDoc2;
            break;
            }
        }
    return(pDoc);
}

///////////////////////////////////////////////////////////////////////////
// Find word we are sitting on
// if begin == end then no word

void    SelWord(CString &str, int col, int *begin, int *end, int scr)
{
    int len = str.GetLength();
    int real = scr2str(str, col);
    int pos1 = min(real, len-1);
    int pos2 = min(real, len-1);

    if(!len)
        goto end2;

    // Step to begin of separators if any
    while(delim.Find(str.GetAt(pos1)) != -1)
        {
        if(--pos1 <= 0)
            break;
        }
    pos1 = max(pos1, 0);
    pos2 = pos1;
    // Step to end of current word:
    while(delim.Find(str.GetAt(pos1)) == -1)
        {
        if(++pos1 >= len)
            break;
        }

    // Step to beginning of current word:
    while(delim.Find(str.GetAt(pos2)) == -1)
       {
       if(--pos2 <= 0)
           break;
       }

    // Step to beginning of current word:
    pos2= max(pos2,0);
    while(delim.Find(str.GetAt(pos2)) != -1)
        {
        if(++pos2 >= len)
            break;
        }

    // Make sure it is in bounds
    pos1 = min(pos1, len); pos1 = max(pos1, 0);
    pos2 = min(pos2, len); pos2 = max(pos2, 0);

end2:
    *begin = str2scr(str, pos2);
    *end   = str2scr(str, pos1);
}

///////////////////////////////////////////////////////////////////////////
// Delete selected cols/lines

void    DeleteSelection(CWedView *v1)

{
    static in_del;

    CString     str, str2;
    int         loop, loop2;
    CWedDoc* pDoc = v1->GetDocument(); ASSERT_VALID(pDoc);

    if(in_del)
        return;
    in_del = TRUE;

    v1->Busy(TRUE);

    // Make logical highlite
    int lsoh, leoh;
    if(v1->soh < v1->eoh)
        {
        lsoh = v1->soh; leoh = v1->eoh;
        }
    else
        {
        leoh = v1->soh; lsoh = v1->eoh;
        }
    // Make logical colomn highlite
    int lsoch, leoch;
    if(v1->soch <= v1->eoch)
        {
        lsoch = v1->soch; leoch = v1->eoch + 1;
        }
    else
        {
        leoch = v1->soch; lsoch = v1->eoch+1;
        }
    SaveUndo(v1, UNDO_NOP, v1->row, v1->col, "");

    // Column mode
    if(v1->soch != -1)
        {
        int tsoch, teoch;
        for (loop = lsoh; loop <= leoh; loop++)
            {
            CString num;
            if(!(loop % 100))
                {
                num.Format( "Deleting line %d", loop);
                message(num);

                if(YieldToWinEx())
                    {
                    AfxMessageBox("Aborted delete");
                    goto end2;
                    }
                }
            str = pDoc->strlist.GetLine(loop);
            tsoch = scr2str(str, lsoch);
            teoch = scr2str(str, leoch);
            pDoc->SetModifiedFlag();
            SaveUndo(v1, UNDO_MOD | UNDO_BLOCK,  loop, v1->col, str);
            CString str3 = str.Left(tsoch) + str.Right(str.GetLength() - teoch);
            pDoc->strlist.SetLine(loop, str3);
            }
        // Position cursor to original place.
        v1->col = lsoch;
        v1->row = lsoh;
        }
    else
        {
        // Row mode
        for (loop2 = lsoh; loop2 <= leoh; loop2++)
            {
            str = pDoc->strlist.GetLine(lsoh);
            CString num;
            if(!(loop2 % 100))
                {
                num.Format( "Deleting at line %d", loop2);
                message(num);

                if(YieldToWinEx())
                    {
                    AfxMessageBox("Aborted delete");
                    break;
                    }
                }
            SaveUndo(v1, UNDO_DEL | UNDO_BLOCK, lsoh, v1->col, str);
            DeleteLine(v1, lsoh);
            }
        v1->row = lsoh;
        }
end2:
    in_del = FALSE;
}

#define MAX_READ 128
CWordArray      widx;
StrList         ignore;
StrList         learn;
FILE            *fp1, *fp2, *fp3;

///////////////////////////////////////////////////////////////////////////
// Spell Check current buffer

void    Spell(CWedView *v1,
           const char *dic,
           const char *idx,
           const char *cus,
           int flag)

{
    static int in_spell = 0;

    if(in_spell)
        return;
    in_spell = TRUE;

    int     cnt = 0, start = 0, end = 0;
    char    buffer[MAX_READ];
    CWedDoc* pDoc = v1->GetDocument(); ASSERT_VALID(pDoc);
    int oldrow = v1->row, oldcol = v1->col;

    P2N("Spell: %s %s %s\r\n", dic, idx, cus);

    fp1 = fopen(dic, "rt");
    if(!fp1)
        {
        AfxMessageBox("Internal: Cannot open data file\n");
        goto endd;
        }
    fp2 = fopen(idx, "rt");
    if(!fp2)
        {
        AfxMessageBox("Internal: Cannot open index file\n");
        fclose(fp1);
        goto endd;
        }
    fp3 = fopen(cus, "r+t");
    if(!fp3)
        {
        AfxMessageBox("Internal: Cannot open custom file\n");
        fclose(fp1);
        fclose(fp2);
        goto endd;
        }
    // Load index to memory
    while(TRUE)
        {
        char    *readd;
        int     pos;

        readd = fgets(buffer, MAX_READ, fp2);
        sscanf(buffer, "%d", &pos);
        widx.SetAtGrow(cnt, pos);
        cnt++;

        if(!readd)
            break;
        }
    fclose(fp2);

#if 0
    {
    // Test index/dict:
    for(int loop = 0; loop < widx.GetSize(); loop++)
        {
        int offset = widx.GetAt(loop);
        fseek(fp1, offset, SEEK_SET);
        fgets(buffer, MAX_READ, fp1);
        P2N("Value: %d DIC: %s\r\n", offset, buffer);
        }
    }
#endif
    // Go line by line
    if(v1->soh != -1)
        {
        start = v1->soh;
        end = v1->eoh + 1;
        end = min(end, pDoc->strlist.GetCount());
        }
    else
        {
        start = v1->row;
        end = pDoc->strlist.GetCount();
        }
    v1->Busy(TRUE);
    for(v1->row = start; v1->row < end; v1->row++)
        {
        CString line;
        if(!(v1->row % 100))
            {
            CString num;
            num.Format("Checking line %d", v1->row);
            message(num);
            }
        if(CheckLine(v1, v1->row, flag))
            break;
        }
    v1->Busy(FALSE);

    fclose(fp1);
    fclose(fp3);

endd:
    in_spell = FALSE;

    // Restore highlites
    v1->soh = v1->eoh = -1;
    v1->soch = v1->eoch = -1;

    // Restore positions
    // v1->col = oldcol; v1->row = oldrow;
    v1->SyncCaret(3); pDoc->UpdateAllViews(NULL);
}

///////////////////////////////////////////////////////////////////////////
// Check line

int     CheckLine(CWedView *v1, int row, int flag)

{
    CWedDoc* pDoc = v1->GetDocument(); ASSERT_VALID(pDoc);
    CString str = pDoc->strlist.GetLine(row);
    int     wbeg, wend, pos = 0, ret = 0,
                on2 = FALSE,  comm = FALSE;
    int stron = FALSE;

    //P2N("\r\nCheck: '%s'\r\n", str);

    if(!str.GetLength())
        goto endd;

    while(TRUE)
        {
        if(pos >= str.GetLength())
            break;
        // Skip to word:
        while(TRUE)
            {
            if(pos >= str.GetLength())
                break;
            // Get and lower case letter
            char cc = str.GetAt(pos);

            if(flag)
                {
                if(cc == '"')
                    stron = !stron;

                if(cc == '/')
                    {
                    if(pos+1 < str.GetLength())
                        if(str.GetAt(pos+1) == '/')
                            comm = TRUE;
                    }
                }
            cc = tolower(cc);
            if(cc >= 'a' && cc <= 'z')
                break;
            pos++;
            }
        wbeg = pos;
        // Skip to non word:
        while(TRUE)
            {
            if(pos >= str.GetLength())
                break;
            // Get and lower case letter
            char cc = str.GetAt(pos);
            if(flag)
                {
                if(cc == '"')
                    on2 = !on2;

                if(cc == '/')
                    {
                    if(pos+1 < str.GetLength())
                        if(str.GetAt(pos+1) == '/')
                            comm = TRUE;
                    }
                }
            cc = tolower(cc);
            if((cc >= 'a' && cc <= 'z') || cc == '\'')
                {}
            else
                break;
            pos++;
            }
        wend = pos;

        // Skip if not string
        if(flag && !stron && !comm)
            continue;

        if(wbeg != wend)
            {
            CString  lstr, rstr, xstr, ystr;
            ystr = str.Mid(wbeg, wend - wbeg);

            v1->soh = row;
            v1->eoh = row;
            v1->soch = wbeg;
            v1->eoch = wend;
            v1->row = row;
            v1->col = wend - 1;

            v1->SyncCaret(3);  pDoc->UpdateAllViews(NULL);
            if(YieldToWinEx())
                {
                ret = TRUE; goto endd;
                }
            int action = CheckWord(v1, ystr, xstr);

            switch(action)
                {
                case SP_OK:
                    SaveUndo(v1, UNDO_MOD,  row, wend, str);
                    lstr = str.Left(wbeg);
                    rstr = str.Right(str.GetLength() - wend);
                    str = lstr + xstr + rstr;
                    pDoc->strlist.SetLine(row, str);
                    pos = wbeg + xstr.GetLength() + 1;
                    v1->SyncCaret(3); pDoc->UpdateAllViews(NULL);
                    break;

                case SP_LEARN:
                    fseek(fp3, 0, SEEK_END);
                    fputs(ystr + "\n",  fp3);
                    break;

                case SP_STOP:
                    ret = TRUE; goto endd;
                    break;

                case SP_IGNORE:
                    break;

                case SP_IGNORE_ALL:
                    ignore.AddTail(ystr);
                    P2N("add ignore: '%s' ", ystr);
                    //AfxMessageBox(ystr);
                    break;
                }
            }

        // Delayed rendering of string off
        if(on2)
            {
            on2 = !on2;
            stron = !stron;
            }
        }
endd:
    return(ret);
}

///////////////////////////////////////////////////////////////////////////
// Check word
// Return action

int     CheckWord(CWedView *v1, CString &instr, CString &repl)

{
    CWedDoc* pDoc = v1->GetDocument(); ASSERT_VALID(pDoc);
    SubClass    sc;
    int         dummy = 0, ret = SP_OK;
    char        buffer[128];

    // Short strings are not checked
    if(instr.GetLength() < 3)
        return(SP_IGNORE);

    instr.MakeLower();

    int offset = 0;
    if(widx.GetSize() > (instr[0] - 'a'))
        offset =  widx.GetAt(instr[0] - 'a');

    //P2N("'%s' %d ", instr, offset);

    // Look up in ignore array
    int lim = ignore.GetCount();
    for (int loop = 0; loop < lim; loop++)
        {
        CString ign = ignore.GetLine(loop);
        if(!strcmp(instr, ign) )
            {
            //P2N("Found ignore: '%s' ", ign);
            ret = 0;
            break;
            }
        }
    // Look up in custom dictionary
    fseek(fp3, 0, SEEK_SET);
    while(TRUE)
        {
        if(!fgets(buffer, 128, fp3) )
            break;
        buffer[strlen(buffer)-1] = '\0';
        if(!strcmp(instr, buffer) )
            {
            // P2N("Found: '%s' ", buffer);
            ret = 0;
            break;
            }
        }
    if(ret)
        {
        // Look up in dictionary
        fseek(fp1, offset, SEEK_SET);
        while(TRUE)
            {
            if(!fgets(buffer, 128, fp1) )
                break;
            buffer[strlen(buffer)-1] = '\0';
            // P2N("'%s'  ", buffer);
            if(!strcmp(instr, buffer) )
                {
                // P2N("Found: '%s' ", buffer);
                ret = 0;
                break;
                }
            if(buffer[0] !=  instr[0])
                break;
            }
        }
    // Get feedback from user
    if(ret)
        {
        v1->SyncCaret(3); pDoc->UpdateAllViews(NULL);

        // Start at letter position
        fseek(fp1, offset, SEEK_SET);
        sc.m_result = instr;
        sc.m_fp = fp1;

        sc.DoModal();

        ret     = sc.m_ret;
        repl    = sc.m_result;
        }
    return(ret);
}
