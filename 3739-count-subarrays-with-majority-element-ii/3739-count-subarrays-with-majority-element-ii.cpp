class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();
        int offset = n + 2;
        int m = 2 * n + 5;

        vector<int> bit(m + 2, 0);

        auto update = [&](int idx) {
            while (idx <= m + 1) {
                bit[idx]++;
                idx += idx & -idx;
            }
        };

        auto query = [&](int idx) {
            long long res = 0;
            while (idx > 0) {
                res += bit[idx];
                idx -= idx & -idx;
            }
            return res;
        };

        long long ans = 0;
        int pref = 0;

        update(offset + 1);

        for (int x : nums) {
            pref += (x == target ? 1 : -1);
            ans += query(pref + offset);
            update(pref + offset + 1);
        }

        return ans;
    }
};