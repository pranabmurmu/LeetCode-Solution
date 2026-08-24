class Solution {
public:
    int stoneGameVIII(vector<int>& stones) {
        int n = stones.size();
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += stones[i];
        }
        
        int ans = sum;
        for (int i = n - 1; i > 1; --i) {
            sum -= stones[i];
            if (sum - ans > ans) {
                ans = sum - ans;
            }
        }
        
        return ans;
    }
};