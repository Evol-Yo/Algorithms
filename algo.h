#ifndef _ALGO_H
#define _ALGO_H

#include <stdlib.h>
#include <assert.h>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

////////////////////////////////////////////////////////
//��������
///////////////////////////////////////////////////////

//ѡȡ��ŦԪ(������汾)
template<class T>
T _SelectPivot(T *arr, int p, int q)
{
    int i = (rand() % (p - q + 1)) + p;
    if (i != q)
    {
        std::swap(arr[i], arr[q]);
    }
    return arr[q];
}

//�Ľ���˫��ɨ��
template<class T>
int Partition(T *arr, int p, int q)
{
    T x = _SelectPivot(arr, p, q);
    int i = p, j = q;
    while (i < j)
    {
        while (i < j && arr[i] < x)
            ++i;
        arr[j] = arr[i];
        while (j > i && arr[j] > x)
            --j;
        arr[i] = arr[j];
    }
    arr[i] = x;
    return i;
}

//β�ݹ��Ż�
template<class T>
void QuickSort(T *arr, int p, int r)
{
    assert(arr != NULL);
    while (p < r)
    {
        int q = Partition(arr, p, r);
        QuickSort(arr, p, q - 1);
        p = q + 1;
    }
}

//////////////////////////////////////////////////////////
// �ϲ�����
//////////////////////////////////////////////////////////

template<class T>
void Merge(T *first1, T *last1, T *first2, T *last2, T *dst)
{//first��last��dst ��Ϊ��
    while ((first1 != last1) && (first2 != last2))
    {
        if (*first1 < *first2)
            *dst++ = *first1++;
        else
            *dst++ = *first2++;
    }
    while (first1 != last1)
        *dst++ = *first1++;
    while (first2 != last2)
        *dst++ = *first2++;
}

template<class T>
T *Copy(T *first, T *last, T *dst)
{
    T *tmp = dst;
    if (first == last)
        return dst;
    while (first != last)
        *tmp++ = *first++;
    return dst;
}

template<class T>
void MergeSort(T *arr, int p, int r)
{
    if (p >= r)
        return;
    int mid = (r + p) / 2;
    MergeSort(arr, p, mid);
    MergeSort(arr, mid + 1, r);
    T *ptr = new T[r - p + 1];
    Merge(&arr[p], &arr[mid + 1], &arr[mid + 1], &arr[r + 1], ptr);
    Copy(&ptr[0], &ptr[r - p + 1], &arr[p]);
    delete[]ptr;
}

///////////////////////////////////////////////////
//���������
//////////////////////////////////////////////////

//Ѱ�ҿ�Խ�е�(mid)�����������ı߽�
template<class T>
void FindCrossingSubArray(T *arr, int low, int mid, int high,
    int &maxLeft, int &maxRight, int &sum)
{
    int leftSum = (int)1 << (sizeof(int) * 8 - 1);
    int rightSum = (int)1 << (sizeof(int) * 8 - 1);
    int tmp = 0;
    maxRight = maxLeft = -1;
    int i;
    for (i = mid; i >= low; i--)
    {
        tmp = tmp + arr[i];
        if (tmp > leftSum)
        {
            leftSum = tmp;
            maxLeft = i;
        }
    }
    tmp = 0;
    for (i = mid + 1; i <= high; i++)
    {
        tmp = tmp + arr[i];
        if (tmp > rightSum)
        {
            rightSum = tmp;
            maxRight = i;
        }
    }
    sum = leftSum + rightSum;
}

