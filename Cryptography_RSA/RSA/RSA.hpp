// Calculators
// divisors - https://www.hackmath.net/en/calculator/divisors
// factors - https://www.calculator.net/common-factor-calculator.html

// LIST OF PRIME NUMBERS
// https://en.wikipedia.org/wiki/List_of_prime_numbers

// NOTES
// szyfrowanie		e * d mod(p) = 1
// deszyfrowanie	
// 1. p * q = n (1024b *1024b = 2048b)

// To generate primes
// https://www.wolframalpha.com/input?i=NextPrime%5B2%5E128+%2B+2%5E10%5D // 128 prime
// https://www.wolframalpha.com/input?i=NextPrime%5B2%5E256+%2B+2%5E10%5D // 256 prime
// https://www.wolframalpha.com/input?i=NextPrime%5B2%5E512+%2B+2%5E10%5D // 512 prime
// https://www.wolframalpha.com/input?i=NextPrime%5B2%5E1024%2B+2%5E10%5D // 1024 prime

#pragma once
#include <math.h>
#include <iostream>
#include <tuple>

#include "../Framework.hpp"
#include "Utility.hpp"
#include "num.hpp"

namespace RSA {

	const size wcharsInUint64 = 4;

	Num g_p, g_q, g_n, g_phi, g_e, g_d;

