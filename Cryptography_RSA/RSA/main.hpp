
// TODO
// 3. prime generation.
// 4. bigintieger understanding 
// 5. bigintieger implementation
// 6. rewrite for block-key size encryption/decryption
// 7. simulation for text field
// 8. simulation for file
// 9. gui implementation


// Calculators
// divisors - https://www.hackmath.net/en/calculator/divisors
// factors - https://www.calculator.net/common-factor-calculator.html

// LIST OF PRIME NUMBERS
// https://en.wikipedia.org/wiki/List_of_prime_numbers

#include "../Framework.hpp"

#include <math.h>
#include <iostream>

#include "../bigint_n.h"
//#include "bigint.hpp"
#include "num.hpp"

// szyfrowanie		e * d mod(p) = 1
// deszyfrowanie	
// 1. p * q = n (1024b *1024b = 2048b)

namespace RSA {

	block GreatestCommonDivisor(
		IN Num a,
		IN Num b
	) {

		while (a != b) {
			if (a > b) a -= b;
			else b -= a;
		}

		return a;
	}

	block CalculatePhi(
		IN const Num& p,
		IN const Num& q
	) {
		return (p - 1) * (q - 1);
	}

	block NumCalculateE(
		IN const Num& phi
	) {
		Num e = 3;

		//while (e < phi) {
		//	Num temp = GreatestCommonDivisor(e, phi);
		//	if (temp == Num(1)) break;
		//	else e += 2;
		//}

		while (e.gcd(e, phi) != 1) e+= 2;

		//while (GreatestCommonDivisor(e, phi) != 1) e += 2;
		// TERMINATE IF E IS >= PHI
		if (e >= phi) exit(-1);

		return e;
	}

	block CalculateD(
		IN const Num phi,
		IN const Num e
	) {
		Num result;
		Num k = 1;

		// Jeœli nie mamy liczby ca³kowitej to musimy zwiêkszaæ t¹ liczbê.
		while (((k * phi) + Num(1)) % e != Num(0)) k += 1;

		result = ((k * phi) + Num(1)) / e;
		return result;
	}

	block GreatestCommonDivisor(
		IN bigint a,
		IN bigint b
	) {

		while (a != b) {
			if (a > b) a -= b;
			else b -= a;
		}

		return a;
	}

	block CalculatePhi(
		IN const bigint& p,
		IN const bigint& q
	) {
		return (p - 1) * (q - 1);
	}

	block CalculateE(
		IN const bigint& phi
	) {
		bigint e = 2;

		while (e < phi) {
			bigint temp = GreatestCommonDivisor(e, phi);
			if (temp == bigint(1)) break;
			else e += 1;
		}

		return e;
	}

	block CalculateD(
		IN const bigint phi,
		IN const bigint e
	) {
		bigint result;
		bigint k = 1;

		// Jeœli nie mamy liczby ca³kowitej to musimy zwiêkszaæ t¹ liczbê.
		while (((k * phi) + bigint(1)) % e != bigint(0)) k += 1;

		result = ((k * phi) + bigint(1)) / e;
		return result;
	}

	block GreatestCommonDivisor(
		IN uint64 a,
		IN uint64 b
	) {

		while (a != b) {
			if (a > b) a -= b;
			else b -= a;
		}

		return a;
	}

	block CalculatePhi(
		IN const uint64& p,
		IN const uint64& q
	) {
		return (p - 1) * (q - 1);
	}
	
	

	// - it has to be prime
	// - higher then 1
	// - lower then phi
	// - no same cooperatives with phi different then 1 and phi itself
	block CalculateE(
		IN const uint64& phi
	) {
		uint64 e = 2;

		//while (e < phi) {
		//	uint64 temp = GreatestCommonDivisor(e, phi);
		//	if (temp == 1) break;
		//	else e++;
		//}

		while (GreatestCommonDivisor(e, phi) != 1) e++;
		// TERMINATE IF E IS >= PHI
		if (e >= phi) exit(-1);

		return e;
	}
	
