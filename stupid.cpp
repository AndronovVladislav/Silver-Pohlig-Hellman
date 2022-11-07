#include <iostream>
#include <cmath>

int stupid_pow(int a, int x, int radix) {
	int res = 1;
	for (int i = 0; i < x; ++i) {
		res *= a;
		res %= radix;
	}
	return res;
}

int main() {
	int b, y, radix;
    	std::cin >> b >> y >> radix;
	for (int i = 0; i < radix; ++i) {
		if (stupid_pow(b, i, radix) == y) {
			std::cout << i;
			break;
		}
	}
	return 0;
}
