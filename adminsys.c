#include <stdio.h>
#include <stdlib.h>
#include "adminsys.h"
#include "functions.h"
#include "mem.h"
#include "select.h"
#include "update.h"


void adminsys(void)
{
	while(1)
	{
		// CUI 菜单式界面
		int op;

		printf("欢迎使用本系统！\n\n");
		printf("操作说明：\n");
		printf("1. 开卡\n");
		printf("2. 会员注销\n");
		printf("3. 修改会员信息\n");
		printf("4. 查询会员信息\n");
		printf("0. 退出系统\n");
		
		printf("\n> ");

		if(scanf("%d", &op) != 1)
		{
			// 输入失败
			// 清空标准输入缓冲区，以免影响下一次 scanf 调用
			while(getchar() != '\n');

			op = -1;
		}

		switch(op)
		{
			case 0:
				{
					printf("\n感谢您的使用，期待下次再见！\n");
					waitclear(1);
					return ;	//返回主函数
				}
				break;

			case 1:
				{
					// 开卡
					mem_reg();
					waitclear(1);
				}
				break;

			case 2:
				{
					// 会员注销
					mem_delete();
				}
				break;

			case 3:
				{
					// 修改会员信息
					mem_update();
				}
				break;

			case 4:
				{
					// 查询会员信息
					waitclear(0);
					mem_key();
					waitclear(0);
				}
				break;

			default:
				{
					// 输入错误
					printf("\n输入错误，请重新输入！\n");
					waitclear(1);
				}
		}
	}

}

