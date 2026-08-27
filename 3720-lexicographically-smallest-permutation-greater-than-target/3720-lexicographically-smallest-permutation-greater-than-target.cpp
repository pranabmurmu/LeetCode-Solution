class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.length();
        vector<int> count(26, 0);
        for (char c : s) {
            count[c - 'a']++;
        }
        
        for (int i = n - 1; i >= 0; --i) {
            vector<int> temp = count;
            bool match = true;
            for (int j = 0; j < i; ++j) {
                if (temp[target[j] - 'a'] == 0) {
                    match = false;
                    break;
                }
                temp[target[j] - 'a']--;
            }
            
            if (match) {
                for (char c = target[i] + 1; c <= 'z'; ++c) {
                    if (temp[c - 'a'] > 0) {
                        string res = target.substr(0, i);
                        res += c;
                        temp[c - 'a']--;
                        for (int k = 0; k < 26; ++k) {
                            res.append(temp[k], 'a' + k);
                        }
                        return res;
                    }
                }
            }
        }
        return "";
    }
};
