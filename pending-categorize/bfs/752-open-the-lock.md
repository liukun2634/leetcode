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