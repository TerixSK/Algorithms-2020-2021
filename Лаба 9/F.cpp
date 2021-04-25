#include <fstream>
#include <vector>
#include <stack>
using namespace std;

vector< vector<int> > g;
vector<string> color;
vector<bool> win;
// проигрывает тот игрок, кому нужно сделать ход из висячию вершину
// если win[start] == true, то ёто выгрышная позиция для первого играка и win[start] == false - проигрышная
// из-за того, что мы используем стек, мы обработаем стартовую вершину в последнею очередь
void game(int start)
{
    stack<int> stack; // создаём стек
    stack.push(start); // кладём в него стартовую вершину
    while (!stack.empty()) // пока стек не пуст
    {
        int cur = stack.top(); // берём из стека верхний элемент
        if (color[cur] == "black") // если вершины уже обработана
            stack.pop(); // то удаляем её из стека
        else if (color[cur] == "grey") // если вершина серая
        {
            bool flag = false; // вводим вспомогательную переменную флаг
            for (auto i: g[cur]) // проходимся по связным с текущей вершинам
                if (win[i] == false) // если хотя бы у одной связной вершины лежит false
                    flag = true; // то у текущей будет лежать обратное
            win[cur] = flag;
            color[cur] = "black"; // после окрашиваем вершину в чёрный
            stack.pop(); // и удаляем её
        }
        else // если вершина белая
        {
            color[cur] = "grey"; // делаем её серой
            for (auto i: g[cur]) // и помещаем все вершины связанные с ней
                if (color[i] == "white")
                    stack.push(i);
        }
    }
}

int main()
{
    ifstream fin("game.in");
    ofstream fout("game.out");
    int n, m, start, v1, v2;
    fin >> n >> m >> start;
    start--;
    g.resize(n);
    for (int i = 0; i < m; i++) // считываем информацию о вершинах
    { // и заполняем матрицу смежности
        fin >> v1 >> v2;
        v1--;
        v2--;
        g[v1].push_back(v2);
    }
    color.assign(n, "white");
    win.assign(n, false);
    game(start); // запускаем функцию
    win[start] == true ? fout << "First player wins" : fout << "Second player wins";
    return 0;
}