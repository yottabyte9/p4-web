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

TEST(test_big_three) {
    List<int> current1;
    current1.push_back(3);
    current1.push_front(5); 
    current1.push_front(16);
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

TEST(push_pop_all) {
    List<double> current5;
    current5.push_front(5.8);
    current5.push_front(5.9);
    current5.push_front(11.3);
    ASSERT_TRUE(current5.front() == 11.3);
    current5.pop_front();
    ASSERT_TRUE(current5.front() == 5.9);
    current5.pop_front();
    ASSERT_TRUE(current5.front() == 5.8);
    current5.pop_front();
    ASSERT_TRUE(current5.size() == 0);
    current5.push_back(6.8);
    current5.push_back(6.9);
    current5.push_back(12.3);
    ASSERT_TRUE(current5.back() == 12.3);
    current5.pop_back();
    ASSERT_TRUE(current5.back() == 6.9);
    current5.pop_back();
    ASSERT_TRUE(current5.back() == 6.8);
    current5.pop_back();
    ASSERT_TRUE(current5.size() == 0);
}

TEST(test_no_elements){
    List<int> current1;
    current1.push_back(3);
    current1.pop_back();
    ASSERT_TRUE(current1.empty());
    current1.push_front(4);
    current1.pop_front();
    ASSERT_TRUE(current1.empty());
    List<int>::Iterator i = current1.begin();
    ASSERT_EQUAL(i, current1.end());
    ASSERT_EQUAL(current1.begin(), current1.end());
}

TEST(test_iterator_erase_insert){
    List<int> current1;
    current1.push_back(1);
    current1.push_back(2);
    current1.push_back(3);
    List<int>::Iterator i = current1.end(); //inserting and erasing into end
    ASSERT_EQUAL(List<int>::Iterator(), i);
    current1.insert(i, 4);
    ASSERT_EQUAL(current1.back(), 4);
    i = current1.begin();
    ++i;
    ++i;
    ++i;
    current1.erase(i);
    ASSERT_EQUAL(current1.back(), 3);
    i = current1.begin(); //inserting and erasing into front
    current1.insert(i, 9); //here
    ASSERT_EQUAL(current1.front(), 9); 
    current1.erase(i);
    ASSERT_EQUAL(current1.front(), 9); 

    List<int> current2; //when there's only 1 element
    current2.push_back(5);
    i = current2.begin();
    ASSERT_EQUAL(5, *i);
    current2.erase(i); 
    ASSERT_TRUE(current2.empty());
    i = current2.begin();
    current2.insert(i,4);
    ASSERT_TRUE(current2.front() == 4);
    ASSERT_TRUE(current2.back() == 4);
    current2.insert(i,3);
    ASSERT_TRUE(current2.back() == 3);

    List<int> current3;
    current3.push_back(1);
    current3.push_back(2);
    current3.push_back(3);
    current3.push_back(4);
    i = current3.begin();
    ++i;
    ++i;
    --i;
    ASSERT_EQUAL(2, *i);
}

TEST(test_for_loop){
    List<int> lf;
    for(int i=0; i<10; i++){
        lf.push_back(i);
    }
    List<int>::Iterator j = lf.begin();
    ++j;
    ++j;
    lf.erase(j);
    for(int i=0; i<9; i++){
        List<int>::Iterator j = lf.begin();
        lf.erase(j);
    }
    ASSERT_TRUE(lf.empty());

    List<int> lf2;
    for(int i=0; i<10; i++){
        List<int>::Iterator j = lf2.end();
        lf2.insert(j,i); // here
    }
    int counter = 0;
    for(List<int>::Iterator i = lf2.begin(); i!=lf2.end(); ++i){
        ASSERT_EQUAL(*i, counter);
        counter ++;
    }
    for(int i=0; i<10; i++){
        List<int>::Iterator j = lf2.begin();
        lf2.erase(j);
    }
    ASSERT_TRUE(lf2.empty());
}

TEST(insert_erase_all) {
    List<int> current7;
    List<int>::Iterator i = current7.begin();
    current7.insert(i, 7);
    ASSERT_TRUE(current7.front() == 7); 
    i = current7.begin();
    current7.insert(i, 3); //here
    ASSERT_TRUE(current7.front() == 3);
    ++i;
    ASSERT_TRUE(i == current7.end());
    ASSERT_FALSE(i != current7.end());
    current7.insert(i, 4);
    current7.insert(i, 14); //here
    ASSERT_TRUE(i == current7.end()); 
    i = current7.begin();
    ASSERT_TRUE(*i == 3);
    ++i;
    ASSERT_TRUE(*i == 7);
    ++i;
    ASSERT_TRUE(*i == 4);
    ++i;
    ASSERT_TRUE(*i == 14);
    ++i;
    i = current7.end();
    current7.insert(i, 8); 
    i = current7.begin();
    current7.insert(i, 34); 
    ++i;
    ASSERT_TRUE(current7.front() == 34);
    ASSERT_TRUE(current7.back() == 8);
    i = current7.begin();
    ++i;
    ++i;
    current7.insert(i, 5);
    --i;
    ASSERT_TRUE(*i == 5);
    current7.erase(i);
    ASSERT_TRUE(current7.front() == 34); 
    i = current7.begin();
    ++i;
    current7.erase(i);
    ASSERT_TRUE(current7.front() == 34);
    current7.erase(current7.begin());
    ASSERT_TRUE(current7.front() == 7);
    i = current7.begin();
    ++i;
    ++i;
    ++i;
    current7.erase(i);
    ASSERT_TRUE(current7.back() == 14); 
    i = current7.begin();
    ++i;
    current7.erase(i);
    i = current7.begin();
    ASSERT_TRUE(current7.front() == 7);
    ASSERT_TRUE(current7.back() == 14);
    ++i;
    current7.erase(i);
    i = current7.begin();
    current7.erase(i);
    ASSERT_TRUE(current7.empty());
    i = current7.begin();
    current7.erase(i);
}
TEST_MAIN()
