#include <fstream>
#include <vector>

using namespace std;

ifstream fin("map.in"); // Пишем это тут, поскольку функция get выводит значения в файл
ofstream fout("map.out");

struct Key // Создаём структуру для хранения даннных ассоциативного массива
{
	string x;
	string y;
};

int func_hash(string& word) // Функция для хешированиея элементов
{
	int hash = 0; // Формула для хеширования: hash = (char1*k^0 + char2*k^1 + char3*k^2 + ... + charn*k^n) % hash_table.size()
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

void put(vector<vector<Key>>& hash_table, string& key, string& word) // Функция добовления элемента в хеш-таблицу
{
	int hash = func_hash(key);
	for (auto& i : hash_table[hash]) // foreach - выполняет итерацию по каждому элементу в массиве  
	{
		if (i.x == key) // поверяем есть ли это ключ в нашей хеш таблице
		{
			i.y = word;
			return;
		}
	}
	hash_table[hash].push_back({ key, word }); // заряжаем ключ и значение для нужного хеша
}

void deleted(vector< vector<Key> >& hash_table, string& key) // Функция удаления элемента из хеш-таблицы
{
	int hash = func_hash(key);
	for (int i = 0; i < hash_table[hash].size(); i++)
	{
		if (hash_table[hash][i].x == key) // Ищем нужный ключ
		{
			hash_table[hash].erase(hash_table[hash].begin() + i); // удаляем его
			return;
		}
	}
}

void get(vector<vector<Key>>& hash_table, string key) // Функция для поиска значения
{
	int hash = func_hash(key); // foreach - выполняет итерацию по каждому элементу в массиве
	for (auto& i : hash_table[hash]) // поиск по хешу
	{
		if (i.x == key) // если нашли нужный ключ
		{
			fout << i.y << endl; // выводим значение
			return;
		}
	}
	fout << "none" << endl; // если не нашли, выводим none
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