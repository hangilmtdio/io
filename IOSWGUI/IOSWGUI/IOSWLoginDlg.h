#pragma once


// CIOSWLoginDlg dialog

class CIOSWLoginDlg : public CDialog
{
	DECLARE_DYNAMIC(CIOSWLoginDlg)

public:
	CIOSWLoginDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIOSWLoginDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN_DIALOG };
#endif
	int GetIOSWMode() { return m_nIOSWMode;  }
protected:
	BOOL CheckLogin(CString strID, CString strPassword);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CString m_strID;
	CString m_strPassword;
	int m_nIOSWMode;

	CBitmap	m_bmpBackgound;
	HBRUSH m_hEditBrush;
	HBRUSH m_hRadioBrush;
public:
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedOk();
	afx_msg void OnStnClickedStaticOk();
	afx_msg void OnStnClickedStaticCancel();
	afx_msg void OnIOSWModeRadioCtrl(UINT ID);
	
};
