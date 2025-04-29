#include <string>
#include <unordered_map>

using namespace std;

class Solution
{
	public:
		int romanToInt(string s)
		{
			int	rint['Z' + 1] = { 0, };
			rint['I'] = 1;
			rint['V'] = 5;
			rint['X'] = 10;
			rint['L'] = 50;
			rint['C'] = 100;
			rint['D'] = 500;
			rint['M'] = 1000;

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
