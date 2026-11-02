class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int start = 0;
        int sum = 0;
        int k = INT_MAX;

        for(int end = 0; end < nums.size(); end++){
            sum += nums[end];

            while(sum >= target){
                k = min(k, end - start + 1);

                sum -= nums[start];
                start++;
            }
        }

        return k == INT_MAX ? 0 : k;
    }
};