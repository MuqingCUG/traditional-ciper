#include<iostream>
#include<cstring>
#include<vector>
#include<stdlib.h>
#include<string>
using namespace std;

void TurnWheel(int* wheel_l, int* wheel_r);//加密时正向转动一次
void ReverseWheel(int* wheel_l, int* wheel_r);//解密时逆向转动一次
void Encrypt(char* text, char* result, int* slow_l, int* slow_r, int* middle_l, int* middle_r, int* fast_l, int* fast_r);//加密
void Decrypt(char* result, char* text, int* slow_l, int* slow_r, int* middle_l, int*middle_r, int* fast_l, int* fast_r);//解密

int main()
{
	int a;
	while (true) {
		cout << "选择：1.加密\t2.解密\t3.退出加解密" << endl;
		cin >> a;
		//慢中快三个轮子的初始状态
		int slow_l[26] = { 24,25,26,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23 };
		int slow_r[26] = { 21,3,15,1,19,10,14,26,20,8,16,7,22,4,11,5,17,9,12,23,18,2,25,6,24,13 };
		int middle_l[26] = { 26,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25 };
		int middle_r[26] = { 20,1,6,4,15,3,14,12,23,5,16,2,22,19,11,18,25,24,13,7,10,8,21,9,26,17 };
		int fast_l[26] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26 };
		int fast_r[26] = { 8,18,26,17,20,22,10,3,13,11,4,23,5,24,9,12,25,16,19,6,15,21,2,7,1,14 };

		char* text = new char[128];
		char* result = new char[128];
		memset(text, 0, 128);//初始化
		memset(result, 0, 128);

		switch (a)
		{
		case 1:
			cout << "请输入你要加密的字符串："<< endl;
			cin >> text;
			Encrypt(text, result, slow_l, slow_r, middle_l, middle_r, fast_l, fast_r);
			cout << "密文：" << endl;
			for (unsigned int i = 0; i < strlen(result); i++)
			{
				cout << result[i];
			}
			cout << endl;
			break;
		case 2:
			cout << "请输入你要解密的字符串：" << endl;
			cin >> result;
			Decrypt(result, text, slow_l, slow_r, middle_l, middle_r, fast_l, fast_r);
			cout << "明文：" << endl;
			for (unsigned int i = 0; i < strlen(text); i++)
			{
				cout << text[i];
			}
			cout << endl;
			break;
		default:
			return 0;
			break;
		}
	}
	return 0;
}

void TurnWheel(int* wheel_l, int* wheel_r)
{
	int temp = wheel_l[25];
	for (int i = 25; i > 0; i--)
		wheel_l[i] = wheel_l[i - 1];
	wheel_l[0] = temp;

	temp = wheel_r[25];
	for (int i = 25; i > 0; i--)
		wheel_r[i] = wheel_r[i - 1];
	wheel_r[0] = temp;
}
void ReverseWheel(int* wheel_l, int* wheel_r)
{
	int temp = wheel_l[0];
	for (int i = 0; i < 25; i++)
		wheel_l[i] = wheel_l[i + 1];
	wheel_l[25] = temp;

	temp = wheel_r[0];
	for (int i = 0; i < 25; i++)
		wheel_r[i] = wheel_r[i + 1];
	wheel_r[25] = temp;
}
void Encrypt(char* text, char* result, int* slow_l, int* slow_r, int* middle_l, int* middle_r, int* fast_l, int* fast_r)
{
	int count = 0;//快轮转动次数
	for (unsigned int i = 0; i < strlen(text); i++)//加密
	{
		if ('A' <= text[i] && text[i] <= 'Z')
		{
			int current = text[i] - 'A';//确定位置
			current = slow_l[current];//第一次替换
			for (int j = 0; j < 26; j++)
			{
				if (current == slow_r[j])
				{
					current = middle_l[j];//第二次替换
					break;
				}
			}
			for (int j = 0; j < 26; j++)
			{
				if (current == middle_r[j])
				{
					current = fast_l[j];//第三次替换
					break;
				}
			}
			for (int j = 0; j < 26; j++)
			{
				if (current == fast_r[j])
				{
					current = j;//第四次替换
					break;
				}
			}
			result[i] = char(current + 65);//加65得到对应的字母，A的ASCII表中序号是65
			count++;
			TurnWheel(fast_l, fast_r);//快轮转动一次
			if (count % 26 == 0)//判断是否要转动
			{
				TurnWheel(middle_l, middle_r);
				if (count % (26 * 26) == 0)
				{
					TurnWheel(slow_l, slow_r);
				}
			}
		}
	}
}
void Decrypt(char* result, char* text, int* slow_l, int* slow_r, int* middle_l, int*middle_r, int* fast_l, int* fast_r)
{
	int count = 0;
	for (unsigned int i = 0; i < strlen(result); i++)//先让轮子转成加密后的状态
	{
		if ('A' <= result[i] && result[i] <= 'Z')
		{
			count++;
			TurnWheel(fast_l, fast_r);
		}
	}
	if (count % 26 == 0)
	{
		TurnWheel(middle_l, middle_r);
		if (count % (26 * 26) == 0)
		{
			TurnWheel(slow_l, slow_r);
		}
	}

	for (int i = strlen(result) - 1; i >= 0; i--)//解密
	{

		if ('A' <= result[i] && result[i] <= 'Z')
		{
			ReverseWheel(fast_l, fast_r);//快轮先转回去一次再解密

			int current = result[i] - 'A';
			current = fast_r[current];
			for (int j = 0; j < 26; j++)
			{
				if (current == fast_l[j])
				{
					current = middle_r[j];
					break;
				}
			}
			for (int j = 0; j < 26; j++)
			{
				if (current == middle_l[j])
				{
					current = slow_r[j];
					break;
				}
			}
			for (int j = 0; j < 26; j++)
			{
				if (current == slow_l[j])
				{
					current = j;
					break;
				}
			}
			if (count % 26 == 0)
			{
				ReverseWheel(middle_l, middle_r);
				if (count % (26 * 26) == 0)
				{
					ReverseWheel(slow_l, slow_r);
				}
			}
			count--;//前面判断完了再减一
			text[i] = char(current + 65);
		}
	}
}


