//Base64�ַ���
const char g_Base64Table[] =
{
 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
 '0','1','2','3','4','5','6','7','8','9','+','/'
};
 
char Base64CharToIndex(char chBase64)
{
 for (unsigned int index =0; index < sizeof(g_Base64Table); index++)
 {
  if (g_Base64Table[index] == chBase64)
  {
   return (char)index;
  }
 }
 return 0xFF;
}


unsigned int Base64Decode(const char *pInString, unsigned int nStrLen, char *pOutString, unsigned int nBufferLen)
{
 unsigned int nGroup = 0;
 unsigned int nMinBufferLen = 0;
 unsigned int nEqualChar = 0;
 const char *pInTemp = NULL;
 char *pOutTemp = NULL;
 char ch1, ch2;
 //error parameter
 if (pInString == NULL || nStrLen == 0)
 {
  return 0;
 }
 if (nStrLen %4 != 0)
 {
  return 0;
 }
 //get equal char count
 pInTemp = pInString + nStrLen - 1;
 while (*pInTemp-- == '=')
 {
  nEqualChar++;
 }
 if (nEqualChar > 2)
 {
  return 0;
 }
 nGroup = nStrLen / 4;
 nMinBufferLen = (nGroup - 1) * 3;
 switch (nEqualChar)
 {
 case 0:
  nMinBufferLen += 3;
  break;
 case 1:
  nMinBufferLen += 2;
  break;
 case 2:
  nMinBufferLen += 1;
  break;
 default:
  break;
 }
 //get  min buffer length
 if (pOutString == NULL && nBufferLen == 0)
 {
  return nMinBufferLen;
 }
 //error parameter
 if (pOutString != NULL && nBufferLen < nMinBufferLen)
 {
  return 0;
 }
 pInTemp = pInString;
 pOutTemp = pOutString;
 
 //decode normal group
 for (unsigned int i = 0; i < nGroup -1; i++)
 {
  ch1 = Base64CharToIndex(*pInTemp++);
  ch2 = Base64CharToIndex(*pInTemp++);
  //6 bit3 + 2bits
  *pOutTemp++ = ((ch1 << 2) & 0xFC) | ((ch2 >> 4) & 0x03);
  
  //4 bits + 4bits
  ch1 = ch2;
  ch2 = Base64CharToIndex(*pInTemp++);
  *pOutTemp++ = ((ch1 << 4) & 0xF0) | ((ch2 >> 2) & 0x0F);
  //2 bits + 6 bits
  ch1 = ch2;
  ch2 = Base64CharToIndex(*pInTemp++);
  *pOutTemp++ = ((ch1 << 6) & 0xC0) | ch2;
 }

 //decode last group
 switch (nEqualChar)
 {
 case 0:
  {
   ch1 = Base64CharToIndex(*pInTemp++);
   ch2 = Base64CharToIndex(*pInTemp++);
   //6 bit3 + 2bits
   *pOutTemp++ = ((ch1 << 2) & 0xFC) | ((ch2 >> 4) & 0x03);
   //4 bits + 4bits
   ch1 = ch2;
   ch2 = Base64CharToIndex(*pInTemp++);
   *pOutTemp++ = ((ch1 << 4) & 0xF0) | ((ch2 >> 2) & 0x0F);
   //2 bits + 6 bits
   ch1 = ch2;
   ch2 = Base64CharToIndex(*pInTemp++);
   *pOutTemp++ = ((ch1 << 6) & 0xC0) | ch2;
  }
  break;
 case 1:
  {
   ch1 = Base64CharToIndex(*pInTemp++);
   ch2 = Base64CharToIndex(*pInTemp++);
   //6 bit3 + 2bits
   *pOutTemp++ = ((ch1 << 2) & 0xFC) | ((ch2 >> 4) & 0x03);
   //4 bits + 4bits
   ch1 = ch2;
   ch2 = Base64CharToIndex(*pInTemp++);
   *pOutTemp++ = ((ch1 << 4) & 0xF0) | ((ch2 >> 2) & 0x0F);
  }
  break;
 case 2:
  {
   ch1 = Base64CharToIndex(*pInTemp++);
   ch2 = Base64CharToIndex(*pInTemp++);
   //6 bit3 + 2bits
   *pOutTemp++ = ((ch1 << 2) & 0xFC) | ((ch2 >> 4) & 0x03);
  }
  break;
	default:
  break;
 }
 return nMinBufferLen;
}