#pragma GCC optimization ("Ofast")
#pragma GCC optimization ("unroll-loops")
#include <iostream>
using namespace std;

int main() {
    int N = 0;
    FILE* fin = fopen("input.txt", "r");
    FILE* fout = fopen("output.txt", "w");
    char line[4];
    fgets(line, 4, fin);
    for (int i = 0; line[i] != '\n'; i++) {
        N = N * 10 + (line[i] - '0');
    }
    for (int i = 0; i < N; i++) {
        int num = 0, a = 0;
        int count[5001] = {};
        char in[96000];
        fgets(in, 96000, fin);
        while(in[a] != '\n') {
            if (in[a] >= '0') {
                num = num * 10 + (in[a] - '0');
            }
            else {
                count[num]++;
                num = 0;
            }
            a++;
        }
        count[num]++;
        char out[96000] = "";
        int index = 0;
        for (int j = 0; j < 10; j++) {
            while (count[j]--) {
                out[index] = j + '0';
                index++;
                out[index] = ' ';
                index++;
            }
        }
        for (int j = 10; j < 100; j++) {
            while (count[j]--) {
                out[index] = j / 10 + '0';
                index++;
                out[index] = j % 10 + '0';
                index++;
                out[index] = ' ';
                index++;
            }
        }
        for (int j = 100; j < 1000; j++) {
            while (count[j]--) {
                out[index] = j / 100 + '0';
                index++;
                out[index] = (j % 100)/10 + '0';
                index++;
                out[index] = j % 10 + '0';
                index++;
                out[index] = ' ';
                index++;
            }
        }
        for (int j = 1000; j < 5001; j++) {
            while (count[j]--) {
                out[index] = j / 1000 + '0';
                index++;
                out[index] = (j % 1000) / 100 + '0';
                index++;
                out[index] = (j % 100) / 10 + '0';
                index++;
                out[index] = j % 10 + '0';
                index++;
                out[index] = ' ';
                index++;
            }
        }
        fwrite(out, 1, index, fout);
        fwrite("\n", 1, 1, fout);
    }
    fclose(fin);
    fclose(fout);
    return 0;
}