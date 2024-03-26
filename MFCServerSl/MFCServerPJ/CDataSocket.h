//데이터 송수신 관련 클래스
#pragma once

// CDataSocket 명령 대상
class CMFCServerPJDlg; //다이얼로그 클래스

class CDataSocket : public CAsyncSocket
{

public:
	CDataSocket(CMFCServerPJDlg* pDlg);
	virtual ~CDataSocket();
	virtual void OnReceive(int nErrorCode);

	CMFCServerPJDlg* m_pDlg; //다이얼로그 클래스에 접근할 포인터 변수

	/* 자체 제작 데이터 송수신 함수 */
	int RecvData();
};


