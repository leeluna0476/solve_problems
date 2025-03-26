#include <limits.h>
#include <string.h>

#define MAX(a, b) a > b ? a : b

static void	init_subidx(short subidx[], const char *str, short s, short e)
{
	for (short i = s; i <= e; ++i)
		subidx[str[i]] = -1;
}

int lengthOfLongestSubstring(char *s)
{
	short	subidx[CHAR_MAX + 1];
	memset(subidx, -1, sizeof(subidx));

	int	max_sublen = 0;
	short	sublen = 0;
	short	i = 0;
	while (s[i])
	{
		if (subidx[s[i]] == -1)
			++sublen;
		else
		{
			short	init_start = i - sublen;
			sublen = i - subidx[s[i]];
			init_subidx(subidx, s, init_start, subidx[s[i]]);
	    }
		max_sublen = MAX(max_sublen, sublen);
		subidx[s[i]] = i;
		++i;
	}
	return max_sublen;
}
