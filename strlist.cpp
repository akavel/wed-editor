// StrList.cpp: implementation of the StrList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "wed.h"
#include "StrList.h"

#include "mxpad.h"


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
    //P2N("Stringlist Constructed\r\n");
}

StrList::~StrList()
{

}

//////////////////////////////////////////////////////////////////////////
// Get a line from offset

CString StrList::GetLine(int line)

{
    CString str;
	//str = new CString;

    //P2N("StrList::GetLine %d\r\n", line);

	if(IsEmpty())
    {
        AddTail("");
    }

	if(line < 0)
	{
		P2N("StrList::GetLine before eof line=%d\r\n", line);
		return(str);
	}

	// Limit to length
	if(line > GetCount()-1)
	{
		P2N("StrList::GetLine beyond eof line=%d size=%d\r\n", line, GetCount()-1);
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

    //P2N("StrList::RemoveLine %d\r\n", line);

    if(pos)
        RemoveAt(pos);
    else
        {
        P2N("StrList::RemoveLine exeption %d\r\n", line);
        }
}

// Insert line before/after position

void    StrList::InsertLine(int line, CString &str, int after)

{
    POSITION pos;

    //P2N("StrList::InsertLine %d\r\n", line);

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
        P2N("StrList::InsertLine positon exception\r\n");
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
    //P2N("StrList::InsertLine %d\r\n", line);
    if(IsEmpty())
		{
        P2N("StrList::SetLine Auto added line\r\n");
        AddTail(str);
        return;
		}
    pos = FindIndex(line);
    if(!pos)
		{
        P2N("StrList::SetLine positon exception\r\n");
		return;
		}
    SetAt(pos, str);
}

