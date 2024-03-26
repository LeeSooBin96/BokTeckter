// MFCServerPJDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCServerPJ.h"
#include "MFCServerPJDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#pragma comment(linker,"/entry:wWinMainCRTStartup /subsystem:console")
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


// CMFCServerPJDlg 대화 상자



CMFCServerPJDlg::CMFCServerPJDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSERVERPJ_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	AfxSocketInit(); //소켓 함수 사용을 위함

	/* 멤버 포인터 변수 초기화 */
	m_pListenSock = NULL;
	m_pDB = NULL;

	m_pAIClient = NULL;
}

void CMFCServerPJDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMG_RECV, m_ctrl_recv);
	DDX_Control(pDX, IDC_IMG_RESULT, m_ctrl_result);
}

BEGIN_MESSAGE_MAP(CMFCServerPJDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN, &CMFCServerPJDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CMFCServerPJDlg::OnBnClickedBtnClose)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCServerPJDlg 메시지 처리기

BOOL CMFCServerPJDlg::OnInitDialog()
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
	SetWindowText(_T("MFCServer")); /* 창 제목 설정 */
	/* 컨트롤 폰트 크기 설정 */
	CFont font;
	GetDlgItem(IDC_STATIC_AI)->SetFont(&font);
	GetDlgItem(IDC_AI_RESULT)->SetFont(&font);
	GetDlgItem(IDC_BTN_OPEN)->SetFont(&font);
	GetDlgItem(IDC_BTN_CLOSE)->SetFont(&font);


	

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCServerPJDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCServerPJDlg::OnPaint()
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
HCURSOR CMFCServerPJDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void ErrQuit(int err) //오류 상황을 파악할 수 있는 코드!
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, err,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL); //lpMsgBuf에 에러 메시지 받아오는 듯!
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, _T("오류 발생"), MB_ICONERROR); //에러 메시지 박스 출력
	LocalFree(lpMsgBuf); //메모리 할당 해제 같지?
	//exit(1); //프로그램 종료
}

void CMFCServerPJDlg::OnBnClickedBtnOpen()
{ 
	/* 서버 오픈 */
	//서버 오픈 -> AI 모델 연결/ DB 연결 -> 클라이언트 연결 대기
	//서버 오픈
	if (m_pListenSock != NULL) {
		AfxMessageBox(_T("서버가 이미 오픈되어 있습니다."), MB_ICONERROR);
		return;
	}
	m_pListenSock = new CListenSocket(this);
	if(!m_pListenSock->Create(26001)) ErrQuit(m_pListenSock->GetLastError());
	if(!m_pListenSock->Listen()) cout<<"연결 대기 x \n"; //클라이언트 연결 대기
	cout << "서버가 오픈되었습니다.\n";
	
	//DB 연결
	m_pDB = new CDBHandle;
	m_pDB->initializeDB(); /* DB 초기화 및 연결 */
}


void CMFCServerPJDlg::OnBnClickedBtnClose()
{
	/* 서버 종료 */
	//서버 종료 -> DB 연결 종료
	//서버 종료
	if (m_pListenSock != NULL) {
		m_pListenSock->Close();
		delete m_pListenSock;
		m_pListenSock = NULL; //재초기화
		cout << "서버가 종료되었습니다.\n";
	}
	//DB 연결 종료
	if (m_pDB != NULL) {
		m_pDB->destroyConnect(); /* DB 연결 종료 */
		delete m_pDB;
		m_pDB = NULL; //재초기화
	}
}


void CMFCServerPJDlg::OnDestroy()
{
	OnBnClickedBtnClose();
	CDialogEx::OnDestroy();
}


