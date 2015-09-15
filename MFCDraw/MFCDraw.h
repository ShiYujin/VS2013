
// MFCDraw.h : main header file for the MFCDraw application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFCDrawApp:
// See MFCDraw.cpp for the implementation of this class
//

class CMFCDrawApp : public CWinAppEx
{
public:
	CMFCDrawApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFreedraw();
	afx_msg void OnLine();
public:
	afx_msg void OnClear();
	//afx_msg void OnAntia();
};

extern CMFCDrawApp theApp;
