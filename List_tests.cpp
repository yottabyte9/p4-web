// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"

using namespace std;

// Add your test cases here

TEST(test_push_pop) {
    List<int> current;
    ASSERT_TRUE(current.empty());
    ASSERT_TRUE(current.size() == 0);
    current.push_front(5);
    current.push_back(3);
    current.push_front(16);
    current.push_back(7);
    current.push_front(56);
    current.push_front(0);
    current.push_back(-4);
    ASSERT_FALSE(current.empty());
    ASSERT_TRUE(current.size() == 7);
    ASSERT_TRUE(current.front() == 0);
    current.pop_front();
    ASSERT_TRUE(current.back() == -4);
    current.pop_back();
    ASSERT_TRUE(current.front() == 56);
    current.pop_front();
    ASSERT_TRUE(current.back() == 7);
    current.pop_back();
    ASSERT_TRUE(current.size() == 3);
    ASSERT_TRUE(current.front() == 16);
    current.pop_front();
    ASSERT_TRUE(current.back() == 3);
    current.pop_back();
    ASSERT_TRUE(current.front() == 5);
    ASSERT_TRUE(current.back() == 5);
    current.pop_front();
    current.push_front(54);
    current.pop_back();
    ASSERT_TRUE(current.empty());
    ASSERT_TRUE(current.size() == 0);
} 

TEST(test_clear_big_three) {
    List<int> current1;
    current1.push_back(3);
    current1.push_front(5); 
    current1.push_front(16);

    List<int>::Iterator i = current1.begin();
    i++;

    current1.push_back(7);
    current1.push_front(56);
    current1.push_front(0);
    current1.push_back(-4);
    List<int> current2(current1);
    List<int> current3;
    current3 = current1;
    ASSERT_TRUE(current2.front() == 0);
    ASSERT_TRUE(current3.back() == -4);
    List<bool> current4;
    current4.push_front(true);
    ASSERT_TRUE(current4.size() == 1);
    ASSERT_FALSE(current4.empty());
}



TEST_MAIN()
