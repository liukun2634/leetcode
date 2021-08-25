#include <iostream>
#include <vector>
using namespace std;
class UF {
private:    
    // 连通分量个数
    int count;
    // 存储一棵树
    vector<int> parent;
    // 记录树的“重量”
    vector<int> size;

public:
    UF(int n) {
        count = n;
        parent.resize(n);
        size.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }
    
    //函数名union 改为 merge
    void merge(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP == rootQ)
            return;
        
        // 小树接到大树下面，较平衡
        if (size[rootP] > size[rootQ]) {
            parent[rootQ] = rootP;
            size[rootP] += size[rootQ];
        } else {
            parent[rootP] = rootQ;
            size[rootQ] += size[rootP];
        }
        count--;
    }

    bool connected(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);
        return rootP == rootQ;
    }

    int find(int x) {
        while (parent[x] != x) {
            // 进行路径压缩
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    int getcount() {
        return count;
    }
};

int main()
{
    UF uf(10);
    uf.merge(3, 4);
    uf.merge(1, 2);
    uf.merge(3, 7);
    uf.merge(2, 1);
    uf.merge(2, 9);
    uf.merge(1, 0);

    cout<<uf.connected(3, 4)<<endl;

    cout<<uf.getcount()<<endl;
}