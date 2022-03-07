
// serverDlg.h : 头文件
//
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

// CserverDlg 对话框
class CserverDlg : public CDialogEx
{
// 构造
public:
	CString GetErrorMsg();
	void OnClose();
	void OnReceive();
	void OnAccept();
	CserverDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SERVER_DIALOG };
//	CListBox	m_ctlRecvd;
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
//	afx_msg void OnBnClickedButton3();
private:
	CMysocket m_sConnectSocket;
	CMysocket m_sListenSocket;
public:
	CListBox m_ctlRecvd;
	CString m_strMsg;
	CString client_IP;
	CString m_strFolder;
	UINT client_Port;
	afx_msg void OnBnClickedBsend();
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedSendFile();
	void SendMsg(CString msg);
	void recvFile();
	afx_msg void OnBnClickedServerclose2();
	int m_Port;
	CString m_strPath;
};
