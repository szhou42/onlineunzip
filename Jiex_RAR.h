//int RarRead(RarStruct->Url_STRUCT *RarStruct->Url, HEAD_STRUCT *Head, MAIN_HEAD *RarStruct->MainHead, FILE_HEAD *FileHead, FILE_DATE *FileDate)
DWORD WINAPI Rar_ThreadProc( LPVOID lpParam )
{

	char TMP[300] = {0};
	RAR_STRUCT *RarStruct = (RAR_STRUCT*)lpParam; 
	DWORD File_P = 7;
	DWORD RarSize = 0;

	strcpy(RarStruct->FileDate.PassWord, "否");
	My_ShowTS("正在获取文件大小。");
	RarSize = GetHead(&RarStruct->Url, NULL, NULL, NULL, NULL, 0); // 初始化并得到文件的总大小
	if (!RarSize)
	{	
		My_ShowTS("压缩包文件大小为0 或 与对方HTTP服务器交互失败。");	
		Ting = TRUE;
		goto Exit;
	}

	sprintf(TMP, "获取该文件大小为： %d 字节。", RarSize);
	My_ShowTS(TMP);

	My_ShowTS("正在分析该文件。。。");
	// 获取标记头
	if (!GetHead(&RarStruct->Url, 0, File_P-1, &RarStruct->Head, sizeof(HEAD_STRUCT), 1))
	{
		My_ShowTS("无法获取标记头，与对方HTTP服务器交互失败。");
		Ting = TRUE;
		goto Exit;
	}

	if(RarStruct->Head.HEAD_CRC != 0x6152 || RarStruct->Head.HEAD_TYPE != 0x72 || RarStruct->Head.HEAD_FLAGS != 0x1A21 || RarStruct->Head.HEAD_SIZE != 0x0007)
	{
		My_ShowTS("该文件不是RAR文件。");
		Ting = TRUE;
		goto Exit;
	}
	// 获取压缩头
	if (!GetHead(&RarStruct->Url, File_P, File_P+7, &RarStruct->MainHead, sizeof(MAIN_HEAD), 1))
	{
		My_ShowTS("无法获取压缩头，与对方HTTP服务器交互失败。");
		Ting = TRUE;
		goto Exit;
	}

	if ((RarStruct->MainHead.HEAD_FLAGS & 0x0080)== 0x0080)		
	{	
		My_ShowTS("该RAR文件中的所有文件名被加密。无法直接得到文件名。");
		Ting = TRUE;
		goto Exit;
	}

	RarStruct->FileDate.FileOffSetTou = File_P  + RarStruct->MainHead.HEAD_SIZE ;

	This->m_PROGRESS_FILEDATE.SetPos(0);
	This->m_PROGRESS_FILEDATE.SetRange32(0,  RarSize);	// 设置进度条
	This->m_PROGRESS_FILEDATE.SetPos(0);

	This->m_PROGRESS_FILEDATE.SetPos(RarStruct->FileDate.FileOffSetTou);

	while (1)
	{

		memset(&RarStruct->Head, 0, sizeof(HEAD_STRUCT));
		memset(&RarStruct->MainHead, 0, sizeof(MAIN_HEAD));
		memset(&RarStruct->FileHead, 0, sizeof(FILE_HEAD));

		// 读取前七个字节
		if(!GetHead(&RarStruct->Url, RarStruct->FileDate.FileOffSetTou, RarStruct->FileDate.FileOffSetTou+7, &RarStruct->Head, sizeof(HEAD_STRUCT), 1))
		{
	//		My_ShowTS("无法获取前7个字节，与对方HTTP服务器交互失败。正在重试。。。");
			GetHead(&RarStruct->Url, NULL, NULL, NULL, NULL, 0);
			if(!GetHead(&RarStruct->Url, RarStruct->FileDate.FileOffSetTou, RarStruct->FileDate.FileOffSetTou+7, &RarStruct->Head, sizeof(HEAD_STRUCT), 1))
			{
				My_ShowTS("无法获取前7个字节，与对方HTTP服务器交互失败。重试失败");
				goto Exit;
			}
		//	My_ShowTS("重试成功。");
		}
		switch (RarStruct->Head.HEAD_TYPE)
		{/*
			case 0x73:							// 压缩文件头
				
				break;*/
				
			case 0x74:							// 文件头
				{
					RarStruct->FileDate.FileOffSetWei = RarStruct->FileDate.FileOffSetTou+RarStruct->Head.HEAD_SIZE-1;
					if (!GetHead(&RarStruct->Url, RarStruct->FileDate.FileOffSetTou, RarStruct->FileDate.FileOffSetWei, &RarStruct->FileHead, sizeof(FILE_HEAD), 1))
					{
					
				//		My_ShowTS("无法获取该文件头，与对方HTTP服务器交互失败。正在重试。。。");
						GetHead(&RarStruct->Url, NULL, NULL, NULL, NULL, 0);
						if (!GetHead(&RarStruct->Url, RarStruct->FileDate.FileOffSetTou, RarStruct->FileDate.FileOffSetWei, &RarStruct->FileHead, sizeof(FILE_HEAD), 1))
						{
							My_ShowTS("无法获取该文件头，与对方HTTP服务器交互失败。重试失败");
							goto Exit;
						}
				//		My_ShowTS("重试成功。");
					}
					// 如果发现是文件夹则跳过
					if ((RarStruct->FileHead.HEAD_FLAGS & 0x00E0)== 0x00E0)
					{
						RarStruct->FileDate.FileOffSetTou += RarStruct->Head.HEAD_SIZE;
						continue;
					}
			
					if ((RarStruct->FileHead.HEAD_FLAGS & 0x04)== 0x04)		// 文件被加密
						strcpy(RarStruct->FileDate.PassWord, "是");
					
					Show_MSG(RarStruct->FileHead.FILE_NAME, RarStruct->FileHead.UNP_SIZE, RarStruct->FileHead.PACK_SIZE, RarStruct->FileDate.PassWord, RarStruct->FileDate.FileOffSetTou, RarStruct->FileDate.FileOffSetWei + RarStruct->FileHead.PACK_SIZE);
					RarStruct->FileDate.FileOffSetTou = RarStruct->FileDate.FileOffSetWei + RarStruct->FileHead.PACK_SIZE + 1;
				}
				break;
		/*		
			case 0x75:							// 旧风格的注释头
				
				break;
				
			case 0x76:							// 旧风格的用户身份信息头
				
				break;
				
			case 0x77:							// 旧风格的子块头
				
				break;
				
			case 0x78:							// 旧风格的恢复记录头
				
				break;
				
			case 0x79:							// 用户身份信息头
				
				break;
				
			case 0x7A:							// 注释头
				
				break;
				*/
			case 0x7B:							// 结尾头
				//	Show_MSG("【下载整个文件】", GetFileAllSize(), RarSize, RarStruct->FileDate.PassWord, 0,  0);

					goto Exit;
				break;

			default:
				{
					RarStruct->FileDate.FileOffSetWei = RarStruct->FileDate.FileOffSetTou+RarStruct->Head.HEAD_SIZE-1;
					if (!GetHead(&RarStruct->Url, RarStruct->FileDate.FileOffSetTou, RarStruct->FileDate.FileOffSetWei, &RarStruct->FileHead, sizeof(FILE_HEAD), 1))
					{
						
						//		My_ShowTS("无法获取该文件头，与对方HTTP服务器交互失败。正在重试。。。");
						GetHead(&RarStruct->Url, NULL, NULL, NULL, NULL, 0);
						if (!GetHead(&RarStruct->Url, RarStruct->FileDate.FileOffSetTou, RarStruct->FileDate.FileOffSetWei, &RarStruct->FileHead, sizeof(FILE_HEAD), 1))
						{
							My_ShowTS("无法获取该文件头，与对方HTTP服务器交互失败。重试失败");
							goto Exit;
						}
						//		My_ShowTS("重试成功。");
					}
					RarStruct->FileDate.FileOffSetTou = RarStruct->FileDate.FileOffSetWei + RarStruct->FileHead.PACK_SIZE + 1;
				}
		}
		This->m_PROGRESS_FILEDATE.SetPos(RarStruct->FileDate.FileOffSetTou+7) ;
	}
	
Exit:
	{
		Ting = TRUE;
	}
	
	return 1;
}