	//struct RSAp {
	//	Num p, q, n, phi, e, d;
	//};

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
		IN const Num& phi,
		IN const Num& min = 3
	) {
		Num e = min;

		while (e.gcd(e, phi) != 1) e += 2;

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
	}

	block Uint64ToWchars(
		OUT wchar* result,
		IN const uint64& data,
		IN const size& resultOffset = 0,
		IN const size& dataCount = 4
	) {
		wchar_t temp = data >> 48;
		result[resultOffset] = temp;

		for (size i = 1; i < dataCount; ++i) {
			temp = (data << (16 * i)) >> 48;
			result[resultOffset + i] = temp;
		}
	}

	namespace RSA256 {

		// 128 + 128
		Num p = "340282366920938463463374607432841953291";
		Num q = "340282366920938463463374607431768212629";
		const wchar* const p_str = L"340282366920938463463374607432841953291";
		const wchar* const q_str = L"340282366920938463463374607431768212629";

		const size nBitLength = 256; // 1024 + 1024
		const size blockSizeWchar = 16 - 4;
		const size blockSizeUint = 4 - 1;
		const size encodedBlockSizeUint = 4;
		//const size blockSizeWchar = 32 - 4;
		//const size blockSizeUint = 8 - 1;
		//const size encodedBlockSizeUint = 8;

	}

	namespace RSA512 {

		// 256 + 256
		Num p = "115792089237316195423570985008687907853269984665640564039457584007913130688523";
		Num q = "115792089237316195423570985008687907853269984665640564039457584007914203382263";
		const wchar* const p_str = L"115792089237316195423570985008687907853269984665640564039457584007913130688523";
		const wchar* const q_str = L"115792089237316195423570985008687907853269984665640564039457584007914203382263";

		const size nBitLength = 512; // 1024 + 1024
		const size blockSizeWchar = 32 - 4;
		const size blockSizeUint = 8 - 1;
		const size encodedBlockSizeUint = 8;
		//const size blockSizeWchar = 64 - 4;
		//const size blockSizeUint = 16 - 1;
		//const size encodedBlockSizeUint = 16;

	}

	namespace RSA1024 {

		// 512 + 512
		Num p = "13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084171";
		Num q = "13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649007132903";
		const wchar* const p_str = L"13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084171";
		const wchar* const q_str = L"13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649007132903";

		const size nBitLength = 1024; // 1024 + 1024
		const size blockSizeWchar = 64 - 4;
		const size blockSizeUint = 16 - 1;
		const size encodedBlockSizeUint = 16;
		//const size blockSizeWchar = 128 - 4;
		//const size blockSizeUint = 32 - 1;
		//const size encodedBlockSizeUint = 32;

	}

	namespace RSA2048 {

		// 1024 + 1024
		const Num p = "179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110541037861746687625057982134295314586803117506495636454552132846092481";
		const Num q = "179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110540932549455019067871284216267630916370798611400235905440878535115721";
		const wchar* const p_str = L"179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110541037861746687625057982134295314586803117506495636454552132846092481";
		const wchar* const q_str = L"179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110540932549455019067871284216267630916370798611400235905440878535115721";

		const size nBitLength = 2048; // 1024 + 1024
		const size blockSizeWchar = 128 - 4;
		const size blockSizeUint = 32 - 1;
		const size encodedBlockSizeUint = 32;
		//const size blockSizeWchar = 256 - 4;
		//const size blockSizeUint = 64 - 1;
		//const size encodedBlockSizeUint = 64;

	}

	using ret = std::tuple<wchar*, size>;

	block Generate(
		IN const Num& p,
		IN const Num& q
	) {
		std::vector<char> buffor;

		g_p = p;
		g_q = q;
		g_n = g_p * g_q;
		g_phi = CalculatePhi(g_p, g_q);
		g_e = NumCalculateE(g_phi, 65537);	// encryption
		g_d = CalculateD(g_phi, g_e);		// decryption

		//g_n.print(buffor);
		//MessageBoxA(nullptr, buffor.data(), "N", MB_OK);
		//g_e.print(buffor);
		//MessageBoxA(nullptr, buffor.data(), "E", MB_OK);
		//g_d.print(buffor);
		//MessageBoxA(nullptr, buffor.data(), "D", MB_OK);
	}

	block FileToWchars(
		OUT std::vector<wchar>& buffor,
		IN const wchar* const inputFilepath
	) {
		std::vector<byte> readData(FileIO::Read::File(inputFilepath));

		if (readData.size() == 0)
			return -1;

		const uint64 bytesInWchar = 2;
		const uint64 length = readData.size() / bytesInWchar;
		const uint64 left = readData.size() % bytesInWchar;

		for (size i = 0; i < length; ++i) {
			wchar temp = readData[i * bytesInWchar];
			temp <<= 8;
			temp += readData[(i * bytesInWchar) + 1];
			buffor.push_back(temp);
		}

		if (left) {
			wchar temp = readData[(length * bytesInWchar)];
			buffor.push_back(temp << 8);
		}

		return 0;

	}

	//block BytesToFile() {
	//
	//}

	block WcharsToFile(
		IN const wchar* const buffor,
		IN const size& bufforLength,
		IN const wchar* const outputFilepath
	) {
		std::vector<byte> writeData;

		const uint64 bytesInWchar = 2;
		const uint64 lastElementPos = bufforLength - 1;
		auto& lastElement = buffor[lastElementPos];

		for (size i = 0; i < lastElementPos; ++i) {
			uint8 temp = buffor[i] >> 8;
			writeData.push_back(temp);
			temp = buffor[i];
			writeData.push_back(temp);
		}

		if (lastElement <= 0b0000'0000'1111'1111) {
			writeData.push_back(lastElement);
		} else {
			writeData.push_back(lastElement >> 8);
		}

		FileIO::Write::File(outputFilepath, writeData.size(), writeData.data());
	}

	block Encrypt(
		IN const wchar* const inputData,
		IN const size& inputDataLength,
		IN const size& blockSizeWchar,
		IN const size& blockSizeUint
	) {
		std::vector<Num> blocks;
		std::vector<Num::word> words; // 64bit datatype

		const auto& wordsLength = inputDataLength / blockSizeWchar;
		const auto& wordsLeftLength = inputDataLength % blockSizeWchar;

		// We're packing those into uint64 therefore we need packs of 4 x 16 wchars.
		const auto& l4Length = wordsLeftLength / wcharsInUint64;
		const auto& l4LeftLength = wordsLeftLength % wcharsInUint64;

		// Block of data
		for (size i = 0; i < wordsLength; ++i) { // Block of data

			for (size j = 0; j < blockSizeUint; ++j) {
				const auto& bufforPtr = inputData;
				uint64 tempAdapter = 0;
				WcharsToUint64(tempAdapter, inputData, wcharsInUint64, (i * blockSizeWchar) + (j * wcharsInUint64));
				words.push_back(tempAdapter);
			}

			blocks.push_back(Num(words.begin()._Ptr, words.end()._Ptr));
			words.clear(); // It is possible to write it better without clear...
		}

		if (wordsLeftLength) { // Last Block (left bytes)

			uint64 bufforPosition = wordsLength * blockSizeWchar;

			// Cpy left bytes of 4's
			for (size i = 0; i < l4Length; ++i) {
				uint64 tempAdapter = 0;
				WcharsToUint64(tempAdapter, inputData, wcharsInUint64, bufforPosition + (i * wcharsInUint64));
				words.push_back(tempAdapter);
			}

			if (l4LeftLength) { // Cpy left bytes of rest
				uint64 tempAdapter = 0;
				WcharsToUint64(tempAdapter, inputData, l4LeftLength, bufforPosition + (l4Length * wcharsInUint64));
				words.push_back(tempAdapter);
			}

			blocks.push_back(Num(words.begin()._Ptr, words.end()._Ptr));
		}

		// Encryption
		std::vector<Num> encryptedBlocks;
		for (size i = 0; i < blocks.size(); ++i) {
			Num nocrypted(blocks[i]);
			Num encrypted = nocrypted.mod_pow(g_e, g_n);
			encryptedBlocks.push_back(encrypted);
		}

		{ // WriteToWchars 16bit
			std::vector<WBuffor> results;
			for (size i = 0; i < encryptedBlocks.size(); ++i) {
				Uint64sToWstring(results, encryptedBlocks[i].words);
			}

			{ // std::vector<WBuffor> TO wchars
				wchar* outputData = nullptr;
				size dataSize = 0;

				{ // GET LENGTH;
					const size length = wBufforLength * results.size();
					dataSize = length + 1;
					outputData = new wchar[dataSize];
				}

				WstringsToWstring(outputData, dataSize, results);
				//return outputData;
				return ret(outputData, dataSize);
			}
		}

	}

	block Decrypt(
		IN std::vector<wchar>& outputData,
		IN const wchar* const inputData,
		IN const size& inputDataLength,
		IN const size& encodedBlockSizeUint
	) {
		std::vector<Num> readblocks;
		std::vector<Num::word> readWords;

		WstringToUint64s(readWords, inputData, inputDataLength);

		const uint64 rblocks = readWords.size() / encodedBlockSizeUint;
		const uint64 rleft = readWords.size() % encodedBlockSizeUint;

		for (size i = 0; i < rblocks; ++i) {
			const auto& begin = readWords.data() + (i * encodedBlockSizeUint);
			const auto& end = begin + encodedBlockSizeUint;
			readblocks.push_back(Num(begin, end));
		}

		if (rleft) {
			const auto& begin = readWords.data() + (rblocks * encodedBlockSizeUint);
			const auto& end = begin + rleft;
			readblocks.push_back(Num(begin, end));
		}

		{ // Decription

			// Decription
			std::vector<Num> decryptedBlocks;
			for (size i = 0; i < readblocks.size(); ++i) {
				Num decrypted = readblocks[i].mod_pow(g_d, g_n);
				decryptedBlocks.push_back(decrypted);
			}

			// BigInts into Wchars
			const uint64 lastDecryptedBlock = decryptedBlocks.size() - 1;
			for (size i = 0; i < lastDecryptedBlock; ++i) {
				for (size j = 0; j < decryptedBlocks[i].words.size(); ++j) {
					Uint64ToWchars(outputData, decryptedBlocks[i].words[j]);
				}
			}

			{ // Last Block ....
				const uint64 lastDecryptedBlockWords = decryptedBlocks[lastDecryptedBlock].words.size() - 1;
				for (size i = 0; i < lastDecryptedBlockWords; ++i) {
					Uint64ToWchars(outputData, decryptedBlocks[lastDecryptedBlock].words[i]);
				}

				// Last Word ....
				uint64 masks[] {
					0b0000'0000'0000'0000'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111,
					0b0000'0000'0000'0000'0000'0000'0000'0000'1111'1111'1111'1111'1111'1111'1111'1111,
					0b0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'1111'1111'1111'1111,
				};
				auto& tempValue = decryptedBlocks[lastDecryptedBlock].words[lastDecryptedBlockWords];
				size counter = 5;	// 0 iterations
				if (tempValue < masks[2]) {			// 4byte'y
					counter = 2;	// 3 iterations
				} else if (tempValue < masks[1]) {	// 3byte'y
					counter = 3;	// 2 iterations
				} else if (tempValue < masks[0]) {	// 2byte'y
					counter = 4;	// 1 iteration
				}
				for (int64 i = counter - 2; i >= 0; --i) {
					wchar tempChar = tempValue >> (i * 16); // 1, 0 a nie 2, 1
					//wchar tempChar = tempValue >> 16;
					outputData.push_back(tempChar);
				}
			}

			outputData.push_back(L'\0');

		}
	}
}