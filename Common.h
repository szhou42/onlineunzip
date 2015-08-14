

// URL结构
struct URL_STRUCT
{
	IN	char	Url[1024];
	OUT	char	XieYi[10];
	OUT	char	Host[1024];
	OUT	char	HostFile[1024];
	OUT	char	FileType[5];
	OUT int		Prot;
};

// 文件结构
struct FILE_DATE
{
	char FileName[MAX_PATH];
	DWORD FileOffSetTou ;		// 文件数据起始位置
	DWORD FileOffSetWei ;		// 文件数据结束位置
	DWORD FileLength;			// 文件总长度
	char PassWord[2];
	
};
/************************************************************************/
/* RAR结构                                                              */
/************************************************************************/


// 块标记结构
struct HEAD_STRUCT
{
	short	HEAD_CRC;			// 2字节 头CRC校验值
	char	HEAD_TYPE;			// 1字节 头类型：
	short	HEAD_FLAGS;			// 2字节 位标记
	short	HEAD_SIZE;			// 2字节 头总大小		
};

// 压缩文件头结构
struct MAIN_HEAD
{
	short	HEAD_CRC;			// 2字节 压缩文件头CRC校验值
	char	HEAD_TYPE;			// 1字节 头类型：0x73
	short	HEAD_FLAGS;			// 2字节 位标记
	short	HEAD_SIZE;			// 2字节 压缩文件头总大小(包括压缩文件注释)
	short	RESERVED1;			// 2字节 保留
	int		RESERVED2;			// 4字节 保留
};

// 文件头结构
struct FILE_HEAD
{
	short	HEAD_CRC;			// 2字节 文件头CRC校验值
	char	HEAD_TYPE;			// 1字节 头类型：0x74
	short	HEAD_FLAGS;			// 2字节 位标记
	short	HEAD_SIZE;			// 2字节 文件头的全部大小(包含文件名和注释)
	int		PACK_SIZE;			// 4字节 文件压缩后的大小
	int		UNP_SIZE;			// 4字节 文件压缩前的大小
	char	HOST_OS;			// 1字节 保存压缩文件使用的操作系统
	int		FILE_CRC;			// 4字节 文件的CRC校验值
	int		FTIME;				// 4字节 MS DOS标准格式的日期和时间
	char	UNP_VER;			// 1字节 解压文件所需要最低 RAR 版本
	char	METHOD;				// 1字节 压缩方式
	short	NAME_SIZE;			// 1字节 文件名大小
	int		ATTR;				// 4字节 文件属性
//	int		HIGH_PACK_SIZE;		// 4字节 压缩文件后的大小 64位值的高4字节	只有在HEAD_FLAGS中的0x100位被设置才存在
//	int		HIGH_UNP_SIZE;		// 4字节 压缩文件前的大小 64位值的高4字节	只有在HEAD_FLAGS中的0x100位被设置才存在
	char	FILE_NAME[MAX_PATH*2];	// 文件名
//	double	SALT;
};

// 文件头结构1
struct FILE_HEAD_1
{
	short	HEAD_CRC;				// 2字节 文件头CRC校验值
	char	HEAD_TYPE;				// 1字节 头类型：0x74
	short	HEAD_FLAGS;				// 2字节 位标记
	short	HEAD_SIZE;				// 2字节 文件头的全部大小(包含文件名和注释)
	int		PACK_SIZE;				// 4字节 文件压缩后的大小
	int		UNP_SIZE;				// 4字节 文件压缩前的大小
	char	HOST_OS;				// 1字节 保存压缩文件使用的操作系统
	int		FILE_CRC;				// 4字节 文件的CRC校验值
	int		FTIME;					// 4字节 MS DOS标准格式的日期和时间
	char	UNP_VER;				// 1字节 解压文件所需要最低 RAR 版本
	char	METHOD;					// 1字节 压缩方式
	short	NAME_SIZE;				// 1字节 文件名大小
	int		ATTR;					// 4字节 文件属性
	int		HIGH_PACK_SIZE;			// 4字节 压缩文件后的大小 64位值的高4字节	只有在HEAD_FLAGS中的0x100位被设置才存在
	int		HIGH_UNP_SIZE;			// 4字节 压缩文件前的大小 64位值的高4字节	只有在HEAD_FLAGS中的0x100位被设置才存在
	char	FILE_NAME[MAX_PATH*2];	// 文件名
	//	double	SALT;
};

