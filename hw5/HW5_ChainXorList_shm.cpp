#pragma GCC optimize("Ofast,unroll-loops")
//#include "data.hpp"
#include <fstream>
#define HASH_MASK 0x0000FFFF
#define SIZE 220755
struct NODE{
	int node;
	unsigned int edge;
	NODE *next;
};
//0x0000FFFF,620755,1080000 1.358
//0x00007FFF,114688,286720
NODE mem[680000];
NODE *edge = &mem[SIZE];
NODE *edge_chain = &mem[SIZE+HASH_MASK+1];
NODE *now;
NODE *nowA;
NODE *nowB;
unsigned int n, I, i, t, k;
int a, b, ansA, ansB;
int main(){
//void solve(tTestData* test_data){
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");
	in >> t;
	while(t--){
		in >> n >> I;
		k = 0;
		for(i = 0; i < n - 1; i++){
			in >> a >> b;
			nowA = &edge[a&HASH_MASK];
			nowB = &edge[b&HASH_MASK];
			if(nowA->node!=0){
				for(;nowA->node != a && nowA->next != nullptr; nowA = nowA->next);
				if(nowA->node != a){
					nowA->next = &edge_chain[k++];
					nowA = nowA->next;
					nowA->node = a;
				}
			}else{
				nowA->node = a;
			}
			if(nowB->node!=0){
				for(;nowB->node != b && nowB->next != nullptr;nowB=nowB->next);
				if(nowB->node != b){
					nowB->next = &edge_chain[k++];
					nowB = nowB->next;
					nowB->node = b;
				}
			}else{
				nowB->node = b;
			}
			nowA->edge ^= (unsigned long long) nowB;
			nowB->edge ^= (unsigned long long) nowA;
		}
		for(; (nowA->edge ^ (unsigned long long)nowB) != 0; ){
			now = nowA;
			nowA = (NODE*) (nowA->edge ^ (unsigned long long)nowB);
			nowB = now;
		}
		a = nowA->node;
		nowB = nullptr;
		if(I + I < n){
			for(i = I; i > 0; i--){
				now = nowA;
				nowA = (NODE*) (nowA->edge ^ (unsigned long long)nowB);
				nowB = now;
				nowB->node = 0;
				nowB->edge = 0;
				nowB->next = nullptr;
			}
			ansA = nowA->node;
			for(i = n-I-I; i > 1; i--){
				now = nowA;
				nowA = (NODE*) (nowA->edge ^ (unsigned long long)nowB);
				nowB = now;
				nowB->node = 0;
				nowB->edge = 0;
				nowB->next = nullptr;
			}
			ansB = nowA->node;
			for(i = I; i > 0; i--){
				now = nowA;
				nowA = (NODE*) (nowA->edge ^ (unsigned long long)nowB);
				nowB = now;
				nowB->node = 0;
				nowB->edge = 0;
				nowB->next = nullptr;
			}
			b = nowA->node;
			nowA->node = 0;
			nowA->edge = 0;
			nowA->next = nullptr;
			if(a > b){
				out << ansA << '\n';
			}else{
				out << ansB << '\n';
			}
		}else{
			for(i = n-I-1; i > 0; i--){
				now = nowA;
				nowA = (NODE*) (nowA->edge ^ (unsigned long long)nowB);
				nowB = now;
				nowB->node = 0;
				nowB->edge = 0;
				nowB->next = nullptr;
			}
			ansA = nowA->node;
			for(i = I+I+2-n; i > 1; i--){
				now = nowA;
				nowA = (NODE*) (nowA->edge ^ (unsigned long long)nowB);
				nowB = now;
				nowB->node = 0;
				nowB->edge = 0;
				nowB->next = nullptr;
			}
			ansB = nowA->node;
			for(i = n-I-1; i > 0; i--){
				now = nowA;
				nowA = (NODE*) (nowA->edge ^ (unsigned long long)nowB);
				nowB = now;
				nowB->node = 0;
				nowB->edge = 0;
				nowB->next = nullptr;
			}
			b = nowA->node;
			nowA->node = 0;
			nowA->edge = 0;
			nowA->next = nullptr;
			if(a < b){
				out << ansA << '\n';
			}else{
				out << ansB << '\n';
			}
		}
	}
}
