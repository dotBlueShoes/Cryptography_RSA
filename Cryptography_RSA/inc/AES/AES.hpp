#pragma once
#include "../Framework.hpp"
#include "../Matrix.hpp"
#include "gmult.hpp"

#include <stdint.h>
#include <stdlib.h>

namespace AES {

	// Number of columns (32-bit words) comprising the State. For this
	// standard, Nb = 4.
	const int Nb = 4;

	// Number of 32-bit double-words comprising the Cipher Key. For this
	// standard, Nk = 4, 6, or 8.
	// eg. 128, 196, 256
	// [ INITIALIZED ]
	int cipherKeydwords;

	// Number of rounds, which is a function of  Nk  and  Nb (which is
	// fixed). For this standard, Nr = 10, 12, or 14.
	// [ INITIALIZED ]
	int rounds;

	using Key128 = array<uint8, 16>;
	using Key192 = array<uint8, 24>;
	using Key256 = array<uint8, 32>;
	using Block = array<uint8, 16>;

	// OUTPUT BUFFOR
	//  max byte - 3 signs
	//  + space and coma character 
	//  for each
	using BlockWcharBuffor = array<wchar, (16 * 3) + (16 * 2)>;
	using Key128WcharBuffor = array<wchar, (88 * 3) + (88 * 2)>;
	using Key196WcharBuffor = array<wchar, (158 * 3) + (158 * 2)>;
	using Key256WcharBuffor = array<wchar, (240 * 3) + (240 * 2)>;

	namespace TEST {

		namespace Key128 {

			const AES::Key128 sample1 {
				0x00, 0x01, 0x02, 0x03,
				0x04, 0x05, 0x06, 0x07,
				0x08, 0x09, 0x0a, 0x0b,
				0x0c, 0x0d, 0x0e, 0x0f
			};

			const AES::Key128 sample2 {
				0x2b, 0x7e, 0x15, 0x16,
				0x28, 0xae, 0xd2, 0xa6,
				0xab, 0xf7, 0x15, 0x88,
				0x09, 0xcf, 0x4f, 0x3c
			};

		}

		namespace Key192 {

			const AES::Key192 sample1 {
				0x8e, 0x73, 0xb0, 0xf7,
				0xda, 0x0e, 0x64, 0x52,
				0xc8, 0x10, 0xf3, 0x2b,
				0x80, 0x90, 0x79, 0xe5,
				0x62, 0xf8, 0xea, 0xd2,
				0x52, 0x2c, 0x6b, 0x7b
			};

			const AES::Key192 sample2 {
				0x00, 0x01, 0x02, 0x03,
				0x04, 0x05, 0x06, 0x07,
				0x08, 0x09, 0x0a, 0x0b,
				0x0c, 0x0d, 0x0e, 0x0f,
				0x10, 0x11, 0x12, 0x13,
				0x14, 0x15, 0x16, 0x17
			};
		}

		namespace Key256 {

			const AES::Key256 sample1 {
				0x60, 0x3d, 0xeb, 0x10,
				0x15, 0xca, 0x71, 0xbe,
				0x2b, 0x73, 0xae, 0xf0,
				0x85, 0x7d, 0x77, 0x81,
				0x1f, 0x35, 0x2c, 0x07,
				0x3b, 0x61, 0x08, 0xd7,
				0x2d, 0x98, 0x10, 0xa3,
				0x09, 0x14, 0xdf, 0xf4
			};

			const AES::Key256 sample2 {
				0x00, 0x01, 0x02, 0x03,
				0x04, 0x05, 0x06, 0x07,
				0x08, 0x09, 0x0a, 0x0b,
				0x0c, 0x0d, 0x0e, 0x0f,
				0x10, 0x11, 0x12, 0x13,
				0x14, 0x15, 0x16, 0x17,
				0x18, 0x19, 0x1a, 0x1b,
				0x1c, 0x1d, 0x1e, 0x1f
			};
		}

	}

