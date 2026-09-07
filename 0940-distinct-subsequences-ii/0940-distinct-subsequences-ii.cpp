class Solution {
public:
    int distinctSubseqII(string s) {
        int mod = 1000000007;
        int dp[26] = {0};
        int total = 0;
        
        for (char c : s) {
            int idx = c - 'a';
            int prev = dp[idx];
            dp[idx] = (total + 1) % mod;
            total = (2LL * total - prev + 1 + mod) % mod;
        }
        
        return total;
    }
};