#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

struct tTestCase
{
    int n;
    int m;
    int preplace[50][2];
};

struct tTestData
{
    int t;
    tTestCase testcase[100];
};

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
    for (int y = 0; y < t; y++)
    {
        int d1 = (x + y) % (2 *t - 1);
        int d2 = (x - y + (2 * t - 1)) % (2 * t - 1);
        if (my[y] != 1 && md1[d1] != 1 && md2[d2] != 1)
        {
            my[y] = md1[d1] = md2[d2] = 1;
            solve_optimize(t, x + 1);
            my[y] = md1[d1] = md2[d2] = 0;
        }
    }
}

int main(){
    ifstream input("input.txt");
    ofstream output("output.txt");
    //Loading Data
    string testnum;
    tTestData data;
    input >> testnum;
    data.t = stoi(testnum);
    for (int i = 0; i < data.t; ++i)
    {
        input >>  data.testcase[i].n >> data.testcase[i].m;
        for (int j = 0; j < data.testcase[i].m; ++j)
        {
            input >> data.testcase[i].preplace[j][0] >> data.testcase[i].preplace[j][1];
        }        
    }
    
    //solve problem
    for (int i = 0; i < data.t; ++i)
    {
        //initialize
        for (int  k = 0; k < data.testcase[i].n; k++)
        {
            my[k] = 0;
            preplacerow[k] = 0;
        }
        for (int p = 0; p < 2*data.testcase[i].n-1; p++){
            md1[p] = 0;
            md2[p] = 0;
        }
            // preplace
        for (int j = 0; j < data.testcase[i].m; ++j)
        {
            int x = data.testcase[i].preplace[j][0];
            int y = data.testcase[i].preplace[j][1];
            my[y] = 1;
            md1[(x + y) % (2 * data.testcase[i].n - 1)] = 1;
            md2[(x - y + (2 * data.testcase[i].n - 1)) % (2 *data.testcase[i].n - 1)] = 1;
            preplacerow[x] = 1;
        }

        int start = 0;
        while (preplacerow[start]!=0){
            if(start==data.testcase[i].n){
                break;
            }
            start++;
        }
        solve_optimize(data.testcase[i].n, start);
        output << count0 << endl;
        cout << count0 << endl;
        count0 = 0;
    }
    return 0;
}