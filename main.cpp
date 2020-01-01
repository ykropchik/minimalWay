/*
 * Дан файл типа: A | B | C , где A - пункт отправление (char[]), B - пункт назначения (char[]), C - расстояние
 * Найти кратчайший путь "из -> в" заданный пользователем
 * Максимальная последовательность может быть 4 пункта
 */
//#include <iostream>
//#include <fstream>
//#include "src/lib.h"
//
//using namespace std;
//
//roadInfo *information = new roadInfo[10];;
//unsigned int sizeArray;
//unsigned int *matrix;
//
//int main() {
//     try{
//         ifstream inputFile("../input.txt");
//
//         try{
//             readFile(inputFile, information, sizeArray);
//         } catch (invalid_argument &err){
//             cout << "Ошибка! " << err.what();
//         }
//     } catch(invalid_argument &err){
//         cout << "Ошибка! " << err.what();
//     }
//
//    for (int i = 0; i <= sizeArray; ++i) {
//        cout << information[i].firstPoint << "|" << information[i].secondPoint << "|" << information[i].length << "\quantityPoint";
//    }
//    return 0;
//}
/*
#include <iostream>
#include <windows.h>
using namespace std;

struct item { //структура для описания элемента карты
    int s,c; //начальный и конечный узлы
    int v; //"вес" пути
};

const int m = 9; //количество путей по графу
struct item map[m] = { //все пути, нумерация узлов с нуля
        {0,1,1}, {0,2,1}, {2,3,1}, {1,4,1}, {2,4,1},
        {4,5,1}, {4,7,1}, {5,6,1}, {6,7,1}
};
const int n = 8; //количество вершин графа
int road[n]; //номера узлов текущей "дороги"
bool incl[n]; //true, если i-ая вершина включена в путь
int way[n]; //искомый самый короткий путь
int waylen; //его длина
int start, finish; //начальная и конечная вершины
bool found;
int len; //найденный "вес" маршрута
int c_len; //текущий "вес" маршрута

int find (int s, int c) { //вес пути из s и c или 0, если пути нет
    for (int i=0; i<m; i++)
        if (map[i].s==s && map[i].c==c ||
            map[i].s==c && map[i].c==s) return map[i].v;
    return 0;
}

void step (int s, int f, int p) { //рекурсивный поиск шага пути
    int c; //номер вершины, куда делаем шаг
    if (s==f) { //путь найден
        found = true; //поставить флажок "найдено"
        len = c_len; //запомнить общий вес пути
        waylen = p; //запомнить длину пути (количество узлов)
        for (int i=0; i<waylen; i++) way[i] = road[i]; //запомнить сам путь
    }
    else { //выбор очередной точки
        for (c=0; c<n; c++) { //проверяем все вершины
            int w = find(s,c); //есть ли путь из s в c
            if (w && !incl[c] && (len==0 || c_len+w<len)) { //нужная точка не включена?
                road[p] = c; //включить точку в путь
                incl[c] = true; //пометить как включенную
                c_len += w; //учесть в общем весе пути
                step (c,f,p+1); //вызвать себя для поиска следующей точки
                road[p] = 0; //вернуть всё как было
                incl[c] = false;
                c_len -= w;
            }
        }
    }
}

int main () {
    //Инициализация данных:
    for (int i=0; i<n; i++) {
        road[i]=way[i]=0; incl[i] = false;
    }
    len = c_len = waylen = 0;

    start = 0; //начало пути - нумерация с 0
    finish = 7; //конец пути - нумерация с 0
    road[0] = start; //первую точку внесли в маршрут
    incl[start] = true; //и пометили как включённую
    found = false; //но путь пока не найден
    step (start,finish,1); //ищем вторую точку

    if (found) {
        cout << "Way is";
        for (int i=0; i<waylen; i++) cout << " " << way[i];
        cout << ", weight is " << len;
    }
    else cout << "Way not found!";
    cout << endl;
    system ("pause");
    return 0;
} */

#include <iostream>
#include "src/lib.h"

using namespace std;

RoadInfo *map;
//set <char*> points;     // Множество пунктов
string *points;
bool isFound;
string start;
string finish;   // Начальный и конечный пункт
int quantityRoad (0);   // Количество дорог
int quantityPoint(0);   // Количество пунктов
int foundedLength;      // Найденный "вес" маршрута
int actualLength;       // Текущий "вес" маршрута
int wayLength;          // Длина самого короткого пути

int countingPoints(RoadInfo *roads, int countRoads){
    set <string> pointsSet;

    for (int i = 0; i < countRoads; ++i) {
        pointsSet.insert(roads[i].startPoint);
        pointsSet.insert(roads[i].endPoint);
    }

    points = new string[pointsSet.size()];

    pointsSet.clear();

    int count(0);
    for (int j = 0; j < countRoads; ++j) {
        if (pointsSet.count(roads[j].startPoint) == 0){
            points[count] = roads[j].startPoint;
            pointsSet.insert(roads[j].startPoint);
            ++count;
        }

        if (pointsSet.count(roads[j].endPoint) == 0){
            points[count] = roads[j].endPoint;
            ++count;
        }
        pointsSet.insert(roads[j].endPoint);
    }

    return count;
}

int main () {

    /**-----Читаю файл и заполняю массив-----**/
    ifstream inputFile("../input.txt");
    readFile(inputFile, map, quantityRoad);

    /**-----Подсчет кол-ва пунктов-----**/
    quantityPoint = countingPoints(map, quantityRoad);

    string road[quantityPoint];          // Номера узлов текущей "дороги"
    bool isIncluded[quantityPoint];     //true, если i-ая вершина включена в путь
    string way[quantityPoint];           // Искомый самый короткий путь

    /**-----Обнуление массивов-----**/
    for (int i = 0; i < quantityPoint; i++) {
        road[i] = way[i] = "";
        isIncluded[i] = false;
    }

    foundedLength = actualLength = wayLength = 0;

    /**-----Получение начала и конца пути-----**/
    cout << "Введите начальный пункт: \n";
    cin >> start;
    cout << "Введите конечный пункт: \n";
    cin >> finish;

    /**-----Начинаем поиск-----**/
    road[0] = start;                                        // Первую точку внесли в маршрут
    isIncluded[0] = true;                                   // Пометили как включённую
    isFound = false;                                        // Но путь пока не найден
    step (start, finish, 1, road, way, isIncluded);       // Ищем вторую точку

    /**-----Выводим результат-----**/
    if (isFound) {
        cout << "Маршрут " << start << " - " << finish << " найден!\n";
        cout << way[0];
        for (int i = 1; i < wayLength; i++) cout << " - " << way[i];
        cout << ", длина маршрута: " << foundedLength << " км";
    }
    else cout << "Путь не найден :(";
    cout << endl;
    return 0;
}