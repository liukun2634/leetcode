#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(nullptr),right(nullptr){}
};

int start = 0;
TreeNode* deseralize(vector<string> nodes){
    if(nodes[start] == "#"){
        start++;
        return nullptr;
    }

   TreeNode* p = new TreeNode(stoi(nodes[start++]));
   p -> left = deseralize(nodes);
   p -> right = deseralize(nodes);
   return p;
}

void preorder(TreeNode* p){
   if(p == nullptr) return;
   cout<<p -> val;
   preorder(p->left);
   preorder(p->right);
}

int main(){
    string s;
    getline(cin, s);
    
    vector<string> nodes;
    string str;
    for(char c : s){
        if(c == ','){
            nodes.push_back(str);
            str.clear();
        } else {
            str.push_back(c);
        }
    }
    if(!str.empty()){
        nodes.push_back(str);
        str.clear();
    }

    TreeNode* root = deseralize(nodes);
    preorder(root);

}

