
// opencameraDlg.cpp: 实现文件
//
#pragma warning(disable:4996)；
#include "pch.h"
#include "framework.h"
#include "opencamera.h"
#include "opencameraDlg.h"
#include "afxdialogex.h"
#include "CvvImage.h"
#include "cv.h"
#include "highgui.h"
#include<iostream>
#include<opencv2/opencv.hpp>
#include<math.h>
#include<stdio.h>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/imgproc/imgproc_c.h>


#define PI 3.1415926;
#define MODE 1   //0，读图片；1，读摄像头

using namespace cv;
using namespace std;

Mat frame;
CvvImage cameraimg, cimg1, cimg2, cdst;
VideoCapture cap(0); //定义摄像头

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//应用在串口初始化中
int BaudRate[] = { 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 38400, 56000, 57600, 115200 };
int Distance[] = { 10, 20 };
int People[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
int DISTANCE = 10, PEOPLE = 1;
CString txtname;
CSerialPort m_SerialPort;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

//没有定义但是不能删除！！！！！！！！！！！！！！
CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

CopencameraDlg::CopencameraDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OPENCAMERA_DIALOG, pParent)
	, result_x(0)
	, result_y(0)
	, radius(0)
	, loop(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CopencameraDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_result_x, result_x);
	DDX_Text(pDX, IDC_result_y, result_y);
	DDX_Text(pDX, IDC_radius, radius);
	DDX_Text(pDX, IDC_loop, loop);
	DDX_Control(pDX, IDC_BUTTON_OPEN_CLOSE, m_OpenCloseCtrl);
	DDX_Control(pDX, IDC_COMBO_PORT_Nr, m_PortNr);
	DDX_Control(pDX, IDC_COMBO_BAUDEATE, m_BaudRate);
	DDX_Control(pDX, IDC_SendEdit, m_Send);
	DDX_Control(pDX, IDC_ReceiveEdit, m_ReceiveCtrl);
	DDX_Control(pDX, IDC_COMBO_DISTANCE, m_Distance);
	DDX_Control(pDX, IDC_COMBO_PEOPLE, m_PEOPLE);
}

BEGIN_MESSAGE_MAP(CopencameraDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_opencamera, &CopencameraDlg::OnBnClickedopencamera)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_pause, &CopencameraDlg::OnBnClickedpause)
	ON_BN_CLICKED(IDC_showpicture, &CopencameraDlg::OnBnClickedshowpicture)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_CLOSE, &CopencameraDlg::OnBnClickedButtonOpenClose)
	ON_BN_CLICKED(IDC_BUTTON_SEND1, &CopencameraDlg::OnBnClickedButtonSend1)
	ON_MESSAGE(WM_COMM_RXSTR, &CopencameraDlg::OnReceiveStr)
	ON_BN_CLICKED(IDC_BUTTON_SEND2, &CopencameraDlg::OnBnClickedButtonSend2)
	ON_BN_CLICKED(IDC_BUTTON_DELECT, &CopencameraDlg::OnBnClickedButtonDelect)
END_MESSAGE_MAP()


BOOL CopencameraDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//cap.set(CAP_PROP_FRAME_WIDTH, 320);
	//cap.set(CAP_PROP_FRAME_HEIGHT, 240);

	CString temp1, temp2, temp3;
	//添加波特率到下拉列表
	for (int i = 0; i < sizeof(BaudRate) / sizeof(int); i++)
	{
		temp1.Format(_T("%d"), BaudRate[i]);
		m_BaudRate.AddString((LPCTSTR)temp1);
	}
	temp1.Format(_T("%d"), 9600);
	m_BaudRate.SetCurSel(m_BaudRate.FindString(0, temp1));

	for (int i = 0; i < sizeof(Distance) / sizeof(int); i++)
	{
		temp2.Format(_T("%d"), Distance[i]);
		m_Distance.AddString((LPCTSTR)temp2);
	}
	temp2.Format(_T("%d"), 10);
	m_Distance.SetCurSel(m_Distance.FindString(0, temp2));

	for (int i = 0; i < sizeof(People) / sizeof(int); i++)
	{
		temp3.Format(_T("%d"), People[i]);
		m_PEOPLE.AddString((LPCTSTR)temp3);
	}
	temp3.Format(_T("%d"), 2);
	m_PEOPLE.SetCurSel(m_PEOPLE.FindString(0, temp3));

	//获取串口号
	CSerialPortInfo a;
	list<string> m_portsList = CSerialPortInfo::availablePorts();
	list<string>::iterator itor;
	TCHAR m_regKeyValue[255];
	for (itor = m_portsList.begin(); itor != m_portsList.end(); ++itor)
	{
#ifdef UNICODE
		int iLength;
		const char * _char = (*itor).c_str();
		iLength = MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, NULL, 0);
		MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, m_regKeyValue, iLength);
