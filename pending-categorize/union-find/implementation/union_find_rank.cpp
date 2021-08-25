#include <iostream>
#include <vector>
using namespace std;

class UnionFindRank {
    //记录连通分量
    int count;
    //x 的父节点是 parent[x]
    vector<int> parent;
    //记录树的大小
    vector<int> size;

public:
    //构造函数
    UnionFindRank(int n)
    {
        count = n;
        parent.resize(n);
        size.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int find(int x)
    {
        while (parent[x] != x) {
            x = parent[x];
        }
        return x;
    }

    void union_vertex(int x, int y)
    {
        int root_x = find(x);
        int root_y = find(y);
        if (root_x == root_y) {
            return;
        }

        if (size[x] > size[y]) {
            parent[root_y] = x;
            size[x] += size[y];
        } else {
            parent[root_x] = y;
            size[y] += size[x];
        }
        count--;
    }

    bool connected(int x, int y)
    {
        int root_x = find(x);
        int root_y = find(y);
        return root_x == root_y;
    }

    int getCount()
    {
        return count;
    }
};

int main()
{
    UnionFindRank uf(10);
    uf.union_vertex(3, 4);
    uf.union_vertex(5, 6);
    cout<<uf.connected(3, 4)<<endl;
    cout<<uf.getCount()<<endl;
}