class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        if (!head || !head->next || !head->next->next) {
            return {-1, -1};
        }
        
        int first_idx = -1;
        int prev_idx = -1;
        int min_dist = 1e9;
        
        int prev_val = head->val;
        ListNode* curr = head->next;
        int idx = 1;
        
        while (curr->next) {
            int curr_val = curr->val;
            int next_val = curr->next->val;
            
            if ((curr_val > prev_val && curr_val > next_val) || 
                (curr_val < prev_val && curr_val < next_val)) {
                if (first_idx == -1) {
                    first_idx = idx;
                } else {
                    if (idx - prev_idx < min_dist) {
                        min_dist = idx - prev_idx;
                    }
                }
                prev_idx = idx;
            }
            
            prev_val = curr_val;
            curr = curr->next;
            idx++;
        }
        
        if (min_dist == 1e9) {
            return {-1, -1};
        }
        
        return {min_dist, prev_idx - first_idx};
    }
};