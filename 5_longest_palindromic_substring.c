/* Given a string s, return the longest palindromic substring in s.
 * 
 * Example 1:
 * Input: s = "babad"
 * Output: "bab"
 * Explanation: "aba" is also a valid answer.
 *
 * Example 2:
 * Input: s = "cbbd"
 * Output: "bb"
 *
 * Constraints:
 * 1 <= s.length <= 1000
 * s consist of only digits and English letters.
 */

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

short	find_last_of(const char *s, short len, char c)
{
	short	i = len;
	while (i-- > 0)
	{
		if (s[i] == c)
			return i;
	}
	return -1;
}

bool	is_palindrome(const char *s, short start, short end)
{
	short	len = end - start + 1;
	for (int i = 0; i < len; ++i)
	{
		if (s[start + i] != s[end - i])
			return false;
	}
	return true;
}

// O(n^2)
char	*longestPalindrome(char *s)
{
	short	slen = strlen(s);
	char	*longest_palindrome = malloc(slen + 1);
	if (!longest_palindrome)
		return NULL;

	short	palen = 0;
	short	longest = 0;
	short	i = 0;
	while (s[i])
	{
		short	last = find_last_of(s, slen, s[i]);
		while (last > i && !is_palindrome(s, i, last))
			last = find_last_of(s, last, s[i]);
		palen = last - i + 1;
		if (palen > longest)
		{
			longest = palen;
			strlcpy(longest_palindrome, s + i, palen + 1);
		}
		++i;
	}
	return longest_palindrome;
}
