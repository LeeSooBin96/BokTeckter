
// mfcAsyncSverDlg.h: 헤더 파일
//
#include "listenSock.h"
#include "accept_Clnt.h"

#pragma once


// CmfcAsyncSverDlg 대화 상자
class CmfcAsyncSverDlg : public CDialogEx
{
// 생성입니다.
public:
	CmfcAsyncSverDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	listenSock m_listenSock;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCASYNCSVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void openServer();
	afx_msg void OnBnClickedButton1();
};
