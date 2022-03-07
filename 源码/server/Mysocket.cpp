// Mysocket.cpp : 实现文件
//

#include "stdafx.h"
#include "server.h"
#include "Mysocket.h"
#include "serverDlg.h"

// CMysocket

CMysocket::CMysocket()
{
}

CMysocket::~CMysocket()
{
}


// CMysocket 成员函数
void CMysocket::SetParent(CDialog *pWnd)
{
   m_pWnd = pWnd;
}

void CMysocket::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
    ((CserverDlg*)m_pWnd)->OnAccept();
	CAsyncSocket::OnAccept(nErrorCode);
}



void CMysocket::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	((CserverDlg*)m_pWnd)->OnClose();
	CAsyncSocket::OnClose(nErrorCode);
}

void CMysocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
    ((CserverDlg*)m_pWnd)->OnReceive();
	CAsyncSocket::OnReceive(nErrorCode);
}
