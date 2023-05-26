
// MfcProject.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMfcProjectApp:
// See MfcProject.cpp for the implementation of this class
//

class CMfcProjectApp : public CWinApp
{
public:
	CMfcProjectApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMfcProjectApp theApp;
