#include <vector>
#include <fstream>
#include <queue>

using namespace std;

ifstream fin("rotation.in");
ofstream fout("rotation.out");

struct Element // Структура для хранение информации для вершины
{
    int value;
    int left;
    int right;
};

class AVLTree
{
private:
    vector <Element> tree; // вектор вершин (наше дерево)
    vector <int> height; // вектор высот для вершин
    int dfs(int top, int h) // Рекрусивная функция для для обхода дерева в глубину (поиск высоты дерева)
    {
        if (top < 0)
            return 0; // рекрусивно спускаемся по этажам дерева до детей листев и после возвращаем значения и + 1
        this->height[top] = max(dfs(this->tree[top].left, h), dfs(this->tree[top].right, h) ) + 1;
        return this->height[top];
    }
    void fix_height(int top)
    {
        this->height[top] = max( this->get_height(this->tree[top].left), this->get_height(this->tree[top].right) ) + 1;
    }
public:
    int get_height(int top) // Функция для получния высоты дерева
    {
        if(top < 0)
            return 0;
        return this->height[top];
    }
    void push_elem(Element* elem) // Процедура для заряжения эл. в дерево
    {
        this->tree.push_back(*elem);
        this->height.push_back(0);
    }
    void calc_height() // Процедура для полученя высоты
    {
        dfs(0, 0);
    }
    int left_rotation(int top) // Функция для малого левостороннего поворота
    {
        int help = this->tree[top].right; // записываем в вспомогательную переменную правого ребёнка
        this->tree[top].right = this->tree[help].left; // в правого ребёнка вершины записываем левого ребёнка help
        this->tree[help].left = top; // вершина становиться левым ребёнком
        this->fix_height(top); // перезаписываем высоты для вершины и изночального првого ребёнка вершины
        this->fix_height(help); //
        return help; // в целом мы меняем местами вершину и правого ребёнка, сохраняя првило BST свапая детей
    }
    int right_rotation(int top) // Функция для малого правостороннего поворота
    { // делаем то же самое, что и в левом повороте, но для левого ребёнка
        int help = this->tree[top].left;
        this->tree[top].left = this->tree[help].right;
        this->tree[help].right = top;
        this->fix_height(top);
        this->fix_height(help);
        return help;
    }
    int big_rotation_left(int top) // Функция для большого левостороннего поворота
    { // выполняеться для срединной (B) вершины (где A - родитель B, а C - ребёнок B )
        this->tree[top].right = this->right_rotation(this->tree[top].right); // сначало используем левосторонний поворот
        return this->left_rotation(top); // после левосторонний поворот
    }
    int rotation(int top)
    {
        int right = this->tree[top].right; // запоминаем правого ребёнка
        int child_l_h = this->get_height(this->tree[right].left); // считаем высоту для правого ребёнка
        int child_r_h = this->get_height(this->tree[right].right);
        if (child_r_h - child_l_h < 0) // в зависимости от баланса решаем какой поворот нам использовать
            return this->big_rotation_left(top); // большой левый
        return this->left_rotation(top); // или левый
    }
    void print_tree(int root) // Процедура для вывода дерева
    {
        fout << this->tree.size() << endl; // печатаем кол-во вершин дерева
        queue<int> q; // вводим очередь
        q.push(root); // заряжаем в неё корень дерева
        int line = 1;
        while(!q.empty()) // пока очередь не пуста
        {
            int top = q.front(); // запоминаем ссылку на первый элемент
            q.pop(); // удаляем его
            int l = 0, r = 0;
            if(this->tree[top].left >= 0) // если есть левый ребёнок
            {
                q.push(this->tree[top].left); // заряжаем в очередь левого ребёнка
                l = ++line;
            }
            if(this->tree[top].right >= 0) // если есть левый ребёнок
            {
                q.push(this->tree[top].right); // заряжаем в очередь правого ребёнка
                r = ++line;
            }
            fout << this->tree[top].value << " " << (l) << " " << (r) << endl; // вывод эл. и индексы на его детей
        }
    }
};

int main()
{
    int n;
    fin >> n;
    Element el;
    auto AVL = new AVLTree();
    for(int i = 0; i < n; i++) // вводим входные данные
    {
        fin >> el.value >> el.left >> el.right;
        el.left--; // уменьшаем индексы входных вершин на 1
        el.right--;
        AVL->push_elem(&el); // заряжаем элемент в дерево
    }
    AVL->calc_height(); // запускаем функцию посчёта высоты
    int new_root = AVL->rotation(0); // запускаем функцию для поворота дерева
    AVL->print_tree(new_root); // запускаем функцию вывода avl дерева
    return 0;
}