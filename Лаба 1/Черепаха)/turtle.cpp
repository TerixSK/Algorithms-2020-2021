#include <fstream>
#include <iostream>
using namespace std;

int main()
{
    ifstream fin("turtle.in");
    ofstream fout("turtle.out");
    long long w;
    long long h;
    fin >> w >> h;
    long long pole[1000][1000];
    long long klonpole[1000][1000]; // Копия массива для проведения махинаций

    // Создание массива
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            fin >> pole[i][j];
        }
    }

    // Заполнение клетки в которой находиться черепаха
    klonpole[w - 1][0] = pole[w - 1][0];

    // Заполнение h0
    for (int i = 1; i < w; i++)
    {
        klonpole[w - i - 1][0] = klonpole[w - i][0] + pole[w - i - 1][0];
    }

    // Заполнение wmax
    for (int i = 0; i < h - 1; i++)
    {
        klonpole[w - 1][i + 1] = klonpole[w - 1][i] + pole[w - 1][i + 1];
    }

    // Заполнение остальных клеток поля
    for (int i = w - 2; i >= 0; i--)
    {
        for (int j = 1; j < h; j++)
        {
            if (klonpole[i + 1][j] > klonpole[i][j - 1])
            {
                klonpole[i][j] = klonpole[i + 1][j] + pole[i][j];
            }
            else
            {
                klonpole[i][j] = klonpole[i][j - 1] + pole[i][j];
            }
        }
    }

    // Вывод ответа
    fout << klonpole[0][h - 1];
    fin.close();
    fout.close();
    return 0;
}