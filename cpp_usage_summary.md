## C++ 标准库使用总结

### STL

**vector**

push_back()
pop_back()

**unordered_map**

- 声明  unordered_map<int, int> map;
- 技巧： 可以定义string，将多个键链接起来
- 记录是否存储 `if(map.count(key))`
- 访问可以直接使用下标方式， 如果不存在会使用类型的默认值，例如 `map[i]++`, 如果 i 不存在于map 中，会令 `map[i] = 0 再加1。
- 遍历map  `for(auto &[dist, cnt] : map)`

**pair**

- 定义 pair = {a, b}
- 获取 auto [a, b] = pair 


**queue**

push()
front()
pop()



**priority_queue**

#include<queue>

默认是大顶堆

top 访问队头元素
empty 队列是否为空
size 返回队列内元素个数
push 插入元素到队尾 (并排序)
emplace 原地构造一个元素并插入队列
pop 弹出队头元素
swap 交换内容

greater 是小顶堆 （这与排序是反的， > 反而是小顶堆）
less 是大顶堆

https://blog.csdn.net/weixin_36888577/article/details/79937886

自定义 compare 函数
http://neutrofoton.github.io/blog/2016/12/29/c-plus-plus-priority-queue-with-comparator/

```C++
struct CustomCompare
{
    bool operator()(const int& lhs, const int& rhs)
    {
        return lhs < rhs; //小于号是大顶堆
    }
};
priority_queue<int,vector<int>, CustomCompare > pq;
```

### algorithm

- max/min({triple})
- sort()

- greater<int>() 从大到小
- less<int>() 从小到大
https://blog.csdn.net/cnd2449294059/article/details/77090174
### lambda

`[](传入类型) -> 返回类型 { 代码区; }`

`[](传入类型){ 代码区; }`

如果获取局部变量，使用&获取局部变量 `[&]() ->{}`

Fuction
https://stackoverflow.com/questions/356950/what-are-c-functors-and-their-uses

### string

stoi()
to_string()


### 类型

int 和 long 都是 32 位
long long 是 64 位


### 优化

参数传递尽量写成全局变量 或者 是地址传递！

### 取余

MOD = 1e9+7
MOD = 10e8+7

可以支持两个int 相加 再取余，多余两个int 相加，要改用long long 保存
或者用long long 保存，支持两个int 相乘再取余

### 向上取整技巧

ceil(x/n)  -> (x+n-1)/n

### 基本数组

int dp[2][3];  
memset(dp, 0, sizeof(dp)); //设初值
memcpy(dp, temp, sizeof(temp)); //拷贝另一个数组

**二维数组转换成一维**

m 是行数，n 是列数

(x,y) 可以转换成 x * n + y 


### 位运算

如果j 是完全 i 的子集
i ^ j 相当于 从 i 中把 j 对应的位置都减去
i | j  相当于 i 加上了 j


### 进制转换

例题：
168. Excel表列名称
171. Excel 表列序号
165. 比较版本号
8. 字符串转换整数 (atoi)

1. 10 进制转换为其他 M 进制 (num 从 0 开始, 从1 开始的话将num 用 (num - 1) 替换)
```C++
   string res;
   while(num != 0) {
          res += num % M - '0';
          num = num / M;
   }

```

2. 其他进制M 转换为 10 进制整数 (num 从 0 开始， 如果不从0 开始，s[i] 要用 s[i] + 1 替换)

```C++
        int res = 0;
        for(int i = 0; i < n; i++){
            res = res * M + (s[i] - '0');
        }
```

3. string 转换 成整数

```C++
        int res = 0;
        for(int i = 0; i < n; i++){
            res = res * 10 + (s[i] - '0');
        }
```

### 输入输出
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);