	block CalculateD(
		IN const uint64 phi,
		IN const uint64 e
	) {
		uint64 result;
		uint64 k = 1;

		// Jeœli nie mamy liczby ca³kowitej to musimy zwiêkszaæ t¹ liczbê.
		while (((k * phi) + 1) % e != 0) k++;

		result = ((k * phi) + 1) / e;
		return result;
	}

	block IsPrime(uint64 number) {
		for (uint64 a = 2; a < number; ++a)
			if (number % a == 0) return false;
		return true;
	}

	//int main() {
	//	for (int currentNum = 2; ; currentNum++) {
	//		if (isPrime(currentNum)) {
	//			std::cout << currentNum << " ";
	//		}
	//	}
	//}

	block GeneratePrime() {
		for (int current = 2;; ++current) {
			if (IsPrime(current)) {
				std::cout << current << " ";
			}
		}
	}
	

	// e, n - private key
	
	block Test1() {
		wchar buffor[256];
	
		// p, q, n, phi, e, d
		uint64 p = 11, q = 19;
		uint64 n = p * q;
		uint64 phi = CalculatePhi(p, q);
		uint64 e = CalculateE(phi);		// encryption
		uint64 d = CalculateD(phi, e);	// decryption

		// encryption
		uint64 nocrypted = 9;//0b0000'1111;

		swprintf_s(buffor, L"%llu", nocrypted);
		MessageBoxW(nullptr, buffor, L"LOGGER NOCRYPTED", MB_OK);

		uint64 k1a = pow(nocrypted, e);
		uint64 encrypted = fmod(k1a, n);

		swprintf_s(buffor, L"%llu", encrypted);
		MessageBoxW(nullptr, buffor, L"LOGGER ENCRYPTED", MB_OK);

		// decryption
		uint64 k1b = pow(encrypted, d);
		uint64 decrypted = fmod(k1b, n);

		swprintf_s(buffor, L"%llu", decrypted);
		MessageBoxW(nullptr, buffor, L"LOGGER DECRYPTED", MB_OK);
	
		return 0;
	}

	//block Test2() {
	//
	//	// p, q, n, phi, e, d
	//	BigInt p = 11, q = 19;
	//	BigInt n = p * q;
	//	BigInt phi = CalculatePhi(p, q);
	//	BigInt e = CalculateE(phi);		// encryption
	//	BigInt d = CalculateD(phi, e);	// decryption
	//	
	//	// encryption
	//	BigInt nocrypted = 9;//0b0000'1111;
	//
	//	//swprintf_s(buffor, L"%llu", nocrypted);
	//	//MessageBoxW(nullptr, buffor, L"LOGGER NOCRYPTED", MB_OK);
	//
	//	BigInt k1a = BigInt(10).pow(e);
	//	//BigInt k1a = pow(nocrypted, e);
	//	BigInt encrypted = fmod(k1a, n);
	//
	//	//swprintf_s(buffor, L"%llu", encrypted);
	//	//MessageBoxW(nullptr, buffor, L"LOGGER ENCRYPTED", MB_OK);
	//
	//	// decryption
	//	BigInt k1b = pow(encrypted, d);
	//	BigInt decrypted = fmod(k1b, n);
	//
	//	//swprintf_s(buffor, L"%llu", decrypted);
	//	//MessageBoxW(nullptr, buffor, L"LOGGER DECRYPTED", MB_OK);
	//
	//}

