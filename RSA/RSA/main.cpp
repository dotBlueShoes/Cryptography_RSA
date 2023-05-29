#include<iostream>
#include<ctime>

#include"RSA.hpp"

void menu() {
	std::cout <<
		"\nRSA program:\n"
		"\te.encrypt\n"
		"\td.decrypt\n"
		"\ts.setkey\n"
		"\tp.print\n"
		"\tq.quit\n"
		"input your choice: ";
}

bool islegal(const string& str) {

	for (string::const_iterator iterator = str.begin(); iterator != str.end(); ++iterator)
		if (!isalnum(*iterator))
			return false;

	return true;
}

bool decrypt(RSA& rsa) {
	string input;

	do {
		std::cout << "Encrypted Message: ";
		std::cin >> input;
	} while (std::cin && input.length() < 1);

	if (!std::cin || islegal(input) == false)
		return false;

	BigInt encryptedMessage(input);
	
	long t1 = clock();
	BigInt decryptedMessage = rsa.DecryptByPr(encryptedMessage);

	long t2 = clock();

	std::cout << "Decryption Time: " << (t2 - t1) << "ms." << std::endl;
	std::cout << "Encrypted Message: " << encryptedMessage << '\n'
		<< "Decrypted Message: " << decryptedMessage << std::endl;

	return true;
}

bool encrypt(RSA& rsa) {
	string input;

	do {
		std::cout << "Nocrypted Message: ";
		std::cin >> input;
	} while (std::cin && input.length() < 1);

	if (!std::cin || islegal(input) == false)
		return false;

	BigInt nocryptedMessage(input);

	BigInt encryptedMessage = rsa.EncryptByPu(nocryptedMessage);

	std::cout << "NOCRYPTED: " << nocryptedMessage << '\n'
		<< "ENCRYPTED: " << encryptedMessage << std::endl;

	return true;
}

void print(RSA& rsa) {
	std::cout << rsa << std::endl;
}

void initialize(RSA& rsa, int keyLength) {
	std::cout << "Creating Key...."<< std::endl;
	long t1 = clock();
	rsa.Initialize(keyLength);

	long t2 = clock();
	std::cout << "Key Created." << std::endl;
	std::cout << "Creation Time: " << (t2 - t1) / 1000 << "s." << std::endl;
}

int loop() {

	char processedInput;
	string input;
	RSA rsa;
	BigInt c, m;
	int keyLength;

	std::cout << "Key Length: ";
	std::cin >> keyLength;

	initialize(rsa, keyLength / 2);

	while (true) {

		menu();
		std::cin >> input;

		if(!std::cin)
			return 0;
		
		if (input.length() < 1)
			std::cout << "Invalid Read Input!" << std::endl;
		else {
			processedInput = input.at(0);
			switch(processedInput) {
				case 'e':
				case 'E': {
					encrypt(rsa);
				} break;

				case 'd':
				case 'D': {
					decrypt(rsa);
				} break;

				case 's':
				case 'S': {
					loop();
				} break;

				case 'p':
				case 'P': {
					print(rsa);
				} break;
				
				case 'q':
				case 'Q':
				default: {
					return 0;
				}
			}
		}
	}
}


int main() {
	loop();
}