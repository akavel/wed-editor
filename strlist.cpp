// StrList.cpp: implementation of the StrList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "wed.h"
#include "StrList.h"

#include "notepad.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

StrList::StrList()
{
    //PrintToNotepad("Stringlist Constructed\r\n");
}

StrList::~StrList()
{

}

// Get a line from offset

CString StrList::GetLine(int line)
{
    CString str;
	//str = new CString;

    //PrintToNotepad("StrList::GetLine %d\r\n", line);

	if(IsEmpty())
    {
        AddTail("");
    }

	if(line < 0)
	{
		//PrintToNotepad("StrList::GetLine before eof%d\r\n", line);
		return(str);
	}

	// Limit to length
	if(line > GetCount()-1)
	{
		//PrintToNotepad("StrList::GetLine beyond eof%d\r\n", line);
		return(str);
	}

    POSITION pos = FindIndex(line);
    if(!pos)
        str = "";
    else
        str = GetAt(pos);

    return(str);
}

// Remove line

void    StrList::RemoveLine(int line)

{
    POSITION pos = FindIndex(line);

    //PrintToNotepad("StrList::RemoveLine %d\r\n", line);

    if(pos)
        RemoveAt(pos);
    else
        {
        PrintToNotepad("StrList::RemoveLine exeption %d\r\n", line);
        }
}

// Insert line before/after position

void    StrList::InsertLine(int line, CString &str, int after)

{
    POSITION pos;

    //PrintToNotepad("StrList::InsertLine %d\r\n", line);

    if(IsEmpty())
    {
        AddTail(str);
        return;
    }
	// Patch if end inserting after EOF
	if(GetCount() - 1 <= line)
		AddTail("");

    pos = FindIndex(line);
    if(!pos)
    {
        PrintToNotepad("StrList::InsertLine positon exception\r\n");
    }
	if(after)
	    InsertAfter(pos, str);
	else
		InsertBefore(pos, str);
}

// Set line at specified position

void    StrList::SetLine(int line, CString &str)

{
    POSITION pos;
    //PrintToNotepad("StrList::InsertLine %d\r\n", line);
    if(IsEmpty())
		{
        PrintToNotepad("StrList::SetLine Auto added line\r\n");
        AddTail(str);
        return;
		}
    pos = FindIndex(line);
    if(!pos)
		{
        PrintToNotepad("StrList::SetLine positon exception\r\n");
		return;
		}
    SetAt(pos, str);
}

