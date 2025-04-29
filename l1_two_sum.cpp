#include <vector>
#include <unordered_map>

using namespace std;

class Solution
{
    public:
        vector<int> twoSum(vector<int>& nums, int target)
        {
            vector<int> answer;

            int                     v_size = nums.size();
            unordered_map<int, int> umap(v_size);
            for (int i = 0; i < v_size; ++i)
            {
                unordered_map<int, int>::iterator    it = umap.find(target - nums[i]);
                if (it != umap.end())
                {
                    answer.push_back(it->second);
                    answer.push_back(i);
                    break;
                }

                umap[nums[i]] = i;
            }
            return answer;
        }
};
