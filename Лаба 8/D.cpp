#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int top1, top2, num = 0;
vector<int> graph[100000];
vector<bool> used;
vector<int> comp;
// мы будем производить серию обходов: сначала запустим обход из первой вершины,
// и все вершины, которые он при этом обошёл — образуют первую компоненту связности.
// Затем найдём первую из оставшихся вершин, которые ещё не были посещены,
// и запустим обход из неё, найдя тем самым вторую компоненту связности. И так далее,
// пока все вершины не станут помеченными.
void dfs(int v) // обход в глубину
{
    used[v] = true; // помечаем текущию вершину
    comp[v] = num;
    if (!graph[v].empty()) // делаем обход
    {
        for (int i: graph[v])
            if (used[i] == false) // если, вершина не помечена
                dfs(i); // то запускаем ф-ию от неё
    }
}

int main()
{
    ifstream fin("components.in");
    ofstream fout("components.out");
    int n, m;
    fin >> n >> m;
    for (int i = 0; i < m; i++) // считываем информацию
    {
        fin >> top1 >> top2;
        top1--;
        top2--;
        graph[top1].push_back(top2);
        graph[top2].push_back(top1);
    }
    for (int i = 0; i < n; i++)
    {
        used.push_back(false); // делаем пометку на всех
        comp.push_back(0); // заполняем вектор компонент нулями
    }
    for (int i = 0; i < n; i++)
    {
        if (used[i] == false) // если вершина ещё не помечена
        {
            num++; // инкриментируем счётчик компонент пар
            dfs(i); // запускаем обход для этой вершины
        }
    }
    fout << num << endl; // вывод
    for (int i = 0; i < n; i++)
        fout << comp[i] << " ";
    return 0;
}