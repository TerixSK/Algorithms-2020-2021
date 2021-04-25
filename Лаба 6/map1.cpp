#include <fstream>
#include <vector>

using namespace std;

ifstream fin("map.in"); // ����� ��� ���, ��������� ������� get ������� �������� � ����
ofstream fout("map.out");

struct Key // ������ ��������� ��� �������� ������� �������������� �������
{
	string x;
	string y;
};

int func_hash(string& word) // ������� ��� ������������ ���������
{
	int hash = 0; // ������� ��� �����������: hash = (char1*k^0 + char2*k^1 + char3*k^2 + ... + charn*k^n) % hash_table.size()
	const int k = 41;
	long long h = 0, m = 1;
	for (char i : word)
	{
		int char_code = (int)(i - 'a' + 1);
		hash = (hash + m * char_code) % 10000001;
		m = (m * k) % 10000001;
	}
	return hash;
}

void put(vector<vector<Key>>& hash_table, string& key, string& word) // ������� ���������� �������� � ���-�������
{
	int hash = func_hash(key);
	for (auto& i : hash_table[hash]) // foreach - ��������� �������� �� ������� �������� � �������  
	{
		if (i.x == key) // �������� ���� �� ��� ���� � ����� ��� �������
		{
			i.y = word;
			return;
		}
	}
	hash_table[hash].push_back({ key, word }); // �������� ���� � �������� ��� ������� ����
}

void deleted(vector< vector<Key> >& hash_table, string& key) // ������� �������� �������� �� ���-�������
{
	int hash = func_hash(key);
	for (int i = 0; i < hash_table[hash].size(); i++)
	{
		if (hash_table[hash][i].x == key) // ���� ������ ����
		{
			hash_table[hash].erase(hash_table[hash].begin() + i); // ������� ���
			return;
		}
	}
}

void get(vector<vector<Key>>& hash_table, string key) // ������� ��� ������ ��������
{
	int hash = func_hash(key); // foreach - ��������� �������� �� ������� �������� � �������
	for (auto& i : hash_table[hash]) // ����� �� ����
	{
		if (i.x == key) // ���� ����� ������ ����
		{
			fout << i.y << endl; // ������� ��������
			return;
		}
	}
	fout << "none" << endl; // ���� �� �����, ������� none
}

int main()
{
	int n = 10000001;
	vector< vector<Key> > hash_table(n, vector<Key>());
	string com;
	while (fin)
	{
		fin >> com;
		if (!fin.eof())
		{
			if (com == "put")
			{
				string key, word;
				fin >> key >> word;
				put(hash_table, key, word);
			}
			else if (com == "get")
			{
				string key;
				fin >> key;
				get(hash_table, key);
			}
			else
			{
				string key;
				fin >> key;
				deleted(hash_table, key);
			}
		}
	}
	return 0;
}