class Solution {
public:
    long long sumAndMultiply(int n) {

        long long rev = 0;

        while (n > 0) {
            int digit = n % 10;

            if (digit != 0)
                rev = rev * 10 + digit;

            n /= 10;
        }

        long long x = 0;

        while (rev > 0) {
            int digit = rev % 10;
            x = x * 10 + digit;
            rev /= 10;
        }

        long long temp = x;
        long long sum = 0;

        while (temp > 0) {
            sum += temp % 10;
            temp /= 10;
        }

        return x * sum;
    }
};