//Ѱ������arr�е����������
//
//@arr - Ŀ������
//@low - Ŀ���������ʼ�±�
//@high - Ŀ������Ľ����±�
//@left - (�������)������������ʼ�±�
//@right - (�������)���������Ľ����±�
//@sum - (�������)���������ĺ�
template<class T>
void FindMaxSubArray(T *arr, int low, int high, int &left, int &right, int &sum)
{
    int mid;
    int leftLow, leftHigh, leftSum;
    int rightLow, rightHigh, rightSum;
    int crossLow, crossHigh, crossSum;

    left = right = -1;
    leftSum = rightSum = (int)1 << (sizeof(int)*8-1);
    if (low == high)
    {
        left = low;
        right = high;
        sum = arr[low];
    }
    else if (low < high)
    {
        mid = (low + high) / 2;
        FindMaxSubArray(arr, low, mid, leftLow, leftHigh, leftSum);
        FindMaxSubArray(arr, mid + 1, high, rightLow, rightHigh, rightSum);
        FindCrossingSubArray(arr, low, mid, high, crossLow, crossHigh, crossSum);
        if (leftSum >= rightSum && leftSum >= crossSum)
        {
            left = leftLow;
            right = leftHigh;
            sum = leftSum;
        }
        else if (rightSum >= leftSum && rightSum >= crossSum)
        {
            left = rightLow;
            right = rightHigh;
            sum = rightSum;
        }
        else
        {
            left = crossLow;
            right = crossHigh;
            sum = crossSum;
        }
    }
}


//��������Arr�е�iС��Ԫ��
//
//@arr - Ŀ������
//@p - ������ʼ�±�
//@r - �����β�±�
//@i - ��iСԪ��
template<class T>
T &RandomizedSelect(T *arr, int p, int r, int i)
{
    if (p == r)
        return arr[p];
    int q = Partition(arr, p, r);
    int k = q - p + 1;
    if (k == i)
        return arr[q];
    else if (k > i)
        return RandomizedSelect(arr, p, q - 1, i);
    return RandomizedSelect(arr, q + 1, r, i - k);
}

//////////////////////////////////////////////////////////////////
// ��̬�滮
///////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
//�����и�

//�Զ�����
int CutRod(int p[], int n)
{
    int q;
    if (n == 0)
        return 0;
    q = (int)1 << (sizeof(int) * 8-1);
    for (int i = 0; i < n; i++)
        q = std::max(q, p[i] + CutRod(p, n - i - 1));
    return q;
}

//�Ե����ϣ����뱸�����ƣ�
int BottomUpCutRod(int p[], int n)
{
    int *r = new int[n + 1];
    int q = (int)1 << (sizeof(int) * 8 - 1);
    r[0] = 0;
    for (int i = 0; i < n; i++)
    {
        int j;
        for (j = 0; j <= i; j++)
            q = std::max(q, r[i - j] + p[j]);
        r[j] = q;
    }
    int ret = r[n];
    delete[]r;
    return ret;
}

//////////////////////////////////////////////////////////
//������ַ���
///////////////////////////////////////////////////////
template<class T>
void print(T** arr, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cout << arr[i][j] << " ";
        cout << endl;
    }
}

/////////////////////////////////////////////////
// ��̬�滮������
//   �����ӽṹΪ��һ������Ϊn���ַ����г���Ϊm�Ļ����Ӵ���
//                ��һ���г���Ϊm-1�Ļ����Ӵ�

//���溯�����ñ������ƣ�ʱ�临�Ӷ�ΪO(n^2)���ռ临�Ӷ�ΪO(n^2)
string longestPalindrome1(string s)
{
    const int len = s.size();
    if (len <= 1)
        return s;
    bool **dp = new bool*[len];
    for (int i = 0; i < len; i++)
    {
        dp[i] = new bool[len];
        memset(dp[i], 0, sizeof(bool)*len);
    }
    int resLeft = 0, resRight = 0;
    dp[0][0] = true;
    for (int i = 1; i < len; i++)
    {
        dp[i][i] = true;
        dp[i][i - 1] = true;
    }
    for (int k = 2; k < len; k++)
        for (int i = 0; i <= len - k; i++)
            if (s[i] == s[i+k-1] && dp[i+1][i+k-2])
            {
                dp[i][i + k - 1] = true;
                if (resRight - resLeft + 1 < k)
                {
                    resLeft = i;
                    resRight = i + k - 1;
                }
            }
    for (int i = 0; i < len; i++)
        delete[]dp[i];
    return s.substr(resLeft, resRight - resLeft + 1);
}

