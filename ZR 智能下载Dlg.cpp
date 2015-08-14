// ZR 智能下载Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZR 智能下载.h"
#include "ZR 智能下载Dlg.h"

#include <io.h>
#include "imagehlp.h"	// 自检需要
#pragma comment (lib, "imagehlp.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


DWORD DownloadFile_Len = 0;
DWORD DownloadFile_LenOK = 0;

char FILETYPE = 0;				// 1 为RAR  2 为 ZIP
/*  全局变量定义 */
CZRDlg *This = NULL;
DWORD	LIST_FILE_LEN = 0;
BOOL	Ting = FALSE;

/*  列表宏定义  */
#define __LIST_FILE_LEN				0		// 文件计数
#define __LIST_FILE_NAME			1		// 文件名
#define __LIST_FILE_UNP_SIZE		2		// 文件压缩前大小
#define __LIST_FILE_PACK_SIZE		3		// 文件压缩后大小
#define __LIST_FILE_PASSWORD		4		// 文件是否被加密
#define __LIST_FILE_FenGe			5		// 文件是否被加密
#define __LIST_FILE_BIAOJILen		6		// 标记+压缩头的长度
#define __LIST_FILE_FILETOU			7		// 文件头指针
#define __LIST_FILE_FILEWEI			8		// 文件尾指针

#define __LIST_FILE_ZIPDESCRIPTION_FILETOU			9		// 文件尾指针
#define __LIST_FILE_ZIPDESCRIPTION_FILEWEI			10		// 文件尾指针


/*  皮肤定义  */
typedef int(__stdcall* FunSkinH_AttachEx)( LPCTSTR strSkinFile, LPCTSTR strPassword);
typedef int(__stdcall* FunSkinH_AdjustAero)( int nAlpha, int nShwDark, int nShwSharp, int nShwSize, int nX, int nY, int nRed, int nGreen, int nBlue );

void Show_MSG(char LIST_FILE_NAME[], int LIST_FILE_UNP_SIZE, int LIST_FILE_PACK_SIZE, char LIST_FILE_PASSWORD[], DWORD FILE_TOU, DWORD FILE_WEI);
#include "URLDecode.h"
#include "Common.h"
#include "Download.h"
#include "Jiex_RAR.h"
#include "Jiex_ZIP.h"

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZRDlg dialog

CZRDlg::CZRDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZRDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZRDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	This = this;
}

void CZRDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZRDlg)
	DDX_Control(pDX, IDC_LIST_MSG, m_TS);
	DDX_Control(pDX, IDC_PROGRESS_DOWNLOADFILEDATE, m_PROGRESS_DOWNLOADFILE);
	DDX_Control(pDX, IDC_PROGRESS_FILEDATE, m_PROGRESS_FILEDATE);
	DDX_Control(pDX, IDC_LIST_FILE, m_LIST_FILE);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CZRDlg, CDialog)
	//{{AFX_MSG_MAP(CZRDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FenX, OnBUTTONFenX)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_FILE, OnDblclkListFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZRDlg message handlers
