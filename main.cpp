#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> 
struct USER //用户链表
{
	int UID;//用户UID
	char Account_Name[20];//用户名
	char Password[20];//用户密码
	float Total_Use_Time;//总使用时间
	float Total_Use_Miles;//
	char Phone_Number[12];
	int Habbit_Time[24];
	float Average_Time;
	struct USER *Next;
};
struct BIKE
{
	int UID;
	int Host_Company_UID;
	bool Usage;
	float Place[2];//地理坐标
	bool Health;
	float Use_Time;
	struct BIKE *Next;
};
struct COMPANY
{
	int UID;
	int Total_Bike;
	int Healthy_Bike;
	int Bike_In_Use;
	float Use_Time;
	float Profit;
	int Total_Use_Time;
	float Payment_Per_Hour;
	float Payment_Ratio;
	struct COMPANY *Next;
};
struct LOGS//日志，完成交易时产生。
{
	int Company;
	int Bike;
	float Start_Place[2];
	float End_Place[2];//地理坐标
	float Time;
	struct LOGS *Next;
};

struct USER *USER_CURSOR;
struct USER *USER_HEAD;
struct BIKE *BIKE_CURSOR;
struct BIKE *BIKE_HEAD;
struct COMPANY *COMPANY_CURSOR;
struct COMPANY *COMPANY_HEAD;
struct LOGS *LOGS_CURSOR;
struct LOGS *LOGS_HEAD;

/*声明函数区*/
int Initial();//初始化数据
int Save();
int Menu_Set();//菜单栏循环嵌套体
int User_Reg();//返回1，注册成功
int User_Log();//返回1，登陆成功，不反悔用户指针，用户指针全局存储
int Use_Bike(struct USER *USER);
void Return_Bike();
void Call_Fix();
void Data_Bike();
void Data_Company();
void Data_User();
FILE *COMPANYDATABASE;
struct USER *PTRUSER;//全局用户指针

