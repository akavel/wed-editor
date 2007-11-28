// oleComm.h: interface for the ColeComm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OLECOMM_H__53938B63_307D_11D3_BC4F_0060674B8E2C__INCLUDED_)
#define AFX_OLECOMM_H__53938B63_307D_11D3_BC4F_0060674B8E2C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class ColeComm : public COleDispatchDriver
{
public:

	char *oleapp;
	void SendBuild();
	void SendExec();
	void SendStr(const char *lpszA);
	
	ColeComm();
	virtual ~ColeComm();

	int first_time;


};

#endif // !defined(AFX_OLECOMM_H__53938B63_307D_11D3_BC4F_0060674B8E2C__INCLUDED_)
