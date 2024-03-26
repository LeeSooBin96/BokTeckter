// MyServer.cpp: 구현 파일
//

#include "pch.h"
#include "MFC_sver.h"
#include "MyServer.h"


// MyServer

MyServer::MyServer()
{
}

MyServer::~MyServer()
{
}


// MyServer 멤버 함수


void MyServer::OnAccept(int nErrorCode)
{
	Accept(m_user); //m_user 클래스의 주소가 넘어감
	//그럼 m_user가 Accept됨

	CSocket::OnAccept(nErrorCode);
}

void MyServer::SendMessage(CDialog* pDialog)
{

	CString file = _T("C:/Users/user/Desktop/sample_test/bbb.png");
	//이 파일 경로를 이제 C#클라가 보내는 
	CFile openfile;

	// 파일 열기
	if (openfile.Open(file, CFile::modeRead)) {
		ULONGLONG openFileSize = openfile.GetLength();
		// 파일 내용 읽어서 길이
		m_user.Send(&openFileSize, sizeof(ULONGLONG));//전송
		std::cout << openFileSize << std::endl;
		//const int buffer_size = 225545;//버퍼사이즈

		CByteArray fileData;
		fileData.SetSize(openFileSize);//객체크기를 배열 사이즈만큼
		openfile.Read(fileData.GetData(), openFileSize);
		openfile.Close();

		m_user.Send(fileData.GetData(), openFileSize);

	}
	else {
		std::cout << "파일없음" << std::endl;
	}
	



	//CString text;
	//pDialog->GetDlgItemTextW(IDC_VALUE_EDIT, text); //에딧에서 글자 가져옴
	//CString name = _T("서버1번");
	////GetDlgItemTextW가 유니코드만 인식해서 CStringA로 아스키로 변환해야함
	//CStringA utf8Text(name +_T("@") + text); //CStringA로 utf8화 시킴
	//	
	//int textSize = utf8Text.GetLength();
	//m_user.Send(&textSize, sizeof(int)); //길이 보내고
	//m_user.Send(utf8Text, textSize); //내용 보냄

}

void MyServer::SendMessage_2(CDialog* pDialog)
{

	CString text;
	pDialog->GetDlgItemTextW(IDC_VALUE_EDIT2, text); //에딧에서 글자 가져옴
	CString name = _T("서버2번");
	//GetDlgItemTextW가 유니코드만 인식해서 CStringA로 아스키로 변환해야함
	CStringA utf8Text(name + _T("@") + text); //CStringA로 utf8화 시킴

	int textSize = utf8Text.GetLength();
	m_user.Send(&textSize, sizeof(int)); //길이 보내고
	m_user.Send(utf8Text, textSize); //내용 보냄

}
