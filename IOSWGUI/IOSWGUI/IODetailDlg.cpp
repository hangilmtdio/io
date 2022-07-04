// IODetailDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IOSWGUI.h"
#include "IODetailDlg.h"
#include "afxdialogex.h"
#include "IOSWUtilities.h"
#include "DOInputDlg.h"
#include "AOInputDlg.h"
#include "DimmerInputDlg.h"
#include "FunctionRudder.h"
#include "FunctionStick.h"

// CIODetailDlg dialog

IMPLEMENT_DYNAMIC(CIODetailDlg, CDialogEx)

CIODetailDlg::CIODetailDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IO_DIALOG, pParent)
{
	m_pIODeviceInfoMgr	= NULL;
	m_pDataMgr = NULL;
	m_nDeviceID = 0;
	m_nBoardID = 0;
	m_pBIDImage = NULL;
	m_pLRUImage = NULL;
	m_pFunction = NULL;

	m_bFunctionTest = false;
}

CIODetailDlg::~CIODetailDlg()
{
	if (m_pBIDImage != NULL) {
		delete m_pBIDImage;
		m_pBIDImage = NULL;
	}

	if (m_pLRUImage != NULL) {
		delete m_pLRUImage;
		m_pLRUImage = NULL;
	}

	if (m_pFunction != NULL) {
		delete m_pFunction;
		m_pFunction = NULL;
	}
}

void CIODetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CIODetailDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_NOTIFY(NM_DBLCLK, IDC_LISTCTRL_IODETAIL, &CIODetailDlg::OnClickIODetailList)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CIODetailDlg message handlers


