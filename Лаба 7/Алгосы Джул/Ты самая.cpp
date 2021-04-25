#include <fstream>
#include <vector>

using namespace std;

struct Node // Создаёи структуру для хранение элементов
{
    int key; // численноре значение вершины
    int height; // высоту вершины
    int children[2]; // создаём двух детей
    Node(int key, int left, int right) : key(key), height(0) // эта строчка нужна чтобы зарядить элементы в вектор
    {
        children[0] = left; // children[0] - левый ребёнок
        children[1] = right; // children[1] - правый ребёнок
    }
};

struct AVL_Tree // Структура в который будут происходить подсчёт баланса каждой вершины
{
    vector<Node *> tree; // создаём вектор который будет хранить вершины нашего дерева

    int balance(int node) // Функция для подсчёта баланса для каждой вершины
    {
        int h_left, h_right; // вводим переменные для хранения высот правого и левого детей
        if (tree[node]->children[0] != -1) // если левый ребёнок существует
            h_left = tree[tree[node]->children[0]]->height; // то присваевываем переменой её высоты
        else // иначе
            h_left = 0; // присвеваем ноль для корректного подсчёта баланса
        if (tree[node]->children[1] != -1) // если правый ребёнок существует
            h_right = tree[tree[node]->children[1]]->height; // то присваевываем переменой её высоты
        else // иначе
            h_right = 0; // присвеваем ноль для корректного подсчёта баланса
        return h_right - h_left; // выводим разницу между правым и левым детьми
    }

    void count_height() // Функция для посчёты высоты дерева
    {
        if (tree.empty()) // если дерево не пустое
            return; // прекращаем работы функции
        height(tree[0]); // запускаем функцию от корня
    }

    int height_right(Node *node) // Функция для определения выосты правого ребёнка
    {
        if (node->children[1] == -1) // если у нас нету правого ребёнка
            return 0; // то возвращаем 0
        else // иначе
            return tree[node->children[1]] -> height; // возращаем его высоту
    }

    int height_left(Node *node) // Функция для определения выосты левого ребёнка
    {
        if (node->children[0] == -1) // если у нас нету левого ребёнка
            return 0; // то возвращаем 0
        else // иначе
            return tree[node->children[0]] -> height; // возращаем его высоту
    }

    void height(Node *node) // Рекрусивная функция для подсчёта в глубину
    {
        for (int child : node->children) // цикл forarche - это цикл, который совершит итерацию для каждого элемента структуры
        { // прогонит цикл для каждого ребёнка
            if (child != -1) // если ребёнок существует
                height(tree[child]); // то рекурсивно запускаем функцию высоты для него
        } // рекурсивную функцию для подсчёта высоты каждой вершины
        node->height = max(height_left(node), height_right(node)) + 1; // рекурсивный спуск вниз (за каждый подьём + 1)
    }
};

int main()
{
    ifstream fin("balance.in");
    ofstream fout("balance.out");
    int n; // вводим кол-во вершин
    fin >> n;
    // auto - автоматическое определение типа переменной
    auto avl = new AVL_Tree(); // Создаём наше дерево
    for (int i = 0; i < n; i++)
    {
        int key, left, right;
        fin >> key >> left >> right; // вводим значения
        avl->tree.push_back(new Node(key, left-1, right-1)); // уменьшаем индексы детей
    }                                                                   // и индекс -1 означает что ребёнка нет

    avl->count_height(); // подсчитывает высоту для кажой вершины

    for (int i = 0; i < avl->tree.size(); i++) // выводим балансы дял каждой вершины
        fout << avl->balance(i) << endl;
}