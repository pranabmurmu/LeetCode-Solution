#pragma GCC optimize("O3")
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int C_nCr[5005][2505];
bool initialized = false;

class Solution {
public:
    Solution() {
        if (!initialized) {
            for (int i = 0; i <= 5000; ++i) {
                C_nCr[i][0] = 1;
                for (int j = 1; j <= i / 2; ++j) {
                    long long val = 0;
                    int r1 = j - 1;
                    if (r1 > (i - 1) / 2) r1 = (i - 1) - r1;
                    val += C_nCr[i - 1][r1];
                    
                    int r2 = j;
                    if (r2 <= i - 1) {
                        if (r2 > (i - 1) / 2) r2 = (i - 1) - r2;
                        val += C_nCr[i - 1][r2];
                    }
                    if (val > 2000000000LL) val = 2000000000LL;
                    C_nCr[i][j] = val;
                }
            }
            initialized = true;
        }
    }

    long long get_C(int n, int r) {
        if (r < 0 || r > n) return 0;
        if (r > n / 2) r = n - r;
        return C_nCr[n][r];
    }

    long long get_perms(const vector<int>& freq, int len) {
        long long perms = 1;
        int rem = len;
        for (int f : freq) {
            if (f > 0) {
                long long c = get_C(rem, f);
                if (c >= 2000000000LL) return 2000000000LL;
                if (perms > 2000000000LL / c) return 2000000000LL;
                perms *= c;
                rem -= f;
            }
        }
        return perms;
    }

    string smallestPalindrome(string s, int k) {
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c - 'a']++;
        }
        
        int mid_char = -1;
        vector<int> half_freq(26, 0);
        int half_len = 0;
        
        for (int i = 0; i < 26; ++i) {
            if (freq[i] % 2 != 0) {
                mid_char = i;
            }
            half_freq[i] = freq[i] / 2;
            half_len += half_freq[i];
        }
        
        long long total_perms = get_perms(half_freq, half_len);
        if (k > total_perms) {
            return "";
        }
        
        string left_half = "";
        int current_len = half_len;
        
        for (int i = 0; i < half_len; ++i) {
            for (int c = 0; c < 26; ++c) {
                if (half_freq[c] > 0) {
                    half_freq[c]--;
                    long long p = get_perms(half_freq, current_len - 1);
                    if (k <= p) {
                        left_half += (char)('a' + c);
                        current_len--;
                        break;
                    } else {
                        k -= p;
                        half_freq[c]++;
                    }
                }
            }
        }
        
        string res = left_half;
        if (mid_char != -1) {
            res += (char)('a' + mid_char);
        }
        string right_half = left_half;
        reverse(right_half.begin(), right_half.end());
        res += right_half;
        
        return res;
    }
};