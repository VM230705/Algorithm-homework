// #include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

struct vertex{
    int num;
    vector<vertex*> adj;
    bool color = 0; // blue = 1  green = 0
};

vector<vertex*> vertices;

vertex* newVertex(int& n){
    vertex *v = new vertex();
    v->num = n;
    vertices.push_back(v);
    return v;
};

void add(int& n1, int&n2){
    vertex *v1, *v2;
    bool flag1 = 0, flag2 = 0;
    for (int i = 0; i < vertices.size(); i++){
        if(vertices[i]->num == n1){
            flag1 = 1;
            v1 = vertices[i];
        }
        if (vertices[i]->num == n2){
            flag2 = 1;
            v2 = vertices[i];
        }
    }
    if(!flag1){
        v1 = newVertex(n1);
    }
    if (!flag2){
        v2 = newVertex(n2);
    }
    v1->adj.push_back(v2);
    v2->adj.push_back(v1);
}


bool visited[101];
bool blue[101];
void BFS(vertex* src, int& index, ofstream& ofs){
    for(int i = 1; i < vertices.size(); ++i){
        visited[i] = false;
        blue[i] = false;
    }
    visited[0] = true;
    blue[0] = true;

    int lastblue=0;
    src->color = true;
    queue<vertex*> q;
    q.push(src);

    while(!q.empty()){
        vertex* f = q.front();
        q.pop();
        for (int i = 0; i < f->adj.size(); ++i){
            if (!visited[f->adj[i]->num]){
                visited[f->adj[i]->num] = true;
                q.push(f->adj[i]);
            }
            if(!f->color){
                f->adj[i]->color = true;
                blue[f->adj[i]->num] = true;
                if(f->adj[i]->num > lastblue)
                    lastblue = f->adj[i]->num;
            }
            if(f->color == true && f->adj[i]->color == true){
                ofs << -1 << endl;
                for (int i = 0; i < vertices.size(); ++i){
                    delete vertices[i];
                }
                return;
            }
        }
    }

    for (int i = 0; i < vertices.size(); ++i)
    {
        if(i == lastblue)
            break;
        if (blue[i]==true){
            ofs << i << ",";
        }
    }
    ofs << lastblue<<endl;

    for (int i = 0; i < vertices.size(); ++i){
        delete vertices[i];
    }
    
    vertices.clear();
}


int main(){
    ifstream ifs("input.txt");
    ofstream ofs("output.txt");
    int edgenum;
    while (ifs >> edgenum){
        // cout << edgenum << endl;
        for (int i = 0; i < edgenum; i++){
            int n1, n2;
            ifs >> n1 >> n2;
            // cout << n1 << " " << n2<<endl;
            add(n1, n2);
        }

        int index;
        vertex *src;
        for (int i = 0; i < vertices.size(); i++){
            if(vertices[i]->num == 0){
                index = i;
                src = vertices[i];
            }
        }
        BFS(src, index, ofs);
        // for (int i = 0; i < vertices.size(); i++){
        //     cout << "vertices " << i << " : " << vertices[i]->num << endl;
        //     for (int j = 0; j < vertices[i]->adj.size(); j++){
        //         cout << "adj " << j << " : " << vertices[i]->adj[j]->num << endl;
        //     }
        // }
    }
    return 0;
}