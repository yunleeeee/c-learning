/*
学习一个方法：滚动数组 优化空间复杂度
众所周知，dp是牺牲空间换时间，但是有时候我们可以通过滚动数组的方式来优化空间复杂度。
比如这道题，我们可以看到，dp[i][j]只和dp[i-1][j]和dp[i][j-1]有关，所以我们可以只用一个一维数组来存储dp[i-1][j]和dp[i][j-1]。
这样我们就可以将空间复杂度从O(m*n)降到O(n)。

*/
int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridSize,
    int* obstacleGridColSize) {
    int n = obstacleGridSize, m = obstacleGridColSize[0];
    int f[m];
    memset(f, 0, sizeof(f));
    f[0] = (obstacleGrid[0][0] == 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (obstacleGrid[i][j] == 1) {
                f[j] = 0;
                continue;
            }
            if (j - 1 >= 0 && obstacleGrid[i][j - 1] == 0) {
                f[j] += f[j - 1];
            }
        }
    }

return f[m - 1];
}