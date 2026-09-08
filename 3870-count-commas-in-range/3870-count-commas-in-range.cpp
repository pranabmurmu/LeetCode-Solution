class Solution {
public:
    int countCommas(int n) {
        int total = 0;
        long long p = 1000;
        while (n >= p) {
            total += (n - p + 1);
            p *= 1000;
        }
        return total;
    }
};