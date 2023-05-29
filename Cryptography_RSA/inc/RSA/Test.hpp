#pragma once
#include "../Framework.hpp"

#include "RSA.hpp"

namespace Tests {

	RSA rsa;

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

			// Likely uses the result of the division - single DIV instruction.
			const uint64 blocksCount = (uint64)readData.size() / 4;
			const uint64 leftBytesCount = readData.size() % 4;

			// 256 encrypted -> 256 decrypted
			// 1. encrypted -> base16 format
			// 2. process on base16
			// 3. decrypted -> base256 format

			{
				AES::Block encoded, decoded;
				std::ofstream outputFile(decodedFilePath, std::ios::binary);

				// For each Block (exclude last one)
				for (size i = 0; i < blocksCount - 1; ++i) {

					uint32 message = readData[i * 4]; // 0, 4, 8, 12, 16
					for (size j = 1; j < 4; ++j) {
						message <<= 8;
						message += readData[(i * 4) + j];
					}

					// Copy read data to Block form
					for (uint8 j = 0; j < 4; ++j) {
						encoded[j] = readData[(i * 4) + j];
					}

					BigInt encrypted(message);
					BigInt decrypted = rsa.DecryptByPr(encrypted);
					MessageBoxA(nullptr, decrypted.toString().c_str(), "DEBUG", MB_OK);
					outputFile << decrypted.toString();

					//AES::Decode<KeyType>(decoded, expandedKey, encoded);

					// Write decoded Block
					for (size j = 0; j < decoded.size(); ++j) {
						outputFile << decoded[j];
					}

				}

				{ // Last block
					const size lastBlockPosition = blocksCount - 1;

					// Copy read data to Block form
					for (uint8 j = 0; j < 16; ++j) {
						encoded[j] = readData[(lastBlockPosition * 16) + j];
					}

					//AES::Decode<KeyType>(decoded, expandedKey, encoded);

					// Write decoded Block
					for (size j = 0; j < bytesLeftCount; ++j) {
						outputFile << decoded[j];
					}
				}
				outputFile.close();
			}
		}

		auto ReadEncodeWrite(
			OUT uint8& bytesLeftCount,
			IN	const wchar* const nocodedFilePath,
			IN	const wchar* const encodedFilePath,
			IN	const uint64& key
		) {
			std::vector<byte> readData(FileIO::Read::File(nocodedFilePath));
			std::ofstream outputFile(encodedFilePath, std::ios::binary);

			// 256 nocrypted -> 256 encrypted
			// 1. nocrypted -> base16 format
			// 2. process on base16
			// 3. encrypted -> base256 format

			// Likely uses the result of the division - single DIV instruction.
			const uint64 blocksCount = (uint64)readData.size() / 4;
			bytesLeftCount = readData.size() % 4;

			Initialize(rsa, 32); // key

			// FOR EACH BLOCK
			for (size i = 0; i < blocksCount; ++i) {

				uint32 message = readData[i * 4]; // 0, 4, 8, 12, 16
				for (size j = 1; j < 4; ++j) {
					message <<= 8;
					message += readData[(i * 4) + j];
				}

				BigInt nocrypted(message);
				BigInt encrypted = rsa.EncryptByPu(nocrypted);
				//MessageBoxA(nullptr, encrypted.toString().c_str(), "DEBUG", MB_OK);
				outputFile << encrypted.toString();

			}

			if (bytesLeftCount != 0) { // FOR BLOCK LEFT
				uint32 message = readData[(blocksCount * 4)];
				for (size i = 1; i < bytesLeftCount; ++i) {
					message <<= 8;
					message += readData[(blocksCount * 4) + i];
				}

				BigInt nocrypted(message);
				BigInt encrypted = rsa.EncryptByPu(nocrypted);
				outputFile << encrypted.toString();
			}

			outputFile.close();
		}
	}

	block BigIntToUInt32() {

	}

	block Key32() {
		std::string output;

		array<byte, 4> bytes {
			0b1111'1111,
			0b0101'0110,
			0b0101'0101,
			0b0101'0100
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

		output = encryptedMessage.toString();
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