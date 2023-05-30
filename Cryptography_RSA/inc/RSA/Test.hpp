#pragma once
#include "../Framework.hpp"

#include "RSA.hpp"

// if (16x,16x) -> FF jest > 0b0111'1111
// trzeba znegowaæ

namespace Tests {

	RSA rsa;
	std::vector<bool> negation1;
	std::vector<bool> negation2;

	block Initialize(RSA& rsa, const uint64& keyLength) {
		uint64 t1, t2;

		std::cout << "Creating Key...." << std::endl;

		t1 = clock();
		rsa.Initialize(keyLength);
		t2 = clock();

		std::cout << "Key Created." << std::endl;
		std::cout << "Creation Time: " << (t2 - t1) / 1000 << "s." << std::endl;
	}

	namespace RSAN {
		auto ReadDecodeWrite(
			IN const wchar* const encodedFilePath,
			IN const wchar* const decodedFilePath,
			IN const uint64& key,
			IN const uint8 bytesLeftCount = 0
		) {
			std::vector<byte> readData(FileIO::Read::File(encodedFilePath));
			std::ofstream outputFile(decodedFilePath, std::ios::binary);

			// Likely uses the result of the division - single DIV instruction.
			const uint64 blockSize = 4 * (key / 16);
			const uint64 blocksCount = (uint64)readData.size() / blockSize;
			const uint64 lastBlock = blocksCount - 1;
			//const uint64 leftBytesCount = readData.size() % blockSize;

			// 256 encrypted -> 256 decrypted
			// 1. encrypted -> base16 format
			// 2. process on base16
			// 3. decrypted -> base256 format

			const uint8 mask = 0b0000'1111;
			char character = 0;

			// FOR EACH BLOCK WITHOUT LAST ONE
			for (size i = 0; i < lastBlock; ++i) {

				std::string temp = "";

				for (size j = 0; j < blockSize; ++j) {
					character = readData[(i * blockSize) + j] >> 4;

					if (character > 9) { // '9'
						character += ('A' - 10); // 'a'
					} else {
						character += '0';
					}
					temp += character;

					character = readData[(i * blockSize) + j] & mask;

					if (character > 9) { // '9'
						character += ('A' - 10); // 'a'
					} else {
						character += '0';
					}
					temp += character;
				}

				//MessageBoxA(nullptr, temp.c_str(), "DEBUG A", MB_OK);

				BigInt encrypted(temp);
				BigInt decrypted = rsa.DecryptByPr(encrypted);

				//std::string result = decrypted.toString(encrypted._isnegative);
				std::string result = decrypted.toString(negation1.back());
				negation1.pop_back();

				for (size j = 0; j < result.size(); ++j) {
					byte t = result[j];
					outputFile << t;
				}

				//outputFile << decrypted.toString();

				//MessageBoxA(nullptr, encrypted.toString().c_str(), "DEBUG B", MB_OK);
				//MessageBoxA(nullptr, decrypted.toString().c_str(), "DEBUG C", MB_OK);
			}

			// LAST BLOCK
			if (bytesLeftCount == 0) {
				
				std::string temp = "";

				for (size j = 0; j < blockSize; ++j) {
					character = readData[(lastBlock * blockSize) + j] >> 4;

					if (character > 9) { // '9'
						character += ('A' - 10); // 'a'
					} else {
						character += '0';
					}
					temp += character;

					character = readData[(lastBlock * blockSize) + j] & mask;

					if (character > 9) { // '9'
						character += ('A' - 10); // 'a'
					} else {
						character += '0';
					}
					temp += character;
				}

				//MessageBoxA(nullptr, temp.c_str(), "DEBUG A", MB_OK);

				BigInt encrypted(temp);
				BigInt decrypted = rsa.DecryptByPr(encrypted);

				//std::string result = decrypted.toString(encrypted._isnegative);
				std::string result = decrypted.toString(negation1.back());
				negation1.pop_back();
				
				for (size j = 0; j < result.size(); ++j) {
					byte t = result[j];
					outputFile << t;
				}

				//MessageBoxA(nullptr, encrypted.toString().c_str(), "DEBUG B", MB_OK);
				//MessageBoxA(nullptr, decrypted.toString().c_str(), "DEBUG C", MB_OK);
			} else {
				std::string temp = "";

				// decrypt message wholy...
				// 

				for (size j = 0; j < blockSize; ++j) {
					character = readData[(lastBlock * blockSize) + j] >> 4;

					if (character > 9) { // '9'
						character += ('A' - 10); // 'a'
					} else {
						character += '0';
					}
					temp += character;

					character = readData[(lastBlock * blockSize) + j] & mask;

					if (character > 9) { // '9'
						character += ('A' - 10); // 'a'
					} else {
						character += '0';
					}
					temp += character;
				}

				//MessageBoxA(nullptr, temp.c_str(), "DEBUG A", MB_OK);

				BigInt encrypted(temp);
				BigInt decrypted = rsa.DecryptByPr(encrypted);

				// Trim 0's
				//std::string r = decrypted.toHexString(encrypted._isnegative).substr(8 - (bytesLeftCount * 2));
				std::string r = decrypted.toHexString(negation1.back()).substr(8 - (bytesLeftCount * 2));
				negation1.pop_back();

				// Convert from 16*16 format to 256 format
				std::string final = "";
				byte charFinal = 0;
				for (uint64 i = 0; i < r.size() / 2; ++i) {

					if (r[i] >= 'A') {
						charFinal = r[i * 2] - '7';
					} else { // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
						charFinal = r[i * 2] - '0';
					}

					charFinal <<= 4;

					if (r[i] >= 'A') {
						charFinal += r[(i * 2) + 1] - '7';
					} else { // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
						charFinal += r[(i * 2) + 1] - '0';
					}

					final += charFinal;
				}

				//MessageBoxA(nullptr, encrypted.toString().c_str(), "DEBUG B", MB_OK);
				//MessageBoxA(nullptr, r.c_str(), "DEBUG C", MB_OK);

				for (size j = 0; j < final.size(); ++j) {
					byte t = final[j];
					outputFile << t;
				}

				//MessageBoxA(nullptr, final.c_str(), "DEBUG D", MB_OK);

				//bytesLeftCount
			}

			//string samplec = "";
			//char tempc = bytesLeftCount + '0';
			//samplec += tempc;
			//MessageBoxA(nullptr, samplec.c_str(), "DEBUG LAST", MB_OK);


			//for (size i = 0; i < readData.size(); ++i) {
			//	const uint8 mask = 0b0000'1111;
			//	character = readData[i] >> 4;
			//
			//	if (character > 9) { // '9'
			//		character += ('A' - 10); // 'a'
			//	} else {
			//		character += '0';
			//	}
			//	temp += character;
			//
			//	character = readData[i] & mask;
			//
			//	if (character > 9) { // '9'
			//		character += ('A' - 10); // 'a'
			//	} else {
			//		character += '0';
			//	}
			//	temp += character;
			//}
			//
			////temp += '\0';
			//MessageBoxA(nullptr, temp.c_str(), "DEBUG A", MB_OK);
			//
			//BigInt encrypted(temp);
			//BigInt decrypted = rsa.DecryptByPr(encrypted);
			//
			//MessageBoxA(nullptr, encrypted.toString().c_str(), "DEBUG B", MB_OK);
			//MessageBoxA(nullptr, decrypted.toString().c_str(), "DEBUG C", MB_OK);

			outputFile.close();
		}

