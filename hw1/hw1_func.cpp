#include <iostream>
#include "data.hpp"
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;



void solve(tTestData* test_data){
	fstream ofs("output.txt", ios::out);

	for(int i=0 ; i<test_data->cnt ; i++){
		std::vector<int> v;
		for(int j=0; j<test_data->seq_size[i]; j++){
			v.push_back(test_data->data[i][j]);
		}
		sort(v.begin(),v.end());
		for(int k=0; k<v.size(); k++){
			ofs << v[k] << " ";
		}
		ofs << endl;
	}
	
	
	ofs.close();
}
