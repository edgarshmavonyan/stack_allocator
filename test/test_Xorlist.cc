#include <gtest/gtest.h>
#include "xorlist/xorlist.h"
#include "test/testGeneration.h"
#include "test/testTime.h"
#include <deque>


TEST(XorList, DISABLED_randomSeq_std) {
    auto sequence = generateSequence(TEST_SIZE);
    double stdListTime = doRandomTesting<int, std::list, std::allocator>(sequence);
    double xorListTime = doRandomTesting<int, XorList, std::allocator>(sequence);
    std::cout << "random sequence" << std::endl;
    std::cout << "XorList compare with std::list on std::allocator (int)" << std::endl;
    std::cout << "std::list time: " << stdListTime << std::endl;
    std::cout << "XorList time: " << xorListTime << std::endl;
}

TEST(XorList, DISABLED_randomPushBack_std) {
    auto sequence = generateInsert(TEST_SIZE);
    double stdListTime = doInsertTesting<int, std::list, std::allocator>(sequence);
    double xorListTime = doInsertTesting<int, XorList, std::allocator>(sequence);
    std::cout << "random insert" << std::endl;
    std::cout << "XorList compare with std::list on std::allocator (int)" << std::endl;
    std::cout << "std::list time: " << stdListTime << std::endl;
    std::cout << "XorList time: " << xorListTime << std::endl;
}

TEST(XorList, iterator_test) {
    XorList<int> myXorList;
    for (int i = 0; i < 10; i++)
        myXorList.push_back(5);
    for (auto it = myXorList.begin(); it != myXorList.end(); ++it)
        ASSERT_EQ(*it, 5);
}

TEST(XorList, insert_after) {
    XorList<int> myXorList;
    for (int i = 0; i < 10; i++)
        myXorList.push_back(5);
    auto iter = myXorList.begin();
    for (int i = 0; i < 3; i++, ++iter);
    auto newIter = myXorList.insert_after(iter, 100);
    ASSERT_EQ(*newIter, 100);
    ASSERT_EQ(myXorList.size(), 11);
    auto thirdIter = myXorList.insert_after(newIter, 1000);
    ASSERT_EQ(*thirdIter, 1000);
    ASSERT_EQ(myXorList.size(), 12);
}

TEST(XorList, insert_before) {
    XorList<int> myXorList;
    for (int i = 0; i < 10; i++)
        myXorList.push_back(5);
    auto iter = myXorList.begin();
    auto newIter = myXorList.insert_before(iter, 100);
    ASSERT_EQ(*newIter, 100);
    ASSERT_EQ(myXorList.size(), 11);
    auto thirdIter = myXorList.insert_before(newIter, 1000);
    ASSERT_EQ(*thirdIter, 1000);
    ASSERT_EQ(myXorList.size(), 12);
    for (int i = 0; i < 3; i++, thirdIter++);
    auto fourthIter = myXorList.insert_before(thirdIter, 21);
    ASSERT_EQ(*fourthIter, 21);
    ASSERT_EQ(myXorList.size(), 13);
}

TEST(XorList, constructor) {
    XorList<int> myXorList;
    for (int i = 0; i < 10; i++)
        myXorList.push_back(5);
    auto b(myXorList);
    for (auto& elem: b)
        std::cout << elem;
}

int main(int argv, char* argc[]) {
    std::list a;
    a.push_back(5);
    std::list<int>::iterator it = a.begin();
    testing::InitGoogleTest(&argv, argc);
    return RUN_ALL_TESTS();
}