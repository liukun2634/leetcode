## 773. 滑动谜题

### 题目

https://leetcode-cn.com/problems/sliding-puzzle/

### 思路1： 朴素BFS



### 思路2： 双向BFS

标准双向BFS，三部分：
1. 准备部分
2. BFS 函数
3. 生成next 函数

```C++
class Solution {
public:
    int N = 2;
    int M = 3;
    int slidingPuzzle(vector<vector<int>>& board) {
        //将状态转换成string
        string target = "123450";
        string start(N * M, ' ');
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++){
                start[i * M + j] = '0' + board[i][j];
            }
        }

        //双向BFS
        queue<string> q1;
        queue<string> q2;
        unordered_map<string, int> m1;
        unordered_map<string, int> m2;

        //压入起点和终点
        q1.push(start);
        q2.push(target);
        m1.emplace(start, 0);
        m2.emplace(target, 0);

        //搜索
        while(!q1.empty() && !q2.empty()){
            int step = -1;
            if(q1.size() < q2.size()){
                step = bfs(q1, m1, m2);
            } else {
                step = bfs(q2, m2, m1);
            }
            if(step != -1) return step;
        }
        return -1;
    }

    int bfs(queue<string>& q, unordered_map<string, int>& m, unordered_map<string, int>& other){
        int sz = q.size();
        for(int i = 0; i < sz; i++){
            string cur = q.front();
            q.pop();
            int step = m[cur];

            //另一边找到该节点，可以返回结果
            //(这步可以优化成在next时候判断，但要保证start ！= target)
            if(other.count(cur)) return step + other[cur];

            vector<string> nexts = generateNext(cur);
            for(string next : nexts) {
                if(!m.count(next)){
                    //如果没访问过，入队同时更新map
                    q.push(next);
                    m.emplace(next, step + 1);
                }
            }
        }
        return -1;
    }

    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    vector<string> generateNext(string cur){
        int idx;
        for(idx = 0; idx < N * M; idx++){
            if(cur[idx] == '0') break; 
        }
        int x = idx / M;
        int y = idx % M;
        vector<string> res;
        for(auto direction : directions){
            int x1 = x + direction[0];
            int y1 = y + direction[1];
           
            if(x1 >= 0 && x1 < N && y1 >= 0 && y1 < M){
                string temp = cur;
                int idx1 = x1 * M + y1;
                swap(temp[idx], temp[idx1]);
                res.push_back(temp);
            }
        }
        return res;
    }
};
```

优化 (实际发现没有提升，反而内存下降了，因为增加了保存的信息)：

- 增加一个struct 存储状态和 0 的位置 (这个可以处理需要保存很多信息的情况)
- 在next 时候就判断是否满足条件，额外处理 target == start的情况

```cpp
struct Node{
    string state; //当前状态
    int x; //0的x，y坐标
    int y; 
    Node(string _state, int _x, int _y) {
        state = _state;
        x = _x;
        y = _y;
    }
};

class Solution {
public:
    int N = 2;
    int M = 3;
    int slidingPuzzle(vector<vector<int>>& board) {
        //将状态转换成string
        string target = "123450";
        string start(N * M, ' ');
        int x, y;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++){
                start[i * M + j] = '0' + board[i][j];
                if(board[i][j] == 0) {
                    x = i;
                    y = j;
                }
            }
        }

        //额外处理target == start 的情况
        if(target == start) return 0;

        //双向BFS
        queue<Node> q1;
        queue<Node> q2;
        unordered_map<string, int> m1;
        unordered_map<string, int> m2;

        //压入起点和终点
        q1.push(Node(start, x, y));
        q2.push(Node(target, N - 1 ,  M - 1));
        m1.emplace(start, 0);
        m2.emplace(target, 0);

        //搜索
        while(!q1.empty() && !q2.empty()){
            int step = -1;
            if(q1.size() < q2.size()){
                step = bfs(q1, m1, m2);
            } else {
                step = bfs(q2, m2, m1);
            }
            if(step != -1) return step;
        }
        return -1;
    }

    int bfs(queue<Node>& q, unordered_map<string, int>& m, unordered_map<string, int>& other){
        int sz = q.size();
        for(int i = 0; i < sz; i++){
            Node cur = q.front();
            q.pop();
            int step = m[cur.state];

            vector<Node> nexts = generateNext(cur);
            for(Node next : nexts) {
                //另一边存在next，可以返回结果
                if(other.count(next.state)) return step + 1 + other[next.state];
                
                //访问过则跳过
                if(m.count(next.state)) continue;

                //如果没访问过，入队同时更新map
                q.push(next);
                m.emplace(next.state, step + 1);
            }
        }
        return -1;
    }

    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    vector<Node> generateNext(Node cur){
        vector<Node> res;
        for(auto direction : directions){
            int x1 = cur.x + direction[0];
            int y1 = cur.y + direction[1];
           
            if(x1 >= 0 && x1 < N && y1 >= 0 && y1 < M){
                string temp = cur.state;
                int idx = cur.x * M + cur.y;
                int idx1 = x1 * M + y1;
                swap(temp[idx], temp[idx1]);
                res.push_back(Node(temp, x1, y1));
            }
        }
        return res;
    }
};
```


**复杂度分析**

时间复杂度：
空间复杂度：