#include <iostream>
#include <fstream>
#include <vector>
#include "data.hpp"

using namespace std;

struct vertex{
    int value;
    int edgenum=0;
    vector<vertex*> neighbor;
};

vector<vertex*> vertices;

vertex* Insert(int num){
    for (int i = 0; i < vertices.size(); i++)
    {
        if(num == vertices[i]->value){
            vertices[i]->edgenum++;
            return vertices[i];
        }
    }
    vertex *v = new vertex;
    v->value = num;
    v->edgenum++;
    vertices.push_back(v);
    return v;
}


void solve(tTestData* data){
    ofstream ofs("output.txt");

    for (int cases = 0; cases < data->t; ++cases) {
        struct tTestCase *temp = &(data->testcase[cases]);

        //store in vector
        vertices.reserve(temp->n);
        
        for (int i = 0; i < data->testcase[cases].n-1; ++i)
        {
            vertex *v1 = Insert(temp->edges[i][0]);
            vertex *v2 = Insert(temp->edges[i][1]);
            v1->neighbor.push_back(v2);
            v2->neighbor.push_back(v1);
        }

        //Find start vertex
        vertex start;
        vertex end;
        for(int i = 0; i < vertices.size();++i){
            if(vertices[i]->edgenum==1 && start.edgenum==0){
                start = *vertices[i];
            }
            else if(vertices[i]->edgenum==1 && start.value < vertices[i]->value){
                start = *vertices[i];
            }
        }

        if (temp->i <= temp->n/2)
        {
            vertex *next = start.neighbor[0];
            vertex *cur = &start;

            for (int j = 0; j < temp->i; ++j)
            {
                if(next->neighbor[0]->value != cur->value){
                    cur = next;
                    next = next->neighbor[0];
                }
                else if(next->edgenum==2){
                    cur = next;
                    next = next->neighbor[1];
                }
                else{
                    cur = next;
                }
            }
        }
        else{
            vertex *pre = start.neighbor[0];
            vertex *cur = &start;
        }

        ofs << cur->value << endl;

        while(!vertices.empty()) {
            delete vertices.back();
            vertices.pop_back();
        }
    }
}

