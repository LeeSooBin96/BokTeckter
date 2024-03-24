﻿
// MFCServerPJDlg.h: 헤더 파일
//

#pragma once
#include "CDBHandle.h"

// CMFCServerPJDlg 대화 상자
class CMFCServerPJDlg : public CDialogEx
{
	CDBHandle* m_pDB = NULL; //DB 연동 클래스
// 생성입니다.
public:
	CMFCServerPJDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCSERVERPJ_DIALOG };
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
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnDestroy();
};