#else
		strcpy_s(m_regKeyValue, 255, (*itor).c_str());
#endif
		m_PortNr.AddString(m_regKeyValue);
	}
	m_PortNr.SetCurSel(0);
	OnBnClickedButtonOpenClose();


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CopencameraDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CopencameraDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CopencameraDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CopencameraDlg::OnBnClickedopencamera()
{
	int i, j;
	CString b;
	i = m_Distance.GetCurSel();
	j = m_PEOPLE.GetCurSel();
	DISTANCE = 10 * (i + 1);
	PEOPLE = j + 1;
	txtname = _T(".txt");
	b.Format(_T("%d"), PEOPLE);
	txtname = b + txtname;
	//result_x = PEOPLE;
	//UpdateData(FALSE);
	SetTimer(1, 1, NULL);
	//CDC *pDC_camera = GetDlgItem(IDC_frame)->GetDC();
	//HDC hdc_camera = pDC_camera->GetSafeHdc();
	//CRect rect_camera;  //矩形类
	//GetDlgItem(IDC_frame)->GetClientRect(&rect_camera);

	//while (cap.isOpened())
	//{
	//	cap >> frame;
	//	//显示摄像头图像
	//	IplImage img = IplImage(frame);
	//	cameraimg.CopyOf(&img);
	//	cameraimg.DrawToHDC(hdc_camera, &rect_camera);
	//	waitKey(30);
	//}
}

