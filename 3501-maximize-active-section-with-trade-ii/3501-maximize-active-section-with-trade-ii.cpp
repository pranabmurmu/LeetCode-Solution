#pragma GCC optimize("O3")
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
    struct Top3Z {
        int v[3];
        int id[3];
        Top3Z() {
            for(int i = 0; i < 3; ++i) { v[i] = -1; id[i] = -1; }
        }
    };

    static Top3Z mergeZ(const Top3Z& a, const Top3Z& b) {
        Top3Z res;
        int i = 0, j = 0, k = 0;
        while (k < 3 && (i < 3 || j < 3)) {
            if (i < 3 && j < 3 && a.id[i] == -1 && b.id[j] == -1) break;
            int val, idx;
            if (i < 3 && (j == 3 || b.id[j] == -1 || a.v[i] > b.v[j])) {
                val = a.v[i]; idx = a.id[i]; i++;
            } else if (j < 3) {
                val = b.v[j]; idx = b.id[j]; j++;
            } else {
                break;
            }
            if (idx == -1) continue;
            bool dup = false;
            for (int p = 0; p < k; ++p) {
                if (res.id[p] == idx) { dup = true; break; }
            }
            if (!dup) {
                res.v[k] = val; res.id[k] = idx; k++;
            }
        }
        return res;
    }

    struct Top3O {
        int v[3];
        int id[3];
        Top3O() {
            for(int i = 0; i < 3; ++i) { v[i] = 1e9; id[i] = -1; }
        }
    };

    static Top3O mergeO(const Top3O& a, const Top3O& b) {
        Top3O res;
        int i = 0, j = 0, k = 0;
        while (k < 3 && (i < 3 || j < 3)) {
            if (i < 3 && j < 3 && a.id[i] == -1 && b.id[j] == -1) break;
            int val, idx;
            if (i < 3 && (j == 3 || b.id[j] == -1 || a.v[i] < b.v[j])) {
                val = a.v[i]; idx = a.id[i]; i++;
            } else if (j < 3) {
                val = b.v[j]; idx = b.id[j]; j++;
            } else {
                break;
            }
            if (idx == -1) continue;
            bool dup = false;
            for (int p = 0; p < k; ++p) {
                if (res.id[p] == idx) { dup = true; break; }
            }
            if (!dup) {
                res.v[k] = val; res.id[k] = idx; k++;
            }
        }
        return res;
    }

