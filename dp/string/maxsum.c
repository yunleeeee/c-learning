
int maxsum(int* nums, int n) {
    if (n == 0) return 0; // 处理空数组的情况
    
    int current_max = nums[0];
    int max_sum = nums[0];
    
    for (int i = 1; i < n; i++) {
        // 计算以当前元素结尾的最大子序列和
        current_max = (nums[i] > current_max + nums[i]) ? nums[i] : current_max + nums[i];
        // 更新全局最大和
        if (current_max > max_sum) {
            max_sum = current_max;
        }
    }
    return max_sum;
}