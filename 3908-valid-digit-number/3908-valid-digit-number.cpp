class Solution {
public:
    bool validDigit(int n, int x) {
        int nm=n;
        int count =0;
        vector<int> num;
        while(nm>0){
            int dig=nm%10;
            nm=nm/10;
            num.push_back(dig);
            if(dig==x){
                count++;
            }


        }
        if(count==0 || num[num.size()-1] == x){
            return false;
        }
        


        return true;
    }
};