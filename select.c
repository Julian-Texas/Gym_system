#include <stdio.h>
#include <time.h>
#include <string.h>
#include "select.h"
#include "mem.h"
#include "functions.h"

//通过姓名和手机号搜索时最多的显示个数
#define SEL_MAX 10

//显示会员信息
void mem_display(const mem* member)
{
	if(member == NULL)
	{
		printf("会员信息为空\n");
		return;
	}

	printf("\n====会员信息====\n");
	printf("卡号: %s\n", member->num);
	printf("ID: %s\n", member->id);
	printf("姓名: %s\n", member->name);
	printf("性别: ");
	switch(member->gd)
	{
		case female:
			printf("女\n"); break;
		case male:
			printf("男\n"); break;
		case other:
			printf("其他\n"); break;
		default:
			printf("未知\n");
	}
	printf("手机号: %s\n", member->phone);
	printf("会员卡类型: ");
	switch(member->tp)
	{
		case annual:
			printf("年卡\n"); break;
		case quarterly:
			printf("季卡\n"); break;
		case monthly:
			printf("月卡\n"); break;
		case weekly:
			printf("周卡\n"); break;
		case times:
			printf("次卡\n"); break;
		case lifetime:
			printf("终身卡\n"); break;
		default:
			printf("未知\n");
	}	

	char time_tmp[20];
	strftime(time_tmp, sizeof(time_tmp), "%Y-%m-%d %H:%M:%S", localtime(&member->regist));
	printf("注册时间: %s\n", time_tmp);

	strftime(time_tmp, sizeof(time_tmp), "%Y-%m-%d %H:%M:%S", localtime(&member->expire));
	printf("到期时间: %s\n", time_tmp);
	
	if(member->tp == times)
	{
		printf("剩余次数: %d\n", member->times_card);
	}
}


//用户自主查询
int self_service_search(const char* num, mem* result)
{
	FILE* fp = fopen(mem_information, "rb");
	if (fp == NULL)	
	{
		perror("\n用户数据文件打开失败!\n");
		return 0;
	}

	mem current;
	int found = 0;

	while(fread(&current, sizeof(mem), 1, fp))
	{
		if(current.state == 0 && strcmp(current.num, num) == 0)
		{
			*result = current;
			found = 1;
			break;
		}
	}

	if (feof(fp))
	{
		printf("\n未找到该会员!\n");
	}
	
	fclose(fp);
	return found;
}


//选择查询方式
void mem_key(void)
{
	int choice;

	printf("\n=== 会员查询 ===\n");
	printf("请选择查询方式:\n");
	printf("1. 按卡号查询\n");
	printf("2. 按姓名查询\n");
	printf("3. 按手机号查询\n");
	printf("0. 返回上级菜单\n");
	
	while(1)
	{
		printf("\n> ");

		if(scanf("%d", &choice) != 1)
		{
			while(getchar() != '\n');
			choice = -1;
		}

		switch (choice)
		{
		case 0:
			{
				return;
			}
			break;

		case 1:
			{
				select_by_num();
			}
			break;

		case 2:
			{
				select_by_name();
			}
			break;

		case 3:
			{
				select_by_phone();
			}
			break;
		
		default:
			{
				printf("输入错误，请重新输入!");
			}
		}
	}

	return;
}


//通过卡号查询
void select_by_num(void)
{
	char num[11];
	printf("请输入卡号:");
	scanf("%10s", num);
	while(getchar() != '\n');
	
	FILE* fp = fopen(mem_information, "rb");
	if (fp == NULL)
	{
		perror("用户数据文件打开失败!");
		return;
	}

	mem result;
	while(fread(&result, sizeof(mem), 1, fp))
	{
		if(result.state == 0 && strcmp(result.num, num) == 0)
			break;
	}

	if(feof(fp))
	{
		printf("未找到该用户...");
	}
	else
		mem_display(&result);

	fclose(fp);
}


//通过姓名查询
void select_by_name(void)
{
	char name[30];
	mem results[SEL_MAX];
	int count = 0;

	printf("请输入姓名:");
	scanf("%29s", name);
	while(getchar() != '\n');

	FILE* fp = fopen(mem_information, "rb");
	if (fp == NULL)
	{
		perror("用户数据文件打开失败!");
		return;
	}

	mem current;

	while(fread(&current, sizeof(mem), 1, fp) && count < SEL_MAX)
	{
		if(current.state == 0 && strcmp(current.name, name) == 0)
		{
			results[count] = current;
			count++;
		}

	}

	if (count > 0)
	{
		printf("找到 %d 个符合要求的会员,他们的信息如下:\n", count);
		for(int i = 0; i < count; i++)
		{
			mem_display(&results[i]);
		}
	}
	else
		printf("未找到该用户...");

	fclose(fp);

}


//通过手机号查询
void select_by_phone(void)
{
	char phone[12];
	mem results[SEL_MAX];
	int count = 0;

	printf("请输入手机号:");
	scanf("%11s", phone);
	while(getchar() != '\n');

	FILE* fp = fopen(mem_information, "rb");
	if (fp == NULL)
	{
		perror("用户数据文件打开失败!");
		return;
	}

	mem current;

	while(fread(&current, sizeof(mem), 1, fp) && count < SEL_MAX)
	{
		if(current.state == 0 && strcmp(current.phone, phone) == 0)
		{
			results[count] = current;
			count++;
		}
	}

	if (count > 0)
	{
		printf("找到 %d 个符合要求的会员,他们的信息如下:\n", count);
		for(int i = 0; i < count; i++)
		{
			mem_display(&results[i]);
		}
	}
	else
		printf("未找到该用户...");

	fclose(fp);
}