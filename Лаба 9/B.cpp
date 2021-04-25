#include <fstream>
#include <vector>
using namespace std;

vector<vector<int>> g;
vector<string> color; // изночально все вершины белые
vector<int> cycle;

int start = -1, finish = -1; // начало и конец для цикла
void dfs(int v)
{
    color[v] = "grey"; // помечаем вершину серой
    for (int i: g[v])
    {
        if (color[i] == "grey") // если мы пришли в серую вершину, то мы нашли цикл
        {
            start = i;
            finish = v;
        }
        else if (color[i] == "black") // если в чёрную, то
        {
            cycle[i] = v; // заполняем массив цикла
            dfs(i); // и продолжаем идти
        }
    }
    color[v] = "black"; // после всем манипуляций помечаем вершину чёрной
}

int main()
{
    ifstream fin("cycle.in");
    ofstream fout("cycle.out");
    int n, m, v1, v2;
    fin >> n >> m;
    g.resize(n);
    color.assign(n, "white"); // изночально все вершины отмечаем белым цветом
    cycle.assign(n, -1);
    for (int i = 0; i < m; i++) // считываем данные о вершинах
    { // и строим список смежности
        fin >> v1 >> v2;
        v1--;
        v2--;
        g[v1].push_back(v2);
    }

    for (int i = 0; i < n; i++) // запускаем dfs для белых вершин
        if (color[i] == "white")
            dfs(i);
    if (start == -1) // если стартовая точка не и зменилась, то циклов в грфае нет
        fout << "NO";
    else // иначе
    {
        fout << "YES" << endl; // выводим да
        vector<int> ans; // и вывоводим цикл с помощью массива предков
        ans.push_back(start + 1);
        for (int i = finish; i != start; i = cycle[i])
            ans.push_back(i + 1);
        for (int i = ans.size() - 1; i >= 0; i--)
            fout << ans[i] << " ";
    }
    return 0;
}