class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> adj(n);
        for (const auto& inv : invocations) {
            adj[inv[0]].push_back(inv[1]);
        }
        
        vector<bool> sus(n, false);
        vector<int> q;
        q.reserve(n);
        q.push_back(k);
        sus[k] = true;
        
        for (int i = 0; i < q.size(); ++i) {
            int u = q[i];
            for (int v : adj[u]) {
                if (!sus[v]) {
                    sus[v] = true;
                    q.push_back(v);
                }
            }
        }
        
        bool possible = true;
        for (const auto& inv : invocations) {
            if (!sus[inv[0]] && sus[inv[1]]) {
                possible = false;
                break;
            }
        }
        
        vector<int> ans;
        if (possible) {
            for (int i = 0; i < n; ++i) {
                if (!sus[i]) {
                    ans.push_back(i);
                }
            }
        } else {
            for (int i = 0; i < n; ++i) {
                ans.push_back(i);
            }
        }
        
        return ans;
    }
};