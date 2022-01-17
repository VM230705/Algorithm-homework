#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int count = 0;
ofstream ofs("output.txt");
struct Node
{
    string key;
    string value;
    Node *left;
    Node *right;
};

Node* newNode(string& key, string& value){
    Node *node = new Node();
    node->key = key;
    node->value = value;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

Node* rightRotate(Node* x){
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

Node* leftRotate(Node* x){
    Node *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

Node* splay(Node* root, string& key){
    if(root==nullptr || root->key == key)
        return root;
    //root->key > key means key is in left subtree
    if (root->key>key){
        if (root->left == nullptr) return root;
        //Zig-Zig(Left-Left)
        if(root->left->key>key){
            // First recursively bring the
            // key as root of left-left
            root->left->left = splay(root->left->left, key);

            // first rotate; second rotate is after else
            root = rightRotate(root);
        }
        else if(root->left->key<key){ //Zig-Zag (Left Right)
            // First recursively bring
            // the key as root of left-right
            root->left->right = splay(root->left->right, key);

            // Do first rotation for root->left
            if (root->left->right != nullptr)
                root->left = leftRotate(root->left);
        }

        // Do second rotation for root 
        //if root->left==nullptr return root ,else return rightrotate(root)
        return (root->left == nullptr) ? root : rightRotate(root);
    }
    else{//key lies in right subtree
        if (root->right == nullptr) return root;

        // Zig-Zag (Right Left)
        if(root->right->key>key){
            // Bring the key as root of right-left
            root->right->left = splay(root->right->left, key);
            
            //Do the first rotation
            if(root->right->left!=nullptr)
                root->right = rightRotate(root->right);
        }
        else if(root->right->key< key){ // Zag-Zag (Right Right)
            // Bring the key as root of
            // right-right and do first rotation
            root->right->right = splay(root->right->right, key);
            
            // first rotate; second rotate is after else
            root = leftRotate(root);
        }
         // Do second rotation for root
        return (root->right == nullptr) ? root : leftRotate(root);
    }
}

Node* Insert(Node* root, string& key, string& value){
    if(root == nullptr){
        ofs << "INSERT " << key << " SUCCESS!" << endl;
        //cout << "INSERT " << key << " SUCCESS!" << endl;
        count++;
        return newNode(key, value);
    }
    //Bring the closest leaf node to root
    root = splay(root, key);

    //key is already in tree or input exceed 300000
    if(root->key == key || count >300000){  
        ofs << "INSERT " << key << " FAIL!" << endl;
       //cout << "INSERT " << key << " FAIL!" << endl;
        return root;
    }
    //create
    Node *node = newNode(key, value);
    
    //key is smaller than root's key
    //make root's key be the key's right child
    if(root->key>key){
        node->right = root;
        node->left = root->left;
        root->left = nullptr;
    }
    // key is greater than root's key
    //make root's key be the key's left child
    else{
        node->left = root;
        node->right = root->right;
        root->right = nullptr;
    }
    ofs << "INSERT " << key << " SUCCESS!" << endl;
    //cout << "INSERT " << key << " SUCCESS!" << endl;
    count++;
    return node; // new node become root of tree
}

Node* Find(Node* root, string& key){
    if(root == nullptr){
        ofs << key << " NOT FOUND!" << endl;
        //cout << key << " NOT FOUND!" << endl;
        return root;
    }
    //bring the closest node to root
    root = splay(root, key);

    if(root->key == key){
        ofs << "FIND " << root->key << ":" << root->value <<"!"<< endl;
        //cout << "FIND " << root->key << ":" << root->value <<"!"<< endl;
    }
    else{
        ofs << key << " NOT FOUND!" << endl;
        //cout << key << " NOT FOUND!" << endl;
    }
    return root;
}

Node* Erase(Node* root, string& key){
    if(root == nullptr){
        ofs << "ERASE " << key << " FAIL!" << endl;
        //cout << "ERASE " << key << " FAIL!" << endl;
        return root;
    }

    // bring the closest node to root
    root = splay(root, key);

    if (root->key != key){
        ofs << "ERASE " << key << " FAIL!" << endl;
        //cout << "ERASE " << key << " FAIL!" << endl;
        return root;
    }

    Node *temp;
    //root->left DNE
    if (root->left == nullptr){
        temp = root;
        root = root->right;
    }
    else{//root->left exist
        temp = root;

        //make the max node be the new root
        root = splay(root->left, key);

        //temp->right is the original right subtree
        root->right = temp->right;
    }
    delete temp;
    ofs << "ERASE " << key << " SUCCESS!" << endl;
    // cout << "ERASE " << key << " SUCCESS!" << endl;
    count--;
    return root;
}

void inOrder(Node* root, string& key1, string& key2){
    if(root == nullptr)
        return;
    if(key1 < root->key){
        inOrder(root->left, key1, key2);
    }
    if (key1 < root->key && root->key <= key2){
        ofs << "ENUM " << root->key << ":" << root->value << endl;
        //cout << "ENUM " << root->key << ":" << root->value << endl;    
    }
    if(key2 > root->key){
        inOrder(root->right, key1, key2);
    }
    
    // if (root != nullptr){
    //     inOrder(root->left, key1, key2);
    //     //key1 <= (root->key) <= key2
    //     if (key1.compare(root->key)<=0 && key2.compare(root->key)>=0){
    //         ofs << "ENUM " << root->key << ":" << root->value << endl;
    //         //cout << "ENUM " << root->key << ":" << root->value << endl;    
    //     }
    //     inOrder(root->right, key1, key2);
    //     //cout << root->key << endl;
    // }
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
    string cmd;
    Node *root = nullptr;
    while (ifs >> cmd)
    {
        //cout << "cmd  = " << cmd << endl;
        // cout << count << endl;
        if(cmd=="CLEAR"){
            root = clear(root);
            count = 0;
            continue;
        }
        string key;
        ifs >> key;
        key.erase(0, 4);
        if(cmd == "INSERT"){
            string value;
            ifs  >> value;
            value.erase(0, 6);
            root = Insert(root, key, value);
        }
        else if (cmd == "FIND"){
            root = Find(root, key);
        }
        else if (cmd == "ERASE"){
            root = Erase(root, key);
        }
        else if (cmd == "ENUM"){
            string  key2;
            ifs >> key2;
            key2.erase(0, 4);
            inOrder(root, key, key2);
        }
    }
    return 0;
}