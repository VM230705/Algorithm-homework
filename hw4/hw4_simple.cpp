#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <string>

#define max_test_num 20

using namespace std;

struct tTestData {
    int testcase_num;
    int seq_num[max_test_num];
    int* seq[max_test_num];
    tTestData(){ 
        for (int i=0; i<max_test_num; i++){
            seq[i] = new int[500000];
        }
    }
};



int main(){
    ifstream ifs("input.txt");
    tTestData t;

    //Loading Data
    ifs >> t.testcase_num;
    for (int i = 0; i < t.testcase_num; i++)
    {
        ifs >> t.seq_num[i];
        for (int j = 0; j < t.seq_num[i]; j++)
        {
            ifs >> t.seq[i][j];
        }
    }
    ifs.close();

    //Solve
    ofstream ofs("output.txt");
    for (int i = 0; i < t.testcase_num; i++)
    {
        long long int count0 = 0;
        for (int j = 0; j < t.seq_num[i]; j++)
        {
            for (int k = j + 1; k < t.seq_num[i]; k++)
            {
                if ((long long)2 * t.seq[i][j] <= t.seq[i][k]){
                    cout << "(" << t.seq[i][j] << "," << t.seq[i][k] << ")" << " ";
                    count0++;
                }
            }
        }
        ofs << count0 << endl;
        cout << count0 << endl;
    }
    ofs.close();
   
        
    return 0;
}