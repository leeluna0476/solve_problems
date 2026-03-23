#include <stdio.h>
#include <string.h>

int cnt;

int recurse(char *s, int left, int right) {
	++cnt;
	if (left >= right) {
		return 1;
	}
	else if (s[left] != s[right]) {
		return 0;
	}
	else {
		return recurse(s, left + 1, right - 1);
	}
}

int is_palindrome(char *s) {
	return recurse(s, 0, strlen(s) - 1);
}

int main(void) {
	int n;
	scanf("%d", &n);

	char s[1001];
	for (int i = 0; i < n; ++i) {
		scanf("%s", s);
		int p = is_palindrome(s);
		printf("%d %d\n", p, cnt); // 백준 서버에서는 변수에 저장 안하면 틀린다. 컴파일러마다 실행 순서가 다르게 처리될 수 있다.
		cnt = 0;
	}
}
