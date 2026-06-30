class Solution {
public:
    int numberOfSubstrings(string s) {
        vector<int> freq(3, 0);
        int i = 0;
        int j = 0;
        int n = s.size();
        int result = 0;
        while (j < n) {
            freq[s[j] - 'a']++;
            while (freq[0] && freq[1] && freq[2]) {
                result += n - j;
                freq[s[i] - 'a']--;
                i++;
            }
            j++;
        }
        return result;
    }
};