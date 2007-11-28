// diff.h : interface of the diff helpers
//
/////////////////////////////////////////////////////////////////////////////

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

int	dodiff(CWedView *v1, CWedView *v2);
int linediff(CWedView *v1, CWedView *v2);
int strdiff(const CString &str1, const CString &str2);