struct RAR_STRUCT
{
	URL_STRUCT		Url;
	HEAD_STRUCT		Head;
	MAIN_HEAD		MainHead;
	FILE_HEAD		FileHead;
	FILE_DATE		FileDate;
};

/************************************************************************/
/* ZIP 结构                                                             */
/************************************************************************/
struct ZIP_HEADER
{
	DWORD Signature;											//标志"PK..":0x04034b50 4
	WORD  VersionToExtract;										//解压版本 2
	WORD  BitFlag;												//通用标志位 2
	WORD  CompressionMethod;									//压缩方式 2
	WORD  LastModifyTime;										//最后修改时间 2
	WORD  LastModifyDate;										//最后修改日期 2
	DWORD CRC32;												//CRC32值 4
	DWORD CompressedSize;										//压缩后大小 4 
	DWORD UncompressedSize;										//压缩前大小 4
	WORD SizeOfFileName;										//文件名大小 2
	WORD SizeOfExtraField;										//扩展域大小 2
	char  *FileName;									    	//文件名  260
	char  ExtraField[MAX_PATH*2];								//扩展域  260*2	
};

struct ZIP_DESCRIPTION
{
	DWORD Signature;											//标志"PK..":0x02014b50
	WORD  VersionToMake;										//压缩版本
	WORD  VersionToExtract;										//解压版本
	WORD  BitFlag;												//通用标志位
	WORD  CompressionMethod;									//压缩方式
	WORD  LastModifyTime;										//最后修改时间
	WORD  LastModifyDate;										//最后修改日期
	DWORD CRC32;												//CRC32值
	DWORD CompressedSize;										//压缩后大小
	DWORD UncompressedSize;										//压缩前大小
	WORD  SizeOfFileName;										//文件名大小
	WORD  SizeOfExtraField;										//扩展域大小
	WORD  SizeOfComment;										//注释大小
	WORD  DiskOffset;											//文件开始位置的磁盘编号
	WORD  InFileAttr;											//文件内部属性
	DWORD ExFileAttr;											//文件外部属性
	DWORD reOffset;												//本地文件header的相对位移
	char  *FileName;											//文件名
	char  *ExtraField;											//扩展域
	char  *Comment;												//注释
};

struct ZIP_FINISH
{
	DWORD Signature;											//标志"PK..":0x02014b50
	WORD  NumOfDisk;											//当前磁盘编号
	WORD  DiskOffset;											//核心目录开始位置的磁盘编号
	WORD  NumOfDire;											//该磁盘上所记录的核心目录数量		
	WORD  NumOfAllDire;											//核心目录结构总数
	DWORD SizeOfCenDire;										//核心目录的大小
	DWORD reOffset;												//核心目录开始位置相对于archive开始的位移
	WORD  SizeOfComment;										//注释大小
	char  *Comment;												//注释
};
struct ZIP_STRUCT
{
	URL_STRUCT			Url;
	ZIP_HEADER			ZipHeader;
	ZIP_DESCRIPTION		ZipDescription;
	ZIP_FINISH			ZipFinish;
	FILE_DATE			FileDate;
};

/************************************************************************/
/* 自定义                                                               */
/************************************************************************/

HINTERNET	hNet				= NULL;
HINTERNET	hConnect			= NULL;
HINTERNET   hHttpFile			= NULL;

SOCKET Socket;

