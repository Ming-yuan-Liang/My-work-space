#include "app_Finger.h"

SysPara AS608Para; // Fingerprint module AS608 parameters 指纹模块AS608参数
u16 ValidN;		   // Number of valid templates within the module 模块内有效模板个数

#define usart4_baund 57600

u8 Finger_Init(void)
{
	u8 ensure;

	char *str;
	for (u8 i = 0; i < 2; i++)
	{
		// initialization 初始化
		printf("AS608 Fingerprint module test\r\n");
		printf("Connect with AS608.....\r\n");
		while (PS_HandShake(&AS608Addr)) // Handshake with AS608 module 与AS608模块握手
		{
			printf("Cannot connect with AS608!\r\n");
			delay_ms(1000);
			printf("Try to connect again....\r\n");
			delay_ms(1000);
		}
	}

	// Successfully connected the module 连接模块成功
	printf("Connect Success!\r\n");
	str = mymalloc(30);
	sprintf(str, "Baudrate:%d\t   Addr:%lx", usart4_baund, AS608Addr); //Display Baud Rate 显示波特率
	printf("%s", str);
	delay_ms(100);
	ensure = PS_ValidTempleteNum(&ValidN); //Number of fingerprint reads in the database 读库指纹个数
	if (ensure != 0x00)
		ShowErrMessage(ensure);			 // Display confirmation code error message 显示确认码错误信息
	ensure = PS_ReadSysPara(&AS608Para); // Read AS608 module parameters 读AS608模块参数
	if (ensure == 0x00)
	{
		mymemset(str, 0, 50);
		sprintf(str, "\r\nRemainNum:%d\t    Level:%d", AS608Para.PS_max - ValidN -1, AS608Para.PS_level); // Display the remaining number of fingerprints and security level 显示剩余指纹数量和安全等级
		printf("%s", str);
	}
	else
	{
		ShowErrMessage(ensure);
		return 1; // Fail
	}

	myfree(str);

	printf("Success!\r\n");
	return 0;
}

// Display confirmation code error message 显示确认码错误信息
void ShowErrMessage(u8 ensure)
{
	printf("%s", EnsureMessage(ensure));
	delay_ms(1000);
}

// Fingerprint recording function 录指纹功能
void Add_FR(void)
{
	u8 i = 0, ensure, processnum = 0;
	u16 a1 = 0;
	while (1)
	{
		switch (processnum)
		{
		case 0:
			i++;
			printf("Please press your finger!\r\n");
			ensure = PS_GetImage();
			if (ensure == 0x00)
			{
				ensure = PS_GenChar(CharBuffer1); // Generate Features 生成特征
				if (ensure == 0x00)
				{

					// Correct fingerprint 指纹正确
					printf("Fingerprint ok\r\n");
					i = 0;
					processnum = 1; // Jump to the second step 跳到第二步
				}
				else
					ShowErrMessage(ensure);
			}
			else
				ShowErrMessage(ensure);
			break;

		case 1:
			i++;
			printf("Press your finger again\r\n");
			ensure = PS_GetImage();
			if (ensure == 0x00)
			{
				ensure = PS_GenChar(CharBuffer2); // Generate Features 生成特征
				if (ensure == 0x00)
				{
					printf("Fingerprint ok\r\n");
					i = 0;
					processnum = 2; //Jump to step three 跳到第三步
				}
				else
					ShowErrMessage(ensure);
			}
			else
				ShowErrMessage(ensure);
			break;

		case 2:
			printf("Compare two fingerprints\r\n");
			ensure = PS_Match();
			if (ensure == 0x00)
			{
				printf("Fingerprint ok\r\n");
				processnum = 3; //Jump to step four 跳到第四步
			}
			else
			{
				printf("Fail:Please press your finger again!\r\n");
				ShowErrMessage(ensure);
				i = 0;
				processnum = 0; //Jump back to the first step 跳回第一步
			}
			delay_ms(1000);
			break;

		case 3:
			printf("Generate a fingerprint module\r\n");
			ensure = PS_RegModel();
			if (ensure == 0x00)
			{
				printf("Successfully generated fingerprint template\r\n");
				processnum = 4; //Jump to step five 跳到第五步
			}
			else
			{
				processnum = 0;
				ShowErrMessage(ensure);
			}
			delay_ms(1000);
			break;

		case 4:
			printf("Please enter the storage location(1-299):\r\n");
			// A1 button control value a1按键控制数值
			while (1)
			{
				if (Key1_State(1)) //Increase numerical value 增加数值
				{
					a1++;
					if (a1 >= 300)
						a1 = 1;
					printf("Current values:%d\r\n", a1);
				}
				if (Key2_State(1)) //Reduce numerical value 减小数值
				{
					if (a1 == 0)
						a1 = 299; //Remove 0 because when deleted, 0 represents clearing the entire library 把0去掉，因为删除时0代表清整个库

					a1--;
					if (a1 == 0)
						a1 = 299;
					printf("Current values:%d\r\n", a1);
				}
				if (Key3_State(1)) //Confirm button 确认按键
				{
					break;
				}
			}
			ensure = PS_StoreChar(CharBuffer2, a1); //Storage Template 储存模板
			if (ensure == 0x00)
			{

				printf("Successfully added fingerprint!\r\n");
				PS_ValidTempleteNum(&ValidN); //Number of fingerprint reads in the database 读库指纹个数
				//Display the remaining number of fingerprints 显示剩余指纹个数
				printf("Remaining capacity:%d\r\n", AS608Para.PS_max - ValidN -1);//Remove 0 去掉0
				delay_ms(1500); //Clear display after delay 延时后清除显示
				printf("Start identifying fingerprints!\r\n");
				return;
			}
			else
			{
				processnum = 0;
				ShowErrMessage(ensure);
			}
			break;
		}
		delay_ms(1000);
		if (i == 5) //Exit without pressing your finger more than 5 times 超过5次没有按手指则退出
		{
			printf("\r\nexit!\r\n");
			break;
		}
	}
}

