#include <fstream>
#include <vector>
using namespace std;

vector< vector<int> > g(100000);
vector< vector<int> > gT(100000); // транспонированный граф
vector<bool> used; // хранит цвета для dfs
vector<int> order; // хранит топологическую сортировку
vector<int> component; // хранит компоненты сильной связности

void dfs1(int v) // топологическая сортировка для обычного графа
{
    used[v] = true;
    for (auto i: g[v])
        if (used[i] == false)
            dfs1(i);
    order.push_back(v);
}

void dfs2(int v) // топологическая сортировка для транспонированного графа
{
    used[v] = true;
    component.push_back(v);
    for (auto i: gT[v])
        if (used[i] == false)
            dfs2(i);
}

int main()
{
    ifstream fin("cond.in");
    ofstream fout("cond.out");
    int n, m, v1, v2;
    fin >> n >> m;
    g.resize(n);
    gT.resize(n);
    for (int i = 0; i < m; i++)
    {
        fin >> v1 >> v2;
        v1--;
        v2--;
        g[v1].push_back(v2); // заполняем список смежности для заданного графа
        gT[v2].push_back(v1); // заполняем список смежности для транспонированного графа
    }
    used.assign(n, false);
    for (int i = 0; i < n; i++) // используем топологическую сортировка для обычного графа
        if (used[i] == false)
            dfs1(i);
    used.assign(n, false); // обнуляем вектор меток
    int k = 0;
    vector<int> ans;
    ans.assign(n, 0);
    for (int i = order.size()-1; i >= 0; i--) // используем топологическую сортировка для транспонированного графа
    {
        if (used[order[i]] == false)
        {
            component.clear(); // очищаем вектор
            dfs2(order[i]); // запускаем ф-ию
            k++; // увеличиваем кол-во сильных ком. связн.
            for (int j: component)
                ans[j] = k; // записываем номер компонент связности для конкретной вершины
        }
    }
    fout << k << endl; // вывод
    for (int i: ans)
        fout << i << " ";
    return 0;
}