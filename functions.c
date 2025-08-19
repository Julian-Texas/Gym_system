#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "functions.h"


//等待a秒后clear
void waitclear(int a)
{
	sleep(a);
	system("clear");
}


//判断卡号输入是否正确,是否全是数字
int if_digits(const char* input)
{
	for(int i = 0; i < 10; i++)
	{
		if (!isdigit((unsigned char)input[i]))  // 不是数字
			return 0;
	}

	return 1;
}
