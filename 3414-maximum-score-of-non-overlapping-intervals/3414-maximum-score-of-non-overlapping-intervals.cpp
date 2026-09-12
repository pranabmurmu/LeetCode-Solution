class Solution {
    struct Interval {
        int l, r, w, id;
        bool operator<(const Interval& other) const {
            if (l != other.l) return l < other.l;
            return r < other.r;
        }
    };

    struct State {
        long long weight = -1;
        int len = 0;
        int ids[4] = {0};
    };

    static bool is_better(const State& a, const State& b) {
        if (a.weight != b.weight) return a.weight > b.weight;
        if (a.weight == -1) return false;
        for (int i = 0; i < a.len && i < b.len; ++i) {
            if (a.ids[i] != b.ids[i]) return a.ids[i] < b.ids[i];
        }
        return a.len < b.len;
    }

    static State combine(const State& prev, const Interval& interval) {
        if (prev.weight == -1) return State();
        State res;
        res.weight = prev.weight + interval.w;
        res.len = prev.len + 1;
        
        int insert_id = interval.id;
        int j = 0;
        while (j < prev.len && prev.ids[j] < insert_id) {
            res.ids[j] = prev.ids[j];
            j++;
        }
        res.ids[j] = insert_id;
        for (int k = j; k < prev.len; ++k) {
            res.ids[k + 1] = prev.ids[k];
        }
        
        return res;
    }

public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<Interval> sorted_intervals(n);
        for (int i = 0; i < n; ++i) {
            sorted_intervals[i] = {intervals[i][0], intervals[i][1], intervals[i][2], i};
        }
        sort(sorted_intervals.begin(), sorted_intervals.end());

        vector<array<State, 5>> dp(n + 1);
        for (int i = 0; i <= n; ++i) {
            dp[i][0].weight = 0;
            dp[i][0].len = 0;
        }

        for (int i = n - 1; i >= 0; --i) {
            int target = sorted_intervals[i].r;
            int low = i + 1, high = n - 1, nxt = n;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (sorted_intervals[mid].l > target) {
                    nxt = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }

            for (int k = 1; k <= 4; ++k) {
                State choice1 = dp[i + 1][k];
                State choice2 = combine(dp[nxt][k - 1], sorted_intervals[i]);
                
                if (is_better(choice2, choice1)) {
                    dp[i][k] = choice2;
                } else {
                    dp[i][k] = choice1;
                }
            }
        }

        State best_state;
        best_state.weight = -2;
        for (int k = 0; k <= 4; ++k) {
            if (is_better(dp[0][k], best_state)) {
                best_state = dp[0][k];
            }
        }

        vector<int> ans(best_state.len);
        for (int i = 0; i < best_state.len; ++i) {
            ans[i] = best_state.ids[i];
        }
        
        return ans;
    }
};