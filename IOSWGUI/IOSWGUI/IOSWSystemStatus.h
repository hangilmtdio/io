#pragma once

#include "IOSWWnd.h"
#include "ImageObject.h"
#include "IOSWThread.h"
#include "IOSWDataManager.h"
#include "IOInformationManager.h"
#include <list>

typedef struct sLRUImageInfo
{
	sLRUImageInfo()
	{
		nDeviceID = 0;
		pObject = new CImageObject();
	}

	~sLRUImageInfo()
	{
		delete pObject;
		pObject = NULL;
	}

	int nDeviceID;
	CImageObject* pObject;

}sLRUImageInfo;

typedef std::list<sLRUImageInfo*>	LRUIMAGE_LIST;
typedef LRUIMAGE_LIST::iterator		LRUIMAGE_LIST_ITR;

class CIOSWSystemStatus : public CIOSWWnd
{
public:
	CIOSWSystemStatus();
	~CIOSWSystemStatus();

	void LoadResource(CIODeviceInformationManager* pMgr);
	void SetDataManager(CIOSWDataManager* pMgr) { m_pDataManager = pMgr;  }
	void EndMonitoring();

protected:
//	DWORD ThreadProc();
	void  UpdateRender();

	// System Resource status
	void UpdateCPUStatus(CDC* pDC, const SYSTEMSTATUSINFO& sInfo);
	void UpdateMemoryStatus(CDC* pDC, const SYSTEMSTATUSINFO& sInfo);
	void UpdateHDDStatus(CDC* pDC, const SYSTEMSTATUSINFO& sInfo);

	// System Interface status
	void UpdateHOSTStatus(CDC* pDC, const NETWORKSTATUS_TYPE& eStatus);
	void UpdateIOSStatus(CDC* pDC, const NETWORKSTATUS_TYPE& eStatus);
	void UpdateIOStatus(CDC* pDC, const NETWORKSTATUS_TYPE& eStatus);

	// LRU status
	void UpdateLRUStatus(CDC* pDC, const IOSW_to_IOSWGUI& sData);

	// Power status
	//void UpdatePWRStatus(CDC* pDC, const IOSW_to_IOSWGUI& sData);

	void ClearAllLRUImageList();

private:
	CImageObject*	m_pBGImage;
	CImageObject*	m_pSetImage;

	CImageObject*	m_pCPUImage;
	CImageObject*	m_pMEMImage;
	CImageObject*	m_pHDDImage;

	CImageObject*	m_pHOSTImage;
	CImageObject*	m_pIOSImage;
	CImageObject*	m_pIOImage;

	//CImageObject*	m_pPWROnImage;
	//CImageObject*	m_pPWROffImage;
	//CImageObject*	m_pThrottleImage;
	LRUIMAGE_LIST*	m_pListLRUImage;

	CFont			m_font;

	CIOSWDataManager*	m_pDataManager;
	CIODeviceInformationManager* m_pDeviceInfoManager;

	float			m_fNormalValue;
	float			m_fErrorValue;
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