void WINAPI TSY()
{	
	for (;;)
	{
		SetDlgItemText(AfxGetApp()->m_pMainWnd->m_hWnd,IDC_TS,"本程序可以提取网络上压缩文件里面指定的文件。而不需要为了一个文件下载整个压缩包。");
		Sleep(5000);
		SetDlgItemText(AfxGetApp()->m_pMainWnd->m_hWnd,IDC_TS,"");
		Sleep(200);	
		SetDlgItemText(AfxGetApp()->m_pMainWnd->m_hWnd,IDC_TS,"此程序是我 (RAR)与【Hades QQ：315102821】(ZIP)合作共同设计而成。感谢 Hades。设计思路是 Hades提出。");
		Sleep(3000);
		SetDlgItemText(AfxGetApp()->m_pMainWnd->m_hWnd,IDC_TS,"");
		Sleep(200);	
		SetDlgItemText(AfxGetApp()->m_pMainWnd->m_hWnd,IDC_TS,"由于时间关系，此程序仓促完成，若发现了BUG请联系我们。谢谢！");
		Sleep(3000);
		SetDlgItemText(AfxGetApp()->m_pMainWnd->m_hWnd,IDC_TS,"");
		Sleep(200);	
		SetDlgItemText(AfxGetApp()->m_pMainWnd->m_hWnd,IDC_TS,"本程序或许会更新升级，访问：http://1007566569.qzone.qq.com");
		Sleep(3000);
		SetDlgItemText(AfxGetApp()->m_pMainWnd->m_hWnd,IDC_TS,"");
		Sleep(200);	
		SetDlgItemText(AfxGetApp()->m_pMainWnd->m_hWnd,IDC_TS,"程序暂时只支持【.RAR】、【.ZIP】压缩格式。");
		Sleep(3000);
		SetDlgItemText(AfxGetApp()->m_pMainWnd->m_hWnd,IDC_TS,"");
		Sleep(200);	
		SetDlgItemText(AfxGetApp()->m_pMainWnd->m_hWnd,IDC_TS,"欢迎和我们一起探讨、交流...O(∩_∩)O~~");
		Sleep(3000);
		SetDlgItemText(AfxGetApp()->m_pMainWnd->m_hWnd,IDC_TS,"");
		Sleep(200);	
	}	
}

BOOL  Scan()
{
	DWORD head_check_sum =1;
	DWORD check_sum=0;
	char buf[512];
	/* 取这个程序的文件名*/
	GetModuleFileName(GetModuleHandle(NULL),buf,512);
	/*调用MapFileAndCheckSum 取该文件的校验和*/
	if(CHECKSUM_SUCCESS!=MapFileAndCheckSum(buf,&head_check_sum,&check_sum))
		exit(1);
	
	/* 分析结果*/
	if(head_check_sum!=check_sum) // 发现被修改!
		return 1;
	return 0;
}

void scanOD() 
{
	// TODO: Add your control notification handler code here
	STARTUPINFO info;
	GetStartupInfo(&info);
	if(info.dwX!=0 || info.dwY!=0 || info.dwXCountChars!=0 || info.dwYCountChars!=0
		|| info.dwFillAttribute!=0 || info.dwXSize!=0 || info.dwYSize!=0)
		exit(1);
}


// 生成皮肤文件
BOOL NewZiYuan(char SK[], char SF[])
{
	// 如果 dll不存在
	if (_access(SK, 0) == -1)
	{
		char a[98277] = {0};
		HRSRC hRc=FindResource(NULL, "#130", "PF");
		if(!hRc)		return FALSE;
		
		HGLOBAL hg=LoadResource(NULL,hRc);  // 将资源载入内存并返回其在内存中首地址保存在hg中 
		DWORD dw=SizeofResource(NULL,hRc);  // 获得资源大小并用dw保存资源大小 
		memset(a,0,sizeof(a));
		memcpy(a,hg,dw); 	
		
		FILE *out=fopen(SK, "wb+");
		fwrite(a,1,dw,out);
		fclose(out);
	}
	
	if (_access(SF, 0) == -1)
	{
		char b[30422] = {0};	
		HRSRC hRc1=FindResource(NULL, "#131", "PF");		
		if(!hRc1)		return FALSE;
		
		HGLOBAL hg=LoadResource(NULL,hRc1);
		DWORD dw=SizeofResource(NULL,hRc1);
		memset(b,0,sizeof(b));
		memcpy(b,hg,dw);	
		
		FILE *out=fopen(SF, "wb+");
		fwrite(b,1,dw,out);
		fclose(out);
	}
	
	return TRUE;
}


