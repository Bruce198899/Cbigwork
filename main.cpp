#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<windows.h> 
#define ； ;//避免冒号错误

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

struct USER *USER_CRUSOR;
struct USER *USER_HEAD;
struct BIKE *BIKE_CRUSOR;
struct BIKE *BIKE_HEAD;
struct COMPANY *COMPANY_CRUSOR;
struct COMPANY *COMPANY_HEAD;
struct LOGS *LOGS_CRUSOR;
struct LOGS *LOGS_HEAD;

/*声明函数区*/
int Initial();//初始化数据
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
	//while(Initial()!=1)
	//{
	///	printf("应用程序初始化失败，请问您是否要再次尝试初始化？如果是请，输入Y；如果否，请输入N：");
	//	char Option;
	//	scanf("%c",&Option);
	//	if(Option=='N')
	//		break;
	//}
	Menu_Set();
	return 0;
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
			//Call_Fix();
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
		return 0;
	default://其他不知名的情况
		{
			choice = 0;
			fflush(stdin);
			printf("\n您没有输入正确的操作指令！将返回主菜单\n\n");
		};
	}
	Menu_Set();
	return 0;
}
int Use_Bike(struct USER *USER)
{
	if(USER==NULL)
		{
			printf("\n您目前没有登陆，如果要登陆，请输入Y；如果您还没有注册，请输入R；如果不想登陆，则您不能用车，请输入N：");
			fflush(stdin);
			char Choice = 0;
			scanf("%c",&Choice);
			if(Choice=='Y')
			{
				if(User_Log()==1)
					Use_Bike(PTRUSER);
				else 
				{
					printf("\n登陆失败！将回到用车菜单！\n");
					Use_Bike(NULL);
				}
			}
			else if(Choice=='R')
				{
					if(User_Reg()==1)
						Use_Bike(PTRUSER);
					else 
					{
						printf("\n注册失败！将回到用车菜单\n");
						Use_Bike(NULL);
					}
			}
			else 
			{
				printf("\n您选择退出或输入了不合法字符，将返回主菜单！\n");
				return 0;
			} 
	}

}
int User_Reg()
{
	char User_Expect_USERNAME[20];
	printf("请输入要注册的用户名（不要输入空格等非法字符）：");
	scanf("%s",User_Expect_USERNAME);


	

	return 0;
}
int User_Log()
{
	return 0;
}
