import crypto.model.FileIO;
import org.junit.Test;

import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;

import static org.junit.Assert.assertArrayEquals;

public class FileIOTest {

	@Test
	public void Charset1Test() {
		String textInput = "ŁŹĄĄŚĄŚĄŚŃĘŚĘ$^(#6!@#^!#%!@$%!@^@#*$^IUIJEHAQEGQ@!@%RTFasfash(^&)%&*$%^@#t%";

		//String textInput = "Hello World!";
		//Charset charset = StandardCharsets.UTF_16;
		//Charset charset = StandardCharsets.US_ASCII;
		Charset charset = StandardCharsets.UTF_8;

		byte[] bytes = textInput.getBytes(charset);

		byte[] result  = {
			(byte)0b11000101, (byte)0b10000001, (byte)0b11000101, (byte)0b10111001,
			(byte)0b11000100, (byte)0b10000100, (byte)0b11000100, (byte)0b10000100,
			(byte)0b11000101, (byte)0b10011010, (byte)0b11000100, (byte)0b10000100,
			(byte)0b11000101, (byte)0b10011010, (byte)0b11000100, (byte)0b10000100,
			(byte)0b11000101, (byte)0b10011010, (byte)0b11000101, (byte)0b10000011,
			(byte)0b11000100, (byte)0b10011000, (byte)0b11000101, (byte)0b10011010,
			(byte)0b11000100, (byte)0b10011000, (byte)0b00100100, (byte)0b01011110,
			(byte)0b00101000, (byte)0b00100011, (byte)0b00110110, (byte)0b00100001,
			(byte)0b01000000, (byte)0b00100011, (byte)0b01011110, (byte)0b00100001,
			(byte)0b00100011, (byte)0b00100101, (byte)0b00100001, (byte)0b01000000,
			(byte)0b00100100, (byte)0b00100101, (byte)0b00100001, (byte)0b01000000,
			(byte)0b01011110, (byte)0b01000000, (byte)0b00100011, (byte)0b00101010,
			(byte)0b00100100, (byte)0b01011110, (byte)0b01001001, (byte)0b01010101,
			(byte)0b01001001, (byte)0b01001010, (byte)0b01000101, (byte)0b01001000,
			(byte)0b01000001, (byte)0b01010001, (byte)0b01000101, (byte)0b01000111,
			(byte)0b01010001, (byte)0b01000000, (byte)0b00100001, (byte)0b01000000,
			(byte)0b00100101, (byte)0b01010010, (byte)0b01010100, (byte)0b01000110,
			(byte)0b01100001, (byte)0b01110011, (byte)0b01100110, (byte)0b01100001,
			(byte)0b01110011, (byte)0b01101000, (byte)0b00101000, (byte)0b01011110,
			(byte)0b00100110, (byte)0b00101001, (byte)0b00100101, (byte)0b00100110,
			(byte)0b00101010, (byte)0b00100100, (byte)0b00100101, (byte)0b01011110,
			(byte)0b01000000, (byte)0b00100011, (byte)0b01110100, (byte)0b00100101,
		};

		assertArrayEquals(
			result,
			bytes
		);

		FileIO.WriteBytesToFile(FileIO.to0, bytes);
	}
}
