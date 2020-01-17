//
// Created by YKROPCHIK on 14.11.2019.
//

#include "gtest/gtest.h"
#include "src/lib.h"

using namespace std;

TEST(wayIsFounded, expectedResult){
    RoadInfo *mapPoints;
    string start, finish;   // Начальный и конечный пункт
    string *way = nullptr;
    int quantityRoad (0);   // Количество дорог
    int wayLength(0);          // Кол-во пунктов самого короткого пути
    int foundedLength;

    /**-----Читаю файл и заполняю массив-----**/
    ifstream inputFile("../input.txt");
    readFile(inputFile, mapPoints, quantityRoad);

    /**-----Получение начала и конца пути-----**/
    start = "Санкт-Петербург";
    finish = "Екатеринбург";

    /**-----Запускаем поиск-----**/
    foundedLength = findingWay(mapPoints, quantityRoad, start, finish, way, wayLength);
    EXPECT_EQ(foundedLength, 2479);

    /**-----Получение начала и конца пути-----**/
    start = "Санкт-Петербург";
    finish = "Москва";

    /**-----Запускаем поиск-----**/
    foundedLength = findingWay(mapPoints, quantityRoad, start, finish, way, wayLength);
    EXPECT_EQ(foundedLength, 712);
}

TEST(wayNotFounded, expectedResult){
    RoadInfo *mapPoints;
    string start, finish;   // Начальный и конечный пункт
    string *way = nullptr;
    int quantityRoad (0);   // Количество дорог
    int wayLength(0);          // Кол-во пунктов самого короткого пути
    int foundedLength;

    /**-----Читаю файл и заполняю массив-----**/
    ifstream inputFile("../input.txt");
    readFile(inputFile, mapPoints, quantityRoad);

    /**-----Получение начала и конца пути-----**/
    start = "Вологда";
    finish = "Владивосток";

    /**-----Запускаем поиск-----**/
    foundedLength = findingWay(mapPoints, quantityRoad, start, finish, way, wayLength);
    EXPECT_EQ(foundedLength, -1);
}
int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}