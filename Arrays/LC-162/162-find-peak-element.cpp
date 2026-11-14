class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        
        for(int i = 1; i < nums.size() - 1; i++){
            if(nums[i - 1] < nums[i] && nums[i] > nums[i + 1]){
                return i;
            }
        }

        if(nums.size() == 1) return 0;

        if(nums[0] > nums[1]) return 0;

        return nums.size() - 1;
    }
};