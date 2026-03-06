#include <iostream>
#include <map>
#include <string>
#include <iomanip>

using namespace std;

int main(void) {
	map<string, int> tree;
	string input;
	int cnt = 0;
	while (getline(cin, input)) {
		++tree[input];
		++cnt;
	}

	cout << fixed << setprecision(4);
	for (map<string, int>::iterator it = tree.begin(); it != tree.end(); ++it) {
		cout << it->first << ' ' << ((float)it->second / cnt * 100) << endl;
	}
}
