DWORD WINAPI Zip_ThreadProc( LPVOID lpParam )
{

	char TMP[300] = {0};
	ZIP_STRUCT *ZipStruct = (ZIP_STRUCT*)lpParam; 
	DWORD File_P = 30;
	DWORD ZipSize = 0;
	DWORD Filetmp = 0;

	DWORD List_len = 0;
	strcpy(ZipStruct->FileDate.PassWord, "��");

	
	My_ShowTS("���ڻ�ȡ�ļ���С��");
	ZipSize = GetHead(&ZipStruct->Url, NULL, NULL, NULL, NULL, 0); // ��ʼ�����õ��ļ����ܴ�С
	if (!ZipSize)
	{	
		My_ShowTS("ѹ�����ļ���СΪ0 �� ��Է�HTTP����������ʧ�ܡ�");	
		Ting = TRUE;
		goto Exit;
	}

	sprintf(TMP, "��ȡ���ļ���СΪ�� %d �ֽڡ�", ZipSize);
	My_ShowTS(TMP);

	My_ShowTS("���ڷ������ļ�������");
	
	ZipStruct->FileDate.FileOffSetWei = 0;

	// ���� ZIP_HEADER  �ṹ
	while(1)
	{     
		ZipStruct->FileDate.FileOffSetTou = ZipStruct->FileDate.FileOffSetWei;
		// ��ȡ���ͷ
		if (!GetHead(&ZipStruct->Url, ZipStruct->FileDate.FileOffSetTou, ZipStruct->FileDate.FileOffSetTou+File_P-1, &ZipStruct->ZipHeader, 30, 1))
		{
			My_ShowTS("�޷���ȡ���ͷ����Է�HTTP����������ʧ�ܡ�");
			Ting = TRUE;
			goto Exit;
		}
		
		// ��������ļ����
		if (ZipStruct->ZipHeader.Signature != 0x04034b50)
			break;
		
		ZipStruct->FileDate.FileOffSetWei = ZipStruct->FileDate.FileOffSetTou+File_P+ZipStruct->ZipHeader.SizeOfFileName+ZipStruct->ZipHeader.SizeOfExtraField;
		ZipStruct->ZipHeader.FileName = new char[ZipStruct->ZipHeader.SizeOfFileName+1];
		memset(ZipStruct->ZipHeader.FileName, 0, ZipStruct->ZipHeader.SizeOfFileName+1);
		
		// ��ȡ�ļ���
		if (!GetHead(&ZipStruct->Url, ZipStruct->FileDate.FileOffSetTou+File_P, ZipStruct->FileDate.FileOffSetTou+File_P+ZipStruct->ZipHeader.SizeOfFileName, ZipStruct->ZipHeader.FileName, ZipStruct->ZipHeader.SizeOfFileName, 1))
		{
			My_ShowTS("�޷���ȡ���ͷ����Է�HTTP����������ʧ�ܡ�");
			Ting = TRUE;
			goto Exit;
		}

		if (!strstr(ZipStruct->ZipHeader.FileName, "/"))
			ZipStruct->FileDate.FileOffSetWei += ZipStruct->ZipHeader.CompressedSize;
		

		// ���������
		if (ZipStruct->ZipHeader.Signature == 0x08074B50)
		{
			strcpy(ZipStruct->FileDate.PassWord, "��");
			ZipStruct->FileDate.FileOffSetWei += 16;
		}
		Show_MSG(ZipStruct->ZipHeader.FileName, ZipStruct->ZipHeader.UncompressedSize, ZipStruct->ZipHeader.CompressedSize, ZipStruct->FileDate.PassWord,ZipStruct->FileDate.FileOffSetTou, ZipStruct->FileDate.FileOffSetWei);
		

		if (ZipStruct->ZipHeader.FileName)
			delete []ZipStruct->ZipHeader.FileName;
	}
	
	// ���� ZIP_DESCRIPTION �ṹ
	
	while (1)
	{	
		File_P = 46;
	
		ZipStruct->FileDate.FileOffSetTou = ZipStruct->FileDate.FileOffSetWei;
		Filetmp = ZipStruct->FileDate.FileOffSetTou; 
		ZipStruct->FileDate.FileOffSetTou = ZipStruct->FileDate.FileOffSetWei;
		ZipStruct->ZipDescription.FileName = NULL;
		ZipStruct->ZipDescription.ExtraField = NULL;
		ZipStruct->ZipDescription.Comment = NULL;

		// ��ȡ ZIP_DESCRIPTION ���ͷ
		if (!GetHead(&ZipStruct->Url, ZipStruct->FileDate.FileOffSetTou, ZipStruct->FileDate.FileOffSetTou+File_P-1, &ZipStruct->ZipDescription, File_P, 1))
		{
			My_ShowTS("�޷���ȡ ZIP_DESCRIPTION ���ͷ����Է�HTTP����������ʧ�ܡ�");
			Ting = TRUE;
			goto Exit;
		}

		if (ZipStruct->ZipDescription.Signature != 0x02014b50)
			break;
		
		ZipStruct->ZipDescription.FileName = new char[ZipStruct->ZipDescription.SizeOfFileName+1];
		memset(ZipStruct->ZipDescription.FileName, 0, ZipStruct->ZipDescription.SizeOfFileName+1);
		Filetmp+=File_P;
		
		// ��ȡ����
		if (!GetHead(&ZipStruct->Url, Filetmp, Filetmp+ZipStruct->ZipDescription.SizeOfFileName, ZipStruct->ZipDescription.FileName, ZipStruct->ZipDescription.SizeOfFileName, 1))
		{
		}
		
		// �������չ�� �� ��ȡ��չ��
		if (ZipStruct->ZipDescription.SizeOfExtraField)
		{
			
			ZipStruct->ZipDescription.ExtraField = new char[ZipStruct->ZipDescription.SizeOfExtraField+1];
			memset(ZipStruct->ZipDescription.ExtraField, 0, ZipStruct->ZipDescription.SizeOfExtraField+1);
			Filetmp+=ZipStruct->ZipDescription.SizeOfFileName;
			
			// ����չ��
			if (!GetHead(&ZipStruct->Url, Filetmp, Filetmp+ZipStruct->ZipDescription.SizeOfExtraField, ZipStruct->ZipDescription.ExtraField, ZipStruct->ZipDescription.SizeOfExtraField, 1))
			{
			}
		}
		
		// �����ע�� ���ȡע��
		if (ZipStruct->ZipDescription.SizeOfComment)
		{
			ZipStruct->ZipDescription.Comment = new char[ZipStruct->ZipDescription.SizeOfComment+1];
			memset(ZipStruct->ZipDescription.Comment, 0, ZipStruct->ZipDescription.SizeOfComment+1);
			Filetmp+=ZipStruct->ZipDescription.SizeOfExtraField;
			
			// ��ע��
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

	// ��ȡ ZIP_FINISH �ṹ

	File_P = 22;
	Filetmp = ZipStruct->FileDate.FileOffSetTou = ZipStruct->FileDate.FileOffSetWei;
	ZipStruct->ZipFinish.Comment = NULL;
	if (!GetHead(&ZipStruct->Url, ZipStruct->FileDate.FileOffSetTou, ZipStruct->FileDate.FileOffSetTou+File_P-1, &ZipStruct->ZipFinish, File_P, 1))
	{

	}

	// ��ȡע��
	if (ZipStruct->ZipFinish.SizeOfComment)
	{	
		ZipStruct->ZipFinish.Comment = new char[ZipStruct->ZipFinish.SizeOfComment+1];
		memset(ZipStruct->ZipFinish.Comment, 0, ZipStruct->ZipFinish.SizeOfComment+1);
		Filetmp += File_P;
		if (!GetHead(&ZipStruct->Url, Filetmp, Filetmp+ZipStruct->ZipFinish.SizeOfComment, ZipStruct->ZipFinish.Comment, ZipStruct->ZipFinish.SizeOfComment, 1))
		{
			
		}
	}

	My_ShowTS("=========������Ϊѹ������ע�����ݣ���Щѹ����������ᱻд��ע�����桿===========================");
	My_ShowTS(ZipStruct->ZipFinish.Comment);
	My_ShowTS("=========������Ϊѹ������ע�����ݣ���Щѹ����������ᱻд��ע�����桿===========================");


	ZipStruct->FileDate.FileOffSetWei =ZipStruct->FileDate.FileOffSetTou + File_P + ZipStruct->ZipFinish.SizeOfComment;

	Show_MSG("�����������ļ���", GetFileAllSize(), ZipSize, ZipStruct->FileDate.PassWord, ZipStruct->FileDate.FileOffSetTou, ZipStruct->FileDate.FileOffSetWei);

	if (ZipStruct->ZipFinish.Comment)
		delete []ZipStruct->ZipFinish.Comment;

Exit:
	{
		Ting = TRUE;
	}
	
	return 1;
}
