class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;

        sort(nums.begin(), nums.end());

        while(left < right){
            if(nums[left] % 2 == 0){
                left++;
            }
            else if(nums[right] % 2 == 1){
                right--;
            }
            else{
                swap(nums[right], nums[left]);
            }
        }

        return nums;
    }
};