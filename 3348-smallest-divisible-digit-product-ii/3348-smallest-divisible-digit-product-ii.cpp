

class Solution {
    int dp[60][40];
    bool dp_init = false;

    void build_dp() {
        if (dp_init)
            return;
        for (int i = 0; i < 60; ++i) {
            for (int j = 0; j < 40; ++j) {
                dp[i][j] = 1e9;
            }
        }
        dp[0][0] = 0;
        for (int i = 0; i < 60; ++i) {
            for (int j = 0; j < 40; ++j) {
                if (dp[i][j] == 1e9)
                    continue;
                auto upd = [&](int di, int dj) {
                    int ni = min(59, i + di);
                    int nj = min(39, j + dj);
                    dp[ni][nj] = min(dp[ni][nj], dp[i][j] + 1);
                };
                upd(1, 0);
                upd(0, 1);
                upd(2, 0);
                upd(1, 1);
                upd(3, 0);
                upd(0, 2);
            }
        }
        dp_init = true;
    }

    int min_d(int r2, int r3) {
        build_dp();
        return dp[min(59, max(0, r2))][min(39, max(0, r3))];
    }

    string get_smallest_suffix(int L, int req2, int req3, int req5, int req7) {
        string res = "";
        for (int j = 0; j < L; ++j) {
            for (int d = 1; d <= 9; ++d) {
                int p2 = 0, p3 = 0, p5 = 0, p7 = 0;
                int temp = d;
                while (temp % 2 == 0) {
                    p2++;
                    temp /= 2;
                }
                while (temp % 3 == 0) {
                    p3++;
                    temp /= 3;
                }
                while (temp % 5 == 0) {
                    p5++;
                    temp /= 5;
                }
                while (temp % 7 == 0) {
                    p7++;
                    temp /= 7;
                }

                int nr2 = max(0, req2 - p2);
                int nr3 = max(0, req3 - p3);
                int nr5 = max(0, req5 - p5);
                int nr7 = max(0, req7 - p7);

                if (L - 1 - j >= nr5 + nr7 + min_d(nr2, nr3)) {
                    res += (char)('0' + d);
                    req2 = nr2;
                    req3 = nr3;
                    req5 = nr5;
                    req7 = nr7;
                    break;
                }
            }
        }
        return res;
    }

public:
    string smallestNumber(string num, long long t) {
        build_dp();

        int r2 = 0, r3 = 0, r5 = 0, r7 = 0;
        long long temp_t = t;
        while (temp_t % 2 == 0) {
            r2++;
            temp_t /= 2;
        }
        while (temp_t % 3 == 0) {
            r3++;
            temp_t /= 3;
        }
        while (temp_t % 5 == 0) {
            r5++;
            temp_t /= 5;
        }
        while (temp_t % 7 == 0) {
            r7++;
            temp_t /= 7;
        }

        if (temp_t > 1)
            return "-1";

        int N = num.length();

        vector<int> pref2(N + 1, 0), pref3(N + 1, 0), pref5(N + 1, 0),
            pref7(N + 1, 0);
        vector<bool> pref_zero(N + 1, false);

        for (int i = 0; i < N; ++i) {
            pref_zero[i + 1] = pref_zero[i] | (num[i] == '0');
            int d = num[i] - '0';
            int c2 = 0, c3 = 0, c5 = 0, c7 = 0;
            if (d > 0) {
                while (d % 2 == 0) {
                    c2++;
                    d /= 2;
                }
                while (d % 3 == 0) {
                    c3++;
                    d /= 3;
                }
                while (d % 5 == 0) {
                    c5++;
                    d /= 5;
                }
                while (d % 7 == 0) {
                    c7++;
                    d /= 7;
                }
            }
            pref2[i + 1] = pref2[i] + c2;
            pref3[i + 1] = pref3[i] + c3;
            pref5[i + 1] = pref5[i] + c5;
            pref7[i + 1] = pref7[i] + c7;
        }

        if (!pref_zero[N] && pref2[N] >= r2 && pref3[N] >= r3 &&
            pref5[N] >= r5 && pref7[N] >= r7) {
            return num;
        }

        for (int i = N - 1; i >= 0; --i) {
            if (pref_zero[i])
                continue;

            for (int d = num[i] - '0' + 1; d <= 9; ++d) {
                int p2 = 0, p3 = 0, p5 = 0, p7 = 0;
                int temp = d;
                while (temp % 2 == 0) {
                    p2++;
                    temp /= 2;
                }
                while (temp % 3 == 0) {
                    p3++;
                    temp /= 3;
                }
                while (temp % 5 == 0) {
                    p5++;
                    temp /= 5;
                }
                while (temp % 7 == 0) {
                    p7++;
                    temp /= 7;
                }

                int nr2 = max(0, r2 - pref2[i] - p2);
                int nr3 = max(0, r3 - pref3[i] - p3);
                int nr5 = max(0, r5 - pref5[i] - p5);
                int nr7 = max(0, r7 - pref7[i] - p7);

                if (N - 1 - i >= nr5 + nr7 + min_d(nr2, nr3)) {
                    string ans = num.substr(0, i);
                    ans += (char)('0' + d);
                    ans += get_smallest_suffix(N - 1 - i, nr2, nr3, nr5, nr7);
                    return ans;
                }
            }
        }

        int L = N + 1;
        while (true) {
            if (L >= r5 + r7 + min_d(r2, r3)) {
                return get_smallest_suffix(L, r2, r3, r5, r7);
            }
            L++;
        }

        return "-1";
    }
};