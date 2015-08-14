

// URL�ṹ
struct URL_STRUCT
{
	IN	char	Url[1024];
	OUT	char	XieYi[10];
	OUT	char	Host[1024];
	OUT	char	HostFile[1024];
	OUT	char	FileType[5];
	OUT int		Prot;
};

// �ļ��ṹ
struct FILE_DATE
{
	char FileName[MAX_PATH];
	DWORD FileOffSetTou ;		// �ļ�������ʼλ��
	DWORD FileOffSetWei ;		// �ļ����ݽ���λ��
	DWORD FileLength;			// �ļ��ܳ���
	char PassWord[2];
	
};
/************************************************************************/
/* RAR�ṹ                                                              */
/************************************************************************/


// ���ǽṹ
struct HEAD_STRUCT
{
	short	HEAD_CRC;			// 2�ֽ� ͷCRCУ��ֵ
	char	HEAD_TYPE;			// 1�ֽ� ͷ���ͣ�
	short	HEAD_FLAGS;			// 2�ֽ� λ���
	short	HEAD_SIZE;			// 2�ֽ� ͷ�ܴ�С		
};

// ѹ���ļ�ͷ�ṹ
struct MAIN_HEAD
{
	short	HEAD_CRC;			// 2�ֽ� ѹ���ļ�ͷCRCУ��ֵ
	char	HEAD_TYPE;			// 1�ֽ� ͷ���ͣ�0x73
	short	HEAD_FLAGS;			// 2�ֽ� λ���
	short	HEAD_SIZE;			// 2�ֽ� ѹ���ļ�ͷ�ܴ�С(����ѹ���ļ�ע��)
	short	RESERVED1;			// 2�ֽ� ����
	int		RESERVED2;			// 4�ֽ� ����
};

// �ļ�ͷ�ṹ
struct FILE_HEAD
{
	short	HEAD_CRC;			// 2�ֽ� �ļ�ͷCRCУ��ֵ
	char	HEAD_TYPE;			// 1�ֽ� ͷ���ͣ�0x74
	short	HEAD_FLAGS;			// 2�ֽ� λ���
	short	HEAD_SIZE;			// 2�ֽ� �ļ�ͷ��ȫ����С(�����ļ�����ע��)
	int		PACK_SIZE;			// 4�ֽ� �ļ�ѹ����Ĵ�С
	int		UNP_SIZE;			// 4�ֽ� �ļ�ѹ��ǰ�Ĵ�С
	char	HOST_OS;			// 1�ֽ� ����ѹ���ļ�ʹ�õĲ���ϵͳ
	int		FILE_CRC;			// 4�ֽ� �ļ���CRCУ��ֵ
	int		FTIME;				// 4�ֽ� MS DOS��׼��ʽ�����ں�ʱ��
	char	UNP_VER;			// 1�ֽ� ��ѹ�ļ�����Ҫ��� RAR �汾
	char	METHOD;				// 1�ֽ� ѹ����ʽ
	short	NAME_SIZE;			// 1�ֽ� �ļ�����С
	int		ATTR;				// 4�ֽ� �ļ�����
//	int		HIGH_PACK_SIZE;		// 4�ֽ� ѹ���ļ���Ĵ�С 64λֵ�ĸ�4�ֽ�	ֻ����HEAD_FLAGS�е�0x100λ�����òŴ���
//	int		HIGH_UNP_SIZE;		// 4�ֽ� ѹ���ļ�ǰ�Ĵ�С 64λֵ�ĸ�4�ֽ�	ֻ����HEAD_FLAGS�е�0x100λ�����òŴ���
	char	FILE_NAME[MAX_PATH*2];	// �ļ���
//	double	SALT;
};

