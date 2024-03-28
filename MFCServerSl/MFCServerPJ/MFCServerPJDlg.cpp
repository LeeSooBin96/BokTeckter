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
		SetDlgItemText(IDC_AI_RESULT, _T("Conncet"));
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

	sendIMGToAI(len); //AI에 검사 이미지 송신

	showRecvIMG();//화면에 이미지 출력
	
	//AI 모델 결과 수신
	int nRet;
	m_pAIClient->Receive(&nRet, 4, 0);
	cout << "AI 검사 결과 :" << nRet << endl;
	CString strProduct;
	bool* ckPoint = NULL; //이미지 분석 결과 저장할 포인터(규격,극,프린팅)
	std::string query = "INSERT INTO TB_DATA(DDATE,DBRAND,DRESULT,DSIZE,DPOLE,DPRINT) VALUES(NOW(),'";
	switch (nRet)
	{
	case 1:
		strProduct = _T("Bexel_A");
		query.append("Bexel_A");
		ckPoint = checkProduct(1);
		break;
	case 2:
		strProduct = _T("Bexel_B");
		query.append("Bexel_B");
		ckPoint = checkProduct(2);
		break;
	case 3:
		strProduct = _T("Duracell");
		query.append("Duracell");
		ckPoint = checkProduct(3);
		break;
	case 4:
		strProduct = _T("Energizer");
		query.append("Energizer");
		ckPoint = checkProduct(4);
		break;
	case 5:
		strProduct = _T("Rocket");
		query.append("Rocket");
		ckPoint = checkProduct(5);
		break;
	default:
		break;
	}
	SetDlgItemText(IDC_AI_RESULT, strProduct);

	/* 브랜드명 화면에 출력 */
	CDC* pDC;
	pDC = m_ctrl_result.GetDC();
	pDC->TextOutW(5, 5, strProduct);
	ReleaseDC(pDC);

	/* 불량 여부 판단 */
	int nResult = 1;
	for (int i = 0; i < 3; i++) {
		if (!ckPoint[i]) { //불량이 하나라도 있으면
			nResult = 0; break;
		}
	}
	//공정에 결과 송신
	TCHAR* result = new TCHAR[4];
	_itow(nResult, result, 10); //C#한테 아스키값으로 가짐...
	pSocket->Send(result, 4, 0); //0또는 1
	
	saveResultIMG();//결과 이미지 저장

	//파일 송신
	CFile readFile;
	readFile.Open(_T("..//result.bmp"), CFile::modeRead);
	int nSize = readFile.GetLength();
	cout <<"보낸 파일 크기: " << nSize << endl;
	TCHAR* data = new TCHAR[4];
	_itow(nSize,data,10); //C#한테 아스키값으로 가지는듯?
	pSocket->Send(data,4,0);
	
	data = new TCHAR[nSize];
	readFile.Read(data, nSize);
	pSocket->Send(data, nSize, 0);
	
	readFile.Close();

	//결과 DB에 저장 --DB다시 구성해야함
	if (nResult == 1) query.append("','PASS',");
	else query.append("','NG',");

	for (int i = 0; i < 3; i++) {
		if (ckPoint[i]) query.append("'O'");
		else query.append("'X'");

		if (i != 2) query.append(",");
		else query.append(");");
	}
	cout << query.c_str() << endl;
	m_pDB->excuteQuery(query.c_str());
	
	delete ckPoint;
}

void CMFCServerPJDlg::sendIMGToAI(int len)
{
	//저장된 파일 읽기
	TCHAR* buffer = new TCHAR[len];
	CFile rFile;
	rFile.Open(_T("..//save.bmp"), CFile::modeRead);
	rFile.Read(buffer, len);
	rFile.Close();

	//AI 모델에 이미지 송신
	m_pAIClient->Send(&len, 4, 0); //파일 크기 보내기
	m_pAIClient->Send(buffer, len, 0); //파일 데이터 보내기
	delete[] buffer;
}

