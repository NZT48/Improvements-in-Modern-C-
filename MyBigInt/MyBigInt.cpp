#include "MyBigInt.h"

int MyBigInt::destrCnt = 0;
int MyBigInt::moveConstrCnt = 0;
int MyBigInt::copyConstrCnt = 0;
int MyBigInt::moveEqCnt = 0;
int MyBigInt::copyEqCnt = 0;

MyBigInt ::MyBigInt(const char* num) {
	std::string nums(num);
	size = nums.length();
	digits = std::make_unique<int8_t[]>(size);
	for (int i = 0; i < size; i++){
		digits[i] = (int8_t)(num[i] - '0');
	}
}

MyBigInt::MyBigInt(int num) {
	std::string nums = std::to_string(num);
	size =  nums.length();
	digits = std::make_unique<int8_t[]>(size);
	for (int i = size-1; i >= 0; i--){
		digits[i] = (int8_t)(nums[i] - '0');
	}
}

MyBigInt::MyBigInt(const MyBigInt& mbi) {
	size = mbi.size;
	digits = std::make_unique<int8_t[]>(size);
	for (int i = 0; i < size; i++)
		digits[i] = mbi.digits[i];
	copyConstrCnt++;
}

MyBigInt::MyBigInt(MyBigInt&& mbi) {
	size = mbi.size;
	mbi.size = 0;
	digits = std::move(mbi.digits);
	mbi.digits = nullptr;
	moveConstrCnt++;
}

MyBigInt& MyBigInt::operator=(const MyBigInt& mbi)  {
		if (this != &mbi) {
			if (mbi.size != size) {
				size = mbi.size;
				digits = std::make_unique<int8_t[]>(size);
			}
			for (int i = 0; i < size; i++)
				digits[i] = mbi.digits[i];
		}
		copyEqCnt++;
		return *this;
}

MyBigInt& MyBigInt::operator= (MyBigInt&& mbi) {
	size = mbi.size;
	mbi.size = 0;
	digits = std::move(mbi.digits);
	mbi.digits = nullptr;
	moveEqCnt++;
}


MyBigInt::~MyBigInt() {
	destrCnt++;
}

MyBigInt::MyBigInt(size_t sz) {
	this->size = sz;
	this->digits = std::make_unique<int8_t[]>(sz);
}

MyBigInt& operator+ (const MyBigInt& mbiA, const MyBigInt& mbiB)  {
	bool first_case = false;
	int8_t* tmp_digits = nullptr;

	if (mbiA.size > mbiB.size) {
		first_case = true;
		tmp_digits = new int8_t[mbiA.size];
		for (int i = 0; i < mbiA.size - mbiB.size; i++)
			tmp_digits[i] = 0;
		for (int i = mbiA.size - mbiB.size, j = 0; i < mbiA.size; i++, j++)
			tmp_digits[i] = mbiB.digits[j];
	} else {
		tmp_digits = new int8_t[mbiB.size];
		for (int i = 0; i < mbiB.size - mbiA.size; i++)
			tmp_digits[i] = 0;
		for (int i = mbiB.size - mbiA.size, j = 0; i < mbiB.size; i++, j++)
			tmp_digits[i] = mbiA.digits[j];
	}

	int8_t carry = 0;
	int8_t* new_big_int = new int8_t[std::max(mbiA.size, mbiB.size)];


	for (int i = std::max(mbiA.size, mbiB.size) - 1; i >= 0; i--) {
		if (first_case) {
			int8_t tmp_d = mbiA.digits[i] + tmp_digits[i] + carry;
			if (tmp_d > 9) carry = 1;
			else carry = 0;
			new_big_int[i] = tmp_d % 10;
		} else {
			int8_t tmp_d = mbiB.digits[i] + tmp_digits[i] + carry;
			if (tmp_d > 9) carry = 1;
			else carry = 0;
			new_big_int[i] = tmp_d % 10;
		}
	}

	MyBigInt* ret_val = nullptr;
	size_t new_size;

	if((int)carry == 1) {
		new_size = std::max(mbiA.size, mbiB.size) + 1;
		ret_val = new MyBigInt(new_size);
			for (int i = std::max(mbiA.size, mbiB.size)+1; i > 0; i--) {
				ret_val->digits[i] = new_big_int[i-1];
			}
		ret_val->digits[0] = 1;
		return *ret_val;
	}

	new_size = std::max(mbiA.size, mbiB.size);
	ret_val = new MyBigInt(new_size);
	for (int i = new_size-1; i >= 0; i--) {
			ret_val->digits[i] = new_big_int[i];
	}

	return *ret_val;
}


bool MyBigInt::operator== (const MyBigInt& mbi) const {
	if (size != mbi.size)
		return false;
	for (int i = 0; i < size; i++)
		if (digits[i] != mbi.digits[i])
			return false;
	return true;
}

bool MyBigInt::operator!= (const MyBigInt& mbi) const {
	return !(*this == mbi);
}


std::ostream& operator<< (std::ostream& out, MyBigInt& mbi) {
	for(int i = 0; i < mbi.size;  i++)
		out << (char) (mbi.digits[i] + '0');
	return out;
}

MyBigInt operator""_mbi(const char *t) {
	MyBigInt mbi = MyBigInt(t);
	return mbi;
}

void MyBigInt::PrintCounters() {
		std::cout << "Number of move constructor calls " << MyBigInt::moveConstrCnt << std::endl;
		std::cout << "Number of move operator = calls " << MyBigInt::moveEqCnt << std::endl;
		std::cout << "Number of copy constructor calls " << MyBigInt::copyConstrCnt << std::endl;
		std::cout << "Number of copy operator = calls " << MyBigInt::copyEqCnt << std::endl;
		std::cout << "Number of destructor calls " << MyBigInt::destrCnt << std::endl;

}
