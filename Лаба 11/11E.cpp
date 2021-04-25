#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

class Edge // Класс для описания ребра
{
private:
    int v1, v2, weigh; // хранит две вершины между которые соеденены ребром и вес ребра
public:
    Edge(int v1, int v2, int weight)
    {
        this->v1 = v1;
        this->v2 = v2;
        this->weigh = weight;
    }
    int getV1() const
    {
        return this->v1;
    }
    int getV2() const
    {
        return this->v2;
    }
    int getW() const
    {
        return this->weigh;
    }
};

vector<Edge> edge;
const int infinity = 1000000000;
vector<int> dist;
vector<int> parent;
vector<int> path;

int main()
{
    ifstream fin("negcycle.in");
    ofstream fout("negcycle.out");
    int n, w;
    fin >> n;
    dist.resize(n, infinity);
    parent.resize(n, -1);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            fin >> w;
            edge.push_back({i, j, w});
        }
    int start;
    dist[0] = 0;
    for (int i = 0; i < n; i++) // Алгоритм Форда-Беллмана (позволяет проверить наличие или отсутствие цикла отрицательного веса)
    {
        start = -1;
        for (auto & j : edge)
        {
            if (dist[j.getV2()] > dist[j.getV1()] + j.getW())
            {
                dist[j.getV2()] = max(dist[j.getV1()] + j.getW(), -infinity);
                parent[j.getV2()] = j.getV1();
                start = j.getV2();
            }
        }
    } // делаем n итераций цикла алгоритма
    if (start == -1) // если на последней итерации не произошло никаких изменений
        fout << "NO"; // то отрицательного цикла в графе нет
    else // иначе
    {
        int end = start; // берём вершину, расстояние до которой изменилось
        for (int i = 0; i < n; i++) // заполнение массива предков
            end = parent[end];
        for (int cur = end; ; cur = parent[cur]) // будем идти по её предкам, пока не войдём в цикл
        {
            path.push_back(cur);
            if (cur == end && path.size() > 1)
                break;
        }
        reverse(path.begin(), path.end()); // этот цикл и будет искомым циклом отрицательного веса
        fout << "YES" << endl;
        fout << path.size() << endl;
        for (auto & i: path)
            fout << i + 1 << " ";
    }
    return 0;
}