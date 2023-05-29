#pragma once

#include"BigInt.hpp"

class RSA {
public:
	RSA();
	~RSA();

	void Initialize(unsigned int n);

	BigInt EncryptByPu(const BigInt& m);
	BigInt DecryptByPr(const BigInt& c);

	BigInt EncryptByPr(const BigInt& m);
	BigInt DecryptByPu(const BigInt& m);

	BigInt CreateOddNumber(unsigned int n);
	bool IsPrime(const BigInt& a, const unsigned int k);
	BigInt CreatePrime(unsigned int n, int it_cout);
	void CreateExponent(const BigInt& ou);
	BigInt CreateRandomSmallThan(const BigInt& a);

	friend ostream& operator << (ostream& result, const RSA& rsa) {
		result << "N: " << rsa.N	<< "\n";
		result << "p: " << rsa.p	<< "\n"; // base encrypt
		result << "q: " << rsa.q	<< "\n"; // base decrypt
		result << "e: " << rsa.e	<< "\n"; // exponent encrypt
		result << "d: " << rsa.d;			 // exponent decrypt
		return result;
	}

	BigInt e, d, N, p, q, _ol;
};