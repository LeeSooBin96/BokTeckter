// accept_Clnt.cpp: 구현 파일
//

#include "pch.h"
#include "mfcAsyncSver.h"
#include "accept_Clnt.h"
#include <iostream>
#include "listenSock.h"


// accept_Clnt

accept_Clnt::accept_Clnt()
{
}

accept_Clnt::~accept_Clnt()
{
}


void accept_Clnt::OnReceive(int nErrorCode)
{
	//CByteArray fileData; // 객체 만들어주고
	//int value;
	//Receive(&value, sizeof(value));

	//std::cout << "111" << std::endl;

	//if (Receive(&fileData, value) > 0) {
	//	std::cout << "받냐?" << std::endl;
	//	CString Path = _T("C:/Users/user/Desktop/sample_test/PY.png");// 지정하고
	//	CFile saveFile(Path, CFile::modeCreate | CFile::modeWrite);
	//	saveFile.Write(fileData.GetData(), value); //데이터 파일에 쓰고
	//	saveFile.Close(); // 파일 닫고
	//}

	CSocket::OnReceive(nErrorCode);
}

//송신 수신부를 어떻게 나눌까?
//C#에서 받고
//그 사진을 화면에 띄우고
//주피터에 보내고
//주피터한테 결과 받고
//ok 넘어가->C#에 보내기
//no일때 검사 -> C#에 결과 보내기