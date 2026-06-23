class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        const int MOD = 1000000007;
        int m = r - l + 1;
        if (n == 1) return m;

        std::vector<long long> up(m, 1), down(m, 1), nu(m), nd(m);

        for (int len = 2; len <= n; ++len) {
            long long pref = 0;
            for (int i = 0; i < m; ++i) {
                nu[i] = pref;
                pref += down[i];
                if (pref >= MOD) pref -= MOD;
            }

            long long suf = 0;
            for (int i = m - 1; i >= 0; --i) {
                nd[i] = suf;
                suf += up[i];
                if (suf >= MOD) suf -= MOD;
            }

            up.swap(nu);
            down.swap(nd);
        }

        long long ans = 0;
        for (int i = 0; i < m; ++i) {
            ans += up[i] + down[i];
            ans %= MOD;
        }
        return (int)ans;
    }
};