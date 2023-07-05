package crypto.model;

import java.math.BigInteger;

public class RSA {

	public static class RSA256 {
		public static final BigInteger testP = new BigInteger("340282366920938463463374607432841953291");
		public static final BigInteger testQ = new BigInteger("340282366920938463463374607431768212629");
		public static final int blockSize = 255; // 256 bytes - 1 no offset
	}

	public static class RSA512 {
		public static final BigInteger testP = new BigInteger("115792089237316195423570985008687907853269984665640564039457584007913130688523");
		public static final BigInteger testQ = new BigInteger("115792089237316195423570985008687907853269984665640564039457584007914203382263");
		public static final int blockSize = 511; // 512 bytes - 1 no offset
	}

	public static class RSA1024 {
		public static final BigInteger testP = new BigInteger("13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084171");
		public static final BigInteger testQ = new BigInteger("13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649007132903");
		public static final int blockSize = 1023; // 1024 bytes - 1 no offset
	}

	public static class RSA2048 {
		public static final BigInteger testP = new BigInteger("179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110541037861746687625057982134295314586803117506495636454552132846092481");
		public static final BigInteger testQ = new BigInteger("179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110540932549455019067871284216267630916370798611400235905440878535115721");
		public static final int blockSize = 2047; // 2048 bytes - 1 no offset
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

	public static BigInteger p, q, n, phi, e, d;

	public static void initialize(final BigInteger newP, final BigInteger newQ) {
		final BigInteger minE = new BigInteger("65537");
		p = newP;
		q = newQ;
		n = p.multiply(q);
		phi = (p.subtract(BigInteger.ONE)).multiply(q.subtract(BigInteger.ONE));
		e = Generation.generateE(phi, minE);
		d = Generation.generateD(phi, e);
	}

	public static byte[] encrypt(byte[] nocrypted) {
		return nocrypted;
	}

	public static byte[] decrypt(byte[] encrypted) {
		return encrypted;
	}

	//public static BigInteger encrypt (BigInteger m) {
	// return m.modPow(e,n);
	// }

    //public static BigInteger decrypt (BigInteger c) {
    //    return c.modPow(d,n);
    //}

    //public BigInteger getE() {
    //    return e;
    //}

    //public BigInteger getD() {
    //    return d;
    //}

}
