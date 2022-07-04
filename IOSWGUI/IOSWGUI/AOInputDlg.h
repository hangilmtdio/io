#pragma once

#include "IOSWDataManager.h"
// CAOInputDlg dialog

class CAOInputDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAOInputDlg)

public:
	CAOInputDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAOInputDlg();

	void SetIOSWDataManager(CIOSWDataManager* pMgr) { m_pDataMgr = pMgr; }
	void SetIOInformation(sIOInformation* pInfo);
	void SetBoardID(int nID) { m_nBoardID = nID; }
	void SetDeviceID(int nID) { m_nDeviceID = nID; }

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_AOINPUT };
#endif
	CPoint				m_ptPosition;

private:
	CBitmap				m_bmpBackgound;
	HBRUSH				m_hEditBrush;
	CIOSWDataManager*	m_pDataMgr;
	sIOInformation*		m_pIOInfo;
	int					m_nBoardID;
	int					m_nDeviceID;
	int					m_nAOValue;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	virtual void OnOK();
	virtual void OnCancel();
};
