class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();
        if (n <= 1) return 0;
        
        vector<int> pref(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            pref[i + 1] = pref[i] + stoneValue[i];
        }
        
        vector<int> dp(n * n, 0);
        
        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i <= n - len; ++i) {
                int j = i + len - 1;
                int max_val = 0;
                int totalSum = pref[j + 1] - pref[i];
                
                for (int k = i; k < j; ++k) {
                    int leftSum = pref[k + 1] - pref[i];
                    int rightSum = totalSum - leftSum;
                    
                    if (leftSum < rightSum) {
                        int cur = leftSum + dp[i * n + k];
                        if (cur > max_val) max_val = cur;
                    } else if (leftSum > rightSum) {
                        int cur = rightSum + dp[(k + 1) * n + j];
                        if (cur > max_val) max_val = cur;
                    } else {
                        int val1 = dp[i * n + k];
                        int val2 = dp[(k + 1) * n + j];
                        int cur = leftSum + (val1 > val2 ? val1 : val2);
                        if (cur > max_val) max_val = cur;
                    }
                }
                dp[i * n + j] = max_val;
            }
        }
        
        return dp[n - 1];
    }
};