class Solution {
public:
    bool searchMatrix(vector<vector<int>>& mat, int tar) {
        int m = mat.size();
        int n = mat[0].size();

        int r=0;
        int c =n-1;

        while(r<m && c>=0){
            if(tar == mat[r][c]){
                return true;
            }else if(tar<mat[r][c]){
                c--;
            }else{
                r++;
            }
        }
        return false;
        
    }
};