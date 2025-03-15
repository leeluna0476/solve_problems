#include <string>
#include <unordered_map>

using namespace std;

class Solution
{
	public:
		int romanToInt(string s)
		{
			unordered_map<char, int>	rint = {
				{ 'I', 1 },
				{ 'V', 5 },
				{ 'X', 10 },
				{ 'L', 50 },
				{ 'C', 100 },
				{ 'D', 500 },
				{ 'M', 1000 }
			};

			string::size_type	i = s.length() - 1;
			int	bef = rint[s[i]];
			int	num = bef;
			while (i-- > 0)
			{
				int	x = rint[s[i]];
				if (x < bef)
					num -= x;
				else
					num += x;
				bef = x;
			}
			return num;
		}
};
