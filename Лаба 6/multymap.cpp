#include <fstream>
#include <vector>

using namespace std;

// ����� ������� main��������� � ��������� ����-��������
int multi_map_size = 100001;
int set_size = 1001;

struct Set // ������ ���������, ������� ����� �������
{
	string key; // ����
	vector < vector <string>> values; // � ��������� ��������
	Set()
	{
		values.resize(set_size); // ����� ������ ��������� ��������
	}
};
struct MultiMap // ������ ����_���������, ������� ����� ������� ��������� set
{
	vector< vector<Set> > set;
	MultiMap()
	{
		set.resize(multi_map_size); // ����� ������ ���������
	}
};
// ---------------
MultiMap multimap; // �������������� ���� ����_���������
// ---------------
int func_hash(string& key, int vector_size) // ������� ��� ����������� ���������
{
	const int k = 31; // ���������
	int hash_code = 0;
	for (int i = 0; i < key.length(); i++)
	{
		hash_code = hash_code * k % vector_size;
		hash_code += (key[i] - 'A' + 1);
		hash_code %= vector_size;
	}
	return hash_code;
}

void put(string& key, string& value) // ��������� ���������� ��������� � ���������
{
	int hash_key = func_hash(key, multi_map_size); // �������� ����
	for (auto& i : multimap.set[hash_key])
	{
		if (i.key == key) // ����� �� ���� �����
		{
			int hash_values = func_hash(value, set_size); // �������� �������� ��������
			for (auto& j : i.values[hash_key])		// ����
				if (j == value)						// ���� ����� ����-�������� ��� ���� � ����� ���������
					return;							//
			i.values[hash_values].push_back(value); // ����
			return;									// ���� ������ ���� ��� ���� � ���������, �� ������� �������� � �� ���
		}
	}
	// ����: ���� ������� ����-�������� ��� � ����� ���������
	Set* new_set = new Set; // ������ ��������� ����-��������										  
	new_set->key = key;	// ���������� ����									  	  
	new_set->values[func_hash(value, set_size)].push_back(value); // �������� ��������
	multimap.set[hash_key].push_back(*new_set); // �������� ������������ ��. � ����_��.				      
	delete new_set; // ����� ���� ��� �� �������� ���� ��. ������� ���������
}

void deleted(string& key, string& value) // ��������� �������� �������� ��� ������� �����
{
	int hash_key = func_hash(key, multi_map_size); // �������� ����
	for (auto& i : multimap.set[hash_key])							// 
	{																//
		if (i.key == key)											//
		{															// ����
			int hash_value = func_hash(value, set_size);			// ����� ���������� ��������
			for (int j = 0; j < i.values[hash_value].size(); j++)	//
			{														//
				if (i.values[hash_value][j] == value)				//
				{
					i.values[hash_value].erase(i.values[hash_value].begin() + j); // �������� ��������
					return;
				}
			}
		}
	}
}

void deletedAll(string& key) // ��������� �������� ���� �������� ��� ������� �����
{
	int hash_key = func_hash(key, multi_map_size); // �������� ����
	for (auto& i : multimap.set[hash_key])
	{
		if (i.key == key) // ���� ������ ����
		{
			for (auto& j : i.values) // ��������� ���� ��� ��������� �������� �����
			{
				while (!j.empty()) // ���� ��������� �� �����
					j.pop_back(); // ������� ��������� ��������
			}
			return;
		}
	}
}

vector<string> get(string& key) // ������� ������ ���� �������� ��� ������� �����
{
	vector<string> answer; // ������ ������ ��. �������� ��� ������� �����, � ������� ����� ��� �����
	int hash_key = func_hash(key, multi_map_size); // �������� ����
	for (auto& i : multimap.set[hash_key])
	{
		if (i.key == key) // ���� ������ ����
		{
			for (auto& j : i.values) // ��������� ���� ��� ��������� �������� �����
				for (auto& k : j) // ��������� ���� ��� ��������
					answer.push_back(k); // ���������� ��� �������� � �����
			return answer; // ���������� �����
		}
	}
	return answer; // ���������� ������ �����
}

int main() {
	ifstream fin("multimap.in");
	ofstream fout("multimap.out");
	string key;
	string value;
	string com;
	while (!fin.eof())
	{
		fin >> com;
		if (com == "put")
		{
			fin >> key >> value;
			put(key, value);
		}
		if (com == "delete")
		{
			fin >> key >> value;
			deleted(key, value);
		}
		if (com == "deleteall")
		{
			fin >> key;
			deletedAll(key);
		}
		if (com == "get")
		{
			fin >> key;
			vector<string> anw = get(key);
			fout << anw.size() << ' ';
			for (string& i : anw)
				fout << i << ' ';
			fout << endl;
		}

	}
	return 0;
}