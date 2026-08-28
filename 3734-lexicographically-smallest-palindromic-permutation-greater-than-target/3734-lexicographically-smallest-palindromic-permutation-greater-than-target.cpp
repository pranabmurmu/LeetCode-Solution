class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.length();
        vector<int> count(26, 0);
        for (char c : s) count[c - 'a']++;
        
        int odd_count = 0;
        char mid_char = 0;
        for (int i = 0; i < 26; ++i) {
            if (count[i] % 2 != 0) {
                odd_count++;
                mid_char = 'a' + i;
            }
        }
        
        if (odd_count > 1) return "";
        
        vector<int> avail(26, 0);
        for (int i = 0; i < 26; ++i) {
            avail[i] = count[i] / 2;
        }
        
        int L = n / 2;
        string res(n, ' ');
        if (n % 2 != 0) {
            res[L] = mid_char;
        }
        
        for (int i = 0; i < L; ++i) {
            bool found = false;
            for (int c = 0; c < 26; ++c) {
                if (avail[c] > 0) {
                    avail[c]--;
                    res[i] = 'a' + c;
                    res[n - 1 - i] = 'a' + c;
                    
                    int left_idx = i + 1;
                    int right_idx = n - 2 - i;
                    
                    string temp_res = res;
                    int temp_avail[26];
                    for (int k = 0; k < 26; ++k) temp_avail[k] = avail[k];
                    
                    for (int k = 25; k >= 0; --k) {
                        while (temp_avail[k] > 0) {
                            temp_res[left_idx] = 'a' + k;
                            temp_res[right_idx] = 'a' + k;
                            left_idx++;
                            right_idx--;
                            temp_avail[k]--;
                        }
                    }
                    
                    if (temp_res > target) {
                        found = true;
                        break;
                    }
                    
                    avail[c]++;
                }
            }
            if (!found) return "";
        }
        
        if (res > target) return res;
        return "";
    }
};