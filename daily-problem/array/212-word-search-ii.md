## 212. 单词搜索 II

### 题目

https://leetcode-cn.com/problems/word-search-ii/

### 思路： 回溯 + 字典树


字典树用于剪枝，记住字典树的Node 结构（children[26], isEnd)， 三个方法（insert，search，startWith)， 和遍历过程中(p = p ->chirdren[c - 'a'])。

回溯就是标准回溯模板。

```C++
struct TrieNode{
    TrieNode* children[26];
    int isEnd = false;
};

class Trie{
private:
    TrieNode* root;

public:
    Trie(){
        root = new TrieNode();
    }

    void insert(string word){
        TrieNode* p = root;
        for(char c : word){
            if(p -> children[c - 'a'] == nullptr){
                p -> children[c - 'a'] = new TrieNode();
            }
            p = p -> children[c - 'a'];
        }
        p->isEnd = true;
    }

    bool search(string word){
        TrieNode* p = root;
        for(char c : word){
            if(p -> children[c - 'a'] == nullptr){
                return false;
            }
            p = p -> children[c - 'a'];
        }
        return p->isEnd;
    }

    bool startWith(string prefix){
        TrieNode* p = root;
        for(char c : prefix){
            if(p -> children[c - 'a'] == nullptr){
                return false;
            }
            p = p -> children[c - 'a'];
        }
        return true;
    }
};

class Solution {
public:
    unordered_set<string> set;
    vector<string> res;
    Trie dictionary;
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        for(string& word : words){
            dictionary.insert(word);
        }

        int n = board.size(), m = board[0].size();
        
        vector<vector<bool>> visited(n, vector<bool>(m));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                string path;
                backtrace(board, i, j, visited, path);
            }
        }
        return res;
    }

    vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    void backtrace(vector<vector<char>>& board, int i, int j, vector<vector<bool>>& visited, string& path){
        int n = board.size(), m = board[0].size();
        //返回条件
        if(i >= n|| i < 0 || j < 0 || j >= m || visited[i][j]) return;

        //当前值处理
        path.push_back(board[i][j]);
        visited[i][j] = true;

        //额外去重
        if(dictionary.search(path) && !set.count(path)) {
            res.push_back(path);
            set.emplace(path);
        }

        if(dictionary.startWith(path)){
            for(auto& direction : directions){
                int x = i + direction[0];
                int y = j + direction[1];
                backtrace(board, x, y, visited, path);
            }
        }
        visited[i][j] = false;
        path.pop_back();
        
    }
};
```

优化：

1. 为避免去重，可以将匹配到的单词从前缀树中移除。（这一招在哈希表用于求三数之和中用到）

2. 可以把字典树递归和回溯算法结合起来，这样只用实现insert方法，不需要search 和 startwith 

```C++
struct TrieNode{
    TrieNode* children[26];
    int isEnd = false;
};

class Trie{
public:
    TrieNode* root = new TrieNode();
    void insert(string word){
        TrieNode* p = root;
        for(char c : word){
            if(p -> children[c - 'a'] == nullptr){
                p -> children[c - 'a'] = new TrieNode();
            }
            p = p -> children[c - 'a'];
        }
        p->isEnd = true;
    }
};

class Solution {
public:
    vector<string> res;
    Trie dictionary;
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        for(string& word : words){
            dictionary.insert(word);
        }

        int n = board.size(), m = board[0].size();
        
        vector<vector<bool>> visited(n, vector<bool>(m));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                string path;
                backtrace(board, i, j, visited, path, dictionary.root);
            }
        }
        return res;
    }

    vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    void backtrace(vector<vector<char>>& board, int i, int j, vector<vector<bool>>& visited, string& path, TrieNode* p){
        int n = board.size(), m = board[0].size();
        //返回条件
        if(i >= n|| i < 0 || j < 0 || j >= m || visited[i][j] || p -> children[board[i][j] - 'a'] == nullptr) return;

        //当前值处理
        path.push_back(board[i][j]);
        visited[i][j] = true;
        TrieNode* cur = p -> children[board[i][j] - 'a'];
        
        if(cur -> isEnd == true) {
            //删除字典树，即可去重
            res.push_back(path);
            cur -> isEnd = false;
        }

       
        for(auto& direction : directions){
            int x = i + direction[0];
            int y = j + direction[1];
            backtrace(board, x, y, visited, path, cur);
        }
        visited[i][j] = false;
        path.pop_back();    
    }
};
```


**复杂度分析**

时间复杂度：
空间复杂度：