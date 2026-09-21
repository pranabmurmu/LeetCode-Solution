class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long long> result(k, 0);
        vector<long long> dp(k, 0);
        vector<long long> next_dp(k, 0);
        vector<int> active;
        active.reserve(k);
        vector<int> next_active;
        next_active.reserve(k);
        
        for (int i = 0; i < n; ++i) {
            int x = nums[i] % k;
            
            if (next_dp[x] == 0) {
                next_active.push_back(x);
            }
            next_dp[x] += 1;
            
            for (int v : active) {
                int val = (1LL * v * x) % k;
                if (next_dp[val] == 0) {
                    next_active.push_back(val);
                }
                next_dp[val] += dp[v];
                dp[v] = 0; 
            }
            
            active.swap(next_active);
            next_active.clear();
            
            for (int v : active) {
                dp[v] = next_dp[v];
                result[v] += dp[v];
                next_dp[v] = 0; 
            }
        }
        
        return result;
    }
};