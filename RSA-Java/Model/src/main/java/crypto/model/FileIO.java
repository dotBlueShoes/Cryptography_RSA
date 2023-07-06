package crypto.model;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;

public class FileIO {

	public static final String to0 = "D:\\Storage\\Projects\\School\\cryptography\\Cryptography_RSA\\data\\to0.txt";

	public static byte[] ReadFileToBytes(File file) {
		try {

			byte[] fileContents = Files.readAllBytes(file.toPath());

			if (fileContents.length == 0) {
				throw new IOException();
			}

			return fileContents;

		} catch (IOException e) {
			//throw new RuntimeException(e);
			// Handle file empty and such errors...
			return null;
		}
	}

	public static void WriteBytesToFile(String filePath, byte[] data) {
		try (FileOutputStream fos = new FileOutputStream(filePath)) {
			fos.write(data);
			// fos.close(); No need for this line "fos" inside the try.
			// And this will automatically close the OutputStream
		} catch (IOException e) {
			//throw new RuntimeException(e);
			//return;
		}
	}

}
