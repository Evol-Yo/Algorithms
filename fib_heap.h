#pragma warning(disable:4996) //for std::copy

#ifndef _FIB_HEAP_H
#define _FIB_HEAP_H

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<climits>
using namespace std;


typedef struct FibonacciHeapNode
{
    int key;       //结点
    int degree;    //度
    FibonacciHeapNode * left;  //左兄弟
    FibonacciHeapNode * right; //右兄弟
    FibonacciHeapNode * parent; //父结点
    FibonacciHeapNode * child;  //第一个孩子结点
    bool marked;           //是否被删除第1个孩子
}FibNode;

//斐波那契堆ADT
typedef struct FibonacciHeap 
{
    int keyNum;   //堆中结点个数
    FibonacciHeapNode * min;//最小堆，根结点
    int maxNumOfDegree;   //最大度
    FibonacciHeapNode **cons;//指向最大度的内存区域
}FibHeap;

//将x从双链表移除
inline void FibNodeRemove(FibNode * x);

//将x堆结点加入y结点之前(循环链表中)
void FibNodeAdd(FibNode * x, FibNode * y);

//初始化一个空的Fibonacci Heap
FibHeap * FibHeapMake();

//初始化结点x
FibNode * FibHeapNodeMake();

//堆结点x插入fibonacci heap中
void FibHeapInsert(FibHeap * heap, FibNode * x);

//将数组内的值插入Fibonacci Heap
void FibHeapInsertKeys(FibHeap * heap, int keys[], int keyNum);

//将值插入Fibonacci Heap
void FibHeapInsertKey(FibHeap * heap, int key);

//抽取最小结点
FibNode * FibHeapExtractMin(FibHeap * heap);

//合并左右相同度数的二项树
void FibHeapConsolidate(FibHeap * heap);

//将x根结点链接到y根结点
void FibHeapLink(FibHeap * heap, FibNode * x, FibNode *y);

//减小一个关键字
void FibHeapDecrease(FibHeap * heap, FibNode * x, int key);

//修改度数
void renewDegree(FibNode * parent, int degree);

//删除结点
void FibHeapDelete(FibHeap * heap, FibNode * x);

//堆内搜索关键字
FibNode * FibHeapSearch(FibHeap * heap, int key);

//被FibHeapSearch调用
FibNode * FibNodeSearch(FibNode * x, int key);

//销毁堆
void FibHeapDestory(FibHeap * heap);

//被FibHeapDestory调用
void FibNodeDestory(FibNode * x);

//输出打印堆
void FibHeapPrint(FibHeap * heap);

//被FibHeapPrint调用
void FibNodePrint(FibNode * x);

#endif //end _FIB_HEAP_H