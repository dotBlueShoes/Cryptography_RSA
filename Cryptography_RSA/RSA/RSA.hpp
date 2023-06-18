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
		IN const Num& phi
	) {
		Num e = 3;

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

	}

	//block Decrypt2048(
	//	OUT wchar* outputBuffor,
	//	IN const wchar* const inputBuffor,
	//	IN const size& inputBufforLength,
	//	IN const HWND& output
	//) {
	//
	//	std::vector<Num> encryptedBlocks;
	//	std::vector<Num::word> words;
	//	char buffor[256] { 0 };
	//
	//	const auto& encodedBlockSizeUint = RSA2048::encodedBlockSizeUint;
	//
	//	const uint64 length = inputBufforLength / wcharsInUint64;
	//	const uint64 lengthLeft = inputBufforLength % wcharsInUint64;
	//	const uint64 length32 = length / encodedBlockSizeUint;
	//	const uint64 length32Left = length % encodedBlockSizeUint;
	//
	//	{ // FOR NOW DISPLAY IN MESSAGE BOXES !
	//
	//		for (size i = 0; i < length32; ++i) {
	//			for (size j = 0; j < encodedBlockSizeUint; ++j) {
	//				uint64 tempAdapter = 0;
	//				WcharsToUint64(tempAdapter, inputBuffor, wcharsInUint64, (i * encodedBlockSizeUint) + (j * wcharsInUint64));
	//				//sprintf_s(buffor, 256, "%llu", tempAdapter);
	//				//MessageBoxA(nullptr, buffor, "LOGGER ENCRYPTED", MB_OK);
	//				words.push_back(tempAdapter);
	//			}
	//
	//			encryptedBlocks.push_back(Num(words.begin()._Ptr, words.end()._Ptr));
	//			words.clear();
	//		}
	//
	//		if (length32Left) {
	//			for (size i = 0; i < length32Left; ++i) {
	//				uint64 tempAdapter = 0;
	//				WcharsToUint64(tempAdapter, inputBuffor, wcharsInUint64, (encodedBlockSizeUint * wcharsInUint64) + (i * wcharsInUint64));
	//				//sprintf_s(buffor, 256, "%llu", tempAdapter);
	//				//MessageBoxA(nullptr, buffor, "LOGGER ENCRYPTED", MB_OK);
	//				words.push_back(tempAdapter);
	//			}
	//
	//			encryptedBlocks.push_back(Num(words.begin()._Ptr, words.end()._Ptr));
	//			words.clear();
	//		}
	//
	//		//std::cout << inputBuffor[(32 * 4) + (13 * 4)];
	//		//std::cout << inputBuffor[(32 * 4) + (13 * 4) + 1];
	//		//std::cout << inputBuffor[(32 * 4) + (13 * 4) + 2];
	//
	//		//if (lengthLeft) {
	//		//	uint64 tempAdapter = 0;
	//		//	WcharsToUint64(tempAdapter, inputBuffor, lengthLeft, 0);
	//		//	words.push_back(tempAdapter);
	//		//	encryptedBlocks.push_back(Num(words.begin()._Ptr, words.end()._Ptr));
	//		//	words.clear();
	//		//}
	//
	//		//1 { // last uint
	//		//1 	uint64 tempAdapter = 0;
	//		//1 	//tempAdapter += inputBuffor[(encodedBlockSizeUint * wcharsInUint64) + (length32Left * wcharsInUint64)];
	//		//1 	//tempAdapter <<= 16;
	//		//1 	//tempAdapter += inputBuffor[(encodedBlockSizeUint * wcharsInUint64) + (length32Left * wcharsInUint64) + 1];
	//		//1 	//tempAdapter <<= 16;
	//		//1 	//tempAdapter += inputBuffor[(encodedBlockSizeUint * wcharsInUint64) + (length32Left * wcharsInUint64) + 2];
	//		//1 	//tempAdapter <<= 16;
	//		//1 	//tempAdapter <<= 16;
	//		//1 	//tempAdapter += inputBuffor[(32 * 4) + (13 * 4) + 3];
	//		//1 	WcharsToUint64(tempAdapter, inputBuffor, lengthLeft, (encodedBlockSizeUint * wcharsInUint64));
	//		//1 	words.push_back(tempAdapter);
	//		//1 }
	//		
	//		//words[14] >>= 16;
	//		
	//	}
	//
	//	// Last uint64 has to be moved by 16 bytes >> ...
	//	//  that information has to be kept.
	//
	//	// Decription
	//	std::vector<Num> decryptedBlocks;
	//	for (size i = 0; i < encryptedBlocks.size(); ++i) {
	//		Num decrypted = encryptedBlocks[i].mod_pow(g_d, g_n);
	//		decryptedBlocks.push_back(decrypted);
	//	}
	//
	//	//decryptedBlocks[decryptedBlocks.size() - 1].
	//
	//	std::vector<wchar_t> outputData;
	//	const uint64 lastDecryptedBlock = decryptedBlocks.size() - 1;
	//	// for blocks
	//	for (size i = 0; i < lastDecryptedBlock; ++i) {
	//		for (size j = 0; j < decryptedBlocks[i].words.size(); ++j) {
	//			Uint64ToWchars(outputData, decryptedBlocks[i].words[j]);
	//		}
	//	}
	//
	//	{ // last block ....
	//		const uint64 lastDecryptedBlockWords = decryptedBlocks[lastDecryptedBlock].words.size() - 1;
	//		// all words of last block except the very last one ...
	//		for (size i = 0; i < lastDecryptedBlockWords; ++i) {
	//
	//			//const auto& tempValue = decryptedBlocks[lastDecryptedBlock].words[i];
	//			//wchar tempChar = (wchar)(tempValue);
	//			//
	//			//for (int64 i = 4 - 1; i >= 0; --i) {
	//			//	wchar tempChar = (wchar)(tempValue << (i * 16));
	//			//	outputData.push_back(tempChar);
	//			//}
	//
	//			Uint64ToWchars(outputData, decryptedBlocks[lastDecryptedBlock].words[i]);
	//		}
	//
	//		//if (length32Left) { // last word
	//		//	//outputData.push_back(L'a');
	//
	//		// 4 ostatnie wchary....
	//		// to mo¿e byæ 1/2/3/4 wchary
	//		
	//		uint64 masks[] {
	//			0b0000'0000'0000'0000'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111,
	//			0b0000'0000'0000'0000'0000'0000'0000'0000'1111'1111'1111'1111'1111'1111'1111'1111,
	//			0b0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'1111'1111'1111'1111,
	//			//0b0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000,
	//		};
	//
	//			auto& tempValue = decryptedBlocks[lastDecryptedBlock].words[lastDecryptedBlockWords];
	//
	//			size counter = 1; // 1 byte
	//
	//			if (tempValue > masks[0]) {			// 4byte'y
	//				counter = 4;
	//			} else if (tempValue > masks[1]) {	// 3byte'y
	//				counter = 3;
	//			} else if (tempValue > masks[2]) {	// 2byte'y
	//				counter = 2;
	//			} 
	//
	//			for (int64 i = counter - 1; i >= 0; --i) {
	//				wchar tempChar = (wchar)(tempValue << (i * 16));
	//				outputData.push_back(tempChar);
	//			}
	//
	//		//	wchar tempChar = (wchar)(tempValue);
	//		//
	//		//	for (int64 i = length32Left - 1; i >= 0; --i) {
	//		//		wchar tempChar = (wchar)(tempValue << (i * 16));
	//		//		outputData.push_back(tempChar);
	//		//	}
	//		//
	//		//	//Uint64ToWchars(outputData, decryptedBlocks[lastDecryptedBlock].words[lastDecryptedBlockWords], 1); // TAM JEST TO 50 !!!!
	//		//	//outputData.push_back(L'a');
	//		//}
	//	}
	//
	//	outputData.push_back(L'\0');
	//
	//	//outputBuffor = new wchar[outputData.size()];
	//	SendMessageW(output, WM_SETTEXT, NULL, (LPARAM)outputData.data());
	//	//delete[] outputBuffor;
	//	
	//	
	//	// DEBUG
	//	//MessageBoxW(nullptr, outputData.data(), L"LOGGER OUTPUT DATA", MB_OK);
	//
	//}

	//block Encrypt2048(
	//	OUT wchar* outputBuffor,
	//	IN const wchar* const inputBuffor,
	//	IN const size& inputBufforLength,
	//	IN const HWND& output
	//) {
	//	std::vector<char> buffor;
	//
	//	std::vector<Num> blocks;
	//	std::vector<Num::word> words; // 64bit datatype builds a single block.
	//	std::vector<Num> encryptedBlocks;
	//
	//	const auto& blockSizeWchar = RSA2048::blockSizeWchar;
	//	const auto& blockSizeUint = RSA2048::blockSizeUint;
	//	const Num& p = RSA2048::p;
	//	const Num& q = RSA2048::q;
	//
	//	const auto& stringLength = inputBufforLength;
	//	const auto& wordsLength = stringLength / blockSizeWchar;
	//	const auto& wordsLeftLength = stringLength % blockSizeWchar;
	//	const auto& wordsZeroesLength = blockSizeWchar - wordsLeftLength;
	//
	//	// We're packing those into uint64 therefore we need packs of 4 x 16 wchars.
	//	const auto& l4Length = wordsLeftLength / wcharsInUint64;
	//	const auto& l4LeftLength = wordsLeftLength % wcharsInUint64;
	//	const auto& l4ZeroesLength = wcharsInUint64 - l4LeftLength;
	//
	//	{ /* Encapsulation */
	//		
	//		for (size i = 0; i < wordsLength; ++i) { // Block of data
	//
	//			for (size j = 0; j < blockSizeUint; ++j) {
	//				const auto& bufforPtr = inputBuffor + (wordsLength * i);
	//				uint64 tempAdapter = 0;
	//				WcharsToUint64(tempAdapter, bufforPtr, wcharsInUint64, j * wcharsInUint64);
	//				words.push_back(tempAdapter);
	//			}
	//
	//			blocks.push_back(Num(words.begin()._Ptr, words.end()._Ptr));
	//			words.clear(); // It is possible to write it better without clear...
	//		}
	//
	//		if (wordsLeftLength) { // Last Block (left bytes)
	//
	//			uint64 bufforPosition = wordsLength * blockSizeWchar;
	//
	//			// Cpy left bytes of 4's
	//			for (size i = 0; i < l4Length; ++i) {
	//				uint64 tempAdapter = 0;
	//				WcharsToUint64(tempAdapter, inputBuffor, wcharsInUint64, bufforPosition + (i * wcharsInUint64));
	//				words.push_back(tempAdapter);
	//			}
	//
	//			if (l4LeftLength) { // Cpy left bytes of rest
	//				uint64 tempAdapter = 0;
	//				WcharsToUint64(tempAdapter, inputBuffor, l4LeftLength, bufforPosition + (l4Length * wcharsInUint64));
	//				words.push_back(tempAdapter);
	//			}
	//
	//			// Fill with zeroes to whole blockSizeUint length.
	//			//for (size i = 0; i < wordsZeroesLength; ++i) {
	//			//	words.push_back(0);
	//			//}
	//
	//			blocks.push_back(Num(words.begin()._Ptr, words.end()._Ptr));
	//		}
	//
	//	}
	//
	//	// Encryption
	//	for (size i = 0; i < blocks.size(); ++i) {
	//		Num nocrypted(blocks[i]);
	//		Num encrypted = nocrypted.mod_pow(g_e, g_n);
	//		encryptedBlocks.push_back(encrypted);
	//
	//		encrypted.print(buffor);
	//		MessageBoxA(nullptr, buffor.data(), "LOGGER ENCRYPTED", MB_OK);
	//	}
	//
	//	uint64 encryptedLength = 0;
	//	for (size i = 0; i < encryptedBlocks.size(); ++i) {
	//		encryptedLength += encryptedBlocks[i].words.size();
	//	}
	//
	//	
	//	const auto encryptedWcharLength = encryptedLength * 4; // (32 + 15) * 4
	//	outputBuffor = new wchar[encryptedWcharLength + 1]; /* null-termination */
	//	
	//	//const auto& length = encryptedBlocks[0].words.size();
	//	//for (size j = 0; j < length; ++j) {
	//	//	Uint64ToWchars(outputBuffor, encryptedBlocks[0].words[j], (0 * length) + (j * 4));
	//	//}
	//
	//	uint64 lastPos = 0;
	//	const uint64 lastBlock = encryptedBlocks.size() - 1;
	//	// FOR EACH BLOCK BUT LAST ONE
	//	for (size i = 0; i < lastBlock; ++i) {
	//		const auto& length = encryptedBlocks[i].words.size();
	//		size j = 0;
	//
	//		for (; j < length; ++j) {
	//			Uint64ToWchars(outputBuffor, encryptedBlocks[i].words[j], lastPos + (j * 4));
	//		}
	//
	//		lastPos += j * 4;
	//	}
	//
	//	// Because 0000'0000.0000'0000
	//	//         1111'1111.1111'1111
	//	//		   1111'1111.1111'1111
	//	//		   1111'1111.1111.1111
	//	// could be our last Uint64.
	//	// it doesnt appear at the end when we're dealing with 32 words - result of 2048 encoding
	//	// but here last uint64 represents a number if the biginteger it represents is samller then whole
	//	// uint64 it might actually only set bits of few wchars leaving possibly 13-wchars as l'\0' !
	//
	//	// 1011'1101.1011'1000
	//	// 1100'0000.1111'1000
	//	// 0001'1001.0100'0000
	//	// 0000'0000.0000'0000
	//
	//	{ // Get last block to get last uint64
	//		const auto& lastLength = encryptedBlocks[lastBlock].words.size() - 1;
	//		for (size i = 0; i < lastLength; ++i) { // 12 + 
	//				Uint64ToWchars(outputBuffor, encryptedBlocks[lastBlock].words[i], lastPos + (i * 4));
	//		}
	//
	//		//lastPos += lastLength;
	//
	//		// i have 4 * 16 here but what now ?
	//		const uint64 masks[] {
	//			0b0000'0000'0000'0000'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111,
	//			0b0000'0000'0000'0000'0000'0000'0000'0000'1111'1111'1111'1111'1111'1111'1111'1111,
	//			0b0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'1111'1111'1111'1111
	//		};
	//
	//		//for (uint64 i = 0; lastLength < masks[0]; ++i) {
	//		//	encryptedBlocks[lastBlock].words[lastPos] <<= 16;
	//		//}
	//		auto& lastWord = encryptedBlocks[lastBlock].words[lastLength];
	//		if (lastWord < masks[0]) {
	//			lastWord <<= 16;
	//			MessageBoxA(nullptr, "1", "LOGGER", MB_OK);
	//		}
	//
	//		if (lastWord < masks[1]) {
	//			lastWord <<= 16;
	//			MessageBoxA(nullptr, "2", "LOGGER", MB_OK);
	//		} 
	//
	//		if (lastWord < masks[2]) {
	//			lastWord <<= 16;
	//			MessageBoxA(nullptr, "3", "LOGGER", MB_OK);
	//		} 
	//
	//		uint64 sample = lastPos + (lastLength * 4);
	//		Uint64ToWchars(outputBuffor, lastWord, sample);
	//
	//		// 1000'0000.1010'0111.1101'1100.1101'1001.0100'1010.1000'0010
	//
	//	//	const uint64 lastBlockSize = encryptedBlocks[lastBlock].size();
	//	//	const uint64 lbs4 = lastBlockSize / 4;
	//	//	const uint64 lbs4left = lastBlockSize % 4;
	//	//	size i = 0;
	//	//
	//	//	for (; i < lbs4 * 4; ++i) { // 12 + 
	//	//		Uint64ToWchars(outputBuffor, encryptedBlocks[lastBlock].words[i], lastPos + (i * 4));
	//	//	}
	//	//
	//	//	
	//	//
	//	//	//if (lbs4left) {
	//	//	//	lastPos += lbs4 * i * 4;
	//	//	//	Uint64ToWchars(outputBuffor, encryptedBlocks[lastBlock].words[lbs4 * 4], lastPos, lbs4left);
	//	//	//}
	//	//
	//	}
	//	
	//	outputBuffor[encryptedWcharLength] = L'\0';
	//
	//	//1 for (size i = 0; i < 47; ++i) { // 47
	//	//1 	uint64 adapter = 0;
	//	//1 	WcharsToUint64(adapter, outputBuffor, 4, i * 4);
	//	//1 	sprintf_s(buffor.data(), 256, "%llu", adapter);
	//	//1 	MessageBoxA(nullptr, buffor.data(), "LOGGER ENCRYPTED", MB_OK);
	//	//1 }
	//	
	//	SendMessageW(output, WM_SETTEXT, NULL, (LPARAM)outputBuffor);
	//	delete[] outputBuffor;
	//}

	using ret = std::tuple<wchar*, size>;

	block Generate(
		IN const Num& p,
		IN const Num& q
	) {
		g_p = p;
		g_q = q;
		g_n = g_p * g_q;
		g_phi = CalculatePhi(g_p, g_q);
		g_e = NumCalculateE(g_phi);			// encryption
		g_d = CalculateD(g_phi, g_e);		// decryption
	}

	block FileToWchars(
		OUT std::vector<wchar>& buffor,
		IN const wchar* const inputFilepath
	) {
		std::vector<byte> readData(FileIO::Read::File(inputFilepath));

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

	}

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