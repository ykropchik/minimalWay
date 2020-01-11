//
// Created by YKROPCHIK on 23.11.2019.
//
#include "lib.h"

using namespace std;

extern RoadInfo *mapPoints;
extern string *points;
extern bool isFound;
extern string start, finish;   // Начальный и конечный пункт
extern int quantityRoad;   // Количество дорог
extern int quantityPoint;   // Количество пунктов
extern int foundedLength;      // Найденный "вес" маршрута
extern int actualLength;       // Текущий "вес" маршрута
extern int wayLength;          // Длина самого короткого пути

int find (const string &startPoint, const string &endPoint) { //вес пути из startPoint и endPoint или 0, если пути нет
    for (int i=0; i < quantityRoad; i++) {
        if ((mapPoints[i].startPoint == startPoint && mapPoints[i].endPoint == endPoint) ||
            ((mapPoints[i].startPoint == endPoint) && mapPoints[i].endPoint == startPoint)) {
            return mapPoints[i].length;
        }
    }
    return 0;
}

void step (const string &startPoint, const string &finishPoint, int p, string *road, string *way, bool isIncluded[]) { //рекурсивный поиск шага пути
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
            int weight = find(startPoint, points[c]); //есть ли путь из startPoint в endPoint
            if (weight && !isIncluded[c] && (foundedLength == 0 || actualLength + weight < foundedLength)) { //нужная точка не включена?
                road[p] = points[c]; //включить точку в путь
                isIncluded[c] = true; //пометить как включенную
                actualLength += weight; //учесть в общем весе пути
                step (points[c], finishPoint, p+1, road, way, isIncluded); //вызвать себя для поиска следующей точки
                road[p] = ""; //вернуть всё как было
                isIncluded[c] = false;
                actualLength -= weight;
            }
        }
    }
}
