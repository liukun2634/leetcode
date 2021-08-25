## 990. 等式方程的可满足性

### 题目

https://leetcode-cn.com/problems/satisfiability-of-equality-equations/

### 思路：并查集

因为连通性判断，所以可以用并查集解决。

采用两次扫描方式，第一次根据相等，建立连通性。第二次根据不相等等式，判断是否正确。

```java
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
    public boolean equationsPossible(String[] equations) {
        UF uf = new UF(26);
        for(String equation : equations){
            if("==".equals(equation.substring(1, 3))){
                int x = equation.charAt(0) - 'a';
                int y = equation.charAt(3) - 'a';
                uf.union(x, y);
            }
        }

        for(String equation : equations){
            if("!=".equals(equation.substring(1, 3))){
                int x = equation.charAt(0) - 'a';
                int y = equation.charAt(3) - 'a';
                if(uf.connected(x, y)) return false;
            }
        }
        return true;
    }
}
```

**复杂度分析**

时间复杂度：
空间复杂度：