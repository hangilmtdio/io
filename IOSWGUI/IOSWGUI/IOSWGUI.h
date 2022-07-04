
// IOSWGUI.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "IOSWGUIDlg.h"

// CIOSWGUIApp:
// See IOSWGUI.cpp for the implementation of this class
//

class CIOSWGUIApp : public CWinApp
{
public:
	CIOSWGUIApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()

public:
	CIOSWGUIDlg* GetMainDlg() { return m_pIOSWGUIDlg; }

private:
	CIOSWGUIDlg	*			m_pIOSWGUIDlg;

public:
	virtual int ExitInstance();
};

extern CIOSWGUIApp theApp;