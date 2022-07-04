#pragma once

#include "IOSWDataManager.h"
// CDOInputDlg dialog

class CDOInputDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDOInputDlg)

public:
	CDOInputDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDOInputDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DOINPUT };
#endif
	void SetIOSWDataManager(CIOSWDataManager* pMgr) { m_pDataMgr = pMgr; }
	void SetIOInformation(sIOInformation* pInfo);
	void SetBoardID(int nID) { m_nBoardID = nID; }
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	afx_msg void OnOffRadioCtrl(UINT ID);

private:
	CBitmap				m_bmpBackgound;
	HBRUSH				m_hRadioBrush;
	CIOSWDataManager*	m_pDataMgr;
	sIOInformation*		m_pIOInfo;
	int					m_nBoardID;
	int					m_nOnOFF;
public:

	CPoint				m_ptPosition;

	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
	virtual void OnCancel();
};
