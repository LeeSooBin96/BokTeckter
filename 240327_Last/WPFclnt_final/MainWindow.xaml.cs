/* 1. TCP/IP C# 클라이언트
   2. 아두이노 연결
   3. 실시간 웹캠 송출 및 캡쳐 */ 

// OpenCV 사용을 위한 using
using OpenCvSharp;
using System;
using System.Drawing;
using System.IO;
using System.IO.Ports; // 시리얼 통신을 사용하기 위한 선언 ^ 아두이노
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Web.UI.WebControls;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;

// Timer 사용을 위한 using
using System.Windows.Threading;

namespace WPF
{

    // OpenCvSharp 설치 시 Window를 명시적으로 사용해 주어야 함 (window -> System.Windows.Window)
    public partial class MainWindow : System.Windows.Window
    {

        // 필요한 변수 선언
        VideoCapture cam;
        Mat frame;
        DispatcherTimer timer;
        bool is_initCam, is_initTimer;

        SerialPort port = new SerialPort("COM3", 9600); // 아두이노 연결, 포트지정, 통신 속도 지정

        public MainWindow()
        {
            InitializeComponent();
        }

        private void windows_loaded(object sender, RoutedEventArgs e)
        {
            // 카메라, 타이머(0.01ms 간격) 초기화
            is_initCam = init_camera();
            is_initTimer = init_Timer(0.01);

            // 초기화 완료면 타이머 실행
            if (is_initTimer && is_initCam) timer.Start();

        }

        private bool init_Timer(double interval_ms)
        {
            try
            {
                timer = new DispatcherTimer();

                timer.Interval = TimeSpan.FromMilliseconds(interval_ms);
                timer.Tick += new EventHandler(timer_tick);

                return true;
            }
            catch
            {
                return false;
            }
        }

        private bool init_camera()
        {
            try
            {
                // 0번 카메라로 VideoCapture 생성 (카메라가 없으면 안됨)
                cam = new VideoCapture(0);
                cam.FrameHeight = (int)Before_frame.Height;
                cam.FrameWidth = (int)Before_frame.Width;

                // 카메라 영상을 담을 Mat 변수 생성
                frame = new Mat();

                return true;
            }
            catch
            {
                return false;
            }
        }



        private void timer_tick(object sender, EventArgs e)
        {
            // 0번 장비로 생성된 VideoCapture 객체에서 frame을 읽어옴
            cam.Read(frame);
            //Bitmap Result_Image = new Bitmap(Path + "/");
            //Mat rImage = Cv2.ImRead("..//After.png", ImreadModes.Unchanged); // 이미지파일 Mat으로 변환
            
            // 읽어온 Mat 데이터를 Bitmap 데이터로 변경 후 컨트롤에 그려줌
            Before_frame.Source = OpenCvSharp.WpfExtensions.WriteableBitmapConverter.ToWriteableBitmap(frame);
            //After_frame.Source = OpenCvSharp.WpfExtensions.WriteableBitmapConverter.ToWriteableBitmap(rImage);
        }


        // [*] 소켓오픈 
        Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.IP);

        
        // 1. 검사 요청 버튼
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            // [*] 영상을 사진으로 저장. 
            var test_image = frame;

            // [1] 검사 이미지 사전작업 
            Cv2.ImWrite("..//Before.png", test_image); // 프레임 스크린샷 저장경로+파일명

            FileInfo file = new FileInfo("..//Before.png"); // 검사 이미지 파일선언
            
            
            //[2] 파일오픈
            using (FileStream stream = new FileStream(file.FullName, FileMode.Open, FileAccess.Read))
            {
                // [*] 파일 binary를 연다.
                byte[] data = new byte[file.Length];
                    stream.Read(data, 0, data.Length);

                // [3] 파일 서버로 접속. 필요시 주소, 포트번호 변경요망
                socket.Connect(IPAddress.Parse("10.10.20.98"), 26001);

                // [*] 함수 정의, C++와 규약 한대로 보내는 데이터 식
                Action<byte[]> Send = (b) =>
                {
                    // 먼저 데이터 사이즈를 보냄
                    socket.Send(BitConverter.GetBytes(b.Length), 4, SocketFlags.None);
                    // 데이터를 보낸다.
                    socket.Send(b, b.Length, SocketFlags.None);
                };
                
                // [4] 서버로 데이터를 보낸다.
                Send(data);
                

                // [5] 결과수신
                byte[] buffer = new byte[4];
                socket.Receive(buffer, 4, SocketFlags.None);
                int result = BitConverter.ToInt32(buffer, 0);

                var bc = new BrushConverter(); // ui 검출결과 출력

                // [*] 아두이노 ^ 아스키 코드 값으로 인식
                if (result == 49) // OK
                {
                    port.Open();
                    port.Write("1");
                    port.Close();

                    // [*] 라벨출력 OK
                    this.Result_Lbl.Content = "OK";
                    this.Result_Lbl.FontSize = 60;
                    this.Result_Lbl.HorizontalContentAlignment = HorizontalAlignment.Center; // 텍스트 중앙으로
                    this.Result_Lbl.VerticalContentAlignment = VerticalAlignment.Center;
                    this.Result_Lbl.Background = (System.Windows.Media.Brush)bc.ConvertFrom("#1500ff");

                }
                else if (result == 48) // NG
                {
                    port.Open();
                    port.Write("0");
                    port.Close();

                    // [*] 라벨출력 NG
                    this.Result_Lbl.Content = "NG";
                    this.Result_Lbl.FontSize = 60;
                    this.Result_Lbl.HorizontalContentAlignment = HorizontalAlignment.Center; // 텍스트 중앙으로
                    this.Result_Lbl.VerticalContentAlignment = VerticalAlignment.Center;
                    this.Result_Lbl.Background = (System.Windows.Media.Brush)bc.ConvertFrom("#ff0000");
                }

                //[6] 받은 데이터 이미지 생성 및 저장
                socket.Receive(buffer, 4, SocketFlags.None);
                int fileSize = BitConverter.ToInt32(buffer, 0); // int 형변환
                byte[] content = new byte[fileSize]; // 이미지 사이즈만큼 확보
                socket.Receive(content, fileSize, SocketFlags.None); // 데이터 받기
                FileStream wFile = new FileStream("..//After.png", FileMode.Create); // 이미지 생성 
                wFile.Write(content, 0, fileSize);
                //wFile.Close(); // 닫아요
                //socket.Close(); // 닫아요

                /*파일 수신 시*/
                // [7] 받아서 저장된 이미지를 출력하기.
                Mat Rimg = Cv2.ImRead("..//After.png", ImreadModes.Unchanged); // 이미지 Mat 으로 변환
                After_frame.Source = OpenCvSharp.WpfExtensions.WriteableBitmapConverter.ToWriteableBitmap(Rimg); // Mat -> bitmap ^ image 출력

                wFile.Close(); // 닫아요
                socket.Close(); // 닫아요

            }
        }

        //2. 버튼 구현
        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            // STOP

            if (socket != null || port != null)
            {
                socket.Close(); // 소켓닫아
                socket.Dispose(); // 소켓지워어어어어어워우어ㅜ어워웡

                port.Close(); // 아두이노 포트 닫고
                port.Dispose(); // 지워요
            }
        }
    }
}