/****************** Socket 初始化 ******************/
int SocketChuShiHua() 
{
	WSADATA wsaData;
	
	if (WSAStartup(MAKEWORD(2,2),&wsaData))
		return 1;			// 无法初始化套接字库
	
	if (HIBYTE(wsaData.wVersion)!=2 ||	LOBYTE(wsaData.wVersion)!=2)
	{
		WSACleanup();	
		return 1;			// 套接字版本不符合2.2
	}
	
	return 0;
}
void My_ShowTS(char Text[])
{
	char *Tou = NULL;
	char *Wei = NULL;

	int Len = 0;
	
	Wei = Text;

	while(1)
	{
		
		Tou = strstr(Wei, "\n");	
		if (Tou)
		{
			Len = Tou-Text;
			char *buf = new char[Len+1];
			memset(buf, 0, Len+1);
			memcpy(buf, Wei, Tou-Wei);
			This->m_TS.AddString(buf);
			This->m_TS.SetCurSel (This->m_TS.GetCount() - 1);

			Wei = Tou+1 ;
		}
		else
			break;
	}
	This->m_TS.AddString(Wei);
	This->m_TS.SetCurSel (This->m_TS.GetCount() - 1);
}
/************************************************************************/
/* 分解URL 不合法则返回 TRUE                                           */
/************************************************************************/
BOOL UrlChaiFen(IN URL_STRUCT *UrlStruct)
{	

	char *Tmp = new char[1024];
	memset(Tmp, 0, sizeof(Tmp));
	char *Tou		= NULL;
	char *Wei		= NULL;

	// 如果是迅雷链接则解码
	if (strnicmp(UrlStruct->Url, "Thunder://", strlen("Thunder://")) == 0)
	{
		char *URL = new char[strlen(UrlStruct->Url)+1];
		memset(URL, 0, sizeof(URL));
		Tou = strstr(UrlStruct->Url, "://");
		if (Tou)
		{
			Tou += strlen("://");
			strcpy(URL, Tou);
		}

		unsigned int nBufLen = Base64Decode(URL, strlen(URL), NULL, 0);
		char *pBase64Decode = (char *)malloc(nBufLen+ 1);
		memset(pBase64Decode, 0, nBufLen+1);
		Base64Decode(URL, strlen(URL), pBase64Decode, nBufLen);
		pBase64Decode[nBufLen] = '\0';	
		memset(URL, 0, sizeof(URL));
		memcpy(URL, pBase64Decode+2 , nBufLen);
		URL[nBufLen-4] = '\0'; 
		free(pBase64Decode);
		memset(UrlStruct, 0, sizeof(UrlStruct));
		strcpy(UrlStruct->Url, URL);
		
		sprintf(Tmp, "成功解析迅雷下载地址：%s", URL);
		My_ShowTS(Tmp);
	}

	// 如果是快车链接则解码
	if (strnicmp(UrlStruct->Url, "Flashget://", strlen("Flashget://")) == 0)
	{
		char *URL = new char[strlen(UrlStruct->Url)+1];
		memset(URL, 0, sizeof(URL));
		Tou = strstr(UrlStruct->Url, "://");
		if (Tou)
		{
			Tou += strlen("://");
			Wei = strstr(Tou, "&");
			if (Wei)
			{
				memcpy(URL, Tou, Wei-Tou);
				URL[Wei-Tou] = '\0';
			}
			else
				strcpy(URL, Tou);
		}
		
		unsigned int nBufLen = Base64Decode(URL, strlen(URL), NULL, 0);
		char *pBase64Decode = (char *)malloc(nBufLen+ 1);
		memset(pBase64Decode, 0, nBufLen+1);
		Base64Decode(URL, strlen(URL), pBase64Decode, nBufLen);
		pBase64Decode[nBufLen] = '\0';
		memset(URL, 0, sizeof(URL));
		memcpy(URL, pBase64Decode+10 , nBufLen);
		free(pBase64Decode);

		URL[nBufLen-20] = '\0';
				
		memset(UrlStruct, 0, sizeof(UrlStruct));
		strcpy(UrlStruct->Url, URL);	
		
		sprintf(Tmp, "成功解析快车下载地址：%s", URL);
		My_ShowTS(Tmp);
	}

	// 如果是QQ旋风链接则解码
	if (strnicmp(UrlStruct->Url, "qqdl://", strlen("qqdl://")) == 0)
	{
		char *URL = new char[strlen(UrlStruct->Url)+1];
		memset(URL, 0, sizeof(URL));
		Tou = strstr(UrlStruct->Url, "://");
		if (Tou)
		{
			Tou += strlen("://");
			Wei = strstr(Tou, "&");
			if (Wei)
			{
				memcpy(URL, Tou, Wei-Tou);
				URL[Wei-Tou] = '\0';
			}
			else
				strcpy(URL, Tou);
		}
		
		unsigned int nBufLen = Base64Decode(URL, strlen(URL), NULL, 0);
		char *pBase64Decode = (char *)malloc(nBufLen+ 1);
		memset(pBase64Decode, 0, nBufLen+1);
		Base64Decode(URL, strlen(URL), pBase64Decode, nBufLen);
		pBase64Decode[nBufLen] = '\0';
		memset(URL, 0, sizeof(URL));
		memcpy(URL, pBase64Decode, nBufLen);
		URL[nBufLen] = '\0';
		free(pBase64Decode);
			
		memset(UrlStruct, 0, sizeof(UrlStruct));
		strcpy(UrlStruct->Url, URL);	
		sprintf(Tmp, "成功解析QQ旋风下载地址：%s", URL);
		My_ShowTS(Tmp);
	}
	This->SetDlgItemText(IDC_EDIT_URL, UrlStruct->Url);
	Tou	= strstr(UrlStruct->Url, "//");					// 获取协议头
	if (Tou)
	{
		Tou += strlen("//");
		memcpy(UrlStruct->XieYi, UrlStruct->Url, Tou - UrlStruct->Url);
		UrlStruct->XieYi[Tou-UrlStruct->Url] = '\0';
	}
	else										
	{	
		strcpy(UrlStruct->XieYi, "http://");				// 如果没有协议头则默认为http协议
		Tou = UrlStruct->Url;
	}
	
	Wei = strstr(Tou, ":");									// 端口分析
	if (Wei)
	{
		Wei ++;
		char Tmp[10] = {0};
		memcpy(Tmp, Wei, strstr(Tou, "/") - Wei);
		UrlStruct->Prot = atoi(Tmp);
	}
	else
		UrlStruct->Prot = 80;

	Wei = strstr(Tou, "/");						// 获取域名和文件名
	if (Wei)
	{
		memcpy(UrlStruct->Host, Tou, Wei-Tou);
		UrlStruct->Host[Wei-Tou] = '\0';
		strcpy(UrlStruct->HostFile, Wei);
		if (UrlStruct->Prot != 80)
		{
			if (strstr(UrlStruct->Host, ":"))
				*(strstr(UrlStruct->Host, ":")) = '\0';
		}
	}
	else
		return TRUE;							// 没有文件名

	return FALSE;	
}

