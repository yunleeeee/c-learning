#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 1000

// 定义一个结构体来存储长度和费用
typedef struct {
    int length;
    int cost;
} LengthCost;

// 比较函数，用于排序
int compare(const void *a, const void *b) {
    LengthCost *lc1 = (LengthCost *)a;
    LengthCost *lc2 = (LengthCost *)b;
    return lc2->length - lc1->length; // 降序排序
}

int get_distance(char c1, char c2) {
    int diff = abs(c1 - c2);
    return diff < 26 - diff ? diff : 26 - diff;
}

int longestPalindromeSubseqWithKOperations(char *s, int k) {
    int n = strlen(s);
    if (n == 0) return 0;

    // 初始化DP表
    LengthCost dp[MAXN][MAXN][MAXN]; // dp[i][j][m] 表示从i到j，长度为m的最小费用
    int dp_count[MAXN][MAXN]; // 记录每个区间内的长度数量

    // 单个字符的情况，费用0，长度1
    for (int i = 0; i < n; i++) {
        dp[i][i][0].length = 1;
        dp[i][i][0].cost = 0;
        dp_count[i][i] = 1;
    }

    // 按区间长度从小到大处理
    for (int l = 2; l <= n; l++) {
        for (int i = 0; i <= n - l; i++) {
            int j = i + l - 1;
            int count = 0;

            char c1 = s[i], c2 = s[j];
            int d = get_distance(c1, c2);

            // 选项1：包含i和j
            if (i + 1 <= j - 1) {
                for (int m = 0; m < dp_count[i + 1][j - 1]; m++) {
                    LengthCost inner = dp[i + 1][j - 1][m];
                    int new_len = inner.length + 2;
                    int new_cost = inner.cost + d;
                    if (new_cost <= k) {
                        dp[i][j][count].length = new_len;
                        dp[i][j][count].cost = new_cost;
                        count++;
                    }
                }
            } else {
                // 内部没有字符，直接形成长度为2的回文
                if (d <= k) {
                    dp[i][j][count].length = 2;
                    dp[i][j][count].cost = d;
                    count++;
                }
            }

            // 选项2：不包含i，取i+1..j
            for (int m = 0; m < dp_count[i + 1][j]; m++) {
                LengthCost right = dp[i + 1][j][m];
                if (right.cost <= k) {
                    dp[i][j][count].length = right.length;
                    dp[i][j][count].cost = right.cost;
                    count++;
                }
            }

            // 选项3：不包含j，取i..j-1
            for (int m = 0; m < dp_count[i][j - 1]; m++) {
                LengthCost left = dp[i][j - 1][m];
                if (left.cost <= k) {
                    dp[i][j][count].length = left.length;
                    dp[i][j][count].cost = left.cost;
                    count++;
                }
            }

            // 去重和排序
            qsort(dp[i][j], count, sizeof(LengthCost), compare);
            int unique_count = 0;
            for (int m = 0; m < count; m++) {
                if (m == 0 || dp[i][j][m].length != dp[i][j][m - 1].length) {
                    dp[i][j][unique_count] = dp[i][j][m];
                    unique_count++;
                }
            }
            dp_count[i][j] = unique_count;
        }
    }

    // 处理整个字符串的区间0..n-1
    for (int m = 0; m < dp_count[0][n - 1]; m++) {
        if (dp[0][n - 1][m].cost <= k) {
            return dp[0][n - 1][m].length;
        }
    }

    return 0;
}

int main() {
    char s[MAXN];
    int k;
    printf("Enter the string: ");
    scanf("%s", s);
    printf("Enter the value of k: ");
    scanf("%d", &k);

    int result = longestPalindromeSubseqWithKOperations(s, k);
    printf("Longest Palindrome Subsequence Length: %d\n", result);

    return 0;
}