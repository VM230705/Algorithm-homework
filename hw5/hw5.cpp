#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct tTestCase {
    int n;
    int i;
    int** edges = new int*[50000];
    tTestCase(){
        for (int j = 0; j < 50000;++j)
        {
            edges[j] = new int[2];
        }
    }
};

struct tTestData {
    int t;
    struct tTestCase testcase[10];
};

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

int main(){
    ifstream ifs("input.txt");
    ofstream ofs("output.txt");
    tTestData data;
    //Load data
    ifs >> data.t;
    for (int cases = 0; cases < data.t; ++cases) {
        struct tTestCase *temp = &(data.testcase[cases]);
        
        ifs >> temp->n >> temp->i;
        for(int j = 0; j < (temp->n) - 1; j++) {
            ifs >> temp->edges[j][0] >> temp->edges[j][1];
        }
    }
    
    //Solve
    for (int cases = 0; cases < data.t; ++cases) {
        struct tTestCase *temp = &(data.testcase[cases]);

        //store in vector
        vertices.reserve(temp->n);
        
        for (int i = 0; i < data.testcase[cases].n-1; ++i)
        {
            vertex *v1 = Insert(temp->edges[i][0]);
            vertex *v2 = Insert(temp->edges[i][1]);
            v1->neighbor.push_back(v2);
            v2->neighbor.push_back(v1);
        }

        //Find start vertex
        //cout << vertices.size() << endl;
        vertex start;
        for(int i = 0; i < vertices.size();++i){
            if(vertices[i]->edgenum==1 && start.edgenum==0){
                start = *vertices[i];
            }
            else if(vertices[i]->edgenum==1 && start.value < vertices[i]->value){
                start = *vertices[i];
            }
        }

        // for(int i = 0; i < vertices.size();++i){
        //     cout << "value " << vertices[i]->value << endl;
        //     cout << "edge " << vertices[i]->edgenum << endl;
        //     cout << vertices[i]->neighbor.size() << endl;
        //     cout << "n1 " << vertices[i]->neighbor[0]->value << endl;
        //     if (vertices[i]->edgenum == 2){
        //         cout << "n2 " << vertices[i]->neighbor[1]->value << endl;
        //     }
        //     cout << endl;
        // }

        //cout << start.neighbor[0]->value << endl;
        vertex *next = start.neighbor[0];
        vertex *cur = &start;
        for (int j = 0; j < temp->i; ++j)
        {
            //cout << j << endl;
            //cout <<"cur " <<cur->value << endl;
            // cout << "next  " << next->value << endl;
            // cout << "next nei 1" << next->neighbor[0]->value << endl;
            // cout << "next nei 2" << next->neighbor[1]->value << endl;
            //cout << j << endl;
            if(next->neighbor[0]->value != cur->value){
                cur = next;
                next = next->neighbor[0];
                // cout << "next " << next->neighbor[0]->value << endl;
            }
            else if(next->edgenum==2){
                cur = next;
                next = next->neighbor[1];
                // cout << "next " << next->neighbor[1]->value << endl;
            }
            else{
                cur = next;
            }
        }
        ofs << cur->value << endl;
        cout << cur->value<<endl;

        while(!vertices.empty()) {
            delete vertices.back();
            vertices.pop_back();
        }

        for (int j = 0; j < 50000;++j)
        {
            delete[] data.testcase[cases].edges[j];
        }
        delete[] data.testcase[cases].edges;
    }
    return 0;
}
