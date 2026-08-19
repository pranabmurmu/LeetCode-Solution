class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        sort(reservedSeats.begin(), reservedSeats.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });
        
        int ans = 2 * n;
        int m = reservedSeats.size();
        
        for (int i = 0; i < m; ) {
            int row = reservedSeats[i][0];
            int res = 0;
            while (i < m && reservedSeats[i][0] == row) {
                res |= (1 << reservedSeats[i][1]);
                i++;
            }
            
            bool left = (res & 60) == 0;
            bool right = (res & 960) == 0;
            bool mid = (res & 240) == 0;
            
            if (left && right) {
            } else if (left || right || mid) {
                ans -= 1;
            } else {
                ans -= 2;
            }
        }
        
        return ans;
    }
};