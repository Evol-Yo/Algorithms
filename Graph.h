#ifndef _GRAPH_H
#define _GRAPH_H

#include <iostream>
#include <assert.h>
#include <limits>
#include <queue>    //for queue & priority_queue
using namespace std;

template<class _Dis>
struct Edge
{
    typedef _Dis _DistType;
    typedef Edge<_Dis> _Myt;
    typedef size_t  size_type;

    Edge(size_type v, const _Dis& dis, _Myt *ptr = NULL)
        : _Dest(v), _Cost(dis), _Link(ptr)
    {}
    bool operator!=(const _Myt& _Right)const
    {
        return !(const == _Right.const);
    }
    bool operator<(const _Myt& _Right)const
    {
        return (_Cost < _Right._Cost);
    }
    size_type  _Dest;
    _DistType  _Cost;
    _Myt      *_Link;
};

template<class _Ty, class _Dis>
struct Vertex
{
    typedef _Ty  _VertexType;
    typedef _Dis _DistType;
    typedef Vertex<_Ty, _Dis> _Myt;
    typedef Edge<_Dis>  _EdgeType;

    Vertex(const _Ty& v = _Ty()) :_Value(v), _Edgeptr(NULL)
    {}

    _VertexType _Value;
    _EdgeType  *_Edgeptr;
};

template<class _Ty, class _Dis>
class Graph;

template<class _Ty, class _Dis>
struct MSTEdgeNode
{
    typedef MSTEdgeNode<_Ty, _Dis> _Myt;
    typedef typename Graph<_Ty, _Dis>::size_type size_type;
    typedef _Dis _DistType;

    bool operator>(const _Myt& _Right)const
    {
        return (_Cost > _Right._Cost);
    }
    size_type _Head;
    size_type _Tail;
    _DistType _Cost;
};

//最小生成树
template<class _Ty, class _Dis = int>
class MinSpanTree
{
public:
    typedef MSTEdgeNode<_Ty, _Dis> _EdgeType;
    typedef typename _EdgeType::size_type size_type;

    MinSpanTree(size_type sz) :_Size(sz)
    {
        _Edgeptr = new _EdgeType[sz];
    }
    _EdgeType& operator[](size_type pos)
    {
        return _Edgeptr[pos];
    }
    void print()const
    {
        for (size_type i = 0; i < _Size; ++i)
        {
            cout << _Edgeptr[i]._Head << "<-->" << _Edgeptr[i]._Tail << endl;
        }
    }
    ~MinSpanTree()
    {
        delete[]_Edgeptr;
        _Edgeptr = NULL;
        _Size = 0;
    }
private:
    _EdgeType *_Edgeptr;
    size_type _Size;
};

//只适用于连通图， 采用邻接表
template<class _Ty, class _Dis = int>
class Graph
{
public:
    typedef Vertex<_Ty, _Dis> _VertexType;
    typedef typename Vertex<_Ty, _Dis>::_EdgeType  _EdgeType;
    typedef _Dis _DistType;
    typedef int  size_type;

    Graph(size_type size = _DefaultSize)
    {
        _MaxNumVertices = size > _DefaultSize ? size : _DefaultSize;
        _NumVertices = 0;
        _NumEdges = 0;
        _VertexTable = new _VertexType[_MaxNumVertices];

        for (size_type i = 0; i < _MaxNumVertices; ++i)
            _VertexTable[i]._Edgeptr = NULL;
    }

    size_type NumberOfVertices()const
    {
        return _NumVertices;
    }

    size_type NumberOfEdges()const
    {
        return _NumEdges;
    }

    int GetWeight(const _Ty& lhs, const _Ty& rhs)const
    {
        int pos1, pos2;
        if ((pos1 = GetVertexPos(lhs)) < 0 ||
            (pos2 = GetVertexPos(rhs)) < 0)
            return numeric_limits<_Dis>::max();
        _EdgeType *pedge = find_edge(pos1, pos2);
        return (pedge == NULL ?
            numeric_limits<_Dis>::max() : pedge->_Cost);
    }

    _Ty GetFirstNeighbor(const _Ty& v)const
    {
        int pos = GetVertexPos(v);
        if (pos < 0)
            return -1;
        _EdgeType *pedge = _VertexTable[pos]._Edgeptr;
        return (pedge == NULL ? -1 : _GetValueOfVertex(pedge->_Cost));
    }

