#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "data.hpp"

using namespace std;

//int tablesize[20];  //at most 20 testcase
bool preplacerow[50];
bool my[50], md1[99], md2[99];
int count0 = 0;

void solve_optimize(int t, int x){
    if(x==t){
        count0++;
        return;
    }
    if(preplacerow[x]==1){
        solve_optimize(t, x + 1);
        return;
    }
    for (int y = 0; y <t; y++)
    {
        int d1 = (x + y) % (2 * t - 1);
        int d2 = (x - y + (2 * t - 1)) % (2 * t - 1);
        if (my[y] != 1 && md1[d1] != 1 && md2[d2] != 1)
        {
            my[y] = md1[d1] = md2[d2] = 1;
            solve_optimize(t, x + 1);
            my[y] = md1[d1] = md2[d2] = 0;
        }
    }
}

void solve(tTestData* test_data){
    ofstream output("output.txt");
    for (int i = 0; i < test_data->t; ++i)
    {
        for (int  k = 0; k < test_data->testcase[i].n; k++)
        {
            my[k] = 0;
            preplacerow[k] = 0;
        }
        for (int p = 0; p < 2* test_data->testcase[i].n-1; p++){
            md1[p] = 0;
            md2[p] = 0;
        }
        // preplace
        for (int j = 0; j < test_data->testcase[i].m; ++j)
        {
            int x = test_data->testcase[i].preplace[j][0];
            int y = test_data->testcase[i].preplace[j][1];
            my[y] = 1;
            md1[(x + y) % (2 *  test_data->testcase[i].n - 1)] = 1;
            md2[(x - y + (2 *  test_data->testcase[i].n - 1)) % (2 *  test_data->testcase[i].n - 1)] = 1;
            preplacerow[x] = 1;
        }
        int start = 0;
        while (preplacerow[start]!=0){
            if(start==test_data->testcase[i].n){
                break;
            }
            start++;
        }
        solve_optimize(test_data->testcase[i].n, start);
        output<< count0 << endl;
        count0 = 0;
    }
	output.close();
}