BOOL URL_ChuLi(URL_STRUCT *Url)
{
	char buf[1024] = {0};	
	char Tmp[1024] = {0};

	while(1)
	{
		if(UrlChaiFen(Url))
		{
			My_ShowTS("域名不合法！");
			return TRUE;
		}
		SOCKET sock = socket(PF_INET, SOCK_STREAM, 0);
		if(sock == INVALID_SOCKET)
		{
			sprintf(buf, "创建套接字失败。错误代码：%d", GetLastError());
			My_ShowTS(buf);
			return TRUE;
		}

		hostent* pHostEnt = gethostbyname(Url->Host);
		if(pHostEnt == NULL)
		{
			sprintf(buf, "解析域名失败。错误代码：%d", GetLastError());
			My_ShowTS(buf);
			return TRUE;
		}
		
		int nTime = 10000;
		setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&nTime, sizeof(nTime));
		setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&nTime, sizeof(nTime));
			
		//连接
		struct in_addr ip_addr;
		memcpy(&ip_addr, pHostEnt->h_addr_list[0], 4);
		
		struct sockaddr_in destaddr;
		memset((void *)&destaddr, 0, sizeof(destaddr));
		destaddr.sin_family = AF_INET;
		destaddr.sin_port = htons(Url->Prot);
		destaddr.sin_addr = ip_addr;
		
		if(0 != connect(sock,(struct sockaddr*)&destaddr, sizeof(destaddr)))
		{
			sprintf(buf, "连接对方服务器失败。错误代码：%d", GetLastError());
			My_ShowTS(buf);
			closesocket(sock);
			return TRUE;
		}
		
		//格式化请求，各字段含义参见HTTP协议RFC2616
		char request[1024] = {0};	
		sprintf(request, "HEAD %s HTTP/1.1\r\nHost:%s\r\n\r\n", Url->HostFile, Url->Host);
		//发送请求
		if(SOCKET_ERROR == send(sock, request, strlen(request), 0))
		{
			sprintf(buf, "发送请求数据包失败。错误代码：%d", GetLastError());
			My_ShowTS(buf);
			closesocket(sock);
			return TRUE;
		}
		
		//接收数据并存储
		int rcv_bytes = 0;
		
		rcv_bytes = recv(sock, buf, sizeof(buf), 0);
		

		if (rcv_bytes == SOCKET_ERROR)
		{
			sprintf(buf, "接收请求数据包失败。错误代码：%d", GetLastError());
			My_ShowTS(buf);
			closesocket(sock);
			return TRUE;
		}
		closesocket(sock);
		char *Tou	= NULL;
		char *Wei	= NULL;
		Tou = strstr(buf, "HTTP/1.1 302");
		if (Tou)
		{
			Tou = strstr(buf, "Location:");
			Tou += strlen("Location: ");
			Wei = strstr(Tou, "\r\n");
			memcpy(buf, Tou, Wei-Tou);
			buf[Wei-Tou] = '\0';
			
			if (strstr(buf, "://"))
			{
				memset(Url, 0, sizeof(URL_STRUCT));
				memcpy(Url->Url, Tou, Wei-Tou);
			}
			else
			{
				strcpy(Url->Url, Url->Host);
				strcat(Url->Url, "/");
				strcat(Url->Url, buf);
			}
			sprintf(Tmp, "URL 被重定向。URL：%s", Url->Url);
			This->SetDlgItemText(IDC_EDIT_URL, Url->Url);
			My_ShowTS(Tmp);
			continue;
		}

		break;	
	}


  //  WSACleanup();
	return TRUE;
}

