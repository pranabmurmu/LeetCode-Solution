#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
    struct Block {
        char c;
        int len;
    };
    struct ZeroBlock {
        int len;
        int idx;
    };
public:
    int maxActiveSectionsAfterTrade(string s) {
        vector<Block> blocks;
        int n = s.length();
        for (int i = 0; i < n; ) {
            int j = i;
            while (j < n && s[j] == s[i]) j++;
            blocks.push_back({s[i], j - i});
            i = j;
        }
        
        int base_1s = 0;
        vector<ZeroBlock> z_blocks;
        for (int i = 0; i < (int)blocks.size(); i++) {
            if (blocks[i].c == '1') {
                base_1s += blocks[i].len;
            } else {
                z_blocks.push_back({blocks[i].len, i});
            }
        }
        
        int k = min(3, (int)z_blocks.size());
        if (k > 0) {
            partial_sort(z_blocks.begin(), z_blocks.begin() + k, z_blocks.end(), 
                         [](const ZeroBlock& a, const ZeroBlock& b) {
                             return a.len > b.len;
                         });
        }
        
        int max_gain = 0;
        for (int i = 1; i < (int)blocks.size() - 1; i++) {
            if (blocks[i].c == '1') {
                int merged_len = blocks[i-1].len + blocks[i].len + blocks[i+1].len;
                int max_other_0 = 0;
                for (int idx = 0; idx < k; idx++) {
                    if (z_blocks[idx].idx != i - 1 && z_blocks[idx].idx != i + 1) {
                        max_other_0 = z_blocks[idx].len;
                        break;
                    }
                }
                int current_max_0 = max(merged_len, max_other_0);
                int gain = current_max_0 - blocks[i].len;
                if (gain > max_gain) {
                    max_gain = gain;
                }
            }
        }
        
        return base_1s + max_gain;
    }
};