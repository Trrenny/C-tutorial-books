class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::unordered_map<int,int> my_map;
		std::vector<int> result;
        for (int i = 0 ; i < nums.size();++i)
        {
            if(!my_map.count((target-nums[i])))
            {
                my_map.insert(std::make_pair(nums[i],i));
                continue;
            }

            else
            {
				result.push_back(i);
				result.push_back(my_map.at(target-nums[i]));
				return result;
            }
        }
        return result;

    }
};