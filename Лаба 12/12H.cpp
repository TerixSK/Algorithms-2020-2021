#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    //ifstream cin("input.txt");
    //ofstream cout("output.txt");
    int n;
    cin >> n;
    if (n == 1)
    {
        cout << 0;
        return 0;
    }
    const int m = 1000000000;
    vector<int> color(n);
    for (int i = 0; i < n; i++)
        cin >> color[i];

    vector<vector<int>> a(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++)
        a[i][i] = 1;
    for (int i = 1; i < n; i++)
        for (int j = 0; j + i < n; j++)
        {
            int k = j + i;
            if (color[j] == color[k])
                a[j][k] = (a[j + 1][k] % m + a[j][k - 1] % m + 1) % m;
            else
                a[j][k] = (a[j + 1][k] % m + a[j][k - 1] % m - a[j + 1][k - 1] % m) % m;
        }
    cout << (a[0][n - 1] + m) % m;
    return 0;
}