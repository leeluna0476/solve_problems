A = [0 for _ in range(100)]
B = [0 for _ in range(100)]
C = [0 for _ in range(100)]

def stack_number(stk):
    if stk is A:
        return 1;
    elif stk is B:
        return 2;
    else:
        return 3;

def hanoi_top(f, tmp, to, n):
    if n == 1:
        print(stack_number(f), stack_number(to));
    else:
        hanoi_top(f, to, tmp, n - 1);
        print(stack_number(f), stack_number(to));
        hanoi_top(tmp, f, to, n - 1);

n = int(input());
print(pow(2, n) - 1);
if n <= 20:
    hanoi_top(A, B, C, n);
