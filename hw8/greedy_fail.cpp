#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <utility>
#define testcase 936

using namespace std;

int n[testcase], l[testcase], w[testcase];
pair<int, int> rad_pos[testcase][10000];
double start[10000]; //record start index of circles
pair<int, pair<int, int>> last_rad_pos [10000];
// int p[testcase][10000], r[testcase][10000];

int minimalcover(int& cases, int& circles){
     //計算直徑加總是否小於長
    int t_radius = 0;
    for (int i = 0; i < circles; i++){
        t_radius += rad_pos[cases][i].first;
    }
    if (2*t_radius<=l[cases]){
        return -1;
    }

    for (int i = 0; i < circles; ++i){
        last_rad_pos[i] = make_pair(rad_pos[cases][i].first + rad_pos[cases][i].second, rad_pos[cases][i]);
    }
    sort(begin(last_rad_pos), begin(last_rad_pos) + circles);
    for (int i = 0; i < circles; ++i){
        cout << last_rad_pos[i].first<<" "<< last_rad_pos[i].second.first <<" " <<last_rad_pos[i].second.second<< endl;
    }
    double x = sqrt(4 * last_rad_pos[0].second.first * last_rad_pos[0].second.first - w[cases] * w[cases])/2;
    double front = last_rad_pos[0].second.second - x;
    double cover = last_rad_pos[0].second.second + x;
    int count = 1;
    if (x<0 || isnan(x)){
        front = 0;
        cover = 0;
    }
    start[0] = front;

    //solve
    for (int i=1; i < circles; ++i){
        cout << "i : " << i << endl;
        cout << " p : " << last_rad_pos[i-1].second.second <<" r : " << last_rad_pos[i-1].second.first << endl;
        cout << "cover : " << cover << endl;
        cout << "front : " << front << endl<<endl;
        cout << "x: " << x << endl;

        //2r <= w
        if (2*last_rad_pos[i].second.first<=w[cases]){
            continue;
        }
        // x =sqrt(4r^2 - w^2)/2 = 圓佔正方形的一半邊長
        x = sqrt(4 * last_rad_pos[i].second.first * last_rad_pos[i].second.first - w[cases] * w[cases])/2;
        // cout << "x: " << x << endl;
        if (x<0 || isnan(x) || (cover >= l[cases] && (last_rad_pos[i].second.second - x) > front)){
            continue;
        }
        
        if (last_rad_pos[i].second.second - x > cover){
            cout << 1 << endl
                << endl;
            continue;
        }
        else if (last_rad_pos[i].second.second + x > cover && last_rad_pos[i].second.second - x <= front){
            cover = last_rad_pos[i].second.second + x;
            front = last_rad_pos[i].second.second - x;
            int circle_in_range = 0;
            for (int j = 0; j < count; ++j){
                if(start[j] > front)
                    circle_in_range += 1;
            }
            if (circle_in_range>1){
                count = count - circle_in_range + 1;
            }
            start[count-1] = front;
            cout << 2 << endl
                << endl;
        }
        else if (last_rad_pos[i].second.second + x > cover && last_rad_pos[i].second.second - x > front && last_rad_pos[i].second.second - x <= cover){
            count += 1;
            cover = last_rad_pos[i].second.second + x;
            front = last_rad_pos[i].second.second - x;
            start[count - 1] = front;
            cout << "count : " << count << endl;
            cout << 3 << endl
                << endl;
        }
        else{
            break;
        }
    }

    if (cover < l[cases]){
        return -1;
    }
    else{
        return count;
    }
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
            // ifs >> p[i][j] >> r[i][j];
        }
    }


    // for (int i = 0; i < testcase; ++i){
    //     //cout << n[i] << " " << l[i] << " " << w[i] << endl;
    //     // for (int j = 0; j < n[i]; ++j)
    //     // {
    //     //     //cout << rad_pos[i][j].first << " " << rad_pos[i][j].second << endl;
    //     // }
    //     sort(begin(rad_pos[i]), begin(rad_pos[i])+n[i]);
    // }
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