void Show_MSG(char LIST_FILE_NAME[], int LIST_FILE_UNP_SIZE, int LIST_FILE_PACK_SIZE, char LIST_FILE_PASSWORD[], DWORD FILE_TOU, DWORD FILE_WEI)
{
	char LEN[5]		= {0};
	char UNP_SIZE[9]	= {0};
	char PACK_SIZE[9]	= {0};

	char FileTou[9] = {0};
	char FileWei[9]	= {0};

	sprintf(LEN, "%d", LIST_FILE_LEN+1);

	sprintf(UNP_SIZE, "%d", LIST_FILE_UNP_SIZE);
	sprintf(PACK_SIZE, "%d", LIST_FILE_PACK_SIZE);

	sprintf(FileTou, "%d", FILE_TOU);
	sprintf(FileWei, "%d", FILE_WEI);

	This->m_LIST_FILE.InsertItem(LIST_FILE_LEN, LEN);
	This->m_LIST_FILE.SetItemText(LIST_FILE_LEN, __LIST_FILE_NAME, LIST_FILE_NAME);
	This->m_LIST_FILE.SetItemText(LIST_FILE_LEN, __LIST_FILE_UNP_SIZE, UNP_SIZE);			
	This->m_LIST_FILE.SetItemText(LIST_FILE_LEN, __LIST_FILE_PACK_SIZE, PACK_SIZE);			
	This->m_LIST_FILE.SetItemText(LIST_FILE_LEN, __LIST_FILE_PASSWORD, LIST_FILE_PASSWORD);	

	This->m_LIST_FILE.SetItemText(LIST_FILE_LEN, __LIST_FILE_FILETOU, FileTou);
	This->m_LIST_FILE.SetItemText(LIST_FILE_LEN, __LIST_FILE_FILEWEI, FileWei);
	
	This->m_LIST_FILE.EnsureVisible(LIST_FILE_LEN, 1);
	LIST_FILE_LEN++;
}