    _Ty GetNextNeighbor(const _Ty& v, int diff)const
    {
        int pos = GetVertexPos(v);
        if (pos < 0)
            return -1;
        _EdgeType *pedge = _VertexTable[pos]._Edgeptr;
        if (pedge == NULL)
            return -1;
        for (int i = diff - 1; i >= 0; --i)
        {
            pedge = pedge->_Link;
            if (pedge == NULL)
                break;
        }
        return (pedge == NULL ? -1 : _GetValueOfVertex(pedge->_Dest));
    }

    bool insert_vertex(const _Ty& v)
    {
        assert(_NumVertices <= _MaxNumVertices);
        if (GetVertexPos(v) < 0)    //如果没有重复的顶点
        {
            _VertexTable[_NumVertices++]._Value = v;
            return true;
        }
        return false;
    }

    bool have_edge(const _Ty& lhs, const _Ty& rhs)
    {
        int pos1, pos2;
        if ((pos1 = GetVertexPos(lhs)) < 0)
            return false;
        if ((pos2 = GetVertexPos(rhs)) < 0)
            return false;
        return _have_edge(pos1, pos2);
    }

    bool insert_edge(const _Ty& lhs, const _Ty& rhs, const _Dis& cost)
    {
        assert(_NumVertices <= _MaxNumVertices - 1);
        assert(lhs != rhs);
        int pos1, pos2;
        if ((pos1 = GetVertexPos(lhs)) < 0)
            return false;
        if ((pos2 = GetVertexPos(rhs)) < 0)
            return false;
        _EdgeType *pedge = new _EdgeType(pos2, cost);
        //I think it need push_back instead of push_front, first in first visit
        if (_push_back_edge(pos1, pedge) == true)
            _push_back_edge(pos2, new _EdgeType(pos1, cost));
        else
            delete pedge;
        _NumEdges++;
        return true;
    }

    void remove_edge(const _Ty& lhs, const _Ty& rhs)
    {
        int pos1, pos2;
        if ((pos1 = GetVertexPos(lhs)) < 0)
            return;
        if ((pos2 = GetVertexPos(rhs)) < 0)
            return;
        if (_remove_edge(pos1, pos2) == true)
            _remove_edge(pos2, pos1);
        _NumEdges--;
    }

    void remove_vertex(const _Ty& v)
    {
        int pos = GetVertexPos(v);
        if (pos < 0)
            return;
        _EdgeType *pedge = _VertexTable[pos]._Edgeptr;
        while (pedge != NULL)
        {
            _remove_edge(pedge->_Dest, pos);
            pedge = pedge->_Link;
            --_NumEdges;
        }
        _delete_edge_list(pos); //释放pos顶点所指的所有的边节点

        //以下用最后一个顶点替换当前节点
        _VertexTable[pos]._Edgeptr = _VertexTable[_NumVertices - 1]._Edgeptr;
        _VertexTable[_NumVertices - 1]._Edgeptr = NULL;
        _VertexTable[pos]._Value = _VertexTable[_NumVertices - 1]._Value;
        --_NumVertices;
        pedge = _VertexTable[pos]._Edgeptr;

        _EdgeType *p;
        while (pedge != NULL)   //修改下标
        {
            p = find_edge(pedge->_Dest, _NumVertices);
            p->_Dest = pos;
            pedge = pedge->_Link;
        }
    }//end remove_vertex

    void print()const
    {
        for (size_type i = 0; i < _NumVertices; ++i)
        {
            cout << _VertexTable[i]._Value << ":> ";
            _EdgeType *pedge = _VertexTable[i]._Edgeptr;
            while (pedge != NULL)
            {
                cout << _GetValueOfVertex(pedge->_Dest) << " ";
                pedge = pedge->_Link;
            }
            cout << endl;
        }
    }
    ~Graph()
    {
        for (size_type i = 0; i < _NumVertices; ++i)
        {
            _delete_edge_list(i);
        }
        delete[]_VertexTable;
        _VertexTable = NULL;
        _MaxNumVertices = 0;
        _NumEdges = 0;
    }
public:
    //深度优先搜索
    void DFS()const
    {
        if (_NumVertices == 0)
            return;
        size_type *visited = new size_type[_NumVertices];
        for (size_type i = 0; i < _NumVertices; ++i)
            visited[i] = 0;
        _DFS(0, visited);
        cout << endl;
        delete[]visited;
    }

