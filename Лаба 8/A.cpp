#include <fstream>
using namespace std;

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int n, m;
    fin >> n >> m;
    int arr[n][n], top1, top2; // вводим двумерный массив
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            arr[i][j] = 0; // заполняем его нулями
    }
    for (int i = 0; i < m; i++)
    {
        fin >> top1 >> top2; // считываем данные о рёбрах
        arr[top1 - 1][top2 - 1] = 1; // отмечаем их в двумерном массиве
    }
    for (int i = 0; i < n; i++) // вывод
    {
        for (int j = 0; j < n; j++)
            fout << arr[i][j] << ' ';
        fout << endl;
    }
    return 0;
}