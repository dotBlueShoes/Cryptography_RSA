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
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;

public class Main {
	public static void main(String[] args) {
		System.out.println("Hello world!");

		//File file = new File("D:\\Storage\\Projects\\School\\cryptography\\Cryptography_RSA\\data\\t0.txt");
		//File file = new File("D:\\Storage\\Projects\\School\\cryptography\\Cryptography_RSA\\data\\t1.txt");
		//File file = new File("D:\\Storage\\Projects\\School\\cryptography\\Cryptography_RSA\\data\\t2.txt");
		//File file = new File("D:\\Storage\\Projects\\School\\cryptography\\Cryptography_RSA\\data\\t3.txt");
		File file = new File("D:\\Storage\\Projects\\School\\cryptography\\Cryptography_RSA\\data\\t4.txt");
		//File output = new File("D:\\Storage\\Projects\\School\\cryptography\\Cryptography_RSA\\data\\o1.txt");

		byte[] fileContent;

		try { // READING
			fileContent = Files.readAllBytes(file.toPath());

			if (fileContent.length == 0) {
				throw new IOException();
			}

			System.out.print("length: " + fileContent.length);
		} catch (IOException e) {
			throw new RuntimeException(e);
			// Handle file empty and such errors...
		}

		//try { // WRITING
		//	FileWriter myWriter = new FileWriter("D:\\Storage\\Projects\\School\\cryptography\\Cryptography_RSA\\data\\o1.txt");
		//	myWriter.write(fileContent);
		//} catch (IOException e) {
		//	throw new RuntimeException(e);
		//}

		try (FileOutputStream fos = new FileOutputStream("D:\\Storage\\Projects\\School\\cryptography\\Cryptography_RSA\\data\\o1.txt")) {
			fos.write(fileContent);
			//fos.close(); There is no more need for this line since you had created the instance of "fos" inside the try. And this will automatically close the OutputStream
		} catch (IOException e) {
			throw new RuntimeException(e);
		}


	}

	public void ReadFileToBytes() {

	}

	public void WriteBytesToFile() {

	}
}