BOOL CIODetailDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	m_bmpBackgound.LoadBitmap(IDB_BITMAP_SUB);

	m_fontListHeader.CreateFont(16, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, _T("³ª´®°íµñ"));

	m_fontListBody.CreateFont(15, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, _T("³ª´®°íµñ"));

	BITMAP BmpInfo;
	m_bmpBackgound.GetBitmap(&BmpInfo);

	this->MoveWindow(0 + (1600 - (int)BmpInfo.bmWidth) / 2, 0 + (1200 - (int)BmpInfo.bmHeight) / 2, (int)BmpInfo.bmWidth, (int)BmpInfo.bmHeight);

	m_listCtrlIODetail.Create(WS_VISIBLE | WS_CHILD | LVS_REPORT | LVS_SINGLESEL, CRect(0, 0, 0, 0), this, IDC_LISTCTRL_IODETAIL);
	m_listCtrlIODetail.SetWindowPos(NULL, 5, 80, 570, 453, SWP_FRAMECHANGED);
	m_listCtrlIODetail.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER);

	m_listCtrlIODetail.SetFont(&m_fontListBody);
	m_listCtrlIODetail.SetItemHeight(28);
	m_listCtrlIODetail.SetBkColor(RGB(67, 79, 95));
	m_listCtrlIODetail.SetTextBkColor(RGB(67, 79, 95));
	m_listCtrlIODetail.SetTextColor(RGB(224, 224, 224));
	m_listCtrlIODetail.SetGridColor(RGB(44, 63, 78));
	m_listCtrlIODetail.SetGridLineWidth(1);
	m_listCtrlIODetail.SetGridHMode(TRUE);
	m_listCtrlIODetail.SetSelBkColor(RGB(47, 59, 75));
	m_listCtrlIODetail.SetSelTextColor(RGB(102, 153, 255));

	m_listCtrlIODetail.SetHeaderFont(&m_fontListHeader);
	m_listCtrlIODetail.SetHeaderHeight(31);
	m_listCtrlIODetail.SetHeaderBkColor(RGB(44, 63, 78));
	m_listCtrlIODetail.SetHeaderTextColor(RGB(255, 255, 255));
	m_listCtrlIODetail.SetHeaderLineColor(RGB(44, 63, 78));
	m_listCtrlIODetail.SetHeaderLineWidth(1);
	m_listCtrlIODetail.SetHeaderEnableResizing(FALSE);

	// Insert columns -------------------------------------------------------------------------------------------------------------------------------
	m_listCtrlIODetail.InsertColumn(0, _T(""), LVCFMT_CENTER, 0, -1);
	m_listCtrlIODetail.InsertColumn(1, _T("No"), LVCFMT_CENTER, 40, -1);
	m_listCtrlIODetail.InsertColumn(2, _T("IO Name"), LVCFMT_CENTER, 250, -1);
	m_listCtrlIODetail.InsertColumn(3, _T("Channel"), LVCFMT_CENTER, 80, -1);
	m_listCtrlIODetail.InsertColumn(4, _T("Type"), LVCFMT_CENTER, 80, -1);
	m_listCtrlIODetail.InsertColumn(5, _T("Value"), LVCFMT_RIGHT, 110, -1);
	m_listCtrlIODetail.InsertColumn(6, _T(""), LVCFMT_RIGHT, 10, -1);

	LoadResource();

	if (m_pIODeviceInfoMgr == NULL)
		return FALSE;

	CIODeviceInfo* pInfo = m_pIODeviceInfoMgr->GetDeivceInfo(m_nDeviceID);

	if (pInfo == NULL)
		return FALSE;

	LIST_ID IndexList;
	LIST_ID_ITR IndexItr;

	pInfo->GetIOIndexList(&IndexList);
	int nItemCount = 0;

	for (IndexItr = IndexList.begin(); IndexItr != IndexList.end(); ++IndexItr)
	{
		int nIndex = *IndexItr;

		sIOInformation* pIOInfo = pInfo->GetIOInfo(nIndex);

		if (pIOInfo != NULL)
		{
			CString strTemp;

			strTemp.Format(_T("%d"), pIOInfo->nIndex);
			m_listCtrlIODetail.InsertItem(nItemCount, strTemp);

			strTemp.Format(_T("%d"), nItemCount + 1);
			m_listCtrlIODetail.SetItemText(nItemCount, 1, strTemp);

			strTemp.Format(_T("%S"), pIOInfo->szIOName);
			m_listCtrlIODetail.SetItemText(nItemCount, 2, strTemp);

			strTemp.Format(_T("%d"), pIOInfo->nChannel);
			m_listCtrlIODetail.SetItemText(nItemCount, 3, strTemp);

			switch (pIOInfo->eKind)
			{
			case IK_DI:
			case IK_DO:
				strTemp.Format(_T("%d   "), pIOInfo->szValue);
				break;
			case IK_AI:
			case IK_AO:
			case IK_DIMMER:
				strTemp.Format(_T("%d   "), pIOInfo->usValue);
				break;
			case IK_AO_IDC:
			case IK_AI_SR:
				strTemp.Format(_T("%d   "), (int)pIOInfo->fValue);
				break;
			default:
				break;
			}

			m_listCtrlIODetail.SetItemText(nItemCount, 4, alpszIOType[pIOInfo->eKind]);
			m_listCtrlIODetail.SetItemText(nItemCount, 5, strTemp);
		}
		nItemCount++;
		Sleep(1);
	}

	SetTimer(100, 200, NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CIODetailDlg::LoadResource()
{
	m_pBIDImage = new CImageObject();

	if (m_pBIDImage) {
		m_pBIDImage->SetXPosition(15);
		m_pBIDImage->SetYPosition(10);
		m_pBIDImage->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("IODetail_BID.bmp")));
	}

	m_pLRUImage = new CImageObject();

	if (m_pLRUImage) {
		m_pLRUImage->SetXPosition(15);
		m_pLRUImage->SetYPosition(45);
		m_pLRUImage->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("IODetail_LRUNAME.bmp")));
	}

	if (m_bFunctionTest)
	{
		m_pFunction = new CImageObject();

		if (m_pFunction) {
			m_pFunction->SetXPosition(450);
			m_pFunction->SetYPosition(40);
			m_pFunction->RegisterImage(0, CIOSWUtilities::GetImagePathFile(_T("FunctionTest_btn.bmp")));
		}
	}
}

void CIODetailDlg::OnClose()
{
	m_fontListHeader.DeleteObject();
	m_fontListBody.DeleteObject();

	CDialogEx::OnClose();
}

void CIODetailDlg::SetIODeviceInfoManager(CIODeviceInformationManager* pMgr)
{
	m_pIODeviceInfoMgr = pMgr;
}