BOOL CZRDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	if (Scan())
	{
		AfxMessageBox("注意！发现文件被修改。此文件不是原版文件。");
		exit(1);
	}
	/************************************************************************/
	/*  皮肤生成                                                            */
	/************************************************************************/
	
	char WindowsTitleTmp[200] = {0};
	char Tmp[MAX_PATH] = {0};
	char Temp[MAX_PATH] = {0};
	DWORD dwSize=100;
	GetTempPath(dwSize, Tmp);//获取临时文件夹路径 
	strcpy(Temp, Tmp);
	
	GetWindowText(WindowsTitleTmp, sizeof(WindowsTitleTmp));
	strcat(WindowsTitleTmp, "_Sk.tmp");
	strcat(Tmp, WindowsTitleTmp);
	GetWindowText(WindowsTitleTmp, sizeof(WindowsTitleTmp));
	strcat(WindowsTitleTmp, "_Sf.tmp");
	strcat(Temp, WindowsTitleTmp);
	
	// 读取自身资源文件 释放皮肤文件
	if (NewZiYuan(Tmp, Temp))
	{
		// 加载皮肤
		HINSTANCE hInstance = NULL;
		hInstance = ::LoadLibrary(Tmp);
		if (hInstance)
		{
			FunSkinH_AttachEx  SkinH_AttachEx = (FunSkinH_AttachEx)GetProcAddress(hInstance, "SkinH_AttachEx");
			FunSkinH_AdjustAero SkinH_AdjustAero = (FunSkinH_AdjustAero)GetProcAddress(hInstance, "SkinH_AdjustAero");
			//			FunSkinH_SetMenuAlpha SkinH_SetMenuAlpha = (FunSkinH_SetMenuAlpha)GetProcAddress(hInstance, "SkinH_SetMenuAlpha");
			//			FunSkinH_Map SkinH_Map = (FunSkinH_Map)GetProcAddress(hInstance, "SkinH_Map");
			//			FunSkinH_SetForeColor SkinH_SetForeColor = (FunSkinH_SetForeColor)GetProcAddress(hInstance, "SkinH_SetForeColor");
			
			if (!SkinH_AttachEx(Temp, NULL))
			{		
				SkinH_AdjustAero(
					100,			//透明度,   0-255, 默认值0
					0,				//亮度,     0-255, 默认值0
					15,				//锐度,	    0-255, 默认值0 
					3,				//阴影大小, 2-19,  默认值2
					0,				//水平偏移, 0-25,  默认值0 (目前不支持)
					0,				//垂直偏移, 0-25,  默认值0 (目前不支持)
					0,				//红色分量, 0-255, 默认值 -1
					0,				//绿色分量, 0-255, 默认值 -1 
					0);				//蓝色分量, 0-255, 默认值 -1
			}
			else
				AfxMessageBox("加载皮肤失败 ~");
		}
		else
			AfxMessageBox("加载皮肤 dll 失败 ~");
	}
	else
		AfxMessageBox(" 读取自身资源文件失败 ~");

	/************************************************************************/
	/************************************************************************/

	DWORD dwStyle = m_LIST_FILE.GetExtendedStyle(); // 添加列表的网格线
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	m_LIST_FILE.SetExtendedStyle(dwStyle);

	m_LIST_FILE.InsertColumn(__LIST_FILE_LEN, "Cout", LVCFMT_CENTER, 38);
	m_LIST_FILE.InsertColumn(__LIST_FILE_NAME, "文件名", LVCFMT_LEFT, 318);
	m_LIST_FILE.InsertColumn(__LIST_FILE_UNP_SIZE, "文件压缩前大小", LVCFMT_LEFT, 100);
	m_LIST_FILE.InsertColumn(__LIST_FILE_PACK_SIZE, "文件压缩后大小", LVCFMT_LEFT, 100);
	m_LIST_FILE.InsertColumn(__LIST_FILE_PASSWORD, "加密", LVCFMT_CENTER, 38);

	m_LIST_FILE.InsertColumn(__LIST_FILE_FenGe, "", LVCFMT_CENTER, 0);
	m_LIST_FILE.InsertColumn(__LIST_FILE_BIAOJILen, "", LVCFMT_CENTER, 0);
	m_LIST_FILE.InsertColumn(__LIST_FILE_FILETOU, "", LVCFMT_CENTER, 0);
	m_LIST_FILE.InsertColumn(__LIST_FILE_FILEWEI, "", LVCFMT_CENTER, 0);

	m_LIST_FILE.InsertColumn(__LIST_FILE_ZIPDESCRIPTION_FILETOU, "", LVCFMT_CENTER, 0);
	m_LIST_FILE.InsertColumn(__LIST_FILE_ZIPDESCRIPTION_FILEWEI, "", LVCFMT_CENTER, 0);


	if (SocketChuShiHua())
	{
		My_ShowTS("Socket初始化失败。");
		return TRUE;
	}
//	SetDlgItemText(IDC_EDIT_URL, "http://tools.pediy.com/Disassemblers/ida/ida6.1/ida61.rar");
	SetDlgItemText(IDC_EDIT_URL, "http://www.mndsoft.com/downfiles/RunStartup.rar");
	
	SetDlgItemText(IDC_EDIT_URL, "http://5.xmyd1.crsky.com/201202/ccdwhs-v1.2.zip");