	// S-box transformation table
	static uint8 sBox[256] {
		// 0     1     2     3     4     5     6     7     8     9     a     b     c     d     e     f
		0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, // 0
		0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, // 1
		0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, // 2
		0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, // 3
		0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, // 4
		0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, // 5
		0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, // 6
		0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, // 7
		0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, // 8
		0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, // 9
		0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, // a
		0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, // b
		0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, // c
		0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, // d
		0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, // e
		0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16  // f
	};

	// Inverse S-box transformation table
	static uint8 inverseSBox[256] {
		// 0     1     2     3     4     5     6     7     8     9     a     b     c     d     e     f
		0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb, // 0
		0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb, // 1
		0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e, // 2
		0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25, // 3
		0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92, // 4
		0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84, // 5
		0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06, // 6
		0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b, // 7
		0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73, // 8
		0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e, // 9
		0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b, // a
		0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4, // b
		0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f, // c
		0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef, // d
		0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61, // e
		0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d  // f
	};

	namespace KeyExpansion {

		// Generates the round constant Rcon[i]
		uint8 R[] { 0x02, 0x00, 0x00, 0x00 };
		uint8* Rcon(uint8 i) {

			if (i == 1) {
				R[0] = 0x01; // x^(1-1) = x^0 = 1
			} else if (i > 1) {
				R[0] = 0x02;
				i--;
				while (i > 1) {
					R[0] = gmult(R[0], 0x02);
					i--;
				}
			}

			return R;
		}

		// Function used in the Key Expansion routine that takes a four-byte
		// and performs a cyclic permutation.
		block WordRotate(uint8* doubleWorld) {
			uint8 temp = doubleWorld[0];

			for (uint8 i = 0; i < 3; i++) {
				doubleWorld[i] = doubleWorld[i + 1];
			}

			doubleWorld[3] = temp;
		}

		// Function used in the Key Expansion routine that takes a four-byte
		// input and applies an S-box to each of the four bytes to
		// produce an output four-byte.
		block WordSubstitution(uint8* doubleWorld) {
			for (uint8 i = 0; i < 4; i++) {
				doubleWorld[i] = sBox[doubleWorld[i]];
			}
		}

		// Addition of 4 byte words
		// m(x) = x4+1
		block WordCoefAdd(uint8* a, uint8* b, uint8* d) {
			d[0] = a[0] ^ b[0];
			d[1] = a[1] ^ b[1];
			d[2] = a[2] ^ b[2];
			d[3] = a[3] ^ b[3];
		}

	}

	namespace Encryption {

		// Multiplication of 4 byte words, m(x) = x4+1
		void CoefMultiplication(uint8* a, uint8* b, uint8* d) {

			d[0] = gmult(a[0], b[0]) ^ gmult(a[3], b[1]) ^ gmult(a[2], b[2]) ^ gmult(a[1], b[3]);
			d[1] = gmult(a[1], b[0]) ^ gmult(a[0], b[1]) ^ gmult(a[3], b[2]) ^ gmult(a[2], b[3]);
			d[2] = gmult(a[2], b[0]) ^ gmult(a[1], b[1]) ^ gmult(a[0], b[2]) ^ gmult(a[3], b[3]);
			d[3] = gmult(a[3], b[0]) ^ gmult(a[2], b[1]) ^ gmult(a[1], b[2]) ^ gmult(a[0], b[3]);
		}

		// Transformation in the Cipher and Inverse Cipher in which a Round
		// Key is added to the State using an XOR operation. The length of a
		// Round Key equals the size of the State (i.e., for Nb = 4, the Round
		// Key length equals 128 bits/16 bytes).
		block AddRoundKey(uint8* state, const uint8* w, const uint8& r) {
			for (uint8 i = 0; i < Nb; ++i) {
				state[Nb * 0 + i] = state[Nb * 0 + i] ^ w[4 * Nb * r + 4 * i + 0];   //debug, so it works for Nb !=4 
				state[Nb * 1 + i] = state[Nb * 1 + i] ^ w[4 * Nb * r + 4 * i + 1];
				state[Nb * 2 + i] = state[Nb * 2 + i] ^ w[4 * Nb * r + 4 * i + 2];
				state[Nb * 3 + i] = state[Nb * 3 + i] ^ w[4 * Nb * r + 4 * i + 3];
			}
		}

