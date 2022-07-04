
// IOSWDlg.h : header file
//

#pragma once

#include "IOSWEngine.h"
#include "SystemStatusManager.h"
#include "afxwin.h"

#define  WM_TRAYICON_MSG WM_USER + 99 

// CIOSWDlg dialog
class CIOSWDlg : public CDialogEx
{
// Construction
public:
	CIOSWDlg(CWnd* pParent = NULL);	// standard constructor

	void DoSystemOff();
	void DoPowerDistributorOn();
	void DoPowerDistributorOff();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IOSW_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	LRESULT OnTrayIcomMessage(WPARAM wParam, LPARAM lParam);
	void	OnTrayShow();
	void	OnTrayExit();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonIosconnection();

private:
	void TraySetting();
	bool m_bTrayStatus;
	bool m_bDebugMode;
	bool m_bPWROffComplete; 

	CSystemStatusManager	mgr;


	CIOSWEngine*	m_pEngine;
	int				m_nPowerDelayTime;

	virtual BOOL DestroyWindow();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonGuiconnection();
	afx_msg void OnBnClickedButtonHostconnection();
	afx_msg void OnBnClickedButtonIoboardconnection();
	afx_msg void OnBnClickedOk();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	CButton m_btnIOSConnection;
	afx_msg void OnBnClickedButtonIosdisconnection();
	CButton m_btnIOSDisconnection;
	CButton m_btnHOSTConnection;
	CButton m_btnHOSTDisconnection;
	CButton m_btnGUIConnection;
	CButton m_btnGUIDisconnection;
	CButton m_btnIOBoardConnection;
	CButton m_btnIOBoardDisconnection;
	afx_msg void OnBnClickedButtonHostdisconnection();
	afx_msg void OnBnClickedButtonGuidisconnection();
	afx_msg void OnBnClickedButtonIoboarddisconnection();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedButtonPoweroff();
	afx_msg void OnBnClickedButtonPoweron();
	CButton m_btnPowerON;
	CButton m_btnPowerOFF;
	afx_msg void OnClose();
};
