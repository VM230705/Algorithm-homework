#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// struct singleTestCase{
//     int M;
//     char word[1024][128];
//     char sentence[32768];
// };
// struct tTestData {
//     int N;
//     struct singleTestCase data[128];
// };

string word[128][1024];
string sentence[128];
int dp[32768];

inline int wordbreak(int& cases, int& dict){
    dp[sentence[cases].size()] = 0;
    for(int i = 0; i < sentence[cases].size(); ++i)
    {
        dp[i] = -1;
    }
    
    for (int i = sentence[cases].size(); i > 0; --i)
    {
        //cout << "i "<<i << endl;
        for (int j = 0; j < dict; ++j)
        {
            //cout <<"j " <<j << endl;
            int len = word[cases][j].size();
            //cout << "len " << len << endl;
            if (len > i || dp[i]==-1){      //len > i (out of range) dp[i]==-1代表後面的字元無法在字典中找到
                continue;
            }
            
            if(dp[i - len]==-1 && word[cases][j] == sentence[cases].substr(i-len, len) ){
                // cout << i << endl;
                // cout << word[cases][j] << endl;
                dp[i - len] = dp[i] + 1;
            }
        }
    }
    // for (int i = 0; i <= sentence[cases].size(); i++)
    // {
    //     cout << "index " << i << " = " << dp[i] << endl;
    // }
    
    //cout <<"dp[0] = "<< dp[0] << endl;
    return dp[0];
}

int main(){
    ifstream ifs("input.txt");
    ofstream ofs("output.txt");
    //load data
    int N;
    int M[128];
    ifs >> N;
    for (int i = 0; i < N; ++i)
    {
        ifs >>M[i];
        for (int j = 0; j < M[i]; ++j)
        {
            ifs >> word[i][j];
        }
        ifs >> sentence[i];
    }

    for (int i = 0; i < N; ++i)
    {
        ofs << wordbreak(i, M[i]) << endl;
    }
    
    // cout << N << endl;
    // for (int i = 0; i < N; i++)
    // {
    //     cout << M[i] << endl;
    //     for (int j = 0; j < M[i]; j++)
    //     {
    //         cout <<word[i][j] << endl;
    //     }
    //     cout << sentence[i] << endl;
    // }
    
    return 0;
}