		// Transformation in the Cipher that processes the State using a non�
		// linear byte substitution table (S-box) that operates on each of the
		// State bytes independently.
		block BytesSubstitution(uint8* state) {
			for (uint8 i = 0; i < 4; i++) {
				for (uint8 j = 0; j < Nb; j++) {
					state[Nb * i + j] = AES::sBox[state[Nb * i + j]];
				}
			}
		}

		// Transformation in the Cipher that processes the State by cyclically
		// shifting the last three rows of the State by different offsets.
		block ShiftRows(uint8* state) {
			for (uint8 i = 1; i < 4; i++) {
				uint8 s = 0;
				while (s < i) {
					uint8 temp = state[Nb * i + 0];

					for (uint8 k = 1; k < Nb; k++) {
						state[Nb * i + k - 1] = state[Nb * i + k];
					}

					state[Nb * i + Nb - 1] = temp;
					s++;
				}
			}
		}

		// Transformation in the Cipher that takes all of the columns of the
		// State and mixes their data (independently of one another) to
		// produce new columns.
		block MixColumns(uint8* state) {
			uint8 a[] = { 0x02, 0x01, 0x01, 0x03 }; // a(x) = {02} + {01}x + {01}x2 + {03}x3
			uint8 col[4], res[4];

			for (uint8 j = 0; j < Nb; j++) {
				for (uint8 i = 0; i < 4; i++)
					col[i] = state[Nb * i + j];

				CoefMultiplication(a, col, res);

				for (uint8 i = 0; i < 4; i++)
					state[Nb * i + j] = res[i];
			}
		}

		// Transformation in the Inverse Cipher that is the inverse of
		// ShiftRows().
		block InverseShiftRows(uint8* state) {
			for (uint8 i = 1; i < 4; i++) {
				uint8 s = 0;
				while (s < i) {
					uint8 tmp = state[Nb * i + Nb - 1];

					for (uint8 k = Nb - 1; k > 0; k--) {
						state[Nb * i + k] = state[Nb * i + k - 1];
					}

					state[Nb * i + 0] = tmp;
					s++;
				}
			}
		}

		// Transformation in the Inverse Cipher that is the inverse of
		// SubBytes().
		block InverseSubstitutionBytes(uint8* state) {
			for (uint8 i = 0; i < 4; i++) {
				for (uint8 j = 0; j < Nb; j++) {
					state[Nb * i + j] = AES::inverseSBox[state[Nb * i + j]];
				}
			}
		}

		// Transformation in the Inverse Cipher that is the inverse of
		// MixColumns().
		block InverseMixColumns(uint8* state) {

			uint8 a[] { 0x0e, 0x09, 0x0d, 0x0b }; // a(x) = {0e} + {09}x + {0d}x2 + {0b}x3
			uint8 col[4], res[4];

			for (uint8 j = 0; j < Nb; j++) {
				for (uint8 i = 0; i < 4; i++)
					col[i] = state[Nb * i + j];

				CoefMultiplication(a, col, res);

				for (uint8 i = 0; i < 4; i++)
					state[Nb * i + j] = res[i];
			}
		}

	}

