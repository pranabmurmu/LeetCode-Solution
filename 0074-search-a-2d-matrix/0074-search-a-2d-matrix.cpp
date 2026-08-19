class Solution {
public:
    bool searchInRow(vector<vector<int>>& mat, int target, int row) {
        int n = mat[0].size();
        int st = 0;
        int end = n - 1;

        while (st <= end) {
            int mid = st + (end - st) / 2;
            if (target == mat[row][mid]) {
                return true;

            } else if (target > mat[row][mid]) {
                st = mid + 1;

            } else {
                end = mid - 1;
            }
        }
        return false;
    }
    bool searchMatrix(vector<vector<int>>& mat, int target) {
        int m = mat.size();
        int n = mat[0].size();
        int stR = 0;
        int endR = m - 1;

        while (stR <= endR) {
            int midR = stR + (endR - stR) / 2;
            if (target >= mat[midR][0] && target <= mat[midR][n - 1]) {
                return searchInRow(mat, target,midR);
            } else if (target >= mat[midR][n - 1]) {
                stR = midR + 1;
            } else {
                endR = midR - 1;
            }
        }
        return false;
    }
};