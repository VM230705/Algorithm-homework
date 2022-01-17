#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <string>

#define max_test_num 20

using namespace std;
// struct tTestData {
//     int testcase_num;
//     int seq_num[max_test_num];
//     int seq[max_test_num][500000];
// };
struct tTestData {
    int testcase_num;
    int seq_num[max_test_num];
    int* seq[max_test_num];
    tTestData(){ 
        for (int i=0; i<max_test_num; ++i){
            seq[i] = new int[500000];
        }
    }
};

inline long long int mergeSort(int arr[], int temp[], int left, int right);
inline void merge(int arr[], int temp[], int left, int mid, int right);


inline long long int increasePairs(int arr[], int array_size)
{
    //cout << "array size " << array_size << endl;
    int temp[array_size];
    return mergeSort(arr, temp, 0, array_size - 1);
}

inline long long int mergeSort(int arr[], int temp[], int left, int right)
{
    if(left >= right) return 0;
    long long int mid = left + (right - left)/2;
    long long int count = mergeSort(arr, temp, left, mid) + mergeSort(arr, temp, mid + 1, right);
    for(int i = left, j = mid+1; i<=mid; ++i){
        while(j<=right && arr[i]>arr[j]/2.0){
            j++;
        }
        count += right - j + 1;
    }

    merge(arr, temp, left, mid, right);
    return count;
}


inline void merge(int arr[], int temp[], int left, int mid, int right)
{
    for (int i = left; i <= right; ++i)
    {
        temp[i] = arr[i];
    }
    int p1 = left;//pointer for left part
    int p2 = mid+1;//pointer for right part
    int k = left;//pointer for sorted array
    while (p1 <= mid || p2 <= right)
    {
        if (p1 > mid || (p2 <= right  && temp[p1] >= temp[p2]))
        {
            arr[k++] = temp[p2++];
        }
        else{
            arr[k++] = temp[p1++];
        }
        
    }
}

int main(){
    ifstream ifs("input.txt");
    tTestData t;

    //Loading Data
    ifs >> t.testcase_num;
    for (int i = 0; i < t.testcase_num; ++i)
    {
        ifs >> t.seq_num[i];
        for (int j = 0; j < t.seq_num[i]; ++j)
        {
            ifs >> t.seq[i][j];
        }
    }
    ifs.close();

    //Solve
    ofstream ofs("output.txt");
    for (int i = 0; i < t.testcase_num; ++i)
    {
        long long int ans = increasePairs(t.seq[i], t.seq_num[i]);
        ofs << ans << endl;
        cout << ans << endl;
    }
    for (int i=0; i<max_test_num; ++i){
        delete[] t.seq[i]; 
    }
    ofs.close();
    return 0;
}