void CIODetailDlg::SetDataManager(CIOSWDataManager* pMgr)
{
	m_pDataMgr = pMgr;
}

void CIODetailDlg::SetLRUInfo(const int & nDeviceID, const int & nBoardID)
{
	m_nDeviceID = nDeviceID;
	m_nBoardID = nBoardID;

	int nRudderTest = CIOSWUtilities::LoadConfigNumber(_T("FUNCTION_IO"), _T("RUDDER_IO"));
	int nStickTest = CIOSWUtilities::LoadConfigNumber(_T("FUNCTION_IO"), _T("STICK_IO"));

	if (m_nDeviceID == nRudderTest || m_nDeviceID == nStickTest)
		m_bFunctionTest = true;
}

BOOL CIODetailDlg::OnEraseBkgnd(CDC* pDC)
{
	if (m_bmpBackgound.m_hObject)
	{
		CDC MemDC;

		if (MemDC.CreateCompatibleDC(pDC) == FALSE)
			return FALSE;

		CBitmap *pOldBitmap = MemDC.SelectObject(&m_bmpBackgound);

		BITMAP BmpInfo;
		m_bmpBackgound.GetBitmap(&BmpInfo);

		pDC->BitBlt(0, 0, BmpInfo.bmWidth, BmpInfo.bmHeight, &MemDC, 0, 0, SRCCOPY);

		MemDC.SelectObject(pOldBitmap);
		MemDC.DeleteDC();

		return TRUE;
	}
	else
		return CDialogEx::OnEraseBkgnd(pDC);
}


void CIODetailDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// Delete oject for bitmap
	m_bmpBackgound.DeleteObject();
	
	//DeleteObject(m_hBrush);
}


HBRUSH CIODetailDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	//switch (nCtlColor)
	//{
	//	case CTLCOLOR_STATIC:
	//	{
	//		pDC->SetTextColor(RGB(255, 255, 255));
	//		pDC->SetBkMode(TRANSPARENT);
	//		return m_hBrush;

	//	}
	//}

	return hbr;
}


