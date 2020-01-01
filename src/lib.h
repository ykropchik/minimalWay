//
// Created by YKROPCHIK on 23.11.2019.
//
#ifndef NAMESPACES_LIB_H
#define NAMESPACES_LIB_H
#endif

#include <fstream>
#include <set>

using namespace std;

struct RoadInfo {
    char *startPoint, *endPoint;    // Начальный и конечный пункт
    int length;                     // Длина дороги
};

void readFile(ifstream &inputFile, RoadInfo *&roadInfo, int &quantityRoad);
void step (const char *startPoint, const char *finishPoint, int p, char *road[], char *way[], bool isIncluded[]);