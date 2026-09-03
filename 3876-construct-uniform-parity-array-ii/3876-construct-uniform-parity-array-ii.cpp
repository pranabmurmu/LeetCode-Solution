class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int min_val = nums1[0];
        bool has_odd = false;
        for (int x : nums1) {
            if (x < min_val)
                min_val = x;
            if (x & 1)
                has_odd = true;
        }
        return (min_val & 1) || !has_odd;
    }
};
