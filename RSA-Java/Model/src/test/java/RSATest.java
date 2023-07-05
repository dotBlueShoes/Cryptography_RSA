import crypto.model.RSA;
import org.junit.Test;

import java.math.BigInteger;

import static org.junit.Assert.assertArrayEquals;

public class RSATest {

	public static class RSA256 {
		String textInput0 = "";
		String textInput1 = "ŁŹĄĄŚĄŚĄŚŃĘŚĘ$^(#6!@#^!#%!@$%!@^@#*$^IUIJEHAQEGQ@!@%RTFasfash(^&)%&*$%^@#t%";
		String textInput2 = "";
		String textInput3 = "";
	}

	@Test
	public void bigIntegerTest() {

		byte[] sample  = {
			//(byte)0b00000000,
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

		// 0, -128, -92, 4, -62, -61, 116, 44, 82, -31, 40, -106, -15, 62, 27, 22, -108, 30, 25, -73, 28, -89, -7, -86, 92, -114, 59, -105, -74, -123, 113, 125

		//System.out.print(sample[0]);
		//byte[] sample = { 0, 1, 2, 3, 4, 5, 6 };
		BigInteger temp = RSA.bytesToBigInteger(sample);

		byte[] result = RSA.bigIntegerToBytes(temp);

		assertArrayEquals(
			sample,
			result
		);
	}

	@Test
	public void sampleTest() {

		// Test for (0-block) size
		// Test for (<block) size
		// Test for (block) size
		// Test for (>block) size

	}

}
