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
        //以下操作避免产生退化树
        if (parent[v1] > parent[v2]) //以v1为节点的数节点多一些
        {
            parent[v1] = v2;
            parent[v2] = tmp;        //让v2称为新的根
        }
        else
        {
            parent[v2] = v1;
            parent[v1] = tmp;       //让v1成为新的根
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
    value_type *parent;    //存放各元素的双亲节点指针（下标）
    size_type  size;
};

#endif //end _UFSETS_H