/*
要解决一个最长回文字串的问题，没什么思路，想到需要用到dp，那么考虑能否找到状态转移方程。
仔细思考能否把问题分解成字问题呢？
如果要让当前字串是回文的，那么去掉两头它也是回文的，那么可以得到状态转移方程：
dp[i][j] = dp[i+1][j-1] && s[i] == s[j]
找到状态转移方程以后，我们要如何实现呢？
我们可以从长度为1的子串开始，然后逐渐增加长度，直到长度为n，这样就可以得到最长的回文子串。



外面的大循环是长度，里面的小循环是起始位置，这样可以保证每次计算dp[i][j]的时候，dp[i+1][j-1]已经计算过了。
而且大循环长度保证每个长度的所有连续字串都被遍历，实在是妙
*/

/*
char dest[10];
const char *src = "Example string";

strncpy(dest, src, sizeof(dest) - 1); // Copy up to 9 characters
dest[sizeof(dest) - 1] = '\0';         // Ensure null termination
*/

/*
再来思考能否继续优化，答案是可以优化空间复杂度。我们可以使用中心扩展法，这样可以减少空间复杂度。
中心扩展法的思路是，从每个字符开始，向两边扩展，直到不是回文串为止，这样可以得到最长的回文串。
但是要注意，回文串有两种情况，一种是奇数长度，一种是偶数长度，所以我们要分别考虑这两种情况。
*/

char* longestPalindrome(char* s) {
    int l = strlen(s);
    if (l == 0) return "";
    int **dp = (int **)malloc(l * sizeof(int *));
    for (int i = 0; i < l; i++) {
        dp[i] = (int *)malloc(l * sizeof(int));
        memset(dp[i], 0, l * sizeof(int));
    }
    for(int i = 0; i < l; i++) {
        dp[i][i] = 1;
    }
    int max = 0;
    int start = 0;
    if(l < 2) return s;

    for(int sl = 2; i <= l; i++) {
        for(int i = 0; i < l; i++) { //i is the start
            int j = i + sl -1;//j is the end
            if(j >= l) break;
            if(s[i] != s[j]) {
                dp[i][j] = 0;
            }
            else {
                if(j - i < 3) {
                    dp[i][j] = 1;
                }
                else {
                    dp[i][j] = dp[i+1][j-1];
                }
            }
            if(dp[i][j] && j - i + 1 > max) {
                max = j - i + 1;
                start = i;
            }
        }
    }
    char *res = (char *)malloc(max + 1);
    strncpy(res, s + start, max);
    res[max] = '\0';
    return res;
}