class Solution {
public:
    bool checkDivisibility(int n) {
        int num = n;
        long long sum = 0;
        long long prod = 1;

        while (num > 0) {
            int dig = num % 10;
            sum += dig;
            prod *= dig;
            num = num/10;
        }
        long long summ = sum + prod;
        if (n % summ == 0) {
            return true;
        } else {
            return false;
        }

        return false;
    }
};