﻿/*
目前大家比较熟悉共享单车的使用。请编制一个共享单车的管理程序，实现如下基本功能。假设有5种品牌的共享单车（品牌内容自定）。
	针对该5种品牌的共享单车，自行设计一套包含每种单车的品牌名称、投放量、投放点、某一时间点的在用数量、每辆车的每天骑行
	次数及单次里程和总里程、开锁过程中发现的损坏次数等信息(所有相关数据均自行设计)的数据结构；
	随着骑行活动的开展，待使用单车的数量将发生变化。要求能对每种单车的使用数量及待使用的数量进行查询统计并输出；
	对于某一投放点的某一品牌的单车，如果无备用车（待使用的车均为备用车），或备用车均为损坏的车，系统应能给出信息提示；
	对于损坏报修的车辆，系统能够进行及时的统计，并能在投放数量中削减损坏车辆的数量，形成真实的有效投放量；
//	能够对客户信息进行处理，包括注册的用户名、电话号码、骑行里程、骑行习惯（比如70%以上的出行时间集中在某个时间段，时间
	段按时钟整点划分）、每天平均的骑行时间等；
	该系统能进行当日使用状况的统计，请用链表排序（排序算法不限）提示交易使用次数排在前三名的单车品牌；
	假设每种单车的使用是收费的，如第一个小时是免费的，第二个小时开始每小时收费0.5元，各品牌可各自推出优惠收费条件（优惠
	条件请自定义），然后根据假设的使用情况，统计出各种品牌的日营业额，并对各品牌的受欢迎程度进行排序。

三、要求使用的知识点：
1)	变量、结构体或联合体；
2)	循环控制、条件判断；
3)	数组、函数；
4)	排序与查找算法及其实现；
5)	指针，用来操作字符串或其它特定内容；
6)	文件，用来保存某些数据；
7)	更多的功能使用，请根据自己程序的情况自由发挥。
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
如果是第一次使用，需要提示输入5种品牌的单车的品牌名称、投放量和投放地点，借此对5个品牌进行初始化；
菜单：1.租车 2.还车 3.使用情况查询 4.车辆报修 5.数据总览 6.客户信息查询
数据结构：
1.sturct USER{int UID,char ACCOUNTNAME[20],char PASSWORD[20],float USELENTH,char TELNUMBER[11],int HABBITTIME[24],int TOTALMILE,float AVERAGETIME,*struct USER next}
2.struct BIKE{int UID,int HOST(归属公司）,bool USAGE,char PLACE,bool HEALTH,float TIME}
3.单车品牌{UID,TOTALBIKE,HEALTHBIKE,BIKEINUSE,USETIME,PROFIT,USEFREQUENCY,PAYRATIO}
4.struct LOGS{int HOST,int BKIE,char START,char END,float TIME}
功能：
1.租车：	1.1未注册：提示注册。写入账号、密码到文件user.data。然后跳转回租车1.
		1.2已注册：	1.2.1：输入“BACK”，退回到1.租车
					1.2.2：账号密码输入错误，提示密码错误后跳转到1.2
					1.2.3：输入正确用户信息正确，自动匹配UID后，带入1.3用车程序
		1.3用车：参数：用车用户UID.
					1.3.1：输入了可用的车辆或品牌的UID，改变用车状态，用户UID不可再用车。对车辆UID赋予使用属性，不可再使用。
					1.3.2：输入的UID在使用状态或者已经损坏，提示后返回1.3。
					1.3.3：输入“BACK”，则返回1.租车
2.车辆报修：不验证用户UID
		1.1查询到该车已经损坏，返回提示信息后回道主菜单
		1.2查询到该车未损坏，给该车结构体的HEALTH赋予损坏属性
		1.3查询到该车不存在，返回提示信息

*/
struct USER 
{
	int UID;
	char Account_Name[20];
	char Password[20];
	float Total_Use_Time;
	float Total_Use_Miles;
	char Phone_Number[12];
	int Habbit_Time[24];
	float Average_Time;
	struct *USER Next;
}
struct BIKE
{
	int UID;
	int Host_Company_UID;
	bool Usage;
	float Place[2];//地理坐标
	bool Health;
	float Use_Time;
	struct BIKE *Next;
}
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
}
struct LOGS//日志，完成交易时产生。
{
	int Company;
	int Bike;
	float Start_Place[2];
	float End_Place[2];//地理坐标
	float Time;
	struct LOGS *Next;
}


