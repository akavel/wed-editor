/////////////////////////////////////////////////////////////////////////////

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Undotype: m=modified  d=deleted  a=added

#define UNDO_NOOP   'n'         // no op
#define UNDO_NOP    'n'         // no op
#define UNDO_MARK   'x'         // beginning
#define UNDO_ADD    'a'         // addedd line
#define UNDO_DEL    'd'         // deleted line
#define UNDO_MOD    'm'         // mofified
#define UNDO_BLOCK  0x80        // continuation
#define UNDO_CHAR   'c'         // added char
#define UNDO_MOVE   'v'         // moved cursor (explicit)
#define UNDO_SEP    's'         // separator or delimiter

// Interface to undo functions

void SaveUndo(CWedView *v1, int tpe, int row, int col, CString str);
void SaveRedo(CWedView *v1, int tpe, int row, int col, CString str);
void UnDo(CWedView *v1);
void ReDo(CWedView *v1);

// EOF
