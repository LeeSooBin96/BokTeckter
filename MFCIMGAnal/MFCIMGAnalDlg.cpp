
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CRect rect; //픽쳐 컨트롤의 크기를 저장할 rect
	m_picture_control.GetWindowRect(rect); //컨트롤 크기 가져오기
	CDC* dc; //픽쳐 컨트롤의 dc 포인터 --GDI에 접근하기 위함
	dc = m_picture_control.GetDC();
	//CImage image;
	//image.Load(_T("test.png")); //이미지 로드
	//일반적인 이미지 로드는 bmp파일만 된다.
	CPngImage pngImg; //png파일은 리소스 파일로 다뤄야함
	pngImg.Load(IDB_PNG, AfxGetResourceHandle());
	CBitmap bitmap; //비트맵 이미지로 변환
	bitmap.Attach(pngImg.Detach());
	CImage image;
	image.Attach(bitmap);

	int nWidth = image.GetWidth();
	int nHeight = image.GetHeight();
	unsigned char* fm = (unsigned char*)image.GetBits();

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
	for (int j = 0;j < nHeight;j++) {
	    for (int i = 0;i < nWidth;i++) {
	        unsigned char r, g, b;
	        r = fm[j * 3 * nPitch + i * 3 + 2];
	        g = fm[j * 3 * nPitch + i * 3 + 1];
	        b = fm[j * 3 * nPitch + i * 3 ]; //bgr 순서
	        fmG[j * nPitch + i] = 0.299 * r + 0.587 * g + 0.114 * b;
			//if(r==0&&b==0&&j>80&&j<100&&i>300&&i<360)
			//cout << "좌표 : " << i << ", " << j << "\t"<<(int)fmG[j * nPitch + i] << endl;
	    }
	}

	//이미지를 픽쳐 컨트롤 크기로
	grayImg.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);
	//상대 위치값 구하기위함(화면상 좌표)
	double nRateX = (double)rect.Width() / nWidth;
	double nRateY = (double)rect.Height() / nHeight;

	//외곽선 찍을 점들 저장할 배열 혹은 리스트 만들기
	CArray<CPoint> arrContour;

	for (int j = 50; j < 450; j++) {
		for (int i = 200; i < 400; i++) {
			if (abs(fmG[j * nPitch + i] - fmG[j * nPitch + i + 1]) > 10) { //명도차이가 50이상이면
				arrContour.Add(CPoint(i * nRateX, j * nRateY));
				cout << i << " " << j << endl;
			}
		}
	}

	//선 그리기
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(0xff, 0xff, 0)); //펜 노란색으로
	CPen* pOldPen = dc->SelectObject(&pen); //새펜으로 선택하고 기존 펜 반환
	//CBrush* pOldBrush = (CBrush*)dc->SelectStockObject(NULL_BRUSH); //색채우기 끄기
	//dc->Ellipse(CRect(300 * nRateX, 80 * nRateY, 360 * nRateX, 100 * nRateY));
	//dc->MoveTo(280*nRateX, 100*nRateY);
	//dc->LineTo(380*nRateX, 450*nRateY);

	for (int i = 0; i < arrContour.GetCount(); i++) {
		dc->Ellipse(arrContour[i].x, arrContour[i].y, arrContour[i].x + 1, arrContour[i].y + 1);
	}

	dc->SelectObject(pOldPen); //기존 펜으로 복구
	//dc->SelectObject(pOldBrush);
	UpdateData();

	ReleaseDC(dc); //dc할당 해제
}
