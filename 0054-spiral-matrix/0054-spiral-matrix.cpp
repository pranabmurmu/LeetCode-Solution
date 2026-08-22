class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& mat) {
        vector<int> ans;
        int m = mat.size();
        int n = mat[0].size();
        int str = 0, stc = 0, endr = m - 1, endc = n - 1;

        while (str<=endr && stc<=endc) {
            for (int j = stc; j <= endc; j++) {
                ans.push_back(mat[str][j]);
            }
            for (int i = str + 1; i <= endr; i++) {
                ans.push_back(mat[i][endc]);
            }
            for (int j = endc - 1; j >= stc; j--) {
                if(str==endr){
                    break;
                }
                ans.push_back(mat[endr][j]);
            }
            for (int i = endr - 1; i >= str + 1; i--) {
                if(stc==endc){
                    break;
                }
                ans.push_back(mat[i][stc]);
            }
            str++;endr--;stc++;endc--;
        }
        return ans;
    }
};