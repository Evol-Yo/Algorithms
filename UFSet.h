#ifndef _UFSET_H
#define _UFSET_H

#include <iostream>
#include <iomanip>
#include <assert.h>

class UFSets
{
public:
    typedef int value_type;
    typedef int size_type;

    UFSets(size_type s) :size(s)
    {
        parent = new value_type[size + 1];
        for (size_type i = 0; i <= size; ++i)
            parent[i] = -1;
    }
    value_type Find(value_type x)const
    {
        assert(x < size);
        return (parent[x] < 0 ? x : Find(parent[x]));
    }
    void Union(value_type x1, value_type x2)
    {
        assert(x1 < size && x2 < size);
        assert(x1 != x2);
        value_type v1 = Find(x1);
        value_type v2 = Find(x2);
        if (v1 == v2)
            return;
        value_type tmp = parent[v1] + parent[v2];
        //���²�����������˻���
        if (parent[v1] > parent[v2]) //��v1Ϊ�ڵ�����ڵ��һЩ
        {
            parent[v1] = v2;
            parent[v2] = tmp;        //��v2��Ϊ�µĸ�
        }
        else
        {
            parent[v2] = v1;
            parent[v1] = tmp;       //��v1��Ϊ�µĸ�
        }
    }
    void print()const
    {
        size_type i;
        for (i = 0; i < size; ++i)
        {
            std::cout << std::setw(4) << parent[i];
        }
        std::cout << std::endl;
        for (i = 0; i < size; ++i)
        {
            std::cout << std::setw(4) << i;
        }
        std::cout << std::endl;
    }
    ~UFSets()
    {
        delete[]parent;
    }
private:
    value_type *parent;    //��Ÿ�Ԫ�ص�˫�׽ڵ�ָ�루�±꣩
    size_type  size;
};

#endif //end _UFSETS_H