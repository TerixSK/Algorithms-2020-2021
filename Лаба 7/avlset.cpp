#include <vector>
#include <fstream>
#include <queue>

using namespace std;

ifstream fin("avlset.in");
ofstream fout("avlset.out");

struct Element // Основная структура для хранение вершин дерева, которая содержит
{
    int value; // значение
    int height; // указатель на левого ребёнка
    Element* left; // указатель на правого ребёнка
    Element* right; // высоту вершины
    Element(int key) : value(key) // авто заполнение некоторых параметров структуры при создании элемнета
    {
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class AVLTree
{
public:
    Element* root = nullptr; // изначально корень равен нулю
    int Size = 0; // размер дерева

    Element *build_dfs(vector <Help> &G, int top)
    {
        if (top < 0 || G.size() == 0)
            return nullptr;
        auto new_el = new Element(G[top].value); // создаём новый элемент структуры
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
    void fix_height(Element* elem) // Процедура для перзаписи высоты
    {
        elem->height = max(this->get_height(elem->left), this->get_height(elem->right)) + 1;
    }
    int get_balance(Element *elem) // Функция для получения баланся вершины
    {// отнимаем высоту левого ребёнка от правого и получаем баланс
        return this->get_height(elem->right) - this->get_height(elem->left);
    }
    Element* balance(Element* elem) // Функция для балансировки дерева
    { // отцениваем баланс вершины
        this->fix_height(elem);
        if (this->get_balance(elem) > 1) // если баланс больше еденицы
        { // То нам нужно сделать большой поворот влева
            if (this->get_balance(elem->right) < 0)
                elem->right = this->right_rotation(elem->right);
            return this->left_rotation(elem);
        }
        if (this->get_balance(elem) < -1) // если баланс меньше -еденицы
        {// То нам нужно сделать большой поворот вправа
            if (this->get_balance(elem->left) > 0)
                elem->left = this->left_rotation(elem->left);
            return this->right_rotation(elem);
        }
        return elem;
    }
    Element* rotation(Element* elem, bool where) // Функция для поворта в дерева в разные стороны
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
    Element* insert(int value, Element* cur_elem) // Функция для вставки в элемента
    {
        if (cur_elem == nullptr) // если текущего элемента не существует
            return new Element(value); // создаём структуру для нового элемента
        if (value > cur_elem->value) // выбираем куда поместить новый элемент (левый или првый ребёнок)
            cur_elem->right = insert_dfs(value, cur_elem->right); // рекрусивного запускаем функцию от правого ребёнка
        else // иначе
            cur_elem->left = insert_dfs(value, cur_elem->left); // для левого ребёнка
        return this->balance(cur_elem); // проводим балансировку после вставки
    }
    Element* last_right(Element* cur_elem) // Функция для вывода крайнего правого элемента
    {
        if (cur_elem->right == nullptr) // если у текущего элемента нет правого ребёнка
            return cur_elem; // то текущий крайний правый элемент
        return last_right(cur_elem->right); // если нет, то рекрусивно запускаем функцию для рекрусивного спуска по правым элементам
    }
    Element* remove(int value, Element* cur_elem) // Функция для удаления элемента
    {
        if (cur_elem == nullptr) // проверка что текущий элемент существует
            return nullptr;
        if (value > cur_elem->value) // если значение больше чем значение текущего
            cur_elem->right = remove_dfs(value, cur_elem->right); // то рекрусивно запускаем ф-ию для правого ребёнка
        else if (value < cur_elem->value) // если значение меньше чем значение текущего
            cur_elem->left = remove_dfs(value, cur_elem->left); // то рекрусивно запускаем ф-ию для левого ребёнка
        else // если значение совпадает с значением текущего элемента
        {
            if (cur_elem->left == nullptr && cur_elem->right == nullptr) // если у элемента нет детей
                return nullptr; // то возращаем пустоту
            else if (cur_elem->left == nullptr) // если нет левого ребёнка
            {
                cur_elem = cur_elem->right; // перезаписываем в текущий элемент правого ребёнка
                return this->balance(cur_elem); // и балансируем дерево
            }
            else // если есть левый и правый потомки
            {
                Element *help = last_right(cur_elem->left); // записываем в переменную значение крайнего правого ребёнка
                cur_elem->value = help->value; // перзаписываем значение
                cur_elem->left = remove_dfs(help->value, cur_elem->left); // рекрусивно запускаем функцию удаления для левого ребёнка
            }
        }
        return this->balance(cur_elem); // после всех махенаций над деревом после удаления элемента балансируем его
    }
    Element* left_rotation(Element *elem) // Функция для левостороннего поворота дерева
    {
        return this->rotation(elem, true);
    }
    Element* right_rotation(Element *elem) // Функция для правостороннего поворота дерева
    {
        return this->rotation(elem, false);
    }
    void build_tree(vector<Help> &G) // Процедура для создания дерева
    {
        this->Size = G.size();
        this->root = this->build_dfs(G, 0);
    }
    void insert(int value) // Процедура для вставки элемента в дерево
    {
        this->root = this->insert_dfs(value, this->root); // используем функции для вставки
        this->Size++; // увиличиваем размер дерева
    }
    void remove(int value) // Процедура для удаления элемента
    {
        this->root = this->remove_dfs(value, this->root);
    }
    Element* search(Element* root, int value) // Функция для поиска
    {
        if (root == nullptr || value == root->value) // еси дошли до конца дерева или нашли искомые значение
            return root; // возвращаем его
        if (value < root->value) // выбираем в какое дерево спускаться
            return search(root->left, value);
        else
            return search(root->right, value);
    }
    void print_tree() // Процедура для вывода дерева
    {
        queue <Element*> q; // создаём очередь для вывода
        q.push(this->root); // заряжаем в неё корень
        int line = 1;
        fout << (this->Size - 1) << endl; // выводим размер
        while (!q.empty()) // пока очередь не пуста
        {
            Element *element = q.front(); // запоминаем ссылку на первый элемент
            q.pop(); // удаляем его
            if (element == nullptr) // если элемента не существует
                break;
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
    size_t n;
    fin >> n;
    auto AVL = new AVLTree();
    for (int i = 0; i < n; i++)
    {
        string com;
        int value;
        fin >> com >> value;
        if (com == "A")
        {
            if (AVL->search(AVL->root, value) == nullptr)
            {
                AVL->insert(value);
            }
            fout << AVL->get_balance(AVL->root) << endl;
        }
        if (com == "D")
        {
            if (AVL->search(AVL->root, value) != nullptr)
            {
                AVL->remove(value);
            }
            fout << AVL->get_balance(AVL->root) << endl;
        }
        if (com == "C")
        {
            fout << ((AVL->search(AVL->root, value) != nullptr) ? "Y" : "N") << endl;
        }
    }
}