public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.length();
        vector<int> pref1(n + 1, 0);
        vector<pair<int, int>> B;
        
        int current_start = -1;
        for (int i = 0; i < n; ++i) {
            pref1[i + 1] = pref1[i] + (s[i] == '1' ? 1 : 0);
            if (s[i] == '0') {
                if (current_start == -1) current_start = i;
            } else {
                if (current_start != -1) {
                    B.push_back({current_start, i - 1});
                    current_start = -1;
                }
            }
        }
        if (current_start != -1) {
            B.push_back({current_start, n - 1});
        }
        
        int K = B.size();
        vector<int> orig_Z(K);
        for (int i = 0; i < K; ++i) {
            orig_Z[i] = B[i].second - B[i].first + 1;
        }
        
        vector<int> orig_O;
        if (K > 1) {
            orig_O.resize(K - 1);
            for (int i = 0; i < K - 1; ++i) {
                orig_O[i] = B[i + 1].first - B[i].second - 1;
            }
        }
        
        vector<int> Adj;
        if (K > 1) {
            Adj.resize(K - 1);
            for (int i = 0; i < K - 1; ++i) {
                Adj[i] = orig_Z[i] + orig_Z[i + 1];
            }
        }
        
        vector<int> lg(max(2, K + 1), 0);
        for (int i = 2; i <= K; ++i) lg[i] = lg[i / 2] + 1;
        
        vector<vector<Top3Z>> stZ;
        if (K > 0) {
            stZ.assign(lg[K] + 1, vector<Top3Z>(K));
            for (int i = 0; i < K; ++i) {
                stZ[0][i].v[0] = orig_Z[i];
                stZ[0][i].id[0] = i;
            }
            for (int p = 1; p <= lg[K]; ++p) {
                int len = 1 << p;
                for (int i = 0; i + len <= K; ++i) {
                    stZ[p][i] = mergeZ(stZ[p - 1][i], stZ[p - 1][i + (len / 2)]);
                }
            }
        }
        
        auto queryZ = [&](int L, int R) -> Top3Z {
            if (L > R) return Top3Z();
            int p = lg[R - L + 1];
            return mergeZ(stZ[p][L], stZ[p][R - (1 << p) + 1]);
        };
        
        vector<vector<Top3O>> stO;
        if (K > 1) {
            stO.assign(lg[K - 1] + 1, vector<Top3O>(K - 1));
            for (int i = 0; i < K - 1; ++i) {
                stO[0][i].v[0] = orig_O[i];
                stO[0][i].id[0] = i;
            }
            for (int p = 1; p <= lg[K - 1]; ++p) {
                int len = 1 << p;
                for (int i = 0; i + len <= K - 1; ++i) {
                    stO[p][i] = mergeO(stO[p - 1][i], stO[p - 1][i + (len / 2)]);
                }
            }
        }
        
        auto queryO = [&](int L, int R) -> Top3O {
            if (L > R) return Top3O();
            int p = lg[R - L + 1];
            return mergeO(stO[p][L], stO[p][R - (1 << p) + 1]);
        };
        
        vector<vector<int>> stAdj;
        if (K > 1) {
            stAdj.assign(lg[K - 1] + 1, vector<int>(K - 1, 0));
            for (int i = 0; i < K - 1; ++i) stAdj[0][i] = Adj[i];
            for (int p = 1; p <= lg[K - 1]; ++p) {
                int len = 1 << p;
                for (int i = 0; i + len <= K - 1; ++i) {
                    stAdj[p][i] = max(stAdj[p - 1][i], stAdj[p - 1][i + (len / 2)]);
                }
            }
        }
        
        auto queryAdj = [&](int L, int R) -> int {
            if (L > R) return 0;
            int p = lg[R - L + 1];
            return max(stAdj[p][L], stAdj[p][R - (1 << p) + 1]);
        };
        
        vector<int> ans;
        ans.reserve(queries.size());
        
        for (const auto& q : queries) {
            int l = q[0], r = q[1];
            int base = pref1[n];
            
            if (K == 0) {
                ans.push_back(base);
                continue;
            }
            
            int u = -1, low = 0, high = K - 1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (B[mid].second >= l) {
                    u = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }
            
            int v = -1;
            low = 0; high = K - 1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (B[mid].first <= r) {
                    v = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
            
            if (u == -1 || v == -1 || u > v) {
                ans.push_back(base);
                continue;
            }
            
            int m = v - u + 1;
            if (m == 1) {
                ans.push_back(base);
                continue;
            }
            
            int Z_1 = min(r, B[u].second) - max(l, B[u].first) + 1;
            int Z_m = min(r, B[v].second) - max(l, B[v].first) + 1;
            
            if (m == 2) {
                ans.push_back(base + Z_1 + Z_m);
                continue;
            }
            
            if (m == 3) {
                int Z_2 = orig_Z[u + 1];
                int O_1 = orig_O[u];
                int O_2 = orig_O[u + 1];
                int gain1 = max(Z_1 + Z_2, Z_m - O_1);
                int gain2 = max(Z_2 + Z_m, Z_1 - O_2);
                ans.push_back(base + max(gain1, gain2));
                continue;
            }
            
            Top3Z midZ = queryZ(u + 1, v - 1);
            Top3Z endsZ;
            if (Z_1 >= Z_m) {
                endsZ.v[0] = Z_1; endsZ.id[0] = u;
                endsZ.v[1] = Z_m; endsZ.id[1] = v;
            } else {
                endsZ.v[0] = Z_m; endsZ.id[0] = v;
                endsZ.v[1] = Z_1; endsZ.id[1] = u;
            }
            Top3Z allZ = mergeZ(endsZ, midZ);
            
            Top3O allO = queryO(u, v - 1);
            
            int max_diff = 0;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    int z_val = allZ.v[i], z_idx = allZ.id[i];
                    int o_val = allO.v[j], o_idx = allO.id[j];
                    if (z_idx == -1 || o_idx == -1) continue;
                    if (z_idx != o_idx && z_idx != o_idx + 1) {
                        max_diff = max(max_diff, z_val - o_val);
                    }
                }
            }
            
            int cand1 = Z_1 + orig_Z[u + 1];
            int cand2 = orig_Z[v - 1] + Z_m;
            int cand3 = 0;
            if (u + 1 <= v - 2) {
                cand3 = queryAdj(u + 1, v - 2);
            }
            
            int max_sum = max({cand1, cand2, cand3});
            ans.push_back(base + max(max_sum, max_diff));
        }
        
        return ans;
    }
};