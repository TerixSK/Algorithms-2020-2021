#include <fstream>
using namespace std;

struct Stack
{
    int data; // данные
    Stack* next; // указатель на сдед. элемент
};

// Функция принимает указатель на вершину стека и переменную, которую мы будем записывать в ячейку
void stack_push(Stack** top, int el) // el - элемент
{
    Stack* new_el; // создаём новый элемент
    new_el = new Stack(); // записываем необхлдимое число в data
    new_el->data = el;
    if (top == NULL) // если вершины нет, то новый элемент будет вершиной
        *top = new_el;
    else
    {
        new_el->next = *top; // кладём новый эл. на вершину
        *top = new_el; // теперь новый элмент стал вершиной
    }
}

//Функция которая принимает вершину top и число которое нужно удалить
void stack_delete(Stack** top, int key)
{
    Stack* new_el = *top;
    Stack* previous = NULL; //создаем указатель на предыдуший элемент, с начала он будет пустым
    while (new_el != NULL) // пока укахатель не пустой мы будем выполнять код в цикле
    {
        if (new_el->data == key) //если data элемента равна key
        {
            if (new_el == *top) // если вершина равна key
            {
                *top = new_el->next;
                free(new_el);
                new_el->data = NULL; //обнуляем переменные
                new_el->next = NULL;
            }
            else
            {
                previous->next = new_el->next;
                free(new_el);
                new_el->data = NULL; //обнуляем переменные
                new_el->next = NULL;
            }
        }// если data элемента НЕ равна числу, которое нам нужно удалить
        previous = new_el;
        new_el = new_el->next; //перемещаем указатель new_el на следующий элемент
    }
}

int main()
{
    ifstream fin("stack.in");
    ofstream fout("stack.out");

    long n;
    fin >> n;
    char command;
    long a;
    Stack* top = NULL; // в начале программы у нас нет очереди, соответственно вершины нет, даем ей значение NULL
    for (int i = 0; i < n; i++)
    {
        fin >> command;
        if (command == '+')
        {
            fin >> a;
            stack_push(&top, a);
        }
        else
        {
            stack_delete(&top, a);
            fout << a << "\n";
        }
    }

    fin.close();
    fout.close();
    return 0;
}
