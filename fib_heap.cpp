#include "fib_heap.h"

//���ѵ���С����Ƴ�����ָ�������ֵ�
static FibNode *FibHeapMinRemove(FibHeap * heap)
{
    FibNode *min = heap->min;
    if (heap->min == min->right)
    {
        heap->min = NULL;
    }
    else
    {
        FibNodeRemove(min);
        heap->min = min->right;
    }
    min->left = min->right = min;
    return min;
}

//����FibHeapConsolidate������ϣ���ÿռ�
static void FibHeapConsMake(FibHeap * heap)
{
    int old = heap->maxNumOfDegree;
    heap->maxNumOfDegree = int(log(heap->keyNum * 1.0) / log(2.0)) + 1;
    if (old < heap->maxNumOfDegree)
    {
        //��Ϊ��Ϊheap->maxNumOfDegree���ܱ��ϲ�,����ҪmaxNumOfDegree + 1
        FibNode ** ptr = new FibNode*[sizeof(FibHeap *) * (heap->maxNumOfDegree + 1)];
        std::copy(&heap->cons[0], &heap->cons[old], ptr);
        delete[]heap->cons;
        heap->cons = ptr;
    }
}

//�ж�x�븸�ڵ�y֮������ӣ�ʹx��Ϊһ����
static void FibHeapCut(FibHeap * heap, FibNode * x, FibNode * y)
{
    FibNodeRemove(x);
    renewDegree(y, x->degree);
    if (x == x->right)
    {
        y->child = NULL;
    }
    else
    {
        y->child = x->right;
    }
    x->parent = NULL;
    x->left = x->right = x;
    x->marked = false;
    FibNodeAdd(x, heap->min);
}

//��������
static void FibHeapCascadingCut(FibHeap * heap, FibNode * y)
{
    FibNode * z = y->parent;
    if (NULL != z)
    {
        if (y->marked == false)
        {
            y->marked = true;
        }
        else
        {
            FibHeapCut(heap, y, z);
            FibHeapCascadingCut(heap, z);
        }
    }
}

//��x��˫�����Ƴ������ǲ��ı�x��ָ��
inline void FibNodeRemove(FibNode * x)
{
    x->left->right = x->right;
    x->right->left = x->left;
}


//��x�ѽ�����y���֮ǰ(ѭ��������)
//a ���� y
//a ���� x ���� y
inline void FibNodeAdd(FibNode * x, FibNode * y) 
{
    x->left = y->left;
    y->left->right = x;
    x->right = y;
    y->left = x;
}

//��ʼ��һ���յ�Fibonacci Heap
FibHeap * FibHeapMake()
{
    FibHeap * heap = NULL;
    heap = new FibHeap;
    memset(heap, 0, sizeof(FibHeap));
    return heap;
}

//��ʼ�����x
FibNode * FibHeapNodeMake() 
{
    FibNode * x = NULL;
    x = new FibNode;
    memset(x, 0, sizeof(FibNode));
    x->left = x->right = x;
    return x;
}

//�ѽ��x����fibonacci heap��
void FibHeapInsert(FibHeap * heap, FibNode * x)
{
    if (0 == heap->keyNum)
    {
        heap->min = x;
    }
    else 
    {
        FibNodeAdd(x, heap->min);
        x->parent = NULL;
        if (x->key < heap->min->key)
        {
            heap->min = x;
        }
    }
    heap->keyNum++;
}

//�������ڵ�ֵ����Fibonacci Heap
void FibHeapInsertKeys(FibHeap * heap, int keys[], int keyNum)
{
    for (int i = 0; i < keyNum; i++) 
    {
        FibHeapInsertKey(heap, keys[i]);
    }
}

//��ֵ����Fibonacci Heap
void FibHeapInsertKey(FibHeap * heap, int key) 
{
    FibNode * x = NULL;
    x = FibHeapNodeMake();
    x->key = key;
    FibHeapInsert(heap, x);
}

//��ȡ��С���
FibNode * FibHeapExtractMin(FibHeap * heap)
{
    FibNode *x = NULL, *z = heap->min;
    if (z != NULL) 
    {
        //ɾ��z��ÿһ������
        while (NULL != z->child) 
        {
            x = z->child;
            FibNodeRemove(x);
            if (x->right == x)
            {
                z->child = NULL;
            }
            else 
            {
                z->child = x->right;
            }
            FibNodeAdd(x, z);//add x to the root list heap
            x->parent = NULL;
        }

        FibNodeRemove(z);
        if (z->right == z) 
        {
            heap->min = NULL;
        }
        else
        {
            heap->min = z->right;
            FibHeapConsolidate(heap);
        }
        heap->keyNum--;
    }
    return z;
}

