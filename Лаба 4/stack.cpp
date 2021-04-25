#include <fstream>
using namespace std;

struct Stack
{
    int data; // ������
    Stack* next; // ��������� �� ����. �������
};

// ������� ��������� ��������� �� ������� ����� � ����������, ������� �� ����� ���������� � ������
void stack_push(Stack** top, int el) // el - �������
{
    Stack* new_el; // ������ ����� �������
    new_el = new Stack(); // ���������� ����������� ����� � data
    new_el->data = el;
    if (top == NULL) // ���� ������� ���, �� ����� ������� ����� ��������
        *top = new_el;
    else
    {
        new_el->next = *top; // ����� ����� ��. �� �������
        *top = new_el; // ������ ����� ������ ���� ��������
    }
}

//������� ������� ��������� ������� top � ����� ������� ����� �������
void stack_delete(Stack** top, int key)
{
    Stack* new_el = *top;
    Stack* previous = NULL; //������� ��������� �� ���������� �������, � ������ �� ����� ������
    while (new_el != NULL) // ���� ��������� �� ������ �� ����� ��������� ��� � �����
    {
        if (new_el->data == key) //���� data �������� ����� key
        {
            if (new_el == *top) // ���� ������� ����� key
            {
                *top = new_el->next;
                free(new_el);
                new_el->data = NULL; //�������� ����������
                new_el->next = NULL;
            }
            else
            {
                previous->next = new_el->next;
                free(new_el);
                new_el->data = NULL; //�������� ����������
                new_el->next = NULL;
            }
        }// ���� data �������� �� ����� �����, ������� ��� ����� �������
        previous = new_el;
        new_el = new_el->next; //���������� ��������� new_el �� ��������� �������
    }
}

int main()
{
    ifstream fin("stack.in");
    ofstream fout("stack.out");

    long n;
    fin >> n;
    char command;
    long a;
    Stack* top = NULL; // � ������ ��������� � ��� ��� �������, �������������� ������� ���, ���� �� �������� NULL
    for (int i = 0; i < n; i++)
    {
        fin >> command;
        if (command == '+')
        {
            fin >> a;
            stack_push(&top, a);
        }
        else
        {
            stack_delete(&top, a);
            fout << a << "\n";
        }
    }

    fin.close();
    fout.close();
    return 0;
}