// �ļ�ͷ�ṹ1
struct FILE_HEAD_1
{
	short	HEAD_CRC;				// 2�ֽ� �ļ�ͷCRCУ��ֵ
	char	HEAD_TYPE;				// 1�ֽ� ͷ���ͣ�0x74
	short	HEAD_FLAGS;				// 2�ֽ� λ���
	short	HEAD_SIZE;				// 2�ֽ� �ļ�ͷ��ȫ����С(�����ļ�����ע��)
	int		PACK_SIZE;				// 4�ֽ� �ļ�ѹ����Ĵ�С
	int		UNP_SIZE;				// 4�ֽ� �ļ�ѹ��ǰ�Ĵ�С
	char	HOST_OS;				// 1�ֽ� ����ѹ���ļ�ʹ�õĲ���ϵͳ
	int		FILE_CRC;				// 4�ֽ� �ļ���CRCУ��ֵ
	int		FTIME;					// 4�ֽ� MS DOS��׼��ʽ�����ں�ʱ��
	char	UNP_VER;				// 1�ֽ� ��ѹ�ļ�����Ҫ��� RAR �汾
	char	METHOD;					// 1�ֽ� ѹ����ʽ
	short	NAME_SIZE;				// 1�ֽ� �ļ�����С
	int		ATTR;					// 4�ֽ� �ļ�����
	int		HIGH_PACK_SIZE;			// 4�ֽ� ѹ���ļ���Ĵ�С 64λֵ�ĸ�4�ֽ�	ֻ����HEAD_FLAGS�е�0x100λ�����òŴ���
	int		HIGH_UNP_SIZE;			// 4�ֽ� ѹ���ļ�ǰ�Ĵ�С 64λֵ�ĸ�4�ֽ�	ֻ����HEAD_FLAGS�е�0x100λ�����òŴ���
	char	FILE_NAME[MAX_PATH*2];	// �ļ���
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
/* ZIP �ṹ                                                             */
/************************************************************************/
struct ZIP_HEADER
{
	DWORD Signature;											//��־"PK..":0x04034b50 4
	WORD  VersionToExtract;										//��ѹ�汾 2
	WORD  BitFlag;												//ͨ�ñ�־λ 2
	WORD  CompressionMethod;									//ѹ����ʽ 2
	WORD  LastModifyTime;										//����޸�ʱ�� 2
	WORD  LastModifyDate;										//����޸����� 2
	DWORD CRC32;												//CRC32ֵ 4
	DWORD CompressedSize;										//ѹ�����С 4 
	DWORD UncompressedSize;										//ѹ��ǰ��С 4
	WORD SizeOfFileName;										//�ļ�����С 2
	WORD SizeOfExtraField;										//��չ���С 2
	char  *FileName;									    	//�ļ���  260
	char  ExtraField[MAX_PATH*2];								//��չ��  260*2	
};

struct ZIP_DESCRIPTION
{
	DWORD Signature;											//��־"PK..":0x02014b50
	WORD  VersionToMake;										//ѹ���汾
	WORD  VersionToExtract;										//��ѹ�汾
	WORD  BitFlag;												//ͨ�ñ�־λ
	WORD  CompressionMethod;									//ѹ����ʽ
	WORD  LastModifyTime;										//����޸�ʱ��
	WORD  LastModifyDate;										//����޸�����
	DWORD CRC32;												//CRC32ֵ
	DWORD CompressedSize;										//ѹ�����С
	DWORD UncompressedSize;										//ѹ��ǰ��С
	WORD  SizeOfFileName;										//�ļ�����С
	WORD  SizeOfExtraField;										//��չ���С
	WORD  SizeOfComment;										//ע�ʹ�С
	WORD  DiskOffset;											//�ļ���ʼλ�õĴ��̱��
	WORD  InFileAttr;											//�ļ��ڲ�����
	DWORD ExFileAttr;											//�ļ��ⲿ����
	DWORD reOffset;												//�����ļ�header�����λ��
	char  *FileName;											//�ļ���
	char  *ExtraField;											//��չ��
	char  *Comment;												//ע��
};

struct ZIP_FINISH
{
	DWORD Signature;											//��־"PK..":0x02014b50
	WORD  NumOfDisk;											//��ǰ���̱��
	WORD  DiskOffset;											//����Ŀ¼��ʼλ�õĴ��̱��
	WORD  NumOfDire;											//�ô���������¼�ĺ���Ŀ¼����		
	WORD  NumOfAllDire;											//����Ŀ¼�ṹ����
	DWORD SizeOfCenDire;										//����Ŀ¼�Ĵ�С
	DWORD reOffset;												//����Ŀ¼��ʼλ�������archive��ʼ��λ��
	WORD  SizeOfComment;										//ע�ʹ�С
	char  *Comment;												//ע��
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
/* �Զ���                                                               */
/************************************************************************/

HINTERNET	hNet				= NULL;
HINTERNET	hConnect			= NULL;
HINTERNET   hHttpFile			= NULL;

SOCKET Socket;

/****************** Socket ��ʼ�� ******************/
int SocketChuShiHua() 
{
	WSADATA wsaData;
	
	if (WSAStartup(MAKEWORD(2,2),&wsaData))
		return 1;			// �޷���ʼ���׽��ֿ�
	
	if (HIBYTE(wsaData.wVersion)!=2 ||	LOBYTE(wsaData.wVersion)!=2)
	{
		WSACleanup();	
		return 1;			// �׽��ְ汾������2.2
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
/* �ֽ�URL ���Ϸ��򷵻� TRUE                                           */
/************************************************************************/
BOOL UrlChaiFen(IN URL_STRUCT *UrlStruct)
{	

	char *Tmp = new char[1024];
	memset(Tmp, 0, sizeof(Tmp));
	char *Tou		= NULL;
	char *Wei		= NULL;

	// �����Ѹ�����������
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
		
		sprintf(Tmp, "�ɹ�����Ѹ�����ص�ַ��%s", URL);
		My_ShowTS(Tmp);
	}

	// ����ǿ쳵���������
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
		
		sprintf(Tmp, "�ɹ������쳵���ص�ַ��%s", URL);
		My_ShowTS(Tmp);
	}

	// �����QQ�������������
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
		sprintf(Tmp, "�ɹ�����QQ�������ص�ַ��%s", URL);
		My_ShowTS(Tmp);
	}
	This->SetDlgItemText(IDC_EDIT_URL, UrlStruct->Url);
	Tou	= strstr(UrlStruct->Url, "//");					// ��ȡЭ��ͷ
	if (Tou)
	{
		Tou += strlen("//");
		memcpy(UrlStruct->XieYi, UrlStruct->Url, Tou - UrlStruct->Url);
		UrlStruct->XieYi[Tou-UrlStruct->Url] = '\0';
	}
	else										
	{	
		strcpy(UrlStruct->XieYi, "http://");				// ���û��Э��ͷ��Ĭ��ΪhttpЭ��
		Tou = UrlStruct->Url;
	}
	
