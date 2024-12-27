#include <vector>
#include <unordered_map>

using namespace std;

class Solution
{
    public:
        vector<int> twoSum(vector<int>& nums, int target)
        {
            vector<int> answer;
            unordered_map<int, int>  umap;

            int v_size = nums.size();
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
