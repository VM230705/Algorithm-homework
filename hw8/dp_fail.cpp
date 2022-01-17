// #include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <utility>
#define testcase 936
using namespace std;

int n[testcase], l[testcase], w[testcase];
pair<int, int> rad_pos[testcase][10000];
// int p[testcase][10000], r[testcase][10000];
int dp[20000];

int minimalcover(int& cases, int& circles){
    //計算直徑加總是否小於長
    int t_radius = 0;
    for (int i = 0; i < circles; i++){
        t_radius += rad_pos[cases][i].first;
    }
    if (2*t_radius<=l[cases]){
        return -1;
    }

    // initialize
    dp[l[cases]+1] = 0;
    for(int i = 0; i <= l[cases]; ++i){
        dp[i] = -1;
    }

    int lastindex = l[cases]+1;
    for (int i = l[cases]; i > 0; --i)      //i = index of array
    {
        // cout << "i = " << i << endl;
        for (int j = circles -1; j  >= 0; --j){   
            if (rad_pos[cases][j].first<=w[cases]/2){
                break;
            }

            // x =sqrt(4r^2 - w^2)/2 = 圓佔正方形的一半邊長
            int x = sqrt(4 * rad_pos[cases][j].first * rad_pos[cases][j].first - w[cases] * w[cases])/2;
            if (x<0){
                continue;
            }
            
            int temp = rad_pos[cases][j].second;
            if(rad_pos[cases][j].second - x<0){
                temp = x;
            }
            // cout << "j = " << j << endl;
            // cout << "circle = r : " << rad_pos[cases][j].first << " p : " << rad_pos[cases][j].second << endl;
            // cout << "x  = " << x << endl;
            // system("pause");
            if (rad_pos[cases][j].second + x >= i && temp - x < lastindex)
            {
                // for (int k = i; k >= rad_pos[cases][j].second - x  ; --k)
                // {
                //     // cout << "k = " << k << endl;
                //     dp[k] = dp[i+1] + 1;
                //     if (k <= 0)
                //         break;
                // }
                dp[temp - x] = dp[lastindex] + 1;
                lastindex = temp - x;
                // cout << temp - x << " = " <<dp[temp-x]<< endl;
                // system("pause");
            }
        }
    }
    
    // for (int i = 0; i <= l[cases]+1; ++i)
    // {
    //     cout << i << " = " << dp[i] << endl;
    //     //system("pause");
    // }
    // cout << dp[0] << endl;
    return dp[0];
}

int main(){
    ifstream ifs("input.txt");
    ofstream ofs("output.txt");
    for (int i = 0; i < testcase; ++i){
        ifs >> n[i] >> l[i] >> w[i];
        for (int j = 0; j < n[i]; ++j){
            int pos, rad;
            ifs >> pos >> rad;
            rad_pos[i][j] = make_pair(rad, pos);
        }
    }


    for (int i = 0; i < testcase; ++i)
    {
        //cout << n[i] << " " << l[i] << " " << w[i] << endl;
        // for (int j = 0; j < n[i]; ++j)
        // {
        //     //cout << rad_pos[i][j].first << " " << rad_pos[i][j].second << endl;
        // }
        sort(begin(rad_pos[i]), begin(rad_pos[i])+n[i]);
    }
    // cout << endl;
    // for (int i = 0; i < testcase; ++i)
    // {
    //     cout << n[i] << " " << l[i] << " " << w[i] << endl;
    //     for (int j = 0; j < n[i]; ++j)
    //     {
    //         cout << rad_pos[i][j].first << " " << rad_pos[i][j].second << endl;
    //     }
    // }
    for (int i = 0; i < testcase; ++i){
        ofs << minimalcover(i, n[i]) << endl;
    }

    return 0;
}