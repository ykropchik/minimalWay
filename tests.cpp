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

void zeroing(string *road, string *way, bool *isIncluded){
    for (int i = 0; i < quantityPoint; i++) {
        road[i] = way[i] = "";
        isIncluded[i] = false;
    }
}

TEST(findWay, expectedResult){
    string *way = nullptr;
    string *road = nullptr;
    bool *isIncluded = nullptr;

    /**-----Читаю файл и заполняю массив-----**/
    ifstream inputFile("../input.txt");
    readFile(inputFile, mapPoints, quantityRoad);

    /**-----Подсчет кол-ва пунктов-----**/
    quantityPoint = countingPoints(mapPoints, quantityRoad);

    road = new string[quantityPoint];          // Номера узлов текущей "дороги"
    isIncluded = new bool[quantityPoint];     //true, если i-ая вершина включена в путь
    way = new string[quantityPoint];           // Искомый самый короткий путь
    /**-----Обнуление массивов-----**/
    zeroing(road, way, isIncluded);

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
    zeroing(road, way, isIncluded);

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
    zeroing(road, way, isIncluded);

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
    zeroing(road, way, isIncluded);

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
    zeroing(road, way, isIncluded);

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