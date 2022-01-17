#pragma GCC optimization ("Ofast")
#pragma GCC optimization ("unroll-loops")
#include <iostream>
#include <fstream>
#include <cstring>
#include "data.hpp"

#define max_test_num 20

using namespace std;

int array[1500000];
int* temp = array + 540000;

inline long long int mergeSort(int left, int right);
inline void merge(int left, int mid, int right);


inline long long int increasePairs(int array_size)
{
    return mergeSort(0, array_size - 1);
}

inline long long int mergeSort(int left, int right)
{
    if(left >= right) return 0;
    long long int mid = left + (right - left)/2;
    long long int count = mergeSort(left, mid) + mergeSort(mid + 1, right);
    for(int i = left, j = mid+1; i<=mid; ++i){
        while(j<=right && array[i]>array[j]/2.0){
            j++;
        }
        count += right - j + 1;
    }

    merge(left, mid, right);
    return count;
}


inline void merge(int left, int mid, int right)
{
    for (int i = left; i <= right; ++i)
    {
        temp[i] = array[i];
    }
    int p1 = left;//pointer for left part
    int p2 = mid+1;//pointer for right part
    int k = left;//pointer for sorted array
    while (p1 <= mid || p2 <= right)
    {
        if (p1 > mid || (p2 <= right  && temp[p1] >= temp[p2]))
        {
            array[k] = temp[p2];
            k++;
            p2++;
        }
        else if (p2 > right || (p1 <= mid  && temp[p2] >= temp[p1]))
        {
            array[k] = temp[p1];
            k++;
            p1++;
        }
    }
}


void solve(tTestData* data){
    ofstream ofs("output.txt");
    for (int i = 0; i < data->testcase_num; i++)
    {
        memcpy(array, data->seq[i], sizeof(int) * data->seq_num[i]);
        memcpy(temp, data->seq[i], sizeof(int) * data->seq_num[i]);
        long long int ans = increasePairs(data->seq_num[i]);
        ofs << ans << endl;
        //cout << ans << endl;
    }
    ofs.close();
}
