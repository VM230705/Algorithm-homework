#include <iostream>
//#include "data.hpp"
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct tTestData {
	int cnt;
	int* seq_size;
	int** data;
};

void solve(tTestData* test_data){
	ofstream ofs;
	ofs.open("output.txt");

	if(!ofs.is_open()){
		cout <<"file is not is not open"<< endl;
	}
	else{
		for(int i=0 ; i<test_data->cnt ; i++){
			std::sort(test_data->data[i],test_data->data[i]+test_data->seq_size[i]);
		}
	}
	for(int i=0; i<test_data->cnt ; i++){
		for(int j=0 ; j<test_data->seq_size[i] ; j++){
			ofs << test_data->data[i][j] << " ";
		}
		ofs << endl;
	}

	for (int i = 0; i < test_data->cnt; ++i){
		delete [] test_data->data[i];
	}
	delete [] test_data->data;
	delete [] test_data->seq_size;
	
	ofs.close();
}

int main(){
	ifstream infile;
	infile.open("input.txt");
	tTestData test_data;
	string line;
	

	if(!infile.is_open()){
		cout << "not open"<<endl;
	}
	else{
		infile >> test_data.cnt;

		test_data.seq_size = new int[test_data.cnt];
		test_data.data = new int* [test_data.cnt];

		getline(infile,line); //讓下個getline從第二行開始讀
		for(int i=0; i<test_data.cnt; i++){
			std::vector<int> num;
			test_data.data[i] = new int[20000];
			
			getline(infile,line);
			stringstream ss(line);
			string temp;
			while(getline(ss,temp,' ')){
				int n = stoi(temp);
				num.push_back(n);
			}
			test_data.seq_size[i] =  num.size();
          	
          	for(unsigned int j=0; j<num.size(); j++){
          		test_data.data[i][j] = num[j];
          	}     	
		}
		infile.close();

	}
	solve(&test_data);




	return 0;
}