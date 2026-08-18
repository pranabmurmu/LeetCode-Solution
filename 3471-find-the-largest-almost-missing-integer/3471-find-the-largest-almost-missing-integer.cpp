class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();
        if (k == n) {
            int mx = -1;
            for (int x : nums) {
                if (x > mx) mx = x;
            }
            return mx;
        }
        
        int max_val = -1;
        for (int x : nums) {
            if (x > max_val) max_val = x;
        }
        
        vector<int> count(max_val + 1, 0);
        for (int x : nums) {
            count[x]++;
        }
        
        if (k == 1) {
            for (int i = max_val; i >= 0; --i) {
                if (count[i] == 1) return i;
            }
            return -1;
        }
        
        int mx = -1;
        if (count[nums[0]] == 1) {
            mx = nums[0];
        }
        if (count[nums[n - 1]] == 1 && nums[n - 1] > mx) {
            mx = nums[n - 1];
        }
        
        return mx;
    }
};