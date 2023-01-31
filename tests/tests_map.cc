//
// Created by Qyburn Bongo on 1/24/23.
//

#include <gtest/gtest.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <iterator>
#include "../src/sorted_container/associative_container/s21_map.h"

using namespace s21;

class S21Map_test : public ::testing::Test {
protected:
    void SetUp() override {}
    S21Map<int, int> map;
    std::map<int, int> std_map;


};

TEST_F(S21Map_test, insert_delete) {

//    map.insert(1, 25);
//    map.insert(0, 4);
//    map.insert(4, 4);
//    std_map.insert(1, 52);
//    std_map.insert(0, 4);
//    std_map.insert(4, 4);
//    EXPECT_EQ(map.size(), 4);
//    map.clear();

// создаем массив на 100+ значений
    std::vector<int> v;
    for (auto i = 0; i < 100; ++i) {
        v.insert(v.begin() + i, i);
    }
//    принтуем для проверки
//    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
//    std::cout << "\n";

// перемешиваем значения в массиве в случайном порядке
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(v.begin(), v.end(), g);

//    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
//    std::cout << "\n";


//закидываем значения в set/map/tree
    std::set<int> v2;
    for (auto i = 0; i < 100; ++i) {
       v2.insert(i);
//        std::copy(v2.begin(), v2.end(), std::ostream_iterator<int>(std::cout, " "));
//        std::cout << "\n";
    }
 //   удаляем значения в set/map/tree  в случайном порядке
    for (auto i = 0; i < 100; ++i) {
        v2.erase(v[i]);
        std::cout << "delete key ="<< v[i]<< "\n";
    std::copy(v2.begin(), v2.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
    }


    //    map.insert(2);
//    map.insert(3);
//    map.insert(4);
//    map.insert(6);
//    map.insert(5);
//    map.insert(8);
    
//    map.print();
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}