	block Test2() {

		std::vector<char> buffor;

		// p, q, n, phi, e, d
		bigint p = 109, q = 163;
		bigint n = p * q;
		bigint phi = CalculatePhi(p, q);
		bigint e = CalculateE(phi);		// encryption
		bigint d = CalculateD(phi, e);		// decryption

		//e.print(buffor);
		//MessageBoxA(nullptr, buffor.data(), "LOGGER E", MB_OK);
		
		bigint nocrypted = 59;//0b0000'1111;
		//nocrypted.set_neg(false);
		//nocrypted.neg = false;

		//nocrypted.print(buffor);
		//MessageBoxA(nullptr, buffor.data(), "LOGGER NOCRYPTED", MB_OK);

		// ENCRYPTION
		bigint encstep = bigint::_big_pow(nocrypted, e);
		bigint encrypted = encstep % n;
		//encrypted.set_neg(false);
		//encrypted.neg = false;

		//encrypted.print(buffor);
		//MessageBoxA(nullptr, buffor.data(), "LOGGER ENCRYPTED", MB_OK);

		// DECRYPTION
		bigint decstep = bigint::_big_pow(encrypted, d);
		bigint decrypted = decstep % n;
		//bigint decrypted = encrypted.mod_pow(d, n);
		//decrypted.set_neg(false);
		//decrypted.neg = false;
		//decrypted != decrypted;

		//decrypted.print(buffor);
		//MessageBoxA(nullptr, buffor.data(), "LOGGER DECRYPTED", MB_OK);

		if (decrypted == nocrypted)
			MessageBoxW(nullptr, L"YES", L"LOGGER FINAL", MB_OK);
		else 
			MessageBoxW(nullptr, L"NO", L"LOGGER FINAL", MB_OK);

		//swprintf_s(buffor, L"%llu", decrypted);
		//MessageBoxW(nullptr, buffor, L"LOGGER DECRYPTED", MB_OK);

	}

	block Test3() {

		std::vector<char> buffor;
		
		//1024b
		//1024b
		//2048b

		// p, q, n, phi, e, d
		
		//Num p = "257422187763775188257134387231", q = "268704472480766259262399638409";

		// 128bit
		//Num p = "340282366920938463463374607432841953291";
		//Num q = "340282366920938463463374607431768212629";

		// 256bit
		//Num p = "115792089237316195423570985008687907853269984665640564039457584007913130688523";
		//Num q = "115792089237316195423570985008687907853269984665640564039457584007914203382263";

		// 512bit
		//Num p = "13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084171";
		//Num q = "13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649007132903";

		// 1024bit
		Num p = "179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110541037861746687625057982134295314586803117506495636454552132846092481";
		Num q = "179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110540932549455019067871284216267630916370798611400235905440878535115721";

		//Num p = "109", q = "163"; // works
		//Num p = "3", q = "11";
		Num n = p * q;
		Num phi = CalculatePhi(p, q);
		Num e = NumCalculateE(phi);		// encryption
		Num d = CalculateD(phi, e);		// decryption

		//e.print(buffor);
		//MessageBoxA(nullptr, buffor.data(), "LOGGER E", MB_OK);

		std::vector<Num::word> words;
		words.push_back(53);
		Num nocrypted(words.begin()._Ptr, words.end()._Ptr);

		//std::string sample = "wololololo";
		//Num nocrypted(sample.front(), 10, sample.back());

		//Num nocrypted = 53; //"257422187763775188257134387232"; //0b0000'1111;
		//nocrypted.set_neg(false);
		//nocrypted.neg = false;

		//nocrypted.print(buffor);
		//MessageBoxA(nullptr, buffor.data(), "LOGGER NOCRYPTED", MB_OK);

		// ENCRYPTION
		Num encrypted = nocrypted.mod_pow(e, n);
		//encrypted.set_neg(false);
		//encrypted.neg = false;

		//encrypted.print(buffor);
		//MessageBoxA(nullptr, buffor.data(), "LOGGER ENCRYPTED", MB_OK);

		// DECRYPTION
		Num decrypted = encrypted.mod_pow(d, n);
		//decrypted.set_neg(false);
		//decrypted.neg = false;
		//decrypted != decrypted;

		decrypted.print(buffor);
		MessageBoxA(nullptr, buffor.data(), "LOGGER DECRYPTED", MB_OK);

		if (decrypted == nocrypted)
			MessageBoxW(nullptr, L"YES", L"LOGGER FINAL", MB_OK);
		else
			MessageBoxW(nullptr, L"NO", L"LOGGER FINAL", MB_OK);

		//swprintf_s(buffor, L"%llu", decrypted);
		//MessageBoxW(nullptr, buffor, L"LOGGER DECRYPTED", MB_OK);

	}

	block WcharsToUint64(
		OUT uint64& result,
		IN const wchar* data, 
		IN const size& dataCount = 4,
		IN const size& offset = 0
	) {
		result = data[offset];		// 16bits
		

		for (size i = 1; i < dataCount; ++i) {
			result <<= 16;
			result += data[offset + i];
		}
		
		//result <<= 16;
		//result += data[offset + 1];	// 32bits
		//result <<= 16;
		//result += data[offset + 2];	// 48bits
		//result <<= 16;
		//result += data[offset + 3];	// 64bits
	}

