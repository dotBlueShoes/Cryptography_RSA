package crypto.model;

import java.math.BigInteger;

public class RSA {

	public static class RSA256 {
		// 256 bytes - 1 no offset
		public static final int blockSize = 255;
	}

	public static class RSA512 {
		// 256 bytes - 1 no offset
		public static final int blockSize = 511;
	}

	public static class RSA1024 {
		// 256 bytes - 1 no offset
		public static final int blockSize = 1023;
	}

	public static class RSA2048 {
		// 256 bytes - 1 no offset
		public static final int blockSize = 2047;
	}

	public static byte[] bigIntegerToBytes(final BigInteger value) {
		byte[] bytes = value.toByteArray();
		byte[] result = new byte[bytes.length];

		for (int i = 0, j = result.length - 1; j > 0; i++, j--)
			result[j] = bytes[i];

		System.out.print("\n\nResult: " +  result[0] + "\n\n");

		//bytes = Arrays.copyOfRange(bytes, 1, bytes.length);
		//System.out.print(result[result.length - 1]);
		//if (result[0] == 0) {
		//	byte[] tmp = new byte[result.length - 1];
		//	System.arraycopy(result, 1, tmp, 0, tmp.length);
		//	result = tmp;
		//}

		return result;
	}

	// 0000'0000
	// 0010'0101
	// 1100'0101

	public static BigInteger bytesToBigInteger(final byte[] bytes) {
		byte[] formatted = new byte[bytes.length + 1];

		for (int i = 0, j = bytes.length; j > 0; i++, j--)
			formatted[j] = bytes[i];

		return new BigInteger(formatted);
	}

	// Bytes to BigInt
	// BigInt to Bytes
	// encryption, decryption tests

	static BigInteger p, q, n, phi, e, d;

	public static void initialize(final BigInteger p, final BigInteger q) {
		n = p.multiply(q);
		phi = (p.subtract(BigInteger.ONE)).multiply(q.subtract(BigInteger.ONE));
		e = Generation.generateE(phi);
		d = Generation.generateD(e, phi);

		//byte[] sample = { 0, 1, 2, 3, 4, 5, 6 };
		//BigInteger result = bytesToBigInteger(sample);
	}

	public static void encrypt() {

	}

	public static void decrypt() {

	}
     public static BigInteger encrypt (BigInteger m) {
         return m.modPow(e,n);
     }

    public static BigInteger dencrypt (BigInteger c) {
        return c.modPow(d,n);
    }

    public BigInteger getE() {
        return e;
    }

    public BigInteger getD() {
        return d;
    }

}