		auto ReadEncodeWrite(
			OUT uint8& bytesLeftCount,
			IN	const wchar* const nocodedFilePath,
			IN	const wchar* const encodedFilePath,
			IN	const uint64& key
		) {
			std::vector<byte> readData(FileIO::Read::File(nocodedFilePath));
			std::ofstream outputFile(encodedFilePath, std::ios::binary);

			negation1.clear();
			// 256 nocrypted -> 256 encrypted
			// 1. nocrypted -> base16 format
			// 2. process on base16
			// 3. encrypted -> base256 format

			// Likely uses the result of the division - single DIV instruction.
			const uint64 blockSize = 4;
			const uint64 blocksCount = (uint64)readData.size() / blockSize;
			bytesLeftCount = readData.size() % blockSize;

			Initialize(rsa, key); // key

			//const uint8 mask = 0b0000'1111;
			//std::ofstream outputFile(encodedFilePath, std::ios::binary);
			//std::string temp = "";
			//char character = 0;
			//
			//for (size i = 0; i < readData.size(); ++i) {
			//	character = readData[i] >> 4;
			//
			//	if (character > 9) { // '9'
			//		character += ('A' - 10); // 'a'
			//	} else {
			//		character += '0';
			//	}
			//	temp += character;
			//
			//	character = readData[i] & mask;
			//
			//	if (character > 9) { // '9'
			//		character += ('A' - 10); // 'a'
			//	} else {
			//		character += '0';
			//	}
			//	temp += character;
			//}
			//
			//BigInt nocrypted(temp);
			//BigInt encrypted = rsa.EncryptByPu(nocrypted);
			//outputFile << encrypted.toString();
			//
			//MessageBoxA(nullptr, nocrypted.toString().c_str(), "DEBUG A", MB_OK);
			//MessageBoxA(nullptr, encrypted.toString().c_str(), "DEBUG B", MB_OK);

			// FOR EACH BLOCK
			for (size i = 0; i < blocksCount; ++i) {
			
				uint32 message = readData[i * blockSize]; // 0, 4, 8, 12, 16
				for (size j = 1; j < blockSize; ++j) {
					message <<= 8;
					message += readData[(i * blockSize) + j];
				}
			
				BigInt nocrypted(message);
				BigInt encrypted = rsa.EncryptByPu(nocrypted);
				//MessageBoxA(nullptr, nocrypted.toString().c_str(), "DEBUG A", MB_OK);
				//MessageBoxA(nullptr, encrypted.toString(nocrypted._isnegative).c_str(), "DEBUG B", MB_OK);
				//outputFile << encrypted.toString(nocrypted._isnegative);
				outputFile << encrypted.toString();

				negation1.push_back(nocrypted._isnegative);
			}
			
			if (bytesLeftCount != 0) { // FOR BLOCK LEFT
				uint32 message = readData[(blocksCount * blockSize)];
				for (size i = 1; i < bytesLeftCount; ++i) {
					message <<= 8;
					message += readData[(blocksCount * blockSize) + i];
				}
			
				BigInt nocrypted(message);
				BigInt encrypted = rsa.EncryptByPu(nocrypted);
				//MessageBoxA(nullptr, encrypted.toString().c_str(), "DEBUG B", MB_OK);
				//outputFile << encrypted.toString(nocrypted._isnegative);
				outputFile << encrypted.toString();

				negation1.push_back(nocrypted._isnegative);
			}

			std::reverse(negation1.begin(), negation1.end());
			outputFile.close();
		}
	}

