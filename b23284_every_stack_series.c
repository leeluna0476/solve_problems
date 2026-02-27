#include <stdio.h>

#define MAX 11
int n;
int series[MAX];
int visited[MAX];

// 중복되면 안됨.
// stack => 들어가는 건 오름차순, 나오는 건 내림차순.
//       => 앞 숫자보다 크다면, 지금까지 나온 숫자들 중 가장 커야 함. (12543 OK, 12534 NOK, 12354 OK)
//       => 앞 숫자보다 작다면, 앞 숫자와 내 사이 숫자들이 모두 나왔어야 함.

char poppable(int m, int prev) {
	for (int i = m + 1; i < prev; ++i) {
		if (!visited[i]) {
			return 0;
		}
	}
	return 1;
}

void generate_stack_series(int prev, int greatest, int cnt) {
	if (cnt == n) {
		for (int i = 0; i < n; ++i) {
			printf("%d ", series[i]);
		}
		printf("\n");
		return;
	}
	for (int i = 1; i <= n; ++i) {
		if (!visited[i] && ((i < prev && poppable(i, prev)) || (i > prev && i > greatest))) {
			if (i > greatest) {
				greatest = i;
			}
			visited[i] = 1;
			series[cnt] = i;
			generate_stack_series(i, greatest, cnt + 1);
			visited[i] = 0;
		}
	}
}

int main(void) {
	scanf("%d", &n);
	generate_stack_series(0, 0, 0);
}
