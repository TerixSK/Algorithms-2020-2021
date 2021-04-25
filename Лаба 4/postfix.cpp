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
	getline(fin, str); // �������� ������
	for (int i = 0; str[i] != '\0'; i++) // ���� ������ �� �����������
	{
		if (str[i] >= '0' && str[i] <= '9') // ���� ����� �����
			stack.push((int)str[i] - '0'); // �������� ��� int���� �������������� (����� ������ ��� �������������� str � int)
		else if (str[i] == '+')
			stack.push(stack.pop() + stack.pop()); // �������� ����� ���� ������� ��������� �������
		else if (str[i] == '-')
		{
			int y = stack.pop(); // ��������� ���. ����������, ������ ��� � ��������� ����� �������
			int x = stack.pop();
			stack.push(x - y); // �������� �������� ���� ������� ��������� �������
		}
		else if (str[i] == '*')
			stack.push(stack.pop() * stack.pop()); // �������� ������������ ���� ������� ��������� �������
	}
	fout << stack.pop() << endl; // ����� ������
	fin.close();
	fout.close();
	return 0;
}