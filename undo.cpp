/////////////////////////////////////////////////////////////////////////////
// Implement Undo/Redo
//
// How it works:
//
// Undo is line based. Information is saved on what we are about to do 
// to the buffer, along with current coordinates, and the old line.
//
// The undo routine interprets the instructions, and reapplies the 
// transaction. Most of the time it is a simple copy of the undo 
// buffer over the old line.
// The cursor is positioned to the undone transaction's place.
//
// A string of transactions are marked as UNDO_BLOCK and we continue 
// until an undo event comes without the block undo flag
//
// The UNDO_MARK is used as the begin of undo mark
// The UNDO_NOOP is used as the block mark
//
// Undo data format:  undotype, row, col, strlen, string

#include "stdafx.h"
#include "wed.h"
#include "srcsel.h"
#include "strlist.h"
#include "Weddoc.h"
#include "WedView.h"
#include "notepad.h"
#include "Undo.h"
#include "editor.h"
#include "misc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static 	void exec_undo(CWedView *v1, int cc, int dd, int ee, int ff, CString &str);
static	void WorkUndo(CWedView *v1, int redo);

int 	undolimit = 10000;
static 	prev    = 0;
static 	prevrow = 0;
static 	prevlen = 0;
static 	in_undo = 0;
static 	in_redo = 0;

/////////////////////////////////////////////////////////////////////////////
// SaveUndo

void SaveUndo(CWedView *v1, int tpe, int row, int col, CString str)

{
	ASSERT_VALID(v1);
    CWedDoc* pDoc = v1->GetDocument(); ASSERT_VALID(pDoc);

    CString	num;
    int     len = str.GetLength();

    // Same line, small transaction, do not save
    if(	prev == UNDO_CHAR && prevrow == row &&
      	abs(prevlen - len) < 6 && !in_redo
      )
   		return;

    // Undo field description: undotype, row, col, strlen, string
    num.Format("%d %d %d %d ", tpe, row, col, len);

    //PrintToNotepad("Saved undo: %s -- %s\r\n", num, str);

    if(pDoc->undo.GetCount() > undolimit)
        {
        pDoc->undo.RemoveTail();
        // Signal that it is not full undo
        pDoc->notfullundo = TRUE;
        }
    pDoc->undo.AddHead(num + str);
	
    prev = tpe;
    prevrow = row;
    prevlen = len;
}

/////////////////////////////////////////////////////////////////////////////
// SaveRedo

void SaveRedo(CWedView *v1, int tpe, int row, int col, CString str)

{
	ASSERT_VALID(v1);
    CString	num;
	CWedDoc* pDoc = v1->GetDocument(); 	ASSERT_VALID(pDoc);

    //PrintToNotepad("SaveRedo() v1:%d tpe:%d row:%d col:%d str:%s\r\n",
	//						v1, tpe, row, col, str);

    num.Format("%d %d %d %d ", tpe, row, col, str.GetLength());
    //PrintToNotepad("Saved redo: %s -- %s\r\n", num, str);
    pDoc->redo.AddHead(num + str);
}

/////////////////////////////////////////////////////////////////////////////
// Execute undo/redo

void WorkUndo(CWedView *v1, int redo)

