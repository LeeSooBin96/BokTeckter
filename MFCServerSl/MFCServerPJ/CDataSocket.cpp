// CDataSocket.cpp: 구현 파일
//

#include "pch.h"
#include "MFCServerPJ.h"
#include "CDataSocket.h"

#include "MFCServerPJDlg.h"
// CDataSocket

CDataSocket::CDataSocket(CMFCServerPJDlg* pDlg)
{
	m_pDlg = pDlg;
}

CDataSocket::~CDataSocket()
{
}


// CDataSocket 멤버 함수


void CDataSocket::OnReceive(int nErrorCode)
{
	CAsyncSocket::OnReceive(nErrorCode);
	m_pDlg->ProcessReceive(this, nErrorCode);
}
 /* 클라이언트 이미지 수신 및 파일 저장 */
int CDataSocket::RecvData()
{
	/* 메시지 길이 먼저 수신 -> 메시지 수신 */
	int nLen; //수신할 데이터 길이 
	if (this->Receive(&nLen, 4, 0) < 0 || nLen < 0) return -1;
	
	//cout << "받아야할 데이터 길이 : " << nLen << endl;

	TCHAR* buffer = new TCHAR[nLen];

	CFile saveFile; // 객체 만들고
	saveFile.Open(_T("..//save.bmp"), CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
	int recvLen = this->Receive(buffer, nLen, 0);
	saveFile.Write(buffer, recvLen);
	
	cout << "수신받은 데이터 길이" << recvLen << endl;
	while (recvLen != nLen) {
		TCHAR* temp=new TCHAR[10000];
		int nTmp = 0;
		nTmp=this->Receive(temp, 10000, 0);
		recvLen += nTmp;
		cout << "얼마나 오고있나 " << nTmp << " 총 " << recvLen << endl;
		if (nTmp < 0) break;
		saveFile.Write(temp, nTmp);
		delete[] temp;
	}
	
	saveFile.Close();
	delete[] buffer;
	
	return recvLen;
}