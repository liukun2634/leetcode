## 并查集


[Java rank](./UnionFindRank.java)

[C++ rank](./union_find_rank.cpp)

1、用 parent 数组记录每个节点的父节点，相当于指向父节点的指针，所以 parent 数组内实际存储着一个森林（若干棵多叉树）。
2、用 size 数组记录着每棵树的重量，目的是让 union 后树依然拥有平衡性，而不会退化成链表，影响操作效率。

3、在 find 函数中进行路径压缩，保证任意树的高度保持在常数，使得 union 和 connected 时间复杂度为 O(1)。

### 连通性

这里所说的「连通」是一种等价关系，也就是说具有如下三个性质：
1、自反性：节点 p 和 p 是连通的。
2、对称性：如果节点 p 和 q 连通，那么 q 和 p 也连通。
3、传递性：如果节点 p 和 q 连通，q 和 r 连通，那么 p 和 r 也连通。

判断这种「等价关系」非常实用，比如说编译器判断同一个变量的不同引用，比如社交网络中的朋友圈计算等等。

### 模板

增加了union "重量" 和 find 压缩

关键 
1. parent 和 size
2. 构造函数
3. int find(int x)
4. void union(int x, int y)
5. boolean connected(int x, int y)

```java
class UF{
    int[] parent;
    int[] size;

    UF(int n){
        parent = new int[n];
        size = new int[n];
        for(int i = 0; i < n; i++){
            parent[i] = i;
            size[i] = 0;
        }
    }

    int find() {
        while(x != parent[x]){
            //压缩
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    void union() {
        int rootX = find(x);
        int rootY = find(y);
        if(rootX == rootY) return;
        //重量判断，小的接到大的上
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
        return find(x) == find(y);
    }
}
```

### 运用

关键要看抽象能力，

主要思路是适时增加虚拟节点，想办法让元素「分门别类」，建立动态连通关系。