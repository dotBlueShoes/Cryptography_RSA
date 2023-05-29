#include "RSA.hpp"
#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>

RSA::RSA() {}

RSA::~RSA() {}

void RSA::Initialize(unsigned int keyLength) {
	srand(time(NULL));

	p = CreatePrime(keyLength, 10);
	q = CreatePrime(keyLength, 10);
	N = p * q;

	phi = (p - 1) * (q - 1);
	CreateExponent(phi);
}

BigInt RSA::CreateOddNumber(unsigned int keyLength) {

	keyLength /= 4;

	static unsigned char hex_table[] {
		'0','1','2','3',
		'4','5','6','7',
		'8','9','A','B',
		'C','D','E','F'
	};

	if (keyLength) {
		std::ostringstream oss;
		for (std::size_t i = 0; i < keyLength - 1; ++i)
			oss << hex_table[rand() % 16];

		oss << hex_table[1]; // Always odd numer.

		string str(oss.str());

		return BigInt(str);
	} else
		return BigInt::Zero;
}

bool RSA::IsPrime(const BigInt& n, const unsigned int k) {

	assert(n != BigInt::Zero);

	if (n == BigInt::Two)
		return true;

	BigInt n_1 = n - 1;
	BigInt::bit b(n_1);

	if (b.at(0) == 1)
		return false;

	for (std::size_t t = 0; t < k; ++t) {

		BigInt a = CreateRandomSmallThan(n_1);
		BigInt d (BigInt::One);

		for (int i = b.size() - 1; i >= 0; --i) {

			BigInt x = d;
			d = (d * d) % n;
			if (d == BigInt::One && x != BigInt::One && x != n_1)
				return false;

			if (b.at(i)) {
				assert(d != BigInt::Zero);
				d = (a * d) % n;
			}
		}

		if (d != BigInt::One)
			return false;
	}

	return true;
}

BigInt RSA::CreateRandomSmallThan(const BigInt& a) {
	unsigned long t = 0;

	do {
		t = rand();
	} while(t == 0);

	BigInt mod(t);
	BigInt r = mod % a;

	if (r == BigInt::Zero) 
		r = a - BigInt::One;

	return r;
}

BigInt RSA::CreatePrime(unsigned int keyLength, int count) {
	assert(count > 0);

	BigInt res = CreateOddNumber(keyLength);

	while (!IsPrime(res, count)) {
		res.add(BigInt::Two);
	}

	return res;
}

void RSA::CreateExponent(const BigInt& ou) {
	e = 65537;
	d = e.extendEuclid(ou);
}

BigInt RSA::EncryptByPu(const BigInt& m) {
	return m.moden(e, N);
}

BigInt RSA::DecryptByPr(const BigInt& c) {
	return c.moden(d, N);
}

BigInt RSA::EncryptByPr(const BigInt& m) {
	return DecryptByPr(m);
}

BigInt RSA::DecryptByPu(const BigInt& c) {
	return EncryptByPu(c);
}