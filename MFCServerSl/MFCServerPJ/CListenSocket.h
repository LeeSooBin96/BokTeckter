//서버 오픈 및 클라이언트 연결 클래스
#pragma once

// CListenSocket 명령 대상
class CMFCServerPJDlg; //다이얼로그 클래스

class CListenSocket : public CAsyncSocket
{

public:
	CMFCServerPJDlg* m_pDlg; //다이얼로그 클래스에 접근할 포인터 변수

	CListenSocket(CMFCServerPJDlg* pDlg);
	virtual ~CListenSocket();
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


