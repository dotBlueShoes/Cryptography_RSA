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

namespace RSA {

	block Test4() {

		std::vector<char> buffor;

		const Num& p = RSA2048::p;
		const Num& q = RSA2048::q;
		const auto& blockSizeWchar = RSA2048::blockSizeWchar;
		const auto& blockSizeUint = RSA2048::blockSizeUint;

		//Num n = p * q;
		//Num phi = CalculatePhi(p, q);
		//Num e = NumCalculateE(phi);		// encryption
		//Num d = CalculateD(phi, e);		// decryption

		g_n = p * q;
		g_phi = CalculatePhi(p, q);
		g_e = NumCalculateE(g_phi);		// encryption
		g_d = CalculateD(g_phi, g_e);		// decryption


		//1 // INPUT SIMULATION 
		//1 //std::vector<wchar_t> inputData; // 16bit datatype
		//1 std::wstring inputData = L"12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012312"; // 124 signs
		//1 //std::wstring inputData = L"12345678123456781234567812345678"; // 32 znaki - 64bytes = 64 * 8 = 512
		//1 
		//1 
		//1 
		//1 // DEBUG
		//1 MessageBoxW(nullptr, inputData.data(), L"LOGGER INPUT DATA", MB_OK);
		//1 
		//1 
		//1 std::vector<Num> blocks;
		//1 std::vector<Num::word> words; // 64bit datatype
		//1 
		//1 
		//1 
		//1 const auto& stringLength = inputData.length() + 1;
		//1 const auto& wordsLength = stringLength / blockSizeWchar;
		//1 const auto& wordsLeftLength = stringLength % blockSizeWchar;
		//1 const auto& wordsZeroesLength = blockSizeWchar - wordsLeftLength;
		//1 
		//1 // We're packing those into uint64 therefore we need packs of 4 x 16 wchars.
		//1 const auto& l4Length = wordsLeftLength / wcharsInUint64;
		//1 const auto& l4LeftLength = wordsLeftLength % wcharsInUint64;
		//1 const auto& l4ZeroesLength = wcharsInUint64 - l4LeftLength;
		//1 
		//1 // last block ()
		//1 //const auto& bufforPtr = inputData.data() + (wordsLength * blockSizeUint) + (l4Length * i);
		//1 //const auto& bufforPtr = inputData.data() + (wordsLength * blockSizeUint) + (l4Length * wcharsInUint64) + (l4LeftLength * i);
		//1 
		//1 // Block of data
		//1 for (size i = 0; i < wordsLength; ++i) {
		//1 
		//1 	for (size j = 0; j < blockSizeUint; ++j) {
		//1 		const auto& bufforPtr = inputData.data() + (wordsLength * i);
		//1 		uint64 tempAdapter = 0;
		//1 		WcharsToUint64(tempAdapter, bufforPtr, wcharsInUint64, j * wcharsInUint64);
		//1 		words.push_back(tempAdapter);
		//1 	}
		//1 
		//1 	blocks.push_back(Num(words.begin()._Ptr, words.end()._Ptr));
		//1 	words.clear(); // It is possible to write it better without clear...
		//1 }
		//1 
		//1 if (wordsLeftLength) { // Last Block (left bytes)
		//1 
		//1 	// Cpy left bytes of 4's
		//1 	for (size i = 0; i < l4Length * 4; ++i) {
		//1 		const auto& bufforPtr = inputData.data() + (wordsLength * blockSizeUint) + (l4Length * i);
		//1 		uint64 tempAdapter = 0;
		//1 		WcharsToUint64(tempAdapter, inputData.data(), wcharsInUint64, i * wcharsInUint64);
		//1 		words.push_back(tempAdapter);
		//1 	}
		//1 
		//1 	// Cpy left bytes of rest
		//1 	for (size i = 0; i < l4LeftLength; ++i) {
		//1 		const auto& bufforPtr = inputData.data() + (wordsLength * blockSizeUint) + (l4Length * wcharsInUint64) + (l4LeftLength * i);
		//1 		uint64 tempAdapter = 0;
		//1 		WcharsToUint64(tempAdapter, inputData.data(), l4LeftLength, i * wcharsInUint64);
		//1 		words.push_back(tempAdapter);
		//1 	}
		//1 
		//1 	// Fill with zeroes to whole blockSizeUint length.
		//1 	for (size i = 0; i < wordsZeroesLength; ++i) {
		//1 		words.push_back(0);
		//1 	}
		//1 
		//1 	blocks.push_back(Num(words.begin()._Ptr, words.end()._Ptr));
		//1 }
		//1 
		//1 // Encryption
		//1 std::vector<Num> encryptedBlocks;
		//1 for (size i = 0; i < blocks.size(); ++i) {
		//1 	Num nocrypted(blocks[i]);
		//1 	Num encrypted = nocrypted.mod_pow(g_e, g_n);
		//1 	encryptedBlocks.push_back(encrypted);
		//1 
		//1 	encrypted.print(buffor);
		//1 	MessageBoxA(nullptr, buffor.data(), "LOGGER ENCRYPTED", MB_OK);
		//1 }
		//1 
		//1 // Decruption
		//1 std::vector<Num> decryptedBlocks;
		//1 for (size i = 0; i < encryptedBlocks.size(); ++i) {
		//1 	Num decrypted = encryptedBlocks[i].mod_pow(g_d, g_n);
		//1 	decryptedBlocks.push_back(decrypted);
		//1 }
		//1 
		//1 
		//1 
		//1 // BIGINT into wchars
		//1 std::vector<wchar_t> outputData;
		//1 for (size i = 0; i < decryptedBlocks.size(); ++i) {
		//1 	for (size j = 0; j < decryptedBlocks[i].words.size(); ++j) {
		//1 		Uint64ToWchars(outputData, decryptedBlocks[i].words[j]);
		//1 	}
		//1 }
		//1 
		//1 
		//1 
		//1 // DEBUG
		//1 MessageBoxW(nullptr, outputData.data(), L"LOGGER OUTPUT DATA", MB_OK);
		//1 
		//1 uint64 isEqual = 0;
		//1 for (size i = 0; i < decryptedBlocks.size(); ++i) {
		//1 	isEqual += decryptedBlocks[i] == blocks[i];
		//1 }
		//1 
		//1 if (isEqual)
		//1 	MessageBoxW(nullptr, L"YES", L"LOGGER FINAL", MB_OK);
		//1 else
		//1 	MessageBoxW(nullptr, L"NO", L"LOGGER FINAL", MB_OK);
	}

}