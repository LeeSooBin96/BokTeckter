
// MFCServerPJDlg.h: 헤더 파일
//

#pragma once
#include "CListenSocket.h"
#include "CDataSocket.h"
#include "CDBHandle.h"

// CMFCServerPJDlg 대화 상자
class CMFCServerPJDlg : public CDialogEx
{
	CListenSocket* m_pListenSock; //서버 오픈 클래스
	CDBHandle* m_pDB; //DB 연동 클래스
	/* 저장할 소켓 멤버 */
	CSocket* m_pAIClient; //AI 모델 연결 소켓
	CArray<CDataSocket*> m_arrCLTList; //클라이언트 연결 소켓

	/* 생성한 메서드 */
	void sendIMGToAI(int); //AI에 검사 이미지 송신
	void showRecvIMG(); //화면에 수신된 이미지 출력
	bool* checkProduct(int nPNum); //제품 검사(각 부분별 검사 결과 반환)
	void saveResultIMG(); //결과 이미지 저장
	/* 이미지 그레이 레벨 변환 및 색상 추출 */
	void changeIMGtoGray(int nPNum, int nHeight, int nWidth, int nPitch, double nRateX, double nRateY,
		unsigned char* fmO, unsigned char* fmG, CArray<CPoint>& arrColor);
	bool examinePrint(int nPNum, int nWidth, CArray<CPoint>& arrContour,CArray<CPoint>& arrColor); //프린팅 상태 검사
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
	void ProcessAccept(int nErrorCode);
	void ProcessClose(int nErrorCode);
	void ProcessReceive(CDataSocket* pSocket, int nErrorCode);
	CStatic m_ctrl_recv; //IDC_IMG_RECV
	CStatic m_ctrl_result; //IDC_IMG_RESULT
};
