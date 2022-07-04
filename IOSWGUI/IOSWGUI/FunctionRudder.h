#pragma once


#include "ImageObject.h"
#include "CommonDefine.h"

// CFunctionRudder dialog


class CFunctionRudder : public CDialogEx
{
	DECLARE_DYNAMIC(CFunctionRudder)

public:
	CFunctionRudder(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFunctionRudder();

	TRIM_COMMAND GetTrimCommand() { return m_eTrimCommand;  }
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RUDDER_FUNCTION };
#endif

private:
	CBitmap				m_bmpBackgound;
	CImageObject*		m_pInitObject;
	CImageObject*		m_pLeftTrimObject;
	CImageObject*		m_pRightTrimObject;
	TRIM_COMMAND		m_eTrimCommand;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
