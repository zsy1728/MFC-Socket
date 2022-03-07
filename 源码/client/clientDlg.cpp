
// clientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "client.h"
#include "clientDlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CclientDlg 对话框




CclientDlg::CclientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CclientDlg::IDD, pParent)
	, m_strIPAddress(_T("127.0.0.1"))
	, m_strFolder(_T("d:\\clientFiles\\"))
	, m_Port(8000)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strMess = _T("");
}

void CclientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EMSG, m_strMess);
	DDX_Control(pDX, IDC_LMSG, m_ctrMessage);
	DDX_Text(pDX, IDC_EDIT_IPADDRESS, m_strIPAddress);
	DDX_Text(pDX, IDC_EDIT_FILEFOLDER, m_strFolder);
	DDX_Text(pDX, IDC_EDIT_PORT, m_Port);
}

BEGIN_MESSAGE_MAP(CclientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CLIENTCONNECT, &CclientDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_CLIENTDISCONNECT, &CclientDlg::OnBnClickedDisconnect)
	ON_BN_CLICKED(IDC_CLIENTSEND, &CclientDlg::OnBnClickedClientSend)
	ON_EN_CHANGE(IDC_EMSG, &CclientDlg::OnEnChangeEmsg)
	ON_BN_CLICKED(IDC_CLIENTOPENFOLDER, &CclientDlg::OnBnClickedClientopenfolder)
	ON_LBN_SELCHANGE(IDC_LMSG, &CclientDlg::OnLbnSelchangeLmsg)
	ON_BN_CLICKED(IDC_BUTTON1, &CclientDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CclientDlg 消息处理程序

BOOL CclientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_sConnectSocket.SetParent(this);
	m_sListenSocket.SetParent(this);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CclientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CclientDlg::OnPaint()
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
HCURSOR CclientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


CString CclientDlg::GetErrorMsg()
{
	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,0, GetLastError(), 
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), //默认语言
		(LPTSTR)&lpMsgBuf, 0, NULL );
	//显示
	CString m_strError;
	m_strError.Format("错误代码：%d  \n出错信息：%s",GetLastError(), (LPCTSTR)lpMsgBuf);
	
	//释放内存
	::LocalFree( lpMsgBuf );
    return m_strError;
}

void CclientDlg::OnReceive()
{	
	char *pBuf = new char[1025];
	int iBufSize = 1024;
	int iRcvd;
	CString strRecvd;
	iRcvd = m_sConnectSocket.Receive(pBuf,iBufSize);
	if(iRcvd == SOCKET_ERROR)
	{
		CString m_ErrorMsg;
		m_ErrorMsg = GetErrorMsg();
		MessageBox(m_ErrorMsg);
		return;
	}
	else
	{
		pBuf[iRcvd] = NULL;
		strRecvd = pBuf;
		if (strRecvd == "aFile")
			ReceiveFile();
		else
		{
			strRecvd = "对方说 : " + strRecvd;
			m_ctrMessage.AddString(strRecvd);
		}
		UpdateData(FALSE);
	}
	delete[] pBuf;
}

void CclientDlg::OnBnClickedConnect()
{
	UpdateData(TRUE);
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return ;
	}
	m_sConnectSocket.Create();
	int retm = m_sConnectSocket.Connect(m_strIPAddress, m_Port);
	CString s;
	s.Format("%d", retm);
	//AfxMessageBox(s);
	if (retm == SOCKET_ERROR)
	{
		CString m_ErrorMsg;
		m_ErrorMsg = GetErrorMsg();
		MessageBox(m_ErrorMsg);
		return;
	}
	GetDlgItem(IDC_CLIENTCONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_CLIENTDISCONNECT)->EnableWindow(TRUE);
	
}


void CclientDlg::OnBnClickedDisconnect()
{
	m_sConnectSocket.Close();
	GetDlgItem(IDC_CLIENTCONNECT)->EnableWindow(TRUE);
	GetDlgItem(IDC_CLIENTDISCONNECT)->EnableWindow(FALSE);
}


void CclientDlg::OnBnClickedClientSend()
{
	int iLen;
	int iSent;
	CString m_strMessage;
	UpdateData(TRUE);
	if(m_strMess !="")
	{  
		m_strMessage = m_strMess;
		iLen = m_strMessage.GetLength();
		
		iSent = m_sConnectSocket.Send(LPCTSTR(m_strMessage),iLen);
		if (iSent == SOCKET_ERROR)
		{
		
			CString m_ErrorMsg;
			m_ErrorMsg = GetErrorMsg();
			MessageBox(m_ErrorMsg);
		}
		else
		{
			m_strMessage = "自己说: "+m_strMessage;
			m_ctrMessage.AddString(m_strMessage);
			m_strMess ="";
			UpdateData(FALSE);
		}
	}
}