//	http://tools.pediy.com/Disassemblers/ida/ida6.1/ida61.rar
// Thunder://QUFodHRwOi8vaW0uYmFpZHUuY29tL2luc3RhbGwvQmFpZHVIaS5leGVaWg==
//	SetDlgItemText(IDC_EDIT_URL, "Thunder://QUFodHRwOi8vaW0uYmFpZHUuY29tL2luc3RhbGwvQmFpZHVIaS5leGVaWg==");
//	SetDlgItemText(IDC_EDIT_URL, "http://www.baidu.com/cb.php?c=IgF_pyfqPWbzrjfdP6KYTjYk0A7b5HbYPjDLn6KbuHY3PWbzrHf0TAq15HmYnHfzPfK15Hnsn1KbnjbYrymYrynLuHb0uZfqnHnvrjD4rHf1nsKdThsqpZwYTjCEQL9GmgG9pi4vTLw9TMwbULI8QhPEUiqbULI8Qh71TjqGujY1PWc0ThfqnHD0mhYqn0KsTWYs0ZNGujYzPWnkPWTv0AqGujYknWnvPjD0mv-b5HcsnW6snsKEIv3qnHD4PWn40APzm1YkPj63P6");

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)TSY, NULL, NULL, NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CZRDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CZRDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CZRDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

int i = 0;
void Test()
{	
	char Tmp[1024] = {0};
	HANDLE Thread;

	RAR_STRUCT *RarStruct = new RAR_STRUCT[10];

	memset(RarStruct, 0, sizeof(RarStruct));		
	This->GetDlgItemText(IDC_EDIT_URL, Tmp, sizeof(Tmp));
	if (!strlen(Tmp))
	{
		MessageBox(0, "请输入RAR下载地址。", "提示", MB_SYSTEMMODAL);
		This->SetDlgItemText(IDC_BUTTON_FenX, "分析");
		if (RarStruct)
			delete []RarStruct;
		return;
	}
	
	strcpy(RarStruct->Url.Url, Tmp);
//	UrlChaiFen(&RarStruct->Url);
	My_ShowTS("正在分析 URL 。。。");
	URL_ChuLi(&RarStruct->Url);
	My_ShowTS("分析 URL 完毕 。。。");

	memset(Tmp, 0, sizeof(Tmp));
	if (!GetHead(&RarStruct->Url, NULL, NULL, NULL, NULL, 0))
	{	
		My_ShowTS("初始化SOCKET失败，请重试。。。");
		This->SetDlgItemText(IDC_BUTTON_FenX, "分析");
		if (RarStruct)
			delete []RarStruct;
		return;
	}
	// 获取标记头
	if (!GetHead(&RarStruct->Url, 0, 6, Tmp, 7, 1))
	{
		My_ShowTS("获取文件类型失败，请重试。。。");
		This->SetDlgItemText(IDC_BUTTON_FenX, "分析");
		if (RarStruct)
			delete []RarStruct;
		return;
	}

	// RAR 文件
	if(Tmp[0] == 0x52 && Tmp[1] == 0x61 && Tmp[2] == 0x72 && Tmp[3] == 0x21 && Tmp[4] == 0x1A && Tmp[5] == 0x07 && Tmp[6] == 0x00 )
	{
		FILETYPE = 1;
		Thread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Rar_ThreadProc, (LPVOID)RarStruct, NULL, NULL);
	}

	// ZIP 文件
	if(Tmp[0] == 0x50 && Tmp[1] == 0x4B && Tmp[2] == 0x03 && Tmp[3] == 0x04 && Tmp[4] == 0x14 && Tmp[5] == 0 && Tmp[6] == 0)
	{
		FILETYPE = 2;
		Thread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Zip_ThreadProc, (LPVOID)RarStruct, NULL, NULL);
	}

	while(!Ting)
		Sleep(300);

	if (RarStruct)
		delete []RarStruct;

	TerminateThread(Thread, 0);
	This->SetDlgItemText(IDC_BUTTON_FenX, "分析");

	My_ShowTS("分析完毕 。。。");
}