	Wei = strstr(Tou, ":");									// �˿ڷ���
	if (Wei)
	{
		Wei ++;
		char Tmp[10] = {0};
		memcpy(Tmp, Wei, strstr(Tou, "/") - Wei);
		UrlStruct->Prot = atoi(Tmp);
	}
	else
		UrlStruct->Prot = 80;

	Wei = strstr(Tou, "/");						// ��ȡ�������ļ���
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
		return TRUE;							// û���ļ���

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
			My_ShowTS("�������Ϸ���");
			return TRUE;
		}
		SOCKET sock = socket(PF_INET, SOCK_STREAM, 0);
		if(sock == INVALID_SOCKET)
		{
			sprintf(buf, "�����׽���ʧ�ܡ�������룺%d", GetLastError());
			My_ShowTS(buf);
			return TRUE;
		}

		hostent* pHostEnt = gethostbyname(Url->Host);
		if(pHostEnt == NULL)
		{
			sprintf(buf, "��������ʧ�ܡ�������룺%d", GetLastError());
			My_ShowTS(buf);
			return TRUE;
		}
		
		int nTime = 10000;
		setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&nTime, sizeof(nTime));
		setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&nTime, sizeof(nTime));
			
		//����
		struct in_addr ip_addr;
		memcpy(&ip_addr, pHostEnt->h_addr_list[0], 4);
		
		struct sockaddr_in destaddr;
		memset((void *)&destaddr, 0, sizeof(destaddr));
		destaddr.sin_family = AF_INET;
		destaddr.sin_port = htons(Url->Prot);
		destaddr.sin_addr = ip_addr;
		
		if(0 != connect(sock,(struct sockaddr*)&destaddr, sizeof(destaddr)))
		{
			sprintf(buf, "���ӶԷ�������ʧ�ܡ�������룺%d", GetLastError());
			My_ShowTS(buf);
			closesocket(sock);
			return TRUE;
		}
		
		//��ʽ�����󣬸��ֶκ���μ�HTTPЭ��RFC2616
		char request[1024] = {0};	
		sprintf(request, "HEAD %s HTTP/1.1\r\nHost:%s\r\n\r\n", Url->HostFile, Url->Host);
		//��������
		if(SOCKET_ERROR == send(sock, request, strlen(request), 0))
		{
			sprintf(buf, "�����������ݰ�ʧ�ܡ�������룺%d", GetLastError());
			My_ShowTS(buf);
			closesocket(sock);
			return TRUE;
		}
		
		//�������ݲ��洢
		int rcv_bytes = 0;
		
		rcv_bytes = recv(sock, buf, sizeof(buf), 0);
		

		if (rcv_bytes == SOCKET_ERROR)
		{
			sprintf(buf, "�����������ݰ�ʧ�ܡ�������룺%d", GetLastError());
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
			sprintf(Tmp, "URL ���ض���URL��%s", Url->Url);
			This->SetDlgItemText(IDC_EDIT_URL, Url->Url);
			My_ShowTS(Tmp);
			continue;
		}

		break;	
	}


  //  WSACleanup();
	return TRUE;
}

