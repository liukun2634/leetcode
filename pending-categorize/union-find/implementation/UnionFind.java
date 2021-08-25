package implementation;
public class UnionFind{
    //记录连通分量
    private int count; 
    //x 的父节点是 parent[x]
    private int[] parent;

    //构造函数
    public UnionFind(int n) {
        count = n;

        parent = new int[n];
        for(int i = 0; i < n; i++){
            parent[i] = i;
        }
    }

    public int find(int x){
        while(parent[x] != x) {
            x = parent[x];
        }
        return x;
    }

    public void union(int x, int y){
        int rootX = find(x);
        int rootY = find(y);
        if(rootX == rootY) {
            return;
        }
        parent[rootX] = rootY;
        count--;
    }

    public boolean connected(int x, int y){
        int rootX = find(x);
        int rootY = find(y);
        return rootX == rootY;
    }

    public int count(){
        return count;
    }

    public static void main(String[] args) {
        UnionFind uf = new UnionFind(10);
        uf.union(3, 4);
        uf.union(5, 6);
        System.out.println(uf.connected(3, 4));
        System.out.println(uf.count());
    }
}