void CZRDlg::OnBUTTONFenX() 
{
	// http://www.mndsoft.com/downfiles/RunStartup.rar
/*	char Tmp[100] = {0};
	DownloadHTTP("www.mndsoft.com", "/downfiles/RunStartup.rar", 0, 32, Tmp);*/
//	RarRead("http://www.mndsoft.com/downfiles/RunStartup.rar" , "SS");
	/*char LEN[5] = {0};
	sprintf(LEN, "%d", LIST_FILE_LEN+1);
	This->m_LIST_FILE.InsertItem(LIST_FILE_LEN, LEN);
	This->m_LIST_FILE.SetItemText(LIST_FILE_LEN, __LIST_FILE_NAME, "sss");
	LIST_FILE_LEN++;
	My_ShowTS("GSGSGDASG");
	return;*/
	scanOD();
	char Tmp[5] = {0}; 
	GetDlgItemText(IDC_BUTTON_FenX, Tmp, sizeof(Tmp));
	if (strcmp(Tmp, "分析") == 0)
	{
		LIST_FILE_LEN = 0;
		Ting = FALSE;
		m_LIST_FILE.DeleteAllItems();
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Test, NULL, NULL, NULL);
		SetDlgItemText(IDC_BUTTON_FenX, "停止");
	}
	else
	{
		Ting = TRUE;
		
	}

	return ;

}

void RAR_DownloadFile(int CtlList)
{
	
	DWORD FileTou	= 0;
	DWORD FileWei	= 0;
	char Tmp[1024] = {0};
	URL_STRUCT *Url;	
	FILE *fp = NULL;
	char Path[MAX_PATH] = {0};
	char RARWEI[] = {0xC4,  0x3D,  0x7B,  0x00,  0x40,  0x07,  0x00};
	char *Buff ;
	
	GetModuleFileName(NULL, Path, sizeof(Path));
	*(strrchr(Path, '\\')+1) = '\0';
	
	Url = new URL_STRUCT;	
	memset(Url, 0, sizeof(URL_STRUCT));
	
	strcpy(Tmp, This->m_LIST_FILE.GetItemText(CtlList, __LIST_FILE_FILETOU));
	FileTou = atoi(Tmp);
	strcpy(Tmp, This->m_LIST_FILE.GetItemText(CtlList, __LIST_FILE_FILEWEI));
	FileWei = atoi(Tmp);
	
	strcpy(Tmp, This->m_LIST_FILE.GetItemText(CtlList, __LIST_FILE_NAME));
	Buff = Tmp;
	while(strstr(Buff, "\\"))
		*(strstr(Buff, "\\")) = '^';

/*	if (strstr(Tmp, "\\"))		
		Buff += strrchr(Tmp, '\\')+1 - Tmp;*/
	strcat(Path, Buff);
	strcat(Path, ".rar");
	fp = fopen(Path, "wb+");
	if (!fp)
	{
		sprintf(Tmp, "创建文件失败：%s 文件被占用或所在路径不可写。", Path);
		Show_MSG(Tmp, GetLastError(), 0, 0, 0, 0);
		return ;
	}
	
	This->GetDlgItemText(IDC_EDIT_URL, Tmp, MAX_PATH);
	strcpy(Url->Url, Tmp);
	UrlChaiFen(Url);
	
	DownloadDate(Url, 0, 19, fp);
	DownloadDate(Url, FileTou, FileWei, fp);
	fwrite(RARWEI, 7, 1, fp);
	fclose(fp);
	
	sprintf(Tmp, "文件下载完毕：%s", Path);
	My_ShowTS(Tmp);
	DownloadFile_Len -- ;
	DownloadFile_LenOK++;
	sprintf(Tmp, " 信息提示 【已完成 %d 文件。剩余 %d 文件。共 %d 文件】", DownloadFile_LenOK, DownloadFile_Len, DownloadFile_Len+DownloadFile_LenOK);
	This->SetDlgItemText(IDC_STATIC_XX, Tmp);

	if (DownloadFile_LenOK == DownloadFile_Len+DownloadFile_LenOK)
	{
		sprintf(Tmp, "所有文件下载完毕。。。", DownloadFile_LenOK, DownloadFile_Len, DownloadFile_Len+DownloadFile_LenOK);
		My_ShowTS(Tmp);
	}
	return ;
}

