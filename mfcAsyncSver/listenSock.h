#pragma once
#include "accept_Clnt.h"
// listenSock 명령 대상

class listenSock : public CAsyncSocket
{
private :
	wchar_t* clntName;
	CMap<CString, LPCTSTR, CSocket*, CSocket*> list; 
public:
	CArray<CSocket*> clntlist;

	listenSock();
	virtual ~listenSock();
	virtual void OnAccept(int nErrorCode);
	void SendMsg(CDialog* pDialog);
};


