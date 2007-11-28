//
// Implement Undo/Redo
//

#include "stdafx.h"
#include "wed.h"
#include "srcsel.h"
#include "strlist.h"
#include "Weddoc.h"
#include "WedView.h"
#include "notepad.h"
#include "Undo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void SaveUndo(CWedView *v1, char tpe, int row, int col, CString str)
{
    CWedDoc* pDoc = v1->GetDocument(); ASSERT_VALID(pDoc);
    char num[16];

    diffchange = TRUE;
    //other->diffchange = TRUE;
    //other->GetDocument()->UpdateAllViews(NULL);

    // Construct undo instruction (for delete)
    // Fields: undotype row, col, strlen, string
    // Undotype: m=modified d= deleted   a=added
    //           r=return   x=boundary

    sprintf(num, "%c %d %d %d", tpe, row, col, str.GetLength());

    //PrintToNotepad("Saved undo info: %s\r\n", num);
    //PrintToNotepad("Saved undo string '%s'\r\n", str);
    pDoc->undo.AddHead(num + str);
}

void SaveRedo(CWedView *v1, char tpe, int row, int col, CString str)
{
    CWedDoc* pDoc = GetDocument(); ASSERT_VALID(pDoc);
    char num[16];

    // Construct undo instruction (for delete)
    // Fields: undotype row, col, strlen, string
    // Undotype: m=modified d= deleted   a=added
    //           r=return   x=boundary

    sprintf(num, "%c %d %d %d", tpe, row, col, str.GetLength());

    //PrintToNotepad("Saved undo info: %s\r\n", num);
    //PrintToNotepad("Saved undo string '%s'\r\n", str);
    pDoc->redo.AddHead(num + str);
}


