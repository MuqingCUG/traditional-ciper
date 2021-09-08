//
//  main.cpp
//  caesar——ciper
//
//  Created by limuqing on 2021/6/24.
//

#include <iostream>
using namespace std;
#define max 100
//caesar 加密
int caesar_encrypt(char *text, char *result, int k)
{
	char small_letter[27] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
		'h', 'i', 'g', 'k', 'l', 'm', 'n', 'o',
		'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	char capital_letter[27] = { 'A','B','C','D','E','F','G','H','I','J','K',
		'L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
	if (text == NULL || k < 0)
		return -1;
	else {
		size_t m = strlen(text);
		for (int i = 0; i < m; ++i) {
			if (text[i] >= 'a'&&text[i] <= 'z')
				result[i] = small_letter[((text[i] - 'a') + k) % 26];
			else if (text[i] >= 'A'&&text[i] <= 'Z')
				result[i] = capital_letter[((text[i] - 'A') + k) % 26];
			else
				result[i] = text[i];
		}
		for (int i = 0; i < m; ++i)
			result[i] = toupper(result[i]);
		return 0;
	}
}

int caesar_decrypt(char*result, char *text, int k)
{
	char small_letter[27] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
		'h', 'i', 'g', 'k', 'l', 'm', 'n', 'o',
		'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	char capital_letter[27] = { 'A','B','C','D','E','F','G','H','I','J','K',
		'L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
	int p;
	if (result == NULL || k < 0)
		return -1;
	else
	{
		size_t m = strlen(result);
		for (int i = 0; i < m; ++i) {
			if (result[i] >= 'a'&&result[i] <= 'z')
			{
				p = ((result[i] - 'a') - k);
				while (p < 0)
					p += 26;
				text[i] = small_letter[p];
			}
			else if (result[i] >= 'A'&&result[i] <= 'Z')
			{
				p = ((result[i] - 'A') - k);
				while (p < 0)
					p += 26;
				text[i] = capital_letter[p];

			}
			else
				text[i] = result[i];
		}
		for (int i = 0; i < m; ++i)
			text[i] = tolower(text[i]);
		return 0;
	}
}
int main(int argc, const char * argv[]) {
	// insert code here...

	int n;
	cout << "------->welcome to caesar ciper<--------" << endl;
	while (true)
	{
		cout << "1、加密\t2、解密" << endl;
		cin >> n;
		switch (n) {
		case 1:
		{
			int k;
			char text[max] = "";
			char result[max] = "";
			cout << "请输入加密密钥：";
			cin >> k;
			cout << "请输入要加密的明文：";
			cin >> text;
			caesar_encrypt(text, result, k);
			cout << "这是加密后的密文：";
			cout << result;
			break;

		}
		case 2:
		{
			int k;
			char text[max] = "";
			char result[max] = "";
			cout << "请输入解密密钥：";
			cin >> k;
			cout << "请输入要解密的密文：";
			cin >> result;
			caesar_decrypt(result, text, k);
			cout << "这是解密后的明文：";
			cout << text;
			break;
		}
		default:
			break;
		}
		cout << endl;

	}

	return 0;
}
