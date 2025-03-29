 int	fib(int n)
{
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;

	int	one = 0;
	int	two = 1;
	int	next = 0;
	--n;
	for (int i = 0; i < n; ++i)
	{
		next = one + two;
		one = two;
		two = next;
	}
	return next;
}