	template <typename KeyType>
	block ExpendKey(
		OUT uint8* expandedKey,
		IN const KeyType& key
	) {
		const uint8 len = Nb * (rounds + 1);
		uint8 tmp[4];

		for (uint8 i = 0; i < cipherKeydwords; i++) {
			expandedKey[4 * i + 0] = key.data()[4 * i + 0];
			expandedKey[4 * i + 1] = key.data()[4 * i + 1];
			expandedKey[4 * i + 2] = key.data()[4 * i + 2];
			expandedKey[4 * i + 3] = key.data()[4 * i + 3];
		}

		for (uint8 i = cipherKeydwords; i < len; i++) {
			tmp[0] = expandedKey[4 * (i - 1) + 0];
			tmp[1] = expandedKey[4 * (i - 1) + 1];
			tmp[2] = expandedKey[4 * (i - 1) + 2];
			tmp[3] = expandedKey[4 * (i - 1) + 3];

			if (i % cipherKeydwords == 0) {
				KeyExpansion::WordRotate(tmp);
				KeyExpansion::WordSubstitution(tmp);
				KeyExpansion::WordCoefAdd(tmp, KeyExpansion::Rcon(i / cipherKeydwords), tmp);
			} else if (cipherKeydwords > 6 && i % cipherKeydwords == 4) {
				KeyExpansion::WordSubstitution(tmp);
			}

			expandedKey[4 * i + 0] = expandedKey[4 * (i - cipherKeydwords) + 0] ^ tmp[0];
			expandedKey[4 * i + 1] = expandedKey[4 * (i - cipherKeydwords) + 1] ^ tmp[1];
			expandedKey[4 * i + 2] = expandedKey[4 * (i - cipherKeydwords) + 2] ^ tmp[2];
			expandedKey[4 * i + 3] = expandedKey[4 * (i - cipherKeydwords) + 3] ^ tmp[3];
		}
	}

	// Initialize AES variables and allocate memory for expanded key
	uint8* Initialize(const size& keySize) {

		switch (keySize) {
			default:
			case 16: cipherKeydwords = 4; rounds = 10; break;
			case 24: cipherKeydwords = 6; rounds = 12; break;
			case 32: cipherKeydwords = 8; rounds = 14; break;
		}

		// 1920 bits = 128 * 15 !!!! DZIA�A
		return (uint8*)malloc(Nb * (rounds + 1) * 4);

	}

	template <class KeyType>
	block Encode(
		OUT Block& encoded,
		IN const uint8* expandedKey,
		IN const Block& nocoded
	) {
		uint8 state[4 * Nb];

		for (uint8 i = 0; i < 4; i++)
			for (uint8 j = 0; j < Nb; j++)
				state[Nb * i + j] = nocoded[i + 4 * j];

		Encryption::AddRoundKey(state, expandedKey, 0);

		for (uint8 r = 1; r < rounds; r++) {
			Encryption::BytesSubstitution(state);
			Encryption::ShiftRows(state);
			Encryption::MixColumns(state);
			Encryption::AddRoundKey(state, expandedKey, r);
		}

		Encryption::BytesSubstitution(state);
		Encryption::ShiftRows(state);
		Encryption::AddRoundKey(state, expandedKey, rounds);

		for (uint8 i = 0; i < 4; i++)
			for (uint8 j = 0; j < Nb; j++)
				encoded[i + 4 * j] = state[Nb * i + j];
	}

	template <class KeyType>
	block Decode(
		OUT Block& decoded,
		IN const uint8* expandedKey,
		IN const Block& encoded
	) {
		uint8 state[4 * Nb];

		for (uint8 i = 0; i < 4; i++)
			for (uint8 j = 0; j < Nb; j++)
				state[Nb * i + j] = encoded[i + 4 * j];

		Encryption::AddRoundKey(state, expandedKey, rounds);

		for (uint8 r = rounds - 1; r >= 1; r--) {
			Encryption::InverseShiftRows(state);
			Encryption::InverseSubstitutionBytes(state);
			Encryption::AddRoundKey(state, expandedKey, r);
			Encryption::InverseMixColumns(state);
		}

		Encryption::InverseShiftRows(state);
		Encryption::InverseSubstitutionBytes(state);
		Encryption::AddRoundKey(state, expandedKey, 0);

		for (uint8 i = 0; i < 4; i++)
			for (uint8 j = 0; j < Nb; j++)
				decoded[i + 4 * j] = state[Nb * i + j];
	}

	template <class KeyType>
	block WcharsToKey(
		OUT KeyType& key,
		IN const wchar* const buffor,
		IN const size& bufforCount
	) {
		uint8 count(0);

		for (size i = 0; i < bufforCount; ++i) {
			key[count] = (uint8)(buffor[i] << 8);
			key[count + 1] = (uint8)(buffor[i]);
			count += 2;
		}
	}

}