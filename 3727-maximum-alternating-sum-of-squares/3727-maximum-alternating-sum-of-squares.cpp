class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        vector<long long> sq(n);
        for (int i = 0; i < n; ++i) {
            sq[i] = 1LL * nums[i] * nums[i];
        }
        
        int m = n / 2;
        nth_element(sq.begin(), sq.begin() + m, sq.end());
        
        long long ans = 0;
        for (int i = 0; i < m; ++i) {
            ans -= sq[i];
        }
        for (int i = m; i < n; ++i) {
            ans += sq[i];
        }
        
        return ans;
    }
};