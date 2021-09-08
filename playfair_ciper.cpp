#include<iostream>
#include<cstring>
#include<string>
#include<vector>
#define max 100
using namespace std;

void transkey(string &key, char matrix[5][5])
{
	//��Կ��Ԥ���������е�j������i
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
				//���ȼ�1
				check2--;
				// Ϊ��ʹ�����һ���ַ���ɾ��ʱ��check2���ᳬ��key�ķ�Χ��
			}
		}
		iter++;
	}
	string allkey = "ABCDEFGHIKLMNOPQRSTUVWXYZ";//ȥ��j

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

void encrypt(char matrix[5][5], string &text, string &result)//textΪ���ģ�resultΪ����
{
	//����Ԥ���������е�j���i
	for (auto it = text.begin(); it != text.end(); ++it)
	{
		if (*it == 'I' || *it == 'J')
			*it = 'I';
	}
	int length = text.length();
	int group;//������ɵ���ĸ������

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
			text.insert(it_1, 'Z');//����ͬ��ĸ�ĵ�һ����ĸ���������Ƨ��ĸ��Z��
			//text.insert(text.end() - 1, 'Z');//���ַ���ĩβ�����Ƨ��ĸ��Z��
			length += 1;
			m_n[j][0] = *it_1;
			m_n[j][1] = *(it_1 + 1);
			++it_1;
			++it_1;
			++j;
		}
	}
	//������ظ����ַ���ӹ����ַ���������Ϊ���������ַ���ĩβ�����Ƨ��ĸ��Z��
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

	//��ȡÿһ����ĸ�� ����Կ�����е�λ�ò���¼�±�
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
		//������ĸ����ͬһ��Ҳ����ͬһ��
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
			//cout << "�������ܺ�������ǣ�" << m_n[i][j];
		}
	cout << "�������ܺ�������ǣ�" << result<<endl;
}

void decrypt(char matrix[5][5], string &text, string &result)//textΪ���ģ�resultΪ����
{
	int length = result.length();
	int group = length / 2;//������ɵ���ĸ������

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

	//��ȡÿһ����ĸ�� ����Կ�����е�λ�ò���¼�±�
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
		//������ĸ����ͬһ��Ҳ����ͬһ��
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
	cout << "�������ܺ�������ǣ�" << text << endl;

}
int main()
{
	//�����ַ����Լ���Կȫ�ô�д��ĸ
	string key;
	char matrix[5][5];
	cout << "������playfair��Կ���Ա�����5*5��Կ����" << endl;
	cin >> key;
	//��Կ�ʵ���Կ����ı任
	transkey(key, matrix);
	int choice;
	bool judge = true;
	string text_1, result_1;
	string text_2, result_2;
	while (judge)
	{
		cout << "1����������" << endl;
		cout << "2����������" << endl;
		cout << "3���˳��ӽ���" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "���������ģ�";
			cin >> text_1;
			encrypt(matrix, text_1, result_1);
			break;
		case 2:
			cout << "���������ģ�";
			cin >> result_2;
			decrypt(matrix, text_2, result_2);
			break;
		default:
			judge = false;
			break;
		}
	}



}