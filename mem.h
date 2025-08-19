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
	




} mem;

#endif
