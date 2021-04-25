#include <fstream>
#include <algorithm>

using namespace std;

struct element // Создаём структура для описания элемента
{
	int value; // само число
	int left; // индекс левого ребёнка
	int right; // индекс правого ребёнка
};

/* Мы спускаемся по этажемам бин. дерева и рассматриваем только те элементы, которые имеют детей.
* Если детей нет, то мы не спускаемся. В итоге дойдя до последних детей мы начинаем подниматься на верх каждый раз 
* добовляя к height(высота) + 1 за каждый этаж. Спускаемся мы за счёт рекурсии, а когда последняя рекурся вернёт значения мы начнём подниматься.
*/

int find_height(element* tree, int h) // Рекрусивна функция поиска высота бмнарного дерева
{
	if (h == -1) // если у элемента нет детей, то спуск не происходит
		return 0;
	else  // если дети есть то мы спускаемся и расматриваем детей как элемент
		return max(find_height(tree, tree[h].left), find_height(tree, tree[h].right)) + 1; // на каждой благополучной итерации спуска max + 1
}

int main()
{
	ifstream fin("height.in");
	ofstream fout("height.out");
	int n;
	fin >> n;
	element* tree = new element[n];
	for (int i = 0; i < n; i++)
	{
		fin >> tree[i].value >> tree[i].left >> tree[i].right;
		tree[i].left--;
		tree[i].right--;
	}
	if (n == 0) // если элементов в дереве нет, то высота равна нулю
		fout << 0;
	else
		fout << find_height(tree, 0) << endl; // иначе ищем высоту
	fin.close();
	fout.close();
	return 0;
}