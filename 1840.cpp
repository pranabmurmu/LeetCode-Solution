// Maximum Building Hight
class Solution {
public:
    int maxBuilding(int n, vector<vector<int>>& restrictions) {
        restrictions.push_back({1, 0});
        sort(restrictions.begin(), restrictions.end());

        int m = restrictions.size();

        for (int i = 1; i < m; i++) {
            restrictions[i][1] = min(restrictions[i][1], restrictions[i - 1][1] + restrictions[i][0] - restrictions[i - 1][0]);
        }

        for (int i = m - 2; i >= 0; i--) {
            restrictions[i][1] = min(restrictions[i][1], restrictions[i + 1][1] + restrictions[i + 1][0] - restrictions[i][0]);
        }

        int ans = 0;

        for (int i = 1; i < m; i++) {
            int x1 = restrictions[i - 1][0], h1 = restrictions[i - 1][1];
            int x2 = restrictions[i][0], h2 = restrictions[i][1];

            int dist = x2 - x1;
            int peak = (h1 + h2 + dist) / 2;
            ans = max(ans, peak);
        }

        if (restrictions.back()[0] != n) {
            ans = max(ans, restrictions.back()[1] + (n - restrictions.back()[0]));
        }

        return ans;
    }
};






