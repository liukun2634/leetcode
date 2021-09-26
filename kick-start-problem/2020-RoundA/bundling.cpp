#include<iostream>
#include<vector>
#include<string>
using namespace std;

int N, K;

struct TrieNode{
    TrieNode* next[26];
    int count;
    bool isEnd;

    TrieNode(){
        //need intialize or use vector
        for(int i = 0; i < 26; i++){
            next[i] = nullptr;
        }
        count = 0;
        isEnd = false;
    }
};
    
void insert(TrieNode* root, string word){
    TrieNode* p = root;
    for(char c : word){
        if(p -> next[c - 'A'] == nullptr){
            p -> next[c - 'A'] = new TrieNode();
        }
        p = p -> next[c - 'A'];
        p -> count = p -> count + 1;
    }
    p -> isEnd = true;
}


void count(TrieNode* root, int level, int& res){
    if(root == nullptr) return;
    //this is important
    //To calculate each prefix contribute to last result
    res += (root -> count) / K;
    for(int i = 0; i < 26; i++){
        count(root->next[i], level + 1, res);
    }
}

int solve(vector<string>& words){
    TrieNode* root = new TrieNode();
    root->count = 0;
    for(string word : words){
        insert(root, word);
    }
    int res = 0;
    count(root, 0, res);
    return res;
}


int main(){
    int T;
    cin>>T;
    for(int t = 1; t <= T; t++){
        cin>>N>>K;
        vector<string> words(N);
        for(int i = 0; i < N; i++){
            cin>>words[i];
        }
        cout<<"Case #"<<t<<": "<<solve(words)<<endl;
    }
    return 0;
}
