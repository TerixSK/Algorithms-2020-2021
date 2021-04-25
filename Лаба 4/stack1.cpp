#include <fstream>
using namespace std;

struct stack_node // Структура элемента, которая хранит инфу(data) и адрес на след. элемент
{
	int data;
	stack_node* next;
};

class Stack // Реализация стека через класс
{
private:
	stack_node* top; // адрес на верхний элемент
public:
	Stack() // Конструктор (нужен для автоматической инициализации переменных)
	{
		top = NULL;
	}
	void push(int el) // push - заряжает элемент
	{
		stack_node* node = new stack_node(); // создаём новый элемент
		node->next = top; // адрес следующего элемента является нынешняя вершина 
		node->data = el; // записываем информацию
		top = node; // обновляем верхний элемент
	}
	int pop() // pop - удаляет элемент (Модификация: функция возвращает резулуьтат так как нам нужно выводить удалённые эл.) 
	{
		int result = top->data; // запоминаем результат
		stack_node* del = top; // объявляем переменную и привязываем адрес чтоб её потом удалить и очистить память
		top = top->next; // перевести указатель на следующий элемент после верхнего 
		delete del; // удалить адрес
		return result; // возвращаем результат
	}
};

int main()
{
	Stack stack;
	ifstream fin("stack.in");
	ofstream fout("stack.out");
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
			stack.push(number);
		}
		else
			fout << stack.pop() << endl;
	}
}
/* -> означает то, что грубо говоря, мы заходим в нашу структуру и достаем оттуда элемент этой структуры.
В строчке node->next = *top мы из нашей ячейки достаем указатель на следующий элемент *next и заменяем его на указатель,
который указывает на вершину стека *top. Другими словами мы проводим связь, от нового элемента к вершине стека.

*/