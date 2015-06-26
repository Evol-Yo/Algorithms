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
    int key;       //���
    int degree;    //��
    FibonacciHeapNode * left;  //���ֵ�
    FibonacciHeapNode * right; //���ֵ�
    FibonacciHeapNode * parent; //�����
    FibonacciHeapNode * child;  //��һ�����ӽ��
    bool marked;           //�Ƿ�ɾ����1������
}FibNode;

//쳲�������ADT
typedef struct FibonacciHeap 
{
    int keyNum;   //���н�����
    FibonacciHeapNode * min;//��С�ѣ������
    int maxNumOfDegree;   //����
    FibonacciHeapNode **cons;//ָ�����ȵ��ڴ�����
}FibHeap;

//��x��˫�����Ƴ�
inline void FibNodeRemove(FibNode * x);

//��x�ѽ�����y���֮ǰ(ѭ��������)
void FibNodeAdd(FibNode * x, FibNode * y);

//��ʼ��һ���յ�Fibonacci Heap
FibHeap * FibHeapMake();

//��ʼ�����x
FibNode * FibHeapNodeMake();

//�ѽ��x����fibonacci heap��
void FibHeapInsert(FibHeap * heap, FibNode * x);

//�������ڵ�ֵ����Fibonacci Heap
void FibHeapInsertKeys(FibHeap * heap, int keys[], int keyNum);

//��ֵ����Fibonacci Heap
void FibHeapInsertKey(FibHeap * heap, int key);

//��ȡ��С���
FibNode * FibHeapExtractMin(FibHeap * heap);

//�ϲ�������ͬ�����Ķ�����
void FibHeapConsolidate(FibHeap * heap);

//��x��������ӵ�y�����
void FibHeapLink(FibHeap * heap, FibNode * x, FibNode *y);

//��Сһ���ؼ���
void FibHeapDecrease(FibHeap * heap, FibNode * x, int key);

//�޸Ķ���
void renewDegree(FibNode * parent, int degree);

//ɾ�����
void FibHeapDelete(FibHeap * heap, FibNode * x);

//���������ؼ���
FibNode * FibHeapSearch(FibHeap * heap, int key);

//��FibHeapSearch����
FibNode * FibNodeSearch(FibNode * x, int key);

//���ٶ�
void FibHeapDestory(FibHeap * heap);

//��FibHeapDestory����
void FibNodeDestory(FibNode * x);

//�����ӡ��
void FibHeapPrint(FibHeap * heap);

//��FibHeapPrint����
void FibNodePrint(FibNode * x);

#endif //end _FIB_HEAP_H