// Fingerprint brushing function 刷指纹功能
void Press_FR(void)
{
	SearchResult seach;
	u8 ensure;
	char *str;
	ensure = PS_GetImage();
	if (ensure == 0x00) //Successfully obtained image 获取图像成功
	{
		ensure = PS_GenChar(CharBuffer1);
		if (ensure == 0x00) //Successfully generated features 生成特征成功
		{
			ensure = PS_HighSpeedSearch(CharBuffer1, 0, 300, &seach);
			if (ensure == 0x00) //Search successful 搜索成功
			{
				printf("Find fingerprint!\r\n");
				str = mymalloc(50);
				sprintf(str, "Match ID:%d  Match score:%d", seach.pageID, seach.mathscore); // 显示匹配指纹的ID和分数
				printf("%s\r\n", str);
				myfree(str);
			}
			else
				ShowErrMessage(ensure);
		}
		else
			ShowErrMessage(ensure);
		delay_ms(1000);
	}
}

//Delete fingerprint function 删除指纹功能
void Del_FR(void)
{
	u8 ensure;
	u16 a = 0;
	printf("Delete fingerprint\r\n");
	printf("Delete fingerprint location:(0=< ID <=299)\r\n");
	printf("If you want to clear the fingerprint library, ID is set to 0.");

	//Change a to key value a改成按键值
	while (1)
	{
		if (Key1_State(1)) //Increase numerical value 增加数值
		{
			a++;
			if (a >= 300)
				a = 0;
			printf("Current values:%d\r\n", a);
		}
		if (Key2_State(1)) //Reduce numerical value 减小数值
		{
			a--; //Because it is of type u, negative numbers cannot occur 因为是u类型的，不可能出现负数
			if (a >= 300)
				a = 299;
			printf("Current values:%d\r\n", a);
		}
		if (Key3_State(1)) //Confirm button 确认按键
		{
			break;
		}
	}

	// If 0 is received, clear the fingerprint library 如果接收到的是0 则清空指纹库
	if (a == 0)
		ensure = PS_Empty(); // Clear fingerprint library 清空指纹库
	else
	{
		ensure = PS_DeletChar(a, 1); //Delete a single fingerprint 删除单个指纹
	}

	if (ensure == 0)
	{
		printf("Successfully deleted fingerprint\r\n");
	}
	else
		ShowErrMessage(ensure);
	delay_ms(1500);				  //Clear display after delay 延时后清除显示
	PS_ValidTempleteNum(&ValidN); //Number of fingerprint reads in the database 读库指纹个数
	printf("Number of fingerprints remaining:%d\r\n", AS608Para.PS_max - ValidN - 1);//Remove 0 去掉0
	delay_ms(50);
	printf("Start identifying fingerprints!");
	return;
}

void Finger_Loop(void)
{
	if (Key1_State(1)) //Fingerprint recording 录指纹
	{
		Add_FR();
	}
	else if (Key2_State(1)) //Delete fingerprint 删指纹
	{
		Del_FR();
	}
	else
	{
		if (PS_Sta)
		{
			Press_FR(); //Brushing fingerprints 刷指纹
		}
	}
}
