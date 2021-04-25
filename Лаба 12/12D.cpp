#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> dp;

void update(int i, int j) // в клетку (i, j) можно прийти из четырех клеток: (i+1, j−2), (i−1, j−2), (i−2, j−1), (i−2, j+1)
{
    dp[i][j] += dp[i - 2][j - 1] + dp[i - 2][j + 1] + dp[i - 1][j - 2] + dp[i + 1][j - 2];
}

int main()
{
    ifstream cin("knight2.in");
    ofstream cout("knight2.out");
    int n, m;
    cin >> n >> m;
    n += 2;
    m += 2;
    dp.resize(n + 1, vector<int> (m + 1, 0));
    dp[2][2] = 1; // изначальная позиция коня
    int i = 2, j = 2;
    // Необходимо двумерный список dp заполнить значениями по этой формуле таким образом,
    // чтобы при вычислении нового значения в клетке были вычислены значения в тех четырех клетках,
    // которые необходимы для вычисления значения в клетке (i,j).
    while (i != n - 1 || j != m - 1)
    {
        int x = i, y = j;
        while (x >= 2 && y < m)
            update(x--, y++);
        i == n - 1 ? j++ : i++;
    }
    update(n - 1, m - 1);
    cout << dp[n - 1][m - 1];
    return 0;
}