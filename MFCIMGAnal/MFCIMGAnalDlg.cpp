
// MFCIMGAnalDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCIMGAnal.h"
#include "MFCIMGAnalDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCIMGAnalDlg 대화 상자



CMFCIMGAnalDlg::CMFCIMGAnalDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCIMGANAL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCIMGAnalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE, m_picture_control);
}

BEGIN_MESSAGE_MAP(CMFCIMGAnalDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_IMG, &CMFCIMGAnalDlg::OnBnClickedBtnImg)
END_MESSAGE_MAP()


// CMFCIMGAnalDlg 메시지 처리기

BOOL CMFCIMGAnalDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCIMGAnalDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCIMGAnalDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCIMGAnalDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


#include <iostream>
using namespace std;
void CMFCIMGAnalDlg::OnBnClickedBtnImg()
{
	/* 픽처 컨트롤 다루기 위한 준비 */
	CRect rect; //픽처 컨트롤 크기를 저장할 rect
	m_picture_control.GetWindowRect(rect); //컨트롤 크기 가져오기
	CDC* dc; //픽처 컨트롤 dc 포인터
	dc = m_picture_control.GetDC(); //dc 가져오기

	/* 이미지 로드 */
	CPngImage pngImg; //png파일을 다룰때는 리소스 파일 활용
	pngImg.Load(IDB_PNG,AfxGetResourceHandle());
	CBitmap bitmap; //비트맵 이미지로 변환하기
	bitmap.Attach(pngImg.Detach());
	CImage image; //검사할 이미지 객체로 로드
	image.Attach(bitmap);

	/* 화면에 이미지 출력 */
	image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);

	/* 이미지 검사에 필요한 변수 */
	int nWidth = image.GetWidth(); //이미지 너비
	int nHeight = image.GetHeight(); //이미지 높이
	unsigned char* fmO = (unsigned char*)image.GetBits(); //원본 이미지 픽셀 포인터

	//화면상 상대 위치값 구하기 위한 비율값
	double nRateX = (double)rect.Width() / nWidth;
	double nRateY = (double)rect.Height() / nHeight;

	CImage grayImg; //그레이 레벨로 변환한 이미지 저장할 객체
	grayImg.Create(nWidth, nHeight, 8); 
	static RGBQUAD rgb[256];
	for (int i = 0; i < 256; i++) {
		rgb[i].rgbRed = rgb[i].rgbBlue = rgb[i].rgbGreen = i;
	}
	grayImg.SetColorTable(0, 256, rgb);
	unsigned char* fmG = (unsigned char*)grayImg.GetBits(); //그레이 레벨 이미지 픽셀 포인터

	int nPitch = grayImg.GetPitch(); //피치(한행 픽셀수)는 그레이 레벨값만 필요
	/* 여기까지 필요한 변수들 준비 완료 */
	
	/* 검사할 사항
	 * 1. 몸통 너비, 높이 --명암 변화로 계산 완료
	 * 2. 극의 존재 여부 --위에서 구한 값으로 수치 통계내면 됨
	 * 3. 프린팅 상태 --이게 문제임... 어떻게 할까
	 * 우선 이미지 그레이 레벨로 변환 */
	/* 색상 추출할 배열 */
	//CArray<CPoint> arrRocket; //제품: 로케트
	CArray<CPoint> arrEnergizer; //제품: 에너자이저
	//CArray<CPoint> arrDuracell; //제품: 듀라셀
	//CArray<CPoint> arrBexelB; //제품: 벡셀 B타입
	//CArray<CPoint> arrBexelA; //제품: 백셀 A타입

	for (int j = 0; j < nHeight; j++) {
		for (int i = 0; i < nWidth; i++) {
			unsigned char r, g, b;
			r = fmO[j * 3 * nPitch + i * 3 + 2];
			g = fmO[j * 3 * nPitch + i * 3 + 1];
			b = fmO[j * 3 * nPitch + i * 3 ]; //bgr 순서
			fmG[j * nPitch + i] = 0.299 * r + 0.587 * g + 0.114 * b;
			/*if (j > 360 && j < 450 && i > 250 && i < 420) {
			if (r < 100 && g < 100 && b>150)
				arrRocket.Add(CPoint(i * nRateX, j * nRateY));
			}*/
			if ( j > 70 && j < 200 && i > 200 && i < 470) {
				if (r == 0 && g == 0 && b == 0)
					arrEnergizer.Add(CPoint(i * nRateX, j * nRateY));
			}
			//if (j>70&&j<220 && i > 200 && i < 470) { //70,220,200,470
			//	if (r>=100&&r<125&&g>40&&g<90&&b>10&&b<100 ||
			//		r>=70&&r<100&&g>10&&g<50&&b<10)
			//		arrDuracell.Add(CPoint(i * nRateX, j * nRateY));
			//}
			//if (j>70&&j<180 && i > 200 && i < 470) { //70,180
			//	if (r == 0 && b == 0 && g > 90)
			//		arrBexelB.Add(CPoint(i * nRateX, j * nRateY));
			//}
			//if (j >300&&j<450 && i > 200 && i < 470) { //300,450
			//	if (r > 70 && r < 175 && g < 100 && b < 50)
			//		arrBexelA.Add(CPoint(i * nRateX, j * nRateY));
			//	//cout << "( " << i << ", " << j << " ) R: " << (int)r << " G: " << (int)g << " B: " << (int)b << endl;
			//}
		}
	}
	//cout << "( " << i << ", " << j << " ) R: " << (int)r << " G: " << (int)g << " B: " << (int)b << endl;
	//grayImg.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY); //확인용
	//cout << "Blue Bottom: " << arrRocket.GetCount() << endl;
	cout << "Black Head: " << arrEnergizer.GetCount() << endl;
	//cout << "Orange Head: " << arrDuracell.GetCount() << endl;
	//cout << "Green Head: " << arrBexelB.GetCount() << endl;
	//cout << "Orange Bottom: " << arrBexelA.GetCount() << endl;

	/* 건전지(객체) 찾아내기 - 명암 변화 이용 */
	CArray<CPoint> arrContour;
	for (int j = 50; j < 460; j++) { //높이 범위
		for (int i = 200; i < 470; i++) { //너비 범위
			if (abs(fmG[j * nPitch + i] - fmG[j * nPitch + i + 1]) > 5)
				arrContour.Add(CPoint(i * nRateX, j * nRateY)); //명도차이로 객체 인식
		}
	}
	cout << "Object Number: " << arrContour.GetCount() << endl;

	/* 인식된 객체의 높이 너비 구하기 */
	int nLeftX = arrContour[0].x;
	int nLeftY = arrContour[0].y;
	int nRightX = arrContour[0].x;
	int nRightY = arrContour[0].y;

	for (int i = 0; i < arrContour.GetCount(); i++) {
		if (arrContour[i].x < nLeftX) nLeftX = arrContour[i].x;
		else if (arrContour[i].x > nRightX) nRightX = arrContour[i].x;
		if (arrContour[i].y < nLeftY) nLeftY = arrContour[i].y;
		else if (arrContour[i].y > nRightY) nRightY = arrContour[i].y;
	}
	cout << "건전지 전체 높이: " << nRightY - nLeftY << ", 너비: " << nRightX - nLeftX << endl;
	/* 건전지 몸통의 높이 구하기(너비는 위에서 구한 것과 일치) */
	int nBodyY = nRightY;
	for (int i = 0; i < arrContour.GetCount(); i++) {
		if (((arrContour[i].x >= nLeftX && arrContour[i].x <= nLeftX + 5)
			|| (arrContour[i].x >= nRightX - 5 && arrContour[i].x <= nRightX))
			&& arrContour[i].y < nBodyY)
			nBodyY = arrContour[i].y;
	}
	cout << "건전지 몸통 높이: " << nRightY - nBodyY << endl;

	/* 검출 결과 화면에 그리기 */
	CPen yelloPen;
	yelloPen.CreatePen(PS_SOLID, 2, RGB(0xff, 0xff, 0));
	CPen* pOldPen = dc->SelectObject(&yelloPen); //새 펜 적용하고 기존 펜 반환
	CBrush* pOldBrush = (CBrush*)dc->SelectStockObject(NULL_BRUSH); //색채우기 끄기

	//dc->Rectangle(200 * nRateX, 300 * nRateY, 470 * nRateX, 450 * nRateY); //범위 확인용
	//200,470

	for (int i = 0; i < arrContour.GetCount(); i++) { //객체 인식 확인용
		dc->Ellipse(arrContour[i].x, arrContour[i].y, arrContour[i].x + 1, arrContour[i].y + 1);
	}
	CPen greenPen;
	greenPen.CreatePen(PS_SOLID, 2, RGB(0, 0xff, 0));
	dc->SelectObject(&greenPen);
	//for (int i = 0; i < arrRocket.GetCount(); i++) { //객체 인식 확인용
	//	dc->Ellipse(arrRocket[i].x, arrRocket[i].y, 
	// arrRocket[i].x+1, arrRocket[i].y+1);
	//}
	for (int i = 0; i < arrEnergizer.GetCount(); i++) { //객체 인식 확인용
		dc->Ellipse(arrEnergizer[i].x, arrEnergizer[i].y, arrEnergizer[i].x+1, arrEnergizer[i].y+1);
	}
	//for (int i = 0; i < arrDuracell.GetCount(); i++) { //객체 인식 확인용
	//	dc->Ellipse(arrDuracell[i].x, arrDuracell[i].y, arrDuracell[i].x+1, arrDuracell[i].y+1);
	//}
	//for (int i = 0; i < arrBexelB.GetCount(); i++) { //객체 인식 확인용
	//	dc->Ellipse(arrBexelB[i].x, arrBexelB[i].y, arrBexelB[i].x+1, arrBexelB[i].y+1);
	//}
	//for (int i = 0; i < arrBexelA.GetCount(); i++) { //객체 인식 확인용
	//	dc->Ellipse(arrBexelA[i].x, arrBexelA[i].y, arrBexelA[i].x+1, arrBexelA[i].y+1);
	//}

	/* 몸통 높이,너비 출력 */
	

	dc->SelectObject(pOldPen); //기존 펜으로 복구
	dc->SelectObject(pOldBrush); //기존 브러쉬 반환
	ReleaseDC(dc); //할당 해제
}

