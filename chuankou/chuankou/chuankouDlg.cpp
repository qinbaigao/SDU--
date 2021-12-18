
// chuankouDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "chuankou.h"
#include "chuankouDlg.h"
#include "afxdialogex.h"
#include "afxdisp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CchuankouDlg 对话框



CchuankouDlg::CchuankouDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHUANKOU_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CchuankouDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_COM, m_cmbCom);
	DDX_Control(pDX, IDC_CMB_BAUD, m_cmbBaud);
	DDX_Control(pDX, IDC_MSCOMM1, m_comm);
	DDX_Control(pDX, IDC_EDT_DATA, m_edtData);
	DDX_Control(pDX, IDC_EDT_SEND, m_edtSend);
}

BEGIN_MESSAGE_MAP(CchuankouDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN, &CchuankouDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BTN_SEND_DATA, &CchuankouDlg::OnBnClickedBtnSendData)
END_MESSAGE_MAP()

char * CstringToChar(CString str)
{
	int n = str.GetLength(); //获取str的字符数    
	int len = WideCharToMultiByte(CP_ACP, 0, str, n, NULL, 0, NULL, NULL); //获取宽字节字符的大小，大小是按字节计算的    
	char *pChar = new char[len + 1]; //以字节为单位    
	WideCharToMultiByte(CP_ACP, 0, str, n, pChar, len, NULL, NULL); //宽字节编码转换成多字节编码    
	pChar[len] = '\0'; //多字节字符以'\0'结束 原文代码有错误哦  

	return pChar;
}
// CchuankouDlg 消息处理程序

BOOL CchuankouDlg::OnInitDialog()
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
	// TODO: 在此添加额外的初始化代码
	m_cmbCom.AddString(L"COM1");
	m_cmbCom.AddString(L"COM2");
	m_cmbCom.AddString(L"COM3");
	m_cmbCom.AddString(L"COM4");
	m_cmbCom.AddString(L"COM5");
	m_cmbCom.AddString(L"COM6");
	m_cmbCom.AddString(L"COM7");
	m_cmbCom.AddString(L"COM8");
	m_cmbCom.AddString(L"COM9");
	m_cmbCom.AddString(L"COM10");
	m_cmbCom.SetCurSel(3);

	m_cmbBaud.AddString(L"600");
	m_cmbBaud.AddString(L"1200");
	m_cmbBaud.AddString(L"2400");
	m_cmbBaud.AddString(L"4800");
	m_cmbBaud.AddString(L"9600");
	m_cmbBaud.AddString(L"38400");
	m_cmbBaud.AddString(L"57600");
	m_cmbBaud.AddString(L"115200");
	//	m_cmbBaud.AddString(L"230400");
	//	m_cmbBaud.AddString(L"460800");
	m_cmbBaud.SetCurSel(7);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CchuankouDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CchuankouDlg::OnPaint()
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

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CchuankouDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CchuankouDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_comm.get_PortOpen())//如果串口未打开
	{

		CString baud;
		GetDlgItemText(IDC_CMB_BAUD, baud);//取得波特率口当前的选择值，存放在baud里
		CString baudPort = baud + _T(",n,8,1");// 设置波特率、无校验，8数据位，1个停止位
		m_comm.put_CommPort(m_cmbCom.GetCurSel());//选择串口，m_cmbCom：串口选择组合框的 成员变量
		m_comm.put_InBufferSize(1024); //   put__InBufferSize(1024); //设置输入缓冲区的大小，Bytes
		m_comm.put_OutBufferSize(1024);   // put__OutBufferSize(512); //设置发送缓冲区的大小，Bytes// 
		m_comm.put_PortOpen(TRUE);//  SetPortOpen(TRUE);
		m_comm.put_InputMode(1);  //  SetInputMode(1); //设置输入方式为二进制方式
		m_comm.put_Settings(baudPort);    //  SetSettings("9600,n,8,1"); //设置波特率等参数
		m_comm.put_RThreshold(1); //SetRThreshold(1); //为1表示有一个字符引发一个事件
		m_comm.put_InputLen(0);// SetInputLen(0); 设置当前接收区数据长度为0,表示全部读取
		SetDlgItemText(IDC_BTN_OPEN, _T("关闭串口"));
	}
	else
	{
		m_comm.put_PortOpen(FALSE);
		SetDlgItemText(IDC_BTN_OPEN, _T("打开串口"));
	}
}
BEGIN_EVENTSINK_MAP(CchuankouDlg, CDialogEx)
	ON_EVENT(CchuankouDlg, IDC_MSCOMM1, 1, CchuankouDlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


void CchuankouDlg::OnCommMscomm1()
{
	// TODO: 在此处添加消息处理程序代码
	CString strData;
	GetDlgItemText(IDC_EDT_DATA, strData);
	if (m_comm.get_CommEvent() == 2)
	{
		char str[1024] = { 0 };
		long k;
		VARIANT InputData = m_comm.get_Input();	//读缓冲区
		COleSafeArray fs;
		fs = InputData;	//VARIANT型变À量转换为COleSafeArray型变量
		for (k = 0; k < (long)fs.GetOneDimSize(); k++)
			fs.GetElement(&k, str + k);	//转换为BYTE型数组

		strData += str;      //	接收到编辑框里面

		SetDlgItemText(IDC_EDT_DATA, strData);
	}
}


void CchuankouDlg::OnBnClickedBtnSendData()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString sendDAta;
	GetDlgItemText(IDC_EDT_SEND, sendDAta);
	if (sendDAta == "")
	{
		MessageBox(_T("发送数据不能为空"), _T("警告"), MB_OK | MB_ICONWARNING);
		return;
	}
	char *data = CstringToChar(sendDAta);

	m_comm.put_Output(COleVariant(sendDAta));
	UpdateData(FALSE);

}

void CchuankouDlg::OnEnErrspaceEdtData()
{
	// TODO: 在此添加控件通知处理程序代码
	int choice = MessageBox(_T("接收数据编辑框可用内存不足！\n是否清楚接收内容？"),
		_T("警告"), MB_OKCANCEL | MB_ICONWARNING);
	if (choice == IDOK)
	{
		SetDlgItemText(IDC_EDT_DATA, L"");
	}
}