	block BigIntToUInt32() {

	}

	block Key32() {
		std::string output;

		array<byte, 4> bytes {
			0b1000'0000,
			'F',
			'2',
			'3'
		};

		uint32 message = bytes[0];
		for (size i = 1; i < bytes.size(); ++i) {
			message <<= 8;
			message += bytes[i];
		}
		
		Initialize(rsa, 32);

		BigInt nocryptedMessage (message);
		BigInt encryptedMessage = rsa.EncryptByPu(nocryptedMessage);
		BigInt decryptedMessage = rsa.DecryptByPr(encryptedMessage);

		//output = nocryptedMessage.toWString();
		//MessageBoxW(nullptr, output.c_str(), L"DEBUG LOG NOCRYPTED", MB_OK);
		//
		//output = encryptedMessage.toWString();
		//MessageBoxW(nullptr, output.c_str(), L"DEBUG LOG ENCRYPTED", MB_OK);
		//
		//output = decryptedMessage.toWString(nocryptedMessage._isnegative);
		//MessageBoxW(nullptr, output.c_str(), L"DEBUG LOG DECRYPTED", MB_OK);

		output = nocryptedMessage.toString();
		MessageBoxA(nullptr, output.c_str(), "DEBUG LOG NOCRYPTED", MB_OK);
		
		output = encryptedMessage.toString(nocryptedMessage._isnegative);
		MessageBoxA(nullptr, output.c_str(), "DEBUG LOG ENCRYPTED", MB_OK);
		
		output = decryptedMessage.toString(nocryptedMessage._isnegative);
		MessageBoxA(nullptr, output.c_str(), "DEBUG LOG DECRYPTED", MB_OK);

	}

	block Key64() {

	}

	block Key128() {

	}

	block Key256() {

	}

	block Key512() {

	}

	block Key1024() {

	}

	block Key2048() {

	}

	block Key4096() {

	}

}