void CMFCServerPJDlg::ProcessAccept(int nErrorCode)
{
	//listenSock이 CAsyncSocket상속이라 비동기로 돌아가고
	//accept될 때마다 동적으로 CSocket의 객체가 만들어지는 듯

	/* 클라이언트 연결 수락-> 구분 (AI -> 따로 저장(가장 처음 연결되는 클라이언트
	 * 공정 클라이언트는 리스트(배열)에 저장)
	 */
	ASSERT(nErrorCode == 0);

	if (m_pAIClient == NULL) { //첫번째 클라이언트이면
		CSocket* pClient = new CSocket;
		if (!m_pListenSock->Accept(*pClient)) {
			delete pClient;
			cout << "AI 클라이언트 연결 수락 실패 \n";
			return;
		}
		m_pAIClient = pClient; //소켓 포인터 저장
		cout << "AI 접속 완료 \n";
	}
	else { //일반 공정 클라이언트 처리
		CDataSocket* pFactoryCLT = new CDataSocket(this); //각 클라이언트에 대해 비동기 처리
		if (!m_pListenSock->Accept(*pFactoryCLT)) {
			delete pFactoryCLT;
			cout << "클라이언트 연결 수락 실패 \n";
			return;
		}
		m_arrCLTList.Add(pFactoryCLT); //리스트(배열)에 저장
		cout << m_arrCLTList.GetCount() << "번 클라이언트가 접속하였습니다. \n";
	}
}


void CMFCServerPJDlg::ProcessClose(int nErrorCode)
{
	if (m_pAIClient != NULL) {
		m_pAIClient->Close();
		delete m_pAIClient;
		m_pAIClient = NULL;
	}
	if (m_arrCLTList.GetCount() != 0) {
		for (int i = 0; i < m_arrCLTList.GetCount(); i++) {
			m_arrCLTList[i]->Close();
			delete m_arrCLTList[i];
			m_arrCLTList[i] = NULL;
		}
	}
}


