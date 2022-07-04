
// IOSWGUIDlg.h : header file
//

#pragma once

#include "IOSWTitle.h"
#include "IOSWSystemStatus.h"
#include "IOSWToolbar.h"
#include "ImageObject.h"
#include "ListCtrlEx.h"
#include "IOSWInterface.h"
#include "IOSWDataManager.h"
#include "IOInformationManager.h"
#include "IOSWLogManager.h"

// CIOSWGUIDlg dialog
class CIOSWGUIDlg : public CDialogEx
{
// Construction
public:
	CIOSWGUIDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IOSWGUI_DIALOG };
//#endif
	void SetIOSWMode(IOSW_MODE eMode);
	IOSW_MODE GetIOSWMode();
	CIOSWDataManager* GetIOSWDataManager() { return m_pDataManager; }
	void StopIOMonitoring();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	LRESULT OnUpdateCockpitList(WPARAM wParam, LPARAM lParam);
	LRESULT OnUpdateCockpitIOList(WPARAM wParam, LPARAM lParam);
	LRESULT OnSelectSetting(WPARAM wParam, LPARAM lParam);
	LRESULT OnUpdateLogEvent(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

protected:
//	DWORD ThreadProc();

private:
	// Load Configuration File
	bool	LoadConfiguration();

	// Load IO Information File
	bool	LoadIOInformation();

	void	UpdateLRUInformation(DEVICE_POSITION eType, IO_KIND eIOType);
	void	UpdateLRUIOMonitoring();
	void	UpdateLRUInformationHeader(IO_KIND eIOType);

	bool	LoadLogFile();


private:
	CBitmap				m_bmpBackgound;
	CIOSWTitle*			m_pTitleBar;
	CIOSWSystemStatus*	m_pSystemStatus;
	CIOSWToolbar*		m_pToolBar;
	CImageObject*		m_pLogImage;
	CImageObject*		m_pKAIImage;

	CListCtrlEx			m_listCtrlIO;
	CListCtrlEx			m_listCtrlLog;
//	CListCtrl			m_listCtrlIO;
//	CListCtrl			m_listCtrlLog;

	DEVICE_POSITION		m_eCockpitType;
	IO_KIND				m_eCockpitIOType;

	CFont				m_fontListHeader;
	CFont				m_fontListBody;

	CIOSWInterface*		m_pIOSWInterface;
	CIOSWDataManager*	m_pDataManager;
	CIODeviceInformationManager* m_pIODeviceInfoManager;
	CIOSWLogManager*	m_pLogManager;
	IOSW_MODE			m_eIOSWMode;
public:
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClickIOList(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
//	virtual void PostNcDestroy();
	virtual void OnCancel();
	virtual void OnOK();
};
