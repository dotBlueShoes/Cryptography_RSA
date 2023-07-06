package crypto.model;

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

		System.out.println("Program Started in Console Mode!");

		{
			System.out.println("File READ/WRITE!");
			File file = new File(ti4);
			byte[] data = FileIO.ReadFileToBytes(file);
			FileIO.WriteBytesToFile(output, data);
		}

	}

}