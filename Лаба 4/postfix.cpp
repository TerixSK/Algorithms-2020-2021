#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct StackNode
{
	int info;
	StackNode* next;
};

class Stack
{
private:
	StackNode* top;
public:
	Stack()
	{
		top = NULL;
	}

	void push(int elem)
	{
		StackNode* node = new StackNode();
		node->next = top;
		node->info = elem;
		top = node;
	}

	int pop()
	{
		int result = top->info;
		StackNode* del = top;
		top = top->next;
		delete del;
		return result;
	}
};

int main()
{
	Stack stack;
	ifstream fin("postfix.in");
	ofstream fout("postfix.out");
	string str;
	getline(fin, str); // заряжаем строку
	for (int i = 0; str[i] != '\0'; i++) // Пока строка не закончиться
	{
		if (str[i] >= '0' && str[i] <= '9') // если сивол цифра
			stack.push((int)str[i] - '0'); // заряжаем его intовое предстовеление (минус должен для преобразования str в int)
		else if (str[i] == '+')
			stack.push(stack.pop() + stack.pop()); // заряжаем сумму двух верхних элементов очереди
		else if (str[i] == '-')
		{
			int y = stack.pop(); // исползуем доп. переменные, потому что в вычитании важен порядок
			int x = stack.pop();
			stack.push(x - y); // заряжаем разность двух верхних элементов очереди
		}
		else if (str[i] == '*')
			stack.push(stack.pop() * stack.pop()); // заряжаем произведение двух верхних элементов очереди
	}
	fout << stack.pop() << endl; // вывод ответа
	fin.close();
	fout.close();
	return 0;
}