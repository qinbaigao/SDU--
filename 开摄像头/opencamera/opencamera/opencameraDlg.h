
// opencameraDlg.h: 头文件
//

#pragma once
#include "SerialPort.h"
using namespace std;
using namespace itas109;
extern CSerialPort m_SerialPort;

// CopencameraDlg 对话框
class CopencameraDlg : public CDialogEx
{
// 构造
public:
	CopencameraDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_showpicture};
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnReceiveStr(WPARAM str, LPARAM commInfo);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedopencamera();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedpause();
	afx_msg void OnBnClickedshowpicture();\
	double result_x;
	double result_y;
	int radius;
	double loop;
	CButton m_OpenCloseCtrl;
	afx_msg void OnBnClickedButtonOpenClose();
	afx_msg void OnBnClickedButtonSend1();
	CComboBox m_PortNr;
	CComboBox m_BaudRate;
	CEdit m_Send;
	CEdit m_ReceiveCtrl;
	afx_msg void OnBnClickedButtonSend2();
	CComboBox m_Distance;
	afx_msg void OnBnClickedButton1();
	CComboBox m_PEOPLE;
	afx_msg void OnBnClickedButtonDelect();
};


