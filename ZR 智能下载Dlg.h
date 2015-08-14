// ZR ÖÇÄÜÏÂÔØDlg.h : header file
//

#if !defined(AFX_ZRDLG_H__65B814B7_9F74_417D_B32C_DA8D01CF98A2__INCLUDED_)
#define AFX_ZRDLG_H__65B814B7_9F74_417D_B32C_DA8D01CF98A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CZRDlg dialog

class CZRDlg : public CDialog
{
// Construction
public:
	CZRDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CZRDlg)
	enum { IDD = IDD_ZR_DIALOG };
	CListBox	m_TS;
	CProgressCtrl	m_PROGRESS_DOWNLOADFILE;
	CProgressCtrl	m_PROGRESS_FILEDATE;
	CListCtrl	m_LIST_FILE;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZRDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CZRDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBUTTONFenX();
	afx_msg void OnDblclkListFile(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZRDLG_H__65B814B7_9F74_417D_B32C_DA8D01CF98A2__INCLUDED_)
