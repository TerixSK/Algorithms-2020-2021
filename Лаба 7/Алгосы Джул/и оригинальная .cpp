#include <fstream>
#include <vector>
#include <queue>

using namespace std;
// создаем enum для хранения информации куда делать поворот
enum Side {right=0, left=1}; // 0 - вправо 1 -влево
struct Input_Node // создаем структуру для хранения элементов входного дерева
{
    int key; //численное значение вершины
    int children[2]; //массивчик из детишек
    Input_Node(int key, int left, int right) : key(key) // эта строчка нужна чтобы зарядить элементы в вектор
    {
        children[0] = left; //левый ребенок
        children[1] = right;//правый ребенок
    }
};
struct Node //структура для хранения элементов
{
    int key; //численное значение вершины
    int height; //высота вершины
    int inp_num;
    Node* children[2]; //массивчик для детишек
    Node(int key, Node * left, Node * right, int num) : key(key), height(0), inp_num(num) // эта строчка нужна чтобы зарядить элементы в вектор
    {
        children[0] = left; //левый ребенок
        children[1] = right; //правый ребенок
    }
    Node(Input_Node * node, int num) : height(0), key(node->key), inp_num(num) // это конструтор структуры, который позволяет
    {
        children[0] = children[1] = nullptr; // автомотически при создании переменой типа Node присвоить детям значения NULL
    }
};
struct AVL_Tree //структура для создания дерева
{
    vector<Input_Node*> input_tree; // вектор, который будет хранить начальную информацию о вершинах дерева
    // (основной вектор, с которым мы будем работать)
    vector<Input_Node*> output_tree; // вектор, в который мы запишем наше дерево после поворота
    Node * root = nullptr; // корень, он изночально равен нулю
    void make_tree() // Функция, которая запускает функцию создания от корня
    {
        root = new Node(input_tree[0], 0); // заполняем структуру корня
        dfs_make(root); // запускаем функцию создания нашего дерва
    }
    // это нам нужно чтобы рекрусивно испольозовать след. ф - ию не создовая каждый раз корень заного
    void dfs_make(Node *node) // Функция слздания нашего дерва
    {
        for (int i = 0; i < 2; i++) // цикл дял каждого ребёночка
        {
            if (input_tree[node->inp_num]->children[i] == -1) // если ребёночка не существует
            {
                node->children[i] = nullptr; // то присвевываем ему пустоту
            }
            else // если ребёнок существует
            {
                node->children[i] = // то создаём дял него структуру и заполняем её входными данными
                        new Node(input_tree[input_tree[node->inp_num]->children[i]], input_tree[node->inp_num]->children[i]);
                dfs_make(node->children[i]); // рукрусивно перезапускаем ф-ию от правого и левого ребёнка
            }
        }
    }
    int count_balance(Node *node) //подсчет баланса
    {
        int h_left, h_right; // вводим переменные для хранения высот правого и левого детей
        if (node->children[1] != nullptr)
            h_right = node->children[1]->height;
        else
            h_right = 0;
        if (node->children[0] != nullptr)
            h_left = node->children[0]->height;
        else
            h_left = 0;
        return h_right - h_left;
    }
    void count_height() // Фукция, которая запускает ф-ию, функцию, которая считает высоту если дерево не пустое
    {
        if (input_tree.empty()) // (если дерево не пустое)
        {
            return;
        }
        dfs(root);
    }
    void fix_height(Node *node) //здесь считаем высоту
    {
        node->height = max(height_left(node), height_right(node)) + 1; // рекурсивный подсёт высоты
    }
    int height_right(Node *node) // Функция для определения выосты правого ребёнка
    {
        if (node->children[1] == nullptr) // если у нас нету правого ребёнка
            return 0; // то возвращаем 0
        else // иначе
            return node->children[1] -> height; // возращаем его высоту
    }
    int height_left(Node * node) // Функция для определения выосты левого ребёнка
    {
        if (node->children[0] == nullptr) // если у нас нету левого ребёнка
            return 0; // то возвращаем 0
        else // иначе
            return node->children[0] -> height; // возращаем его высоту
    }
    void dfs(Node *node) // Функция вызывает функцию, которая считает высоту
    {
        for (auto child : node->children) // цикл forarche для каждог оребёка
        { // child = i то же самое
            if (child != nullptr) // если ребёкочек существует
            {
                dfs(child);
            }
        }
        fix_height(node);
    }
    Node *rotate(Node *node, int side) // Функция для поворота дерева в право или в лево
    {
        Node *temp; // вводим временую переменую
        if (side == Side::left) // если нам нужно повернуть влево
            temp = node->children[1]; // то врем. перем. будет правым ребёнком
        else // иначе
            temp = node->children[0]; // левым
        // если поварачиваем влево свапаем правого ребёночка и поступающий в ф-ию элемент
        if (side == Side::left)
            node->children[1] = temp->children[0];
        else
            node->children[0] = temp->children[1];
        if (side == Side::left)
            temp->children[0] = node;
        else
            temp->children[1] = node;
        // конец свапа
        fix_height(node); // персчитываем высоту для входящего элемента
        fix_height(temp); // персчитываем высоту и для левого или правого ребёнка
        return temp; // возвращем временый элемент
    }
    Node * balance(Node * node) // Функция автоматической балансировки(будет проверять сбалансированное ли дерево и если нет то будет делать нужные повороты)
    {
        fix_height(node); // считаем высоту от постипившего после вставки ёлемента
        if (count_balance(node) > 1) // если баланс больше одного (правое поддеро больше чем левое)
        { // делаем либо большой левый или малый левый
            if (count_balance(node->children[1]) < 0) // от этого условия зависит какой поворот мы будем использовать
            {// если блананм правого ребэнка меньше нуля
                node->children[1] = rotate(node->children[1], Side::right); // то делаем большой поворот
            }
            return rotate(node, Side::left); // если нет то малый
        }
        if (count_balance(node) < -1) // если баланс меншьше минус одного (левое поддеро больше чем правое)
        { // делаем большой или малый ПРАВЫЙ поворот
            if (count_balance(node->children[0]) > 0) // от этого условия зависит какой поворот мы будем использовать
            {// если блананм левого ребэнка меньше нуля
                node->children[0] = rotate(node->children[0], Side::left); // то делаем большой поворот
            }
            return rotate(node, Side::right); // если нет то малый
        }
        return node;
    }
    void make_output_tree() // Функция, которая выводить наше дерево (после воворота(поворота))
    {
        queue<Node *> queue; // создаём очередь
        queue.push(root); // кладёт в очередь корень дерева
        int num = 1; // вводим доп. переменую, для обзначения номера ребёночка
        while (!queue.empty()) // пока неперенесём все элементы  в выходной вектор
        {
            Node * node = queue.front(); // запоминаем ссылку на первый элемент (на корень на первой итерации)
            queue.pop(); // удаляем его из очереди
            int children_num[2] = {0, 0}; // массив для детишек
            for (int i = 0; i < 2; i++) // цикл дял детишек
            {
                if (node->children[i] != nullptr) // если ребёночек существует
                {
                    queue.push(node->children[i]); // кладём его в очередь
                    children_num[i] = ++num; // прибавляем 1 для смены ребенка
                }
            }
            // полученный элеменет отпраляем в вектор котрый впоследствии выводим
            output_tree.push_back(new Input_Node(node->key, children_num[0], children_num[1]));
        }
    }
    Node * insert(Node * node, int key) // Функция для вставки элемента в дерево
    { // мы начиная с корня в замисимости от числового значения решаем в какое поддерво нам рекурсивно спустится до того момента пока не дойдём до последних детей
        if (node == nullptr) // если элемента не существет
        {
            return new Node(key, nullptr, nullptr, (int)(input_tree.size()+1)); // то создаём пустую структуру и заполняем его нашим значением
        } //  нам нужно орпеделить куда вставлять элемнет, для этого мы решаем куда мы рекрусивно спустимся (по правилу двоич. дерева поиска)
        if (key < node->key) // если значение вставляемого элемента меньше текущего элемента
            node->children[0] = insert(node->children[0], key); // то запускаем функцию для вставки от левого ребёнка, ведь левый ребёночек всегда должен быть меньше чем его родитель
        else // если значение вставляемого элемента больше корня
            node->children[1] = insert(node->children[1], key); // уже от правого, ведь правый ребёночек должен быть больше чем родитель
        return balance(node); // используем функцию для балансировки дерева после вставки элемента
    }
};

int main()
{
    ifstream fin("addition.in");
    ofstream fout("addition.out");
    int n;
    fin >> n;
    auto avl = new AVL_Tree();
    for (int i = 0; i < n; i++)
    {
        int key;
        int left, right;
        fin >> key >> left >> right;
        avl->input_tree.push_back(new Input_Node(key, left-1, right-1));
    }
    int key; // вводим числовое значение вершины что мы должны втавить
    fin >> key;
    if (n == 0)
    {
        fout << 1 << "\n" << key << " " << 0 << " " << 0 << endl;
        return 0;
    }
    avl->make_tree(); // используем функцию создания дерева
    avl->count_height(); // используем функцию подсчёта высоты
    avl->root = avl->insert(avl->root, key); // запускаем функцию для вставки элемента
    avl->make_output_tree(); // используем функцию заполнения вектора с элементами после поворота
    fout << n + 1 << endl; // // выводи кол-во элементов
    for (auto v : avl->output_tree) // выводи конечное дерево после вставки элементов
    {
        fout << v->key << " " << v->children[0] << " " << v->children[1] << endl;
    }
}