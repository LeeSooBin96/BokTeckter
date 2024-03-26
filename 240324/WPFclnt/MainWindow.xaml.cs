/* 1. TCP/IP C# 클라이언트
   2. 아두이노 연결
   3. 실시간 웹캠 송출 및 캡쳐 */ 

// OpenCV 사용을 위한 using
using OpenCvSharp;
using System;
using System.IO;
using System.IO.Ports; // 시리얼 통신을 사용하기 위한 선언 ^ 아두이노
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Web.UI.WebControls;
using System.Windows;
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
                cam.FrameHeight = (int)Cam_1.Height;
                cam.FrameWidth = (int)Cam_1.Width;

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
            // 읽어온 Mat 데이터를 Bitmap 데이터로 변경 후 컨트롤에 그려줌
            Cam_1.Source = OpenCvSharp.WpfExtensions.WriteableBitmapConverter.ToWriteableBitmap(frame);
        }




        //[*] 아두이노
        //private SerialPort mySerial; // 아두이노 연결부분
        // 1. 시리얼포트 생성
        SerialPort port = new SerialPort("COM3", 9600); // 아두이노 연결, 포트지정, 통신 속도 지정

        //2. 버튼 구현
        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            port.Open();
            port.Write("1");
            port.Close();
        }


        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            port.Open();
            port.Write("0");
            port.Close();
        }

        


        /// 아두이노 끝

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            // [*] 영상을 사진으로 캡쳐. 
            Cv2.ImShow("클라?", frame);
            var test_image = frame;
            // frame을 저장해야함.
            Cv2.ImWrite("C:\\test\\TTTTTTTTTTTTTTTTTTTT.jpg", test_image); // 프레임 스크린샷 저장경로+파일명
            // 업로드 할 파일 정보
            FileInfo file = new FileInfo("C:\\test\\TTTTTTTTTTTTTTTTTTTT.jpg"); // 작업할 파일 불러오기.

            //[1] 파일오픈
            using (FileStream stream = new FileStream(file.FullName, FileMode.Open, FileAccess.Read))
            {
                // 파일 binary를 연다.
                byte[] data = new byte[file.Length];
                stream.Read(data, 0, data.Length);

                // [2] 소켓오픈
                using (Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.IP))
                {
                    // [3] 파일 서버로 접속. 주소, 포트번호 변경요망
                    socket.Connect(IPAddress.Parse("127.0.0.1"), 9090);

                    // [4] 람다 함수 정의 C++와 약속한 규약대로 데이터를 송수신한다. 함수의 변수명은 Send
                    Action<byte[]> Send = (b) =>
                    {
                        // 먼저 데이터 사이즈를 보냄
                        socket.Send(BitConverter.GetBytes(b.Length), 4, SocketFlags.None);
                        //MessageBox.Show(b.Length.ToString()); // 데이터전송 확인용
                        // 데이터를 보낸다.
                        socket.Send(b, b.Length, SocketFlags.None);
                    };

                    // 먼저 파일명을 전송한다 
                    // unicode가 아닌 utf8형식으로 전송한다. Send는 변수
                    Send(Encoding.UTF8.GetBytes("Download.jpg\0")); // 서버에 보낸이미지 이름?
                    // 파일 바이너리 데이터를 보낸다. Send는 변수
                    Send(data); // 서버에 보내주는 데이터?
                    // 서버로 부터 byte=1 데이터가 오면 클라를 종료한다.
                    byte[] ret = new byte[1];
                    socket.Receive(ret, 1, SocketFlags.None);
                    if (ret[0] == 1)
                    {
                        Console.WriteLine("Completed");
                    }
                }
            }
        }
    }
}