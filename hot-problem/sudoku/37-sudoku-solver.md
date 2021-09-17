## 37. 解数独

### 题目

https://leetcode-cn.com/problems/sudoku-solver/

### 思路：回溯

标准回溯，需要额外一个判断valid 的函数

```C++
class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        backtrack(board, 0, 0);
    }

     bool backtrack(vector<vector<char>>& board, int x, int y){
        //寻找下一个位置
        int n = board.size(), m = board[0].size();
        auto [i, j] = findNext(board, x, y);

        //返回条件： 全部填完
        if(i == n && j == m) return true;

        //填入当前节点，递归下一个节点
        for(int k = 1; k <= 9; k++){
            board[i][j] = '0' + k;
            if(validate(board, i, j)) {
                if(backtrack(board, i , j)){
                    return true;
                }
            }
        }
        //最后置为'.'清空
        board[i][j] = '.';
        return false;
    }

    pair<int, int> findNext(vector<vector<char>>& board, int x, int y){
        int n = board.size(), m = board[0].size();
        int j = y;
        for(int i = x; i < n; i++){
            for(; j < m; j++){
                if(board[i][j] == '.'){
                    return {i, j};
                }
            }
            j = 0;
        }
        return {n, m};
    }

    bool validate(vector<vector<char>>& board, int x, int y){
        int n = board.size(), m = board[0].size();

        vector<bool> used(10, false);
        for(int i = 0; i < n; i++){
            if(board[i][y] == '.') continue;
            if(used[board[i][y] - '0']) return false;
            used[board[i][y] - '0'] = true;
        }

        vector<bool> used1(10, false);
        for(int j = 0; j < m; j++){
             if(board[x][j] == '.') continue;
             if(used1[board[x][j] - '0']) return false;
             used1[board[x][j] - '0'] = true;
        }

        //注意是9个框
        vector<bool> used2(10, false);
        for (int k = 0; k < n; k++){
            int i = (x/3)*3 + k/3;
            int j = (y/3)*3 + k%3;
            if(board[i][j] == '.') continue;
            if(used2[board[i][j] - '0']) return false;
            used2[board[i][j] - '0'] = true;
        }
        return true;
    }
};
```

**复杂度分析**

时间复杂度：
空间复杂度：