//�ϲ�������ͬ�����Ķ�����
void FibHeapConsolidate(FibHeap * heap)
{
    int D, d;
    FibNode * w = heap->min, *x = NULL, *y = NULL;
    FibHeapConsMake(heap);//���ٹ�ϣ���ÿռ�
    D = heap->maxNumOfDegree + 1;
    for (int i = 0; i < D; i++) 
    {
        *(heap->cons + i) = NULL;
    }
    //�ϲ���ͬ�ȵĸ��ڵ㣬ʹÿ�������Ķ�����Ψһ
    while (NULL != heap->min) 
    {
        x = FibHeapMinRemove(heap);
        d = x->degree;
        while (NULL != *(heap->cons + d))
        {
            y = *(heap->cons + d);
            if (x->key > y->key)
            {//�����key��С
                swap(x, y);
            }
            FibHeapLink(heap, y, x);
            *(heap->cons + d) = NULL;
            d++;
        }
        *(heap->cons + d) = x;
    }
    heap->min = NULL;//ԭ�и������
    //��heap->cons�н�㶼���¼ӵ������У����ҳ���С��
    for (int i = 0; i < D; i++)
    {
        if (*(heap->cons + i) != NULL) 
        {
            if (NULL == heap->min) 
            {
                heap->min = *(heap->cons + i);
            }
            else 
            {
                FibNodeAdd(*(heap->cons + i), heap->min);
                if ((*(heap->cons + i))->key < heap->min->key) 
                {
                    heap->min = *(heap->cons + i);
                }
            }
        }
    }
}

//��x��������ӵ�y�����
void FibHeapLink(FibHeap * heap, FibNode * x, FibNode *y) 
{
    FibNodeRemove(x);
    if (NULL == y->child)
    {
        y->child = x;
    }
    else 
    {
        FibNodeAdd(x, y->child);
    }
    x->parent = y;
    y->degree++;
    x->marked = false;
}

//��Сһ���ؼ���
void FibHeapDecrease(FibHeap * heap, FibNode * x, int key)
{
    FibNode * y = x->parent;
    if (x->key < key) 
    {
        std::cerr << "new key is greater than current key!" << std::endl;
        return;
    }
    x->key = key;

    if (NULL != y && x->key < y->key) 
    {
        //�ƻ�����С�����ʣ���Ҫ���м������в���
        FibHeapCut(heap, x, y);
        FibHeapCascadingCut(heap, y);
    }
    if (x->key < heap->min->key)
    {
        heap->min = x;
    }
}

//�޸Ķ���
void renewDegree(FibNode * parent, int degree)
{
    parent->degree -= degree;
    if (parent->parent != NULL) 
    {
        renewDegree(parent->parent, degree);
    }
}

//ɾ�����
void FibHeapDelete(FibHeap * heap, FibNode * x)
{
    FibHeapDecrease(heap, x, INT_MIN);
    FibHeapExtractMin(heap);
}

//���������ؼ���
FibNode * FibHeapSearch(FibHeap * heap, int key)
{
    return FibNodeSearch(heap->min, key);
}

static FibNode * FibNodeSearch(FibNode * x, int key) 
{
    FibNode *w = x, *y = NULL;
    if (x != NULL)
    {
        do 
        {
            if (w->key == key) 
            {
                y = w;
                break;
            }
            else if (NULL != (y = FibNodeSearch(w->child, key))) 
            {
                break;
            }
            w = w->right;
        } while (w != x);
    }
    return y;
}

//���ٶ�
void FibHeapDestory(FibHeap * heap)
{
    FibNodeDestory(heap->min);
    delete []heap->cons;
    delete heap;
    heap = NULL;
}

//��FibHeapDestory����
static void FibNodeDestory(FibNode * x)
{
    FibNode *p = x, *q = NULL;
    while (p != NULL)
    {
        FibNodeDestory(p->child);
        q = p;
        if (p->left == x) //û���ֵܽڵ�
        {
            p = NULL;
        }
        else 
        {
            p = p->left;
        }
        delete q;
    }
}