    //广度优先搜索
    void BFS()const
    {
        if (_NumVertices == 0)
            return;
        size_type *visited = new size_type[_NumVertices];   //记录顶点是否被访问过
        for (size_type i = 0; i < _NumVertices; ++i)        //初始化为0
            visited[i] = 0;

        queue<size_type> q;
        q.push(0);
        while (!q.empty())                                  //还有未访问节点
        {
            size_type pos = q.front();
            q.pop();
            if (visited[pos])
                continue;
            cout << _GetValueOfVertex(pos) << " ";          //访问当前节点
            visited[pos] = 1;                               //标记为已访问
            _EdgeType *pedge = _VertexTable[pos]._Edgeptr;
            while (pedge != NULL)                           //将与当前节点关联的边入队
            {
                if (!visited[pedge->_Dest])
                    q.push(pedge->_Dest);
                pedge = pedge->_Link;
            }
        }
        cout << endl;
        delete[]visited;
    }

    //最小生成树Kruskal算法
    void Kruskal(MinSpanTree<_Ty, _Dis> &T)const;
    //最小生成树prim算法
    void Prim(MinSpanTree<_Ty, _Dis> &T)const;

private:
    _EdgeType *find_edge(size_type lhs, size_type rhs)const
    {
        assert(lhs >= 0 && rhs < _NumVertices);
        _EdgeType *pedge = _VertexTable[lhs]._Edgeptr;
        while (pedge != NULL && pedge->_Dest != rhs)
        {
            pedge = pedge->_Link;
        }
        return pedge;
    }

    bool _have_edge(size_type lhs, size_type rhs)const
    {
        assert(lhs >= 0 && lhs < _NumVertices);
        assert(rhs >= 0 && rhs < _NumVertices);
        _EdgeType *p = _VertexTable[lhs]._Edgeptr;
        while (p != NULL && p->_Dest != rhs)
        {
            p = p->_Link;
        }
        return (p == NULL ? false : true);
    }

    bool _push_back_edge(size_type pos, _EdgeType *ptr)
    {
        assert(pos >= 0 && pos < _NumVertices);
        _EdgeType *pedge;
        if ((pedge = _VertexTable[pos]._Edgeptr) == NULL)
        {
            _VertexTable[pos]._Edgeptr = ptr;
            return true;
        }
        else
        {
            while (pedge->_Link != NULL && pedge->_Dest != ptr->_Dest)
                pedge = pedge->_Link;
            if (pedge->_Dest == ptr->_Dest)
                return false;
            pedge->_Link = ptr;
            return true;
        }
    }// _push_back_edge

    bool _remove_edge(size_type lhs, size_type rhs)
    {
        assert(lhs < _NumVertices && rhs < _NumVertices);
        _EdgeType *pedge;
        if ((pedge = _VertexTable[lhs]._Edgeptr) == NULL)
            return false;
        if (pedge->_Dest == rhs)
        {
            _VertexTable[lhs]._Edgeptr = pedge->_Link;
            delete pedge;
        }
        else
        {
            while (pedge->_Link != NULL && pedge->_Link->_Dest != rhs)
            {
                pedge = pedge->_Link;
            }
            if (pedge->_Link == NULL)
                return false;
            _EdgeType *p = pedge->_Link;
            pedge->_Link = p->_Link;
            delete p;
        }
        return true;
    } //end _remove_edge

    void _delete_edge_list(size_type pos)
    {
        assert(pos >= 0 && pos < _NumVertices);
        _EdgeType *pedge = _VertexTable[pos]._Edgeptr;
        _EdgeType *p;
        while (pedge != NULL)
        {
            p = pedge;
            pedge = pedge->_Link;
            delete p;
        }
        _VertexTable[pos]._Edgeptr = NULL;
    }

    int GetVertexPos(const _Ty& v)const
    {
        for (size_type i = 0; i < _NumVertices; ++i)
        {
            if (_VertexTable[i]._Value == v)
            {
                return i;
            }
        }
        return -1;
    }

    int _GetFirstNeighbor(size_type pos)const
    {
        assert(pos < _NumVertices);
        _EdgeType *pedge = _VertexTable[pos]._Edgeptr;
        return (pedge == NULL ? -1 : pedge->_Dest);
    }
    //pos顶点所指向边cur的下一条边
    int _GetNextNeighbor(size_type pos, size_type cur)const
    {
        assert(pos < _NumVertices && cur < _NumVertices);
        _EdgeType *pedge;
        if ((pedge = _VertexTable[pos]._Edgeptr) == NULL)
            return -1;
        while (pedge->_Link != NULL && pedge->_Dest != cur)
        {
            pedge = pedge->_Link;
        }
        pedge = pedge->_Link;
        return (pedge == NULL ? -1 : pedge->_Dest);
    }

