#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
using namespace std;

int main()
{
 int N;
 char c;
 ifstream fin("input.txt");
 ofstream fout("output.txt");

 fin >> N;
 string s;
 getline(fin, s, '\n');
 for (int i = 0; i < N; i++) {
  getline(fin, s, '\n');
  int num = 0;
  int count[5001] = {};
  for (int j = 0; j <= s.size(); j++) { //為了避免第一個輸入是0
   if (isdigit(s[j])) {//276   1st->num = 0*10+ 2;2nd-> num = 2*10 + 7; 3rd = 27*10 + 6;
    num = num * 10 + (s[j] - '0');
   }
   else{//讀到空白的話
    count[num]++;
    num = 0;
   }
  }
  
  for (int j = 0; j < 5001; j++) {
   while (count[j]--) {
    fout << j << ' ';
   }
  }
  fout << '\n';
 }
 return 0;
}