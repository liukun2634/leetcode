#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//思路1：双指针，比较到第k个

//思路2： 二分法 log(m + n)
//k == 1, k == 2, k == 3 

//pivot1 = nums1[k/2 - 1]
//pivot2 = nums2[k/2 - 1]
//pivot = min(pivot1, pivot2) 最多也是第k - 1 个，把 index 更新为 pivot + 1

int findKth(vector<int> nums1, vector<int> nums2, int k){
    //初始化从 0 开始
    int index1 = 0, index2 = 0;
    int n = nums1.size(), m = nums2.size();

    while(true) {
        //1. 终结条件1， 等于length的长度
        if (index1 == n){
            return nums2[index2 + k - 1]; //下标需要额外减1
        }

        //2. 终结条件2
        if (index1 == m){
            return nums1[index1 + k - 1]; 
        }

        //3. 终结条件3， k 为 1 的时候， 返回两者最小的值
        if (k == 1){
            return min(nums1[index1], nums2[index2]); //下标需要额外减1
        }

        //每次更新值
        int half = k / 2;
        int newIndex1 = min(index1 + half - 1, n - 1);
        int newIndex2 = min(index2 + half - 1, m - 1);
        int pivot1 = nums1[newIndex1];
        int pivot2 = nums2[newIndex2];
        if (pivot1 < pivot2){
            //1、减去 index1 中一定小于 k 的数目
            k = k - (newIndex1 - index1 + 1);
            //2、index1更新为 newIndex1 + 1, 使用 + 1 后，就可能为第 k 个
            index1 = newIndex1 + 1; 
        } else {
            k = k - (newIndex2 - index2 + 1);
            index2 = newIndex2 + 1;
        }
    }
}