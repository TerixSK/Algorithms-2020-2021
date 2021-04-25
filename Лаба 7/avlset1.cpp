#include <fstream>
#include <vector>
#include <opencl-c.h>

using namespace std;

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

class AVL_Tree
{
public:
    Element* root = nullptr; // изначально корень равен нулю

    int get_balance(Element* elem)
    {
        if (elem == nullptr)
            return 0;
        return (elem->right != nullptr ? elem->right->height : 0) - (elem->left != nullptr ? elem->left->height : 0);
    }
    void fix_height(Element* elem) // Процедура для перезаписи высоты
    {
        elem->height = max(right_h(elem), left_h(elem)) + 1;
    }
    int right_h(Element* elem)
    {
        return elem->right == nullptr ? 0 : elem->right->height;
    }
    int left_h(Element* elem)
    {
        return elem->left == nullptr ? 0 : elem->left->height;
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
    Element* left_rotation(Element *elem) // Функция для левостороннего поворота дерева
    {
        return this->rotation(elem, true);
    }
    Element* right_rotation(Element *elem) // Функция для правостороннего поворота дерева
    {
        return this->rotation(elem, false);
    }
    Element* insert(int value, Element* elem) // Функция для вставки в элемента
    {
        if (elem == nullptr) // если текущего элемента не существует
            return new Element(value); // создаём структуру для нового элемента
        if (value > elem->value) // выбираем куда поместить новый элемент (левый или првый ребёнок)
            elem->right = insert(value, elem->right); // рекрусивного запускаем функцию от правого ребёнка
        else // иначе
            elem->left = insert(value, elem->left); // для левого ребёнка
        return balance(elem);
    }
    Element* last_right_child(Element* elem) // Функция для вывода крайнего правого элемента
    {
        if (elem->right == nullptr) // если у текущего элемента нет правого ребёнка
            return elem; // то текущий крайний правый элемент
        return last_right_child(elem->right); // если нет, то рекрусивно запускаем функцию для рекрусивного спуска по правым элементам
    }
    Element* remove(int value, Element* elem) // Функция для удаления элемента
    {
        if (elem == nullptr) // проверка что текущий элемент существует
            return nullptr;
        if (value > elem->value) // если значение больше чем значение текущего
            elem->right = remove(value, elem->right); // то рекрусивно запускаем ф-ию для правого ребёнка
        else if (value < elem->value) // если значение меньше чем значение текущего
            elem->left = remove(value, elem->left); // то рекрусивно запускаем ф-ию для левого ребёнка
        else // если значение совпадает с значением текущего элемента
        {
            if (elem->left == nullptr && elem->right == nullptr) // если у элемента нет детей
                return nullptr; // то возращаем пустоту
            else if (elem->left == nullptr) // если нет левого ребёнка
            {
                elem = elem->right; // перезаписываем в текущий элемент правого ребёнка
                return this->balance(elem); // и балансируем дерево
            }
            else // если есть левый и правый потомки
            {
                Element *help = last_right_child(elem->left); // записываем в переменную значение крайнего правого ребёнка
                elem->value = help->value; // перзаписываем значение
                elem->left = remove(help->value, elem->left); // рекрусивно запускаем функцию удаления для левого ребёнка
            }
        }
        return this->balance(elem); // после всех махенаций над деревом после удаления элемента балансируем его
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
};

int main()
{
    ifstream fin("avlset.in");
    ofstream fout("avlset.out");
    int n;
    fin >> n;
    auto AVL = new AVL_Tree;
    for (int i = 0; i < n; i++)
    {
        string com;
        int value;
        fin >> com >> value;
        if (com == "A")
        {
            if (AVL->search(AVL->root, value) == nullptr)
                AVL->root = AVL->insert(value, AVL->root);
            fout << AVL->get_balance(AVL->root) << endl;
        }
        if (com == "D")
        {
            if (AVL->search(AVL->root, value) != nullptr)
                AVL->root = AVL->remove(value, AVL->root);
            fout << AVL->get_balance(AVL->root) << endl;
        }
        if (com == "C")
            fout << ((AVL->search(AVL->root, value) != nullptr) ? "Y" : "N") << endl;
    }
}