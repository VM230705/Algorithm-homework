#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Node
{
    string key;
    string value;
    Node *left;
    Node *right;
};

Node* newNode(string key, string value){
    Node *node = new Node();
    node->key = key;
    node->value = value;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}


Node* Find(Node* root, string key){
    if(root == nullptr){
        return root;
    }
    Node *cur = root;
    while (cur!=nullptr && cur->key!=key){
        //cout << cur->key << endl;
        if (cur->key.compare(key)>0){
            //cout << ">0" << endl;
            cur = cur->left;
        }
        else{
            //cout << "<0" << endl;
            cur = cur->right;
        }
    }
    if (cur == nullptr){
        return root;
    }
    else{
        return cur;
    }
}

Node* Insert(Node* root, string key, string value ,int& count, ofstream& ofs){
    if(root == nullptr){
        cout << "INSERT " << key << " SUCCESS!" << endl;
        ofs << "INSERT " << key << " SUCCESS!" << endl;
        count++;
        return newNode(key, value);
    }
    Node *node = Find(root, key);
    if(node->key == key|| count >300000){  
        cout << "INSERT " << key << " FAIL!" << endl;
        ofs << "INSERT " << key << " FAIL!" << endl;
        return root;
    }
    if (root->key.compare(key)<0){
        root->right = Insert(root->right, key, value, count, ofs);
    }
    else{
        root->left = Insert(root->left, key, value, count, ofs);
    }

    return root;
}

Node* minValueNode(Node* node)
{
    Node* cur = node;
    /* loop down to find the leftmost leaf */
    while (cur != nullptr&& cur->left != nullptr)
        cur = cur->left;

    return cur;
}

Node* maxValueNode(Node* node)
{
    Node* cur = node;
    /* loop down to find the leftmost leaf */
    while (cur != nullptr&& cur->right != nullptr)
        cur = cur->right;

    return cur;
}

Node* Erase(Node* root, string key, int& count, ofstream& ofs){
    if(root == nullptr){
        cout << "ERASE " << key << " FAIL!" << endl;
        ofs << "ERASE " << key << " FAIL!" << endl;
    }

    Node *node = Find(root, key);
    if(node->key!=key){
        cout << "ERASE " << key << " FAIL!" << endl;
        ofs << "ERASE " << key << " FAIL!" << endl;
        return root;
    }

    if (root->key.compare(key)>0)
        root->left = Erase(root->left, key, count, ofs);
    else if (root->key.compare(key)<0)
        root->right = Erase(root->right, key, count, ofs);
    else {
        if(root->key!=key){
            cout << "ERASE " << key << " FAIL!" << endl;
            ofs << "ERASE " << key << " FAIL!" << endl;
            return root;
        }
        // node has no child
        if (root->left==nullptr && root->right==nullptr){
            cout << "ERASE " << key << " SUCCESS!" << endl;
            ofs << "ERASE " << key << " SUCCESS!" << endl;
            return nullptr;
        }
        // node with only one child or no child
        else if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            cout << "ERASE " << key << " SUCCESS!" << endl;
            ofs << "ERASE " << key << " SUCCESS!" << endl;
            return temp;
        }
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            cout << "ERASE " << key << " SUCCESS!" << endl;
            ofs << "ERASE " << key << " SUCCESS!" << endl;
            return temp;
        }
        // node with two children: Get the inorder successor
        // (smallest in the right subtree)
        Node* temp = minValueNode(root->right);
        // Copy the inorder successor's content to this node
        root->key = temp->key;
        root->value = temp->value;
        // Delete the inorder successor
        root->right = Erase(root->right, temp->key, count, ofs);
    }
    return root;
}

void inOrder(Node* root, string key1, string key2, ofstream& ofs){
    if (root == nullptr)
        return;

    Node *n1 = Find(root, key1);
    Node *n2 = Find(root, key2);
    if(n1->key!=key1)
        key1 = minValueNode(root)->key;
    if(n2->key!=key2)
        key2 = maxValueNode(root)->key;
    
    if (root != nullptr){
        inOrder(root->left, key1, key2, ofs);
        //key1 <= (root->key) <= key2
        if (key1.compare(root->key)<=0 && key2.compare(root->key)>=0){
            cout << "ENUM " << root->key << ":" << root->value << "!" << endl;
            ofs << "ENUM " << root->key << ":" << root->value << "!" << endl;
        }
        inOrder(root->right, key1, key2, ofs);
    }
}

Node* clear(Node* root){
    if(root == nullptr)
        return root;
    clear(root->left);
    clear(root->right);
    delete root;
    root = nullptr;
    return root;
}

int main(){
    ifstream ifs("input.txt");
    ofstream ofs("output.txt");
    if(!ifs.is_open()){
        cout << "file not open" << endl;
        exit(1);
    }

    int count = 0;
    string cmd;
    Node *root = nullptr;
    while (ifs >> cmd)
    {
        //cout << "cmd  = " << cmd << endl;
        //cout << count << endl;
        if(cmd=="CLEAR"){
            root = clear(root);
            count = 0;
            continue;
        }
        string key;
        ifs >> key;
        size_t pos = key.find(":");
        key = key.substr(pos + 1);
        if(cmd == "INSERT"){
            string value;
            ifs  >> value;
            size_t pos2 = value.find(":");
            value = value.substr(pos2+1);
            root = Insert(root, key, value, count, ofs);
            //cout << "root = " << root->key << " " << root->value << endl;
        }
        else if (cmd == "FIND"){
            root = Find(root, key);
            if(root->key!=key){
                cout << key << " NOT FOUND!" << endl;
                ofs << key << " NOT FOUND!" << endl;
            }
            else{
                cout << "FIND " << root->key << ":" << root->value << endl;
                ofs << "FIND " << root->key << ":" << root->value << endl;
            }
        }
        else if (cmd == "ERASE"){
            root = Erase(root, key, count, ofs);
        }
        else if (cmd == "ENUM"){
            string  key2;
            ifs >> key2;
            size_t pos2 = key2.find(":");
            key2 = key2.substr(pos2+1);
            inOrder(root, key, key2, ofs);
        }
    }
    return 0;
}