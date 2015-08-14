/*
int DownloadDate(URL_STRUCT *Url, DWORD	DataTou, DWORD DataWei, FILE *fp)
{
		char  buf[100] = {0};
	char *Tou;
	char *Wei;
	

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
		while(rcv_bytes)
		{
				
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
					fwrite(request, rcv_bytes,1,fp);
					memset(request, 0, sizeof(request));
				}
				else
				{
					fwrite(Tou, rcv_bytes,1,fp);
					memset(request, 0, sizeof(request));
				}
			}
			else
			{
				fwrite(request, rcv_bytes,1,fp);
				memset(request, 0, sizeof(request));
			}
			rcv_bytes = recv(Socket, request, sizeof(request), 0);
		}

	

	return TRUE;
}*/
/*	获取指定数据	*/

int DownloadDate(URL_STRUCT *Url, DWORD	DataTou, DWORD DataWei, FILE *fp)
{
	int			ErrorRetu = 0;
	DWORD		dwBytesRead			= DataWei-DataTou;
	char		lpszHeaders[100]	= {0};
	HINTERNET	hNet				= NULL;
	HINTERNET	hConnect			= NULL;
	HINTERNET   hHttpFile			= NULL;
	char Date[100] = {0};

	sprintf(lpszHeaders, "Range: bytes=%d-%d", DataTou, DataWei);
	DWORD dwHeadersLength = strlen(lpszHeaders);	

	do 
	{	
		hNet = ::InternetOpen(NULL, PRE_CONFIG_INTERNET_ACCESS, NULL, INTERNET_INVALID_PORT_NUMBER, 0);
		if(hNet == NULL)
		{
			ErrorRetu = 1;
			break;
		}

		hConnect = ::InternetConnect(hNet, Url->Host, Url->Prot, NULL, NULL,  INTERNET_SERVICE_HTTP, 0, 0);
		if (hConnect == NULL)
		{
			ErrorRetu = 2;
			break;
		}
		
		hHttpFile = ::HttpOpenRequest(hConnect, "GET", Url->HostFile, HTTP_VERSION, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);
		if (hHttpFile == NULL)
		{
			ErrorRetu = 3;
			break;
		}
		
		if (!HttpAddRequestHeaders(hHttpFile, lpszHeaders, dwHeadersLength, HTTP_ADDREQ_FLAG_ADD))
		{
			ErrorRetu = 4;
			break;
		}
		
		if (!HttpSendRequest(hHttpFile, NULL, NULL, NULL, NULL))
		{
			int err = GetLastError();
			return 5;
		}		
		
		DWORD dwQuerRead = 0; 
		::InternetQueryDataAvailable(hHttpFile, &dwQuerRead, 0, 0);
		if (!dwQuerRead)
				break;

		This->m_PROGRESS_DOWNLOADFILE.SetPos(0);

		DWORD Size = 0;
		DWORD Tl = dwBytesRead;
		do 
		{	
			::InternetReadFile(hHttpFile, Date, sizeof(Date), &dwBytesRead);	
			fwrite(Date, dwBytesRead,1,fp);
			memset(Date, 0, sizeof(Date));
			This->m_PROGRESS_DOWNLOADFILE.SetRange32(0,  Tl);	// 设置进度条
			Size += dwBytesRead;
			This->m_PROGRESS_DOWNLOADFILE.SetPos(Size);				

			::InternetQueryDataAvailable(hHttpFile, &dwQuerRead, 0, 0);
			if (!dwQuerRead)
				break;	
	
		} while (1);
		
	} while (0);
	if (hNet)
		::InternetCloseHandle(hNet);
	if (hConnect)
		::InternetCloseHandle(hConnect);
	if (hHttpFile)
		::InternetCloseHandle(hHttpFile);
	
	return TRUE;
	
}
