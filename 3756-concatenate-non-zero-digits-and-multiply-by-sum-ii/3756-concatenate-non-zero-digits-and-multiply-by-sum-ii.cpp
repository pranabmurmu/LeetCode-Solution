class Solution {
public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int n = s.length();
        long long M = 1e9 + 7;

        vector<long long> pow10(n + 1, 1);
        vector<long long> inv10(n + 1, 1);
        long long inv = 700000005;

        for (int i = 1; i <= n; ++i) {
            pow10[i] = (pow10[i - 1] * 10) % M;
            inv10[i] = (inv10[i - 1] * inv) % M;
        }

        vector<int> cnt(n + 1, 0);
        vector<long long> S(n + 1, 0);
        vector<long long> P(n + 1, 0);

        for (int i = 1; i <= n; ++i) {
            int val = s[i - 1] - '0';
            S[i] = S[i - 1] + val;
            cnt[i] = cnt[i - 1] + (val > 0 ? 1 : 0);

            if (val > 0) {
                P[i] = (P[i - 1] + val * inv10[cnt[i]]) % M;
            } else {
                P[i] = P[i - 1];
            }
        }

        vector<int> ans;
        ans.reserve(queries.size());

        for (const auto& q : queries) {
            int L = q[0] + 1;
            int R = q[1] + 1;

            long long sum_val = S[R] - S[L - 1];

            if (sum_val == 0) {
                ans.push_back(0);
            } else {
                long long x_val = (P[R] - P[L - 1] + M) % M;
                x_val = (x_val * pow10[cnt[R]]) % M;

                long long res = (x_val * (sum_val % M)) % M;
                ans.push_back(res);
            }
        }

        return ans;
    }
};