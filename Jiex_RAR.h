//int RarRead(RarStruct->Url_STRUCT *RarStruct->Url, HEAD_STRUCT *Head, MAIN_HEAD *RarStruct->MainHead, FILE_HEAD *FileHead, FILE_DATE *FileDate)
DWORD WINAPI Rar_ThreadProc( LPVOID lpParam )
{

	char TMP[300] = {0};
	RAR_STRUCT *RarStruct = (RAR_STRUCT*)lpParam; 
	DWORD File_P = 7;
	DWORD RarSize = 0;

	strcpy(RarStruct->FileDate.PassWord, "��");
	My_ShowTS("���ڻ�ȡ�ļ���С��");
	RarSize = GetHead(&RarStruct->Url, NULL, NULL, NULL, NULL, 0); // ��ʼ�����õ��ļ����ܴ�С
	if (!RarSize)
	{	
		My_ShowTS("ѹ�����ļ���СΪ0 �� ��Է�HTTP����������ʧ�ܡ�");	
		Ting = TRUE;
		goto Exit;
	}

	sprintf(TMP, "��ȡ���ļ���СΪ�� %d �ֽڡ�", RarSize);
	My_ShowTS(TMP);

	My_ShowTS("���ڷ������ļ�������");
	// ��ȡ���ͷ
	if (!GetHead(&RarStruct->Url, 0, File_P-1, &RarStruct->Head, sizeof(HEAD_STRUCT), 1))
	{
		My_ShowTS("�޷���ȡ���ͷ����Է�HTTP����������ʧ�ܡ�");
		Ting = TRUE;
		goto Exit;
	}

	if(RarStruct->Head.HEAD_CRC != 0x6152 || RarStruct->Head.HEAD_TYPE != 0x72 || RarStruct->Head.HEAD_FLAGS != 0x1A21 || RarStruct->Head.HEAD_SIZE != 0x0007)
	{
		My_ShowTS("���ļ�����RAR�ļ���");
		Ting = TRUE;
		goto Exit;
	}
	// ��ȡѹ��ͷ
	if (!GetHead(&RarStruct->Url, File_P, File_P+7, &RarStruct->MainHead, sizeof(MAIN_HEAD), 1))
	{
		My_ShowTS("�޷���ȡѹ��ͷ����Է�HTTP����������ʧ�ܡ�");
		Ting = TRUE;
		goto Exit;
	}

	if ((RarStruct->MainHead.HEAD_FLAGS & 0x0080)== 0x0080)		
	{	
		My_ShowTS("��RAR�ļ��е������ļ��������ܡ��޷�ֱ�ӵõ��ļ�����");
		Ting = TRUE;
		goto Exit;
	}

	RarStruct->FileDate.FileOffSetTou = File_P  + RarStruct->MainHead.HEAD_SIZE ;

	This->m_PROGRESS_FILEDATE.SetPos(0);
	This->m_PROGRESS_FILEDATE.SetRange32(0,  RarSize);	// ���ý�����
	This->m_PROGRESS_FILEDATE.SetPos(0);

	This->m_PROGRESS_FILEDATE.SetPos(RarStruct->FileDate.FileOffSetTou);

	while (1)
	{

		memset(&RarStruct->Head, 0, sizeof(HEAD_STRUCT));
		memset(&RarStruct->MainHead, 0, sizeof(MAIN_HEAD));
		memset(&RarStruct->FileHead, 0, sizeof(FILE_HEAD));

		// ��ȡǰ�߸��ֽ�
		if(!GetHead(&RarStruct->Url, RarStruct->FileDate.FileOffSetTou, RarStruct->FileDate.FileOffSetTou+7, &RarStruct->Head, sizeof(HEAD_STRUCT), 1))
		{
	//		My_ShowTS("�޷���ȡǰ7���ֽڣ���Է�HTTP����������ʧ�ܡ��������ԡ�����");
			GetHead(&RarStruct->Url, NULL, NULL, NULL, NULL, 0);
			if(!GetHead(&RarStruct->Url, RarStruct->FileDate.FileOffSetTou, RarStruct->FileDate.FileOffSetTou+7, &RarStruct->Head, sizeof(HEAD_STRUCT), 1))
			{
				My_ShowTS("�޷���ȡǰ7���ֽڣ���Է�HTTP����������ʧ�ܡ�����ʧ��");
				goto Exit;
			}
		//	My_ShowTS("���Գɹ���");
		}
		switch (RarStruct->Head.HEAD_TYPE)
		{/*
			case 0x73:							// ѹ���ļ�ͷ
				
				break;*/
				
			case 0x74:							// �ļ�ͷ
				{
					RarStruct->FileDate.FileOffSetWei = RarStruct->FileDate.FileOffSetTou+RarStruct->Head.HEAD_SIZE-1;
					if (!GetHead(&RarStruct->Url, RarStruct->FileDate.FileOffSetTou, RarStruct->FileDate.FileOffSetWei, &RarStruct->FileHead, sizeof(FILE_HEAD), 1))
					{
					
				//		My_ShowTS("�޷���ȡ���ļ�ͷ����Է�HTTP����������ʧ�ܡ��������ԡ�����");
						GetHead(&RarStruct->Url, NULL, NULL, NULL, NULL, 0);
						if (!GetHead(&RarStruct->Url, RarStruct->FileDate.FileOffSetTou, RarStruct->FileDate.FileOffSetWei, &RarStruct->FileHead, sizeof(FILE_HEAD), 1))
						{
							My_ShowTS("�޷���ȡ���ļ�ͷ����Է�HTTP����������ʧ�ܡ�����ʧ��");
							goto Exit;
						}
				//		My_ShowTS("���Գɹ���");
					}
					// ����������ļ���������
					if ((RarStruct->FileHead.HEAD_FLAGS & 0x00E0)== 0x00E0)
					{
						RarStruct->FileDate.FileOffSetTou += RarStruct->Head.HEAD_SIZE;
						continue;
					}
			
					if ((RarStruct->FileHead.HEAD_FLAGS & 0x04)== 0x04)		// �ļ�������
						strcpy(RarStruct->FileDate.PassWord, "��");
					
					Show_MSG(RarStruct->FileHead.FILE_NAME, RarStruct->FileHead.UNP_SIZE, RarStruct->FileHead.PACK_SIZE, RarStruct->FileDate.PassWord, RarStruct->FileDate.FileOffSetTou, RarStruct->FileDate.FileOffSetWei + RarStruct->FileHead.PACK_SIZE);
					RarStruct->FileDate.FileOffSetTou = RarStruct->FileDate.FileOffSetWei + RarStruct->FileHead.PACK_SIZE + 1;
				}
				break;
		/*		
			case 0x75:							// �ɷ���ע��ͷ
				
				break;
				
			case 0x76:							// �ɷ����û������Ϣͷ
				
				break;
				
			case 0x77:							// �ɷ����ӿ�ͷ
				
				break;
				
			case 0x78:							// �ɷ��Ļָ���¼ͷ
				
				break;
				
			case 0x79:							// �û������Ϣͷ
				
				break;
				
			case 0x7A:							// ע��ͷ
				
				break;
				*/
			case 0x7B:							// ��βͷ
				//	Show_MSG("�����������ļ���", GetFileAllSize(), RarSize, RarStruct->FileDate.PassWord, 0,  0);

					goto Exit;
				break;

			default:
				{
					RarStruct->FileDate.FileOffSetWei = RarStruct->FileDate.FileOffSetTou+RarStruct->Head.HEAD_SIZE-1;
					if (!GetHead(&RarStruct->Url, RarStruct->FileDate.FileOffSetTou, RarStruct->FileDate.FileOffSetWei, &RarStruct->FileHead, sizeof(FILE_HEAD), 1))
					{
						
						//		My_ShowTS("�޷���ȡ���ļ�ͷ����Է�HTTP����������ʧ�ܡ��������ԡ�����");
						GetHead(&RarStruct->Url, NULL, NULL, NULL, NULL, 0);
						if (!GetHead(&RarStruct->Url, RarStruct->FileDate.FileOffSetTou, RarStruct->FileDate.FileOffSetWei, &RarStruct->FileHead, sizeof(FILE_HEAD), 1))
						{
							My_ShowTS("�޷���ȡ���ļ�ͷ����Է�HTTP����������ʧ�ܡ�����ʧ��");
							goto Exit;
						}
						//		My_ShowTS("���Գɹ���");
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
