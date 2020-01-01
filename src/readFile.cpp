//
// Created by YKROPCHIK on 23.11.2019.
//
#include <fstream>
#include "lib.h"

using namespace std;

void readFile(ifstream &inputFile, RoadInfo *&map, int &quantityRoad){
    inputFile.seekg(0,ios_base::beg);

    char *temp = new char[1024];
    while (!inputFile.eof()){
        inputFile.getline(temp, 1024, '\n');
        ++quantityRoad;
    }

    map = new RoadInfo[quantityRoad];

    inputFile.seekg(0,ios_base::beg);
    for (int i = 0; !inputFile.eof() ; ++i) {
//        char *firstPointStr = new char[50];
//        char *secondPointStr = new char[50];
//        char *lengthStr = new char[50];

//        inputFile.getline(firstPointStr, 50, '|');
//        inputFile.getline(secondPointStr, 50, '|');
//        inputFile.getline(lengthStr, 50);

        string firstPointStr;
        string secondPointStr;
        string lengthStr;

        getline(inputFile, firstPointStr, '|');
        getline(inputFile, secondPointStr, '|');
        getline(inputFile, lengthStr);

        map[i].startPoint = firstPointStr;
        map[i].endPoint = secondPointStr;
        map[i].length = stoi(lengthStr);
    }
}
