#include <cassert>
#include <iostream>
#include "MyBigInt.h"
#include "zad3Fin.h"

int main()
{
	MyBigInt k{123};
	std::cout << k << std::endl;

	MyBigInt l = k;
	std::cout << l << std::endl;

	l = l + 1111;
	std::cout << l << std::endl;
	std::cout << k << std::endl;

	k = 13_mbi;
	std::cout << k << std::endl;

	MyBigInt m = 222232244629420445529739893461909967206666939096499764990979600_mbi;
	std::cout << m << std::endl;

	m = m + k;
	std::cout << m << std::endl;

	assert(m == 222232244629420445529739893461909967206666939096499764990979613_mbi);

	return 0;

}