void CMFCServerPJDlg::showRecvIMG()
{
	CRect rect; //컨트롤 크기 저장할 rect
	m_ctrl_recv.GetWindowRect(rect); //컨트롤 크기 가져오기
	CDC* dc; //픽쳐 컨트롤의 dc 포인터 --UI 접근
	dc = m_ctrl_recv.GetDC();

	CImage image;
	image.Load(_T("..//save.bmp")); //이미지 가져오기
	image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY); //화면에 출력
	ReleaseDC(dc);
}

bool* CMFCServerPJDlg::checkProduct(int nPNum)
{
	/* 이미지 로드 */
	CImage image;
	image.Load(_T("..//save.bmp")); //이미지 가져오기
	/* 불량 여부 상태값 */
	bool bSize = false; //규격 검사값
	bool bPole = false; //극 존재 유무 검사값
	bool bPrint = false; //프린팅 검사값
	/* 픽처 컨트롤을 다루기 위한 준비 */
	CRect rect1; //컨트롤 크기 저장할 rect
	m_ctrl_result.GetWindowRect(rect1); //컨트롤 크기 가져오기
	CDC* dc1; //픽처 컨트롤의 dc 포인터
	dc1 = m_ctrl_result.GetDC(); //dc 가져오기
	/* 화면에 이미지 출력 */
	image.StretchBlt(dc1->m_hDC, 0, 0, rect1.Width(), rect1.Height(), SRCCOPY); //화면에 출력

	/* 이미지 검사에 필요한 변수 */
	int nWidth = image.GetWidth(); //이미지 너비
	int nHeight = image.GetHeight(); //이미지 높이
	unsigned char* fmO = (unsigned char*)image.GetBits(); //원본 이미지 픽셀 포인터

	/* 화면상 상대 위치값을 구하기 위한 비율값 */
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
	/* 여기까지 필요한 변수 준비 완료 */

	/* 이미지 그레이 레벨 변환 및 색상 추출 */
	CArray<CPoint> arrColor; //각 제품별 검사할 색상 포인트 저장할 배열
	//그레이 레벨 변환 및 색상 추출 -- 추출된 지점 배열에 저장됨
	changeIMGtoGray(nPNum, nHeight, nWidth, nPitch, nRateX, nRateY, fmO, fmG, arrColor);
	/* 건전지(객체) 찾아내기 - 명암 변화 이용 */
	CArray<CPoint> arrContour;
	for (int j = 50; j < 460; j++) { //높이 범위
		for (int i = 200; i < 470; i++) { //너비 범위
			if (abs(fmG[j * nPitch + i] - fmG[j * nPitch + i + 1]) > 5)
				arrContour.Add(CPoint(i * nRateX, j * nRateY)); //명도차이로 객체 인식
		}
	}

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

	/* 건전지 몸통의 높이 구하기(너비는 위에서 구한 것과 일치) */
	int nBodyY = nRightY;
	for (int i = 0; i < arrContour.GetCount(); i++) {
		if (((arrContour[i].x >= nLeftX && arrContour[i].x <= nLeftX + 5)
			|| (arrContour[i].x >= nRightX - 5 && arrContour[i].x <= nRightX))
			&& arrContour[i].y < nBodyY)
			nBodyY = arrContour[i].y;
	}

	/* 규격 검사 */
	double nBodyRate = (double)(nRightX - nLeftX)/(nRightY - nBodyY);
	if (nBodyRate > 0.20 && nBodyRate < 0.26) bSize = true;
	/* 극 존재 유무 검사 */
	if (nBodyY - nLeftY > 5) bPole = true;
	/* 프린트 상태 검사 */
	bPrint = examinePrint(nPNum,nRightX - nLeftX,arrContour, arrColor);
	cout << bSize << " " << bPole << " " << bPrint << endl;

	/* 검사 결과 화면에 출력 */
	//사용할 펜 준비
	CPen whitePen;
	whitePen.CreatePen(PS_SOLID, 2, RGB(0xff, 0xff, 0xff)); 
	CPen yelloPen;
	yelloPen.CreatePen(PS_SOLID, 2, RGB(0xff, 0xff, 0));
	CPen greenPen;
	greenPen.CreatePen(PS_SOLID, 2, RGB(0, 0xff, 0));
	CPen redPen;
	redPen.CreatePen(PS_SOLID, 2, RGB(0xff, 0, 0));
	CPen* pOldPen = dc1->SelectObject(&whitePen); //새펜으로 선택하고 기존 펜 반환
	CBrush* pOldBrush = (CBrush*)dc1->SelectStockObject(NULL_BRUSH); //색채우기 끄기

	/* 인식한 건전지 객체 테두리 출력 */
	dc1->Rectangle(nLeftX - 10, nLeftY - 10, nRightX + 10, nRightY + 10);

	dc1->SelectObject(&greenPen); //펜 색상 변경
	/* 건전지 몸체의 너비 출력 */
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
	strWidth.Format(_T("Width : %d"), nRightX - nLeftX); //너비 출력
	dc1->TextOutW(nRightX, nLeftY + (nRightY - nLeftY) / 2, strWidth);

	/* 건전지 몸체의 높이 출력 */
	dc1->MoveTo(nLeftX + (nRightX - nLeftX) / 2, nBodyY);
	dc1->LineTo(nLeftX + (nRightX - nLeftX) / 2 - 5, nBodyY + 5);
	dc1->MoveTo(nLeftX + (nRightX - nLeftX) / 2, nBodyY);
	dc1->LineTo(nLeftX + (nRightX - nLeftX) / 2 + 5, nBodyY + 5);
	dc1->MoveTo(nLeftX + (nRightX - nLeftX) / 2, nBodyY);
	dc1->LineTo(nLeftX + (nRightX - nLeftX) / 2, nRightY);
	dc1->LineTo(nLeftX + (nRightX - nLeftX) / 2 - 5, nRightY - 5);
	dc1->MoveTo(nLeftX + (nRightX - nLeftX) / 2, nRightY);
	dc1->LineTo(nLeftX + (nRightX - nLeftX) / 2 + 5, nRightY - 5);

	CString strHeight;
	strWidth.Format(_T("Height : %d"), nRightY - nBodyY);
	dc1->TextOutW(nLeftX + (nRightX - nLeftX) / 2, nRightY, strWidth);

	dc1->SelectObject(&yelloPen); //펜 색상 변경
	if (bPrint) { //색상 검출 되었을때만
		int nPLeftX = arrColor[0].x;
		int nPLeftY = arrColor[0].y;
		int nPRightX = arrColor[0].x;
		int nPRightY = arrColor[0].y;

		for (int i = 0; i < arrColor.GetCount(); i++) {
			if (arrColor[i].x < nPLeftX) nPLeftX = arrColor[i].x;
			else if (arrColor[i].x > nPRightX) nPRightX = arrColor[i].x;
			if (arrColor[i].y < nPLeftY) nPLeftY = arrColor[i].y;
			else if (arrColor[i].y > nPRightY) nPRightY = arrColor[i].y;
		}
		
		/* 검출 범위 출력 */
		dc1->Rectangle(nPLeftX, nPLeftY, nPRightX, nPRightY);
		switch (nPNum)
		{
		case 1: //Bexel_A
			dc1->TextOutW(nPRightX, nPLeftY, _T("Orange Bottom"));
			break;
		case 2: //Bexel_B
			dc1->TextOutW(nPRightX, nPRightY, _T("Green Head"));
			break;
		case 3: //Duracell
			dc1->TextOutW(nPRightX, nPRightY, _T("Orange Head"));
			break;
		case 4: //Energizer
			dc1->TextOutW(nPRightX, nPRightY, _T("Black Head"));
			break;
		case 5: //Rocket
			dc1->TextOutW(nPRightX, nPLeftY, _T("Blue Bottom"));
			break;
		default:
			break;
		}
	}

	dc1->SelectObject(&redPen); //펜 색상 변경
	if (bPole) { //극 o
		dc1->Ellipse(CRect(nLeftX + (nRightX - nLeftX) / 2 - 10, nLeftY + 10, nLeftX + (nRightX - nLeftX) / 2 + 10, nLeftY));
		dc1->TextOutW(nLeftX + (nRightX - nLeftX) / 2, nLeftY - 20, _T("Pole : true"));
	}
	else { //극 x
		dc1->TextOutW(nLeftX + (nRightX - nLeftX) / 2, nLeftY - 20, _T("Pole : false"));
	}

	dc1->SelectObject(pOldPen); //기존 펜으로 복구
	dc1->SelectObject(pOldBrush); //기존 브러쉬 반환
	ReleaseDC(dc1);

	bool* result = new bool[3];
	result[0] = bSize; result[1] = bPole; result[2] = bPrint;
	return result;
}

