package crypto;

// TODO:
// 4. whats my current block size then ? RSA256{}, RSA512{}, RSA1024{}, RSA2048{}
// 5. Proper Code-Page handling
// 6. Text input read and write
// 7. Sample other projects
// 8. Test String(WString) to bytes and file and vice-versa

import java.io.File;
import java.math.BigInteger;

public class Main {

	public static final String output = "D:\\Storage\\Projects\\School\\cryptography\\Cryptography_RSA\\data\\o1.txt";
	public static final String ti0 = "D:\\Storage\\Projects\\School\\cryptography\\Cryptography_RSA\\data\\t0.txt";
	public static final String ti1 = "D:\\Storage\\Projects\\School\\cryptography\\Cryptography_RSA\\data\\t1.txt";
	public static final String ti2 = "D:\\Storage\\Projects\\School\\cryptography\\Cryptography_RSA\\data\\t2.txt";
	public static final String ti3 = "D:\\Storage\\Projects\\School\\cryptography\\Cryptography_RSA\\data\\t3.txt";
	public static final String ti4 = "D:\\Storage\\Projects\\School\\cryptography\\Cryptography_RSA\\data\\t4.txt";

	public static void main(String[] args) {

		System.out.println("Program Start!");

		{
			System.out.println("File READ/WRITE!");
			File file = new File(ti4);
			byte[] data = FileIO.ReadFileToBytes(file);
			FileIO.WriteBytesToFile(output, data);
		}

		{
			BigInteger message = new BigInteger("100");

			BigInteger p = new BigInteger("100");
			BigInteger q = new BigInteger("100");
			RSA.initialize(p, q);

			// encrypt
			// - in:  ByteStream: those will be packed into blocks and later encoded.
			// - out: ByteStream: encoded formatted bytes - meaning they will be fine to send and transform back.
			// - does:
			//  - 1. Creates data blocks on which it will operate.
			//  - 2. Encrypts those data blocks.
			//  - 3. Transform those data blocks into form that can be sent and written.

			//  decrypt
			// - in:  ByteStream: those will be packed into blocks and later decoded.
			// - out: ByteStream: decoded bytes
			// - does:
			//  - 1. Creates data blocks on which it will operate.
			//  - 2. Decrypts those data blocks.

			//BigInteger encrypted = RSA.encrypt(message);
			//BigInteger decrypted = RSA.decrypt(encrypted);
		}


	}

}