void ZIP_DownloadFile(int CtlList)
{
	
	DWORD FileTou	= 0;
	DWORD FileWei	= 0;
	DWORD ZipDescriptionTou = 0;
	DWORD ZipDescriptionWei = 0;
	DWORD ZipFinishTou = 0;
	DWORD ZipFinishWei = 0;

	char Tmp[1024] = {0};
	URL_STRUCT *Url;	
	FILE *fp = NULL;
	char Path[MAX_PATH] = {0};
	char *Buff ;
	
	GetModuleFileName(NULL, Path, sizeof(Path));
	*(strrchr(Path, '\\')+1) = '\0';
	
	Url = new URL_STRUCT;	
	memset(Url, 0, sizeof(URL_STRUCT));
	
	strcpy(Tmp, This->m_LIST_FILE.GetItemText(CtlList, __LIST_FILE_FILETOU));
	FileTou = atoi(Tmp);
	strcpy(Tmp, This->m_LIST_FILE.GetItemText(CtlList, __LIST_FILE_FILEWEI));
	FileWei = atoi(Tmp);

	strcpy(Tmp, This->m_LIST_FILE.GetItemText(CtlList, __LIST_FILE_ZIPDESCRIPTION_FILETOU));
	ZipDescriptionTou = atoi(Tmp);

	strcpy(Tmp, This->m_LIST_FILE.GetItemText(CtlList, __LIST_FILE_ZIPDESCRIPTION_FILEWEI));
	ZipDescriptionWei = atoi(Tmp);

	strcpy(Tmp, This->m_LIST_FILE.GetItemText(LIST_FILE_LEN-1, __LIST_FILE_FILETOU));
	ZipFinishTou = atoi(Tmp);

	strcpy(Tmp, This->m_LIST_FILE.GetItemText(LIST_FILE_LEN-1, __LIST_FILE_FILEWEI));
	ZipFinishWei = atoi(Tmp);
	
	strcpy(Tmp, This->m_LIST_FILE.GetItemText(CtlList, __LIST_FILE_NAME));
	Buff = Tmp;
	while(strstr(Buff, "\\"))
		*(strstr(Buff, "\\")) = '^';

/*	if (strstr(Tmp, "\\"))		
		Buff += strrchr(Tmp, '\\')+1 - Tmp;*/
	strcat(Path, Buff);
	strcat(Path, ".zip");
	fp = fopen(Path, "wb+");
	if (!fp)
	{
		sprintf(Tmp, "创建文件失败：%s 文件被占用或所在路径不可写。", Path);
		Show_MSG(Tmp, GetLastError(), 0, 0, 0, 0);
		return ;
	}
	
	This->GetDlgItemText(IDC_EDIT_URL, Tmp, MAX_PATH);
	strcpy(Url->Url, Tmp);
	UrlChaiFen(Url);

	DownloadDate(Url, FileTou, FileWei-1, fp);
	DownloadDate(Url, ZipDescriptionTou, ZipDescriptionWei-1, fp);
	DownloadDate(Url, ZipFinishTou, ZipFinishWei, fp);
	fclose(fp);

	sprintf(Tmp, "文件下载完毕：%s", Path);
	My_ShowTS(Tmp);

	sprintf(Tmp, "正在处理该文件。。。");
	My_ShowTS(Tmp);
	DWORD Size = 0;
	fp = fopen(Path, "rb+");
	fseek(fp,FileWei-FileTou+42, 0);
	fwrite(&Size, 2, 1, fp);					// 修改第一个ZIP_HEADER出现的位 即0 
	Size = 1;
	fseek(fp, FileWei-FileTou+(ZipDescriptionWei-ZipDescriptionTou)+8, 0);
	fwrite(&Size, 2, 1, fp);
	fwrite(&Size, 2, 1, fp);
	Size = ZipDescriptionWei-ZipDescriptionTou;
	fwrite(&Size, 4, 1, fp);
	Size = FileWei-FileTou;
	fwrite(&Size, 4, 1, fp);
	fclose(fp);

	sprintf(Tmp, "处理该文件完毕。。。");
	My_ShowTS(Tmp);
	
	DownloadFile_Len -- ;
	DownloadFile_LenOK++;
	sprintf(Tmp, " 信息提示 【已完成 %d 文件。剩余 %d 文件。共 %d 文件】", DownloadFile_LenOK, DownloadFile_Len, DownloadFile_Len+DownloadFile_LenOK);
	This->SetDlgItemText(IDC_STATIC_XX, Tmp);

	if (DownloadFile_LenOK == DownloadFile_Len+DownloadFile_LenOK)
	{
		sprintf(Tmp, "所有文件下载完毕。。。", DownloadFile_LenOK, DownloadFile_Len, DownloadFile_Len+DownloadFile_LenOK);
		My_ShowTS(Tmp);
	}
	return ;
}

