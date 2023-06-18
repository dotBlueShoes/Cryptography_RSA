#include "../Framework.hpp"
#include "RSA.hpp"

// TODO
// 3. prime generation.
// 7. simulation for data smaller then key
// 8. simulation for data bigger then key
// 7. simulation for text field
// 8. simulation for file
// 9. gui implementation
// 10. remove zeroes ?

// I need a method to save my uint64 types.
//  1 word will always be the size of "encodedBlockSizeUint" - 32/16/8/4 or smaller
// 
// and one to convert back.


namespace RSA {

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

	block Test4(
		IN const wchar* const inputData,
		IN const size& inputDataLength,
		IN const size& blockSizeWchar,
		IN const size& blockSizeUint
	) {
		std::vector<char> buffor; // DEBUG
		
		// DEBUG
		MessageBoxW(nullptr, inputData, L"LOGGER NOCRYPTED DATA", MB_OK);
		
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
		
			{ // DEBUG
				encrypted.print(buffor);
				MessageBoxA(nullptr, buffor.data(), "LOGGER ENCRYPTED", MB_OK);
			}
			
		}
		
		// Decription
		std::vector<Num> decryptedBlocks;
		for (size i = 0; i < encryptedBlocks.size(); ++i) {
			Num decrypted = encryptedBlocks[i].mod_pow(g_d, g_n);
			decryptedBlocks.push_back(decrypted);
		}

		// BigInts into Wchars
		std::vector<wchar_t> outputData;
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
			size counter = 1; // 1 byte
			if (tempValue > masks[0]) {			// 4byte'y
				counter = 4;
			} else if (tempValue > masks[1]) {	// 3byte'y
				counter = 3;
			} else if (tempValue > masks[2]) {	// 2byte'y
				counter = 2;
			}
			for (int64 i = counter - 1; i >= 0; --i) {
				wchar tempChar = (wchar)(tempValue << (i * 16));
				outputData.push_back(tempChar);
			}
		}

		outputData.push_back(L'\0');
		
		{ // DEBUG
			MessageBoxW(nullptr, outputData.data(), L"LOGGER DECRYPTED DATA", MB_OK);
			uint64 isEqual = 0;
			for (size i = 0; i < decryptedBlocks.size(); ++i) {
				isEqual += decryptedBlocks[i] == blocks[i];
			}
			if (isEqual)
				MessageBoxW(nullptr, L"YES", L"LOGGER FINAL", MB_OK);
			else
				MessageBoxW(nullptr, L"NO", L"LOGGER FINAL", MB_OK);
		}
		
	}

	void EncryptAFile() {

	}

	void DecryptAFile() {

	}

	void EncryptWText() {

	}

	void DecryptWText() {

	}


	const size wBufforLength = 20;
	using WBuffor = std::array<wchar, wBufforLength + 1>;

	block WstringsToWstring(
		OUT wchar* result,
		OUT size& resultLength,
		IN const std::vector<WBuffor>& strings
	) {
		for (size i = 0; i < strings.size(); ++i) {
			for (size j = 0; j < wBufforLength; ++j) {
				result[j + (i * wBufforLength)] = strings[i][j];
			}
		}

		result[resultLength - 1] = L'\0';
	}

	block Uint64sToWstring(
		OUT std::vector<WBuffor>& results,
		IN const std::vector<Num::word>& words
	) {
		int written = 0;

		for (size i = 0; i < words.size(); ++i) {
			WBuffor buffor { 0 }, zeroesBuffor { 0 }; // 1 extra for null-terminator.

			written = swprintf(buffor.data(), buffor.size(), L"%llu", words[i]);

			// FORCE 0es to appear at the begin - 00001234.
			const int zeroes = wBufforLength - written;
			if (zeroes) {
				for (size j = 0; j < zeroes; ++j) {
					zeroesBuffor[j] = L'0';
				}

				for (size j = 0; j < written; ++j) {
					zeroesBuffor[zeroes + j] = buffor[j];
				}
				buffor = zeroesBuffor;
			}

			results.push_back(buffor);
		}

		results.size();
	}

	block WstringToUint64s(
		OUT std::vector<Num::word>& words,
		IN const wchar* encodedData,
		IN const size& encodedDataSize
	) {
		wchar* end;

		const uint64 packets = encodedDataSize / wBufforLength;
		const uint64 left = encodedDataSize % wBufforLength;

		for (size i = 0; i < packets; ++i) {

			WBuffor buffor { 0 };

			// Copy To buffor
			for (size j = 0; j < wBufforLength; ++j) {
				buffor[j] = encodedData[(i * wBufforLength) + j];
			}

			uint64 result = wcstoull(buffor.data(), &end, 10);
			words.push_back(result);

		}

		words.size();

	}

}