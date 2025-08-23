#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "adminsys.h"
#include "functions.h"
#include "select.h"
#include "mem.h"

void mem_query()
{
}


int main()
{
	waitclear(0);
	while(1)
	{
		char input[20] = {0};

		printf("\n欢迎使用健身房会员管理系统！\n");
		printf("\n会员自主查询请刷卡...\n\n管理员请输入规定内容进入系统...\n");
		printf("\n> ");
		scanf("%19s", input);

		//输入manage进入管理员系统，并输入密码验证
		if(strcmp(input, "manage") == 0)
		{
			char pwd[20];
			printf("\n请输入管理员密码: ");
			scanf("%19s", pwd);

			if(strcmp(pwd, "1962325350") == 0)
			{
				waitclear(0);
				adminsys();
			}
			else
			{
				printf("\n密码错误，拒绝访问！\n");
				waitclear(1);
			}
		}	

		//会员查询信息
		else if(strlen(input) == 10 && if_digits(input))
		{
			mem member;
			if(self_service_search(input, &member))
			{
				mem_display(&member);
				waitclear(5);
			}
		}

		else
		{
			printf("\n非法输入\n");
			waitclear(1);
		}

	}

	return 0;
}
