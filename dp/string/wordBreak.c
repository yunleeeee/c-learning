/*
第一次有不想写的想法，真的好难想到啊，完全想不到怎么做，看了题解才知道怎么做。
给你一个字符串 s 和一个字符串列表 wordDict 作为字典。如果可以利用字典中出现的一个或多个单词拼接出 s 则返回 true。
例如，给定 s = "leetcode" 和 wordDict = ["leet", "code"]，返回 true。

在询问过deepseek后我的一些理解：对于这道题，定义一个dp数组，dp[i]表示s[0:i]是否可以被wordDict中的单词拼接而成。
那么我么要做的就是检查j=0~i-1，如果dp[j]为true且s[j:i]在wordDict中，那么dp[i]就为true。
*/

typedef struct {
    char *word;
    int len;
}wordlist;

bool wordBreak(char* s, char** wordDict, int wordDictSize) {
    if (s == NULL || wordDict == NULL || wordDictSize == 0) {
        return false;
    }

    int max = 0;
    wordlist *list = (wordlist*) malloc (sizeof(wordlist) * wordDictSize);
    for(int i = 0; i < wordDictSize; i++) {
        list[i].word = wordDict[i];
        list[i].len = strlen(wordDict[i]);
        if (list[i].len > max) {
            max = list[i].len;
        }
    }

    int n = strlen(s);
    bool *dp = (bool *)calloc(n + 1, sizeof(bool));
    dp[0] = true;

    for(int i = 0; i < n; i++) {
        int start = (i - max) > 0 ? (i - max) : 0;
        for(int j = start; j < i; j++) {
            if(dp[j]) {
                int substr_len = i - j;
                // 遍历字典检查子串是否存在
                for (int k = 0; k < wordDictSize; k++) {
                    if (list[k].len == substr_len && strncmp(list[k].word, s + j, substr_len) == 0) {
                        dp[i] = true;
                        break;  // 找到匹配即可跳出循环
                    }
                }
            }
            if(dp[i]) break;
        }
    }
    const bool result = dp[n];
    free(list);
    free(dp);
    return result;
}