#include <fstream>
#include <vector>
using namespace std;

vector< vector<int> > g(100000);
vector<bool> used;
vector<int> order;

void dfs(int v) // топологическая сортировка
{
    used[v] = true;
    for (auto i: g[v])
        if (used[i] == false)
            dfs(i);
    order.push_back(v);
}

int main()
{
    ifstream fin("hamiltonian.in");
    ofstream fout("hamiltonian.out");
    int n, m, v1, v2;
    fin >> n >> m;
    g.resize(n);
    used.assign(n, false);
    for (int i = 0; i < m; i++)
    {
        fin >> v1 >> v2;
        v1--;
        v2--;
        g[v1].push_back(v2);
    }
    for (int i = 0; i < n; i++)
        if (used[i] == false)
            dfs(i);
    bool flag = true; // создаём флаг
    for (int i = order.size() - 1; i > 0; i--)
    {
        bool tempFlag = false; // доп. флаг
        for (int j = 0; j < g[order[i]].size(); j++)
            if (g[order[i]][j] == order[i - 1]) // если вершина из топологической сортировки совпадает с текущей
                tempFlag = true;
        if (tempFlag == false) // если прошли все вершины и флаг не изменился
        {
            flag = false; // то гамильнотого путя нет
            break;
        }
    }
    flag == true ? fout << "YES" : fout << "NO";
    return 0;
}