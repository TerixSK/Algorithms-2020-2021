#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> graph[100000];
vector<bool> used;
vector<int> dist;

void bfs(int v) // обход в ширину
{
    used[v] = true; // помечаем первую вершину
    dist[v] = 0;
    queue<int> q;
    q.push(v); // добовляем её в очередь
    while (!q.empty()) // пока очередь не пуста
    {
        int E = q.front(); // достаём из очереди первый элемент
        for (int i = 0; i < graph[E].size(); i++)
        {
            if (used[graph[E][i]] == false) // если вершина ещё непомечена
            {
                used[graph[E][i]] = true; // помечаем её
                dist[graph[E][i]] = dist[E] + 1; // добовляем 1 за пройденную вершину
                q.push(graph[E][i]); // добвляем вершину в очередь
            }
        }
        q.pop();
    }
}

int main()
{
    ifstream fin("pathbge1.in");
    ofstream fout("pathbge1.out");
    int n, m, top1, top2;
    fin >> n >> m;
    for (int i = 0; i < m; i++) // считываем входные данные
    {
        fin >> top1 >> top2;
        top1--;
        top2--;
        graph[top1].push_back(top2);
        graph[top2].push_back(top1);
    }
    for (int i = 0; i < n; i++) // заполняем векторы меток и расстояния
    {
        used.push_back(false);
        dist.push_back(0);
    }
    for (int i = 0; i < n; i++) // запускаем обход в ширину
        if (used[i] == false)
            bfs(i);
    for (int i = 0; i < n; i++)
        fout << dist[i] << " ";
    return 0;
}
