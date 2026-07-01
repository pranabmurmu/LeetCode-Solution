class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size();

        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
        queue<pair<int, int>> q;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    dist[i][j] = 0;
                    q.push({i, j});
                }
            }
        }

        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};

        while (!q.empty()) {
            auto cur = q.front();
            q.pop();

            int x = cur.first;
            int y = cur.second;

            for (int k = 0; k < 4; k++) {
                int nx = x + dx[k];
                int ny = y + dy[k];

                if (nx >= 0 && nx < n && ny >= 0 && ny < n &&
                    dist[nx][ny] == INT_MAX) {
                    dist[nx][ny] = dist[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }

        int low = 0, high = 2 * n;

        auto can = [&](int val) {
            if (dist[0][0] < val || dist[n - 1][n - 1] < val)
                return false;

            vector<vector<int>> vis(n, vector<int>(n, 0));
            queue<pair<int, int>> qq;
            qq.push({0, 0});
            vis[0][0] = 1;

            while (!qq.empty()) {
                auto cur = qq.front();
                qq.pop();

                int x = cur.first;
                int y = cur.second;

                if (x == n - 1 && y == n - 1)
                    return true;

                for (int k = 0; k < 4; k++) {
                    int nx = x + dx[k];
                    int ny = y + dy[k];

                    if (nx >= 0 && nx < n && ny >= 0 && ny < n &&
                        !vis[nx][ny] && dist[nx][ny] >= val) {
                        vis[nx][ny] = 1;
                        qq.push({nx, ny});
                    }
                }
            }

            return false;
        };

        while (low < high) {
            int mid = (low + high + 1) / 2;
            if (can(mid))
                low = mid;
            else
                high = mid - 1;
        }

        return low;
    }
};