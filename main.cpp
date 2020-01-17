/*
 * Дан файл типа: A | B | C , где A - пункт отправление (char[]), B - пункт назначения (char[]), C - расстояние
 * Найти кратчайший путь "из -> в" заданный пользователем
 * Максимальная последовательность может быть 4 пункта
 */

#include <iostream>
#include "src/lib.h"

using namespace std;

int main () {

    RoadInfo *mapPoints;
    string start, finish;   // Начальный и конечный пункт
    string *way = nullptr;
    int quantityRoad (0);   // Количество дорог
    int wayLength(0);          // Кол-во пунктов самого короткого пути

    /**-----Читаю файл и заполняю массив-----**/
    ifstream inputFile("../input.txt");
    readFile(inputFile, mapPoints, quantityRoad);

    /**-----Получение начала и конца пути-----**/
    cout << "Введите начальный пункт: \n";
    getline(cin, start);
    cout << "Введите конечный пункт: \n";
    getline(cin, finish);

    /**-----Запускаем поиск-----**/
    int foundedLength = findingWay(mapPoints, quantityRoad, start, finish, way, wayLength);

    /**-----Выводим результат-----**/
    if (foundedLength != -1) {
        cout << "Маршрут " << start << " - " << finish << " найден!\n";
        cout << way[0];
        for (int i = 1; i < wayLength; i++) cout << " - " << way[i];
        cout << ", длина маршрута: " << foundedLength << " км";
    }
    else cout << "Путь не найден :(";
    cout << endl;
    return 0;
}