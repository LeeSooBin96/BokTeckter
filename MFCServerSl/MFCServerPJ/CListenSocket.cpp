// CListenSocket.cpp: 구현 파일
//

#include "pch.h"
#include "MFCServerPJ.h"
#include "CListenSocket.h"

#include "MFCServerPJDlg.h"

// CListenSocket

CListenSocket::CListenSocket(CMFCServerPJDlg* pDlg)
{
	m_pDlg = pDlg;
}

CListenSocket::~CListenSocket()
{
}


// CListenSocket 멤버 함수


void CListenSocket::OnAccept(int nErrorCode)
{
	CAsyncSocket::OnAccept(nErrorCode);
	m_pDlg->ProcessAccept(nErrorCode);
}


void CListenSocket::OnClose(int nErrorCode)
{
	CAsyncSocket::OnClose(nErrorCode);
	m_pDlg->ProcessClose(nErrorCode);
}


