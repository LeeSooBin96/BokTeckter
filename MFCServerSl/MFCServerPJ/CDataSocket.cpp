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
 /* 데이터 수신 스레드 (수신 메시지 저장할 버퍼 인자로 받음) */
void CDataSocket::RecvData(TCHAR* &buffer)
{
	/* 메시지 길이 먼저 수신 -> 메시지 수신 */
	int nLen; //수신할 데이터 길이 
	this->Receive(&nLen, 4, 0);

	buffer = new TCHAR[nLen];
	//CByteArray* buffer=new CByteArray;
	//buffer->SetSize(nLen);
	int recvLen = this->Receive(buffer, nLen, 0);
	//buffer[nLen-2] = '\0';
	//cout << (LPCSTR)buffer << endl;
	
	//CFile saveFile; // 객체 만들고
	//saveFile.Open(_T("..//save.png"), CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
	//saveFile.Write(buffer, nLen); //파일 저장 잘되는것 까지 확인 완료
	//saveFile.Close();
}