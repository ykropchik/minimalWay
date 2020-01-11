/*
 * Дан файл типа: A | B | C , где A - пункт отправление (char[]), B - пункт назначения (char[]), C - расстояние
 * Найти кратчайший путь "из -> в" заданный пользователем
 * Максимальная последовательность может быть 4 пункта
 */

#include <iostream>
#include "src/lib.h"

using namespace std;

RoadInfo *mapPoints;
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
    readFile(inputFile, mapPoints, quantityRoad);

    /**-----Подсчет кол-ва пунктов-----**/
    quantityPoint = countingPoints(mapPoints, quantityRoad);

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
    getline(cin, start);
    cout << "Введите конечный пункт: \n";
    getline(cin, finish);

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