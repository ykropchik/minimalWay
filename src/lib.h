//
// Created by YKROPCHIK on 23.11.2019.
//

#include <fstream>
#include <set>

struct RoadInfo {
    std::string startPoint, endPoint;
    //char *startPoint, *endPoint;    // Начальный и конечный пункт
    int length;                     // Длина дороги
};

void readFile(std::ifstream &inputFile, RoadInfo *&roadInfo, int &quantityRoad);
int countingPoints(RoadInfo *roads, int countRoads);
void step (const std::string &startPoint, const std::string &finishPoint, int p, std::string *road, std::string *way, bool isIncluded[]);