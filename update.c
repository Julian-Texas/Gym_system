#include <stdio.h>
#include <string.h>
#include "mem.h"
#include "select.h"
#include "functions.h"
#include "update.h"

void mem_delete(void)
{
	char num[11];
	mem member;

	printf("请输入要注销的会员的卡号:\n");
	scanf("%10s", num);
	while(getchar() != '\n');

	FILE* fp = fopen(mem_information, "r+b");
	if(fp == NULL)
	{
		perror("\n用户数据文件打开失败!\n");
		return;
	}

	while (fread(&member, sizeof(mem), 1, fp))
	{
		if(strcmp(member.num, num) == 0)
		{
			break;
		}
	}

	if(feof(fp))
	{
		printf("\n未找到该用户...\n");
		waitclear(1);
	}
	else
	{
		printf("\n要注销的会员的信息如下:\n");
		mem_display(&member);

		char choice;
		printf("是否要注销此会员(Y/N):");
		scanf("%c", &choice);
		while(getchar() != '\n');

		if(choice == 'Y' || choice == 'y')
		{
			member.state = 1;
			fseek(fp, -sizeof(mem), SEEK_CUR);
			fwrite(&member, sizeof(mem), 1, fp);
			printf("\n会员注销成功!\n");

			waitclear(1);
		}
		else
		{
			printf("\n取消注销操作...\n");
			waitclear(1);
		}
	}

	fclose(fp);

}


//修改会员信息
void mem_update(void)
{
	char num[11];
	mem member;

	printf("请输入要修改的会员的卡号:\n");
	scanf("%10s", num);
	while(getchar() != '\n');

	FILE* fp = fopen(mem_information, "r+b");
	if(fp == NULL)
	{
		perror("\n用户数据文件打开失败!\n");
		return;
	}

	while (fread(&member, sizeof(mem), 1, fp))
	{
		if(strcmp(member.num, num) == 0)
		{
			break;
		}
	}

	if(feof(fp))
	{
		printf("\n未找到该用户...\n");
		waitclear(1);
	}
	else
	{
		printf("\n要修改的会员的信息如下:\n");
		mem_display(&member);

		printf("\n请选择要修改的信息:");
		printf("\n1.姓名...");
		printf("\n2.手机号...");
		printf("\n3.次卡剩余次数\n");
		printf(" >");

		int choice;

		if(scanf("%d", &choice) != 1)
		{
			while(getchar() != '\n');
			choice = -1;
		}

		switch(choice)
		{
			case 1:
				{
					char name[30];
					char choice;

					while(getchar() != '\n');

					printf("\n请输入更改后的姓名:");
					/*
					   if(fgets(name, sizeof(name),stdin) != NULL)
					   {
					   name[strcspn(name, "\n")] = '\0';
					   }

					   while(getchar() != '\n');
					   */

					if(fgets(name, sizeof(name), stdin) != NULL) {
						size_t len = strlen(name);
						if(len > 0 && name[len - 1] == '\n')
						{
							name[len - 1] = '\0';  // 去掉换行
						} else
						{
							// 没读到换行，说明输入超长，丢弃剩余
							int ch;
							while ((ch = getchar()) != '\n' && ch != EOF);
						}
					}


					printf("更改后的姓名为:%s,是否要更改(Y/N)", name);
					fflush(stdout);
					choice = getchar();
					while(getchar() != '\n');

					if(choice == 'Y' || choice == 'y')
					{
						strncpy(member.name, name, sizeof(member.name));

						fseek(fp, -sizeof(mem), SEEK_CUR);
						fwrite(&member, sizeof(mem), 1, fp);
						printf("\n姓名更改成功!\n");

						waitclear(1);
					}

					else
					{
						printf("\n取消更改操作...\n");
						waitclear(1);
					}

					break;
				}

			case 2:
				{
					char phone[12];
					char choice;

					while(getchar() != '\n');

					printf("\n请输入更改后的手机号:");

					if(fgets(phone, sizeof(phone), stdin) != NULL) {
						size_t len = strlen(phone);
						if(len > 0 && phone[len - 1] == '\n')
						{
							phone[len - 1] = '\0';  // 去掉换行
						} else
						{
							// 没读到换行，说明输入超长，丢弃剩余
							int ch;
							while ((ch = getchar()) != '\n' && ch != EOF);
						}
					}


					printf("更改后的手机号为:%s,是否要更改(Y/N)", phone);
					fflush(stdout);
					choice = getchar();
					while(getchar() != '\n');

					if(choice == 'Y' || choice == 'y')
					{
						strncpy(member.phone, phone, sizeof(member.phone));

						fseek(fp, -sizeof(mem), SEEK_CUR);
						fwrite(&member, sizeof(mem), 1, fp);
						printf("\n手机号更改成功!\n");

						waitclear(1);
					}

					else
					{
						printf("\n取消更改操作...\n");
						waitclear(1);
					}
					break;
				}

			case 3:
				{
					if(member.tp == times)
					{
						int remain_times;
						char choice;

						while(getchar() != '\n');

						printf("\n请输入更改后的次数:");
						scanf("%d",&remain_times);

						while(getchar() != '\n');

						printf("更改后的次数为:%d,是否要更改(Y/N)", remain_times);
						fflush(stdout);
						choice = getchar();
						while(getchar() != '\n');

						if(choice == 'Y' || choice == 'y')
						{
							member.times_card = remain_times;

							fseek(fp, -sizeof(mem), SEEK_CUR);
							fwrite(&member, sizeof(mem), 1, fp);
							printf("\n剩余次数更改成功!\n");

							waitclear(1);
						}

						else
						{
							printf("\n取消更改操作...\n");
							//waitclear(1);
						}
					}

					else
					{
						printf("非次卡用户不能更改!");
						waitclear(1);
					}
					

					break;
				}

			default:
				{
					printf("\n输入错误!\n");
					waitclear(1);
					break;
				}
		}


	}

	fclose(fp);

}
