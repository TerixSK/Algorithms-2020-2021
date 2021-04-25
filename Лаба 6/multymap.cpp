#include <fstream>
#include <vector>

using namespace std;

// Задаём размеры mainМножества и множества ключ-значений
int multi_map_size = 100001;
int set_size = 1001;

struct Set // Создаём множество, которое будеи хранить
{
	string key; // ключ
	vector < vector <string>> values; // и множество значений
	Set()
	{
		values.resize(set_size); // задаём размер множеству значений
	}
};
struct MultiMap // Создаём мейн_множество, которое будет хранить множество set
{
	vector< vector<Set> > set;
	MultiMap()
	{
		set.resize(multi_map_size); // задаём размер множеству
	}
};
// ---------------
MultiMap multimap; // инициализируем наше мейн_множество
// ---------------
int func_hash(string& key, int vector_size) // Функция для хеширование элементов
{
	const int k = 31; // константа
	int hash_code = 0;
	for (int i = 0; i < key.length(); i++)
	{
		hash_code = hash_code * k % vector_size;
		hash_code += (key[i] - 'A' + 1);
		hash_code %= vector_size;
	}
	return hash_code;
}

void put(string& key, string& value) // Процедура добовление элементов в множество
{
	int hash_key = func_hash(key, multi_map_size); // хешируем ключ
	for (auto& i : multimap.set[hash_key])
	{
		if (i.key == key) // поиск по хешу ключа
		{
			int hash_values = func_hash(value, set_size); // хешируем значение элемента
			for (auto& j : i.values[hash_key])		// Блок
				if (j == value)						// Если такое ключ-значение уже есть в нашем множестве
					return;							//
			i.values[hash_values].push_back(value); // Блок
			return;									// Если данный ключ уже есть в множестве, но данного значения в нём нет
		}
	}
	// Блок: если данного ключ-значения нет в нашем множестве
	Set* new_set = new Set; // создаём множество ключ-значений										  
	new_set->key = key;	// записываем ключ									  	  
	new_set->values[func_hash(value, set_size)].push_back(value); // заряжаем значение
	multimap.set[hash_key].push_back(*new_set); // заряжаем получившиеся мн. в мейн_мн.				      
	delete new_set; // после того как мы зарядили наше мн. удаляем структуру
}

void deleted(string& key, string& value) // Процедура удаления значения для данного ключа
{
	int hash_key = func_hash(key, multi_map_size); // хешируем ключ
	for (auto& i : multimap.set[hash_key])							// 
	{																//
		if (i.key == key)											//
		{															// Блок
			int hash_value = func_hash(value, set_size);			// Поиск удаляемого значения
			for (int j = 0; j < i.values[hash_value].size(); j++)	//
			{														//
				if (i.values[hash_value][j] == value)				//
				{
					i.values[hash_value].erase(i.values[hash_value].begin() + j); // удаление значения
					return;
				}
			}
		}
	}
}

void deletedAll(string& key) // Процедура удаления всех значений для данного ключа
{
	int hash_key = func_hash(key, multi_map_size); // хешируем ключ
	for (auto& i : multimap.set[hash_key])
	{
		if (i.key == key) // ищем данный ключ
		{
			for (auto& j : i.values) // запускаем цикл для множества значений ключа
			{
				while (!j.empty()) // пока множество не пусто
					j.pop_back(); // удаляем последнее значение
			}
			return;
		}
	}
}

vector<string> get(string& key) // Функция поиска всех значений для данного ключа
{
	vector<string> answer; // создаём пустое мн. значений для данного ключа, в который вернём как ответ
	int hash_key = func_hash(key, multi_map_size); // хешируем ключ
	for (auto& i : multimap.set[hash_key])
	{
		if (i.key == key) // ищем данный ключ
		{
			for (auto& j : i.values) // запускаем цикл для множества значений ключа
				for (auto& k : j) // запускаем цикл для значений
					answer.push_back(k); // записываем все значения в ответ
			return answer; // возвращаем ответ
		}
	}
	return answer; // возвращаем пустой ответ
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