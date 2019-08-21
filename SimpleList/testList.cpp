#include "SimpleList.h"

int main() {
	SimpleList head;

	head.add(2);
	head.add(4);
	head.add(6);
	head.add(8);
	head.add(10);

	for (int x : head) {
		std::cout << x << " ";
	}
	std::cout << std::endl;

	for (int& x : head) {
		x = x * x;
	}

	for (const int& x : head) {
		std::cout << x << " ";
	}
	std::cout << std::endl;

	return 0;
}
