#include <fstream>
#include <vector>

using namespace std;

ifstream fin("linkedmap.in"); // открываем файлы тут поскольку некотрые функции выводят ответ
ofstream fout("linkedmap.out");

int Hash(const string& key) // Функция для хеширования ключей
{
    int hash_code = 0;
    int k = 41; // константа
    for (auto& i : key)
    {
        int s = 0;
        if (((i - 'a') >= 0) && (i - 'a' <= 9))
            s = i - 'a';
        else
            s = i - 'A';
        hash_code = (hash_code + ((s + 1) *k) % 1000000) % 1000000;
        k = (k * 41) % 1000000;
    }
    return hash_code % 100001;
}

vector<vector<pair<string, string>>> hash_table; // создаём двумерный вектор, который будет хранить пары элементов ключ-значение

vector<string> key_table; // вспомогательный вектор для ключей

void Get(const string& key) // Функция для поиска элемента по ключу и вывод его значение (если он есть в хеш-таблице)
{
    int h = Hash(key); // хешируем элемент
    if(hash_table[h].empty()) // если вектор пустой, то нам нет смысла искать нашу пару
    {
        fout << "none\n"; // выводим, то что элемента нет
        return; // прекращаем работу функции
    }
    for(auto& i : hash_table[h]) // Это цикл forarche - цикл который совершает итерацию на каждый элемент вектора
    { // auto - это тип переменной, который зависит от того что в ней храниться, например auto x = 5.5 => flout x = 5,5
        if(i.first == key) // ищем по хешу нужный ключ
        {
            fout << i.second << '\n'; // выводим его значение
            return; // прекращаем работу функции
        }
    }
    fout << "none\n"; // если мы не нашли нужный ключ, то его нет в хеш-таблице
}

bool Get_bool(const string& key) // Вспомогательныя функция, для того чтобы определеть есть ли искомый ключ в хеш-таблице
{
    int h = Hash(key); // хешируем элемент
    if(hash_table[h].empty()) // если вектор пустой, то нам нет смысла искать нашу пару
        return false; // возвращаем что нет такого ключа
    for(auto& i : hash_table[h]) // ищем ключ по хешу
    {
        if(i.first == key) // если находим ключ
            return true; // возвращаем что такой ключ есть
    }
    return false; // если прошли всю таблицу и не нашли ключ значит его в ней нет
}

void Put(const string& key, const string& value) // Функция добавления пары ключ-значение в таблицу
{
    int hash = Hash(key); // хешируем ключ
    if(!hash_table[hash].empty()) // проверяем что наш вектор не пустой
    { // i - это счётчик
        auto i = hash_table[hash].begin(); // будем проверять есть ли уже эта пара в таблице
        while(i != hash_table[hash].end()) // запускаем цикл пока не пройдём весь вектор
        {
            if(i->first == key) // если нашли такю же пару
            {
                i->second = value;
                return; // прекращаем работу функции
            }
            ++i;
        }
    } // если такой пары нет в векторе
    hash_table[hash].push_back({key, value}); // записываем наше значение и ключ
    key_table.push_back(key); // записываем ключ
}

void Delete(const string& key) // Функция удаления пары из таблицы
{
    int hash = Hash(key); // хешируем элемент
    if(hash_table[hash].empty()) // если вектор пуст
    {
        return; // прекращаем работу программы
    }
    auto i = hash_table[hash].begin(); // вводи наш счётчик для прохода по ветору
    while(i != hash_table[hash].end()) // цикл пока вектор не закочиться
    {
        if(i->first == key) // если встречаем наш ключ
        {
            hash_table[hash].erase(i); // удаляем его
            auto j = key_table.begin(); // также запускаем цикл, вводим счётчик, ищем и удаляем ключ из вектора ключей
            while(j != key_table.end())
            {
                if(*j == key){
                    key_table.erase(j);
                    return;
                }
                ++j;
            }
            return;
        }
        ++i;
    }
}

void prev(const string& key) // Функция поиска для предыдущего ключа
{
    if(Get_bool(key)) // проверяем что наш ключ есть в таблице
    {
        if((key_table.empty()) || key_table[0] == key) // если вектор пуст или наш ключ первый (предудущего у него нет)
            fout << "none\n";
        for(int i = 0; i < key_table.size(); i++) // ищем наш ключ в нашей таблице ключей
        {
            if(key_table[i] == key) // если нашли нужный ключ
            {
                Get(key_table[i - 1]); // выводим предыдущий
                return;
            }
        }
    }
    else
        fout << "none\n"; // если не нашли ключ
}

void next(const string& key) // Функция поиска для следующего ключа (анологично предыдущей функции)
{
    if(Get_bool(key)){
        if((key_table.empty()) || (key_table[key_table.size() - 1] == key)){
            fout << "none\n";
            return;
        }
        for(int i = 0; i < key_table.size(); i++){
            if(key_table[i] == key){
                Get(key_table[i + 1]);
                return;
            }
        }
    }
    else
        fout << "none\n";
}

int main(){
    hash_table.resize(100001); // задаём размер таблице
    string com;
    string key;
    string node;
    while(fin >> com){
        if(com == "put"){
            fin >> key;
            fin >> node;
            Put(key, node);
        }
        if(com == "delete"){
            fin >> key;
            Delete(key);
        }
        if(com == "get"){
            fin >> key;
            Get(key);
        }
        if(com == "prev"){
            fin >> key;
            prev(key);
        }
        if(com == "next"){
            fin >> key;
            next(key);
        }
    }
    return 0;
}
