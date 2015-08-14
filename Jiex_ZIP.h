DWORD WINAPI Zip_ThreadProc( LPVOID lpParam )
{

	char TMP[300] = {0};
	ZIP_STRUCT *ZipStruct = (ZIP_STRUCT*)lpParam; 
	DWORD File_P = 30;
	DWORD ZipSize = 0;
	DWORD Filetmp = 0;

	DWORD List_len = 0;
	strcpy(ZipStruct->FileDate.PassWord, "否");

	
	My_ShowTS("正在获取文件大小。");
	ZipSize = GetHead(&ZipStruct->Url, NULL, NULL, NULL, NULL, 0); // 初始化并得到文件的总大小
	if (!ZipSize)
	{	
		My_ShowTS("压缩包文件大小为0 或 与对方HTTP服务器交互失败。");	
		Ting = TRUE;
		goto Exit;
	}

	sprintf(TMP, "获取该文件大小为： %d 字节。", ZipSize);
	My_ShowTS(TMP);

	My_ShowTS("正在分析该文件。。。");
	
	ZipStruct->FileDate.FileOffSetWei = 0;

	// 分析 ZIP_HEADER  结构
	while(1)
	{     
		ZipStruct->FileDate.FileOffSetTou = ZipStruct->FileDate.FileOffSetWei;
		// 获取标记头
		if (!GetHead(&ZipStruct->Url, ZipStruct->FileDate.FileOffSetTou, ZipStruct->FileDate.FileOffSetTou+File_P-1, &ZipStruct->ZipHeader, 30, 1))
		{
			My_ShowTS("无法获取标记头，与对方HTTP服务器交互失败。");
			Ting = TRUE;
			goto Exit;
		}
		
		// 如果不是文件标记
		if (ZipStruct->ZipHeader.Signature != 0x04034b50)
			break;
		
		ZipStruct->FileDate.FileOffSetWei = ZipStruct->FileDate.FileOffSetTou+File_P+ZipStruct->ZipHeader.SizeOfFileName+ZipStruct->ZipHeader.SizeOfExtraField;
		ZipStruct->ZipHeader.FileName = new char[ZipStruct->ZipHeader.SizeOfFileName+1];
		memset(ZipStruct->ZipHeader.FileName, 0, ZipStruct->ZipHeader.SizeOfFileName+1);
		
		// 读取文件名
		if (!GetHead(&ZipStruct->Url, ZipStruct->FileDate.FileOffSetTou+File_P, ZipStruct->FileDate.FileOffSetTou+File_P+ZipStruct->ZipHeader.SizeOfFileName, ZipStruct->ZipHeader.FileName, ZipStruct->ZipHeader.SizeOfFileName, 1))
		{
			My_ShowTS("无法获取标记头，与对方HTTP服务器交互失败。");
			Ting = TRUE;
			goto Exit;
		}

		if (!strstr(ZipStruct->ZipHeader.FileName, "/"))
			ZipStruct->FileDate.FileOffSetWei += ZipStruct->ZipHeader.CompressedSize;
		

		// 如果被加密
		if (ZipStruct->ZipHeader.Signature == 0x08074B50)
		{
			strcpy(ZipStruct->FileDate.PassWord, "是");
			ZipStruct->FileDate.FileOffSetWei += 16;
		}
		Show_MSG(ZipStruct->ZipHeader.FileName, ZipStruct->ZipHeader.UncompressedSize, ZipStruct->ZipHeader.CompressedSize, ZipStruct->FileDate.PassWord,ZipStruct->FileDate.FileOffSetTou, ZipStruct->FileDate.FileOffSetWei);
		

		if (ZipStruct->ZipHeader.FileName)
			delete []ZipStruct->ZipHeader.FileName;
	}
	
	// 分析 ZIP_DESCRIPTION 结构
	
	while (1)
	{	
		File_P = 46;
	
		ZipStruct->FileDate.FileOffSetTou = ZipStruct->FileDate.FileOffSetWei;
		Filetmp = ZipStruct->FileDate.FileOffSetTou; 
		ZipStruct->FileDate.FileOffSetTou = ZipStruct->FileDate.FileOffSetWei;
		ZipStruct->ZipDescription.FileName = NULL;
		ZipStruct->ZipDescription.ExtraField = NULL;
		ZipStruct->ZipDescription.Comment = NULL;

		// 获取 ZIP_DESCRIPTION 标记头
		if (!GetHead(&ZipStruct->Url, ZipStruct->FileDate.FileOffSetTou, ZipStruct->FileDate.FileOffSetTou+File_P-1, &ZipStruct->ZipDescription, File_P, 1))
		{
			My_ShowTS("无法获取 ZIP_DESCRIPTION 标记头，与对方HTTP服务器交互失败。");
			Ting = TRUE;
			goto Exit;
		}

		if (ZipStruct->ZipDescription.Signature != 0x02014b50)
			break;
		
		ZipStruct->ZipDescription.FileName = new char[ZipStruct->ZipDescription.SizeOfFileName+1];
		memset(ZipStruct->ZipDescription.FileName, 0, ZipStruct->ZipDescription.SizeOfFileName+1);
		Filetmp+=File_P;
		
		// 读取名字
		if (!GetHead(&ZipStruct->Url, Filetmp, Filetmp+ZipStruct->ZipDescription.SizeOfFileName, ZipStruct->ZipDescription.FileName, ZipStruct->ZipDescription.SizeOfFileName, 1))
		{
		}
		
		// 如果有扩展域 则 读取扩展域
		if (ZipStruct->ZipDescription.SizeOfExtraField)
		{
			
			ZipStruct->ZipDescription.ExtraField = new char[ZipStruct->ZipDescription.SizeOfExtraField+1];
			memset(ZipStruct->ZipDescription.ExtraField, 0, ZipStruct->ZipDescription.SizeOfExtraField+1);
			Filetmp+=ZipStruct->ZipDescription.SizeOfFileName;
			
			// 读扩展域
			if (!GetHead(&ZipStruct->Url, Filetmp, Filetmp+ZipStruct->ZipDescription.SizeOfExtraField, ZipStruct->ZipDescription.ExtraField, ZipStruct->ZipDescription.SizeOfExtraField, 1))
			{
			}
		}
		
		// 如果有注释 则读取注释
		if (ZipStruct->ZipDescription.SizeOfComment)
		{
			ZipStruct->ZipDescription.Comment = new char[ZipStruct->ZipDescription.SizeOfComment+1];
			memset(ZipStruct->ZipDescription.Comment, 0, ZipStruct->ZipDescription.SizeOfComment+1);
			Filetmp+=ZipStruct->ZipDescription.SizeOfExtraField;
			
			// 读注释
			if (!GetHead(&ZipStruct->Url, Filetmp, Filetmp+ZipStruct->ZipDescription.SizeOfComment, ZipStruct->ZipDescription.Comment, ZipStruct->ZipDescription.SizeOfComment, 1))
			{
			}
		}
		
		ZipStruct->FileDate.FileOffSetWei = Filetmp + ZipStruct->ZipDescription.SizeOfFileName + ZipStruct->ZipDescription.SizeOfExtraField + ZipStruct->ZipDescription.SizeOfComment;

		sprintf(TMP, "%d", ZipStruct->FileDate.FileOffSetTou);
		This->m_LIST_FILE.SetItemText(List_len, __LIST_FILE_ZIPDESCRIPTION_FILETOU, TMP);
		sprintf(TMP, "%d", ZipStruct->FileDate.FileOffSetWei);
		This->m_LIST_FILE.SetItemText(List_len, __LIST_FILE_ZIPDESCRIPTION_FILEWEI, TMP);

		List_len++;
		
		if (ZipStruct->ZipDescription.FileName)
			delete []ZipStruct->ZipDescription.FileName;

		if (ZipStruct->ZipDescription.ExtraField)
			delete []ZipStruct->ZipDescription.ExtraField;

		if (ZipStruct->ZipDescription.Comment)
			delete []ZipStruct->ZipDescription.Comment;
	}

	// 读取 ZIP_FINISH 结构

	File_P = 22;
	Filetmp = ZipStruct->FileDate.FileOffSetTou = ZipStruct->FileDate.FileOffSetWei;
	ZipStruct->ZipFinish.Comment = NULL;
	if (!GetHead(&ZipStruct->Url, ZipStruct->FileDate.FileOffSetTou, ZipStruct->FileDate.FileOffSetTou+File_P-1, &ZipStruct->ZipFinish, File_P, 1))
	{

	}

	// 读取注释
	if (ZipStruct->ZipFinish.SizeOfComment)
	{	
		ZipStruct->ZipFinish.Comment = new char[ZipStruct->ZipFinish.SizeOfComment+1];
		memset(ZipStruct->ZipFinish.Comment, 0, ZipStruct->ZipFinish.SizeOfComment+1);
		Filetmp += File_P;
		if (!GetHead(&ZipStruct->Url, Filetmp, Filetmp+ZipStruct->ZipFinish.SizeOfComment, ZipStruct->ZipFinish.Comment, ZipStruct->ZipFinish.SizeOfComment, 1))
		{
			
		}
	}

	My_ShowTS("=========【以下为压缩包的注释内容，有些压缩包的密码会被写在注释里面】===========================");
	My_ShowTS(ZipStruct->ZipFinish.Comment);
	My_ShowTS("=========【以上为压缩包的注释内容，有些压缩包的密码会被写在注释里面】===========================");


	ZipStruct->FileDate.FileOffSetWei =ZipStruct->FileDate.FileOffSetTou + File_P + ZipStruct->ZipFinish.SizeOfComment;

	Show_MSG("【下载整个文件】", GetFileAllSize(), ZipSize, ZipStruct->FileDate.PassWord, ZipStruct->FileDate.FileOffSetTou, ZipStruct->FileDate.FileOffSetWei);

	if (ZipStruct->ZipFinish.Comment)
		delete []ZipStruct->ZipFinish.Comment;

Exit:
	{
		Ting = TRUE;
	}
	
	return 1;
}
