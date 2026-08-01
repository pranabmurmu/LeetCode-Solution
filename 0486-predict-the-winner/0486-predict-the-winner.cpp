using namespace std;

class Solution {
public:
    bool predictTheWinner(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp = nums;
        for (int d = 1; d < n; ++d) {
            for (int i = 0; i < n - d; ++i) {
                dp[i] = max(nums[i] - dp[i + 1], nums[i + d] - dp[i]);
            }
        }
        return dp[0] >= 0;
    }
};