//
// Created by YKROPCHIK on 23.11.2019.
//
#include "lib.h"

using namespace std;

int countingPoints(RoadInfo *roads, int countRoads, string *&points){
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

int find (RoadInfo *mapPoints, const string &startPoint, const string &endPoint, int quantityRoad) { //вес пути из startPoint и endPoint или 0, если пути нет
    for (int i=0; i < quantityRoad; i++) {
        if ((mapPoints[i].startPoint == startPoint && mapPoints[i].endPoint == endPoint) ||
            ((mapPoints[i].startPoint == endPoint) && mapPoints[i].endPoint == startPoint)) {
            return mapPoints[i].length;
        }
    }
    return 0;
}

void step (RoadInfo *mapPoints, const string &startPoint, const string &finishPoint, int p, string *road, string *way,
           bool isIncluded[], bool &isFound, int &foundedLength, int &actualLength, int &wayLength, const int &quantityPoint, const int &quantityRoad, string *points) { //рекурсивный поиск шага пути
    int c; //номер вершины, куда делаем шаг
    if (startPoint == finishPoint) { //путь найден
        isFound = true; //поставить флажок "найдено"
        foundedLength = actualLength; //запомнить общий вес пути
        wayLength = p; //запомнить длину пути (количество узлов)
        for (int i=0; i < wayLength; i++){
            way[i] = road[i]; //запомнить сам путь
        }
    }
    else { //выбор очередной точки
        for (c = 0; c < quantityPoint; c++) { //проверяем все вершины
            string test = points[c];
            int weight = find(mapPoints, startPoint, points[c], quantityRoad); //есть ли путь из startPoint в endPoint
            if (weight && !isIncluded[c] && (foundedLength == 0 || actualLength + weight < foundedLength)) { //нужная точка не включена?
                road[p] = points[c]; //включить точку в путь
                isIncluded[c] = true; //пометить как включенную
                actualLength += weight; //учесть в общем весе пути
                step (mapPoints, points[c], finishPoint, p+1, road, way, isIncluded,
                      isFound, foundedLength, actualLength,
                      wayLength, quantityPoint, quantityRoad, points); //вызвать себя для поиска следующей точки
                road[p] = ""; //вернуть всё как было
                isIncluded[c] = false;
                actualLength -= weight;
            }
        }
    }
}

int findingWay(RoadInfo *mapPoints, int quantityRoad, string start, string finish, string *&way, int &wayLength){

    string *points = nullptr;
    bool isFound;
    int foundedLength;      // Найденный "вес" маршрута
    int actualLength;       // Текущий "вес" маршрута
    int quantityPoint(0);   // Количество пунктов

    foundedLength = actualLength = wayLength = 0;

    /**-----Подсчет кол-ва пунктов-----**/
    quantityPoint = countingPoints(mapPoints, quantityRoad, points);

    string road[quantityPoint];         // Номера узлов текущей "дороги"
    bool isIncluded[quantityPoint];     //true, если i-ая вершина включена в путь
    way = new string[quantityPoint];    // Искомый самый короткий путь

    /**-----Обнуление массивов-----**/
    for (int i = 0; i < quantityPoint; i++) {
        road[i] = way[i] = "";
        isIncluded[i] = false;
    }

    /**-----Начинаем поиск-----**/
    road[0] = start;                                        // Первую точку внесли в маршрут
    isIncluded[0] = true;                                   // Пометили как включённую
    isFound = false;                                        // Но путь пока не найден
    step (mapPoints, start, finish, 1, road, way, isIncluded,
            isFound, foundedLength, actualLength,
            wayLength, quantityPoint, quantityRoad, points);       // Ищем вторую точку

    if (isFound){
        return foundedLength;
    }

    return -1;
}