class Solution {
    static constexpr long long MOD = 1000000007LL;
    using Mat = std::vector<std::vector<long long>>;

    Mat multiply(const Mat& a, const Mat& b) {
        int n = (int)a.size();
        Mat c(n, std::vector<long long>(n, 0));
        for (int i = 0; i < n; ++i) {
            for (int k = 0; k < n; ++k) {
                if (!a[i][k]) continue;
                long long x = a[i][k];
                for (int j = 0; j < n; ++j) {
                    if (b[k][j]) {
                        c[i][j] = (c[i][j] + x * b[k][j]) % MOD;
                    }
                }
            }
        }
        return c;
    }

    std::vector<long long> multiplyVec(const Mat& a, const std::vector<long long>& v) {
        int n = (int)a.size();
        std::vector<long long> res(n, 0);
        for (int i = 0; i < n; ++i) {
            long long sum = 0;
            for (int j = 0; j < n; ++j) {
                if (a[i][j] && v[j]) {
                    sum = (sum + a[i][j] * v[j]) % MOD;
                }
            }
            res[i] = sum;
        }
        return res;
    }

public:
    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;
        if (n == 1) return m;

        int d = 2 * m;
        Mat trans(d, std::vector<long long>(d, 0));

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < i; ++j) trans[i][m + j] = 1;
            for (int j = i + 1; j < m; ++j) trans[m + i][j] = 1;
        }

        Mat power = trans;
        Mat result(d, std::vector<long long>(d, 0));
        for (int i = 0; i < d; ++i) result[i][i] = 1;

        long long e = n - 1;
        while (e > 0) {
            if (e & 1) result = multiply(result, power);
            power = multiply(power, power);
            e >>= 1;
        }

        std::vector<long long> init(d, 1);
        std::vector<long long> fin = multiplyVec(result, init);

        long long ans = 0;
        for (long long x : fin) ans = (ans + x) % MOD;
        return (int)ans;
    }
};