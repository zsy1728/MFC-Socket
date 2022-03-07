#pragma once

// CMysocket ÃüÁîÄ¿±ê

class CMysocket : public CAsyncSocket
{
public:
	CMysocket();
	virtual ~CMysocket();
	void SetParent(CDialog *pWnd);
	CDialog* m_pWnd;
	virtual void OnReceive(int nErrorCode);
};