//连接

DWORD GetHead(URL_STRUCT *Url, DWORD DataTou, DWORD DataWei, LPVOID Head, DWORD HeadSize, BOOL Dw)
{
	char  buf[100] = {0};
	char *Tou;
	char *Wei;
	
	if (!Dw)
	{
		closesocket(Socket);
		
		Socket = socket(PF_INET, SOCK_STREAM, 0);
		if(Socket == INVALID_SOCKET)
		{
			sprintf(buf, "创建套接字失败。错误代码：%d", GetLastError());
			My_ShowTS(buf);
			return FALSE;
		}
		
		hostent* pHostEnt = gethostbyname(Url->Host);
		if(pHostEnt == NULL)
		{
			sprintf(buf, "解析域名失败。错误代码：%d", GetLastError());
			My_ShowTS(buf);
			return FALSE;
		}
		
		int nTime = 10000;
		setsockopt(Socket, SOL_SOCKET, SO_SNDTIMEO, (char*)&nTime, sizeof(nTime));
		setsockopt(Socket, SOL_SOCKET, SO_SNDTIMEO, (char*)&nTime, sizeof(nTime));
		
		struct in_addr ip_addr;
		memcpy(&ip_addr, pHostEnt->h_addr_list[0], 4);
		
		struct sockaddr_in destaddr;	
		memset((void *)&destaddr, 0, sizeof(destaddr));
		destaddr.sin_family = AF_INET;
		destaddr.sin_port = htons(Url->Prot);
		destaddr.sin_addr = ip_addr;
		
		if(0 != connect(Socket,(struct sockaddr*)&destaddr, sizeof(destaddr)))
		{
			sprintf(buf, "连接对方服务器失败。错误代码：%d", GetLastError());
			My_ShowTS(buf);
			closesocket(Socket);
			return FALSE;
		}
		
		//格式化请求，各字段含义参见HTTP协议RFC2616
		char request[1024] = {0};	
		sprintf(request, "HEAD %s HTTP/1.1\r\nHost:%s\r\n\r\n", Url->HostFile, Url->Host);
		//发送请求
		if(SOCKET_ERROR == send(Socket, request, strlen(request), 0))
		{
			sprintf(buf, "发送请求数据包失败。错误代码：%d", GetLastError());
			My_ShowTS(buf);
			closesocket(Socket);
			return FALSE;
		}
		
		//接收数据并存储
		int rcv_bytes = 0;
		
		rcv_bytes = recv(Socket, request, sizeof(request), 0);	
		if (rcv_bytes == SOCKET_ERROR)
		{
			sprintf(buf, "接收请求数据包失败。错误代码：%d", GetLastError());
			My_ShowTS(buf);
			closesocket(Socket);
			return FALSE;
		}


		Tou = strstr(request, "Content-Length: ");
		if (Tou)
		{
			Tou += strlen("Content-Length: ");
			Wei = strstr(Tou, "\r\n");
			memset(buf, 0, sizeof(buf));
			memcpy(buf, Tou, Wei-Tou);
			buf[Wei-Tou] = '\0';
			return atoi(buf);
		}
		return TRUE;

	}
	else
	{
		char request[1024] = {0};	
		sprintf(request, "GET %s HTTP/1.1\r\nHost:%s\r\nRange: bytes=%d-%d\r\n\r\n", Url->HostFile, Url->Host, DataTou, DataWei);
		//发送请求
		if(SOCKET_ERROR == send(Socket, request, strlen(request), 0))
		{
			sprintf(buf, "发送请求数据包失败。错误代码：%d", GetLastError());
			My_ShowTS(buf);
			closesocket(Socket);
			return FALSE;
		}
		
		int rcv_bytes = 0;
		memset(request, 0, sizeof(request));
		rcv_bytes = recv(Socket, request, sizeof(request), 0);	
		if (rcv_bytes == SOCKET_ERROR)
		{
			sprintf(buf, "接收请求数据包失败。错误代码：%d", GetLastError());
			My_ShowTS(buf);
			return FALSE;
		}

		Tou = strstr(request, "\r\n\r\n");
		if (Tou)
		{
			Tou += strlen("\r\n\r\n");
			if (!strlen(Tou))
			{
				memset(request, 0, sizeof(request));
				rcv_bytes = recv(Socket, request, sizeof(request), 0);
				memcpy(Head, request, HeadSize);
			}
			else
			 memcpy(Head, Tou, HeadSize);
			return TRUE;
		}
		else
			return FALSE;	
	}

	return TRUE;
}

