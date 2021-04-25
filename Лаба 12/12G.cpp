#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream cin("knapsack.in");
    ofstream cout("knapsack.out");
    int n, s;
    cin >> n >> s;
    vector<vector<int>> a(s + 1, vector<int>(n + 1, 0));
    vector<int> w(s + 1);
    for (auto i = 1; i <= s; i++)
        cin >> w[i];

    for (auto i = 0; i < n + 1; i++)
        a[0][i] = 0;

    for (int i = 1; i <= s; i++)
        for (auto j = 0; j <= n; j++)
        {
            if (j >= w[i])
                a[i][j] = max(a[i - 1][j], a[i - 1][j - w[i]] + w[i]);
            else
                a[i][j] = a[i - 1][j];
        }
    cout << a[s][n] << endl;
    return 0;
}