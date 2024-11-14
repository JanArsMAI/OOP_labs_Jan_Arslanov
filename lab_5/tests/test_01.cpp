#include "../src/array.cpp"
#include <gtest/gtest.h>

TEST(ArrayTest, InitialCapacity) {
    Array<int> arr(10);
    EXPECT_EQ(arr.get_capacity(), 10);
    EXPECT_EQ(arr.get_size(), 0);
}

TEST(ArrayTest, PushBack) {
    Array<int> arr(2);
    arr.push_back(10);
    arr.push_back(20);
    EXPECT_EQ(arr.get_size(), 2);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
}

TEST(ArrayTest, PushBackWithResize) {
    Array<int> arr(1);
    arr.push_back(10);
    arr.push_back(20);
    EXPECT_EQ(arr.get_size(), 2);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_GT(arr.get_capacity(), 1);
}

TEST(ArrayTest, ClearArray) {
    Array<int> arr(3);
    arr.push_back(10);
    arr.push_back(20);
    arr.clear();
    EXPECT_EQ(arr.get_size(), 0);
    EXPECT_TRUE(arr.is_empty());
    EXPECT_NO_THROW(arr.push_back(30));
}

TEST(ArrayTest, InsertSingleElement) {
    Array<int> arr(3);
    arr.push_back(10);
    arr.push_back(30);
    arr.insert(arr.begin() + 1, 20);
    EXPECT_EQ(arr.get_size(), 3);
    EXPECT_EQ(arr[1], 20);
}

TEST(ArrayTest, EraseSingleElement) {
    Array<int> arr(3);
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);
    arr.erase(arr.begin() + 1);
    EXPECT_EQ(arr.get_size(), 2);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 30);
}

TEST(ArrayTest, OutOfRangeAccess) {
    Array<int> arr(2);
    arr.push_back(10);
    arr.push_back(20);
    EXPECT_THROW(arr[2], std::out_of_range);
}

TEST(ArrayTest, InsertMultipleElements) {
    Array<int> arr(5);
    arr.push_back(10);
    arr.push_back(20);
    arr.insert(arr.begin() + 1, 15, 2);
    EXPECT_EQ(arr.get_size(), 4);
    EXPECT_EQ(arr[1], 15);
    EXPECT_EQ(arr[2], 15);
}

TEST(ArrayTest, EraseRangeOfElements) {
    Array<int> arr(5);
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);
    arr.push_back(40);
    arr.erase(arr.begin() + 1, arr.begin() + 3);
    EXPECT_EQ(arr.get_size(), 2);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 40);
}

TEST(ArrayTest, PushBackAndPopBack) {
    Array<int> arr(3);
    arr.push_back(10);
    arr.push_back(20);
    arr.pop_back();
    EXPECT_EQ(arr.get_size(), 1);
    EXPECT_EQ(arr[0], 10);
    arr.pop_back();
    EXPECT_TRUE(arr.is_empty());
}

TEST(ArrayTest, InsertElementAtBeginning) {
    Array<int> arr(3);
    arr.push_back(10);
    arr.push_back(20);
    arr.insert(arr.begin(), 5);
    EXPECT_EQ(arr.get_size(), 3);
    EXPECT_EQ(arr[0], 5);
}

TEST(ArrayTest, InsertElementAtEnd) {
    Array<int> arr(3);
    arr.push_back(10);
    arr.push_back(20);
    arr.insert(arr.end(), 30);
    EXPECT_EQ(arr.get_size(), 3);
    EXPECT_EQ(arr[2], 30);
}

TEST(ArrayTest, SwapArrays) {
    Array<int> arr1(3);
    arr1.push_back(10);
    arr1.push_back(20);
    Array<int> arr2(3);
    arr2.push_back(30);
    arr2.push_back(40);
    arr1.swap(arr2);
    EXPECT_EQ(arr1.get_size(), 2);
    EXPECT_EQ(arr1[0], 30);
    EXPECT_EQ(arr2[0], 10);
}

TEST(ArrayTest, ReserveCapacity) {
    Array<int> arr(2);
    arr.reserve_data(10);
    EXPECT_EQ(arr.get_capacity(), 10);
}

TEST(ArrayTest, ResizeArrayOnInsertBeyondCapacity) {
    Array<int> arr(2);
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);
    EXPECT_GT(arr.get_capacity(), 2);
    EXPECT_EQ(arr[2], 30);
}

TEST(ArrayTest, CheckIsEmpty) {
    Array<int> arr(3);
    EXPECT_TRUE(arr.is_empty());
    arr.push_back(10);
    EXPECT_FALSE(arr.is_empty());
}