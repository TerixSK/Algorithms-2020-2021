#include <fstream>
#include <string>

using namespace std;

struct element // ������ �������� ��� ��������� ���. ������ ������
{
    int value; // ���� �����
    element* parent; // ��������� �� ��������
    element* left; // ��������� �� ������ ������
    element* right; // ��������� �� ������� ������
};

class BinTreeSearch // ������ ����� 
{
private:
    element* root = NULL; // ������ �������, �� �� ������ ����� �������
public:

    element* Search(int x) // ����� �������� � ���. ������ ������
    {
        element* current_el = root; // ������� ��. ����� �����
        while (current_el != NULL && x != current_el->value) // ��������� while ���� �� ����� �������� ��. ��� �������, ��� ������ ��. � ������ ���
        {
            if (x < current_el->value)          // }
                current_el = current_el->left;  // } ������������ ����� �������� ����� � ����� ��� � ������ ���������
            else                                // }
                current_el = current_el->right; // }
        }
        return current_el; // ���������� ��������� ��������
    }

    void Insert(int x) // �������, ������� �������� �������
    {
        if (Check_el(x)) // �������� ��������� �� ���������� �������
            return;
        element* new_el = new element; // ������ ����� ����� � ����� ������ 
        new_el->value = x;             // }
        new_el->parent = NULL;         // } ��������� �������� ��� ������ ��������
        new_el->left = NULL;           // }
        new_el->right = NULL;          // }
        element* current_el = root; // ������ ��������� ��� �������� ��.
        // ������ (���� ����� ��� ������ ������ ��������)
        while (current_el != NULL)                 // ���� ������� > ������, �� ���� ����� ����� ������� ��.(������ ��� ����� �������)                
        {
            new_el->parent = current_el;
            if (new_el->value < current_el->value)
                current_el = current_el->left;
            else
                current_el = current_el->right;   //          
        }
        if (new_el->parent == NULL) // ���� ������ �����, �� ����� ��. ������ ������
            root = new_el;          //                       
        else
        {
            if (new_el->value < new_el->parent->value) // ���� ������� < ������, �� ���� ����� ����� ����� ��.(������ ��� ����� �������)     
                new_el->parent->left = new_el;
            else
                new_el->parent->right = new_el;
        }
        // ����� (���� ����� ��� ������ ������ ��������)
    }

    void Delete(int x) // �������, ������� �������� ��������
    {
        element* del_el = Search(x); // ���� ������ ��� �������
        if (del_el == NULL) // ���� ������� ��� �������� ���
        {
            return;
        }
        element* previous_el; // ��������� ��� ����������� ��.
        element* hepl_el; // ��������� ��� ���������������� ��.
        if (del_el->left == NULL || del_el->right == NULL) // ���� � ���������� ��. ��� �����
            previous_el = del_el; // �� ���������� ����������� ����� ������������
        else
            previous_el = Next(x); // ����� ���� ���. > x 
        if (previous_el->left != NULL) // ���� ����� ������ �� ����� �������
            hepl_el = previous_el->left;
        else
            hepl_el = previous_el->right;
        if (hepl_el != NULL) // ���� ��������������� ��. �� ����� �������
            hepl_el->parent = previous_el->parent;
        if (previous_el->parent == NULL) // ���� �������� ����� �������
            root = hepl_el;
        else
        {
            if (previous_el == previous_el->parent->left)
                previous_el->parent->left = hepl_el;
            else
                previous_el->parent->right = hepl_el;
        }
        if (previous_el != del_el) // �� ����� ���� ���������� ��. �� ����� ����������
            del_el->value = previous_el->value; // ��������� ����������� ����������
        delete previous_el; // � ������� ��������� �������
    }

    bool Check_el(int x) // �������� ����� �� ������ ��� ������� �������
    {
        return Search(x) != NULL; // ���������� true ��� false
    }

    element* Next(int x) // ������� ���������� ����������� ��. > x ��� none(���� ������ ���)
    {
        element* current_el = root;   // ������� ������� ����� �����
        element* successor_el = NULL; // ��������� - �������
        // ������ (���� ������ �������, ��������� �������)
        while (current_el != NULL)
        {
            if (current_el->value > x) // �������� �������
            {
                successor_el = current_el;
                current_el = current_el->left;
            }
            else
                current_el = current_el->right;
        }
        // ����� (���� ������ �������, ��������� �������)
        return successor_el; // ���������� ��������
    }

    element* Previous(int x) // ������� ���������� ������������ ��. < x ��� none(���� ������ ���)
    {
        element* current_el = root; // ������� ��. ����� �����
        element* previous_el = NULL; // ���������� - �������
        // ������ (���� ������ �������, ��������� �������)
        while (current_el != NULL)
        {
            if (current_el->value < x) // �������� �������
            {
                previous_el = current_el;
                current_el = current_el->right;
            }
            else
                current_el = current_el->left;
        }
        // ����� (���� ������ �������, ��������� �������)
        return previous_el;
    }
};

int main()
{
    ifstream fin("bstsimple.in");
    ofstream fout("bstsimple.out");
    BinTreeSearch tree;
    string command;
    int key;
    while (fin >> command >> key)
    {
        if (command == "insert")            // }
            tree.Insert(key);               // }
        if (command == "delete")            // }
            tree.Delete(key);               // }
        if (command == "exists")            // }
        {                                   // }
            if (tree.Search(key))           // }
                fout << "true\n";           // }
            else                            // }
                fout << "false\n";          // }
        }                                   // }     ���� ������ ������� � ���������� ��
        if (command == "next")              // }
        {                                   // }
            element* res = tree.Next(key);  // }
            if (res == NULL)                // }
                fout << "none\n";           // }
            else                            // }
                fout << res->value << "\n"; // }
        }                                   // }
        if (command == "prev")              // }
        {                                   // }
            element* res = tree.Previous(key); // }
            if (res == NULL)                   // }
                fout << "none\n";              // }
            else                               // }
                fout << res->value << "\n";    // }
        }
    }
    fin.close();
    fout.close();
    return 0;
}