string longestPalindrome2(string s)
{
    const int len = s.size();
    if (len <= 1)
        return s;
    int start, maxLen = 0;
    for (int i = 1; i < len; i++)
    {
        //Ѱ����i-1,iΪ�е�ż�����ȵĻ���
        int low = i - 1, high = i;
        while (low >= 0 && high < len && s[low] == s[high])
        {
            low--;
            high++;
        }
        if (high - low - 1 > maxLen)
        {
            maxLen = high - low - 1;
            start = low + 1;
        }
        //Ѱ����iΪ���ĵ��������ȵĻ���
        low = i - 1; high = i + 1;
        while (low >= 0 && high < len && s[low] == s[high])
        {
            low--;
            high++;
        }
        if (high - low - 1 > maxLen)
        {
            maxLen = high - low - 1;
            start = low + 1;
        }
    }
    return s.substr(start, maxLen);
}

string preProcess(const string &s);

//Manncher�㷨��ʱ�临�Ӷ�ΪO(n), �ռ临�Ӷ�ΪO(n)
string longestPalindrome3(string s)
{
    const int len = s.size();
    if (len <= 1)
        return s;
    //Manncher�㷨��o��n��
    string str = preProcess(s);
    int n = str.size(), id = 0, mx = 0;
    vector<int> p(n, 0);
    for (int i = 1; i < n - 1; i++)
    {
        p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;
        //if(mx <= i || (mx > i && p[2*id-i] == mx - i)) //��������б�岿�ֵ�ע�ͣ������Ҫ�ɲ�Ҫ
        while (str[i + p[i]] == str[i - p[i]])
            p[i]++;
        if (i + p[i] > mx)
        {
            mx = i + p[i];
            id = i;
        }
    }

    //����p��Ѱ�������ĳ���
    int maxLen = 0, index = 0;
    for (int i = 1; i < n - 1; i++)
        if (p[i] > maxLen)
        {
            maxLen = p[i];
            index = i;
        }
    return s.substr((index - maxLen) / 2, maxLen - 1);
}

//Ԥ�����ַ�����abcԤ�������$#a#b#c#^
string preProcess(const string &s)
{
    int n = s.size();
    string res;
    res.push_back('$');//��$�ŵ��ַ���ͷ��
    res.push_back('#');//��#��Ϊԭ���ַ�����ÿ���ַ��ļ��
    for (int i = 0; i < n; i++)
    {
        res.push_back(s[i]);
        res.push_back('#');
    }
    res.push_back('^');//��^��Ϊ�ַ����Ľ�β
    return res;
}


////////////////////////////////////////////
// ŷ���������������
////////////////////////////////////////////
struct tagPoint
{
    double x, y;
};

//�����i�͵�j֮���ֱ�߾���  
double distance(tagPoint *points, int i, int j)
{
    return sqrt((points[i].x - points[j].x) * (points[i].x - points[j].x) +
        (points[i].y - points[j].y) * (points[i].y - points[j].y));
}

//@pointsΪ��������������飬�±��1��ʼ
double DP(tagPoint *points, int n)
{
    const int MaxVal = 999999;
    const int MaxLen = 100;
    double b[MaxLen][MaxLen];//��¼���·���ĳ���  
    //������������µ�b[i][j]��1 <= i <= j  
    //��ʼ��  
    b[1][2] = distance(points, 1, 2);
    for (int j = 3; j <= n; ++j)
    {
        //i < j-1  
        for (int i = 1; i <= j - 2; ++i)
        {
            b[i][j] = b[i][j - 1] + distance(points, j - 1, j);
        }
        //i = j - 1,b[i][j] = min(b[k][j - 1] + distance(k,j));  
        b[j - 1][j] = MaxVal;
        for (int k = 1; k <= j - 2; ++k)
        {
            double temp = b[k][j - 1] + distance(points, k, j);
            if (temp < b[j - 1][j])
            {
                b[j - 1][j] = temp;
            }
        }
    }

    b[n][n] = b[n - 1][n] + distance(points, n - 1, n);

    return b[n][n];
}

