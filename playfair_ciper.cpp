#include<iostream>
#include<cstring>
#include<string>
#include<vector>
#define max 100
using namespace std;

void transkey(string &key, char matrix[5][5])
{
	//密钥词预处理，将所有的j处理变成i
	for (auto it = key.begin(); it != key.end(); ++it)
	{
		if (*it == 'I' || *it == 'J')
			*it = 'I';
	}
	string::iterator iter = key.begin();
	while (iter != key.end()) {
		for (string::iterator check2 = iter + 1; check2 != key.end(); check2++) {
			if (*iter == *check2) {
				key.erase(check2);
				//长度减1
				check2--;
				// 为了使得最后一次字符被删除时，check2不会超出key的范围。
			}
		}
		iter++;
	}
	string allkey = "ABCDEFGHIKLMNOPQRSTUVWXYZ";//去除j

	for (string::iterator it1 = key.begin(); it1 != key.end(); ++it1)
	{
		for (string::iterator it = allkey.begin(); it != allkey.end(); ++it)
		{
			if (*it == *it1)
			{
				allkey.erase(it);
			}
		}
	}
	key += allkey;
	cout << key << endl;
	cout << key.length() << endl;

	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
		{
			matrix[i][j] = key[i + j + 4 * i];
		}
}

void encrypt(char matrix[5][5], string &text, string &result)//text为明文，result为密文
{
	//明文预处理，将所有的j变成i
	for (auto it = text.begin(); it != text.end(); ++it)
	{
		if (*it == 'I' || *it == 'J')
			*it = 'I';
	}
	int length = text.length();
	int group;//最后分配成的字母对数量

	char m_n[max][2];
	int i = 0, j = 0;
	string::iterator it_1, it_2;
	it_1 = text.begin();
	while (it_1 < text.end() - 1/* && j < length / 2*/)
	{
		if (*it_1 != *(it_1 + 1))
		{
			m_n[j][0] = *it_1;
			m_n[j][1] = *(it_1 + 1);
			++it_1;
			++it_1;
			++j;
		}
		else
		{
			text.insert(it_1, 'Z');//在相同字母的第一个字母后面添加生僻字母‘Z’
			//text.insert(text.end() - 1, 'Z');//在字符串末尾添加生僻字母‘Z’
			length += 1;
			m_n[j][0] = *it_1;
			m_n[j][1] = *(it_1 + 1);
			++it_1;
			++it_1;
			++j;
		}
	}
	//如果在重复的字符添加过后，字符串长度仍为奇数，在字符串末尾添加生僻字母‘Z’
	if (length % 2 == 1)
	{
		text += "Z";
		m_n[(length + 1) / 2][0] = *(text.end() - 2);
		m_n[(length + 1) / 2][1] = *(text.end() - 1);
		group = (length + 1) / 2;
	}
	else
	{
		group = length / 2;
	}

	//获取每一组字母对 在密钥矩阵中的位置并记录下标
	int m = 0, n = 0;
	int p = 0, q = 0;
	int a = 0;
	while (a < group)
	{
		for (int i = 0; i < 5; ++i)
			for (int j = 0; j < 5; ++j)
			{
				if (matrix[i][j] == m_n[a][0])
				{
					m = i;
					n = j;
				}
				else if (matrix[i][j] == m_n[a][1])
				{
					p = i;
					q = j;
				}
			}
		//两个字母不在同一列也不在同一行
		if (m != p && n != q)
		{
			m_n[a][0] = matrix[m][q];
			m_n[a][1] = matrix[p][n];
			//result += m_n[a][0] + m_n[a][1];
		}
		else if (m == p && n != q)
		{
			if (n == 4)
			{
				m_n[a][0] = matrix[m][0];
				m_n[a][1] = matrix[p][q + 1];
			}
			else if (q == 4)
			{
				m_n[a][0] = matrix[m][n + 1];
				m_n[a][1] = matrix[p][0];
			}
			else
			{
				m_n[a][0] = matrix[m][n + 1];
				m_n[a][1] = matrix[p][q + 1];
			}
		}
		else if (m != p && n == q)
		{
			if (m == 4)
			{
				m_n[a][0] = matrix[0][n];
				m_n[a][1] = matrix[p + 1][q];
			}
			else if (n == 4)
			{
				m_n[a][0] = matrix[m + 1][n];
				m_n[a][1] = matrix[0][q];
			}
			else
			{
				m_n[a][0] = matrix[m + 1][n];
				m_n[a][1] = matrix[p + 1][q];
			}
		}
		++a;
	}

	for (int i = 0; i < group; ++i)
		for (int j = 0; j < 2; ++j)
		{
			result += m_n[i][j];
			//cout << "经过加密后的密文是：" << m_n[i][j];
		}
	cout << "经过加密后的密文是：" << result<<endl;
}

