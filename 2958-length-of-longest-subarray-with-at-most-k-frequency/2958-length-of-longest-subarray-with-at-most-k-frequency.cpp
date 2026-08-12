class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        freq.reserve(nums.size());
        
        int max_len = 0;
        int left = 0;
        int n = nums.size();
        
        for (int right = 0; right < n; ++right) {
            freq[nums[right]]++;
            
            while (freq[nums[right]] > k) {
                freq[nums[left]]--;
                left++;
            }
            
            if (right - left + 1 > max_len) {
                max_len = right - left + 1;
            }
        }
        
        return max_len;
    }
};