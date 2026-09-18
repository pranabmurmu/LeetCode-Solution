class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int first[26], last[26];
        fill(first, first + 26, -1);
        int n = s.length();
        
        for (int i = 0; i < n; ++i) {
            int c = s[i] - 'a';
            if (first[c] == -1) {
                first[c] = i;
            }
            last[c] = i;
        }
        
        vector<pair<int, int>> intervals;
        intervals.reserve(26);
        
        for (int i = 0; i < 26; ++i) {
            if (first[i] != -1) {
                int left = first[i];
                int right = last[i];
                bool valid = true;
                
                for (int j = left; j <= right; ++j) {
                    int c = s[j] - 'a';
                    if (first[c] < left) {
                        valid = false;
                        break;
                    }
                    if (last[c] > right) {
                        right = last[c];
                    }
                }
                
                if (valid) {
                    intervals.emplace_back(right, left);
                }
            }
        }
        
        sort(intervals.begin(), intervals.end());
        
        vector<string> ans;
        int last_end = -1;
        
        for (const auto& p : intervals) {
            if (p.second > last_end) {
                ans.push_back(s.substr(p.second, p.first - p.second + 1));
                last_end = p.first;
            }
        }
        
        return ans;
    }
};