// ZR 智能下载.h : main header file for the ZR 智能下载 application
//

#if !defined(AFX_ZR_H__D2071D01_6EDF_4A75_8AF0_76BBAF95E5A3__INCLUDED_)
#define AFX_ZR_H__D2071D01_6EDF_4A75_8AF0_76BBAF95E5A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CZRApp:
// See ZR 智能下载.cpp for the implementation of this class
//

class CZRApp : public CWinApp
{
public:
	CZRApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZRApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CZRApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZR_H__D2071D01_6EDF_4A75_8AF0_76BBAF95E5A3__INCLUDED_)
