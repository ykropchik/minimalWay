//
// Created by YKROPCHIK on 23.11.2019.
//

#include <fstream>
#include <set>

struct RoadInfo {
    std::string startPoint, endPoint;   // Начальный и конечный пункт
    int length;                         // Длина дороги
};

void readFile(std::ifstream &inputFile, RoadInfo *&roadInfo, int &quantityRoad);
int countingPoints(RoadInfo *roads, int countRoads, std::string *&points);
int findingWay(RoadInfo *mapPoints, int quantityRoad, std::string start, std::string finish, std::string *&way, int &wayLength);