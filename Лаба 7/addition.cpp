#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("addition.in");
ofstream fout("addition.out");

struct Help // Вспомогательная структура для записи вершин
{
    int value;
    int left;
    int right;
};

struct Element // Основная структура для хранение вершин дереваБ которая содержит
{
    int value; // значение
    Element* left; // указатель на левого ребёнка
    Element* right; // указатель на правого ребёнка
    int height; // высоту вершины
    Element(int value) : value(value) // авто заполнение некоторых параметров структуры при создании элемнета
    {
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class AVLTree
{
private:
    Element* root = nullptr; //
    int Size = 0;

    Element* build_dfs(vector <Help> &G, int top)
    {
        if (top < 0 || G.size() == 0)
            return nullptr;
        auto new_el = new Element(G[top].value); // создаём новый элемент структуры
        this->Size++; // увиличиваем размер
        new_el->left = build_dfs(G, G[top].left);
        new_el->right = build_dfs(G, G[top].right);
        new_el->height = max(this->get_height(new_el->left), this->get_height(new_el->right)) + 1;
        return new_el;
    }
    int get_height(Element* elem) // Функция для получения высоты вершины
    {
        if (elem == nullptr) // если элемент не существует
            return 0; // возвращаем ноль
        return elem->height; // если нет, то возвращаем высоту
    }
    void fix_height(Element *elem) // Процедура для перзаписи высоты
    {
        elem->height = max(this->get_height(elem->left), this->get_height(elem->right)) + 1;
    }
    int get_balance(Element* elem) // Функция для получения баланся вершины
    { // отнимаем высоту левого ребёнка от правого и получаем баланс
        return this->get_height(elem->right) - get_height(elem->left);
    }
    Element* balance(Element *elem) // Функция для балансировки дерева
    { // отцениваем баланс вершины
        if (this->get_balance(elem) > 1) // если баланс больше еденицы
        { // То нам нужно сделать большой поворот в лева
            if (this->get_balance(elem->right) < 0)
                elem->right = this->right_rotation(elem->right);
            return this->left_rotation(elem);
        }
        if (this->get_balance(elem) < -1) // // если баланс меньше -еденицы
        { // То нам нужно сделать большой поворот в права
            if (this->get_balance(elem->left) > 0)
                elem->left = this->left_rotation(elem->left);
            return this->right_rotation(elem);
        }
        return elem;
    }
    Element* rotation(Element *elem, bool where) // Функция для поворта в дерева в разные стороны
    {
        Element *help = where ? elem->right : elem->left; // выбираем куда нам нужно повернуть дерево
        // Начало: В зависимости от стороны разворачиваем дерево
        if (where)
        {
            elem->right = help->left;
            help->left = elem;
        }
        else
        {
            elem->left = help->right;
            help->right = elem;
        }
        // Конец
        this->fix_height(elem); // перзаписываем высоты
        this->fix_height(help);
        return help;
    }
    Element* insert_dfs(int value, Element *cur_elem)  // Функция для вставки в элемента
    {
        if (cur_elem == nullptr) // если текущего элемента не существует
            return new Element(value); // создаём структуру для нового элемента
        if (value > cur_elem->value) // выбираем куда поместить новый элемент (левый или првый ребёнок)
            cur_elem->right = insert_dfs(value, cur_elem->right); // рекрусивного запускаем функцию от правого ребёнка
        else // иначе
            cur_elem->left = insert_dfs(value, cur_elem->left); // для левого ребёнка
        this->fix_height(cur_elem); // перезаписываем высоту
        return this->balance(cur_elem); // проводим балансировку после вставки
    }
public:
    Element* left_rotation(Element *elem) // Функция для левостороннего поворота дерева
    {
        return this->rotation(elem, true);
    }
    Element* right_rotation(Element *elem) // Функция для правостороннего поворота дерева
    {
        return this->rotation(elem, false);
    }
    void build_tree(vector<Help> &G) // Функция для создания дерева
    {
        this->root = this->build_dfs(G, 0);
    }
    void insert(int value) // Функция для вставки элемента в дерево
    {
        this->root = this->insert_dfs(value, this->root); // используем функции для вставки
        this->Size++; // увиличиваем размер дерева
    }
    void print_tree() // Процедура для вывода дерева
    {
        queue <Element*> q; // создаём очередь для вывода
        q.push(this->root); // заряжаем в неё корень
        int line = 1;
        fout << this->Size << endl; // выводим размер
        while (!q.empty()) // пока очередь не пуста
        {
            Element *element = q.front(); // запоминаем ссылку на первый элемент
            q.pop(); // удаляем его
            int left = 0, right = 0;
            if (element->left != nullptr) // если есть левый ребёнок
            {
                q.push(element->left); // заряжаем в очередь левого ребёнка
                left = ++line;
            }
            if (element->right != nullptr) // если есть правый ребёнок
            {
                q.push(element->right); // заряжаем в очередь правого ребёнка
                right = ++line;
            }
            fout << element->value << " " << left << " " << right << endl; // вывод эл. и индексы на его детей
        }
    }
};

int main()
{
    int n;
    fin >> n;
    vector <Help> elements(n);
    for (int i = 0; i < n; i++)
    {
        fin >> elements[i].value >> elements[i].left >> elements[i].right;
        elements[i].left--;
        elements[i].right--;
    }
    auto AVL = new AVLTree();
    AVL->build_tree(elements);
    int new_value;
    fin >> new_value;
    AVL->insert(new_value);
    AVL->print_tree();
    return 0;
}