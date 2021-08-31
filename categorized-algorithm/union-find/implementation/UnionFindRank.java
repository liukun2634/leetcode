package implementation;

public class UnionFindRank{
    //记录连通分量
    private int count; 
    //x 的父节点是 parent[x]
    private int[] parent;
    //记录树的大小
    private int[] size;

    //构造函数
    public UnionFindRank(int n) {
        count = n;

        parent = new int[n];
        size = new int[n];
        for(int i = 0; i < n; i++){
            parent[i] = i;
            size[i] = 1;
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

        //小树接在大树下面，更为平衡
        if(size[rootX] > size[rootY]) {
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        } else {
            parent[rootX] = rootY;
            size[rootY] += size[rootX];
        }
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
        UnionFindRank uf = new UnionFindRank(10);
        uf.union(3, 4);
        uf.union(5, 6);
        System.out.println(uf.connected(3, 4));
        System.out.println(uf.count());
    }
}