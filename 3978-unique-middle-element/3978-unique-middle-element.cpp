class Solution {
public:
    bool isMiddleElementUnique(vector<int>& nums) {
        // vector<int> num = nums;
        int n = nums.size();
        int mid = n / 2;
        int count = 0;

        for (int i = 0; i < n; i++) {
            if (nums[mid] == nums[i]) {
                count++;
            }
        }
        if (count > 1) {
            return false;
        }

        return true;
    }
};