//����

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
			sprintf(buf, "�����׽���ʧ�ܡ�������룺%d", GetLastError());
			My_ShowTS(buf);
			return FALSE;
		}
		
		hostent* pHostEnt = gethostbyname(Url->Host);
		if(pHostEnt == NULL)
		{
			sprintf(buf, "��������ʧ�ܡ�������룺%d", GetLastError());
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
			sprintf(buf, "���ӶԷ�������ʧ�ܡ�������룺%d", GetLastError());
			My_ShowTS(buf);
			closesocket(Socket);
			return FALSE;
		}
		
		//��ʽ�����󣬸��ֶκ���μ�HTTPЭ��RFC2616
		char request[1024] = {0};	
		sprintf(request, "HEAD %s HTTP/1.1\r\nHost:%s\r\n\r\n", Url->HostFile, Url->Host);
		//��������
		if(SOCKET_ERROR == send(Socket, request, strlen(request), 0))
		{
			sprintf(buf, "�����������ݰ�ʧ�ܡ�������룺%d", GetLastError());
			My_ShowTS(buf);
			closesocket(Socket);
			return FALSE;
		}
		
		//�������ݲ��洢
		int rcv_bytes = 0;
		
		rcv_bytes = recv(Socket, request, sizeof(request), 0);	
		if (rcv_bytes == SOCKET_ERROR)
		{
			sprintf(buf, "�����������ݰ�ʧ�ܡ�������룺%d", GetLastError());
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
		//��������
		if(SOCKET_ERROR == send(Socket, request, strlen(request), 0))
		{
			sprintf(buf, "�����������ݰ�ʧ�ܡ�������룺%d", GetLastError());
			My_ShowTS(buf);
			closesocket(Socket);
			return FALSE;
		}
		
		int rcv_bytes = 0;
		memset(request, 0, sizeof(request));
		rcv_bytes = recv(Socket, request, sizeof(request), 0);	
		if (rcv_bytes == SOCKET_ERROR)
		{
			sprintf(buf, "�����������ݰ�ʧ�ܡ�������룺%d", GetLastError());
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
			sprintf(lpszHeaders, "InternetOpen ʧ�ܡ�������룺%d", GetLastError());
			My_ShowTS(lpszHeaders);
			return FALSE;
		}
		
		hConnect = ::InternetConnect(hNet, Url->Host, Url->Prot, NULL, NULL,  INTERNET_SERVICE_HTTP, 0, 0);
		if (hConnect == NULL)
		{
			sprintf(lpszHeaders, "��Է�Web ��������������ʧ�ܡ�������룺%d", GetLastError());
			My_ShowTS(lpszHeaders);	
			return FALSE;	
		}
		
		hHttpFile= HttpOpenRequest(hConnect, NULL, Url->HostFile, NULL, NULL, NULL, dwFlags,  NULL);
		if (hHttpFile == NULL)
		{
			sprintf(lpszHeaders, "��ʼ�� HttpOpenRequest ʧ�ܡ�������룺%d", GetLastError());
			My_ShowTS(lpszHeaders);	
			return FALSE;
		}
		
//MessageBox(0, Url->HostFile, Url->Host, 0);
		// �������
		InternetSetOption(hHttpFile,INTERNET_OPTION_SEND_TIMEOUT, &tmeout, sizeof(DWORD));			// ��������ĳ�ʱʱ��
		InternetSetOption(hHttpFile,INTERNET_OPTION_CONNECT_TIMEOUT, &tmeout, sizeof(DWORD));		// �������ӳ�ʱ
		tmeout = 600;
		InternetSetOption(hHttpFile,INTERNET_OPTION_RECEIVE_TIMEOUT,&tmeout, sizeof(DWORD));		// �������ݵĳ�ʱʱ��
		tmeout = 500;
		InternetSetOption(hHttpFile,INTERNET_OPTION_CONNECT_BACKOFF,&tmeout, sizeof(DWORD));		// ��������֮��ļ��ʱ��
		tmeout = 3;
		InternetSetOption(hHttpFile,INTERNET_OPTION_CONNECT_RETRIES,&tmeout, sizeof(DWORD));		//��ʱ���Դ�����Ĭ��ֵ��5

		if (!HttpSendRequest(hHttpFile, NULL, NULL, NULL, NULL))
		{
			sprintf(lpszHeaders, "��ʼ�� HttpSendRequest �����������ݰ�ʧ�ܡ�������룺%d", GetLastError());
			My_ShowTS(lpszHeaders);	
			return FALSE;
		}
		TCHAR szBuffer[INTERNET_MAX_URL_LENGTH] = {0};
		DWORD dwLen = sizeof(szBuffer);
		// ��ȡHTTP������Ϣ��HTTP_QUERY_LOCATION��ȡ�ľ���URL��LocationӦ��ͷ��
		if (HttpQueryInfo(hHttpFile, HTTP_QUERY_LOCATION, szBuffer, &dwLen, NULL))			// ���ض���
		{
			strcpy(Url->Url, szBuffer);
			UrlChaiFen(Url);
			My_ShowTS("�����ض����Ѿ�ת����ʵ�����ص�ַ��");	
			This->SetDlgItemText(IDC_EDIT_URL, Url->Url);
			goto Kao;
		}

		DWORD dwByteToRead = 0;//�ļ���С  
		DWORD dwSizeOfRq = 4;

		if (!HttpQueryInfo(hHttpFile, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER, (LPVOID)&dwByteToRead, &dwSizeOfRq, NULL))
		{
			sprintf(lpszHeaders, "��ȡѹ�����ļ���Сʧ�ܡ�������룺%d", GetLastError());
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
			sprintf(lpszHeaders, "HttpOpenRequest ʧ�ܡ�������룺%d", GetLastError());
			My_ShowTS(lpszHeaders);	
			return FALSE;
		}

		
		// �������
		InternetSetOption(hHttpFile,INTERNET_OPTION_SEND_TIMEOUT, &tmeout, sizeof(DWORD));			// ��������ĳ�ʱʱ��
		InternetSetOption(hHttpFile,INTERNET_OPTION_CONNECT_TIMEOUT, &tmeout, sizeof(DWORD));		// �������ӳ�ʱ
		tmeout = 600;
		InternetSetOption(hHttpFile,INTERNET_OPTION_RECEIVE_TIMEOUT,&tmeout, sizeof(DWORD));		// �������ݵĳ�ʱʱ��
		tmeout = 500;
		InternetSetOption(hHttpFile,INTERNET_OPTION_CONNECT_BACKOFF,&tmeout, sizeof(DWORD));		// ��������֮��ļ��ʱ��
		tmeout = 3;
		InternetSetOption(hHttpFile,INTERNET_OPTION_CONNECT_RETRIES,&tmeout, sizeof(DWORD));		//��ʱ���Դ�����Ĭ��ֵ��5


		if (!HttpAddRequestHeaders(hHttpFile, lpszHeaders, strlen(lpszHeaders), HTTP_ADDREQ_FLAG_ADD))
		{
			sprintf(lpszHeaders, "HttpAddRequestHeaders ʧ�ܡ�������룺%d", GetLastError());
			My_ShowTS(lpszHeaders);	
			return FALSE;
		}
		
		if (!HttpSendRequest(hHttpFile, NULL, NULL, NULL, NULL))
		{
			sprintf(lpszHeaders, "HttpSendRequest �����������ݰ�ʧ�ܡ���������룺%d", GetLastError());
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