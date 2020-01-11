//
// Created by YKROPCHIK on 14.11.2019.
//

#include "gtest/gtest.h"
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

TEST(findWay, expectedResult){
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

    /**-----Начинаем поиск-----**/
    start = "Санкт-Петербург";
    finish = "Москва";
    road[0] = start;                                        // Первую точку внесли в маршрут
    isIncluded[0] = true;                                   // Пометили как включённую
    isFound = false;                                        // Но путь пока не найден
    foundedLength = actualLength = wayLength = 0;
    step (start, finish, 1, road, way, isIncluded);       // Ищем вторую точку

    EXPECT_EQ(foundedLength, 712);

    /**-----Обнуление массивов-----**/
    for (int i = 0; i < quantityPoint; i++) {
        road[i] = way[i] = "";
        isIncluded[i] = false;
    }

    /**-----Начинаем поиск-----**/
    start = "Москва";
    finish = "Нижний-Новгород";
    road[0] = start;                                        // Первую точку внесли в маршрут
    isIncluded[0] = true;                                   // Пометили как включённую
    isFound = false;                                        // Но путь пока не найден
    foundedLength = actualLength = wayLength = 0;
    step (start, finish, 1, road, way, isIncluded);       // Ищем вторую точку

    EXPECT_EQ(foundedLength, 0);

    /**-----Обнуление массивов-----**/
    for (int i = 0; i < quantityPoint; i++) {
        road[i] = way[i] = "";
        isIncluded[i] = false;
    }

    /**-----Начинаем поиск-----**/
    start = "Москва";
    finish = "Екатеринбург";
    road[0] = start;                                        // Первую точку внесли в маршрут
    isIncluded[0] = true;                                   // Пометили как включённую
    isFound = false;                                        // Но путь пока не найден
    foundedLength = actualLength = wayLength = 0;
    step (start, finish, 1, road, way, isIncluded);       // Ищем вторую точку

    EXPECT_EQ(foundedLength, 1767);

    /**-----Обнуление массивов-----**/
    for (int i = 0; i < quantityPoint; i++) {
        road[i] = way[i] = "";
        isIncluded[i] = false;
    }

    /**-----Начинаем поиск-----**/
    start = "Санкт-Петербург";
    finish = "Самара";
    road[0] = start;                                        // Первую точку внесли в маршрут
    isIncluded[0] = true;                                   // Пометили как включённую
    isFound = false;                                        // Но путь пока не найден
    foundedLength = actualLength = wayLength = 0;
    step (start, finish, 1, road, way, isIncluded);       // Ищем вторую точку

    EXPECT_EQ(foundedLength, 1818);

    /**-----Обнуление массивов-----**/
    for (int i = 0; i < quantityPoint; i++) {
        road[i] = way[i] = "";
        isIncluded[i] = false;
    }

    /**-----Начинаем поиск-----**/
    start = "Нижний Новгород";
    finish = "Самара";
    road[0] = start;                                        // Первую точку внесли в маршрут
    isIncluded[0] = true;                                   // Пометили как включённую
    isFound = false;                                        // Но путь пока не найден
    foundedLength = actualLength = wayLength = 0;
    step (start, finish, 1, road, way, isIncluded);       // Ищем вторую точку

    EXPECT_EQ(foundedLength, 683);
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}