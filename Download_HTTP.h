

int GetHttpRequest(char HOST[], char HOST_FILE[], DWORD	DataTou, DWORD DataWei, HEAD_STRUCT *Head)
{
	int			ErrorRetu = 0;
	DWORD		dwBytesRead			= DataWei-DataTou;
	char		lpszHeaders[100]	= {0};
	HINTERNET	hNet				= NULL;
	HINTERNET	hConnect			= NULL;
	HINTERNET   hHttpFile			= NULL;
	
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
		
		hConnect = ::InternetConnect(hNet, HOST, INTERNET_INVALID_PORT_NUMBER, NULL, NULL,  INTERNET_SERVICE_HTTP, 0, 0);
		if (hConnect == NULL)
		{
			ErrorRetu = 2;
			break;
		}
		
		hHttpFile = ::HttpOpenRequest(hConnect, "GET", HOST_FILE, HTTP_VERSION, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);
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
		
		do 
		{
			DWORD dwQuerRead = 0; 
			::InternetQueryDataAvailable(hHttpFile, &dwQuerRead, 0, 0);
			if (!dwQuerRead)
				break;	
			::InternetReadFile(hHttpFile, Head, 7, &dwBytesRead);	
			
		} while (dwBytesRead!=0);
		
	} while (0);
	
	if (hNet)
		::InternetCloseHandle(hNet);
	if (hConnect)
		::InternetCloseHandle(hConnect);
	if (hHttpFile)
		::InternetCloseHandle(hHttpFile);
	
	return TRUE;
	
}

int DownloadHTTP(char HOST[], char HOST_FILE[], DWORD	DataTou, DWORD DataWei, char Buf[])
{
	int			ErrorRetu = 0;
	DWORD		dwBytesRead			= DataWei-DataTou;
	char		lpszHeaders[100]	= {0};
	HINTERNET	hNet				= NULL;
	HINTERNET	hConnect			= NULL;
	HINTERNET   hHttpFile			= NULL;

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

		hConnect = ::InternetConnect(hNet, HOST, INTERNET_INVALID_PORT_NUMBER, NULL, NULL,  INTERNET_SERVICE_HTTP, 0, 0);
		if (hConnect == NULL)
		{
			ErrorRetu = 2;
			break;
		}

		hHttpFile = ::HttpOpenRequest(hConnect, "GET", HOST_FILE, HTTP_VERSION, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);
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

		do 
		{
			DWORD dwQuerRead = 0; 
			::InternetQueryDataAvailable(hHttpFile, &dwQuerRead, 0, 0);
			if (!dwQuerRead)
				break;
			
			char Temp[35];
			
			::InternetReadFile(hHttpFile, Buf, 35, &dwBytesRead);
			
	//		strcpy(Buf, Temp);
	//		Buf[dwBytesRead-1] = '\0';
	


		} while (dwBytesRead!=0);

	} while (0);

	if (hNet)
		::InternetCloseHandle(hNet);
	if (hConnect)
		::InternetCloseHandle(hConnect);
	if (hHttpFile)
		::InternetCloseHandle(hHttpFile);

	return TRUE;

}