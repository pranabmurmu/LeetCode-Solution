// class Solution {
// public:
//     int findPeakElement(vector<int>& nums) {
//         int n =nums.size();
//         if(nums.size()==1){ //corner case where arr size is 1
//             return 0;
//         }

//         if(nums[0]>nums[1]){ //corner case where index zero is included
//             return 0;
//         }
//         if(nums[n-1]>nums[n-2]){ //corner case where index n-1 is included
//             return n-1; 
//         }
         

//         int st = 1;
//         int end = nums.size() - 2;

//         while (st <= end) {
//             int mid = st + (end - st) / 2;
//             if (nums[mid - 1] < nums[mid] && nums[mid] > nums[mid + 1]) {
//                 return mid;
//             }
//             if (nums[mid - 1] < nums[mid]) {
//                 st = mid + 1;
//             } else {
//                 end = mid - 1;
//             }
//         }

//         return -1;
//     }
// };
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] < nums[mid + 1])
                left = mid + 1;
            else
                right = mid;
        }

        return left;
    }
};