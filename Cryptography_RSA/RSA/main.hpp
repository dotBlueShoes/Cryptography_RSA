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

	block Test4(
		IN const wchar* const inputData,
		IN const size& inputDataLength,
		IN const size& blockSizeWchar,
		IN const size& blockSizeUint,
		IN const size& encodedBlockSizeUint
	) {
		//std::vector<char> buffor; // DEBUG
		
		// DEBUG
		// MessageBoxW(nullptr, inputData, L"LOGGER NOCRYPTED DATA", MB_OK);
		
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
		
			//{ // DEBUG
			//	encrypted.print(buffor);
			//	MessageBoxA(nullptr, buffor.data(), "LOGGER ENCRYPTED", MB_OK);
			//}
			
		}

		{ // WriteToWchars 16bit
			std::vector<WBuffor> results;
			for (size i = 0; i < encryptedBlocks.size(); ++i) {
				Uint64sToWstring(results, encryptedBlocks[i].words);
			}
			
			{ // std::vector<WBuffor> TO wchars
				wchar* data = nullptr;
				size dataSize = 0;

				{ // GET LENGTH;
					const size length = wBufforLength * results.size();
					dataSize = length + 1;
					data = new wchar[dataSize];
				}

				WstringsToWstring(data, dataSize, results);

				{ // ReadFromWchars
					std::vector<Num> readblocks;
					std::vector<Num::word> readWords;

					WstringToUint64s(readWords, data, dataSize - 1);
					
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

						// begin of 64 int
						// 0000'0000.0000'0000
						// 0000'0000.0000'0000
						// 0000'0000.0000'0000
						// 16bit wchar
						// 0000'0000
						// 0011'1001
						// 0000'0000
						// 0011'0000

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

				}

				delete[] data;
			}
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

}