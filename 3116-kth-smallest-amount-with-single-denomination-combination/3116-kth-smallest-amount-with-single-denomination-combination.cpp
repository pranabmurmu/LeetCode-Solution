class Solution {
public:
    long long findKthSmallest(vector<int>& coins, int k) {
        vector<int> fc;
        sort(coins.begin(), coins.end());
        for (int c : coins) {
            bool ok = true;
            for (int f : fc) {
                if (c % f == 0) {
                    ok = false;
                    break;
                }
            }
            if (ok) fc.push_back(c);
        }
        
        int n = fc.size();
        int sz = (1 << n) - 1;
        vector<long long> lcms(sz + 1);
        vector<int> signs(sz + 1);
        
        for (int i = 0; i < n; ++i) {
            lcms[1 << i] = fc[i];
            signs[1 << i] = 1;
        }
        
        for (int mask = 1; mask <= sz; ++mask) {
            int lsb = mask & -mask;
            if (mask != lsb) {
                lcms[mask] = std::lcm(lcms[mask ^ lsb], lcms[lsb]);
                signs[mask] = -signs[mask ^ lsb];
            }
        }
        
        long long low = 1;
        long long high = (long long)fc[0] * k;
        long long ans = high;
        
        while (low <= high) {
            long long mid = low + (high - low) / 2;
            long long cnt = 0;
            
            for (int mask = 1; mask <= sz; ++mask) {
                cnt += (mid / lcms[mask]) * signs[mask];
            }
            
            if (cnt >= k) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        
        return ans;
    }
};