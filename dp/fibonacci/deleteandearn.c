
/*
删除或增加点数：要解决一个问题，给定一个数组，如果选择获取一个元素，就不能获取相邻元素。如获取了5，就不能获取4，6；
要求输出能够获取的最大值
想解决这样一个问题，我们发现如果直接分析dp[i]是难以实现的，因为问题的字问题并不是清晰的
所以我们可以先对数组进行排序，然后再考虑规划
但这时候又出现了问题，可能数据并非连续的，那我们该如何判断这个数据是否可以选择呢？
我们可以不对数组全体进行排序，而是仅仅找到最大值，然后动态分配空间，建立一个新数组m
m数组用来统计每个元素出现的次数，每个元素出现次数记录在m[num[i]]中，这样就使得m数组可以直接进行动态规划
写出状态转移方程：dp[i] = max(dp[i-1], dp[i-2]+m[i]*i)
这样就可以解决这个问题
*/

int deleteAndEarn(int* nums, int numsSize) {
    int sum = 0;
    int max = INT_MIN;
    for(int i = 0; i < numsSize; i++){
        if(nums[i] > max){
            max = nums[i];
        }
    }
    int *m = (int*)malloc(sizeof(int) * (max+1));
    memset(m, 0, sizeof(int) * (max+1));
    for(int i = 0; i < numsSize; i++) {
        m[nums[i]]++;
    }
    int *dp = (int*)malloc(sizeof(int) * (max+1));
    if(numsSize == 1){
        return nums[0];
    }
    dp[0] = 0;
    int* sum = (int*)malloc((max_num + 1) * sizeof(int));
    for (int i = 0; i <= max_num; i++) {
        sum[i] = i * count[i];
    }
    for(int i = 1; i <= max; i++){
        dp[i] = max(dp[i-1], dp[i-2] + m[i]*i);
    }
    return dp[max];
}

