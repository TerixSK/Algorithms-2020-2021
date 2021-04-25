#include <fstream>
using namespace std;

struct Element // ��������� ��������, ������� ������ ����(data) � ������ �� ���������� � ����. ��������
{
	int data;
	Element* prev;
	Element* next;
};

class Queue // ���������� ������� ����� ����� (����������� ������)
{
private:
	Element* start; // ������ ������� � �������
	Element* last; // ��������� ������� � �������
public:
	Queue() // ����������� (����� ��� �������������� ������������� ����������)
	{
		start = NULL; // ����������� ������� ����� �������
		last = NULL; // ����������� ������� ����� ����������
	}
	void enqueue(int el) // enqueue - �������� ������� � �������
	{
		Element* point = new Element(); // �������� ������ ��������
		if (start != NULL) // �������� �������
			start->next = point; // ������� ����. ������� ����� �������
		else
			last = point; // ������� �����
		point->data = el; // ������� ����.
		point->prev = start; // ��������� �� ���������� ������� ������ �������� �������� �������
		point->next = NULL; // ��������� �� ��������� ������� NULL (�.�. ��� ���, �.�. ��� ��������)
		start = point; // ���������� ����� 
	}
	int dequeue() // dequeue - ������� ��. �� �������
	{   // (�����������: ������� ���������� ���������� ��� ��� ��� ����� �������� �������� ��.) 
		int result = last->data; // ���������� ���������
		Element* del = last; // ��������� ���������� � ����������� ����� ���� � ����� ������� � �������� ������
		last = last->next; // ��������� ��������� �� ��������� ������� ����� ����������
		if (last == NULL) /// �������� �������
		{
			start = NULL;
		}
		delete del; // ������� �����
		return result; // ���������� ���������
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