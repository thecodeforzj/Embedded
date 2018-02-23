//2018/02/23/16：56
//返回值	：1（包含）
  ：0（不包含）
//判断两个字符串是否包含对方
int JudgeStringCmp(const char *strLong, const char *strShort)
{
	char counter2 = 0;
	char counter1 = 0;
	const char * str1 = NULL, *str2 = NULL;
//判断哪个字符串是长字符串
	while( ('\0' != strLong[counter1]) || ('\0' != strShort[counter1]))
	{
		counter1++;
		counter2++;
		if ('\0' == strShort[counter1])
		{
			str1 = strLong;
			str2 = strShort;
		}
		if ('\0' == strLong[counter1])
		{
			str1 = strShort;
			str2 = strLong;
		}
	}
	counter2 = 0;
//判断字符串包含
	while (*str1 != '\0')
	{
		if (*str1 == *str2)
		{
			while (*str1 == str2[counter2])
			{
				str1++;
				counter2++;
				if (('\0' == *str1) || ('\0' == str2[counter2]))
				{
					return 1;
				}
			}
			counter2 = 0;
		}
		else
		{
			str1++;
		}
	}
	return 0;


}
