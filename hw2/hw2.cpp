
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <map>

using namespace std;
struct Matrix{
    int row;
    int column;
    map<pair<int, int>, int> matrix;
};

inline void Assign(Matrix* a, int r, int c, int v){
    a->matrix[make_pair(r, c)] = v;
}

inline void Print(Matrix* a ,ofstream&output){
    for ( auto x : a->matrix)
    {
        if(x.second == 0){
            continue;
        }
        output << "(" << x.first.first<< " " << x.first.second << " " << x.second << ")"<< " ";
    }
    output << endl;
}

int main(){
    ifstream input;
    ofstream output;
    input.open("input.txt");
    output.open("output.txt");
    string line;
    vector<pair<Matrix,string>> Matrices;
    stringstream ss;
    while(getline(input,line)){
        ss << line;
        string word;
        ss >> word;

        if(word == "Matrix")    //Construct
        {
            string name;
            Matrix a;
            ss >> name;
            Matrices.push_back(make_pair(a,name));
        }
        else if (word=="Assign")    //assign value
        {
            string temp;
            ss >> temp;
            for (long long unsigned int i = 0; i < Matrices.size(); ++i)
            {
                if(temp == Matrices[i].second){
                    int row, column, value;
                    ss >> row >> column >> value;
                    Assign(&Matrices[i].first, row, column, value);
                }
            }
        }
        else if (word== "Delete")
        {
            for (long long unsigned int i = 0; i < Matrices.size(); ++i)
            {
                string temp;
                ss >> temp;
                if(temp == Matrices[i].second){
                    Matrices.erase(Matrices.begin() + i);
                }
            }
        }
        else if (word=="Mult")
        {
            string a,b,c;
            ss >> a >> b >> c;
            Matrix m1, m2;
            int c_index;
            for (long long unsigned int i = 0; i < Matrices.size(); ++i)
            {
                if(a==Matrices[i].second){
                    m1 =Matrices[i].first;
                }
                else if (b==Matrices[i].second)
                {
                    m2 = Matrices[i].first;
                }
                else if (c==Matrices[i].second)
                {
                    c_index = i;
                }
            }
            //only if a.column == b.row ,they need multiply
            for (auto x: m1.matrix){
                map<pair<int, int>, int>::iterator start, end, iter;
                pair<int, int> p1, p2;
                p1 = make_pair(x.first.second , 0);
                p2 = make_pair(x.first.second + 1, 0);
                m2.matrix[p1];
                m2.matrix[p2];
                start = m2.matrix.find(p1);
                end = m2.matrix.find(p2);
                for (iter = start; iter != end; ++iter)
                {
                    Matrices[c_index].first.matrix[make_pair(x.first.first, iter->first.second)] += x.second * iter->second;
                }
            }
        }
        else if (word=="Add")
        {
            string a,b,c;
            ss >> a >> b >> c;
            Matrix m1, m2;
            int c_index;
            for (long long unsigned int i = 0; i < Matrices.size(); ++i)
            {
                if(a==Matrices[i].second){
                    m1 = Matrices[i].first;
                }
                else if (b==Matrices[i].second)
                {
                    m2 = Matrices[i].first;
                }
                else if (c==Matrices[i].second)
                {
                    c_index = i;
                }
            }
            //paste a and b value to c
            for(auto a1:m1.matrix){                     
                Matrices[c_index].first.matrix[a1.first] = a1.second;
            }
            for(auto b1:m2.matrix){
                Matrices[c_index].first.matrix[b1.first] = b1.second;
            }
            //if a and b in same position have value then exchange
            for (auto x : m1.matrix){                 
                for(auto y: m2.matrix){
                    if(x.first == y.first ){
                        Matrices[c_index].first.matrix[x.first] = x.second + y.second;
                    }
                }
            }
        }
        else if (word=="Print")
        {
            string temp;
            ss >> temp;
            for (long long unsigned int i = 0; i < Matrices.size(); ++i)
            {
                if(temp == Matrices[i].second){
                    Print(&Matrices[i].first,output);
                }
            }
        }
        ss.clear();
        ss.str("");
    }

    return 0;
}