void CclientDlg::OnEnChangeEmsg()
{
	UpdateData();
}

//通过按钮或收到的信息触发本函数来接收信息
void CclientDlg::ReceiveFile()
{
	AfxSocketInit(NULL);
	CSocket sockClient;
	sockClient.Create();

	CString	szIP;
	GetDlgItemText(IDC_EDIT_IPADDRESS, szIP);

	if (!sockClient.Connect((LPCTSTR)szIP, 8800))
	{
		AfxMessageBox("对方未发送");
		return;
	}

	SOCKET_STREAM_FILE_INFO StreamFileInfo;
	sockClient.Receive(&StreamFileInfo, sizeof(SOCKET_STREAM_FILE_INFO));

	UpdateData(TRUE);
	CString strFolderPath= m_strFolder;
	if (!PathFileExists(strFolderPath))//文件夹是否存在
	{
		CreateDirectory(strFolderPath, NULL);//如果不存在就创建
	}
	CString strFileName;
	strFileName.Format("%s", StreamFileInfo.szFileTitle);
	strFileName = strFolderPath + strFileName;
	CFile destFile(strFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);

	UINT dwRead = 0;
	while (dwRead < StreamFileInfo.nFileSizeLow)
	{
		byte* data = new byte[1024];
		memset(data, 0, 1024);

		UINT dw = sockClient.Receive(data, 1024);
		destFile.Write(data, dw);

		dwRead += dw;
		delete[] data;
	}
	SetFileTime((HANDLE)destFile.m_hFile, &StreamFileInfo.ftCreationTime,
		&StreamFileInfo.ftLastAccessTime, &StreamFileInfo.ftLastWriteTime);
	destFile.Close();
	SetFileAttributes(StreamFileInfo.szFileTitle, StreamFileInfo.dwFileAttributes);
	
	sockClient.Close();
	m_ctrMessage.AddString("接收到了文件"+ strFileName);
	m_strRecieveFile = strFolderPath+strFileName;

	UpdateData(FALSE);
}


void CclientDlg::OnBnClickedClientopenfolder()
{	
	ShellExecute(NULL, "open", m_strFolder, NULL, NULL, SW_SHOWNORMAL);
}


void CclientDlg::OnLbnSelchangeLmsg()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CclientDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog	Dlg(TRUE);
	if (Dlg.DoModal() != IDOK)
		return;

	CFile myFile;
	if (!myFile.Open(Dlg.GetPathName(), CFile::modeRead | CFile::typeBinary))
	{
		AfxMessageBox("文件不存在!");
		return;
	}
	CString strFileName = myFile.GetFileTitle();
	CSocket sockSrvr;
	sockSrvr.Create(9800);

	sockSrvr.Listen();

	m_ctrMessage.AddString("正在发送文件" + strFileName);
	UpdateData(FALSE);

	//提示对方在发送文件


	CString m_strMessage = "aFile";
	m_sConnectSocket.Send(LPCTSTR(m_strMessage), m_strMessage.GetLength());

	CSocket sockRecv;
	sockSrvr.Accept(sockRecv);

	SOCKET_STREAM_FILE_INFO	StreamFileInfo;
	WIN32_FIND_DATA FindFileData;

	FindClose(FindFirstFile(Dlg.GetPathName(), &FindFileData));
	memset(&StreamFileInfo, 0, sizeof(SOCKET_STREAM_FILE_INFO));
	CString strFileTitle = myFile.GetFileTitle();
	strcpy_s(StreamFileInfo.szFileTitle, strFileTitle.GetLength() + 1, strFileTitle);
	//注意一定要加1，因为不包括结束符"\0"

	StreamFileInfo.dwFileAttributes = FindFileData.dwFileAttributes;
	StreamFileInfo.ftCreationTime = FindFileData.ftCreationTime;
	StreamFileInfo.ftLastAccessTime = FindFileData.ftLastAccessTime;
	StreamFileInfo.ftLastWriteTime = FindFileData.ftLastWriteTime;
	StreamFileInfo.nFileSizeHigh = FindFileData.nFileSizeHigh;
	StreamFileInfo.nFileSizeLow = FindFileData.nFileSizeLow;

	sockRecv.Send(&StreamFileInfo, sizeof(SOCKET_STREAM_FILE_INFO), 0);

	UINT dwRead = 0;
	while (dwRead < StreamFileInfo.nFileSizeLow)
	{
		byte* data = new byte[1024];
		UINT dw = myFile.Read(data, 1024);
		sockRecv.Send(data, dw);

		dwRead += dw;
		delete[] data;
	}
	myFile.Close();
	sockRecv.Close();

	m_ctrMessage.AddString(strFileName + "文件发送完成");
	UpdateData(FALSE);

}

