class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n =nums.size();
        if(nums.size()==1){
            return 0;
        }

        if(nums[0]>nums[1]){
            return 0;
        }
        if(nums[n-1]>nums[n-2]){
            return n-1;
        }
         

        int st = 1;
        int end = nums.size() - 2;

        while (st <= end) {
            int mid = st + (end - st) / 2;
            if (nums[mid - 1] < nums[mid] && nums[mid] > nums[mid + 1]) {
                return mid;
            }
            if (nums[mid - 1] < nums[mid]) {
                st = mid + 1;
            } else {
                end = mid - 1;
            }
        }

        return -1;
    }
};