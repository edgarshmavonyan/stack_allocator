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
    auto const_it = myXorList.cbegin();
    for (auto it = myXorList.begin(); it != myXorList.end() && const_it != myXorList.cend(); ++it, ++const_it) {
        ASSERT_EQ(*it, 5);
        ASSERT_EQ(*const_it, 5);
        auto casted_const_it = XorList<int>::const_iterator(it);
        ASSERT_EQ(casted_const_it, const_it);
    }
}

TEST(XorList, reverse_iterator_test) {
    XorList<int> myXorList;
    for (int i = 0; i < 10; i++)
        myXorList.push_back(5);
    auto const_it = myXorList.crbegin();
    for (auto it = myXorList.rbegin(); it != myXorList.rend() && const_it != myXorList.crend(); ++it, ++const_it) {
        ASSERT_EQ(*it, 5);
        ASSERT_EQ(*const_it, 5);
        auto casted_const_it = XorList<int>::const_reverse_iterator(it);
        ASSERT_EQ(casted_const_it, const_it);
    }
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
    auto copied(myXorList);
    auto my_it = myXorList.begin();
    auto copy_it = copied.begin();
    for (; my_it != myXorList.end() && copy_it != copied.end(); ++my_it, ++copy_it)
        ASSERT_EQ(*my_it, *copy_it);
}

TEST(XorList, move_constructor) {
    XorList<int> myXorList;
    for (int i = 0; i < 10; i++)
        myXorList.push_back(5);
    XorList<int> movedXorList(std::move(myXorList));
    ASSERT_EQ(movedXorList.size(), 10);
    for (const auto& element: movedXorList)
        ASSERT_EQ(element, 5);
}

TEST(XorList, move_assign) {
    XorList<int> myXorList;
    for (int i = 0; i < 10; i++)
        myXorList.push_back(5);
    XorList<int> movedXorList;
    movedXorList = std::move(myXorList);
    ASSERT_EQ(movedXorList.size(), 10);
    for (const auto& element: movedXorList)
        ASSERT_EQ(element, 5);
}

TEST(XorList, front_back) {
    XorList<int> myXorList;
    for (int i = 0; i < 10; i++)
        myXorList.push_back(5);
    while (!myXorList.empty()) {
        ASSERT_EQ(myXorList.front(), *myXorList.begin());
        ASSERT_EQ(myXorList.back(), *myXorList.rbegin());
        myXorList.pop_front();
    }
}

int main(int argv, char* argc[]) {
    testing::InitGoogleTest(&argv, argc);
    return RUN_ALL_TESTS();
}