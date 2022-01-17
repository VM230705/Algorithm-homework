// #include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <utility>
#define testcase 936

using namespace std;

int n[testcase], l[testcase], w[testcase];
// pair<int, int> rad_pos[testcase][10000];
int p[testcase][10000], r[testcase][10000];
pair<double,pair<double ,pair<int, int>>> x_left_rad_pos [10000];

inline int minimalcover(int& cases, int& circles){
     //計算直徑加總是否小於長
    int t_radius = 0;
    for (int i = 0; i < circles; i++){
        t_radius += r[cases][i];
    }
    if (2*t_radius<=l[cases]){
        return -1;
    }

    int num_of_zero = 0;
    for (int i = 0; i < circles; ++i){
        double x = sqrt(4 * r[cases][i] * r[cases][i] - w[cases] * w[cases])/2;
        if (x<0 || isnan(x) || 2*r[cases][i] <= w[cases]){
            x=0;
            x_left_rad_pos[i] = make_pair(0, make_pair(0, make_pair(0, 0)));
            num_of_zero + 1;
            continue;
        }
        x_left_rad_pos[i] = make_pair(p[cases][i]-x,make_pair(x, make_pair(r[cases][i], p[cases][i])));
    }
    sort(begin(x_left_rad_pos), begin(x_left_rad_pos) + circles);

    double left = 0;
    int count = 0;
    while (left<l[cases]){
        double max = left;
        for (int i = num_of_zero; i < circles; ++i){
            // if   p - x <= left && p + x > max 
            // double x = sqrt(4 * x_left_rad_pos[i].second.second.first * x_left_rad_pos[i].second.second.first - w[cases] * w[cases])/2;

            if (x_left_rad_pos[i].first <= left && x_left_rad_pos[i].second.second.second + x_left_rad_pos[i].second.first > max){
                max = x_left_rad_pos[i].second.second.second + x_left_rad_pos[i].second.first;
            }
        }
        if (max == left){
            return -1;
        }
        left = max;
        count += 1;
    }
    return count;
}

int main(){
    ifstream ifs("input.txt");
    ofstream ofs("output.txt");
    for (int i = 0; i < testcase; ++i){
        ifs >> n[i] >> l[i] >> w[i];
        for (int j = 0; j < n[i]; ++j){
            // int pos, rad;
            // ifs >> pos >> rad;
            // rad_pos[i][j] = make_pair(rad, pos);
            ifs >> p[i][j] >> r[i][j];
        }
        ofs << minimalcover(i, n[i]) << endl;
    }


    // for (int i = 0; i < testcase; ++i){
    //     ofs << minimalcover(i, n[i]) << endl;
    // }

    return 0;
}