void CMFCServerPJDlg::saveResultIMG()
{
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
	cout << "저장될 이미지 크기: " << bmih.biSizeImage << endl;
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
}

void CMFCServerPJDlg::changeIMGtoGray(int nPNum, int nHeight, int nWidth, int nPitch, 
	double nRateX, double nRateY,unsigned char* fmO, unsigned char* fmG, CArray<CPoint>& arrColor)
{
	for (int j = 0; j < nHeight; j++) {
		for (int i = 0; i < nWidth; i++) {
			unsigned char r, g, b;
			r = fmO[j * 3 * nPitch + i * 3 + 2];
			g = fmO[j * 3 * nPitch + i * 3 + 1];
			b = fmO[j * 3 * nPitch + i * 3]; //bgr 순서
			fmG[j * nPitch + i] = 0.299 * r + 0.587 * g + 0.114 * b;
			switch (nPNum)
			{
			case 1: //Bexel_A
				if (j > 300 && j < 450 && i > 200 && i < 470) { 
					if (r > 70 && r < 175 && g < 100 && b < 50)
						arrColor.Add(CPoint(i * nRateX, j * nRateY));
				}
				break;
			case 2: //Bexel_B
				if (j > 70 && j < 180 && i > 200 && i < 470) {
					if (r == 0 && b == 0 && g > 90)
						arrColor.Add(CPoint(i * nRateX, j * nRateY));
				}
				break;
			case 3: //Duracell
				if (j > 70 && j < 220 && i > 200 && i < 470) {
					if (r >= 100 && r < 125 && g>40 && g < 90 && b>10 && b < 100 ||
						r >= 70 && r < 100 && g>10 && g < 50 && b < 10)
						arrColor.Add(CPoint(i * nRateX, j * nRateY));
				}
				break;
			case 4: //Energizer
				if (j > 70 && j < 200 && i > 200 && i < 470) {
					if (r == 0 && g == 0 && b == 0)
						arrColor.Add(CPoint(i * nRateX, j * nRateY));
				}
				break;
			case 5: //Rocket
				if (j > 360 && j < 450 && i > 250 && i < 420) {
					if (r < 100 && g < 100 && b>150)
						arrColor.Add(CPoint(i * nRateX, j * nRateY));
				}
				break; 
			default:
				break;
			}
		}
	}
}

