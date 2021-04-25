#include <fstream>
#include <vector>
#include <string>

using namespace std;

int func_hash(int x) // Функция для хеширования элемента
{
    return x = abs(x % 100001);
}

int exists(vector< vector<int> >& hash_table, int x) // Проверка на то есть ли элемент в хеш-таблице
{
    int hash = func_hash(x);
    for (int i : hash_table[hash]) // forarche - происходит итерация на каждый элемент в массиве
    {
        if (i == x)
            return 0; // 0 - числе есть в хеш-таблице
    }
    return 1; // 1 - числа нет в хеш-таблице
}

void insert(vector< vector<int> >& hash_table, int x) // Функция для добовления элемента в хеш-таблицу
{
    int hash = func_hash(x);
    if (exists(hash_table, x) == 1) // если числа ещё нет в нашей хеш-таблице добовляем его
        hash_table[hash].push_back(x);
}

void deleted(vector< vector<int> >& hash_table, int x) // Функция для удаления элемента из хеш-таблицы
{
    int hash = func_hash(x);
    for (int i = 0; i < hash_table[hash].size(); i++)
    {
        if (hash_table[hash][i] == x) // ищем удаляемое число
        {
            hash_table[hash].erase(hash_table[hash].begin() + i); // удаляем часть вектора, содержащие наше число
            break;                                        // erase - позволяет удалить любой элемент вектора
        }
    }
}

int main()
{
    ifstream fin("set.in");
    ofstream fout("set.out");
    int n = 100001;
    vector < vector<int> > hash_table(n, vector<int>()); // Создаём двумерный вектор, котрый явл. нашей хеш-таблицей
    string com;
    int x;
    while (fin)
    {
        fin >> com;
        if (!fin.eof())
        {
            if (com == "insert")
            {
                fin >> x;
                insert(hash_table, x);
            }
            else if (com == "delete")
            {
                fin >> x;
                deleted(hash_table, x);
            }
            else {
                fin >> x;
                if (exists(hash_table, x) == 0)
                    fout << "true\n";
                else
                    fout << "false\n";
            }
        }
    }
    return 0;
}
