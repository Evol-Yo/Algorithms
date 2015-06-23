#include <iostream>
#include "algo.h"
using namespace std;

template<class T>
void print(const T *arr, int size)
{
    int i = 0;
    while (i < size)
    {
        cout << arr[i++] << "  ";
    }
    cout << endl;
}



void test7()
{
    string s1("ABCBDAB");
    string s2("BDCABA");
    string s3;
    s3 = LCSLength(s1, s2);
}

void test8()
{
    //初始化列表构造方法(C++11)
    vector<ActiveInfo> v({ { 1, 4 }, { 3, 5 }, { 0, 6 }, { 5, 7 }, { 3, 9 }, { 5, 9 },
    { 6, 10 }, { 8, 11 }, { 8, 12 }, { 2, 14 }, { 12, 16 } }); 
    //RecursiveActivitySelector(v);
    vector<ActiveInfo> res = GreedyActivitySelector(v);
    IntervalGraphColoring1(v);
}

void test9()
{
    //初始化列表构造方法(C++11)
    vector<ActiveInfo> v({ { 4, 70 }, { 2, 60 }, { 4, 50 }, { 3, 40 }, 
    { 1, 30 }, { 4, 20 }, { 6, 10 } });
    //RecursiveActivitySelector(v);
    //int res = GreedyTaskScheduling(v);
    int res = GreedyTaskScheduling1(v, NULL);
}

#include <set>
#include "BTree.h"
#include "g_bTree.h"
#include "g_btree_container.h"

void test_performance()
{
    const int n = 1000000;
    int *p = new int[n];
    for (int i = 0; i < n; i++)
    {
        p[i] = rand() % n;
    }

    std::pair<int, int> *pa = new std::pair<int, int>[n];
    for (int i = 0; i < n; i++)
    {
        pa[i].first = p[i];
        pa[i].second = i;
    }

    g_btree::btree_unique_container<g_btree::btree<g_btree::btree_set_params<int, std::less<int>, std::allocator<int>, 256> > > g_bt;
    g_bt.insert(&p[0], &p[n]);

    std::set<int> s;
    s.insert(&p[0], &p[n]);

    stx::btree<int, int> stx_bt;
    stx_bt.insert(&pa[0], &pa[n]);

    //cout << g_bt.bytes_used() << endl;
    //cout << g_bt.average_bytes_per_value() << endl;
}

int main()
{
    /*int arr[] = { 13, -3, -25, 20, -3, -16, -23, 18, 20,
                  -7, 12, -5, -22, 15, -4, 7 };
    int left = -1;
    int right = -1;
    int sum = 0;
    FindMaxSubArray(arr, 0, 15, left, right, sum);
    cout << "left : " << left << ", right : " << right << ", sum : " << sum << endl;*/
    //test1();
    //test2();
    test9();

    return 0;
}

void test1()
{
    int arr[] = { 5, 2, 4, 6, 1, 3 };
    print(arr, 6);
    //InsertSort(arr, 6);
    //BInsertSort(arr, 6);
    //TwoWayInsertSort(arr, 6);
    //ShellSort(arr, 6);
    //QuickSort(arr, 0, 5);
    MergeSort(arr, 0, 5);
    print(arr, 6);
}

void test2()
{
    int arr[] = { 5, 2, 4, 6, 1, 3 };
    print(arr, 6);
    int i = 4;
    int ret = RandomizedSelect(arr, 0, 5, i);
    cout << "第 " << i << " 小的元素是 " << ret << endl;
}

void test3()
{
    int p[] = { 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
    //int ret = CutRod(p, 3);
    int ret = BottomUpCutRod(p, 4);
}

void test4()
{
    string s("bacecard");
    string sub = longestPalindrome3(s);
}

void test5()
{
    tagPoint tag[8] = { { 0, 0 }, { 0, 6 }, { 1, 0 }, { 2, 3 }, { 5, 4 }, { 6, 1 }, { 7, 5 }, { 8, 2 } };
    double ret = DP(tag, 7);
}

void test6()
{
    int arr[] = { 1, 4, 6, 7, 10, 14, 20, 22, 35, 37 };

    int ret = BinarySearch(arr, 10, 20);
}