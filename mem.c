#include <stdio.h>
#include <time.h>
#include "mem.h"


//新增会员
void mem_reg(void)
{
	mem reg;

	printf("您现在正在添加会员，请输入会员信息：\n");
	printf("卡号:");
	scanf("%10s",reg.num);
	printf("姓名:");
	scanf("%29s",reg.name);
	printf("性别(0-女,1-男,2-其他):");
	int temp1;
	scanf("%d",&temp1);
	reg.gd = (gender)temp1;
	printf("手机号:");
	scanf("%11s",reg.phone);
	printf("会员卡类型(1-年卡,2-季卡,3-月卡,4-周卡,5-次卡,6-终身卡):");
	int temp2;
	scanf("%d",&temp2);
	reg.tp = (type)temp2;

	//注册时间 time(&reg.regist)
	reg.regist = time(NULL);
	
	//ID
	//struct tm *dt = localtime(&reg.regist);
	//strftime(reg.id, sizeof(reg.id), "%Y%m%d%H%M%S", dt);
	strftime(reg.id, sizeof(reg.id), "%Y%m%d%H%M%S", localtime(&reg.regist));

	//到期时间
	switch (reg.tp) {
		case annual:
			reg.expire = reg.regist + 365 * 24 * 3600;
			break;
		case quarterly:
			reg.expire = reg.regist + 91 * 24 * 3600;
			break;
		case monthly:
			reg.expire = reg.regist + 30 * 24 * 3600;
			break;
		case weekly:
			reg.expire = reg.regist + 7 * 24 * 3600;
			break;
		case times:
			reg.expire = reg.regist + 365 * 24 * 3600;
			break;
		case lifetime:
			reg.expire = reg.regist + 200L * 365 * 24 * 3600;
			break;
		default:
			perror("\n到期时间错误,请重新录入");
			return;
	}

	//剩余次数
	if(reg.tp == times)
	{
		printf("剩余次数:");
		scanf("%d", &reg.times_card);
	}
	else
		reg.times_card = -1;

	//删除状态
	reg.state = 0;

	FILE* fp = fopen(mem_information,"ab");
	if(fp == NULL)
	{
		perror("注册失败");
		return;
	}
	fwrite(&reg,sizeof(reg),1,fp);
	fclose(fp);

	printf("\n会员注册成功!!!\n");
}


