class Solution {
public:
    int mirrorDistance(int n) {
        int reverse= 0;
        int num = n;
        while(n > 0){
            int digit = n%10;
            n = n/10;
            reverse = reverse*10 + digit;
        }

        int dis = abs( num - reverse);

        return dis;
    }
};