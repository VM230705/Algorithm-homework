#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "data.hpp"

using namespace std;

void solve(tTestData* data){
    ofstream output("output.txt");
    for (int i = 0; i < data->testcase_num; i++)
    {
        long long int count0 = 0;
        for (int j = 0; j < data->seq_num[i]; j++)
        {
            for (int k = j + 1; k < data->seq_num[i]; k++)
            {
                if ((long long)2 * data->seq[i][j] <= data->seq[i][k]){
                    count0++;
                }
            }
        }
        output << count0 << endl;
        cout << count0 << endl;
    }
    output.close();
}
