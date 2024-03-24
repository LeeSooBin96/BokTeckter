#pragma once

// accept_Clnt 명령 대상

class accept_Clnt : public CSocket
{
public:

	accept_Clnt();
	virtual ~accept_Clnt();
	virtual void OnReceive(int nErrorCode);
};