//��������
int BinarySearch(int array[], int n, int value)
{
    int left = 0;
    int right = n - 1;
    int mid;
    while (left <= right)
    {
        //mid = (left + right) / 2;
        mid = left + ((right - left) >> 1);         //�������
        //mid = (right&left) + ((right^left) >> 1); //this is amazing��but worse
        if (array[mid] > value)
            right = mid - 1;
        else if (array[mid] < value)
            left = mid + 1;
        else
            return mid;
    }
    return -1;
}

/////////////////////////////////////////////////////
// �����������
////////////////////////////////////////////////////
void GetLCS(string str, char **record, int m, int n, string& dst)
{
    if (m == 0 || n == 0)
        return;
    while (m > 0 && n > 0 && record[m-1][n-1] != '\0')
    {
        if (record[m - 1][n - 1] == '|')
            m--;
        else if (record[m - 1][n - 1] == '-')
            n--;
        else if (record[m - 1][n - 1] == '\\')
        {
            dst += str[m - 2];
            m--, n--;
        }
    }
}

string LCSLength(string first, string second)
{
    string result;
    const int m = first.length();
    const int n = second.length();
    int **res = new int*[m + 1];
    char **record = new char*[m + 1];
    for (int i = 0; i <= m; i++)
    {
        res[i] = new int[n + 1];
        record[i] = new char[n + 1];
        memset(res[i], 0, sizeof(int)*(n + 1));
        memset(record[i], 0, sizeof(char)*(n + 1));
    }
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (first[i - 1] == second[j - 1])
            {
                res[i][j] = res[i - 1][j - 1] + 1;
                record[i][j] = '\\';
            }
            else if (res[i - 1][j] >= res[i][j - 1])
            {
                res[i][j] = res[i - 1][j];
                record[i][j] = '|';
            }
            else
            {
                res[i][j] = res[i][j - 1];
                record[i][j] = '-';
            }
        }
    }
    GetLCS(first, record, m + 1, n + 1, result);
    std::reverse(result.begin(), result.end());
    return result;
}

//////////////////////////////////////////////////////////////
// ̰���㷨
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
//�ѡ������

//�ݹ�̰���㷨
typedef pair<int, int> ActiveInfo;

void _RecursiveActivitySelector(vector<ActiveInfo> &active, int k, vector<ActiveInfo> &res)
{
    int m = k + 1;
    int n = active.size();
    while (m < n && active[m].first < active[k].second)
        m++;
    if (m < n)
    {
        res.push_back(active[m - 1]);
        _RecursiveActivitySelector(active, m, res);
    }
}

// ��������ݻ��
//
// @active - �����(����pair<int, int>�洢�˻��ʼ�ͽ���ʱ�䣬�ü��ϱ���
//               �Ѿ�������ʱ��ǵݼ�����)
// ����active��һ�������ݻ��
vector<ActiveInfo> RecursiveActivitySelector(vector<ActiveInfo> &active)
{
    vector<ActiveInfo> res;
    res.push_back(active[0]);
    _RecursiveActivitySelector(active, 0, res);
    return res;
}

//����̰���㷨
vector<ActiveInfo> GreedyActivitySelector(vector<ActiveInfo> &active)
{
    int n = active.size();
    int m = 1, k = 0;
    vector<ActiveInfo> res;
    res.push_back(active[0]);

    while (m < n)
    {
        if (active[m].first >= active[k].second)
        {
            k = m;
            res.push_back(active[m]);
        }
        m++;
    }
    return res;
}

//////////////////////////////////////////////////////////
// ����ͼ��ɫ����

