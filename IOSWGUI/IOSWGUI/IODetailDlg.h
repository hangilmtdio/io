#pragma once

#include "ListCtrlEx.h"
#include "IOInformationManager.h"
#include "IOSWDataManager.h"
#include "ImageObject.h"

// CIODetailDlg dialog

class CIODetailDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CIODetailDlg)

public:
	CIODetailDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIODetailDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IO_DIALOG };
#endif

public:
	void SetIODeviceInfoManager(CIODeviceInformationManager* pMgr);
	void SetDataManager(CIOSWDataManager* pMgr);
	void SetLRUInfo(const int & nDeviceID, const int & nBoardID);
	void LoadResource();

private:
	CListCtrlEx			m_listCtrlIODetail;
//	CListCtrl			m_listCtrlIODetail;
	CFont				m_fontListHeader;
	CFont				m_fontListBody;
	CBitmap				m_bmpBackgound;

	CImageObject*		m_pBIDImage;
	CImageObject*		m_pLRUImage;
	CImageObject*		m_pFunction;

	bool				m_bFunctionTest;

	CIODeviceInformationManager*	m_pIODeviceInfoMgr;
	CIOSWDataManager*				m_pDataMgr;
	int								m_nDeviceID;
	int								m_nBoardID;
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClickIODetailList(NMHDR *pNMHDR, LRESULT *pResult);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