//摄像头图像显示
void CopencameraDlg::OnTimer(UINT_PTR nIDEvent)
{
	//为显示摄像头图像做准备
	CDC *pDC_camera = GetDlgItem(IDC_frame)->GetDC();
	HDC hdc_camera = pDC_camera->GetSafeHdc();
	CRect rect_camera;  //矩形类
	GetDlgItem(IDC_frame)->GetClientRect(&rect_camera);
	
	if (cap.isOpened())
	{
		cap >> frame;
		//显示摄像头图像
		IplImage img = IplImage(frame);
		cameraimg.CopyOf(&img);
		cameraimg.DrawToHDC(hdc_camera, &rect_camera);
		//waitKey(30);
		SetTimer(1, 10, NULL);
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CopencameraDlg::OnBnClickedpause()
{
	KillTimer(1);
}

//寻找弹孔函数
void findhole(Mat mat1_gray, Mat mat2_gray, Mat mat1, int sum[], int hole[], int found[])
{
	Mat dst;
	Mat element_hole = getStructuringElement(2, Size(3, 3));
	absdiff(mat1_gray, mat2_gray, dst);
	if (DISTANCE == 10)
	{
		threshold(dst, dst, 40, 255, THRESH_BINARY);
		//adaptiveThreshold(dst, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 7, 0);//自动阈值分割，高斯邻域
		morphologyEx(dst, dst, CV_MOP_OPEN, element_hole); //条件好的时候不用开运算，二值化即可消除大部分干扰
	}	
	if (DISTANCE == 20)
	{
		threshold(dst, dst, 20, 255, THRESH_BINARY);
		//远距离下不要使用开运算，本来弹孔就只有两三个像素的直径。
		//morphologyEx(dst, dst, CV_MOP_OPEN, element_hole); //条件好的时候不用开运算，二值化即可消除大部分干扰
	}
	int i = 0, x = 0, y = 0;
	vector<vector<Point> > v;
	vector<Vec4i> hierarchy;
	findContours(dst, v, hierarchy, RETR_CCOMP, CV_CHAIN_APPROX_NONE);
	if (hierarchy.size() > 0) //找到弹孔了，标志位置一
		found[0] = 1;
	for (i = 0; i < hierarchy.size(); i++)
	{
		Rect rect;
		rect = boundingRect(v.at(i));					//获得包括轮廓的最小矩形
		drawContours(mat1, v, i, Scalar(0, 0, 255), 1, 8, hierarchy); //画轮廓
		rectangle(mat1, rect, Scalar(0, 0, 255));					  //画最小矩形
		x = rect.x + rect.width / 2;
		y = rect.y + rect.height / 2;
	}
	hole[0] = x;
	hole[1] = y;
}
//寻找中心函数
void findcenter(Mat mat1_gray, Mat mat1, int center[])
{
	Mat element_center_OPEN_10 = getStructuringElement(2, Size(9, 9));
	Mat element_center_CLOSE_10 = getStructuringElement(2, Size(11, 11));
	Mat element_center_OPEN_20 = getStructuringElement(2, Size(5, 5));
	Mat element_center_CLOSE_20 = getStructuringElement(2, Size(7, 7));
	if (DISTANCE == 10)
	{
		GaussianBlur(mat1_gray, mat1_gray, Size(9, 9), 2, 2);	 //滤波，若检测出太多虚假圆，增大size规模
		threshold(mat1_gray, mat1_gray, 170, 255, THRESH_BINARY);//二值化
		morphologyEx(mat1_gray, mat1_gray, CV_MOP_OPEN, element_center_OPEN_10);//开运算，去除数字与环线
		//morphologyEx(mat1_gray, mat1_gray, CV_MOP_CLOSE, element_center_CLOSE_10);//闭运算，去除“10”
	}
	if (DISTANCE == 20)
	{
		GaussianBlur(mat1_gray, mat1_gray, Size(3, 3), 2, 2);	 //滤波，若检测出太多虚假圆，增大size规模
		threshold(mat1_gray, mat1_gray, 100, 255, THRESH_BINARY);//二值化
		morphologyEx(mat1_gray, mat1_gray, CV_MOP_OPEN, element_center_OPEN_20);//开运算，去除数字与环线
		//morphologyEx(mat1_gray, mat1_gray, CV_MOP_CLOSE, element_center_CLOSE_20);//闭运算，去除“10”
	}
	vector<Vec3f> circles;
	int center_x = 0, center_y = 0, r = 0, i = 0;
	if(DISTANCE == 10)
		HoughCircles(mat1_gray, circles, HOUGH_GRADIENT, 1, 100, 100, 30, 10, 300);
	if (DISTANCE == 20)
		HoughCircles(mat1_gray, circles, HOUGH_GRADIENT, 1, 50, 80, 15, 5, 200);
	for (i = 0; i < circles.size(); i++)
	{

		Vec3f c;
		c = circles[i];
		circle(mat1, Point(cvRound(c[0]), cvRound(c[1])), 3, Scalar(0, 255, 50), 2);
		circle(mat1, Point(cvRound(c[0]), cvRound(c[1])), cvRound(c[2]), Scalar(0, 255, 50), 3, 8, 0);
		center[0] = cvRound(c[0]);
		center[1] = cvRound(c[1]);
		center[2] = cvRound(c[2]);
	}
}
//计算环数
void findloop(int hole[], int center[], double l[])
{
	//计算真实像素距离
	l[0] = sqrt((hole[0] - center[0])*(hole[0] - center[0]) + (hole[1] - center[1])*(hole[1] - center[1]));
	//计算弹孔到中心点的距离与半径的比例
	l[1] = l[0] / center[2];
	if (l[1] < 1)
		l[2] = 10;
	if (l[1] >= 1 && l[1] < 2)
		l[2] = 9;
	if (l[1] >= 2 && l[1] < 3)
		l[2] = 8;
	if (l[1] >= 3 && l[1] < 4)
		l[2] = 7;
	if (l[1] >= 4 && l[1] < 5)
		l[2] = 6;
}

void CopencameraDlg::OnBnClickedshowpicture()
{
	//为相机、图片显示做准备
	CDC *pDC_camera = GetDlgItem(IDC_frame)->GetDC();
	HDC hdc_camera = pDC_camera->GetSafeHdc();
	CRect rect_camera;  //矩形类
	GetDlgItem(IDC_frame)->GetClientRect(&rect_camera);
	CDC *pDC_pic = GetDlgItem(IDC_showpic)->GetDC();
	HDC hdc_pic = pDC_pic->GetSafeHdc();
	CRect rect_pic;  //矩形类
	GetDlgItem(IDC_showpic)->GetClientRect(&rect_pic);


	//初始化各个变量
	int i = 0, sum_x = 0, sum_y = 0, hole_x = 0, hole_y = 0, frame_num = 0;
	int hole[2] = { 0, 0 }, sum[2] = { 0, 0 }, center[3] = { 0, 0, 0 }, found[2] = { 0, 0 };
	double l[3] = { 0, 0, 0 };//{像素距离，比例，环数}
	Mat mat1, mat2, mat1_gray, mat2_gray, mean, stddev;
	double m, s;
	
	/*FILE *fp;
	char str[100];
	fp = fopen("demo.txt", "rt");
	while (fgets(str, 100, fp) != NULL) {
		int a = strlen(str);
		TRACE("%d\n", a);
	}
	fclose(fp);*/
	/*ifstream infile("demo.txt");
	int num = 0;
	for (i = 0; i < 10; i++)
	{
		infile >> num;
		if (num != NULL)
			TRACE("%d\n", num);
	}*/

	ofstream outfile(txtname, ios::app);
	outfile << '\n' << l[2];
	outfile.close();

	if (MODE == 0)
	{
		mat1 = imread("save_20_1.jpg");
		mat2 = imread("save_20_2.jpg");
		cvtColor(mat1, mat1_gray, CV_BGR2GRAY);
		cvtColor(mat2, mat2_gray, CV_BGR2GRAY);
		//meanStdDev(mat1, mean, stddev);
		//m = mean.at<double>(0, 0);
		//s = stddev.at<double>(0, 0);

		findhole(mat1_gray, mat2_gray, mat1, sum, hole, found);//寻找弹孔
		findcenter(mat1_gray, mat1, center);//寻找中心
		findloop(hole, center, l);//计算环数

		//结果显示
		result_x = hole[0];
		result_y = hole[1];
		loop = l[1];
		radius = l[2];
		UpdateData(FALSE);

		//示意图显示
		IplImage adst = IplImage(mat1);
		cdst.CopyOf(&adst);
		cdst.DrawToHDC(hdc_pic, &rect_pic);
	}
	else
	{
		while (1)
		{
			mat1 = mat2.clone();//将上一帧存放到mat1里
			cap >> mat2;//读取新的一帧存放到mat2里
			//mat2 = mat2(Range(0,100), Range(0, 100));//裁剪图片
			result_x = frame_num;	
			UpdateData(FALSE);
			//if(frame_num<10)
			frame_num = frame_num + 1;
			if (frame_num > 3)//三帧之后开始检测
			{
				cvtColor(mat1, mat1_gray, CV_BGR2GRAY);
				cvtColor(mat2, mat2_gray, CV_BGR2GRAY);
				findhole(mat1_gray, mat2_gray, mat1, sum, hole, found);//寻找弹孔
				//findcenter(mat1_gray, mat1, center);//寻找中心
				//findloop(hole, center, l);//计算环数

				//结果显示
				/*result_x = frame_num;
				result_y = hole[1];
				loop = l[1];
				radius = l[2];
				UpdateData(FALSE);*/
	
				if (found[0] == 1)//找到弹孔了，显示示意图并sleep一段时间，frame_num置0，标志位置0。
				{
					IplImage adst = IplImage(mat1);
					cdst.CopyOf(&adst);
					cdst.DrawToHDC(hdc_pic, &rect_pic);
					//ofstream outfile(txtname, ios::app);
					//outfile << '\n' << l[2];
					//outfile.close();
					//Sleep(500);
					frame_num = 4;
					found[0] = 0;
				}
			}
			waitKey(1);//没有这玩意不行，我也不知道为啥！！！！！！！！！！！！！！！！！吐了
		}
	}
}




void CopencameraDlg::OnBnClickedButtonOpenClose()
{
	// TODO: 在此添加控件通知处理程序代码
	//GetDlgItem(IDC_SendEdit)->SetFocus();
	CString temp;
	m_OpenCloseCtrl.GetWindowText(temp);///获取按钮的文本
	UpdateData(true);
	if (temp == _T("关机"))///表示点击后是"关闭串口"，也就是已经关闭了串口
	{
		m_SerialPort.ClosePort();
		m_OpenCloseCtrl.SetWindowText(_T("开机"));///设置按钮文字为"打开串口"
	}
	///打开串口操作
	else if (m_PortNr.GetCount() > 0)///当前列表的内容个数
	{

		int SelPortNO, SelBaudRate;
		UpdateData(true);
		m_PortNr.GetWindowText(temp);///CString temp
		temp.Delete(0, 3);
		SelPortNO = _tstoi(temp);

		m_BaudRate.GetWindowText(temp);
		SelBaudRate = _tstoi(temp);

		if (m_SerialPort.InitPort(this->GetSafeHwnd(), SelPortNO, SelBaudRate))
		{

			m_SerialPort.StartMonitoring();
			m_OpenCloseCtrl.SetWindowText(_T("关机"));
		}
		else
		{
			AfxMessageBox(_T("串口已被占用！"));
		}
	}
	else
	{
		AfxMessageBox(_T("没有发现串口！"));
	}
}




void CopencameraDlg::OnBnClickedButtonSend1()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_SendEdit)->SetFocus();
	CString temp;
	UpdateData(true);
	m_OpenCloseCtrl.GetWindowText(temp);
	if (temp == "开机")///没有打开串口
	{
		AfxMessageBox(_T("请首先开机"));
		return;
	}

	//m_Send.GetWindowText(temp);
	temp = "5";
	size_t len = _tcsclen(temp) + 1;
	char* m_str = NULL;
	size_t* converted = 0;
	m_str = new char[len];
#ifdef UNICODE
	wcstombs_s(converted, m_str, len, temp.GetBuffer(0), _TRUNCATE);
#else
	m_str = temp.GetBuffer(0);
#endif
	m_SerialPort.WriteToPort(m_str, len);
}





