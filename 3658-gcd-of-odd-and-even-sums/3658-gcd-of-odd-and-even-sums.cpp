class Solution {
public:
    int gcdOfOddEvenSums(int n) {
        int odd = n*n;
        int even =n*(n+1);

        while(even!=0){
            int rem = odd%even;
            odd=even;
            even =rem;
        }

        return odd;
        
    }
};