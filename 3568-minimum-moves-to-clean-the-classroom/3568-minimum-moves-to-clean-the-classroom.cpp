class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();
        int L_count = 0;
        int litter_id[20][20];
        memset(litter_id, -1, sizeof(litter_id));
        int start_r = -1, start_c = -1;
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (classroom[i][j] == 'L') {
                    litter_id[i][j] = L_count++;
                } else if (classroom[i][j] == 'S') {
                    start_r = i;
                    start_c = j;
                }
            }
        }
        
        if (L_count == 0) return 0;
        
        int max_e[20][20][1024];
        memset(max_e, -1, sizeof(max_e));
        
        struct State {
            int8_t r, c;
            int16_t mask;
            int8_t energy;
        };
        
        vector<State> q, nq;
        q.push_back({(int8_t)start_r, (int8_t)start_c, 0, (int8_t)energy});
        max_e[start_r][start_c][0] = energy;
        
        int moves = 0;
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        int target = (1 << L_count) - 1;
        
        while (!q.empty()) {
            nq.clear();
            for (const State& curr : q) {
                if (curr.mask == target) {
                    return moves;
                }
                
                if (curr.energy < max_e[curr.r][curr.c][curr.mask]) {
                    continue;
                }
                
                for (int d = 0; d < 4; ++d) {
                    int nr = curr.r + dr[d];
                    int nc = curr.c + dc[d];
                    
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n && classroom[nr][nc] != 'X') {
                        int n_energy = curr.energy - 1;
                        if (n_energy < 0) continue;
                        
                        if (classroom[nr][nc] == 'R') {
                            n_energy = energy;
                        }
                        
                        int n_mask = curr.mask;
                        if (litter_id[nr][nc] != -1) {
                            n_mask |= (1 << litter_id[nr][nc]);
                        }
                        
                        if (n_energy > max_e[nr][nc][n_mask]) {
                            max_e[nr][nc][n_mask] = n_energy;
                            nq.push_back({(int8_t)nr, (int8_t)nc, (int16_t)n_mask, (int8_t)n_energy});
                        }
                    }
                }
            }
            q.swap(nq);
            moves++;
        }
        
        return -1;
    }
};