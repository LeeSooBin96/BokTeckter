// listenSock.cpp: 구현 파일
//

#include "pch.h"
#include "mfcAsyncSver.h"
#include "listenSock.h"
#include <iostream>


// listenSock

listenSock::listenSock()
{
}

listenSock::~listenSock()
{
}


// listenSock 멤버 함수


void listenSock::OnAccept(int nErrorCode)
{	//listenSock이 CAsyncSocket상속이라 비동기로 돌아가고
	//accept될 때마다 동적으로 accept_clnt의 객체가 만들어지는 듯
	accept_Clnt* pClient = new accept_Clnt; 

	if (Accept(*pClient)) {
		clntlist.Add(pClient);

		//CString a = _T("안녕");
		//std::string message = CT2CA(a, CP_UTF8);
		//for (int i = 0; i < clntlist.GetCount(); i++) {
		//	clntlist[i]->Send(message.c_str(), message.size());
		//}

		int value;
		Receive(&value, sizeof(value));
		clntlist[0]->Receive(&value, sizeof(value));

		std::cout << value << std::endl;
		char* buff = new char[value];
		if (int len=clntlist[0]->Receive(buff, value) > 0)
		{
			std::cout <<  len<< std::endl;
			CString Path = _T("C:/Users/user/Desktop/sample_test/PY11.png"); // 파일 경로 지정
			CFile saveFile; // 객체 만들고
			saveFile.Open(Path, CFile::modeCreate | CFile::modeWrite| CFile::typeBinary);
			saveFile.Write(buff, value);
			//saveFile.Flush();
			saveFile.Close(); // 파일 닫기
		}

		


	}
	else {
		// 연결 수락 실패
		delete pClient;
	}
	CAsyncSocket::OnAccept(nErrorCode);
}





void listenSock::SendMsg(CDialog* pDialog)
{
	std::cout << "실행되냐?" << std::endl;

	wchar_t* str_1 = L"PY1";
	CString a = _T("안녕");
	std::string message = CT2CA(a, CP_UTF8);
	list[str_1]->Send(message.c_str(), message.size());
	//wchar_t형식이 _T("PY1")맞는거같은데

	wchar_t* str_2 = L"PY2";
	CString b = _T("잘가");
	std::string message_1 = CT2CA(a, CP_UTF8);
	list[str_2]->Send(message_1.c_str(), message_1.size());

	

}