void CMFCServerPJDlg::ProcessReceive(CDataSocket* pSocket, int nErrorCode)
{
	/* 공정 클라이언테 요청 데이터 처리 */
	int len = pSocket->RecvData(); //검사 이미지 수신
	if (len < 0) return;
	cout << "수신 길이: " << len << endl;

	//저장된 파일 읽기
	TCHAR* buffer = new TCHAR[len];
	CFile rFile;
	rFile.Open(_T("..//save.bmp"), CFile::modeRead);
	rFile.Read(buffer, len);
	rFile.Close();

	//AI 모델에 이미지 송신
	m_pAIClient->Send(&len, 4, 0); //파일 크기 보내기
	m_pAIClient->Send(buffer, len, 0); //파일 데이터 보내기

	//화면에 이미지 출력
	CRect rect; //컨트롤 크기 저장할 rect
	m_ctrl_recv.GetWindowRect(rect); //컨트롤 크기 가져오기
	CDC* dc; //픽쳐 컨트롤의 dc 포인터 --UI 접근
	dc = m_ctrl_recv.GetDC();

	CImage image;
	image.Load(_T("..//save.bmp")); //이미지 가져오기
	image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY); //화면에 출력
	ReleaseDC(dc);
	//AI 모델 결과 수신
	int nRet;
	m_pAIClient->Receive(&nRet, 4, 0);
	cout << "AI 검사 결과 :" << nRet << endl;
	//공정에 결과 송신
	TCHAR* result = new TCHAR[4];
	_itow(nRet, result, 10);
	//pSocket->Send(result, 4, 0); //0또는 1
	//검사 결과 송신 후 이미지 분석
	//불량 상태 검사 값
	bool bGreen = false; //Green Head 존재여부
	bool bSize = false; //규격 일치 여부
	bool bPole = false; //극 존재 여부
	//검사 이미지 출력
	CRect rect1; //컨트롤 크기 저장할 rect
	m_ctrl_result.GetWindowRect(rect1); //컨트롤 크기 가져오기
	CDC* dc1; //픽처 컨트롤의 dc 포인터
	dc1 = m_ctrl_result.GetDC();

	image.StretchBlt(dc1->m_hDC, 0, 0, rect1.Width(), rect1.Height(), SRCCOPY); //화면에 출력

	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(0xff, 0xff, 0)); //펜 노란색으로
	CPen* pOldPen = dc1->SelectObject(&pen); //새펜으로 선택하고 기존 펜 반환
	CBrush* pOldBrush = (CBrush*)dc1->SelectStockObject(NULL_BRUSH); //색채우기 끄기
	//검사 이미지 분석 준비
	int nWidth = image.GetWidth();
	int nHeight = image.GetHeight();
	unsigned char* fm = (unsigned char*)image.GetBits();

	//화면상 상대 위치값을 구하기 위한 비율값
	double nRateX = (double)rect1.Width() / nWidth;
	double nRateY = (double)rect1.Height() / nHeight;

	CImage grayImg; //그레이 레벨로 변환한 이미지 저장할 객체
	grayImg.Create(nWidth, nHeight, 8);
	static RGBQUAD rgb[256];
	for (int i = 0; i < 256; i++) {
		rgb[i].rgbRed = rgb[i].rgbBlue = rgb[i].rgbGreen = i;
	}
	grayImg.SetColorTable(0, 256, rgb);
	unsigned char* fmG = (unsigned char*)grayImg.GetBits();
	int nPitch = grayImg.GetPitch();

	//검사 이미지 분석 시작
	/* 그레이 레벨 변환 및 Green Head 검사 */
	CArray<CPoint> arrGPoint; /* 초록색인 지점(Point) 저장할 배열 */
	for (int j = 0; j < nHeight; j++) {
		for (int i = 0; i < nWidth; i++) {
			unsigned char r, g, b;
			r = fm[j * 3 * nPitch + i * 3 + 2];
			g = fm[j * 3 * nPitch + i * 3 + 1];
			b = fm[j * 3 * nPitch + i * 3]; //bgr 순서
			/* 그레이 레벨로 변환 */
			fmG[j * nPitch + i] = 0.299 * r + 0.587 * g + 0.114 * b;
			/* 색상 검사 - 초록색 머리 존재 */
			if (r == 0 && b == 0 && g > 100 && i > 240 && i < 400 && j < 300) //이미지 중앙 상단부에 초록색 탐지
			{ //==========수치 조절 가능 : i(너비), j(높이)
				arrGPoint.Add(CPoint(i * nRateX, j * nRateY));
			}
		}
	}
	cout <<"초록색 픽셀 수 :"<< arrGPoint.GetCount() << endl; //확인용
	//초록색인 지점 개수 정상 제품 기준 통계화 해서 조건문 수정할 것
	if (arrGPoint.GetCount() > 500) {
		bGreen = true;
		//Green Head 화면에 출력
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

		dc1->Rectangle(nLeftX, nLeftY, nRightX, nRightY);
		dc1->TextOutW(nRightX, nRightY, _T("Green Head"));
	}

	CPen pen2; 
	pen2.CreatePen(PS_SOLID, 2, RGB(0, 0xff, 0));
	dc1->SelectObject(&pen2); //펜 색상 변경
	/* 건전지 찾아내기 테두리 포인트 찾아냄*/
	CArray<CPoint> arrContour;
	//==========검사 범위 수정 가능 : i(너비), j(높이)
	for (int j = 50; j < 480; j++) {
		for (int i = 200; i < 400; i++) {
			if (abs(fmG[j * nPitch + i] - fmG[j * nPitch + i + 1]) > 5) { //명도차이가 10이상이면
				arrContour.Add(CPoint(i * nRateX, j * nRateY));
			}
		}
	}
	/* 좌상단, 우하단 좌표 계산 */
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
	/* 규격 검사 */
	double nBodyRate = (double)(nRightX - nLeftX) / (nRightY - nLeftY);
	cout << "너비/높이 = " << nBodyRate << endl;
	//=========== 너비/높이 비율 통계내서 정상 수치 범위 정하기
	//if(nBodyRate)
	/*너비 출력*/
	dc1->MoveTo(nLeftX, nLeftY + (nRightY - nLeftY) / 2);
	dc1->LineTo(nLeftX + 5, nLeftY + (nRightY - nLeftY) / 2 - 5);
	dc1->MoveTo(nLeftX, nLeftY + (nRightY - nLeftY) / 2);
	dc1->LineTo(nLeftX + 5, nLeftY + (nRightY - nLeftY) / 2 + 5);
	dc1->MoveTo(nLeftX, nLeftY + (nRightY - nLeftY) / 2);
	dc1->LineTo(nRightX, nLeftY + (nRightY - nLeftY) / 2);
	dc1->LineTo(nRightX - 5, nLeftY + (nRightY - nLeftY) / 2 - 5);
	dc1->MoveTo(nRightX, nLeftY + (nRightY - nLeftY) / 2);
	dc1->LineTo(nRightX - 5, nLeftY + (nRightY - nLeftY) / 2 + 5);

	CString strWidth;
	strWidth.Format(_T("Width : %d"), nRightX - nLeftX);
	dc1->TextOutW(nRightX, nLeftY + (nRightY - nLeftY) / 2, strWidth);

	/*높이 출력*/
	dc1->MoveTo(nLeftX + (nRightX - nLeftX) / 2, nLeftY);
	dc1->LineTo(nLeftX + (nRightX - nLeftX) / 2 - 5, nLeftY + 5);
	dc1->MoveTo(nLeftX + (nRightX - nLeftX) / 2, nLeftY);
	dc1->LineTo(nLeftX + (nRightX - nLeftX) / 2 + 5, nLeftY + 5);
	dc1->MoveTo(nLeftX + (nRightX - nLeftX) / 2, nLeftY);
	dc1->LineTo(nLeftX + (nRightX - nLeftX) / 2, nRightY);
	dc1->LineTo(nLeftX + (nRightX - nLeftX) / 2 - 5, nRightY - 5);
	dc1->MoveTo(nLeftX + (nRightX - nLeftX) / 2, nRightY);
	dc1->LineTo(nLeftX + (nRightX - nLeftX) / 2 + 5, nRightY - 5);

	CString strHeight;
	strWidth.Format(_T("Height : %d"), nRightY - nLeftY);
	dc1->TextOutW(nLeftX + (nRightX - nLeftX) / 2, nRightY, strWidth);

	CPen pen3;
	pen3.CreatePen(PS_SOLID, 2, RGB(0xff, 0, 0));
	dc1->SelectObject(&pen3); //펜 색상 변경

	/* 몸통 길이 계산 */
	int nBodyY = nRightY;
	for (int i = 0; i < arrContour.GetCount(); i++) {
		if (arrContour[i].x == nLeftX && arrContour[i].y < nBodyY)
			nBodyY = arrContour[i].y;
	}
	/* 극 존재 여부 검사 */
	//========== 극 존재 범위 수치 조절 가능
	if (nBodyY - nLeftY > 5) {
		bPole = true;
		//극 존재 여부 화면에 출력
		dc1->Ellipse(CRect(nLeftX + (nRightX - nLeftX) / 2 - 10, nLeftY + 10, nLeftX + (nRightX - nLeftX) / 2 + 10, nLeftY));
		dc1->TextOutW(nLeftX + (nRightX - nLeftX) / 2, nLeftY - 20, _T("Pole : true"));
	}
	else {
		dc1->TextOutW(nLeftX + (nRightX - nLeftX) / 2, nLeftY - 20, _T("Pole : false"));
	}
	ReleaseDC(dc1);

	//결과 이미지 저장
	CDC* pDC = m_ctrl_result.GetDC();
	HDC hDC = pDC->m_hDC;
	RECT rc;
	m_ctrl_result.GetClientRect(&rc);
	/* 비트맵 생성 */
	//지정된 디바이스와 호환되는 DC(메모리 디바이스 컨텍스트) 생성
	HDC hMemDC = CreateCompatibleDC(hDC);
	//지정된 디바이스 컨텍스트와 연결된 디바이스와 호환되는 비트맵 생성
	HBITMAP hBitmap = CreateCompatibleBitmap(hDC, rc.right, rc.bottom);
	HBITMAP hBmpOld = (HBITMAP)SelectObject(hMemDC, hBitmap);
	//지정된 원본 디바이스 컨텍스트에서 대상 디바이스 컨텍스트로 픽셀 사각형에 해당하는 색 데이터의 비트 블록 전송
	//(대상 디바이스 컨텍스트 핸들, 대상의 왼쪽 위 모서리 x, 대상의 왼쪽 위 모서리y, 
	// 원본 및 대상 사각형의 너비, 원본 및 대상 사각형의 높이, 원본 디바이스 컨텍스트 핸들,
	// 원본 사각형 왼쪽 위 x, 원본 사각형 왼쪽 위 y, 작업 코드)
	BitBlt(hMemDC, 0, 0, rc.right, rc.bottom, hDC, 0, 0, SRCCOPY);
	SelectObject(hMemDC, hBmpOld);
	DeleteDC(hMemDC);

	/* 비트맵 사양 설정 */
	BITMAPINFOHEADER bmih;
	ZeroMemory(&bmih, sizeof(BITMAPINFOHEADER));
	bmih.biSize = sizeof(BITMAPINFOHEADER);
	bmih.biWidth = rc.right;
	bmih.biHeight = rc.bottom;
	bmih.biPlanes = 1;
	bmih.biBitCount = 24;
	bmih.biCompression = BI_RGB;

	/* 비트맵(DIB) 데이터 추출 */
	GetDIBits(hDC, hBitmap, 0, rc.bottom, NULL, (LPBITMAPINFO)&bmih, DIB_RGB_COLORS);
	cout <<"저장될 이미지 크기: "<< bmih.biSizeImage<<endl;
	LPBYTE lpBits = new BYTE[bmih.biSizeImage];
	GetDIBits(hDC, hBitmap, 0, rc.bottom, lpBits, (LPBITMAPINFO)&bmih, DIB_RGB_COLORS);
	ReleaseDC(pDC);
	DeleteObject(hBitmap);

	/* 비트맵 파일 헤더 설정 */
	BITMAPFILEHEADER bmfh;
	bmfh.bfType = 'MB';
	bmfh.bfSize = sizeof(BITMAPFILEHEADER)
		+ sizeof(BITMAPINFOHEADER) + bmih.biSizeImage;
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	/* 파일명설정 */
	CString Name = _T("..//result.bmp");
	_bstr_t gg(Name);
	BSTR lpszFileName = gg.copy();

	/* 비트맵 파일 생성 및 데이터 저장 */
	DWORD dwWritten;
	HANDLE hFile = CreateFile(lpszFileName, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(hFile, &bmfh, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	WriteFile(hFile, &bmih, sizeof(BITMAPINFOHEADER), &dwWritten, NULL);
	WriteFile(hFile, lpBits, bmih.biSizeImage, &dwWritten, NULL);

	CloseHandle(hFile);
	delete[] lpBits;
	/*참고 사이트: https://l71026.tistory.com/108 
				 https://rvs86.tistory.com/134 */



	//std::locale::global(std::locale("kor")); //유니코드 문자 콘솔에 출력되게 해줌
	/* 처음 받는 데이터는 이미지 파일 -> 저장하자 
	 * 그러고 검사 로직 실행하고
	 * 검사 결과 보내주기
	 * 검사 결과 DB 저장
	 */
	//파일 저장
	 //CFile saveFile; // 객체 만들고
	 //saveFile.Open(_T("..//save.png"), CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
	 //saveFile.Write(buffer, len); //파일 저장 잘되는것 까지 확인 완료
	 //saveFile.Close(); //여기서도 확인
	//받은 메시지 확인
	//CString strMSG(buffer);
	//wcout << (LPCSTR)(LPCTSTR)strMSG<<" " << strMSG.GetLength() << endl; //받은 메시지 확인하고 싶으면
	//메시지 보낼때
	/*CString temp = _T("PASS");
	TCHAR* msg = (LPTSTR)(LPCTSTR)temp;
	wcout << msg << endl;
	pSocket->Send(msg, temp.GetLength() * sizeof(TCHAR), 0); */
	//파일 송신
	CFile readFile;
	readFile.Open(_T("..//result.bmp"), CFile::modeRead);
	int nSize = readFile.GetLength();
	cout <<"보낸 파일 크기: " << nSize << endl;
	TCHAR* data = new TCHAR[4];
	_itow(nSize,data,10);
	pSocket->Send(data,4,0);
	
	data = new TCHAR[nSize];
	readFile.Read(data, nSize);
	pSocket->Send(data, nSize, 0);
	
	readFile.Close();
	delete[] buffer;
	
	//delete data;
}
