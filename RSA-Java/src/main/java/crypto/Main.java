package crypto;

// TODO:
// 1. BigInt tests and understanding
// 2. Add Model Project
// 3. File reading and writing
// 4. Proper Code-Page handling
// 5. Text input read and write
// 6. Sample other projects
// 7. Tests?

import java.io.File;

public class Main {

	public static String output = "D:\\Storage\\Projects\\School\\cryptography\\Cryptography_RSA\\data\\o1.txt";
	public static String t0 = "D:\\Storage\\Projects\\School\\cryptography\\Cryptography_RSA\\data\\t0.txt";
	public static String t1 = "D:\\Storage\\Projects\\School\\cryptography\\Cryptography_RSA\\data\\t1.txt";
	public static String t2 = "D:\\Storage\\Projects\\School\\cryptography\\Cryptography_RSA\\data\\t2.txt";
	public static String t3 = "D:\\Storage\\Projects\\School\\cryptography\\Cryptography_RSA\\data\\t3.txt";
	public static String t4 = "D:\\Storage\\Projects\\School\\cryptography\\Cryptography_RSA\\data\\t4.txt";

	public static void main(String[] args) {
		System.out.println("Hello world!");

		File file = new File(t4);
		byte[] data = FileIO.ReadFileToBytes(file);
		FileIO.WriteBytesToFile(output, data);

	}

}