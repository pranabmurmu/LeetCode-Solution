class Solution {
public:
    int countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();
        int offset = n + 2;
        int m = 2 * n + 5;

        vector<int> bit(m + 1, 0);

        auto update = [&](int idx) {
            while (idx <= m) {
                bit[idx]++;
                idx += idx & -idx;
            }
        };

        auto query = [&](int idx) {
            int res = 0;
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

        return (int)ans;
    }
};