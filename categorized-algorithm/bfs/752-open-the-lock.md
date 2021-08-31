## 752. 打开转盘锁

### 题目

https://leetcode-cn.com/problems/open-the-lock/

### 思路1： 朴素BFS

标准BFS模板求最短距离。

注意：
- 利用额外哈希集合存储deadends，能够迅速找到
- 这里因为可以返回之前的位置，所以需要增加visited，这里因为标记string，直接用set保存。

```C++
class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        unordered_set<string> deadset;
        for(string s : deadends){
            deadset.emplace(s);
        }
        //"0000" 特殊处理
        if(deadset.count("0000")) return -1;

        //1.定义结构
        queue<pair<string, int>> q;
        unordered_set<string> visited;
        //2.压入起点
        q.push({"0000", 0});
        visited.emplace("0000");
        //3.搜索
        while(!q.empty()){
            int sz = q.size();
            //4.通过size，遍历队列中该层的所有值
            for(int i = 0; i < sz; i++){
                //5.出列
                auto[cur, step] = q.front();
                q.pop();
                //6. 满足要求
                if(cur == target) return step;
                //7. 压入相邻值
                vector<string> nexts = generateNext(cur);
                for(string next : nexts){
                    if(!deadset.count(next) && !visited.count(next)) {
                        q.push({next, step + 1});
                        visited.emplace(next);
                    }
                }
            }
        }
        return -1;
    }

    vector<string> generateNext(string cur){
        vector<string> res;
        for(int i = 0; i < 4; i++){
            string temp = cur;
            if(cur[i] == '0') {
                temp[i] = '9';
                res.push_back(temp);
                temp[i] = '1';
                res.push_back(temp);
            } else if (cur[i] == '9'){
                temp[i] = '0';
                res.push_back(temp);
                temp[i] = '8';
                res.push_back(temp);
            } else {
                temp[i] = cur[i] - 1;
                res.push_back(temp);
                temp[i] = cur[i] + 1;
                res.push_back(temp);
            }
        }
        return res;
    }
};
```

部分代码可以优化：
- unodered_set 可以直接用vector初始化 ` unordered_set<string> dead(deadends.begin(), deadends.end())`
- generateNext

- 可以不需要 dead 这个哈希集合，可以直接将这些元素初始化到 visited 集合中


**复杂度分析**

时间复杂度：O(b^d*d^2+m*d)，其中 b 是数字的进制，d 是转盘数字的位数，m 是数组deadends 的长度，在本题中 b=10，d=4。

空间复杂度：O(b^d*d+m)


### 思路2： 双向BFS

参考： https://leetcode-cn.com/problems/open-the-lock/solution/gong-shui-san-xie-yi-ti-shuang-jie-shuan-wyr9/

两个队列，一个从起点出发，一个从终点出发。

两个队列还需要分别增加一个`hashmap<key, value>` ，一方面可以判断是否存在于已访问的集合中，同时又能快速拿到该节点需要走过的步数。但可以省去visited了，因为map可以记录该信息。

要点：

1、 创建「两个队列」分别用于两个方向的搜索；
2、 创建「两个哈希表」用于「解决相同节点重复搜索」和「记录转换次数」；
3、 为了尽可能让两个搜索方向“平均”，每次从队列中取值进行扩展时，先判断哪个队列容量较少；
4、 如果在搜索过程中「搜索到对方搜索过的节点」，说明找到了最短路径。

```C++
class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        unordered_set<string> deadset(deadends.begin(), deadends.end());
        //"0000" 特殊处理
        if(deadset.count("0000")) return -1;

        //1.定义双向BFS
        //多增加一个map存储访问过的节点和步骤
        queue<string> q1;
        queue<string> q2;
        unordered_map<string, int> m1;
        unordered_map<string, int> m2;
        
        //2.压入起点和终点
        q1.push("0000");
        q2.push(target);
        m1.emplace("0000", 0);
        m2.emplace(target, 0);

        //3.搜索
        while(!q1.empty() && !q2.empty()){
           int step = -1;
           if(q1.size() < q2.size()){
               step = bfs(q1, m1, m2, deadset);
           } else {
               step = bfs(q2, m2, m1, deadset);
           } 
           if(step != -1) return step;
        }
        return -1;
    }

    //通过函数，q1 和 q2 能分别调用
    int bfs(queue<string>& q, unordered_map<string, int>& m, unordered_map<string, int>& other, unordered_set<string>& deadset){
        //4. 该层的数目
        int sz = q.size();
        for(int i = 0; i < sz; i++){
            //5.出列
            string cur = q.front();
            q.pop();
            int step = m[cur];
            //6. 到达另一边map中的节点，即可到达target(这步可以优化成在next时候判断，但要保证start ！= target)
            if(other.count(cur)) return step + other[cur];

            //7. 压入相邻值
            vector<string> nexts = generateNext(cur);
            for(string next : nexts){
                //判断是否访问过
                if(!deadset.count(next) && !m.count(next)) {
                    q.push(next);
                    m.emplace(next, step + 1);
                }
            }
        }
        return -1;
    }

    vector<string> generateNext(string cur){
        vector<string> res;
        for(int i = 0; i < 4; i++){
            string temp = cur;
            if(cur[i] == '0') {
                temp[i] = '9';
                res.push_back(temp);
                temp[i] = '1';
                res.push_back(temp);
            } else if (cur[i] == '9'){
                temp[i] = '0';
                res.push_back(temp);
                temp[i] = '8';
                res.push_back(temp);
            } else {
                temp[i] = cur[i] - 1;
                res.push_back(temp);
                temp[i] = cur[i] + 1;
                res.push_back(temp);
            }
        }
        return res;
    }
};
```