#include <fstream>
using namespace std;

struct Element // Структура элемента, которая хранит инфу(data) и адресы на предыдущий и след. элементы
{
	int data;
	Element* prev;
	Element* next;
};

class Queue // Реализация очереди через класс (двухсвязный список)
{
private:
	Element* start; // первый элемент в очереди
	Element* last; // последний элемент в очереди
public:
	Queue() // Конструктор (нужен для автоматической инициализации переменных)
	{
		start = NULL; // присваимаем нулевой адрес первому
		last = NULL; // присваимаем нулевой адрес последниму
	}
	void enqueue(int el) // enqueue - заряжает элемент в очередь
	{
		Element* point = new Element(); // создание нового элемента
		if (start != NULL) // проверка условия
			start->next = point; // указать след. элемент после первого
		else
			last = point; // указать финиш
		point->data = el; // заносим инфу.
		point->prev = start; // указатель на предыдущий элемент теперь является нынешним стартом
		point->next = NULL; // указатель на следующий элемент NULL (т.е. его нет, т.к. нет элемента)
		start = point; // обновляпем старт 
	}
	int dequeue() // dequeue - удаляет эл. из очереди
	{   // (Модификация: функция возвращает резулуьтат так как нам нужно выводить удалённые эл.) 
		int result = last->data; // запоминаем результат
		Element* del = last; // объявляем переменную и привязываем адрес чтоб её потом удалить и очистить память
		last = last->next; // перевести указатель на следующий элемент после последнего
		if (last == NULL) /// Проверка условия
		{
			start = NULL;
		}
		delete del; // удалить адрес
		return result; // возвращаем результат
	}
};

int main()
{
	Queue q;
	ifstream fin("queue.in");
	ofstream fout("queue.out");
	int n;
	fin >> n;
	char command;
	for (int i = 0; i < n; i++)
	{
		fin >> command;
		if (command == '+')
		{
			int number;
			fin >> number;
			q.enqueue(number);
		}
		else
			fout << q.dequeue() << endl;
	}
	return 0;
}