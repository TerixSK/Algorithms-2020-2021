#include <fstream>
#include <iostream>
using namespace std;

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int n, m;
    fin >> n >> m;
    int arr[n][n], check = 0, top1, top2; // создаём двумерный массив
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            arr[i][j] = 0; // заполняем его нулями
    }
    for (int i = 0; i < m; i++)
    {
        fin >> top1 >> top2; // считываем данные рёбер
        top1--;
        top2--;
        if (arr[top1][top2] == 0) // если такого ребра ещё нет, то записываем его
            arr[top1][top2] = 1;
        else // если есть, то паральные рёбра ещё есть
            check = 1;
        if (arr[top1][top2] == 1 && arr[top2][top1] == 1) // проверка на паралельность
            check = 1;
    }
    if (check == 1) // вывод
        fout << "YES";
    else
        fout << "NO";
    return 0;
}