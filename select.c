#include <stdio.h>
#include <time.h>
#include "select.h"


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
	switch(member->gb)
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
	printf("注册时间: %s\n", time_str);

	strftime(time_tmp, sizeof(time_tmp), "%Y-%m-%d %H:%M:%S", localtime(&member->expire));
	printf("到期时间: %s\n", time_str);
	
	if(member->tp == times)
	{
		printf("剩余次数: %d\n", member->times_card);
	}
}
