// Calculators
// divisors - https://www.hackmath.net/en/calculator/divisors
// factors - https://www.calculator.net/common-factor-calculator.html

// LIST OF PRIME NUMBERS
// https://en.wikipedia.org/wiki/List_of_prime_numbers

// NOTES
// szyfrowanie		e * d mod(p) = 1
// deszyfrowanie	
// 1. p * q = n (1024b *1024b = 2048b)

#pragma once
#include <math.h>
#include <iostream>

#include "../Framework.hpp"
#include "num.hpp"

namespace RSA {

	const size wcharsInUint64 = 4;

	Num g_n, g_phi, g_e, g_d;

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

		const size nBitLength = 256; // 1024 + 1024
		const size blockSizeWchar = 16 - 4;
		const size blockSizeUint = 4 - 1;
	}

	namespace RSA512 {

		// 256 + 256
		Num p = "115792089237316195423570985008687907853269984665640564039457584007913130688523";
		Num q = "115792089237316195423570985008687907853269984665640564039457584007914203382263";

		const size nBitLength = 512; // 1024 + 1024
		const size blockSizeWchar = 32 - 4;
		const size blockSizeUint = 8 - 1;
	}

	namespace RSA1024 {

		// 512 + 512
		Num p = "13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084171";
		Num q = "13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649007132903";

		const size nBitLength = 1024; // 1024 + 1024
		const size blockSizeWchar = 64 - 4;
		const size blockSizeUint = 16 - 1;
	}

	namespace RSA2048 {

		// 1024 + 1024
		const Num p = "179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110541037861746687625057982134295314586803117506495636454552132846092481";
		const Num q = "179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110540932549455019067871284216267630916370798611400235905440878535115721";

		const size nBitLength = 2048; // 1024 + 1024
		const size blockSizeWchar = 128 - 4;
		const size blockSizeUint = 32 - 1;

	}

	block Decrypt2048(
		OUT wchar* outputBuffor,
		IN const wchar* const inputBuffor,
		IN const size& inputBufforLength,
		IN const HWND& output
	) {

		std::vector<Num> encryptedBlocks;
		std::vector<Num::word> words;
		char buffor[256] { 0 };

		const uint64 length = inputBufforLength / 4;
		const uint64 length32 = length / 32;
		const uint64 length32Left = length % 32;

		{ // FOR NOW DISPLAY IN MESSAGE BOXES !
			for (size i = 0; i < 32; ++i) {
				uint64 tempAdapter = 0;
				WcharsToUint64(tempAdapter, inputBuffor, 4, i * 4);
				//sprintf_s(buffor, 256, "%llu", tempAdapter);
				//MessageBoxA(nullptr, buffor, "LOGGER ENCRYPTED", MB_OK);
				words.push_back(tempAdapter);
			}

			encryptedBlocks.push_back(Num(words.begin()._Ptr, words.end()._Ptr));
			words.clear();

			for (size i = 0; i < 14; ++i) {
				uint64 tempAdapter = 0;
				WcharsToUint64(tempAdapter, inputBuffor, 4, (32 * 4) + (i * 4));
				//sprintf_s(buffor, 256, "%llu", tempAdapter);
				//MessageBoxA(nullptr, buffor, "LOGGER ENCRYPTED", MB_OK);
				words.push_back(tempAdapter);
			}

			//std::cout << inputBuffor[(32 * 4) + (13 * 4)];
			//std::cout << inputBuffor[(32 * 4) + (13 * 4) + 1];
			//std::cout << inputBuffor[(32 * 4) + (13 * 4) + 2];

			{ // last uint
				uint64 tempAdapter = 0;
				tempAdapter += inputBuffor[(32 * 4) + (14 * 4)];
				tempAdapter <<= 16;
				tempAdapter += inputBuffor[(32 * 4) + (14 * 4) + 1];
				tempAdapter <<= 16;
				tempAdapter += inputBuffor[(32 * 4) + (14 * 4) + 2];
				//tempAdapter <<= 16;
				//tempAdapter <<= 16;
				//tempAdapter += inputBuffor[(32 * 4) + (13 * 4) + 3];
				//WcharsToUint64(tempAdapter, inputBuffor, 3, (32 * 4) + (14 * 4));
				words.push_back(tempAdapter);
			}
			
			//words[14] >>= 16;
			encryptedBlocks.push_back(Num(words.begin()._Ptr, words.end()._Ptr));
			words.clear();
		}

		// Last uint64 has to be moved by 16 bytes >> ...
		//  that information has to be kept.

		// Decruption
		std::vector<Num> decryptedBlocks;
		for (size i = 0; i < encryptedBlocks.size(); ++i) {
			Num decrypted = encryptedBlocks[i].mod_pow(g_d, g_n);
			decryptedBlocks.push_back(decrypted);
		}

		//decryptedBlocks[decryptedBlocks.size() - 1].

		// BIGINT into wchars
		std::vector<wchar_t> outputData;
		for (size i = 0; i < decryptedBlocks.size(); ++i) {
			for (size j = 0; j < decryptedBlocks[i].words.size(); ++j) {
				Uint64ToWchars(outputData, decryptedBlocks[i].words[j]);
			}
		}

		//outputBuffor = new wchar[outputData.size()];
		SendMessageW(output, WM_SETTEXT, NULL, (LPARAM)outputData.data());
		delete[] outputBuffor;
		
		
		// DEBUG
		//MessageBoxW(nullptr, outputData.data(), L"LOGGER OUTPUT DATA", MB_OK);

	}

	block Encrypt2048(
		OUT wchar* outputBuffor,
		IN const wchar* const inputBuffor,
		IN const size& inputBufforLength,
		IN const HWND& output
	) {
		std::vector<char> buffor;

		std::vector<Num> blocks;
		std::vector<Num::word> words; // 64bit datatype builds a single block.
		std::vector<Num> encryptedBlocks;

		const auto& blockSizeWchar = RSA2048::blockSizeWchar;
		const auto& blockSizeUint = RSA2048::blockSizeUint;
		const Num& p = RSA2048::p;
		const Num& q = RSA2048::q;

		const auto& stringLength = inputBufforLength + 1;
		const auto& wordsLength = stringLength / blockSizeWchar;
		const auto& wordsLeftLength = stringLength % blockSizeWchar;
		const auto& wordsZeroesLength = blockSizeWchar - wordsLeftLength;

		// We're packing those into uint64 therefore we need packs of 4 x 16 wchars.
		const auto& l4Length = wordsLeftLength / wcharsInUint64;
		const auto& l4LeftLength = wordsLeftLength % wcharsInUint64;
		const auto& l4ZeroesLength = wcharsInUint64 - l4LeftLength;

		{ /* Encapsulation */
			
			for (size i = 0; i < wordsLength; ++i) { // Block of data

				for (size j = 0; j < blockSizeUint; ++j) {
					const auto& bufforPtr = inputBuffor + (wordsLength * i);
					uint64 tempAdapter = 0;
					WcharsToUint64(tempAdapter, bufforPtr, wcharsInUint64, j * wcharsInUint64);
					words.push_back(tempAdapter);
				}

				blocks.push_back(Num(words.begin()._Ptr, words.end()._Ptr));
				words.clear(); // It is possible to write it better without clear...
			}

			if (wordsLeftLength) { // Last Block (left bytes)

				// Cpy left bytes of 4's
				for (size i = 0; i < l4Length * 4; ++i) {
					const auto& bufforPtr = inputBuffor + (wordsLength * blockSizeUint) + (l4Length * i);
					uint64 tempAdapter = 0;
					WcharsToUint64(tempAdapter, inputBuffor, wcharsInUint64, i * wcharsInUint64);
					words.push_back(tempAdapter);
				}

				// Cpy left bytes of rest
				for (size i = 0; i < l4LeftLength; ++i) {
					const auto& bufforPtr = inputBuffor + (wordsLength * blockSizeUint) + (l4Length * wcharsInUint64) + (l4LeftLength * i);
					uint64 tempAdapter = 0;
					WcharsToUint64(tempAdapter, inputBuffor, l4LeftLength, i * wcharsInUint64);
					words.push_back(tempAdapter);
				}

				// Fill with zeroes to whole blockSizeUint length.
				for (size i = 0; i < wordsZeroesLength; ++i) {
					words.push_back(0);
				}

				blocks.push_back(Num(words.begin()._Ptr, words.end()._Ptr));
			}

		}

		// Encryption
		for (size i = 0; i < blocks.size(); ++i) {
			Num nocrypted(blocks[i]);
			Num encrypted = nocrypted.mod_pow(g_e, g_n);
			encryptedBlocks.push_back(encrypted);

			encrypted.print(buffor);
			MessageBoxA(nullptr, buffor.data(), "LOGGER ENCRYPTED", MB_OK);
		}

		uint64 encryptedLength = 0;
		for (size i = 0; i < encryptedBlocks.size(); ++i) {
			encryptedLength += encryptedBlocks[i].words.size();
		}

		
		const auto encryptedWcharLength = encryptedLength * 4; // (32 + 15) * 4
		outputBuffor = new wchar[encryptedWcharLength + 1]; /* null-termination */
		
		//const auto& length = encryptedBlocks[0].words.size();
		//for (size j = 0; j < length; ++j) {
		//	Uint64ToWchars(outputBuffor, encryptedBlocks[0].words[j], (0 * length) + (j * 4));
		//}

		uint64 lastPos = 0;
		const uint64 lastBlock = encryptedBlocks.size() - 1;
		for (size i = 0; i < lastBlock; ++i) {
			const auto& length = encryptedBlocks[i].words.size();
			size j = 0;

			for (; j < length; ++j) {
				Uint64ToWchars(outputBuffor, encryptedBlocks[i].words[j], lastPos + (j * 4));
			}

			lastPos += j * 4;
		}

		// Because 0000'0000.0000'0000
		//         1111'1111.1111'1111
		//		   1111'1111.1111'1111
		//		   1111'1111.1111.1111
		// could be our last Uint64.
		// it doesnt appear at the end when we're dealing with 32 words - result of 2048 encoding
		// but here last uint64 represents a number if the biginteger it represents is samller then whole
		// uint64 it might actually only set bits of few wchars leaving possibly 13-wchars as l'\0' !

		{ // Get last block to get last uint64
			const auto& lastLength = encryptedBlocks[lastBlock].words.size() - 1;
			for (size i = 0; i < lastLength; ++i) { // 12 + 
					Uint64ToWchars(outputBuffor, encryptedBlocks[lastBlock].words[i], lastPos + (i * 4));
			}

			//lastPos += lastLength;

			// i have 4 * 16 here but what now ?
			const uint64 masks[] {
				0b0000'0000'0000'0000'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111'1111,
				0b0000'0000'0000'0000'0000'0000'0000'0000'1111'1111'1111'1111'1111'1111'1111'1111,
				0b0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'0000'1111'1111'1111'1111
			};

			//for (uint64 i = 0; lastLength < masks[i]; ++i) {
			//	encryptedBlocks[lastBlock].words[lastPos] <<= 16;
			//}
			auto& lastWord = encryptedBlocks[lastBlock].words[lastLength];
			if (lastWord < masks[0]) {
				lastWord <<= 16;
				MessageBoxA(nullptr, "1", "LOGGER", MB_OK);
			}

			if (lastWord < masks[1]) {
				lastWord <<= 16;
				MessageBoxA(nullptr, "2", "LOGGER", MB_OK);
			} 

			if (lastWord < masks[2]) {
				lastWord <<= 16;
				MessageBoxA(nullptr, "3", "LOGGER", MB_OK);
			} 

			uint64 sample = lastPos + (lastLength * 4);
			Uint64ToWchars(outputBuffor, lastWord, sample);

			// 1000'0000.1010'0111.1101'1100.1101'1001.0100'1010.1000'0010

		//	const uint64 lastBlockSize = encryptedBlocks[lastBlock].size();
		//	const uint64 lbs4 = lastBlockSize / 4;
		//	const uint64 lbs4left = lastBlockSize % 4;
		//	size i = 0;
		//
		//	for (; i < lbs4 * 4; ++i) { // 12 + 
		//		Uint64ToWchars(outputBuffor, encryptedBlocks[lastBlock].words[i], lastPos + (i * 4));
		//	}
		//
		//	
		//
		//	//if (lbs4left) {
		//	//	lastPos += lbs4 * i * 4;
		//	//	Uint64ToWchars(outputBuffor, encryptedBlocks[lastBlock].words[lbs4 * 4], lastPos, lbs4left);
		//	//}
		//
		}
		
		outputBuffor[encryptedWcharLength] = L'\0';

		//1 for (size i = 0; i < 47; ++i) { // 47
		//1 	uint64 adapter = 0;
		//1 	WcharsToUint64(adapter, outputBuffor, 4, i * 4);
		//1 	sprintf_s(buffor.data(), 256, "%llu", adapter);
		//1 	MessageBoxA(nullptr, buffor.data(), "LOGGER ENCRYPTED", MB_OK);
		//1 }
		
		SendMessageW(output, WM_SETTEXT, NULL, (LPARAM)outputBuffor);
		delete[] outputBuffor;
	}
}