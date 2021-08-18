## C++ 标准库使用总结

### STL

**unordered_map**

- 声明  unordered_map<int, int> map;
- 技巧： 可以定义string，将多个键链接起来
- 记录是否存储 `if(map.count(key))`
- 访问可以直接使用下标方式， 如果不存在会使用类型的默认值，例如 `map[i]++`, 如果 i 不存在于map 中，会令 `map[i] = 0 再加1。

**pair**

- 定义 pair = {a, b}
- 获取 auto [a, b] = pair 

**priority_queue**

### algorithm

- max/min({triple})
- sort()

- greater<int>() 从大到小


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

### 基本数组


int dp[2][3];  
memset(dp, 0, sizeof(dp)); //设初值
memcpy(dp, temp, sizeof(temp)); //拷贝另一个数组