LRESULT CopencameraDlg::OnReceiveStr(WPARAM str, LPARAM commInfo)
{
	struct serialPortInfo
	{
		UINT portNr;//串口号
		DWORD bytesRead;//读取的字节数
	}*pCommInfo;
	pCommInfo = (serialPortInfo*)commInfo;

	CString str1((char*)str);
	//char* m_str = (char*)str;
	//TCHAR* dest = NULL;
	//dest = new TCHAR[sizeof(TCHAR) * pCommInfo->bytesRead];
	//wmemcpy(dest, (TCHAR*)str, sizeof(TCHAR)* pCommInfo->bytesRead+1);

	//获取指定串口的数据
	//if (pCommInfo->portNr == 2)
	//{
	int len = _tcslen(str1.GetBuffer(0));
	if (len == pCommInfo->bytesRead)
	{
		GetDlgItem(IDC_ReceiveEdit)->SetWindowText(_T(""));
		m_ReceiveCtrl.SetSel(-1, -1);
		m_ReceiveCtrl.ReplaceSel(str1);
	}
	else
	{
		AfxMessageBox(_T("数据长度错误"));
	}
	//}
	return TRUE;
}




void CopencameraDlg::OnBnClickedButtonSend2()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_SendEdit)->SetFocus();
	CString temp;
	UpdateData(true);
	m_OpenCloseCtrl.GetWindowText(temp);
	if (temp == "开机")///没有打开串口
	{
		AfxMessageBox(_T("请首先开机"));
		return;
	}

	//m_Send.GetWindowText(temp);
	temp = "2";
	size_t len = _tcsclen(temp) + 1;;
	char* m_str = NULL;
	size_t* converted = 0;
	m_str = new char[len];
#ifdef UNICODE
	wcstombs_s(converted, m_str, len, temp.GetBuffer(0), _TRUNCATE);
#else
	m_str = temp.GetBuffer(0);
#endif
	m_SerialPort.WriteToPort(m_str, len);
}


void CopencameraDlg::OnBnClickedButtonDelect()
{
	ofstream fout;
	fout.open(txtname);
	fout.close();
}
