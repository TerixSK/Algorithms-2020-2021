#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

vector<vector<int>> g;
vector<vector<int>> d;
 
void dfs(int v)
{
    d[v][0] = 0;
    d[v][1] = 1;

    for (int i: g[v])
        dfs(i);
    for (int i: g[v])
    {
        d[v][1] += d[i][0];
        d[v][0] += max(d[i][0], d[i][1]);
    }
}

int main()
{
    //ifstream cin("input.txt");
    //ofstream cout("output.txt");
    int n, v, root = 0;
    cin >> n;
    g.resize(n);
    d.resize(n, vector<int>(2));
    for (int i = 0; i < n; i++)
    {
        cin >> v;
        if (v == 0)
            root = i;
        else
            g[v-1].push_back(i);
    }
    dfs(root);
    cout << max(d[root][0], d[root][1]);
}