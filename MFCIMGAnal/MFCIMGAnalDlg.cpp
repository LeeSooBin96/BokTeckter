
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
	/* 1. 색상 - 초록색 검사
	 * 그레이 레벨 변환해서
	 * 건전지 테두리 따기
	 * 2. 두께 길이 측정
	 * 3. 극 여부 판단
	 */
	CRect rect; //픽쳐 컨트롤의 크기를 저장할 rect
	m_picture_control.GetWindowRect(rect); //컨트롤 크기 가져오기
	CDC* dc; //픽쳐 컨트롤의 dc 포인터 --GDI에 접근하기 위함
	dc = m_picture_control.GetDC();

	CPngImage pngImg; //png파일은 리소스 파일로 다뤄야함
	pngImg.Load(IDB_PNG, AfxGetResourceHandle());
	CBitmap bitmap; //비트맵 이미지로 변환
	bitmap.Attach(pngImg.Detach());
	CImage image;
	image.Attach(bitmap);
	
	int nWidth = image.GetWidth();
	int nHeight = image.GetHeight();
	unsigned char* fm = (unsigned char*)image.GetBits();

	//화면상 상대 위치값 구하기위함(화면상 좌표)
	double nRateX = (double)rect.Width() / nWidth;
	double nRateY = (double)rect.Height() / nHeight;

	CImage grayImg;
	grayImg.Create(nWidth, nHeight, 8);
	static RGBQUAD rgb[256];
	for (int i = 0; i < 256; i++)
	{
		rgb[i].rgbRed = rgb[i].rgbBlue = rgb[i].rgbGreen = i;
	}
	grayImg.SetColorTable(0, 256, rgb);
	unsigned char* fmG = (unsigned char*)grayImg.GetBits();



	int nPitch = grayImg.GetPitch();
	/* 색상 검사 - 초록색 머리 존재 */
	CArray<CPoint> arrGPoint;
	/* */
	for (int j = 0;j < nHeight;j++) {
	    for (int i = 0;i < nWidth;i++) {
	        unsigned char r, g, b;
	        r = fm[j * 3 * nPitch + i * 3 + 2];
	        g = fm[j * 3 * nPitch + i * 3 + 1];
	        b = fm[j * 3 * nPitch + i * 3 ]; //bgr 순서
	        fmG[j * nPitch + i] = 0.299 * r + 0.587 * g + 0.114 * b;
			/* 색상 검사 - 초록색 머리 존재 */
			if (r == 0 && b == 0 && g>100 && i > 240 && i < 400 && j < 240) //이미지 중앙 상단부에 초록색 탐지
			{
				arrGPoint.Add(CPoint(i*nRateX, j*nRateY));
			}
	    }
	}
	cout << arrGPoint.GetCount() << endl;
	
	//이미지를 픽쳐 컨트롤 크기로
	image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);
	

	/* 건전지 찾아내기 테두리 포인트 찾아냄*/
	CArray<CPoint> arrContour;

	for (int j = 50; j < 480; j++) {
		for (int i = 200; i < 400; i++) {
			if (abs(fmG[j * nPitch + i] - fmG[j * nPitch + i + 1]) > 5) { //명도차이가 10이상이면
				arrContour.Add(CPoint(i * nRateX, j * nRateY));
			}
		}
	}

	//선 그리기
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(0xff, 0xff, 0)); //펜 노란색으로
	CPen* pOldPen = dc->SelectObject(&pen); //새펜으로 선택하고 기존 펜 반환
	CBrush* pOldBrush = (CBrush*)dc->SelectStockObject(NULL_BRUSH); //색채우기 끄기
	//dc->Ellipse(CRect(300 * nRateX, 80 * nRateY, 360 * nRateX, 100 * nRateY));
	//dc->MoveTo(280*nRateX, 100*nRateY);
	//dc->LineTo(380*nRateX, 450*nRateY);

	/* 색상 검출 결과 프린트 */
	//for (int i = 0; i < arrGPoint.GetCount(); i++) {
	//	dc->Ellipse(arrGPoint[i].x, arrGPoint[i].y, arrGPoint[i].x + 1, arrGPoint[i].y + 1);
	//}
	int nLeftX = arrGPoint[0].x;
	int nLeftY = arrGPoint[0].y;
	int nRightX = arrGPoint[0].x;
	int nRightY = arrGPoint[0].y;

	for (int i = 0; i < arrGPoint.GetCount(); i++) {
		if (arrGPoint[i].x < nLeftX) nLeftX = arrGPoint[i].x;
		else if (arrGPoint[i].x > nRightX) nRightX = arrGPoint[i].x;
		if (arrGPoint[i].y < nLeftY) nLeftY = arrGPoint[i].y;
		else if (arrGPoint[i].y > nRightY) nRightY = arrGPoint[i].y;
	}
	int nGreenMinY = nLeftY;

	dc->Rectangle(nLeftX, nLeftY, nRightX, nRightY);
	dc->TextOutW(nRightX, nRightY, _T("Green Head"));
	/* */

	CPen pen2;
	pen2.CreatePen(PS_SOLID, 2, RGB(0, 0xff, 0));
	dc->SelectObject(&pen2);
	//for (int i = 0; i < arrContour.GetCount(); i++) {
	//	dc->Ellipse(arrContour[i].x, arrContour[i].y, arrContour[i].x + 1, arrContour[i].y + 1);
	//}
	for (int i = 0; i < arrContour.GetCount(); i++) {
		if (arrContour[i].x < nLeftX) nLeftX = arrContour[i].x;
		else if (arrContour[i].x > nRightX) nRightX = arrContour[i].x;
		if (arrContour[i].y < nLeftY) nLeftY = arrContour[i].y;
		else if (arrContour[i].y > nRightY) nRightY = arrContour[i].y;
	}
	/*너비 출력*/
	dc->MoveTo(nLeftX, nLeftY + (nRightY - nLeftY) / 2);
	dc->LineTo(nLeftX + 5, nLeftY +(nRightY - nLeftY) / 2 - 5);
	dc->MoveTo(nLeftX, nLeftY + (nRightY - nLeftY) / 2);
	dc->LineTo(nLeftX + 5, nLeftY + (nRightY - nLeftY) / 2 + 5);
	dc->MoveTo(nLeftX, nLeftY + (nRightY - nLeftY) / 2);
	dc->LineTo(nRightX, nLeftY + (nRightY - nLeftY) / 2);
	dc->LineTo(nRightX - 5, nLeftY + (nRightY - nLeftY) / 2 - 5);
	dc->MoveTo(nRightX, nLeftY + (nRightY - nLeftY) / 2);
	dc->LineTo(nRightX - 5, nLeftY + (nRightY - nLeftY) / 2 + 5);

	CString strWidth;
	strWidth.Format(_T("Width : %d"), nRightX - nLeftX);
	dc->TextOutW(nRightX, nLeftY+(nRightY - nLeftY) / 2, strWidth);

	/*높이 출력*/
	dc->MoveTo(nLeftX+(nRightX-nLeftX)/2, nLeftY);
	dc->LineTo(nLeftX + (nRightX - nLeftX) / 2 - 5, nLeftY + 5);
	dc->MoveTo(nLeftX + (nRightX - nLeftX) / 2, nLeftY);
	dc->LineTo(nLeftX + (nRightX - nLeftX) / 2 + 5, nLeftY + 5);
	dc->MoveTo(nLeftX + (nRightX - nLeftX) / 2, nLeftY);
	dc->LineTo(nLeftX + (nRightX - nLeftX) / 2, nRightY);
	dc->LineTo(nLeftX + (nRightX - nLeftX) / 2 - 5, nRightY - 5);
	dc->MoveTo(nLeftX + (nRightX - nLeftX) / 2, nRightY);
	dc->LineTo(nLeftX + (nRightX - nLeftX) / 2 + 5, nRightY - 5);

	CString strHeight;
	strWidth.Format(_T("Height : %d"), nRightY - nLeftY);
	dc->TextOutW(nLeftX + (nRightX - nLeftX) / 2, nRightY, strWidth);

	CPen pen3;
	pen3.CreatePen(PS_SOLID, 2, RGB(0xff, 0, 0));
	dc->SelectObject(&pen3);

	cout << nGreenMinY - nLeftY << endl;
	if(nGreenMinY-nLeftY<5){
		dc->TextOutW(nLeftX + (nRightX - nLeftX) / 2, nLeftY - 20, _T("Pole : false"));
	}
	else {
		dc->Ellipse(CRect(nLeftX + (nRightX - nLeftX) / 2 -10, nLeftY + 10, nLeftX + (nRightX - nLeftX) / 2+10, nLeftY));
		dc->TextOutW(nLeftX + (nRightX - nLeftX) / 2, nLeftY - 20, _T("Pole : true"));
	}

	dc->SelectObject(pOldPen); //기존 펜으로 복구
	dc->SelectObject(pOldBrush);
	//UpdateData();

	ReleaseDC(dc); //dc할당 해제
}

//bool CMFCIMGAnalDlg::isGreenHead(CImage* image)
//{ // 초록색 탐지
//
//	int nWidth = image->GetWidth();
//	int nHeight = image->GetHeight();
//	int nPitch = image->GetPitch();
//
//	unsigned char* fm = (unsigned char*)image->GetBits();
//
//	CArray<CPoint> arrPoint;
//	for (int j = 0; j < nHeight; j++) {
//		for (int i = 0; i < nWidth; i++) {
//			unsigned char r, g, b;
//			r = fm[j * 3 * nPitch + i * 3 + 2];
//			g = fm[j * 3 * nPitch + i * 3 + 1];
//			b = fm[j * 3 * nPitch + i * 3];
//			if (r == 0 && b == 0 && i > 240 && i < 400 && j < 240) //이미지 중앙의 초록색 탐지
//				arrPoint.Add(CPoint(i, j));
//		}
//	}
//
//	cout << arrPoint.GetCount() << endl;
//	return false;
//}