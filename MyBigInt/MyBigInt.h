#ifndef __MY_BIG_INT__
#define __MY_BIG_INT__

#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <memory>

class MyBigInt {
public:
	static int destrCnt;
	static int moveConstrCnt;
	static int copyConstrCnt;
	static int moveEqCnt;
	static int copyEqCnt;

	MyBigInt() = default;
	MyBigInt(const char* num);
	MyBigInt(int num);
	MyBigInt(const MyBigInt& mbi);
	MyBigInt(MyBigInt&& mbi);
	MyBigInt(size_t sz);
	~MyBigInt();

	MyBigInt& operator= (const MyBigInt& mbi);
	MyBigInt& operator= (MyBigInt&& mbi);
	friend MyBigInt& operator+ (const MyBigInt& mbiA, const MyBigInt& mbiB);
	bool operator== (const MyBigInt& mbi) const;
	bool operator!= (const MyBigInt& mbi) const;
	friend std::ostream& operator<< (std::ostream& os, MyBigInt& mbi);

	static void PrintCounters();

private:

	std::unique_ptr<int8_t[]> digits;
	size_t size = 0;
};

MyBigInt operator""_mbi(const char* t);

#endif