bool CMFCServerPJDlg::examinePrint(int nPNum,int nWidth, CArray<CPoint>& arrContour, CArray<CPoint>& arrColor)
{
	bool check = false;
	int nObjectNum = arrContour.GetCount(); //인식된 오브젝트 수
	int nColorNum = arrColor.GetCount(); //인식된 색상 수

	double ckObject = (double)nWidth / nObjectNum; // 너비/오브젝트 수
	double ckColor = (double)nWidth / nColorNum; // 너비/색상 수
	cout << ckColor << " " << ckObject << endl;
	switch (nPNum)
	{
	case 1: //Bexel_A
		if (ckColor > 0.004 && ckColor < 0.008 && ckObject>0.003 && ckObject < 0.007)
			check = true;
		break;
	case 2: //Bexel_B
		if (ckColor > 0.01 && ckColor < 0.014 && ckObject>0.0035 && ckObject < 0.007)
			check = true;
		break;
	case 3: //Duracell
		if (ckColor > 0.006 && ckColor < 0.0071 &&
			(ckObject>0.0055 && ckObject < 0.007)|| (ckObject > 0.004 && ckObject < 0.006))
			check = true;
		break;
	case 4: //Energizer
		if (ckColor > 0.01 && ckColor < 0.025 && ckObject>0.004 && ckObject < 0.006)
			check = true;
		break;
	case 5: //Rocket
		if (ckColor > 0.014 && ckColor < 0.019 && ckObject>0.0035 && ckObject < 0.006)
			check = true;
		break;
	default:
		break;
	}
	return check;
}