
// mfcAsyncSver.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "mfcAsyncSver.h"
#include "mfcAsyncSverDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmfcAsyncSverApp

BEGIN_MESSAGE_MAP(CmfcAsyncSverApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CmfcAsyncSverApp 생성

CmfcAsyncSverApp::CmfcAsyncSverApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CmfcAsyncSverApp 개체입니다.

CmfcAsyncSverApp theApp;


// CmfcAsyncSverApp 초기화

BOOL CmfcAsyncSverApp::InitInstance()
{
	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	CmfcAsyncSverDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	
	return FALSE;
}

