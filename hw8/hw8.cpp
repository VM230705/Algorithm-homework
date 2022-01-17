#include <fstream>
#include <cmath>
#include <algorithm>
#include <utility>
#define testcase 936

using namespace std;

int n[testcase], l[testcase], w[testcase];
pair<double, double> left_right[testcase][10000];

inline int minimalcover(int& cases, int& circles){
    double left = 0;
    int count = 0;
    while (left<l[cases]){
        double max = left;
        for (int i = 0; i < circles; ++i){
            // if   p - x <= left && p + x > max 
            if (left_right[cases][i].first <= left && left_right[cases][i].second > max){
                max = left_right[cases][i].second;
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
        int circles = 0;
        int t_radius = 0;
        for (int j = 0; j < n[i]; ++j){
            int pos, rad;
            ifs >> pos >> rad;
            t_radius += rad;
            double x = sqrt(4 * rad * rad - w[i] * w[i])/2;
            if (x<0 || isnan(x) || 2*rad <= w[i]){
                continue;
            }
            left_right[i][circles] = make_pair(pos - x, pos + x);
            circles += 1;
        }
        //直徑加總<長
        if (2*t_radius<= l[i]){
            ofs << -1 << endl;
            continue;
        }
        
        sort(begin(left_right[i]), begin(left_right[i]) + circles);
        ofs << minimalcover(i, circles) << endl;
    }
    return 0;
}