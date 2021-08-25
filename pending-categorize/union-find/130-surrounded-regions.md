## 130. 被围绕的区域

### 题目

https://leetcode-cn.com/problems/surrounded-regions/

### 思路1：并查集 

1. 增加一个dummy 节点 标记 那些不会变成 'X'的节点，可以使用并查集 与 dummy 连接。最后判断那些'O'没有连接。

2. 将二维数组转换为一维数组：(x,y) 可以转换成 x * n + y，
其中 m 是行数，n 是列数

```Java
class UF{
    int[] parent;
    int[] size;

    UF(int n){
        parent = new int[n];
        size = new int[n];
        for(int i = 0; i < n; i++){
            parent[i] = i;
            size[i] = 1;
        }
    }

    int find(int x) {
        while(x != parent[x]){
            //压缩
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    void union(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if(rootX == rootY) return;
        if(size[rootX] > size[rootY]){
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        } else {
            parent[rootX] = rootY;
            size[rootY] += size[rootX];
        }
        return;
    }

    boolean connected(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        return rootX == rootY;
    }
}

class Solution {
    public void solve(char[][] board) {
        int m = board.length;
        int n = board[0].length;
        //额外增加一个dummy节点连通不会变成'O'的节点
        int dummy = m * n;
        UF uf = new UF(dummy + 1);
        //1.将首列和末列'O'与dummy连接
        for(int i = 0; i < m; i++){
            if(board[i][0] == 'O'){
                uf.union(i * n, dummy);
            }
            if(board[i][n - 1] == 'O'){
                uf.union(i * n + n - 1, dummy);
            }
        }

        //2.将首行和末行'O'与dummy连接
        for(int j = 0; j < n; j++){
            if(board[0][j] == 'O'){
                uf.union(j, dummy);
            }
            if(board[m - 1][j] == 'O'){
                uf.union((m - 1) * n + j, dummy);
            }
        }

        //3.将与边界'O'相邻的'O'连接
        int[][] d = new int[][]{{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
        for(int i = 1; i < m - 1; i++){
            for(int j = 1; j < n - 1; j++){
                if(board[i][j] == 'O'){
                    for(int k = 0; k < 4; k++){
                        int x = i + d[k][0];
                        int y = j + d[k][1];
                        if(board[x][y] == 'O'){
                            uf.union(i * n + j, x * n + y);
                        }
                    }
                }
            }
        }

        //4. 将所有没有跟dummy 相通的 'O' 置为 'X'
        for(int i = 1; i < m - 1; i++){
            for(int j = 1; j < n - 1; j++){
                if(board[i][j] == 'O'){
                    if(!uf.connected(i * n + j, dummy)){
                        board[i][j] = 'X';
                    }
                }
            }
        }
    }
}
```

**复杂度分析**

时间复杂度：O(mn)
空间复杂度：O(mn)


### 思路2：DFS

先用 for 循环遍历棋盘的四边，用 DFS 算法把那些与边界相连的 O 换成一个特殊字符，比如 #；然后再遍历整个棋盘，把剩下的 O 换成 X，把 # 恢复成 O。这样就能完成题目的要求，时间复杂度 O(MN)。