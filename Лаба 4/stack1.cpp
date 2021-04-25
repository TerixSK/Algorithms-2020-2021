#include <fstream>
using namespace std;

struct stack_node // ��������� ��������, ������� ������ ����(data) � ����� �� ����. �������
{
	int data;
	stack_node* next;
};

class Stack // ���������� ����� ����� �����
{
private:
	stack_node* top; // ����� �� ������� �������
public:
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
	int pop() // pop - ������� ������� (�����������: ������� ���������� ���������� ��� ��� ��� ����� �������� �������� ��.) 
	{
		int result = top->data; // ���������� ���������
		stack_node* del = top; // ��������� ���������� � ����������� ����� ���� � ����� ������� � �������� ������
		top = top->next; // ��������� ��������� �� ��������� ������� ����� �������� 
		delete del; // ������� �����
		return result; // ���������� ���������
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
/* -> �������� ��, ��� ����� ������, �� ������� � ���� ��������� � ������� ������ ������� ���� ���������.
� ������� node->next = *top �� �� ����� ������ ������� ��������� �� ��������� ������� *next � �������� ��� �� ���������,
������� ��������� �� ������� ����� *top. ������� ������� �� �������� �����, �� ������ �������� � ������� �����.

*/