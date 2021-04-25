#include <fstream>
#include <string>

using namespace std;

struct element // Создаём стуктуры для элементов бин. дерева поиска
{
    int value; // само число
    element* parent; // указатель на родителя
    element* left; // указатель на левого ребёнка
    element* right; // указатель на правого ребёнка
};

class BinTreeSearch // Создаём класс 
{
private:
    element* root = NULL; // верхий элемент, он же корень равен пустоте
public:

    element* Search(int x) // Поиск элемента в бин. дереве поиска
    {
        element* current_el = root; // текущий эл. равен корню
        while (current_el != NULL && x != current_el->value) // запускаем while пока не найдём значение эл. или выясним, что такого эл. в дереве нет
        {
            if (x < current_el->value)          // }
                current_el = current_el->left;  // } Опциональный поиск искомого числа в левом или в правом поддереве
            else                                // }
                current_el = current_el->right; // }
        }
        return current_el; // возвращаем найденное значение
    }

    void Insert(int x) // Функция, которые заряжает элемнты
    {
        if (Check_el(x)) // проверка сущетвует ли заряжаемый элемент
            return;
        element* new_el = new element; // создаём новый ветвь в нашем дереве 
        new_el->value = x;             // }
        new_el->parent = NULL;         // } заполняем стуктуру для нашего элемента
        new_el->left = NULL;           // }
        new_el->right = NULL;          // }
        element* current_el = root; // создаём структуру для текущего эл.
        // Начало (Ищем место для нашего нового элемента)
        while (current_el != NULL)                 // если текущий > нового, то ищем каким будет текущий эл.(правым или левым ребёнком)                
        {
            new_el->parent = current_el;
            if (new_el->value < current_el->value)
                current_el = current_el->left;
            else
                current_el = current_el->right;   //          
        }
        if (new_el->parent == NULL) // если дерево пусто, то новый эл. станет корнем
            root = new_el;          //                       
        else
        {
            if (new_el->value < new_el->parent->value) // если текущий < нового, то ищем каким будет новый эл.(правым или левым ребёнком)     
                new_el->parent->left = new_el;
            else
                new_el->parent->right = new_el;
        }
        // Конец (Ищем место для нашего нового элемента)
    }

    void Delete(int x) // Функция, которая обнуляет элементы
    {
        element* del_el = Search(x); // ищем нужный нам элемент
        if (del_el == NULL) // если нужного нам элемента нет
        {
            return;
        }
        element* previous_el; // структура для предыдущего эл.
        element* hepl_el; // структура для вспомогательного эл.
        if (del_el->left == NULL || del_el->right == NULL) // если у удаляемого эл. нет детей
            previous_el = del_el; // то предыдущий становиться равен удаляемымому
        else
            previous_el = Next(x); // иначе ищем мин. > x 
        if (previous_el->left != NULL) // если левый ребёнок не равен пустоте
            hepl_el = previous_el->left;
        else
            hepl_el = previous_el->right;
        if (hepl_el != NULL) // если вспомогательный эл. не равен пустоте
            hepl_el->parent = previous_el->parent;
        if (previous_el->parent == NULL) // если родитель равен пустоте
            root = hepl_el;
        else
        {
            if (previous_el == previous_el->parent->left)
                previous_el->parent->left = hepl_el;
            else
                previous_el->parent->right = hepl_el;
        }
        if (previous_el != del_el) // по итогу если предыдущий эл. не равен удаляемому
            del_el->value = previous_el->value; // удаляемый становиться предыдущим
        delete previous_el; // и удаляем следующий элемент
    }

    bool Check_el(int x) // проверка равен ли нужный нам элемент пустоте
    {
        return Search(x) != NULL; // возвращаем true или false
    }

    element* Next(int x) // Функция возвращает минимальный эл. > x или none(если такого нет)
    {
        element* current_el = root;   // текущий элемент равен корню
        element* successor_el = NULL; // следующий - пустоте
        // Начало (ищем нужный элемент, используя условие)
        while (current_el != NULL)
        {
            if (current_el->value > x) // основное условие
            {
                successor_el = current_el;
                current_el = current_el->left;
            }
            else
                current_el = current_el->right;
        }
        // Конец (ищем нужный элемент, используя условие)
        return successor_el; // возвращаем значение
    }

    element* Previous(int x) // Функция возвращает максимальный эл. < x или none(если такого нет)
    {
        element* current_el = root; // текущий эл. равен корню
        element* previous_el = NULL; // предыдущий - пустоте
        // Начало (ищем нужный элемент, используя условие)
        while (current_el != NULL)
        {
            if (current_el->value < x) // основное условие
            {
                previous_el = current_el;
                current_el = current_el->right;
            }
            else
                current_el = current_el->left;
        }
        // Конец (ищем нужный элемент, используя условие)
        return previous_el;
    }
};

int main()
{
    ifstream fin("bstsimple.in");
    ofstream fout("bstsimple.out");
    BinTreeSearch tree;
    string command;
    int key;
    while (fin >> command >> key)
    {
        if (command == "insert")            // }
            tree.Insert(key);               // }
        if (command == "delete")            // }
            tree.Delete(key);               // }
        if (command == "exists")            // }
        {                                   // }
            if (tree.Search(key))           // }
                fout << "true\n";           // }
            else                            // }
                fout << "false\n";          // }
        }                                   // }     Блок чтения команад и выполнение их
        if (command == "next")              // }
        {                                   // }
            element* res = tree.Next(key);  // }
            if (res == NULL)                // }
                fout << "none\n";           // }
            else                            // }
                fout << res->value << "\n"; // }
        }                                   // }
        if (command == "prev")              // }
        {                                   // }
            element* res = tree.Previous(key); // }
            if (res == NULL)                   // }
                fout << "none\n";              // }
            else                               // }
                fout << res->value << "\n";    // }
        }
    }
    fin.close();
    fout.close();
    return 0;
}