	block Uint64ToWchars(
		OUT std::vector<wchar_t>& result,
		IN const uint64& data,
		IN const size& dataCount = 4
	) {
		wchar_t temp = data >> 48;
		result.push_back(temp);

		for (size i = 1; i < dataCount; ++i) {
			temp = (data << (16 * i)) >> 48;
			result.push_back(temp);
		}

		
		//temp = (data << 32) >> 48;
		//result.push_back(temp);
		//temp = (data << 48) >> 48;
		//result.push_back(temp);
	}

	block Test4() {

		std::vector<char> buffor;

		//1024b
		//1024b
		//2048b

		// p, q, n, phi, e, d

		//Num p = "257422187763775188257134387231", q = "268704472480766259262399638409";

		// 128bit
		//Num p = "340282366920938463463374607432841953291";
		//Num q = "340282366920938463463374607431768212629";

		// 256bit
		//Num p = "115792089237316195423570985008687907853269984665640564039457584007913130688523";
		//Num q = "115792089237316195423570985008687907853269984665640564039457584007914203382263";

		// 512bit
		//Num p = "13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084171";
		//Num q = "13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649007132903";

		// 1024bit
		Num p = "179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110541037861746687625057982134295314586803117506495636454552132846092481";
		Num q = "179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110540932549455019067871284216267630916370798611400235905440878535115721";
		
		size nBitLength = 2048; // 1024 + 1024
		// 2048 / 16 = 128
		// czyli 1 block = 127 wcharów

		//Num p = "109", q = "163"; // works
		//Num p = "3", q = "11";
		Num n = p * q;
		Num phi = CalculatePhi(p, q);
		Num e = NumCalculateE(phi);		// encryption
		Num d = CalculateD(phi, e);		// decryption

		//e.print(buffor);
		//MessageBoxA(nullptr, buffor.data(), "LOGGER E", MB_OK);

		std::vector<wchar_t> inputData; // 16bit datatype
		//inputData.push_back(L'S');
		//inputData.push_back(L'A');
		//inputData.push_back(L'M');
		for (size i = 0; i < 126; ++i) {
			inputData.push_back(L'S');
		}
		inputData.push_back(L'\0');
		//inputData.push_back(L'L');
		//inputData.push_back(L'E');

		// WCHAR TO UINT64
		uint64 tempAdapter = 0;
		WcharsToUint64(tempAdapter, inputData.data());

		std::vector<Num::word> words; // 64bit datatype
		words.push_back(tempAdapter);
		Num nocrypted(words.begin()._Ptr, words.end()._Ptr);
		//Num nocrypted = 53; //"257422187763775188257134387232"; //0b0000'1111;

		//nocrypted.print(buffor);
		//MessageBoxA(nullptr, buffor.data(), "LOGGER NOCRYPTED", MB_OK);

		// ENCRYPTION
		Num encrypted = nocrypted.mod_pow(e, n);

		//encrypted.print(buffor);
		//MessageBoxA(nullptr, buffor.data(), "LOGGER ENCRYPTED", MB_OK);

		// DECRYPTION
		Num decrypted = encrypted.mod_pow(d, n);

		//decrypted.print(buffor);
		//MessageBoxA(nullptr, buffor.data(), "LOGGER DECRYPTED", MB_OK);

		// UINT64 TO WCHAR
		std::vector<wchar_t> outputData;
		for (size i = 0; i < decrypted.words.size(); ++i) {
			Uint64ToWchars(outputData, decrypted.words[i]);
		}
		

		MessageBoxW(nullptr, outputData.data(), L"LOGGER DATA", MB_OK);

		if (decrypted == nocrypted)
			MessageBoxW(nullptr, L"YES", L"LOGGER FINAL", MB_OK);
		else
			MessageBoxW(nullptr, L"NO", L"LOGGER FINAL", MB_OK);

		//swprintf_s(buffor, L"%llu", decrypted);
		//MessageBoxW(nullptr, buffor, L"LOGGER DECRYPTED", MB_OK);

	}

}