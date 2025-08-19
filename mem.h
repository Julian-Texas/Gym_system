#ifndef MEM_H
#define MEM_H

//声明性别枚举类型
typedef enum
{
	female = 0,
	male,
	other
} gender;

//声明会员卡枚举类型
typedef enum
{
	annual = 1,
	quarterly,
	monthly,
	weekly,
	times,
	lifetime
} type;


typedef struct
{
	char num[11];	//卡号
	char id[15];	//ID号
	char name[30];	//姓名
	gender gd;	//性别
	char phone[12];	//手机号
	type tp;	//会员卡类型
	time_t regist;	//注册时间
	time_t expire;	//到期时间
	int times_card;	//剩余次数
	int state;	//删除状态，0表示为删除，1表示已删除
} mem;

void mem_reg(void);

#endif
