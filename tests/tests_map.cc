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
using std::cout;
using std::endl;


class S21Map_test : public ::testing::Test {
protected:
    void SetUp() override {}
    S21Map<int, int> map;
    S21Map<int, int> map2;
    S21Map<int, std::string> map_s;
    std::map<int, int> std_map;
    std::map<int, std::string> std_map_s;
    S21Map<int, int> map3{{10, 50}, {8, 60}, {6, 70}};
    std::map<int, int> std_map3{{10, 50}, {8, 60}, {6, 70}};




};

TEST_F(S21Map_test, construct_il) {

    for (const auto &pair : std_map3) {
        EXPECT_EQ(map3.at(pair.first), std_map3.at(pair.first));
    }
}

TEST_F(S21Map_test, construct_copy) {
    S21Map<int, int> map4(map3);
    std::map<int, int> std_map4(std_map3);

//    for (auto &pair : std_map4) {
//        EXPECT_EQ(map4.at(pair.first), std_map4.at(pair.first));
//    }
}

TEST_F(S21Map_test, size) {
    map.insert(std::pair(1, 25));
    map.insert(std::pair(0, 43));
    map.insert(std::pair(4, 4));
    map.insert(std::pair(7, 11));
    map.insert(std::pair(-5, 28));
    std_map.insert(std::pair{1, 25});
    std_map.insert(std::pair(0, 43));
    std_map.insert(std::pair(4, 4));
    std_map.insert(std::pair(7, 11));
    std_map.insert(std::pair(-5, 28));
    EXPECT_EQ(map.size(), std_map.size());

//    cout << map3[8]<<endl;
//
//    cout << std_map3[8]<<endl;
}

TEST_F(S21Map_test, max_size) {
    EXPECT_EQ(map.max_size(), std_map.max_size());
}

TEST_F(S21Map_test, clear) {
    map.insert(std::pair(1, 25));
    map.insert(std::pair(0, 43));
    map.insert(std::pair(4, 4));
    map.insert(std::pair(7, 11));
    map.insert(std::pair(-5, 28));
    std_map.insert(std::pair{1, 25});
    std_map.insert(std::pair(0, 43));
    std_map.insert(std::pair(4, 4));
    std_map.insert(std::pair(7, 11));
    std_map.insert(std::pair(-5, 28));
    EXPECT_EQ(map.size(), std_map.size());
    map.clear();
    EXPECT_EQ(map.size(), std_map.size());
    EXPECT_ANY_THROW(map.at(1));
    EXPECT_ANY_THROW(map.at(1));
}

TEST_F(S21Map_test, at) {
    map.insert(std::pair(1, 25));
    map.insert(std::pair(0, 43));
    map.insert(std::pair(4, 4));
    map.insert(std::pair(7, 11));
    map.insert(std::pair(-5, 28));
    std_map.insert(std::pair{1, 25});
    std_map.insert(std::pair(0, 43));
    std_map.insert(std::pair(4, 4));
    std_map.insert(std::pair(7, 11));
    std_map.insert(std::pair(-5, 28));

    for (const auto &pair : std_map) {
    EXPECT_EQ(map.at(pair.first), std_map.at(pair.first));
    }
    EXPECT_ANY_THROW(map.at(9));
    EXPECT_ANY_THROW(map.at(9));
}

TEST_F(S21Map_test, operator_brkt) {
    map.insert(std::pair(1, 25));
    map.insert(std::pair(0, 43));
    map.insert(std::pair(4, 4));
    map.insert(std::pair(7, 11));
    map.insert(std::pair(-5, 28));
    std_map.insert(std::pair{1, 25});
    std_map.insert(std::pair(0, 43));
    std_map.insert(std::pair(4, 4));
    std_map.insert(std::pair(7, 11));
    std_map.insert(std::pair(-5, 28));

    map[0];
    map = std::move(map);
    map[1] = 35;
    map[9];
    std_map[0];
    std_map[1] = 35;
    std_map[9];
    EXPECT_EQ(map[1], 35);
    EXPECT_EQ(map[0], std_map[0]);
    EXPECT_EQ(map[1], std_map[1]);
    EXPECT_EQ(map[9], std_map[9]);

    map_s.insert(std::pair(1, "25"));
    map_s.insert(std::pair(3, "50"));
    std_map_s.insert(std::pair{1, "25"});
    std_map_s.insert(std::pair{3, "50"});
    map_s[1] = "43";
    map_s[3];
    map_s[9];
    std_map_s[1] = "43";
    std_map_s[3];
    std_map_s[9];
    EXPECT_EQ(map_s[1], std_map_s[1]);
    EXPECT_EQ(map_s[3], std_map_s[3]);
    EXPECT_EQ(map_s[9], std_map_s[9]);
}

TEST_F(S21Map_test, empty) {
    EXPECT_TRUE(map.empty());
    EXPECT_TRUE(std_map.empty());
}

TEST_F(S21Map_test, insert_or_assign) {
    map.insert(std::pair(1, 25));
    map.insert(std::pair(0, 43));
    map.insert(std::pair(4, 4));
    map.insert(std::pair(7, 11));
    map.insert(std::pair(-5, 28));
    auto pr1 =map.insert_or_assign(9, 35);
    std_map.insert(std::pair{1, 25});
    std_map.insert(std::pair(0, 43));
    std_map.insert(std::pair(4, 4));
    std_map.insert(std::pair(7, 11));
    std_map.insert(std::pair(-5, 28));
    auto pr2 =std_map.insert_or_assign(9, 35);

    EXPECT_EQ(pr1.second, pr2.second);
    EXPECT_EQ((*(pr1.first)).second, (*(pr2.first)).second);
    auto pr3 =map.insert_or_assign(9, 48);
    auto pr4 =std_map.insert_or_assign(9, 48);
    EXPECT_EQ(pr3.second, pr4.second);
    EXPECT_EQ((*(pr1.first)).second, (*(pr2.first)).second);

    map_s.insert(std::pair(1, "25"));
    auto pr_s1 =map_s.insert_or_assign(9, "35");
    std_map_s.insert(std::pair{1, "25"});
    auto pr_s2 =std_map_s.insert_or_assign(9, "35");

    EXPECT_EQ(pr_s1.second, pr_s2.second);
    EXPECT_EQ((*(pr_s1.first)).second, (*(pr_s2.first)).second);
    auto pr_s3 =map_s.insert_or_assign(9, "48");
    auto pr_s4 =std_map_s.insert_or_assign(9, "48");
    EXPECT_EQ(pr_s3.second, pr_s4.second);
    EXPECT_EQ((*(pr_s3.first)).second, (*(pr_s4.first)).second);

}

TEST_F(S21Map_test, insert_delete) {

    map.insert(std::pair(1, 25));
    auto pr = map.insert(std::pair(0, 43));
    auto pr2 =map.insert_or_assign(1, 4);
    map.insert(std::pair(7, 11));
    map.insert(std::pair(-5, 28));
    auto pr3 = std_map.insert(std::pair{1, 25});
    std_map.insert(std::pair(1, 43));
    auto pr4 =std_map.insert_or_assign(4, 4);
    std_map.insert(std::pair(7, 11));
    std_map.insert(std::pair(-5, 28));

//    EXPECT_EQ(std_map.size(), 5);
//    map.clear();


    map.print();
//    cout<<map.max_size() << endl;
//    cout<<"std ="<<std_map.max_size() << endl;
//    cout<<map.size() << endl;
    cout<< (*(pr2.first)).second << endl;
//    cout<< (*(pr4.first)).second << endl;
    cout<< pr2.second << endl;
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}