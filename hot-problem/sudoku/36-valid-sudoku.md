## 36. 有效的数独

### 题目

https://leetcode-cn.com/problems/valid-sudoku/

### 思路1：哈希表 

用哈希表存储当前行，列，3*3空格内数字出现情况。

这里使用二维数组代替哈希表。哈希表也可以用string 组合作为key实现二维。

```C++
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int n = 9;
        vector<vector<bool>> col(n, vector<bool>(10, false));
        vector<vector<bool>> row(n, vector<bool>(10, false));
        vector<vector<bool>> box(n, vector<bool>(10, false));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(board[i][j] != '.'){
                    int num = board[i][j] - '0';
                    if(row[i][num]) return false;
                    if(col[j][num]) return false;
                    if(box[(i/3)*3 + j / 3][num]) return false;
                    col[j][num] = true;
                    row[i][num] = true;
                    box[(i/3)*3 + j / 3][num] = true;
                }
            }
        }
        return true;
    }
};
```

**复杂度分析**

时间复杂度：
空间复杂度：