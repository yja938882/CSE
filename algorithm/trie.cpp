#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int ELEMENT_NUM = 'z'-'a'+1;

struct Node{
    struct Node * children[ELEMENT_NUM];
    bool isLeaf;
};

/*
    @brief : return new Node
 */
struct Node* makeNode(void){
    struct Node* node = new struct Node;
    node->isLeaf = false;
    for(int i=0;i<ELEMENT_NUM;i++) node->children[i] = NULL;
    return node;
}

/*
    @breif :if not exist, insert into trie
 */
void insert(struct Node *root, string key){
    struct Node *curNode = root;
    for(int i=0;i<key.length();i++){
        if(curNode->children[key[i] -'a'] ==NULL )
            curNode->children[key[i]-'a']= makeNode();
        curNode = curNode->children[key[i] -'a'];
    }
    curNode->isLeaf = true;
}

/*
    @breif : return true if key exists
 */
bool find(struct Node *root, string key){
    struct Node *curNode = root;
    for(int i=0;i<key.length();i++){
        if(curNode->children[key[i] -'a']==NULL)
            return false;
        curNode = curNode->children[key[i] -'a'];
    }
    return curNode!=NULL && curNode->isLeaf;
}

int main(){
    struct Node *root = makeNode();
    vector<string> inputs;
    int N;
    cout<<"input num : ";
    cin>>N;
    cout<<"input string :\n";
    for(int i=0;i<N;i++){
        string in;
        cin>>in;
        inputs.push_back(in);
    }
    
    for(int i=0;i<N;i++){
        insert(root,inputs[i]);
    }
    
    cout<<"find string : ";
    string fs;
    cin>>fs;
    if(find(root,fs))cout<<"find!\n";
    else cout<<"not exists\n";
}
