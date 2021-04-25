#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

struct Label // ������ ��������� ��� ����� �����, ������� �������� 
{
    string name; // ���� ������
    int num; // � ��������
};

int main()
{
    ifstream fin("quack.in");
    ofstream fout("quack.out");
    vector <string> a;
    vector <Label> label; // ������ �����
    queue < > Queue; // ��������� �������
    unsigned short int registers[26]; // ��������� �������
    for (int i = 0; i < 26; i++)
        registers[i] = 0; // ����������� ���� ������ ������� ����
    while (!fin.eof()) // ��������� ���� ���� �� ��������� �������� ����
    {
        string com;
        fin >> com;
        a.push_back(com); // �������� ���� ������� � ������
        if (com[0] == ':')
        {
            string name = com;
            name.erase(0, 1); // ������� ������ ������ ������ (�� ��� �������� ������� erase)
            label.push_back({ name, (int)a.size() - 1 }); // �������� � ������� 
        }
    }
    int i = 0; // ������ ������� ��� while
    while (i < a.size()) // ��������� ���� ���� �� �������� �� ���� ��������
    {
        // ������ ��� ������� ��. ������� => ������� �� => �������� ����������� �������� => ��������� �������� � �������
        if (a[i][0] == '-')
        {   // unsigned - ����������� �����
            unsigned short int x = Queue.front(); // ���������� ������ ������� � �������
            Queue.pop(); // �������
            unsigned short int y = Queue.front(); // front - ���������� ������ �� ������ ������� �������
            Queue.pop(); // �� �� �������� �������� � ��������� ������
            Queue.push((x - y) % 65536); // ��������� �������� �������� � ����
        }
        // ������ ��� ������� ��. ������� => ������� �� => �������� ����������� �������� => ��������� �������� � �������
        else if (a[i][0] == '+')
        {
            unsigned short int x = Queue.front();
            Queue.pop();
            unsigned short int y = Queue.front();
            Queue.pop();
            Queue.push((x + y) % 65536);
        }
        // ������ ��� ������� ��. ������� => ������� �� => �������� ����������� �������� => ��������� �������� � �������
        else if (a[i][0] == '*')
        {
            unsigned short int x = Queue.front();
            Queue.pop();
            unsigned short int y = Queue.front();
            Queue.pop();
            Queue.push((x * y) % 65536);
        }
        // ������ ��� ������� ��. ������� => ������� �� => �������� ����������� �������� => ��������� �������� � �������
        else if (a[i][0] == '%')
        {
            unsigned short int x = Queue.front();
            Queue.pop();
            unsigned short int y = Queue.front();
            Queue.pop();
            if (y == 0) // �������� ������� �� ������� �� ���� -  ��� ����, ��
                Queue.push(0); // �������� ����
            else
                Queue.push(x % y); // ����� �������� ��������� ��������
        }
        // ������ ��� ������� ��. ������� => ������� �� => �������� ����������� �������� => ��������� �������� � �������
        else if (a[i][0] == '/')
        {
            unsigned short int x = Queue.front();
            Queue.pop();
            unsigned short int y = Queue.front();
            Queue.pop();
            if (y == 0) // ������������� ������, ����� ������ - ��� ����
                Queue.push(0);
            else
                Queue.push(x / y);
        }

        else if (a[i][0] == '>')
        {
            unsigned short int x = Queue.front();
            Queue.pop(); // ������� ��. �� �������
            registers[(int)a[i][1] - (int)'a'] = x; // �������� �������� ��. � ��������
        }
        else if (a[i][0] == '<') // ���� �������� �� ��������
            Queue.push(registers[(int)a[i][1] - (int)'a']);
        else if (a[i][0] == 'P')
        {
            if (a[i].size() == 1) // ���� ����� � ������������ ������ � ������
            {
                fout << Queue.front() << "\n"; // ������� ��. ������� �� � ����������� ������
                Queue.pop();
            }
            else
            {
                fout << registers[(int)a[i][1] - (int)'a'] << "\n"; // ������� �������� �� ��������
            }
        }
        else if (a[i][0] == 'C') // ������ ����� �� �� �����, ��� � '�', ������ ������� ����� ��� ������
        {
            if (a[i].size() == 1)
            {
                fout << (char)(Queue.front() % 256);
                Queue.pop();
            }
            else
            {
                fout << (char)(registers[(int)a[i][1] - (int)'a'] % 256);
            }
        }
        else if (a[i][0] == 'J') // ��� ������� ������������ ������� �� ������ � ������
        {
            string str = a[i]; // ���������� ������� � ������
            str.erase(0, 1); // �������� ����� J
            for (int j = 0; j < label.size(); j++) // ���� � ������ ������
                if (label[j].name == str)
                {
                    i = label[j].num; // ��� ������ ������� ������� ����� ����������� ����� ������� ����� 
                    break; // ���������� �����
                }
        }
        else if (a[i][0] == 'Z') // ���� �������� �������� = 0, �� ���������� ��������� ������������ � �����
        {
            if (registers[(int)a[i][1] - (int)'a'] == 0) // ��������� ����� �� ������� ����
            {
                string str = a[i]; // ������ �������
                str.erase(0, 2); // �������� ������ ��� ������
                for (int j = 0; j < label.size(); j++)
                    if (label[j].name == str) // ���� � ������ ������
                    {
                        i = label[j].num; // ��� ������ ������� ������� ����� ����������� ����� ������� ����� 
                        break; // ���������� �����
                    }
            }
        }
        else if (a[i][0] == 'E') // ���� �������� ���� ��������� �����, �� ���������� ��������� ������������ � �����
        {
            if (registers[(int)a[i][1] - (int)'a'] == registers[(int)a[i][2] - (int)'a']) // �������� �� �������� ���������
            {
                string str = a[i];
                str.erase(0, 3); // �������� ��� ������ ������ �������
                for (int j = 0; j < label.size(); j++)
                    if (label[j].name == str) // ���� � ������ ������
                    {
                        i = label[j].num; // ��� ������ ������� ������� ����� ����������� ����� ������� ����� 
                        break; // ���������� �����
                    }
            }
        }
        else if (a[i][0] == 'G') // ���� �������� ������� �������� ������ �������� �������, �� ���������� ��������� ������������ � �����
        {
            if (registers[(int)a[i][1] - (int)'a'] > registers[(int)a[i][2] - (int)'a']) // �������� ��������, ����������� ����
            {
                string str = a[i];
                str.erase(0, 3); // �������� ��� ������ ������ �������
                for (int j = 0; j < label.size(); j++)
                    if (label[j].name == str) // ���� � ������ ������
                    {
                        i = label[j].num; // ��� ������ ������� ������� ����� ����������� ����� ������� ����� 
                        break; // ���������� �����
                    }
            }
        }
        else if (a[i][0] == 'Q') // ���������� ������ ���������
            break;
        else if (a[i][0] >= '0' && a[i][0] <= '9') // ���� ��������� ������� �����
        {
            unsigned short int element = 0;
            for (int j = 0; j < a[i].size(); j++)
                element = element * 10 + (int)a[i][j] - (int)'0';
            Queue.push(element);
        }
        i++; // ��������� � �������� + 1 ��� ����������� ������ ������
    }
    fin.close();
    fout.close();
    return 0;
}
