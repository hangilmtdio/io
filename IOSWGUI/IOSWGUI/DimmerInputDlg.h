#pragma once
#include "afxcmn.h"

#include "IOSWDataManager.h"

// CDimmerInputDlg dialog

class CDimmerInputDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDimmerInputDlg)

public:
	CDimmerInputDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDimmerInputDlg();
	void SetIOSWDataManager(CIOSWDataManager* pMgr) { m_pDataMgr = pMgr; }
	void SetIOInformation(sIOInformation* pInfo);
	void SetBoardID(int nID) { m_nBoardID = nID; }
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DIMMERINPUT };
#endif
	CPoint				m_ptPosition;
private:
	CBitmap				m_bmpBackgound;
	HBRUSH				m_hEditBrush;
	int m_nDimmerValue;
	int m_nDimmerTrackValue;
	CSliderCtrl			m_ctrlDimmerSlider;
	CIOSWDataManager*	m_pDataMgr;
	sIOInformation*		m_pIOInfo;
	int					m_nBoardID;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual void OnOK();
	virtual void OnCancel();
};
