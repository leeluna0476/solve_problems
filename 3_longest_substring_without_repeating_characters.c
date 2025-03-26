#include <limits.h>
#include <string.h>

#define MAX(a, b) a > b ? a : b

void	init_idxmap(short idxmap[], const char *str, short s, short e)
{
	for (short i = s; i <= e; ++i)
		idxmap[str[i]] = -1;
}

/*
 * 1. s를 순회한다.
 * 2. s에서 각 문자가 등장하는 인덱스를 idxmap에 저장한다. 새로운 문자를 읽을 때마다 부분열의 길이를 업데이트한다.
 * 3. 부분열 내에서 문자가 중복으로 등장하면(idxmap[c] != -1) 부분열의 시작 문자부터 해당 문자까지의 모든 문자를 삭제하고 부분열의 길이를 업데이트한다.
 * 4. 가장 긴 부분열의 길이를 업데이트한다.
 */
int lengthOfLongestSubstring(char *s)
{
	short	idxmap[CHAR_MAX + 1];
	memset(idxmap, -1, sizeof(idxmap));

	int	max_sublen = 0;
	short	sublen = 0;
	short	i = 0;
	while (s[i])
	{
		if (idxmap[s[i]] == -1)
			++sublen;
		else
		{
			short	init_start = i - sublen;
			sublen = i - idxmap[s[i]];
			init_idxmap(idxmap, s, init_start, idxmap[s[i]]);
	    }
		max_sublen = MAX(max_sublen, sublen);
		idxmap[s[i]] = i;
		++i;
	}
	return max_sublen;
}