    _Ty _GetValueOfVertex(size_type pos)const
    {
        assert(pos < _NumVertices);
        return _VertexTable[pos]._Value;
    }
private:
    void _DFS(size_type pos, size_type *visited)const
    {
        cout << _GetValueOfVertex(pos) << " ";
        visited[pos] = 1;
        int w = _GetFirstNeighbor(pos);
        while (w != -1)
        {
            if (!visited[w])
                _DFS(w, visited);
            w = _GetNextNeighbor(pos, w);
        }
    }
private:
    enum{ _DefaultSize = 10 };
    size_type _MaxNumVertices;
    size_type _NumVertices;
    size_type _NumEdges;
    _VertexType *_VertexTable;
};

template<class _Ty = void>
struct Greater : public binary_function < _Ty, _Ty, bool >
{
    bool operator()(const _Ty& _Left, const _Ty& _Right) const
    {
        return (_Left > _Right);
    }
};

template<class _Ty, class _Dis>
void Graph<_Ty, _Dis>::Kruskal(MinSpanTree<_Ty, _Dis> &T)const
{
    typedef MSTEdgeNode<_Ty, _Dis> _MSTEdgeType;
    _MSTEdgeType e;
    priority_queue < _MSTEdgeType, vector<_MSTEdgeType>, Greater<_MSTEdgeType> >  minHeap;
    int numVertices = NumberOfVertices();
    _EdgeType *pedge;
    size_type u, v;
    //将所有边插入到MinHeap中
    for (u = 0; u < numVertices; ++u)
    {
        for (v = u + 1; v < numVertices; ++v)
        {
            if ((pedge = find_edge(u, v)) != NULL)
            {
                e._Head = u;
                e._Tail = v;
                e._Cost = pedge->_Cost;
                minHeap.push(e);
            }
        }
    }
    size_type count = 0;
    UFSets _F(numVertices);
    //依次从MinHeap中将权值最小的边放入MinSpanTree中
    while (count < numVertices - 1)
    {
        e = minHeap.top();
        minHeap.pop();
        u = _F.Find(e._Tail);
        v = _F.Find(e._Head);
        if (u != v) //u != v则没有产生回路
        {
            _F.Union(u, v);
            T[count] = e;
            count++;
        }
    }
} //end Kruskal

//Prim算法求最小生成树，适用于连通图
template<class _Ty, class _Dis>
void Graph<_Ty, _Dis>::Prim(MinSpanTree<_Ty, _Dis> &T)const
{
    size_type numVertices = NumberOfVertices();
    _Dis      *lowcost = new _Dis[numVertices];
    size_type *nearvex = new size_type[numVertices];

    size_type i, j, k;
    _EdgeType *pedge;
    lowcost[0] = 0;
    for (i = 1; i < numVertices; ++i)
    {
        pedge = find_edge(0, i);
        lowcost[i] = (pedge == NULL ?
            numeric_limits<_Dis>::max() : pedge->_Cost);
        nearvex[i] = 0;
    }
    nearvex[0] = -1;
    size_type count = 0;
    for (i = 1; i < numVertices; ++i)
    {
        int min = numeric_limits<_Dis>::max(); //最大权值（无关联）
        int v = 0;
        for (j = 1; j < numVertices; ++j)
        {
            if (nearvex[j] != -1 && lowcost[j] < min)
            {
                v = j;
                min = lowcost[j];
            }
        }
        if (v)  //v == 0表示再也找不到要求的顶点了
        {
            T[count]._Tail = nearvex[v];
            T[count]._Head = v;
            T[count]._Cost = lowcost[v];
            count++;
            nearvex[v] = -1;
            for (j = 0; j < numVertices; ++j)
            {
                if (nearvex[j] == -1)
                    continue;
                for (k = 1; k < numVertices; ++k)
                {
                    if (nearvex[k] != -1)
                        continue;
                    pedge = find_edge(k, j);
                    if (pedge != NULL && pedge->_Cost < lowcost[j])
                    {
                        lowcost[j] = pedge->_Cost;
                        nearvex[j] = k;
                    }
                }
            }
        }
    }
    delete[]lowcost;
    delete[]nearvex;
}//end Prim

#endif // end _GRAPH_H