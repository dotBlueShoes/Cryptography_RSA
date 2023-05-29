#pragma once
#include "../Framework.hpp"

#include "RSA.hpp"

namespace Tests {

	block Initialize(RSA& rsa, const uint64& keyLength) {
		uint64 t1, t2;

		std::cout << "Creating Key...." << std::endl;

		t1 = clock();
		rsa.Initialize(keyLength);
		t2 = clock();

		std::cout << "Key Created." << std::endl;
		std::cout << "Creation Time: " << (t2 - t1) / 1000 << "s." << std::endl;
	}

	//block StreamBufforToString(std::streambuf* buffor) {
	//block StreamBufforToString(std::ostream buffor) {
	//	std::stringstream ss;
	//	ss << buffor;
	//	std::string cstring = ss.str();
	//
	//	//string narrow_string("A string");
	//	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	//	//std::string narrow = converter.to_bytes(wide_utf16_source_string);
	//	std::wstring wstring = converter.from_bytes(cstring);
	//	MessageBoxW(nullptr, wstring.c_str(), L"DEBUG LOG", MB_OK);
	//}

	block Decrypt(RSA& rsa) {
		//string input;
		//
		//do {
		//	std::cout << "Encrypted Message: ";
		//	std::cin >> input;
		//} while (std::cin && input.length() < 1);
		//
		//if (!std::cin || islegal(input) == false)
		//	return false;

		//BigInt encryptedMessage(input);
		//
		//long t1 = clock();
		//BigInt decryptedMessage = rsa.DecryptByPr(encryptedMessage);
		//
		//long t2 = clock();
		//
		//std::cout << "Decryption Time: " << (t2 - t1) << "ms." << std::endl;
		//std::cout << "Encrypted Message: " << encryptedMessage << '\n'
		//	<< "Decrypted Message: " << decryptedMessage << std::endl;
	}

	block Encrypt(RSA& rsa) {
		//string input;
		//
		//do {
		//	std::cout << "Nocrypted Message: ";
		//	std::cin >> input;
		//} while (std::cin && input.length() < 1);
		//
		//if (!std::cin || islegal(input) == false)
		//	return false;

		//BigInt nocryptedMessage(input);
		//
		//BigInt encryptedMessage = rsa.EncryptByPu(nocryptedMessage);
		//
		//std::cout << "NOCRYPTED: " << nocryptedMessage << '\n'
		//	<< "ENCRYPTED: " << encryptedMessage << std::endl;
	}

	block Key32() {
		RSA rsa;
		std::wstring output;

		//byte message = 0b0101'0101;
		//uint16 message = 0b0101'0101'0101'0101;
		uint32 message = 0b0101'0101'0101'0101'0101'0101'0101'0101;
		
		Initialize(rsa, 32);

		BigInt nocryptedMessage (message);
		BigInt encryptedMessage = rsa.EncryptByPu(nocryptedMessage);
		BigInt decryptedMessage = rsa.DecryptByPr(encryptedMessage);

		output = nocryptedMessage.toWString();
		MessageBoxW(nullptr, output.c_str(), L"DEBUG LOG NOCRYPTED", MB_OK);

		output = encryptedMessage.toWString();
		MessageBoxW(nullptr, output.c_str(), L"DEBUG LOG ENCRYPTED", MB_OK);

		output = decryptedMessage.toWString();
		MessageBoxW(nullptr, output.c_str(), L"DEBUG LOG DECRYPTED", MB_OK);

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