{
    CStringList *ll;
    CString     str, str2, action;
    CWedDoc*    pDoc;
    int         ccc, repeat, cc, dd, ee, ff;

    // Atomic ============================
    if(in_undo)
       return;
    in_undo = TRUE;
    // Atomic ============================

	v1->Busy(TRUE);

    pDoc= v1->GetDocument(); ASSERT_VALID(pDoc);
    pDoc->SetModifiedFlag();

    // Select list we use:
    if(redo)
		{
		action =  "Redo";
        ll = &pDoc->redo;
		}
    else
		{
		action =  "Undo";
        ll = &pDoc->undo;
		}
    // Set cache:
    prev = 0; prevrow = 0;
  again:
    repeat = FALSE;
    if(ll->IsEmpty())
    	{
		CString num; 
		num.Format("Nothing to %s", action); message(num);
        goto end;
    	}
    // Pop information off the undo stack:				 
    str = ll->RemoveHead();

    sscanf(str, "%d %d %d %d ", &cc , &dd, &ee, &ff);
    
    //PrintToNotepad("Undoing: %d %d %d '%s'\r\n", 
    //			cc, dd, ee, str.Right(ff));

    // Push old line to redo
    if(!redo)
        {
        str2 = pDoc->strlist.GetLine(dd);
        SaveRedo(v1, cc, dd, ee,  str2);
        }
    // See if block undo ...
    ccc = cc;
    if(cc & UNDO_BLOCK)
        {
		// yes
        repeat = TRUE; ccc &= ((~UNDO_BLOCK) & 0xff);
        }
    else
        {
        repeat = FALSE;
        }
    if(redo)
        {
        // Reverse flag
        switch(ccc)
            {
            case UNDO_DEL:
                ccc = UNDO_ADD;
                break;

            case UNDO_ADD:
                ccc = UNDO_DEL;
                break;

            // All other actions are reversed by just reapplying them
            }
        }
    if(redo)
        {
        str2 = pDoc->strlist.GetLine(dd);
        SaveUndo(v1, cc, dd, ee,  str2);
        }
    // Do it
    exec_undo(v1, ccc, dd, ee, ff, str);

	// Show message and see if user wants to interact
	if(!(ll->GetCount() % 100))
		{
        CString num;

		num.Format("%sing item %d", action, ll->GetCount());
        message(num);

		pDoc->UpdateAllViews(NULL); v1->SyncCaret(1);
		if(YieldToWinEx())
			{
			// Stop by force repeat to FALSE
			num.Format("Aborted %s", action);
			AfxMessageBox(num);
			repeat = FALSE;
			}
		}
	// Was a block undo, go get next item
    if(repeat)
        goto again;

end:
    // If met original position, this is clean file
	if(pDoc->undoorig == ll->GetCount() || 
		pDoc->undoorig + 1 == ll->GetCount())
			pDoc->SetModifiedFlag(FALSE);

    v1->SyncCaret(); YieldToWin();
	pDoc->UpdateAllViews(NULL);

	v1->Busy(FALSE);
    in_undo = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
//  UnDo

void UnDo(CWedView *v1)

{
 	WorkUndo(v1, FALSE);
}

/////////////////////////////////////////////////////////////////////////////
//  ReDo

void ReDo(CWedView *v1)

{
    // Call undo with redo flag set
    in_redo = TRUE;
    WorkUndo(v1, TRUE);
    in_redo = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Exec undo
//

void exec_undo(CWedView *v1, int cc, int dd, int ee, int ff, CString &str)

{
    CWedDoc* pDoc = v1->GetDocument(); ASSERT_VALID(pDoc);
	//ASSERT_VALID(str);

    switch(cc)
        {
        case UNDO_MARK:
            // This opcode is pushed as a marker
			message("Reached file save boundary");
			AfxMessageBox(
			"Information: Undo/Redo reached file save boundary.", 
			      MB_ICONINFORMATION );
			pDoc->notfullundo = TRUE;
            //pDoc->SetModifiedFlag(FALSE);
            break;

        case UNDO_DEL:
            // Deleted, line restore it
            v1->row = dd;
            if(v1->row >= pDoc->strlist.GetCount()-1)
                {
                pDoc->strlist.AddTail(str.Right(ff));
                }
            else
                {
                pDoc->strlist.InsertLine(dd, str.Right(ff));
                }
            break;

        case UNDO_ADD:
            // Added line, remove it:
            v1->row = dd;
            DeleteLine(v1, dd);
            break;

        case  UNDO_SEP:
        case  UNDO_CHAR:
        case  UNDO_MOD:
            // Modified:
            v1->row = dd;
            v1->col = ee;
            pDoc->strlist.SetLine(dd, str.Right(ff));
            break;

        case  UNDO_MOVE:
            // Cursor moved:
            v1->row = dd;
            v1->col = ee;
            break;

        case UNDO_NOP:
			// No operation
            break;

        default:
           	message("Warning: Invalid undo opcode");
            //PrintToNotepad("Invalid undo opcode %d\r\n", cc);
            break;
        }
}

// EOF
