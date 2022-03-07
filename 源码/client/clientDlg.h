
// clientDlg.h : 头文件
#include "Mysocket.h"
#pragma once

typedef struct _SOCKET_STREAM_FILE_INFO {

	TCHAR       szFileTitle[128];                   //文件的标题名
	DWORD       dwFileAttributes;                   //文件的属性
	FILETIME    ftCreationTime;                     //文件的创建时间
	FILETIME    ftLastAccessTime;                   //文件的最后访问时间
	FILETIME    ftLastWriteTime;                    //文件的最后修改时间
	DWORD       nFileSizeHigh;                      //文件大小的高位双字
	DWORD       nFileSizeLow;                       //文件大小的低位双字
	DWORD       dwReserved0;                        //保留，为0
	DWORD       dwReserved1;                        //保留，为0

} SOCKET_STREAM_FILE_INFO, * PSOCKET_STREAM_FILE_INFO;

// CclientDlg 对话框
class CclientDlg : public CDialogEx
{
// 构造
public:
	CString GetErrorMsg();
	//	重写OnReceive()；
	void OnReceive();
	CclientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CLIENT_DIALOG };

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
//	afx_msg void OnLbnSelchangeList1();
private:
	CMysocket m_sConnectSocket;
	CMysocket m_sListenSocket;
public:
	CString m_strMess;
	CListBox m_ctrMessage;
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedDisconnect();
	afx_msg void OnBnClickedClientSend();
	afx_msg void OnEnChangeEmsg();
	afx_msg void ReceiveFile();
	CString m_strIPAddress;
	CString m_strFolder;
	afx_msg void OnBnClickedClientopenfolder();
	CString m_strRecieveFile;
	afx_msg void OnLbnSelchangeLmsg();
	afx_msg void OnBnClickedButton1();
	int m_Port;
};
