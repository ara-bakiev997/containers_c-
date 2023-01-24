//
// Created by Qyburn Bongo on 1/24/23.
//

#include <gtest/gtest.h>

#include <iostream>
#include <map>

//using namespace s21;

class S21Map_test : public ::testing::Test {
protected:
    void SetUp() override {}


};

TEST_F(S21Map_test, emplace) {
    std::cout<<"hello"<<"\n";
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}