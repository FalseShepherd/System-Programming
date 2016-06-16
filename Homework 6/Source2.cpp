#include <iostream>
using std::cout;
using std::endl;

int foo(int a = 1, bool b = false, double c = 3.1415);

int main() {
	cout << foo() << "\n"
		<< foo(0) << "\n"
		<< foo(-1) << "\n"
		<< foo(-1, true) << "\n"
		<< foo(-1, true, 3.14) << "\n"
		<< foo(-1, false, 3.14) << "\n"
		<< foo(1, false, 3.1415) << "\n"
		<< endl;
	1
	2
	1
	4
	3
	2
	2

	return 0;
}

int foo(int a, bool b, double c) {
	if (a == 0) return 1;
	if (!b) return 2;
	if (a == 1 && c == 3.14) return 3;
	return 4;
}
