/*
对于这道题目，我本来的想法是认为只需要选取在当前状态下最小值即可，但这会忽略掉一些情况，比如说：
    2
   3 4
  6 5 4
 4 1 8 0
 按照我的思路，是选取2，3，5，1，但实际上应该是2，4，4，0
 所以这道题我能想到的是一个O(n^2)的解法，对于每一个数都计算其与下方较小数的和，最后将得到的一个一维数组排序，最小值就是答案
 但能否找到一个更好的解法呢？有没有办法利用滚动数组来解决呢？没有，时间复杂度下限就是O(n^2)
 事实上，我们可以认为，我的思路就是一个滚动数组，因为是用一个一维数组来解决二维问题的
 */

 对于每一行数据从前往后来是不对的，因为这样会导致数据的覆盖，所以应该从后往前来 666
 */
 int minimumTotal(int** triangle, int triangleSize, int* triangleColSize) {
    int* sum = (int*)calloc(triangleSize, sizeof(int));
    sum[0] = triangle[0][0]; // 初始化第一个元素

    for (int i = 1; i < triangleSize; i++) {
        // 从后向前更新，避免覆盖问题
        for (int j = triangleColSize[i] - 1; j >= 0; j--) {
            if (j == 0) {
                // 首元素只能来自上一层的首元素
                sum[j] = sum[j] + triangle[i][j];
            } else if (j == triangleColSize[i] - 1) {
                // 末尾元素只能来自上一层的末尾元素（即上一层的 j-1）
                sum[j] = sum[j-1] + triangle[i][j];
            } else {
                // 中间元素取上一层 j-1 和 j 的最小值
                sum[j] = fmin(sum[j-1], sum[j]) + triangle[i][j];
            }
        }
    }

    int result = INT_MAX;
    for (int i = 0; i < triangleColSize[triangleSize-1]; i++) {
        result = fmin(result, sum[i]);
    }
    free(sum);
    return result;
}