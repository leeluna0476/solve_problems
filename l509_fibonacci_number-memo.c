int	dfib(int n, int *memo)
{
	if (n && !memo[n])
	{
		if (n == 1 || n == 2)
			memo[n] = 1;
		else
			memo[n] = dfib(n - 1, memo) + dfib(n - 2, memo);
	}
	return memo[n];
}

int	fib(int n)
{
	int	*memo = calloc(n + 1, sizeof(int));
	if (!memo)
		return 0;
	int	ret = dfib(n, memo);
	free(memo);
	return ret;
}
