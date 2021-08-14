# 贪心算法

Interval Scheduling 区间调度问题

 - 方法1， 按照 start/end 排序，转换成end/start最长上升序列问题 (o(n^2) - O(n))
 - 方法2： 贪心，按照end 排序，然后按照start排除所有重叠的


 例题：
 435. 无重叠区间（中等）
 452. 用最少数量的箭引爆气球（中等）