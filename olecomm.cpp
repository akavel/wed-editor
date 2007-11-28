//////////////////////////////////////////////////////////////////////
// oleComm.cpp: implementation of the ColeComm class.
//

#include "stdafx.h"
#include "wed.h"
#include "oleComm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction

ColeComm::ColeComm()

{
	first_time = TRUE;
	oleapp = "msdev.application";
}

//////////////////////////////////////////////////////////////////////
//  ColeComm::~ColeComm

ColeComm::~ColeComm()

{
	first_time = FALSE;
}


//////////////////////////////////////////////////////////////////////
// void ColeComm::SendBuild

void ColeComm::SendBuild()

{
	SendStr("build");
}

//////////////////////////////////////////////////////////////////////
// void ColeComm::SendExec

void ColeComm::SendExec()

{
	SendStr("executeconfiguration");
}


//////////////////////////////////////////////////////////////////////
// Send a given command to devstudio

void ColeComm::SendStr(const char *lpszA)

{
	// Just in time connect ... OLE is BAAAD,
	// ...so we init it on demand

	if(first_time)
	{
		// Connect now
		first_time = FALSE;

		// Create the object that we'll drive through OLE automation
		COleException e;
		CLSID clsid;
		if (CLSIDFromProgID(OLESTR("msdev.application"), &clsid) != NOERROR)
			{
			AfxMessageBox("Cannot find compiler object");
			return;
			}

		// Try to get the active one, before creating a new instance
		LPUNKNOWN lpUnk;
		LPDISPATCH lpDispatch;
		if (GetActiveObject(clsid, NULL, &lpUnk) == NOERROR)
		{
			HRESULT hr = lpUnk->QueryInterface(IID_IDispatch,
				(LPVOID*)&lpDispatch);
			lpUnk->Release();
			if (hr == NOERROR)
				AttachDispatch(lpDispatch, TRUE);
		}
		// If no dispatch ptr attached yet, create one
		if (m_lpDispatch == NULL &&  !CreateDispatch(clsid, &e))
			{
			AfxMessageBox("Unable to attach to Devstudio");
			return;
			}
		}

	////////////////////////////////////////////////
	DISPID dispid = 0;

	// We want to convert an MBCS string in lpszA
	int nLen = MultiByteToWideChar(CP_ACP, 0, lpszA, -1, NULL, NULL);
	LPWSTR lpszW = new WCHAR[nLen];
	MultiByteToWideChar(CP_ACP, 0, lpszA, -1, lpszW, nLen);

	// Translate string to ID ....
	HRESULT res = m_lpDispatch->GetIDsOfNames(
								IID_NULL,
								&lpszW,
								1,
						  		LOCALE_SYSTEM_DEFAULT,
								&dispid);
	if(dispid == -1)
		{
		AfxMessageBox("Cannot find method");
		}

	// Go get it ....
	InvokeHelper(dispid,  DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

