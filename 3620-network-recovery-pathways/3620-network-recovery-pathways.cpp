class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size();

        vector<vector<pair<int,int>>> adj(n);
        vector<int> indeg(n, 0);
        int mx = 0;

        for (auto &e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
            indeg[e[1]]++;
            mx = max(mx, e[2]);
        }

        queue<int> q;
        vector<int> topo;
        for (int i = 0; i < n; i++) {
            if (indeg[i] == 0) q.push(i);
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topo.push_back(u);
            for (auto &p : adj[u]) {
                if (--indeg[p.first] == 0)
                    q.push(p.first);
            }
        }

        auto check = [&](int lim) {
            const long long INF = (1LL << 60);
            vector<long long> dist(n, INF);
            dist[0] = 0;

            for (int u : topo) {
                if (dist[u] == INF) continue;
                if (u != 0 && u != n - 1 && !online[u]) continue;

                for (auto &[v, w] : adj[u]) {
                    if (w < lim) continue;
                    if (v != 0 && v != n - 1 && !online[v]) continue;
                    if (dist[u] + w < dist[v])
                        dist[v] = dist[u] + w;
                }
            }

            return dist[n - 1] <= k;
        };

        int lo = 0, hi = mx, ans = -1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (check(mid)) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        return ans;
    }
};