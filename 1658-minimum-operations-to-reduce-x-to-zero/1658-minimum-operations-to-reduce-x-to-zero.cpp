class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int target = -x;
        for (int num : nums) {
            target += num;
        }
        
        if (target < 0) return -1;
        if (target == 0) return nums.size();
        
        int n = nums.size();
        int max_len = -1;
        int current_sum = 0;
        
        for (int left = 0, right = 0; right < n; ++right) {
            current_sum += nums[right];
            while (current_sum > target && left <= right) {
                current_sum -= nums[left++];
            }
            if (current_sum == target) {
                if (right - left + 1 > max_len) {
                    max_len = right - left + 1;
                }
            }
        }
        
        return max_len == -1 ? -1 : n - max_len;
    }
};