int IntervalGraphColoring1(vector<ActiveInfo> &active)
{
    int res = 0; //��Ҫ���Ҹ���
    int n = active.size();
    bool *arr = new bool[n];
    memset(arr, 0, sizeof(bool)*n);

    int m = 0, j = 0, k = 0;
    while (j < n)
    {
        while (j < n && arr[j] == true)
            j++;
        if (j >= n)
            break;
        arr[j] = true;
        res++;

        //�ڳ���ǹ��Ļ������������ݻ��
        k = j;
        m = k + 1;
        while (m < n)
        {
            if (arr[m] == false && active[m].first >= active[k].second)
            {
                k = m;
                arr[m] = true;
            }
            m++;
        }
    }
    delete[]arr;
    return res;
}

int IntervalGraphColoring2(vector<ActiveInfo> &active)
{
    //1.�������л��ʱ��㰴�����������n���������2n��ʱ��㣩��
    //  ��¼ÿ��ʱ������ʼ�Ļ�����ֹ�ģ��������ʱ�򣬶���ֵ��ͬ��ʱ��㣬��
    //  ������ֹʱ���Ļ���������ǰ�档
    //2.�ʼ��ѡ���һ����ʼʱ��㣬������Ӧ�Ļ����һ�����ң�ͬʱ��¼���
    //  ��ʼʱ����Ӧ����ֹʱ��㡣
    //3.���Ű���ѡ���i����ʼʱ��㣨ֻѡ����ʼʱ��㣩�����ڵ�i����ʼʱ��㣬�Ƚ�
    //  �������н����еĻ����ֹʱ��㣬������ĳ����ֹʱ��㣬��ֱ�ӽ���i����ʼʱ��
    //  ���Ӧ�Ļ�Ž���Ӧ�Ľ��ң������¿���һ������������������

    //������
    return 0;
}

///////////////////////////////////////////////////////////////////
// �������������������

typedef pair<int, int> TaskInfo;

// �����ܳͷ�ֵ(����task���б����Ѿ����ճͷ�ֵ�����ݼ�����)
// ʱ�临�Ӷ�O(n^2)
int GreedyTaskScheduling(vector<TaskInfo> &task)
{
    int n = task.size();
    if (n <= 1)
        return 0;
    int i = n - 1, j = 1;
    for (; i > 0; i--)
    {
        for (j = 1; j <= i; j++)
        {
            if ((task[j].first < task[j - 1].first && task[j].first >= j) ||
                    (task[j - 1].first < j && task[j].first > task[j-1].first))
                swap(task[j - 1], task[j]);
        }
    }
    i = n - 1;
    int ret = 0;
    while (i >= 0)
    {
        if (task[i].first >= i)
            break;
        ret += task[i].second;
        i--;
    }
        
    return ret;
}

// �����������
//
// �����ܳͷ�ֵ(����task���б����Ѿ����ճͷ�ֵ�����ݼ�����)
// ��result��NULL�������˳��洢��result������
// ʱ�临�Ӷ�O(n)���ռ临�Ӷ�O(n)
int GreedyTaskScheduling1(const vector<TaskInfo> &task, int *result)
{
    int n = task.size();
    if (n <= 1)
        return 0;
    int *p;
    if (result == NULL)
        p = new int[n];
    else
        p = result;
    memset(p, 0, sizeof(int)*n);
    
    int i, tmp;
    for (i = 0; i < n; i++)
    {
        tmp = task[i].first;
        while (tmp > 0 && p[tmp - 1] != 0)
            tmp--;
        if (tmp == 0)
        {
            tmp = n;
            while (p[tmp - 1] != 0)
                tmp--;
        }
        p[tmp - 1] = i + 1;
    }

    tmp = 0;
    i = n - 1;
    while (i >= 0 && task[p[i] - 1].first < i)
    {
        tmp += task[p[i] - 1].second;
        i--;
    }

    if (result == NULL)
        delete[]p;
    
    return tmp;
}

#endif //_ALGO_H

