#include <fstream>
using namespace std;

struct stack_node // ��������� ��������, ������� ������ ����(data) � ����� �� ����. �������
{
	int data;
	stack_node* next;
};

class Stack // ���������� ����� ����� �����
{
public:
	stack_node* top; // ����� �� ������� �������
	Stack() // ����������� (����� ��� �������������� ������������� ����������)
	{
		top = NULL;
	}
	void push(int el) // push - �������� �������
	{
		stack_node* node = new stack_node(); // ������ ����� �������
		node->next = top; // ����� ���������� �������� �������� �������� ������� 
		node->data = el; // ���������� ����������
		top = node; // ��������� ������� �������
	}
	void pop() // pop - ������� �������
	{
		if (!Empty()) // ���� ������ Empty - true �� �������� (����� ������� ��.)
		{
			stack_node* del = top; // ��������� ���������� � ����������� ����� ���� � ����� ������� � �������� ������
			top = top->next; // ��������� ��������� �� ��������� ������� ����� �������� 
			delete del; // ������� �����
		}
	}
	char getTop() // �������� ������� �������
	{
		return top->data;
	}
	bool Empty() // �������� �� ������� �����
	{
		if (top == NULL) // ���� �������� �������� ���(����� �������)
		{
			return true; // ������� true
		}
		return false;
	}

};

string answer(string str1) // �������� ������� ������ �� ����������
{
	Stack stack;
	for (int i = 0; str1[i] != '\0'; i++) // �������� �������� �� ��� �������, ���� ������ �� �����������
	{
		if (str1[i] == '(' || str1[i] == '[') // ���� �������� �����������, �� �������� � ����
		{
			stack.push(str1[i]);
		}
		else
		{
			if (stack.Empty() == false && ((stack.getTop() == '[' && str1[i] == ']') || (stack.getTop() == '(' && str1[i] == ')')))
			{
				stack.pop(); // ���� ���� �� ���� � ���� ������ ����������� � �������� ��� �������,
			} //                                                                           �� ������� ������� ������� �� �����
			else
			{
				return "NO"; //  ���� if �� ���., �� ������������������ �� ������ ��� �� ����������
			}

		}
	}
	if (stack.Empty()) // �������� �� ������� �����
	{
		return "YES"; // ���� ����, �� ��� ������ ������������ �������
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
	while (fin >> str) //  ������������� �������� ������� ��� ��� �����
	{
		fout << answer(str) << endl;
	}
	fin.close();
	fout.close();
	return 0;
}