#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Element // Создаём класс для хренеия элементов
{
public:
    int value; // значение
    int left; // индекс левого потомка
    int right; // индекс правого потомка
    int h = 0; // высота узла
    Element(int _value, int _left, int _right) : value(_value), left(_left), right(_right) {}
};

int right_h(int i, vector<Element>& tree) // Рекрусивная функция для поиска высоты справа
{
    if (tree[i].right == -1) // если ребёнка нет
        return 0; // то дальше идти некуда
    return tree[tree[i].right].h; // иначе, рекрусивный спуск
}

int left_h(int i, vector<Element>& tree) // Рекрусивная функция для поиска высоты слева
{
    if (tree[i].left == -1) // если ребёнка нет
        return 0; // то дальше идти некуда
    return tree[tree[i].left].h; // иначе, рекрусивный спуск
}

void find_height(int i, vector<Element>& tree) // 
{
    if (tree[i].left != -1) // если левый ребёнок существует
        find_height(tree[i].left, tree); // спускаемся к левому ребёнку
    if (tree[i].right != -1) // еслый правый ребёнок существует
        find_height(tree[i].right, tree); // спускаемся к правому ребёнку
    tree[i].h = max(left_h(i, tree), right_h(i, tree)) + 1; // считаем высоту вершины от правого и левого поддеревьев
}                                                                                              // и выбираем наибольшую

int balance(int i, vector<Element>& tree) // Функция для подсчёта баланса вершины
{
    int Right = 0, Left = 0; // Если ребёнок существует, то присвиваем высоту одного из детей, иначе 0
    Right = tree[i].right != -1 ? tree[tree[i].right].h : 0;
    Left = tree[i].left != -1 ? tree[tree[i].left].h : 0;
    return Right - Left; // Считаем баланс по определению
}

int main()
{
    ifstream fin("balance.in");
    ofstream fout("balance.out");
    int n;
    fin >> n;
    vector <Element> tree;
    for (int i = 0; i < n; i++)
    {
        int v, l, r;
        fin >> v >> l >> r;
        tree.push_back(Element(v, l - 1, r - 1));
    }
    find_height(0, tree); // запускаем функцию поиска высота для каждого узла
    for (int i = 0; i < n; i++)
        fout << balance(i, tree) << endl; // считаем баланс для каждой вершны
    fin.close();
    fout.close();
    return 0;
}