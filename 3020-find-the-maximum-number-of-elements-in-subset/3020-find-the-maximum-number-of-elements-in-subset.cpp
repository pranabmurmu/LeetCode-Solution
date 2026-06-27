class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long, int> cnt;
        for (int x : nums) cnt[x]++;

        int ans = 1;

        if (cnt.count(1)) {
            int c = cnt[1];
            ans = max(ans, (c & 1) ? c : c - 1);
        }

        for (auto &[x, c] : cnt) {
            if (x == 1) continue;

            long long cur = x;
            int len = 0;

            while (true) {
                if (!cnt.count(cur)) break;

                if (cnt[cur] >= 2) {
                    len += 2;
                } else {
                    len += 1;
                    break;
                }

                if (cur > 1000000000LL / cur) break;
                cur *= cur;
            }

            if ((len & 1) == 0) len--;
            ans = max(ans, len);
        }

        return ans;
    }
};