/*主函数及子函数区*/
int main()
{
	system("color 0A");
	while(Initial()!=1)
	{
		printf("【系统】应用程序初始化失败，请问您是否要再次尝试初始化？如果是请，输入Y；如果否，将会退出程序，请输入N：");
		char Option;
		if((Option=getchar())!='Y')
			exit(0);
	}
	Menu_Set();
	return 0;
}
int Initial()//初始化，从文件中读取、建立数据文件；
{
	FILE *USER_array,*COMPANY_array,*BIKE_array;
	if((USER_array=fopen("USERDATA","r"))==NULL/*||(COMPANY_array=fopen("COMPDATA","r"))==NULL||(BIKE_array=fopen("BIKEDATA","r"))==NULL*/)
		return 0;
	else
	{
		//这些代码是用来把已经有的文件里面的东西读到链表里面去的！但是应该是出了什么大问题。
		/*
		USER_HEAD=(USER *)malloc(sizeof(USER));
		fread(USER_HEAD,sizeof(USER),1,USER_array);
		USER_CURSOR=USER_HEAD;//先把用户读一个头进去
		do
		{
			if(USER_HEAD->Next=NULL)//这表明：要么没有用户，要么到这就结束了
				break;
			else 
			{
				struct USER *TEMPNODE=(USER *)malloc(sizeof(USER));
				fread(TEMPNODE,sizeof(USER),1,USER_array);
				USER_CURSOR->Next=TEMPNODE;
				USER_CURSOR=USER_CURSOR->Next;
			}
		}
		while(USER_CURSOR->Next!=NULL);
		COMPANY_HEAD=(COMPANY *)malloc(sizeof(COMPANY));
		fread(COMPANY_HEAD,sizeof(COMPANY),1,COMPANY_array);
		COMPANY_CURSOR=COMPANY_HEAD;
		do
		{
			if(COMPANY_HEAD->Next=NULL)
				break;
			else 
			{
				struct COMPANY *TEMPNODE=(COMPANY *)malloc(sizeof(COMPANY));
				fread(TEMPNODE,sizeof(COMPANY),1,COMPANY_array);
				COMPANY_CURSOR->Next=TEMPNODE;
				COMPANY_CURSOR=COMPANY_CURSOR->Next;
			}
		}
		while(COMPANY_CURSOR->Next!=NULL);
		BIKE_HEAD=(BIKE *)malloc(sizeof(BIKE));
		fread(BIKE_HEAD,sizeof(BIKE),1,BIKE_array);
		BIKE_CURSOR=BIKE_HEAD;//先把用户读一个头进去
		do
		{
			if(BIKE_HEAD->Next=NULL)//这表明：要么没有用户，要么到这就结束了
				break;
			else 
			{
				struct BIKE *TEMPNODE=(BIKE *)malloc(sizeof(BIKE));
				fread(TEMPNODE,sizeof(BIKE),1,BIKE_array);
				BIKE_CURSOR->Next=TEMPNODE;
				BIKE_CURSOR=BIKE_CURSOR->Next;
			}
		}
		while(USER_CURSOR->Next!=NULL);
		return 1;
		*/
	}
}
int Save()
{
FILE *USER_array,*COMPANY_array,*BIKE_array;
	if((USER_array=fopen("USERDATA","w+"))==NULL||(COMPANY_array=fopen("COMPDATA","w+"))==NULL||(BIKE_array=fopen("BIKEDATA","w+"))==NULL)
		return 0;
	else
	{
		USER_CURSOR=USER_HEAD;
		do
		{
			fwrite(USER_CURSOR,sizeof(USER),1,USER_array);
			USER_CURSOR=USER_CURSOR->Next;
		}
		while(USER_CURSOR!=NULL);
		COMPANY_CURSOR=COMPANY_HEAD;
		do
		{
			fwrite(COMPANY_CURSOR,sizeof(COMPANY),1,COMPANY_array);
			COMPANY_CURSOR=COMPANY_CURSOR->Next;
		}
		while(COMPANY_CURSOR!=NULL);
		BIKE_CURSOR=BIKE_HEAD;
		do
		{
			fwrite(BIKE_CURSOR,sizeof(USER),1,COMPANY_array);
			BIKE_CURSOR=BIKE_CURSOR->Next;
		}
		while(USER_CURSOR!=NULL);
		return 1;
	}
}
int Menu_Set()
{
	printf("┌───────────────────────────────────────────────────────────────────────┐\n│                                                                       │\n");
	printf("│                            共享单车管理系统                           │\n│                                                                       │\n");
	printf("│                    By BruceZTY   All Rights Reserved                  │\n│                                                                       │\n");
	printf("│                              1.用户用车                               │\n│                                                                       │\n");
	printf("│                              2.用户还车                               │\n│                                                                       │\n");
	printf("│                              3.车辆报修                               │\n│                                                                       │\n");
	printf("│                          4.车辆使用情况查询                           │\n│                                                                       │\n");
	printf("│                          5.服务公司数据总览                           │\n│                                                                       │\n");
	printf("│                          6.单车用户数据总览                           │\n│                                                                       │\n");
	printf("│                              7.退出程序                               │\n│                                                                       │\n");
	printf("└───────────────────────────────────────────────────────────────────────┘\n");
	printf("请输入要选择的功能前的数字：");
	int choice=0;
	scanf("%d",&choice);
	switch(choice)
	{
	case 1:
		{
			Use_Bike(PTRUSER);
			break;
		}
	case 2:
		{
			//Return_Bike();
			break;
		}
	case 3:
		{
			Call_Fix();
			break;
		}
	case 4:
		{
			//Data_Bike();
			break;
		}
	case 5:
		{
			//Data_Company();
			break;
		}
	case 6:
		{
			//Data_User();
			break;
		}
	case 7:
		{
			while(Save()!=1)
			{
				printf("\n【系统】数据保存失败，如果要放弃保存请输入Q，否则将再次尝试保存用户数据：");
				char choice;
				if((choice=getchar())!='Q')
					break;
			}
			return 0;
		}
	default://其他不知名的情况
		{
			choice = 0;
			fflush(stdin);
			printf("\n【系统】您没有输入正确的操作指令！将返回主菜单\n\n");
		};
	}
	Menu_Set();
	return 0;
}
int Use_Bike(struct USER *USER)
{
	if(USER==NULL)
		{
			printf("\n【系统】您目前没有登陆，如果要登陆，请输入Y；如果您还没有注册，请输入R；如果不想登陆，则您不能用车，请输入N：");
			fflush(stdin);
			char Choice = 0;
			scanf("%c",&Choice);
			if(Choice=='Y')
			{
				if(User_Log()==1)
					Use_Bike(PTRUSER);
				else 
				{
					printf("\n【系统】登陆失败！将回到用车菜单！\n");
					Use_Bike(NULL);
				}
			}
			else if(Choice=='R')
				{
					if(User_Reg()==1)
						Use_Bike(PTRUSER);
					else 
					{
						printf("\n【系统】注册失败！将回到用车菜单\n");
						Use_Bike(NULL);
					}
			}
			else 
			{
				printf("\n【系统】您选择退出或输入了不合法字符，将返回主菜单！\n");
				return 0;
			} 
	}

}
int User_Reg()
{
	char User_Expect_USERNAME[20];
	printf("【系统】请输入要注册的用户名（不要输入空格等非法字符）：");
	scanf("%s",User_Expect_USERNAME);


	

	return 0;
}
int User_Log()
{
	return 0;
}
void Call_Fix()
{
	printf("\n【报修】感谢您报修，报修不需要用户登录，但是需要您提供车辆的编号：");
	int _UID;
	scanf("%d",&_UID);
	BIKE_CURSOR=BIKE_HEAD;
	while(BIKE_CURSOR->UID!=_UID)
		BIKE_CURSOR=BIKE_CURSOR->Next;
	if(BIKE_CURSOR=NULL)
		printf("\n【系统】未查询到您要报修的车辆，请您检查后再次尝试，将会返回主菜单！");
	else 
	{
		if(BIKE_CURSOR->Usage=1)
			printf("\n【报修】报修车辆前请先还车！");
		else
		{
			BIKE_CURSOR->Health=0;
			printf("\n【报修】报修成功，谢谢您对我们的支持！");
		}
	}
}
void Data_Bike()
{
	printf("UID    所属公司UID    正在用否    健康情况    地理位置    总计时长");
	BIKE_CURSOR=BIKE_HEAD;
	while(BIKE_CURSOR!=NULL)
	{
		printf("%5d%5d%5d%5d%   (%5f,%5f)%5f",BIKE_CURSOR->UID,BIKE_CURSOR->Host_Company_UID,BIKE_CURSOR->Usage,BIKE_CURSOR->Health,BIKE_CURSOR->Place[0],BIKE_CURSOR->Place[1],BIKE_CURSOR->Use_Time);
	}

}