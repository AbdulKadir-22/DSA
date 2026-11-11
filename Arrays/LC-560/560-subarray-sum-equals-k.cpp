class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int,int> map;
        
        int prefixSum = 0;
        int count = 0;

        map[0] = 1;

        for(int num : nums){
            prefixSum += num;
            int remaining = prefixSum - k;

            if(map.find(remaining) != map.end()){
                count += map[remaining];
            }

            map[prefixSum]++;
        }

        return count;
    }
};