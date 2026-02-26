#include <cstdio>
#include <set>
#include <algorithm>

using namespace std;

#define MAX 300001
set<int> keys;
int depths[MAX];
unsigned long long c;

int main(void) {
	int n;

	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		int x;
		scanf("%d", &x);
		if (i == 0) {
			depths[x] = 0;
		}
		else {
			set<int>::iterator ub = keys.upper_bound(x);
			int left_depth = -1;
			int right_depth = -1;
			if (ub != keys.end()) { // x보다 큰 값 존재
				right_depth = depths[*ub];
			}
			if (ub != keys.begin()) {
				--ub;
			}
			left_depth = depths[*ub];
			depths[x] = max(left_depth, right_depth) + 1;
			c += depths[x];
		}
		keys.insert(x);
		printf("%llu\n", c);
	}
}
