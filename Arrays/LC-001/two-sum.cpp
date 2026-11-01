class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> numbers;

        for(int i = 0; i < nums.size(); i++){
            int complement = target - nums[i];
            if(numbers.contains(complement)){
                return {numbers[complement], i};
            }

            numbers[nums[i]] = i;
        }
        return {};
    }
};