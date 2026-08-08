class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.length();
        int m = word2.length();
        
        vector<int> suf(n + 1, 0);
        int j = m - 1;
        for (int i = n - 1; i >= 0; --i) {
            if (j >= 0 && word1[i] == word2[j]) {
                j--;
            }
            suf[i] = m - 1 - j;
        }
        
        vector<int> ans;
        ans.reserve(m);
        bool changed = false;
        int curr = 0;
        
        for (int k = 0; k < m; ++k) {
            bool found = false;
            while (curr < n) {
                if (word1[curr] == word2[k]) {
                    ans.push_back(curr);
                    curr++;
                    found = true;
                    break;
                } else if (!changed && suf[curr + 1] >= m - 1 - k) {
                    ans.push_back(curr);
                    changed = true;
                    curr++;
                    found = true;
                    break;
                }
                curr++;
            }
            if (!found) {
                return {};
            }
        }
        
        return ans;
    }
};