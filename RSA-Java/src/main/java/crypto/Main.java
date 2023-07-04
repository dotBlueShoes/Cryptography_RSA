package crypto;

// TODO:
// 1. BigInt tests and understanding / done
// 2. Add Model Project / done
// 3. File reading and writing / done
// 4. Proper Code-Page handling
// 5. Text input read and write
// 6. Sample other projects
// 7. Test String(WString) to bytes and file and vice-versa

import java.io.File;
import java.math.BigInteger;

public class Main {

	public static String output = "D:\\Storage\\Projects\\School\\cryptography\\Cryptography_RSA\\data\\o1.txt";
	public static String t0 = "D:\\Storage\\Projects\\School\\cryptography\\Cryptography_RSA\\data\\t0.txt";
	public static String t1 = "D:\\Storage\\Projects\\School\\cryptography\\Cryptography_RSA\\data\\t1.txt";
	public static String t2 = "D:\\Storage\\Projects\\School\\cryptography\\Cryptography_RSA\\data\\t2.txt";
	public static String t3 = "D:\\Storage\\Projects\\School\\cryptography\\Cryptography_RSA\\data\\t3.txt";
	public static String t4 = "D:\\Storage\\Projects\\School\\cryptography\\Cryptography_RSA\\data\\t4.txt";

	public static void main(String[] args) {

		System.out.println("Program Start!");

		{
			System.out.println("File READ/WRITE!");
			File file = new File(t4);
			byte[] data = FileIO.ReadFileToBytes(file);
			FileIO.WriteBytesToFile(output, data);
		}

		{
			BigInteger message = new BigInteger("100");

			BigInteger p = new BigInteger("100");
			BigInteger q = new BigInteger("100");
			RSA.initialize(p, q);
			//BigInteger encrypted = RSA.encrypt(message);
			//BigInteger decrypted = RSA.decrypt(encrypted);
		}


	}

}