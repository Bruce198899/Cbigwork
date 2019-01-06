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
	int Habbit_Time;
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
	char Brand_Name[10];
	int Total_Bike;
	int Healthy_Bike;
	int Bike_In_Use;
	float Use_Time_length;
	float Profit;
	int Total_Use_Times;
	float Payment_Per_Hour;
	float Payment_Ratio;
	struct COMPANY *Next;
};
struct USER *USER_CURSOR;
struct USER *USER_HEAD;
struct USER *PTRUSER;//全局登录的用户指针
struct BIKE *BIKE_CURSOR;
struct BIKE *BIKE_HEAD;
struct COMPANY *COMPANY_CURSOR;
struct COMPANY *COMPANY_HEAD;
/*声明函数区*/
int Initial();//初始化数据
int Save();
int Menu_Set();//菜单栏循环嵌套体
int User_Reg();//返回1，注册成功
int User_Log();//返回1，登陆成功，并且把PTRUSER指向正确的用户
int Use_Bike(struct USER *USER);
int Return_Bike(struct USER *USER);
int Call_Fix();
int Data_Bike();
int Data_Company();
int Data_User();
void Show_Bike_List();
void Show_Company_List();
void Show_User_List();
int usernum=0;//用户数量
/*排序算法区，用了归并排序，复杂度o(nlogn)，比较适合链表*/
BIKE *mergeBIKE(BIKE *head1, BIKE *head2)
{
	if(head1 == NULL)return head2;
	if(head2 == NULL)return head1;
	BIKE *res , *p ;
	if(head1->Use_Time < head2->Use_Time)
	{
		res = head1; head1 = head1->Next;
	}
	else{res = head2; head2 = head2->Next;}
	p = res;
	while(head1 != NULL && head2 != NULL)
	{
		if(head1->Use_Time < head2->Use_Time)
		{
			p->Next = head1;
			head1 = head1->Next;
		}
		else
		{
			p->Next = head2;
			head2 = head2->Next;
		}
		p = p->Next;
	}
	if(head1 != NULL)p->Next = head1;
	else if(head2 != NULL)p->Next = head2;
	return res;
}
BIKE *mergeSortListBIKE(BIKE *head) 
{
	if(head == NULL || head->Next == NULL) return head;
	else
    {
		BIKE *fast = head,*slow = head;
		while(fast->Next != NULL && fast->Next->Next != NULL)
		{
			fast = fast->Next->Next;
            
			slow = slow->Next;    
		}
		fast = slow;
		slow = slow->Next;
		fast->Next = NULL;
		fast = mergeSortListBIKE(head);//前半段排序
		slow = mergeSortListBIKE(slow);//后半段排序
		return mergeBIKE(fast,slow);
	}
}
COMPANY *mergeCOMPANY(COMPANY *head1, COMPANY *head2)
{
	if(head1 == NULL)return head2;
	if(head2 == NULL)return head1;
	COMPANY *res , *p ;
	if(head1->Total_Use_Times < head2->Total_Use_Times)
	{
		res = head1; head1 = head1->Next;
	}
	else{res = head2; head2 = head2->Next;}
	p = res;
	while(head1 != NULL && head2 != NULL)
	{
		if(head1->Total_Use_Times < head2->Total_Use_Times)
		{
			p->Next = head1;
			head1 = head1->Next;
		}
		else
		{
			p->Next = head2;
			head2 = head2->Next;
		}
		p = p->Next;
	}
	if(head1 != NULL)p->Next = head1;
	else if(head2 != NULL)p->Next = head2;
	return res;
}
COMPANY *mergeSortListCOMPANY(COMPANY *head) 
{
	if(head == NULL || head->Next == NULL) return head;
	else
    {
		COMPANY *fast = head,*slow = head;
		while(fast->Next != NULL && fast->Next->Next != NULL)
		{
			fast = fast->Next->Next;
            
			slow = slow->Next;    
		}
		fast = slow;
		slow = slow->Next;
		fast->Next = NULL;
		fast = mergeSortListCOMPANY(head);//前半段排序
		slow = mergeSortListCOMPANY(slow);//后半段排序
		return mergeCOMPANY(fast,slow);
	}
}
COMPANY *mergeCOMPANY1(COMPANY *head1, COMPANY *head2)
{
	if(head1 == NULL)return head2;
	if(head2 == NULL)return head1;
	COMPANY *res , *p ;
	if(head1->Use_Time_length < head2->Use_Time_length)
	{
		res = head1; head1 = head1->Next;
	}
	else{res = head2; head2 = head2->Next;}
	p = res;
	while(head1 != NULL && head2 != NULL)
	{
		if(head1->Use_Time_length < head2->Use_Time_length)
		{
			p->Next = head1;
			head1 = head1->Next;
		}
		else
		{
			p->Next = head2;
			head2 = head2->Next;
		}
		p = p->Next;
	}
	if(head1 != NULL)p->Next = head1;
	else if(head2 != NULL)p->Next = head2;
	return res;
}
COMPANY *mergeSortListCOMPANY1(COMPANY *head) 
{
	if(head == NULL || head->Next == NULL) return head;
	else
    {
		COMPANY *fast = head,*slow = head;
		while(fast->Next != NULL && fast->Next->Next != NULL)
		{
			fast = fast->Next->Next;
            
			slow = slow->Next;    
		}
		fast = slow;
		slow = slow->Next;
		fast->Next = NULL;
		fast = mergeSortListCOMPANY1(head);//前半段排序
		slow = mergeSortListCOMPANY1(slow);//后半段排序
		return mergeCOMPANY1(fast,slow);
	}
}
/*主函数子函数区*/
int main()
{
	system("color F0");
	system("title C语言大作业：Bruce的共享单车管理程序：https://github.com/Bruce198899/Shared-Bike-Controller");
    system("mode con cols=100 lines=35");//窗口宽度高度
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
	FILE *USER_array;
	FILE *COMPANY_array;
	FILE *BIKE_array;
	FILE *USER_NUMBER;
	if((USER_array=fopen("USERDATA","r"))==NULL||(COMPANY_array=fopen("COMPANYDATA","r"))==NULL||(BIKE_array=fopen("BIKEDATA","r"))==NULL||(USER_NUMBER=fopen("USERNUM","r"))==NULL)
	{
		return 0;
	}
	else
	{
		fread(&usernum,sizeof(int),1,USER_NUMBER);
		USER_HEAD=(USER *)malloc(sizeof(USER));
		fread(USER_HEAD,sizeof(USER),1,USER_array);
		USER_HEAD->Next=NULL;
		USER_CURSOR=USER_HEAD;
		for(int i=0;i<=usernum-2;i++)//默认4个用户
		{
			struct USER *TEMPNODE=(USER *)malloc(sizeof(USER));
			fread(TEMPNODE,sizeof(USER),1,USER_array);
			TEMPNODE->Next=NULL;
			USER_CURSOR->Next=TEMPNODE;
			USER_CURSOR=USER_CURSOR->Next;
		}
		//
		BIKE_HEAD=(BIKE *)malloc(sizeof(BIKE));
		fread(BIKE_HEAD,sizeof(BIKE),1,BIKE_array);
		BIKE_HEAD->Next=NULL;
		BIKE_CURSOR=BIKE_HEAD;
		for(int i=0;i<=4;i++)//默认共6车
		{
			struct BIKE *TEMPNODE=(BIKE *)malloc(sizeof(BIKE));
			fread(TEMPNODE,sizeof(BIKE),1,BIKE_array);
			TEMPNODE->Next=NULL;
			BIKE_CURSOR->Next=TEMPNODE;
			BIKE_CURSOR=BIKE_CURSOR->Next;
		}
		//
		COMPANY_HEAD=(COMPANY *)malloc(sizeof(COMPANY));
		fread(COMPANY_HEAD,sizeof(COMPANY),1,COMPANY_array);
		COMPANY_HEAD->Next=NULL;
		COMPANY_CURSOR=COMPANY_HEAD;
		for(int i=0;i<=1;i++)//默认共三个公司
		{
			struct COMPANY *TEMPNODE=(COMPANY *)malloc(sizeof(COMPANY));
			fread(TEMPNODE,sizeof(COMPANY),1,COMPANY_array);
			TEMPNODE->Next=NULL;
			COMPANY_CURSOR->Next=TEMPNODE;
			COMPANY_CURSOR=COMPANY_CURSOR->Next;
		}
		fclose(BIKE_array);
		fclose(COMPANY_array);
		fclose(USER_array);
		fclose(USER_NUMBER);
		return 1;
	}
}
int Save()
{
FILE *USER_array,*COMPANY_array,*BIKE_array,*USER_NUM;
	if((USER_array=fopen("USERDATA","w"))==NULL||(COMPANY_array=fopen("COMPANYDATA","w"))==NULL||(BIKE_array=fopen("BIKEDATA","w"))==NULL||(USER_NUM=fopen("USERNUM","w"))==NULL)
		{
			return 0;
	}
	else
	{
		USER_CURSOR=USER_HEAD;
		while(USER_CURSOR!=NULL)
		{
			fwrite(USER_CURSOR,sizeof(USER),1,USER_array);
			USER_CURSOR=USER_CURSOR->Next;
		}
		COMPANY_CURSOR=COMPANY_HEAD;
		while(COMPANY_CURSOR!=NULL)
		{
			fwrite(COMPANY_CURSOR,sizeof(COMPANY),1,COMPANY_array);
			COMPANY_CURSOR=COMPANY_CURSOR->Next;
		}
		BIKE_CURSOR=BIKE_HEAD;
		while(BIKE_CURSOR!=NULL)
		{
			fwrite(BIKE_CURSOR,sizeof(BIKE),1,BIKE_array);
			BIKE_CURSOR=BIKE_CURSOR->Next;
		}
		fwrite(&usernum,sizeof(int),1,USER_NUM);
		return 1;
	}
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
	printf("│                              7.注销用户                               │\n│                                                                       │\n");
	printf("│                              8.退出程序                               │\n│                                                                       │\n");
	printf("└───────────────────────────────────────────────────────────────────────┘\n");
	printf("请输入要选择的功能前的数字：");
	fflush(stdin);
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
			Return_Bike(PTRUSER);
			break;
		}
	case 3:
		{
			Call_Fix();
			break;
		}
	case 4:
		{
			Data_Bike();
			break;
		}
	case 5:
		{
			Data_Company();
			break;
		}
	case 6:
		{
			Data_User();
			break;
		}
	case 8:
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
	case 7:
		{
			if(PTRUSER!=NULL)
			{
				printf("\n【注销】您的编号%d的用户已经注销！\n",PTRUSER->UID);
				PTRUSER=NULL;
				break;
			}
			else 
			{
				printf("\n【注销】您尚且没有登录，无需注销！\n");
				break;
			}
		}
	default:
		{
			choice = 0;
			fflush(stdin);
			printf("\n【系统】您没有输入正确的操作指令！将返回主菜单\n");
		};
	}
	printf("\n");
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
					Use_Bike(NULL);
				}
			}
			else if(Choice=='R')
				{
					if(User_Reg()==1)
						{
							Use_Bike(PTRUSER);
					}
					else 
					{
						Use_Bike(NULL);
					}
			}
			else 
			{
				printf("\n【用车】您选择退出或输入了不合法字符，将返回主菜单！\n");
				return 0;
			} 
	}
	else 
	{
		Show_Bike_List();
		printf("\n【用车】用户%d您好，请输入您要用的车的编号！如果要返回主菜单，请输入0：",USER_CURSOR->UID);
		int choice=0;
		fflush(stdin);
		scanf("%d",&choice);
		if(choice==0)
			return 0;
		else 
		{
			BIKE_CURSOR=BIKE_HEAD;
			while(BIKE_CURSOR->Next!=NULL)
				{
					if(BIKE_CURSOR->UID!=choice)
						BIKE_CURSOR=BIKE_CURSOR->Next;
					else 
					{
						if(BIKE_CURSOR->Usage==1)
						{
							printf("\n【用车】车辆在使用中，您不能使用！\n");
							Use_Bike(PTRUSER);
						}
						else if(BIKE_CURSOR->Health==0)
						{
							printf("\n【用车】车辆已经损坏，不能使用！\n");
							Use_Bike(PTRUSER);
						}
						else
						{
							COMPANY_CURSOR=COMPANY_HEAD;
							while(BIKE_CURSOR->Host_Company_UID!=COMPANY_CURSOR->UID)
								COMPANY_CURSOR=COMPANY_CURSOR->Next;
							COMPANY_CURSOR->Bike_In_Use++;
							BIKE_CURSOR->Usage=1;
							printf("\n【用车】你已经租用了编号为%d的车辆\n",choice);
							return 1;
						}
					}
			
			}
			if(BIKE_CURSOR->UID!=choice)
			{
				printf("\n【用车】车辆选择错误，查无此车！\n");
				Use_Bike(PTRUSER);
			}
			else 
			{
				if(BIKE_CURSOR->Usage==1)
					{
						printf("\n【用车】车辆在使用中，您不能使用！\n");
						Use_Bike(PTRUSER);
				}
				else if(BIKE_CURSOR->Health==0)
				{
					printf("\n【用车】车辆已经损坏，不能使用！\n");
					Use_Bike(PTRUSER);
				}
				else
				{
					COMPANY_CURSOR=COMPANY_HEAD;
					while(BIKE_CURSOR->Host_Company_UID!=COMPANY_CURSOR->UID)
						COMPANY_CURSOR=COMPANY_CURSOR->Next;//公司数据变动：可用车数量下降，其他量在归还时改变；
					COMPANY_CURSOR->Bike_In_Use++;
					BIKE_CURSOR->Usage=1;
					printf("\n【用车】你已经租用了编号为%d的车辆\n",choice);
					return 1;
				}
			}
		}
	}
}
int User_Log()
{
	char _Account_Name[20],_Password[20];
	printf("\n【登录】请输入您要登录的用户名,如果要放弃登录，请输入Q并回车：");
	scanf("%s",_Account_Name);
	if(strcmp("Q\0",_Account_Name)==0)
		{
			printf("\n【登录】您选择退回用车菜单！\n");
			return 0;
	}
	USER_CURSOR=USER_HEAD;
	while (USER_CURSOR->Next!=NULL)
	{
		if(strcmp(USER_CURSOR->Account_Name,_Account_Name)!=0)
			USER_CURSOR=USER_CURSOR->Next;
		else
		{
			printf("\n【登录】请输入您要登录的用户的密码：");
			scanf("%s",_Password);
			if(strcmp(_Password,USER_CURSOR->Password)!=0)
				{
					printf("\n【登录】密码错误!\n");
					User_Log();
			}
			else PTRUSER=USER_CURSOR;
			return 1;
		}
	}
	if(strcmp(USER_CURSOR->Account_Name,_Account_Name)!=0)
	{
		printf("\n【登录】您输入的用户名不存在！\n");
		User_Log();
	}
	else
	{			
		printf("\n【登录】请输入您要登录的用户的密码：");
		scanf("%s",_Password);
		if(strcmp(_Password,USER_CURSOR->Password)!=0)
		{
				printf("密码错误!");
				User_Log();
		}
		else PTRUSER=USER_CURSOR;
		return 1;
	}
}
int User_Reg()
{
	char _Account_Name[20],_Password[20],_Phone_Number[12];
	int _Habbit_Time=0;
	printf("\n【注册】请输入您要注册的用户名,如果要放弃注册，请输入Q并回车：");
	scanf("%s",_Account_Name);
	if(strcmp("Q\0",_Account_Name)==0)
		{
			printf("\n【注册】您选择退回用车菜单！\n");
			return 0;
	}
	USER_CURSOR=USER_HEAD;
	while (USER_CURSOR->Next!=NULL)
	{
		if(strcmp(USER_CURSOR->Account_Name,_Account_Name)==0)
			{
				printf("\n【注册】您要注册的用户名已经被注册!\n");
				User_Reg();
		}
		USER_CURSOR=USER_CURSOR->Next;
	}
	if(strcmp(USER_CURSOR->Account_Name,_Account_Name)==0)
			{
				printf("\n【注册】您要注册的用户名已经被注册!\n");
				User_Reg();
		}
	printf("\n【注册】请输入您要注册的用户名%s的密码：",_Account_Name);
	scanf("%s",_Password);
	printf("\n【注册】请输入您的手机号：");
	scanf("%s",_Phone_Number);
	printf("\n【注册】请输入您习惯用车时间，只能输入某一个小时：");
	scanf("%d",&_Habbit_Time);
	PTRUSER=(USER *)malloc(sizeof(USER));
	PTRUSER->UID=USER_CURSOR->UID+1;
	PTRUSER->Average_Time=0;
	PTRUSER->Habbit_Time=_Habbit_Time;
	PTRUSER->Total_Use_Miles=0;
	PTRUSER->Total_Use_Time=0;
	strcpy(PTRUSER->Account_Name,_Account_Name);
	strcpy(PTRUSER->Password,_Password);
	strcpy(PTRUSER->Phone_Number,_Phone_Number);
	USER_CURSOR->Next=PTRUSER;
	USER_CURSOR=USER_CURSOR->Next;
	USER_CURSOR->Next=NULL;
	usernum++;
	printf("\n【注册】您已经成功注册账户名为：%s，密码为：%s 的账户，请保管好您的账户！\n",USER_CURSOR->Account_Name,USER_CURSOR->Password);
	return 1;
}
int Call_Fix()
{
	printf("\n【报修】感谢您报修，报修不需要用户登录，请您提供车辆的编号，如果要返回主菜单，请输入0：");
	int _UID;
	fflush(stdin);
	scanf("%d",&_UID);
	if(_UID==0)
		return 0;
	BIKE_CURSOR=BIKE_HEAD;
	while(BIKE_CURSOR->Next!=NULL)
		{
			if(BIKE_CURSOR->UID==_UID)
				break;
			else BIKE_CURSOR=BIKE_CURSOR->Next;
	}
	if (BIKE_CURSOR->Next==NULL&&BIKE_CURSOR->UID!=_UID)
	{
		printf("\n【报修】查无此车！\n");
	}
	else
	{
		if(BIKE_CURSOR->Usage==0&&BIKE_CURSOR->Health==1)
			{
				BIKE_CURSOR->Health=0;
				COMPANY_CURSOR=COMPANY_HEAD;
				while(BIKE_CURSOR->Host_Company_UID!=COMPANY_CURSOR->UID)
					COMPANY_CURSOR=COMPANY_CURSOR->Next;
				COMPANY_CURSOR->Healthy_Bike--;
				//公司数据变化：健康车辆数下降
				printf("\n【报修】成功将%d号车辆报修，该车辆在维修前将不能使用！\n",BIKE_CURSOR->UID);
				return 0;
		}
		else 
		{
			printf("\n【报修】您提供的车辆不需要报修或者正在使用中\n【提示】如果正在使用中，则您需先归还车辆！将要返回报修菜单！\n");
			Call_Fix();
		}
	}
	return 0;
}
int Return_Bike(struct USER *USER)
{
	if(USER==NULL)
		{
			printf("\n【系统】您目前没有登陆，如果要登陆，请输入Y；如果不想登陆，则您不能用车，请输入N：");
			fflush(stdin);
			char Choice = 0;
			scanf("%c",&Choice);
			if(Choice=='Y')
			{
				if(User_Log()==1)
					Return_Bike(PTRUSER);
				else 
				{
					Return_Bike(NULL);
				}
			}
			else 
			{
				printf("\n【还车】您选择退出或输入了不合法字符，将返回主菜单！\n");
				return 0;
			} 
	}
	else 
	{
		Show_Bike_List();
		printf("\n【还车】用户%d您好，请输入您要归还的车的编号！如果要返回主菜单，请输入0：",USER_CURSOR->UID);
		int choice=0;
		fflush(stdin);
		scanf("%d",&choice);
		if(choice==0)
			return 0;
		else 
		{
			BIKE_CURSOR=BIKE_HEAD;
			while(BIKE_CURSOR->Next!=NULL)
			{
				if(BIKE_CURSOR->UID!=choice)
					BIKE_CURSOR=BIKE_CURSOR->Next;
				else 
				{
					if(BIKE_CURSOR->Usage==0)
						{
							printf("\n【换车】车辆无需归还！\n");
							Return_Bike(PTRUSER);
					}
					else
					{
						float _USE_TIME,_USE_MILE,_USE_X,_USE_Y;
						printf("\n【还车】请依次输入您的用车时间、用车里程、现在的车辆x坐标和y坐标，均用空格隔开：\n");
						fflush(stdin);
						scanf("%f %f %f %f",&_USE_TIME,&_USE_MILE,&_USE_X,&_USE_Y);
						BIKE_CURSOR->Use_Time+=_USE_TIME;
						BIKE_CURSOR->Place[0]=_USE_X;
						BIKE_CURSOR->Place[1]=_USE_Y;
						PTRUSER->Total_Use_Miles+=_USE_MILE;
						PTRUSER->Total_Use_Miles+=_USE_MILE;
						COMPANY_CURSOR=COMPANY_HEAD;
						while(COMPANY_CURSOR->UID!=BIKE_CURSOR->Host_Company_UID)
							COMPANY_CURSOR=COMPANY_CURSOR->Next;
						COMPANY_CURSOR->Total_Use_Times++;
						COMPANY_CURSOR->Use_Time_length+=_USE_TIME;
						COMPANY_CURSOR->Bike_In_Use--;
						COMPANY_CURSOR->Profit+=_USE_TIME*(COMPANY_CURSOR->Payment_Per_Hour)*(COMPANY_CURSOR->Payment_Ratio);
						BIKE_CURSOR->Usage=0;
						printf("\n【还车】你已经归还了编号为%d的车辆\n",choice);
						return 1;
					}
				}
			}
			if(BIKE_CURSOR->UID!=choice)
				{
					printf("\n【还车】还车失败，查无此车！\n");
						Return_Bike(PTRUSER);
			}
			else 
			{
				if(BIKE_CURSOR->Usage==0)
					{
						printf("\n【还车】车辆无需归还！\n");	
						Use_Bike(PTRUSER);
				}
				else
				{
					float _USE_TIME,_USE_MILE,_USE_X,_USE_Y;
					printf("\n【还车】请依次输入您的用车时间、用车里程、现在的车辆x坐标和y坐标，均用空格隔开：\n");
					fflush(stdin);
					scanf("%f %f %f %f",&_USE_TIME,&_USE_MILE,&_USE_X,&_USE_Y);
					BIKE_CURSOR->Use_Time+=_USE_TIME;
					BIKE_CURSOR->Place[0]=_USE_X;
					BIKE_CURSOR->Place[1]=_USE_Y;
					PTRUSER->Total_Use_Miles+=_USE_MILE;
					PTRUSER->Total_Use_Miles+=_USE_MILE;
//公司数据的改动:使用车辆数量下降1，总使用次数、里程提高相应数值，计算收益累加；
					COMPANY_CURSOR=COMPANY_HEAD;
					while(COMPANY_CURSOR->UID!=BIKE_CURSOR->Host_Company_UID)
						COMPANY_CURSOR=COMPANY_CURSOR->Next;
					COMPANY_CURSOR->Total_Use_Times++;
					COMPANY_CURSOR->Use_Time_length+=_USE_TIME;
					COMPANY_CURSOR->Bike_In_Use--;
					COMPANY_CURSOR->Profit+=_USE_TIME*(COMPANY_CURSOR->Payment_Per_Hour)*(COMPANY_CURSOR->Payment_Ratio);
					BIKE_CURSOR->Usage=0;
					printf("\n【还车】你已经归还了编号为%d的车辆\n",choice);
					return 1;
				}
			}
		}
	}
}
int Data_Bike()
{
	Show_Bike_List();
	printf("    A:统计单车的使用情况和待使用情况        B:统计车辆损坏情况\n\n    C:对车辆按照总计骑行时间排序            D:返回主菜单\n\n【数据】请输入您要执行的功能：");
	char choice=0;
	fflush(stdin);
	scanf("%c",&choice);
	switch(choice)
	{
	case 'A':			//统计单车共计用了多少里程，已使用多少辆，有多少辆未使用，有多少辆损坏不能使用。
		{
			BIKE_CURSOR=BIKE_HEAD;
			int Bike_In_Use_Total=0,Bike_Not_Use_Total=0,Bike_Broken=0;
			float Time_Total=0;
			for(int i=0;i<=5;i++)
			{
				if(BIKE_CURSOR->Usage==1) 
					Bike_In_Use_Total++;
				else Bike_Not_Use_Total++;
				if(BIKE_CURSOR->Health!=1) 
					{
						Bike_Broken++;
				}
				Time_Total+=BIKE_CURSOR->Use_Time;
				BIKE_CURSOR=BIKE_CURSOR->Next;
			}
			if(Bike_Broken==0) printf("\n【数据输出】总计使用时长为为：%.2f小时，共有%d辆车正在被使用，有%d辆没有使用\n\n【数据输出】所有车均为好车！",Time_Total,Bike_In_Use_Total,Bike_Not_Use_Total);
			else 
			{
				printf("\n【数据输出】总计使用时长为为：%.2f小时，共有%d辆车正在被使用，有%d辆没有使用\n\n【数据输出】有%d辆车是坏车，他们的编号和所在地址是：",Time_Total,Bike_In_Use_Total,Bike_Not_Use_Total,Bike_Broken);
				BIKE_CURSOR=BIKE_HEAD;
				for(int i=0;i<=5;i++)	
					{
						if(BIKE_CURSOR->Health!=1) 
							printf("编号：%d号，所在地(%4.2f,%4.2f);",BIKE_CURSOR->UID,BIKE_CURSOR->Place[0],BIKE_CURSOR->Place[1]);
						BIKE_CURSOR=BIKE_CURSOR->Next;
				}
				printf("\n");
			}
			break;
		}
	case 'B'://统计车辆损坏多少辆，并输出该车辆位置
		{
			BIKE_CURSOR=BIKE_HEAD;
			int Bike_In_Use_Total=0,Bike_Not_Use_Total=0,Bike_Broken=0;
			float Time_Total=0;
			for(int i=0;i<=5;i++)
			{
				if(BIKE_CURSOR->Health!=1) 
						Bike_Broken++;
				BIKE_CURSOR=BIKE_CURSOR->Next;
			}
			if(Bike_Broken==0) printf("所有车均为好车！");
			else 
			{
				printf("有%d辆车是坏车，他们的编号和所在地址是：",Bike_Broken);
				BIKE_CURSOR=BIKE_HEAD;
				for(int i=0;i<=5;i++)	
					{
						if(BIKE_CURSOR->Health!=1) 
							printf("编号：%d号，所在地(%4.2f,%4.2f);",BIKE_CURSOR->UID,BIKE_CURSOR->Place[0],BIKE_CURSOR->Place[1]);
						BIKE_CURSOR=BIKE_CURSOR->Next;
				}
				printf("\n");
			}
			break;
		}
	case 'C'://对车辆按照骑行时间进行链表排序
		{
			BIKE_HEAD=mergeSortListBIKE(BIKE_HEAD);//归并排链表
			break;
		}
	case 'D'://返回主菜单
		{
			return 1000;
		}
	default://其他不知名的情况
		{
			choice = 0;
			fflush(stdin);
			printf("\n【系统】您没有输入正确的操作指令！将返回车辆查询菜单！\n");
		};
	}
	Data_Bike();
}
void Show_Bike_List()
{
	printf("\n┌──────────────────────────【自行车属性查询】──────────────────────────┐\n");
	printf("│ 车辆编号│ 公司编号 │ 使用否 │ 损坏否 │     所处位置    │ 总计骑行时间│\n");
	BIKE_CURSOR=BIKE_HEAD; 
	for(int i=0;i<=5;i++)
	{
		printf("│    %2d   │    %2d    │",BIKE_CURSOR->UID,BIKE_CURSOR->Host_Company_UID);
		BIKE_CURSOR->Usage==1?printf("   是   │"):printf("   否   │");
		BIKE_CURSOR->Health==1?printf("   否   │"):printf("   是   │");
		printf("   (%4.2f,%4.2f) │",BIKE_CURSOR->Place[0],BIKE_CURSOR->Place[1]);
		printf("    %4.2f   │\n",BIKE_CURSOR->Use_Time);
		BIKE_CURSOR=BIKE_CURSOR->Next;
	}
	printf("└──────────────────────────────────────────────────────────────────────┘\n");
}
int Data_Company()
{
	Show_Company_List();
	printf("    A:按照使用次数排序           B:检查是否有无备用车\n\n    C:按照使用时间排序           D:返回主菜单\n\n【数据】请输入您要执行的功能：");
	char choice=0;
	fflush(stdin);
	scanf("%c",&choice);
	switch(choice)
	{
	case 'A':
		{
			COMPANY_HEAD=mergeSortListCOMPANY(COMPANY_HEAD);
			break;
		}
	case 'B':
		{
			COMPANY_CURSOR=COMPANY_HEAD;
			while(COMPANY_CURSOR!=NULL)
			{
				if(COMPANY_CURSOR->Healthy_Bike==0)
					printf("\n【数据输出】%s公司已经没有可使用的车辆投放！\n",COMPANY_CURSOR->Brand_Name);
				else printf("\n【数据输出】%s公司车辆投放正常！\n",COMPANY_CURSOR->Brand_Name);
				COMPANY_CURSOR=COMPANY_CURSOR->Next;
			}
			break;
		}
	case 'C':
		{			
			COMPANY_HEAD=mergeSortListCOMPANY1(COMPANY_HEAD);
			break;
		}
	case 'D'://返回主菜单
		{
			return 1000;
		}
	default://其他不知名的情况
		{
			choice = 0;
			fflush(stdin);
			printf("\n【系统】您没有输入正确的操作指令！将返回公司查询菜单！\n");
		};
	}
	Data_Company();
	return 0;
}
void Show_Company_List()
{
	printf("\n┌──────────────────────────────────────【单车公司属性查询】─────────────────────────────────────┐\n");
	printf("│ 公司编号│ 公司商标 │ 总车数│ 好车数│ 使用中│ 总计骑行时间 │ 总使用次数 │  利润  │ 单价 │ 折扣 │\n");
	COMPANY_CURSOR=COMPANY_HEAD; 
	for(int i=0;i<=2;i++)
	{
		printf("│    %2d   │  %6s  │    %d  │   %d   │   %d   │    %.2f   │     %d    │ %.2f│ %.2f │ %.2f │\n",
			COMPANY_CURSOR->UID,COMPANY_CURSOR->Brand_Name,COMPANY_CURSOR->Total_Bike,COMPANY_CURSOR->Healthy_Bike,COMPANY_CURSOR->Bike_In_Use,COMPANY_CURSOR->Use_Time_length,COMPANY_CURSOR->Total_Use_Times,COMPANY_CURSOR->Profit,COMPANY_CURSOR->Payment_Per_Hour,COMPANY_CURSOR->Payment_Ratio);
		COMPANY_CURSOR=COMPANY_CURSOR->Next;
	}
	printf("└───────────────────────────────────────────────────────────────────────────────────────────────┘\n");
}
int Data_User()
{
	Show_User_List();
	printf("\n如果要返回主菜单，请输入Q：");
	char choice=0;
	fflush(stdin);
	scanf("%c",&choice);
	while(choice!='Q')
	{
		printf("\n\n【警告】您没有输入正确的操作指令！请重新输入：");
		fflush(stdin);
		scanf("%c",&choice);
	}
	return 0;
}
void Show_User_List()
{
	printf("\n┌──────────────────────────────────────【用户属性查询】───────────────────────────────────────┐\n");
	printf("│ 用户编号│ 用户名 │ 用户密码 │ 总使用时间 │ 总使用里程│  电话号码  │ 习惯时间 │ 平均每次时间 │ \n");
	USER_CURSOR=USER_HEAD; 
	while(USER_CURSOR!=NULL)
	{
		printf("│   %2d │ %6s │  %8s│   %6.2f   │   %6.2f  │ %s│    %2d    │     %5.2f    │\n",
			USER_CURSOR->UID,USER_CURSOR->Account_Name,USER_CURSOR->Password,USER_CURSOR->Total_Use_Time,USER_CURSOR->Total_Use_Miles,USER_CURSOR->Phone_Number,USER_CURSOR->Habbit_Time,USER_CURSOR->Average_Time);
		USER_CURSOR=USER_CURSOR->Next;
	}
	printf("└─────────────────────────────────────────────────────────────────────────────────────────────┘\n");
}
