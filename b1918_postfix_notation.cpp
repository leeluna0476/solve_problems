// A*(B+C) -> ABC+*
// A*(B+C*D+E)+F -> ABCD*+E+*F+
// A+(B+C*D+E)+F -> ABCD*+E++F+
// A+(B+C)*(D-E) -> ABC+DE-*+
// A+B+C*D*(E+F) -> AB+CD*EF+*+

#include <iostream>
#include <stack>
#include <string>
#include <cctype>

using namespace std;

int level(char c) {
	if (c == '(') {
		return 3;
	}
	else if (c == '*' || c == '/') {
		return 2;
	}
	else {
		return 1;
	}
}

// a > b
bool is_greater(char a, char b) {
	return a != '(' && level(a) >= level(b);
}

void generate_postfix_notation(string &s, string &result) {
	stack<char> operators;

	for (string::iterator i = s.begin(); i != s.end(); ++i) {
		if (isupper(*i)) {
			result.push_back(*i);
		}
		else {
			while (!operators.empty() && operators.top() != '(' && is_greater(operators.top(), *i)) {
				result.push_back(operators.top());
				operators.pop();
			}
			if (!operators.empty() && operators.top() == '(' && *i == ')') {
				operators.pop();
			}

			if (*i != ')') {
				operators.push(*i);
			}
		}
	}

	while (!operators.empty() && operators.top() != '(') {
		result.push_back(operators.top());
		operators.pop();
	}
}

int main(void) {
	string input, result;
	cin >> input;

	generate_postfix_notation(input, result);
	cout << result << endl;

	return 0;
}
