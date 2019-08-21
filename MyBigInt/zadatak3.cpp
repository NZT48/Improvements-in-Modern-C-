#include <cassert>
#include <iostream>
#include "MyBigInt.h"
//#include "zad3Fin.h"

MyBigInt fibo(int n) {
	MyBigInt a(0), b(1), c(0);
	//if( n == 0)
	//	return a;

	for(int i = 1; i < n; i++ ){
		c = a + b;
		//std::cout << "C = " << a << " + " << b << std::endl;
		a = std::move(b);
		//b = std::move(c);
		//a = b;
		b = c;
	}
	return c;
}


int main()
{
	MyBigInt k{123};
	std::cout << k << std::endl;

	k = fibo(9);
	//k = 8 + 13;
	std::cout << k << std::endl;

	k = k + 5;
	std::cout << k << std::endl;

	k = 7 + fibo(11);
	std::cout << k << std::endl;

	k = 13_mbi;
	std::cout << k << std::endl;

	MyBigInt l = fibo(300);
	if (l != 222232244629420445529739893461909967206666939096499764990979600_mbi) {
		std::cout << "Greska!" << std::endl;
		return 1;
	}
	std::cout << l << std::endl;

	{
		MyBigInt m = l;
		std::cout << m << std::endl;
	}
	std::cout << l << std::endl;

	{
		MyBigInt n = std::move(l);
		std::cout << n << std::endl;
	}

	MyBigInt::PrintCounters();

	return 0;
}
