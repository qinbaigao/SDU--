
// chuankouDlg.h: 头文件
//

#pragma once
#include "mscomm1.h"
#include "afxwin.h"

// CchuankouDlg 对话框
class CchuankouDlg : public CDialogEx
{
// 构造
public:
	CchuankouDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHUANKOU_DIALOG };
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
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cmbCom;
	CComboBox m_cmbBaud;
	CMscomm1 m_comm;
	CEdit m_edtData;
	afx_msg void OnBnClickedButton1();
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm1();
	CEdit m_edtSend;
	afx_msg void OnBnClickedBtnSendData();
	void OnEnErrspaceEdtData();
};
