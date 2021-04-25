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

int func_hash(const string& word) // ������� ��� ������������ ���������
{
    int hash = 0;
    int k = 41; // ���������
    for (int i = 0; i < word.size(); i++)
    {
        int s = 0;
        if (word[i] - 'a' >= 0 && word[i] - 'a' <= 9)
            s = word[i] - 'a';
        else
            s = word[i] - 'A';
        hash = (hash + ((s + 1) * k) % 1000000) % 1000000;
        k = (k * 41) % 1000000;
    }
    return hash;
}

void put(vector<vector<Key>>& hash_table, const string& key, const string& word) // ������� ���������� �������� � ���-�������
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
void get(vector<vector<Key>>& hash_table, const string& key) // ������� ��� ������ ��������
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
void deleted(vector<vector<Key>>& hash_table, const string& key) // ������� �������� �������� �� ���-�������
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
int main()
{
    vector<vector<Key>> hash_table(10000001, vector<Key>());
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