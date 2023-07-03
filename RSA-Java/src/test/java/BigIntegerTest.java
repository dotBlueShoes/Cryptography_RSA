import org.junit.Test;

import java.math.BigInteger;
import java.nio.ByteBuffer;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

public class BigIntegerTest {

	@Test
	public void signumTest() {
		// Determines the sign of the BigInteger.
		assertEquals(1, BigInteger.TEN.signum());
		assertEquals(-1, BigInteger.TEN.negate().signum());
		assertEquals(0, BigInteger.ZERO.signum());
	}

	@Test
	public void magTest() {
		// Mag property stores the given value in an array using the binary representation.
		//  Groups them in 32-bit portions – a set of four bytes.
		//  - big-endian notation - The zeroth element of this array is the most significant int of the magnitude.
		assertEquals(new BigInteger("1"), new BigInteger(new byte[]{0b1}));
		assertEquals(new BigInteger("2"), new BigInteger(new byte[]{0b10}));
		assertEquals(new BigInteger("4"), new BigInteger(new byte[]{0b100}));
	}

	@Test
	public void negativeTest() {
		byte[] bytes = { -128 }; // 1000 0000
		assertEquals(new BigInteger("128"), new BigInteger(1, bytes));
		assertEquals(new BigInteger("-128"), new BigInteger(-1, bytes));

		//assertEquals("10000000", new BigInteger(1, bytes));
		//assertEquals("-10000000", new BigInteger(-1, bytes));
	}

	@Test
	public void sample() {
		BigInteger bi1 = BigInteger.ZERO.setBit(63);
		String str = bi1.toString(2);

		assertEquals(64, bi1.bitLength());
		assertEquals(1, bi1.signum());
		assertEquals("9223372036854775808", bi1.toString());
		assertEquals(BigInteger.ONE, bi1.subtract(BigInteger.valueOf(Long.MAX_VALUE)));

		assertEquals(64, str.length());
		assertTrue(str.matches("^10{63}$")); // 1000 0000 ... 0000

		{
			byte[] bytes = ByteBuffer.allocate(Long.BYTES).putLong(Long.MIN_VALUE).array();
			BigInteger bi2 = new BigInteger(1, bytes);
			assertEquals(bi1, bi2);
		}

	}

	@Test
	public void BigIntegerAdd() {
		BigInteger testSubject1 = new BigInteger("100000000000000000000000000000000000000000000000");
		BigInteger testSubject2 = new BigInteger("911111111111111111111111111111111111111111111111");
		BigInteger result = new BigInteger("1011111111111111111111111111111111111111111111111");

		assertEquals(result, testSubject1.add(testSubject2));
	}

	@Test
	public void BigIntegerSubtract() {
		BigInteger testSubject1 = new BigInteger("100000000000000000000000000000000000000000000000");
		BigInteger testSubject2 = new BigInteger("911111111111111111111111111111111111111111111111");
		BigInteger result = new BigInteger("811111111111111111111111111111111111111111111111");

		assertEquals(result, testSubject2.subtract(testSubject1));
	}

	@Test
	public void BigIntegerPowerMod() {
		BigInteger testSubject1 = new BigInteger("100000000000000000000000000000000000000000000000");
		BigInteger power = new BigInteger("911111111111111111111111111111111111111111111111");
		BigInteger mod = new BigInteger("67345623512356236236236236326326");
		BigInteger result = new BigInteger("59684624648632765396744309710582");

		assertEquals(result, testSubject1.modPow(power, mod));
	}

	@Test
	public void BigIntegerRSA256() {

	}

	@Test
	public void BigIntegerRSA512() {

	}

	@Test
	public void BigIntegerRSA1024() {

	}

	@Test
	public void BigIntegerRSA2048() {

	}

}
