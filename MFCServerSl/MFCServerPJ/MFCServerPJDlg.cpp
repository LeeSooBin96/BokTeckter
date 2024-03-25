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
	TCHAR* buffer = NULL;
	int len = pSocket->RecvData(buffer);
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
	//CFile readFile;
	//readFile.Open(_T("..//save.png"), CFile::modeRead|CFile::typeBinary);
	//int nSize = readFile.GetLength();
	//TCHAR* data = new TCHAR[4];
	//_itow(nSize,data,10);
	//pSocket->Send(data,4,0);
	//
	//data = new TCHAR[nSize];
	//readFile.Read(data, nSize);
	//pSocket->Send(data, nSize, 0);
	//
	//readFile.Close();
	delete buffer;
	//delete data;
}
