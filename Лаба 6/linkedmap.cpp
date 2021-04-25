#include <vector>
#include <fstream>
// * возвращает значения ячёки памяти, а & возвращает адрес ячейки памяти
using namespace std;

struct Element // Создаём структуру для элемента, которая будет хранить  
{
	string key; // ключ
	string value; // значение
	Element* next; // указатель на след. элемент
	Element* prev; // указатель на предыдущий элемент
	Element* next_queue; // указатель на след. элемент в цепочке
};

class LinkedMap
{
private:
	Element* list;
public:
	LinkedMap() // Конструктор (вызывается при объявлении переменной)
	{
		list = new Element(); // создаём новый элемент
		list->value = list->key = ""; // записываем в ключ и в значение пустую строку
		list->next_queue = NULL; // адресу следующего элемента в цепочке ставим NULL
	}
	void Insert(string& key, string& value, Element* head) // МЕТОД ВСТАВКИ ЭЛЕМЕНТА
	{
		Element* new_el = Search(key); // находим адрес элемента по ключу
		if (Search(key) == NULL) // если такого эелемента не существует, то создаём новый
		{
			new_el = new Element; // объявляем новую переменную для вызова конструктора
			new_el->key = key; // заносим ключ
			new_el->value = value; // заносим значение
			new_el->next_queue = list->next_queue; // переводим адрес следующего в цепочке
			list->next_queue = new_el; // обвноляем адрес следующего в цепочке
			Element* tail = head->prev; // объявляем переменную конца списка и присвиваем адрес прыдыдущего перед началом
			tail->next = new_el; // обновляем адрес следующего элемента
			head->prev = new_el; // обновляем адрес предыдущего элемента
			new_el->next = head; // ставим адрес следующего элемента
			new_el->prev = tail; // ставим адрес предыдущего элемента
		}
		else // если элемент не найден
			new_el->value = value; // то перезаписываем значение
	}
	void Deleted(string key) // МЕТОД УДАЛЕНИЯ ЭЛЕМЕНТА
	{
		Element* cur_el = list; // ставим адрес на начало списка

		while (cur_el->next_queue != NULL) // перебираем все адреса списка
		{
			if (cur_el->next_queue->key == key) // если нашли нужный элемент
			{
				Element* del = cur_el->next_queue; // запоминаем адрес
				cur_el->next_queue = cur_el->next_queue->next_queue; // переводим адрес на следующий
				Element* prev_el = del->prev, * next_el = del->next; // запоминаем адреса предыдущего/следующего
				del->prev->next = next_el; // заносим адрес следующего
				del->next->prev = prev_el; // заносим адрес предыдущего
				delete del; // удаляем элемент
				break;
			}
			else
				cur_el = cur_el->next_queue; // иначе, переходим к следующему адресу (элементу списка)
		}
	}
	Element* Search(string& key) // МЕТОД ПОИСКА АДРЕСА ЭЛ. ПО КЛЮЧУ
	{
		Element* cur_el = list; // начинаем с начального адреса элемента
		while (cur_el->next_queue != NULL) // до того момента пока адрес след. эл. не равен NULL
		{
			if (cur_el->next_queue->key == key) // если нашли элемент
				return cur_el->next_queue; // возвращаем его
			else
				cur_el = cur_el->next_queue; // иначе, переходим к след. элементу
		}
		return NULL; // если ничего не нашли, то нужного эл. нет
	}
};

class UpgradeLinkedMap // класс для оптимизации работы через массив
{
private:
	LinkedMap hash_table[100001];
	Element* head; // адрес начального/конечно элемента ("головы" списка)
public:
	UpgradeLinkedMap() // Конструктор
	{
		head = new Element; // объявляем переменную
		head->next = head->prev = head; // присваиваем предыдещму и следующему элементу один адрес
		head->value = head->key = "HEAD"; // присваиваем ключу и значению строку "HEAD"
	}
	int func_hash(string key) // Метод для хеширования
	{
		int hash = 0; // результат
		int pow = 1; // степень
		int k = 31; // константа
		for (int i = 0; i < key.length(); i++)
		{
			hash += (key[i] - 'A') * pow;
			pow *= k;
		}
		return abs(hash % 100001); // возвращаем остаток от деления результата на макс. кол-во элементов в массиве
	}
	void put(string key, string value) // Метод добавления элемента
	{
		int hash = func_hash(key);
		hash_table[hash].Insert(key, value, head);
	}
	string get(string key) // Метод получения значения в элементе
	{
		int hash = func_hash(key);
		Element* result = hash_table[hash].Search(key); // Находим элемент по ключу
		if (result == NULL) // если такого элемента нет
			return "none"; // то возвращаем "none"
		else
			return result->value; // иначе возвращаем значение которое хранится по этому адресу
	}
	void deleted(string key) // Метод удаления элемента
	{
		int hash = func_hash(key);
		hash_table[hash].Deleted(key);
	}
	string next(string key) // Метод получения значения следующего элемента
	{
		int hash = func_hash(key);
		Element* result = hash_table[hash].Search(key); // находим адрес элемента
		if (result == NULL || result->next == head) // если адрес текущего элемента равен NULL или адрес следующего элемента равен адресу Head
			return "none"; // то  возвращаем "none"
		else //иначе
			return result->next->value; // возвращаем значение следующего элемента
	}
	string prev(string key) // Метод получения значения предыдущего элемента
	{
		int hash = func_hash(key);
		Element* result = hash_table[hash].Search(key); // находим адрес элемента по ключу
		if (result == NULL || result->prev == head) // если адрес текущего элемента равен NULL или адрес предыдущего равен адресу Head
			return "none"; // то возвращаем "none"
		else // иначе
			return result->prev->value; // возвращаем значение предыдущего элемента
	}
};

int main()
{
	ifstream fin("linkedmap.in");
	ofstream fout("linkedmap.out");
	string key;
	string value;
	string com;
	UpgradeLinkedMap map;
	while (fin >> com)
	{
		if (com == "put")
		{
			fin >> key >> value;
			map.put(key, value);
		}
		else if (com == "delete")
		{
			fin >> key;
			map.deleted(key);
		}
		else if (com == "get")
		{
			fin >> key;
			fout << map.get(key) << endl;
		}
		else if (com == "next")
		{
			fin >> key;
			fout << map.next(key) << endl;
		}
		else if (com == "prev")
		{
			fin >> key;
			fout << map.prev(key) << endl;
		}
	}
	return 0;
}