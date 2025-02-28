#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int rob(int* nums, int numsize) {
    int *dp = (int *)malloc(sizeof(int) * numsize);
    memset(dp, 0, sizeof(int) * numsize);
    if (numsize == 0) {
        return 0;
    }
    if (numsize == 1) {
        return nums[0];
    }
    if (numsize == 2) {
        return nums[0] > nums[1] ? nums[0] : nums[1];
    }
    dp[0] = nums[0];
    dp[1] = nums[0] > nums[1] ? nums[0] : nums[1];
    for (int i = 2; i < numsize; i++) {
        dp[i] = dp[i - 1] > dp[i - 2] + nums[i] ? dp[i - 1] : dp[i - 2] + nums[i];
    }
    return dp[numsize - 1];
}


//盗窃问题：不能连续盗窃，也就意味着dp[i] = max(dp[i-1], dp[i-2] + nums[i]即在这一位置的最大盗窃金额是前一个位置的最大盗窃金额和前两个位置的最大盗窃金额加上当前位置的最大盗窃金额的最大值