// StrList.h: interface for the StrList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRLIST_H__B5170923_E910_11D2_B398_525400D994D7__INCLUDED_)
#define AFX_STRLIST_H__B5170923_E910_11D2_B398_525400D994D7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class StrList : public CStringList  
{
public:

	CString GetLine(int line);
	// POSITION InsertBefore(POSITION pos, CString &str);
	void  RemoveLine(int line);
	void  InsertLine(int line, CString &str, int after = 0);
	void  SetLine(int line, CString &str);

	StrList();
	virtual ~StrList();

};

#endif // !defined(AFX_STRLIST_H__B5170923_E910_11D2_B398_525400D994D7__INCLUDED_)
