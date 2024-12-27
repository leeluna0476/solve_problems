#include <string>

using namespace std;

class Solution
{
    public:
        bool    isPalindrome(int x)
        {
            string  num_str = to_string(x);
            int     digits = num_str.size();
            int     half_digits = digits / 2;

            int didx = digits - 1;
            for (int i = 0; i < half_digits; ++i)
            {
                if (num_str[i] != num_str[didx - i])
                {
                    return false;
                }
            }

            return true;
        }
};
