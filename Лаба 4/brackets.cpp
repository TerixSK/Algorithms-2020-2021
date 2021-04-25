#include <fstream>
using namespace std;

struct stack_node // Структура элемента, которая хранит инфу(data) и адрес на след. элемент
{
	int data;
	stack_node* next;
};

class Stack // Реализация стека через класс
{
public:
	stack_node* top; // адрес на верхний элемент
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
	void pop() // pop - удаляет элемент
	{
		if (!Empty()) // Если функия Empty - true то работаем (можем удалять эл.)
		{
			stack_node* del = top; // объявляем переменную и привязываем адрес чтоб её потом удалить и очистить память
			top = top->next; // перевести указатель на следующий элемент после верхнего 
			delete del; // удалить адрес
		}
	}
	char getTop() // получить верхний элемент
	{
		return top->data;
	}
	bool Empty() // Проверка на пустоту стека
	{
		if (top == NULL) // если верхнего элемента нет(равен пустоте)
		{
			return true; // выводим true
		}
		return false;
	}

};

string answer(string str1) // Основная функция работы со скобочками
{
	Stack stack;
	for (int i = 0; str1[i] != '\0'; i++) // проверка символов до той степени, пока строка не закончиться
	{
		if (str1[i] == '(' || str1[i] == '[') // если скобочка открывается, то харяжаем в стек
		{
			stack.push(str1[i]);
		}
		else
		{
			if (stack.Empty() == false && ((stack.getTop() == '[' && str1[i] == ']') || (stack.getTop() == '(' && str1[i] == ')')))
			{
				stack.pop(); // если стек не пуст и если скобка закрывается и подходит под условие,
			} //                                                                           то удаляем верхний элемент из стека
			else
			{
				return "NO"; //  если if не вып., то последовательность из скобок уже не правильная
			}

		}
	}
	if (stack.Empty()) // проверка на пустоту стека
	{
		return "YES"; // если пуст, то все скобки соответсвуют условию
	}
	else
	{
		return "NO";
	}
}

int main()
{
	ifstream fin("brackets.in");
	ofstream fout("brackets.out");
	string str;
	while (fin >> str) //  Использовании основной функции для всёх строк
	{
		fout << answer(str) << endl;
	}
	fin.close();
	fout.close();
	return 0;
}