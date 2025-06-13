// problem link: https://leetcode.cn/problems/longest-unequal-adjacent-groups-subsequence-ii/description/

#include <climits>
#include <string>
#include <vector>
using namespace std;

// a very classic dynamic programming problem.
class Solution
{
public:
    int calcHaming(const string &s1, const string &s2)
    {
        int s1len = s1.size(), s2len = s2.size();
        if (s1len != s2len)
            return INT_MAX;
        int dis = 0;
        for (int i = 0; i < s1len; i++)
        {
            dis += s1[i] != s2[i];
        }
        return dis;
    }
    vector<string> getWordsInLongestSubsequence(vector<string> &words,
                                                vector<int> &groups)
    {
        int size = groups.size();
        // dp[i]: the max length of sub sequence starts with words[i].
        // for j in [i + 1, size - 1], if groups[j] != groups[i], and
        // the Hanming distance between words[i] and words[j] is 1, then
        // dp[j] + 1 MIGHT be a valid answer for dp[i], that is,
        // dp[i] = MAX(dp[i], dp[j] + 1).
        vector<int> dp(size);
        // use back array for generate ans. Back record the index(j) of biggest dp[j] + 1.
        vector<int> back(size);
        int maxInd = -1;
        int maxVal = INT_MIN;
        for (int i = size - 1; i >= 0; i--)
        {
            dp[i] = 1;
            back[i] = size;
            for (int j = i + 1; j < size; j++)
            {
                if (calcHaming(words[i], words[j]) == 1 && groups[i] != groups[j])
                {
                    if (dp[j] + 1 > dp[i])
                    {
                        dp[i] = dp[j] + 1;
                        back[i] = j;
                    }
                }
            }
            if (dp[i] > maxVal)
            {
                maxVal = dp[i];
                maxInd = i;
            }
        }
        vector<string> ans;
        while (maxInd != size)
        {
            ans.push_back(words[maxInd]);
            maxInd = back[maxInd];
        }
        return ans;
    }
};