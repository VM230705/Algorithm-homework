#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#define MAX_NUM 5001
using namespace std;
int main()
{
	fstream input;
	fstream output;
	input.open("input.txt", ios::in);
	output.open("output.txt", ios::out);
	int n;
	int8_t count[MAX_NUM] = {};
	input >> n;
	input.ignore();
	while(n--)
	{
		string array;
		stringstream nums;
		getline(input, array);
		nums << array;
		int num;
		while(nums >> num)
		{
			count[num]++;
		}
		for(int i = 1; i < MAX_NUM; i++)
		{
			while(count[i] > 0)
			{
				output << i << " ";
				count[i]--;
			}
		}
		output << '\n';
	}
	return 0;
}
