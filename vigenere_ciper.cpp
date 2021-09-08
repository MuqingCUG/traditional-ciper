#include<iostream>
#include<cstring>
using namespace std;

//加密
int encrypt(char *text, char *result, char *k)
{
	int i, j = 0, z = 0;
	int m = strlen(k); //获取密钥的长度
	int l = strlen(text); //获取明文的长度
	for (i = 0; i < l; i++)
	{
		//判断大小写
		if (text[i] >= 'A' && text[i] <= 'Z') {
			if (j == m) {
				j = 0;   //循环密钥
				result[z] = (text[i] - 'A' + k[j] - 'A') % 26 + 'A';
			}
			else {
				result[z] = (text[i] - 'A' + k[j] - 'A') % 26 + 'A';
			}
			j++;
		}
		else if (text[i] >= 'a' && text[i] <= 'z') {
			if (j == m) {
				j = 0;   //循环密钥
				result[z] = (text[i] - 'a' + k[j] - 'a') % 26 + 'a';
			}
			else {
				result[z] = (text[i] - 'a' + k[j] - 'a') % 26 + 'a';
			}
			j++;
		}
		else {  //判断是否是空格
			result[z] = text[i];
		}
		z++;
	}
	return 0;
}

//解密
int decrypt(char *text, char *result, char *k)
{
	int i, j = 0, z = 0;
	int m = strlen(k); //获取密钥的长度
	int l = strlen(text); //获取密文的长度
	for (i = 0; i < l; i++)
	{
		//判断是否是空格
		if (text[i] >= 'A' && text[i] <= 'Z') {
			if (j == m) {
				j = 0;   //循环密钥
				result[z] = (text[i] - k[j] + 26) % 26 + 'A';
			}
			else {
				result[z] = (text[i] - k[j] + 26) % 26 + 'A';
			}
			j++;
		}
		else if (text[i] >= 'a' && text[i] <= 'z') {
			if (j == m) {
				j = 0;   //循环密钥
				result[z] = (text[i] - k[j] + 26) % 26 + 'a';
			}
			else {
				result[z] = (text[i] - k[j] + 26) % 26 + 'a';
			}
			j++;
		}
		else {
			result[z] = text[i];
		}
		z++;
	}
	return 0;
}

int main()
{
	char text[50] = "";
	char result[50] = "";
	char k[50] = "";
	int type=0;
	/**欢迎**/
	cout << "--------欢迎使用Vigenere密码-----------" << endl;
	cout << "请填写明文或者密文" << endl;
	cin >> text;
	while (true)
	{
		cout << "选择：1、加密\t2、解密\t3、退出加解密" << endl;
		cin >> type;
		switch (type)
		{
		case 1:
			cout << "请输入密钥k" << endl;;
			cin >> k;
			/**加密**/
			encrypt(text, result, k);
			cout << "明文" << text << "的密文为:" << result << endl;
			break;
		case 2:
			cout << "请输入密钥k" << endl;;
			cin >> k;
			/**解密**/
			decrypt(text, result, k);
			cout << "明文" << text << "的密文为:" << result << endl;
			break;
		default:
			return 0;
			break;
		}
	}

	return 0;
}