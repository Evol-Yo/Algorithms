#include <iostream>
#include "algo.h"
#include "fib_heap.h"
#include "UFSet.h"
#include "Graph.h"
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

void test_fib_heap()
{
    int keys[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    FibHeap * heap = NULL;
    FibNode * x = NULL;
    heap = FibHeapMake();
    FibHeapInsertKeys(heap, keys, 10);

    x = FibHeapExtractMin(heap);
    x = FibHeapSearch(heap, 7);
    if (NULL != x)
    {
        cout << x->key << endl;
        FibHeapDecrease(heap, x, 0);
    }
    x = FibHeapSearch(heap, 8);
    if (NULL != x)
    {
        cout << x->key << endl;
        FibHeapDelete(heap, x);
    }
    FibHeapDestory(heap);
}

void test_UFSET()
{
    UFSets u(10);
    //(1 3 6) (4 5) (2 7 8)
    u.Union(1, 3);
    u.Union(1, 6);
    u.Union(4, 5);
    u.Union(2, 7);
    u.Union(7, 8);
    cout << u.Find(1)<<endl;
    u.print();
}

void test_count_sort()
{
    int arr[8] = { 8, 7, 6, 5, 4, 3, 0, 0 };
    int res[8];
    CountSort(arr, 8, res, 8);
    print(res, 8);
}

#include "vEBTree.h"
void test_vEB()
{
    vEB vtree;
    vtree.build(10000);
    vtree.insert(1);
    vtree.insert(10);
    vtree.insert(25);
    vtree.insert(9999);
    cout << vtree.succ(9) << endl;
    vtree.del(10);
    cout << vtree.succ(9) << endl;
    cout << vtree.succ(5555) << endl;
    cout << vtree.exist(9999) << endl;
}

void test_Graph()
{
    Graph<char> gh;
    gh.insert_vertex('0');
    gh.insert_vertex('1');
    gh.insert_vertex('2');
    gh.insert_vertex('3');
    gh.insert_vertex('4');
    gh.insert_vertex('5');
    gh.insert_vertex('6');

    gh.insert_edge('0', '1', 28);
    gh.insert_edge('1', '2', 16);
    gh.insert_edge('2', '3', 12);
    gh.insert_edge('3', '4', 22);
    gh.insert_edge('4', '5', 25);
    gh.insert_edge('5', '0', 10);
    gh.insert_edge('4', '6', 24);
    gh.insert_edge('6', '3', 18);
    gh.insert_edge('1', '6', 14);

    gh.print();
    MinSpanTree<char> tree(gh.NumberOfVertices() - 1);
    gh.Kruskal(tree);
    tree.print();
    cout << "-------------------------------" << endl;
    gh.Prim(tree);
    tree.print();
}

int main()
{
    //test1();
    //test2();
    //test9();
    //test_fib_heap();
    //test_count_sort();
    //test_vEB();
    //test_UFSET();
    test_Graph();

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