void CIODetailDlg::OnPaint()
{
	CPaintDC dc(this); 

	if (m_pBIDImage != NULL) {
		CString strTemp;
		strTemp.Format(_T("Board ID : %d"), m_nBoardID);
		m_pBIDImage->DrawObject(&dc, strTemp, &m_fontListHeader, RGB(255, 255, 255), 0, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	}

	if (m_pLRUImage != NULL) {

		if (m_pIODeviceInfoMgr != NULL) {
			CIODeviceInfo* pInfo = m_pIODeviceInfoMgr->GetDeivceInfo(m_nDeviceID);

			if (pInfo != NULL)
			{
				CString strLRU;
				CString strTemp;

				pInfo->GetDeviceName(strLRU);
				strTemp.Format(_T("LRU Name : %s"), strLRU);

				m_pLRUImage->DrawObject(&dc, strTemp, &m_fontListHeader, RGB(255, 255, 255), 0, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
			}
		}
	}

	if (m_pFunction != NULL) {
		m_pFunction->DrawObject(&dc);
	}

}

void CIODetailDlg::OnClickIODetailList(NMHDR *pNMHDR, LRESULT *pResult)
{
	IOSW_MODE eMode = theApp.GetMainDlg()->GetIOSWMode();

	// The monitoring mode can not be input.
	if (eMode == IM_MONITORING) {
		*pResult = 0;
		return;
	}

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nClickItem = pNMListView->iItem;

	if (nClickItem < 0)
		return;
	
	int nIndex = 0;
	nIndex = _ttoi(m_listCtrlIODetail.GetItemText(nClickItem, 0));

	if (m_pIODeviceInfoMgr != NULL) {

		CIODeviceInfo* pInfo = m_pIODeviceInfoMgr->GetDeivceInfo(m_nDeviceID);

		if (pInfo != NULL) {
			sIOInformation * psIOInfo = pInfo->GetIOInfo(nIndex);
			CRect rect;
			m_listCtrlIODetail.GetItemRect(nClickItem, &rect, LVIR_BOUNDS);

			switch (psIOInfo->eKind)
			{
			case IK_DO:
			{
				CDOInputDlg dlg;
				
				dlg.m_ptPosition.y = rect.top + 120;
				dlg.SetBoardID(pInfo->GetBoardID());
				dlg.SetIOInformation(psIOInfo);
				dlg.SetIOSWDataManager(m_pDataMgr);

				dlg.DoModal();

			}
			break;
			case IK_AO:
			case IK_AO_IDC:
			{
				CAOInputDlg dlg;
				dlg.m_ptPosition.y = rect.top + 120;
				dlg.SetBoardID(pInfo->GetBoardID());;
				dlg.SetDeviceID(pInfo->GetDeviceID());
				dlg.SetIOInformation(psIOInfo);
				dlg.SetIOSWDataManager(m_pDataMgr);

				dlg.DoModal();
			}
			break;
			case IK_DIMMER:
			{
				CDimmerInputDlg dlg;
				dlg.m_ptPosition.y = rect.top + 120;
				dlg.SetBoardID(pInfo->GetBoardID());
				dlg.SetIOInformation(psIOInfo);
				dlg.SetIOSWDataManager(m_pDataMgr);

				dlg.DoModal();
			}
			break;
			default:
				break;
			}
		}
	}

	*pResult = 0;
}


void CIODetailDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 100 && m_pIODeviceInfoMgr != NULL) {

		CIODeviceInfo* pInfo = m_pIODeviceInfoMgr->GetDeivceInfo(m_nDeviceID);

		if (pInfo != NULL)
		{
			LIST_ID IndexList;
			LIST_ID_ITR IndexItr;

			pInfo->GetIOIndexList(&IndexList);
			int nItemCount = 0;

			for (IndexItr = IndexList.begin(); IndexItr != IndexList.end(); ++IndexItr)
			{
				int nIndex = *IndexItr;

				sIOInformation* pIOInfo = pInfo->GetIOInfo(nIndex);

				if (pIOInfo != NULL)
				{
					CString strTemp;

					switch (pIOInfo->eKind)
					{
					case IK_DI:
					case IK_DO:
						strTemp.Format(_T("%d   "), pIOInfo->szValue);
						break;
					case IK_AI:
						strTemp.Format(_T("%d   "), pIOInfo->nValue);
						break;
					case IK_AO:
					case IK_DIMMER:
						strTemp.Format(_T("%d   "), pIOInfo->usValue);
						break;
					case IK_AO_IDC:
						strTemp.Format(_T("%d   "), (int) pIOInfo->fValue);
						break;
					case IK_AI_SR:
						strTemp.Format(_T("%0.1f   "), pIOInfo->fValue);
						break;
					default:
						break;
					}

					m_listCtrlIODetail.SetItemText(nItemCount, 5, strTemp);
				}
				nItemCount++;
			}

		}

	}

	CDialogEx::OnTimer(nIDEvent);
}


void CIODetailDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	//CDialogEx::OnOK();
}


void CIODetailDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::OnCancel();
}


void CIODetailDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	int nRudderTest = CIOSWUtilities::LoadConfigNumber(_T("FUNCTION_IO"), _T("RUDDER_IO"));
	int nStickTest = CIOSWUtilities::LoadConfigNumber(_T("FUNCTION_IO"), _T("STICK_IO"));

	if (m_nDeviceID == nRudderTest && m_pFunction != NULL) {

		if (m_pFunction->IsPtInRect(point))
		{
			CFunctionRudder dlg;
			dlg.DoModal();

			TRIM_COMMAND eCommand = dlg.GetTrimCommand();

			if (m_pDataMgr) {
				m_pDataMgr->SetMaintenaceRudderFunctionData(m_nBoardID, eCommand);
			}

		}

	}

	if (m_nDeviceID == nStickTest && m_pFunction != NULL) {

		if (m_pFunction->IsPtInRect(point))
		{
			CFunctionStick dlg;
			dlg.DoModal();

			TRIM_COMMAND eCommand = dlg.GetTrimCommand();

			if (m_pDataMgr) {
				m_pDataMgr->SetMaintenaceStickFunctionData(m_nBoardID, eCommand);
			}

		}

	}

	CDialogEx::OnLButtonDown(nFlags, point);
}