DWORD GetFileAllSize()
{
	DWORD Filetmp = 0;
	for (int List_len=0; List_len<LIST_FILE_LEN; List_len++)
	{
		char Tmp[5] = {0};
		strcpy(Tmp, This->m_LIST_FILE.GetItemText(List_len, __LIST_FILE_UNP_SIZE));
		Filetmp += atoi(Tmp);
	}
	return Filetmp;
}
/*
DWORD GetHead(URL_STRUCT *Url, DWORD DataTou, DWORD DataWei, LPVOID Head, DWORD HeadSize, BOOL Dw)
{

	char		lpszHeaders[100]	= {0};
	DWORD		tmeout = 6000;

	DWORD dwFlags = 
		INTERNET_FLAG_EXISTING_CONNECT|INTERNET_FLAG_RAW_DATA|INTERNET_FLAG_RELOAD|        
 INTERNET_FLAG_NO_AUTO_REDIRECT|INTERNET_FLAG_DONT_CACHE|INTERNET_FLAG_PRAGMA_NOCACHE;

Kao:
	if (!Dw)
	{
		if (hNet)
			::InternetCloseHandle(hNet);
		if (hConnect)
			::InternetCloseHandle(hConnect);
		if (hHttpFile)
			::InternetCloseHandle(hHttpFile);

		hNet = ::InternetOpen(NULL, PRE_CONFIG_INTERNET_ACCESS, NULL, INTERNET_INVALID_PORT_NUMBER, 0);
		if(hNet == NULL)
		{
			sprintf(lpszHeaders, "InternetOpen 失败。错误代码：%d", GetLastError());
			My_ShowTS(lpszHeaders);
			return FALSE;
		}
		
		hConnect = ::InternetConnect(hNet, Url->Host, Url->Prot, NULL, NULL,  INTERNET_SERVICE_HTTP, 0, 0);
		if (hConnect == NULL)
		{
			sprintf(lpszHeaders, "与对方Web 服务器建立链接失败。错误代码：%d", GetLastError());
			My_ShowTS(lpszHeaders);	
			return FALSE;	
		}
		
		hHttpFile= HttpOpenRequest(hConnect, NULL, Url->HostFile, NULL, NULL, NULL, dwFlags,  NULL);
		if (hHttpFile == NULL)
		{
			sprintf(lpszHeaders, "初始化 HttpOpenRequest 失败。错误代码：%d", GetLastError());
			My_ShowTS(lpszHeaders);	
			return FALSE;
		}
		
//MessageBox(0, Url->HostFile, Url->Host, 0);
		// 纠错机制
		InternetSetOption(hHttpFile,INTERNET_OPTION_SEND_TIMEOUT, &tmeout, sizeof(DWORD));			// 发送请求的超时时间
		InternetSetOption(hHttpFile,INTERNET_OPTION_CONNECT_TIMEOUT, &tmeout, sizeof(DWORD));		// 网络连接超时
		tmeout = 600;
		InternetSetOption(hHttpFile,INTERNET_OPTION_RECEIVE_TIMEOUT,&tmeout, sizeof(DWORD));		// 接受数据的超时时间
		tmeout = 500;
		InternetSetOption(hHttpFile,INTERNET_OPTION_CONNECT_BACKOFF,&tmeout, sizeof(DWORD));		// 两次重试之间的间隔时间
		tmeout = 3;
		InternetSetOption(hHttpFile,INTERNET_OPTION_CONNECT_RETRIES,&tmeout, sizeof(DWORD));		//超时重试次数，默认值是5

		if (!HttpSendRequest(hHttpFile, NULL, NULL, NULL, NULL))
		{
			sprintf(lpszHeaders, "初始化 HttpSendRequest 发送请求数据包失败。错误代码：%d", GetLastError());
			My_ShowTS(lpszHeaders);	
			return FALSE;
		}
		TCHAR szBuffer[INTERNET_MAX_URL_LENGTH] = {0};
		DWORD dwLen = sizeof(szBuffer);
		// 获取HTTP请求信息（HTTP_QUERY_LOCATION获取的绝对URL在Location应答头）
		if (HttpQueryInfo(hHttpFile, HTTP_QUERY_LOCATION, szBuffer, &dwLen, NULL))			// 有重定向
		{
			strcpy(Url->Url, szBuffer);
			UrlChaiFen(Url);
			My_ShowTS("发生重定向，已经转向真实的下载地址。");	
			This->SetDlgItemText(IDC_EDIT_URL, Url->Url);
			goto Kao;
		}

		DWORD dwByteToRead = 0;//文件大小  
		DWORD dwSizeOfRq = 4;

		if (!HttpQueryInfo(hHttpFile, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER, (LPVOID)&dwByteToRead, &dwSizeOfRq, NULL))
		{
			sprintf(lpszHeaders, "获取压缩包文件大小失败。错误代码：%d", GetLastError());
			My_ShowTS(lpszHeaders);	
			return FALSE;
		}

		if (hHttpFile)
			::InternetCloseHandle(hHttpFile);

		return dwByteToRead ;
	}
	else
	{
		DWORD		dwBytesRead			= DataWei-DataTou;
		sprintf(lpszHeaders, "Range: bytes=%d-%d", DataTou, DataWei);

		hHttpFile = ::HttpOpenRequest(hConnect, "GET", Url->HostFile, HTTP_VERSION, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);
		if (hHttpFile == NULL)
		{
			sprintf(lpszHeaders, "HttpOpenRequest 失败。错误代码：%d", GetLastError());
			My_ShowTS(lpszHeaders);	
			return FALSE;
		}

		
		// 纠错机制
		InternetSetOption(hHttpFile,INTERNET_OPTION_SEND_TIMEOUT, &tmeout, sizeof(DWORD));			// 发送请求的超时时间
		InternetSetOption(hHttpFile,INTERNET_OPTION_CONNECT_TIMEOUT, &tmeout, sizeof(DWORD));		// 网络连接超时
		tmeout = 600;
		InternetSetOption(hHttpFile,INTERNET_OPTION_RECEIVE_TIMEOUT,&tmeout, sizeof(DWORD));		// 接受数据的超时时间
		tmeout = 500;
		InternetSetOption(hHttpFile,INTERNET_OPTION_CONNECT_BACKOFF,&tmeout, sizeof(DWORD));		// 两次重试之间的间隔时间
		tmeout = 3;
		InternetSetOption(hHttpFile,INTERNET_OPTION_CONNECT_RETRIES,&tmeout, sizeof(DWORD));		//超时重试次数，默认值是5


		if (!HttpAddRequestHeaders(hHttpFile, lpszHeaders, strlen(lpszHeaders), HTTP_ADDREQ_FLAG_ADD))
		{
			sprintf(lpszHeaders, "HttpAddRequestHeaders 失败。错误代码：%d", GetLastError());
			My_ShowTS(lpszHeaders);	
			return FALSE;
		}
		
		if (!HttpSendRequest(hHttpFile, NULL, NULL, NULL, NULL))
		{
			sprintf(lpszHeaders, "HttpSendRequest 发送请求数据包失败。。错误代码：%d", GetLastError());
			My_ShowTS(lpszHeaders);	
			return FALSE;
		}
		do 
		{
			DWORD dwQuerRead = 0; 
			::InternetQueryDataAvailable(hHttpFile, &dwQuerRead, 0, 0);
			if (!dwQuerRead)
				break;	
			::InternetReadFile(hHttpFile, Head, HeadSize, &dwBytesRead);	
			
		} while (dwBytesRead!=0);
	}
	return TRUE;
}
*/