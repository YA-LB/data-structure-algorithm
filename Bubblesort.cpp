/*排序算法实现*/

#include <iostream>
using namespace std;


/*冒泡排序*/
/*从左向右扫描数据，选择最大的数据，放在右边*/
/*要点：比较相邻的两个数，如果左边的数大于右边的数就进行交换*/
//list[]:要排序数组，n：排序个数大小；
void Bubblesort(int list[], const int n)
{
    for (int i = 0;i < n - 1;i++)
    {   
        for (int j = 0; j < n - i - 1; j++)
        {
            if (list[j] > list[j + 1])
                swap(list[j], list[j+1]);
        }
    }
}



/*选择排序*/
/*从当前未排序的整数中找到一个最小的整数，将它放在已排序的整数列表的最后*/
/*要点：选择排序最小的，往左边选*/
/*想象一条毛巾*/
/*每次比较左右，重新设定最小的位置坐标*/
void  SelectSort(int list[], const int n)
{   
    for (int i = 0; i < n-1; i++)
    {
        int min = i;//先假设最小的就是第一个数
        for (int j = i + 1; j < n; j++)
        {
            if (list[j] < list[i])
            {
                min = j;//
            }
        }
        swap(list[i], list[min]);
    }
}

/*插入排序*/
/*速度在低级排序中最快*/
/*和已经排序好的相互比较，移动已经排序的*/
void InsertSort(int* a,int n)
{
    int in, out;
    //以第一个为基准进行排序
    for (out = 1; out < n; ++out)
    {
        int temp = a[out];
        in = out;
        while (in > 0 && a[in - 1] >= temp)
        {   //满足条件就交换
            a[in] = a[in - 1];
            --in;
        }
        a[in] = temp;

    }
}

/*插入排序(升级版)，用C++的函数模板*/
/*速度在低级排序中最快*/
/*和已经排序好的相互比较，移动已经排序的*/
template<class T>
void InsertionSort(T* a, int n)
{
    int in, out;
    //以第一个为基准进行排序
    for (out = 1; out < n; ++out)
    {
        T temp = a[out];
        in = out;
        while (in > 0 && a[in - 1] >= temp)
        {   //满足条件就交换
            a[in] = a[in - 1];
            --in;
        }
        a[in] = temp;

    }
}



/*顺序查找（线性查找）*/
/*要点：主要运用于没有排序的数据*/
/*a为传入的数组，n为数据个数，x为待查找数据*/
int SequentialSearch(int* a, const int n, const int x)
{
    int i;
    for (i = 0; i < n; i++)
    {
        //找到数据，返回下标
        if (a[i] == x)
            return i;
    }
    //没有找到，返回-1；
    if (i = n)
    {
        return -1;
    }
}
/*二分查找（折半查找）*/
/*要点：必须要先排序
        不断地折半，速度快，100万个数据只要20次，2^20=100万（1M），1G个数只要30次*/
int BinarySearch(int* a, const int x, const int n)
{ 
    int low = 0;//最小下标
    int high = n - 1;//最大下标
    int mid;//折半
    while (low <= high)
    {
        mid = (high + low) / 2;
        if (a[mid] == x)
        {
            return mid;
        }
        else if (a[mid] < x)
        {
            low = mid + 1;
        }
        else if (a[mid]>x)
        {
            high = mid - 1;
        }

    }
    return -1;
}

/*二分查找（折半查找）（迭代版）*/
/*要点：必须要先排序
        不断地折半，速度快，100万个数据只要20次，2^20=100万（1M），1G个数只要30次*/
int BinarySearch(int* a, const int x, const int n)
{
    int low = 0;//最小下标
    int high = n - 1;//最大下标
    int mid;//折半
    while (low <= high)
    {
        mid = (high + low) / 2;
        if (a[mid] == x)
        {
            return mid;
        }
        else if (a[mid] < x)
        {
            low = mid + 1;
        }
        else if (a[mid] > x)
        {
            high = mid - 1;
        }

    }
    return -1;
}


/*递归调用（二分查找）*/
/*自己调用自己*/
/*返回值数组下标*/
int BinarySearch_d(int* a, const int x, const int high, const int low)
{
    if (low <= high)
    {
        int middle = (high + low) / 2;
        if (x < a[middle])
        {
            return BinarySearch_d(a, x, middle - 1, low);
        }
        else if (x > a[middle])
        {
            return BinarySearch_d(a, x, high, middle + 1);
        }
        else return middle;
    }
    return -1;
}



int main()
{
    /*int a[] = { 1,3,2,5,4,6,7,8,5,10};
    double b[]= { 1.1,3.0,2.0,5,4,6,7,8,5,10.1 };
    cout << sizeof(a) << endl;
    cout << sizeof(b) << endl;
   InsertionSort(a, 10);
   InsertionSort(b, 10);
    int k;
    for (int k=0; k < 10; k++)
    {
        cout << a[k] <<" " ;
    }
    for (int k = 0; k < 10; k++)
    {
        cout << b[k] << " ";
    }*/
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
