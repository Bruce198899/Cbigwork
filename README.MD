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
