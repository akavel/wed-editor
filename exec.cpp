// exec.cpp : implementation file
//

#include "stdafx.h"
#include "wed.h"
#include "exec.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// exec

IMPLEMENT_DYNCREATE(exec, CCmdTarget)

exec::exec()
{
}

exec::~exec()
{
}


BEGIN_MESSAGE_MAP(exec, CCmdTarget)
	//{{AFX_MSG_MAP(exec)
	ON_COMMAND(ID_COMPILE_MAKE, OnCompileMake)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// exec message handlers

void exec::OnCompileMake() 
{

	system("nmake");
}
