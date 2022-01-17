#pragma GCC optimize("Ofast,unroll-loops")
#include "data.hpp"
#include <fstream>
#define MAX 10000000
int edge[20000001], node[100000], cur;
int_fast32_t n, I, i, j, t, a, b;
void solve(tTestData* test_data){
	std::ofstream out("output.txt");
	for(t = 0; t < test_data->t; t++){
		n = test_data->testcase[t].n - 1;
		I = test_data->testcase[t].i;
		for(i = 0, j = 0; i < n; i++){
			a = test_data->testcase[t].edges[i][0] + MAX;
			b = test_data->testcase[t].edges[i][1] + MAX;
			edge[a] ^= (b^-1);
			edge[b] ^= (a^-1);
			node[j++] = a;
			node[j++] = b;
		}
		if( I+I < n){
			cur = 0;
			//find start node
			for(i = 0; ; i++){
				if(edge[node[i]] < 0){
					if(node[i] > cur) cur = node[i];
					edge[node[i]] ^= -1;
					if(b == 0) break;
					b = 0;
				}
			}
			for(i = I; i > 0; i--){
				a = cur;
				cur = edge[cur] ^ b;  //cur = 0^node(start+1)^-1^-1^0  = node(start +1)      (now b=0)
				b = a;
			}
		}else{
			cur = 20000002;
			for(i = j-1; i >= 0; i--){
				//find end  node
				if(edge[node[i]] < 0){
					if(node[i] < cur) cur = node[i];
					edge[node[i]] ^= -1;
					if(b == 0) break;
					b = 0;
				}
			}
			for(i = n - I; i > 0; i--){
				a = cur;
				cur = edge[cur] ^ b; 
				b = a;
			}
		}
		out << cur - MAX << '\n';
		for(i = 0; i < j; i++) edge[node[i]] = 0;
	}
}