void decrypt(char matrix[5][5], string &text, string &result)//text为明文，result为密文
{
	int length = result.length();
	int group = length / 2;//最后分配成的字母对数量

	char m_n[max][2];

	int i = 0, j = 0;
	string::iterator it_1, it_2;
	it_1 = result.begin();
	while (it_1 < result.end() - 1 && j < group)
	{
		m_n[j][0] = *it_1;
		m_n[j][1] = *(it_1 + 1);
		++it_1;
		++it_1;
		++j;
	}

	//获取每一组字母对 在密钥矩阵中的位置并记录下标
	int m = 0, n = 0;
	int p = 0, q = 0;
	int a = 0;
	while (a < group)
	{
		for (int i = 0; i < 5; ++i)
			for (int j = 0; j < 5; ++j)
			{
				if (matrix[i][j] == m_n[a][0])
				{
					m = i;
					n = j;
				}
				else if (matrix[i][j] == m_n[a][1])
				{
					p = i;
					q = j;
				}
			}
		//两个字母不在同一列也不在同一行
		if (m != p && n != q)
		{
			m_n[a][0] = matrix[m][q];
			m_n[a][1] = matrix[p][n];
			//result += m_n[a][0] + m_n[a][1];
		}
		else if (m == p && n != q)
		{
			if (n == 0)
			{
				m_n[a][0] = matrix[m][4];
				m_n[a][1] = matrix[p][q - 1];
			}
			else if (q == 0)
			{
				m_n[a][0] = matrix[m][n - 1];
				m_n[a][1] = matrix[p][4];
			}
			else
			{
				m_n[a][0] = matrix[m][n - 1];
				m_n[a][1] = matrix[p][q - 1];
			}
		}
		else if (m != p && n == q)
		{
			if (m == 0)
			{
				m_n[a][0] = matrix[4][n];
				m_n[a][1] = matrix[p - 1][q];
			}
			else if (n == 0)
			{
				m_n[a][0] = matrix[m - 1][n];
				m_n[a][1] = matrix[4][q];
			}
			else
			{
				m_n[a][0] = matrix[m - 1][n];
				m_n[a][1] = matrix[p - 1][q];
			}
		}
		++a;
	}

	for (int i = 0; i < group; ++i)
		for (int j = 0; j < 2; ++j)
		{
			text += m_n[i][j];
		}
	cout << "经过解密后的明文是：" << text << endl;

}
int main()
{
	//输入字符串以及密钥全用大写字母
	string key;
	char matrix[5][5];
	cout << "请输入playfair密钥，以便生成5*5密钥矩阵。" << endl;
	cin >> key;
	//密钥词到密钥矩阵的变换
	transkey(key, matrix);
	int choice;
	bool judge = true;
	string text_1, result_1;
	string text_2, result_2;
	while (judge)
	{
		cout << "1、加密明文" << endl;
		cout << "2、解密密文" << endl;
		cout << "3、退出加解密" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "请输入明文：";
			cin >> text_1;
			encrypt(matrix, text_1, result_1);
			break;
		case 2:
			cout << "请输入密文：";
			cin >> result_2;
			decrypt(matrix, text_2, result_2);
			break;
		default:
			judge = false;
			break;
		}
	}



}