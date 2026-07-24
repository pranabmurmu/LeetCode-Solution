// #pragma GCC optimize("O3")
// #include <vector>

// using namespace std;

class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int max_val = 0;
        for (int x : nums) {
            if (x > max_val) max_val = x;
        }
        
        int limit = 1;
        while (limit <= max_val) {
            limit <<= 1;
        }
        
        vector<int> has(limit, 0);
        vector<int> U;
        U.reserve(nums.size());
        for (int x : nums) {
            if (!has[x]) {
                has[x] = 1;
                U.push_back(x);
            }
        }
        
        int sz = U.size();
        vector<int> has_pair(limit, 0);
        for (int i = 0; i < sz; ++i) {
            int ui = U[i];
            for (int j = i; j < sz; ++j) {
                has_pair[ui ^ U[j]] = 1;
            }
        }
        
        vector<int> valid(limit, 0);
        int ans = 0;
        for (int i = 0; i < limit; ++i) {
            if (has_pair[i]) {
                for (int j = 0; j < sz; ++j) {
                    int val = i ^ U[j];
                    if (!valid[val]) {
                        valid[val] = 1;
                        ans++;
                    }
                }
            }
        }
        
        return ans;
    }
};