DWORD DownloadFile(LPVOID lpParam)
{
	int CtlList = (int) lpParam;
	if(CtlList != LIST_FILE_LEN-1 || FILETYPE == 1)
	{
		// 如果 __LIST_FILE_ZIPDESCRIPTION_FILETOU 没有存放数据则认为是RAR  否则认为ZIP
		if (FILETYPE == 1)
			RAR_DownloadFile(CtlList);
		else if (FILETYPE == 2)
			ZIP_DownloadFile(CtlList);
	}
	else 
	{
		
		char Tmp[1024] = {0};
		URL_STRUCT *Url;	
		FILE *fp = NULL;
		char Path[MAX_PATH] = {0};
		char *Buff ;
		
		GetModuleFileName(NULL, Path, sizeof(Path));
		*(strrchr(Path, '\\')+1) = '\0';
		
		Url = new URL_STRUCT;	
		memset(Url, 0, sizeof(URL_STRUCT));
		
		This->GetDlgItemText(IDC_EDIT_URL, Tmp, MAX_PATH);
		strcpy(Url->Url, Tmp);
		UrlChaiFen(Url);

		strcpy(Tmp, Url->HostFile);
		Buff = Tmp;
		Buff += strrchr(Buff, '//')-Buff;
		Buff ++;
		while(strstr(Buff, "\\"))
			*(strstr(Buff, "\\")) = '^';

		strcat(Path, Buff);
		strcat(Path, ".zip");
		fp = fopen(Path, "wb+");
		if (!fp)
		{
			sprintf(Tmp, "创建文件失败：%s 文件被占用或所在路径不可写。%d", Path, GetLastError());
			My_ShowTS(Tmp);
			return 1;
		}
		
		DWORD Size = 0;
		strcpy(Tmp, This->m_LIST_FILE.GetItemText(CtlList, __LIST_FILE_PACK_SIZE));
		Size = atoi(Tmp);
		DownloadDate(Url, 0, Size, fp);
		fclose(fp);

		sprintf(Tmp, "文件下载完毕：%s", Path);
		My_ShowTS(Tmp);

	}
	
	return 1;
}

void XiaFaRenWu()
{
	DownloadFile_Len = DownloadFile_LenOK = 0;
	char Tmp[100] = {0};
	for (DWORD i=0; i<LIST_FILE_LEN; i++)
	{
		
		// 如果是选中则发送指令
		if ( This->m_LIST_FILE.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			DownloadFile_Len++;
			while(!CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)DownloadFile, (LPVOID)i, NULL, NULL))
				Sleep(1000);
		}		
	}
	sprintf(Tmp, "正在下载选中的 %d 个文件。。。", DownloadFile_Len);
	My_ShowTS(Tmp);
}

void CZRDlg::OnDblclkListFile(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)XiaFaRenWu, NULL, NULL, NULL);	

	*pResult = 0;
}
