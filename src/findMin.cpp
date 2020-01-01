//
// Created by YKROPCHIK on 23.11.2019.
//
#include <string.h>
#include "lib.h"

extern RoadInfo *map;
//set <char*> points;     // Множество пунктов
extern char **points;
extern bool isFound;
extern char *start, *finish;   // Начальный и конечный пункт
extern int quantityRoad;   // Количество дорог
extern int quantityPoint;   // Количество пунктов
extern int foundedLength;      // Найденный "вес" маршрута
extern int actualLength;       // Текущий "вес" маршрута
extern int wayLength;          // Длина самого короткого пути

bool isEqual(const char *string1, const char *string2){
    int len = strlen(string1);
    int len2 = strlen(string2);
    if (strlen(string1) == strlen(string2)){
        for (int i = 0; i < strlen(string1); ++i) {
            if (string1[i] != string2[i]){
                return false;
            }
        }
    } else {
        return false;
    }

    return true;
}

int find (const char *startPoint, const char *endPoint) { //вес пути из startPoint и endPoint или 0, если пути нет
    for (int i=0; i < quantityRoad; i++) {
        if ((isEqual(map[i].startPoint, startPoint) && isEqual(map[i].endPoint, endPoint)) ||
            (isEqual(map[i].startPoint, endPoint) && isEqual(map[i].endPoint, startPoint))) {
            return map[i].length;
        }
    }
    return 0;
}

void step (const char *startPoint, const char *finishPoint, int p, char *road[], char *way[], bool isIncluded[]) { //рекурсивный поиск шага пути
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
                road[p] = nullptr; //вернуть всё как было
                isIncluded[c] = false;
                actualLength -= weight;
            }
        }
    }
}
